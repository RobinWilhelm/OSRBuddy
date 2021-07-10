#include "GrindBot.h"
#include "OSRAPI.h"
#include "SDK/AtumApplication.h"
#include "OSRBuddy.h"
#include <string> 
#include "KitBot.h"
#include "Miscellaneous.h"
#include "D3D9Renderer.h"
#include <cmath>
#include "Utility.h"

#define TARGET_LOCK_THRESHOLD    45.0f

  
GrindBot::GrindBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
    m_current_state = GrindBot::State::WAITING;
    m_on_target = false;
    m_target = nullptr;
    m_kitbot = nullptr;
    m_get_new_target = true;   

    m_mobs.clear(); 

    m_shoot_all_goldies = true;
    m_front_only = true;
    m_humanized_overshoot = true;
    m_humanized_target_delay_min = MIN_NEW_TARGET_DELAY_TIME.count();
    m_humanized_target_delay_max = MAX_NEW_TARGET_DELAY_TIME.count();
    m_target_mode = TargetMode::CrosshairDistance;


    m_smoothtype = SmoothType::Time;
    m_smooth_factor_distance = 0.5f;
    m_smooth_factor_time = 0.5f;

    m_aimtime_current = 0ms;
    m_aimtime_final = 0ms;
    m_anti_ram = true;

    m_update_mobs_timer = BuddyTimer(UPDATE_GRINDMOBS_TIME);
}   

void GrindBot::Tick()
{                           
    UpdateCheckTime();

    if (!IsEnabled() || OSR_API->GetPlayerGearType() != GearType::AGear) {
        return;
    }  

    UpdateGrindMobInfo();


    if (OSR_API->IsShuttleDead()) {
        return;
    }

    GetNewTarget();
 
    switch (m_current_state)
    {
    case GrindBot::State::WAITING:   
        // show the user what the next targets would be
        m_get_new_target = true;                             
        break;

    case GrindBot::State::SIEGEING:
        UpdateGrindingTime();
        // check for overheat and valid target first
        if (OSR_API->GetPrimaryWeapon()->m_bOverHeat) 
        {
            ChangeState(GrindBot::State::OVERHEATED);
            return;
        }

        // ------------------------ 
        // re-think this
        if (!m_target)
        {
            m_no_target_time += std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
            if ((m_no_target_time - m_shoot_new_target_delay) >= NO_TARGET_STOP_SHOOTING_TIME)
            {
                OSR_API->UsePrimaryWeapon(false);
                OSR_API->UseSecondaryWeapon(false);
            }  

            if (m_no_target_time >= NO_TARGET_SIEGE_DISABLE_TIME) {
                m_kitbot->ToggleSKill(SkillType::Siege_Mode, false);
            }
        } 
        // ------------------------ 

        if (!IsValidTargetMonster(m_target) || !CanShootAtTarget(m_target))
        {
            if (m_target)
            {
                Reset_NewTargetDelayTime();
                m_target = nullptr;
            }
            m_get_new_target = true;
            return;
        }                 

        if (!m_kitbot->ToggleSKill(SkillType::Siege_Mode, true)) {
            return;
        }

        AimAtTarget(m_target);
        if (m_on_target)
        {
            OSR_API->UsePrimaryWeapon(true);
            // only use secondary if in radar range          
            OSR_API->UseSecondaryWeapon(GetTargetDistance(m_target) < OSR_API->GetRadarRangeSecondary());        
        } 
        else
        {
            if (!m_humanized_overshoot) 
            {
                OSR_API->UsePrimaryWeapon(false);
                OSR_API->UseSecondaryWeapon(false);
            }
        }
        break;

    case GrindBot::State::OVERHEATED: 
        UpdateGrindingTime();
        if (!OSR_API->GetPrimaryWeapon()->m_bOverHeat) 
        {
            // check if a monster has come close to the player  
            if (m_anti_ram)
            {
                CMonsterData* closetarget = FindNewTarget(250, m_front_only);
                if (closetarget) {
                    ChangeTarget(closetarget);
                }
            }            
            ChangeState(GrindBot::State::SIEGEING);
        }       
        break;
    }
}
   	 
void GrindBot::RenderImGui()
{
    if (!DrawEnableCheckBox()) {
        //return;
    } 
    ImGui::NewLine();
    ImGui::BeginColumns("GrindBotColumns", 2, ImGuiColumnsFlags_NoResize);
    {
        ImGui::SetColumnWidth(0, 400);
        ImGui::BeginChild("GrindBotColumn1", ImVec2(), false);
        {              
            ImGui::BeginDisabledMode(OSR_API->GetPlayerGearType() != GearType::AGear || !IsEnabled());
            {   
                ImGui::Separator();
                ImGui::Text("Settings");
                ImGui::Separator();
                ImGui::Text("Start / Stop hotkey: \"U\"");        
  
                const char* items[] = { "Gear distance", "Crosshair distance" };
                ImGui::ComboEx("Target Mode:", reinterpret_cast<int*>(&m_target_mode), items, 2, -1, true, 150);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Gear distance: Will shoot the nearest mob first.\nCrosshair distance: Will shoot the mob closest to the crosshair first.");
                }
                ImGui::Checkbox("Shoot and prio all goldies", &m_shoot_all_goldies);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Will shoot an prioritise all gold mobs, even if they are not in the monster selection list yet.");
                }                         
                ImGui::Checkbox("Visible only", &m_front_only);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Will shoot only visible mobs in front of the player.");
                }
                ImGui::Checkbox("Overshoot", &m_humanized_overshoot);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Will continue to shoot for some time after a mob died.");
                }                
                ImGui::Checkbox("Anti ram", &m_anti_ram);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Will prioritise close targets that could ram the gear and turn it upside down.");
                }
                  
                ImGui::NewLine();
                ImGui::Text("Targeting delay");
                ImGui::Separator();
                ImGui::BeginColumns("TargetDelayColumns", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
                { 
                    if(ImGui::SliderInt("Min", &m_humanized_target_delay_min, 0, 500))
                    {
                        if (m_humanized_target_delay_min > m_humanized_target_delay_max) {
                            m_humanized_target_delay_min = m_humanized_target_delay_max;
                        }
                    }
                }
                ImGui::NextColumn();
                {
                    if (ImGui::SliderInt("Max", &m_humanized_target_delay_max, 0, 500)) 
                    { 
                        if (m_humanized_target_delay_min > m_humanized_target_delay_max) {
                            m_humanized_target_delay_max = m_humanized_target_delay_min;
                        }
                    }
                }
                ImGui::EndColumns();

                ImGui::NewLine();
                ImGui::Text("Aim smoothing");
                ImGui::Separator();
                const char* smoothitems[] = { "Distance", "Time" };
                ImGui::ComboEx("Type:", reinterpret_cast<int*>(&m_smoothtype), smoothitems, 2, -1, true, 100);

                ImGui::Text("Factor:");
                ImGui::SameLine();
                ImGui::PushItemWidth(150);
                if (m_smoothtype == SmoothType::Time) {
                    ImGui::SliderFloat("###timeSmoothfactor", &m_smooth_factor_time, 0, 1);
                }
                else {
                    ImGui::SliderFloat("###distanceSmoothfactor", &m_smooth_factor_distance, 0, 1);
                }
                ImGui::PopItemWidth();
                /*
                ImGui::BeginColumns("AimSmoothingColumns", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
                {
                    if (m_smoothtype == SmoothType::Time) {
                        ImGui::SliderFloat("X", &m_time_smooth_x, 0, 1);
                    }
                    else {
                        ImGui::SliderFloat("X", &m_dist_smooth_x, 0, 1);
                    }
                }
                ImGui::NextColumn();
                {
                    if (m_smoothtype == SmoothType::Time) {
                        ImGui::SliderFloat("Y", &m_time_smooth_y, 0, 1);
                    }
                    else {
                        ImGui::SliderFloat("Y", &m_dist_smooth_y, 0, 1);
                    }
                }
                ImGui::EndColumns();
                */
            }
            ImGui::EndDisabledMode();
        }
        ImGui::EndChild();
    }
    ImGui::NextColumn();
    {
        ImGui::BeginChild("GrindBotColumn2", ImVec2(), false);
        {   
            ImGui::Separator();
            ImGui::Text("Statistics");
            ImGui::Separator();

            std::string grindtime = "Grinding Time: " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(m_grinding_time).count());
            ImGui::Text(grindtime.c_str());

            std::string mobskilled = "Mobs killed: " + std::to_string(m_total_mobs_killed);
            ImGui::Text(mobskilled.c_str());

            ImGui::SetNextWindowSize(ImVec2(300.0f, 200.0f));
            if (ImGui::BeginPopup("GrindBotStatisticsPopup"/*, &m_popup_statistics_open*/, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar))
            {  
                ImGui::BeginColumns("MonsterStatisticColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
                {
                    for (auto& monsterinfo : m_mobs)
                    {
                        if (monsterinfo.second.killed > 0)
                        {
                            ImGui::Text(monsterinfo.second.clean_name.c_str());
                            ImGui::NextColumn();
                            ImGui::Text(std::to_string(monsterinfo.second.killed).c_str());
                            ImGui::NextColumn();
                        }
                    }
                }
                ImGui::EndColumns();
                ImGui::EndPopup();
            }
            ImGui::NewLine();
            if (ImGui::Button("Details")) {
                ImGui::OpenPopup("GrindBotStatisticsPopup");
            }

            ImGui::NewLine();
            ImGui::BeginDisabledMode(OSR_API->GetPlayerGearType() != GearType::AGear || !IsEnabled());
            {
                ImGui::Separator();
                ImGui::Text("Monster Selection");
                ImGui::Separator();

                ImGui::BeginColumns("MonsterSelectColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
                {
                    ImGui::Text("Shoot at");
                    ImGui::NextColumn();
                    ImGui::Text("Prioritise");
                    ImGui::NextColumn();
                    for (auto& monsterinfo : m_mobs)
                    {
                        ImGui::Checkbox(monsterinfo.second.clean_name.c_str(), &monsterinfo.second.shoot);
                        ImGui::NextColumn();
                        ImGui::Checkbox(("###" + monsterinfo.second.clean_name).c_str(), &monsterinfo.second.priority);
                        ImGui::NextColumn();
                    }
                }
                ImGui::EndColumns();
            }
            ImGui::EndDisabledMode();
        }
        ImGui::EndChild();
    }
    ImGui::EndColumns();
}

std::string GrindBot::GetName() const
{
	return "GrindBot";
}

bool GrindBot::OnReadPacket(unsigned short msgtype, byte* packet)
{
    if (!IsEnabled())
        return false;

    switch (msgtype)
    {
    case T_FC_MONSTER_CHANGE_HP:
        if (m_target && ((MSG_FC_MONSTER_CHANGE_HP*)packet)->MonsterIndex == m_target->m_info.MonsterIndex)
        {             
            if (((MSG_FC_MONSTER_CHANGE_HP*)packet)->CurrentHP <= 0)
            {
                //um_target->m_info.CurrentHP = 0; 
                auto monsterinfo = FindGrindMonsterInfo(m_target->m_info.MonsterUnitKind);
                if (monsterinfo != m_mobs.end())                 
                {
                    monsterinfo->second.killed++;
                    m_total_mobs_killed++;
                }

                Reset_NewTargetDelayTime();
                m_target = nullptr;
            }              
        }
        break;
    }
 
    return false;
}

int GrindBot::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{ 
    switch (msg)
    {
    case WM_KEYUP:
        switch (wParam)
        {
        case 0x55: // u                                              
            ToggleGrinding();
            return 1;
        }
    }
    return 0;
}

float GrindBot::GetTargetDistance(CAtumData* m_target)
{
    if (!m_target) {
        return 0.0f;
    }

    D3DXVECTOR3 delta = m_target->m_vPos - OSR_API->GetAtumApplication()->m_pShuttleChild->m_vPos;
    return D3DXVec3Length(&delta);  
}

bool GrindBot::CanShootAtTarget(CUnitData* target)
{
    if (!target || target->m_bIsUnderWater) {
        return false;
    }

    if (GetTargetDistance(target) > OSR_API->GetRadarRangePrimary() * 1.30f) {
        return false;
    }
 
    return OSR_API->IsHitablePrimary(target);
}

bool GrindBot::IsValidTargetMonster(CMonsterData* monster)
{
    if (!monster) {
        return false;
    }  

    if ( IsMonsterDead(monster)) {
        return false;
    }

    auto monsterinfo = FindGrindMonsterInfo(monster->m_info.MonsterUnitKind);
    if(monsterinfo != m_mobs.end() && monsterinfo->second.shoot) {
            return true;
    }
    return false;
}

CMonsterData* GrindBot::FindNewTarget(float max_distance, bool front_only)
{ 
    float min_distance = 999999;
    CMonsterData* newtarget = nullptr;

    float min_distance_prio = 999999;
    CMonsterData* newtarget_prio = nullptr;   

    D3DXVECTOR3 mousepos = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vMousePos;
    D3DXVECTOR3 mousedir = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vMouseDir;

    D3DXVECTOR3 sourceDir = mousedir;
    D3DXVec3Normalize(&sourceDir, &sourceDir);

    auto checkTarget = [&](CMonsterData* monster) -> bool
    {
        if (!IsValidTargetMonster(monster)) {
            return false;
        }

        if (GetTargetDistance(monster) > max_distance) {
            return false;
        }

        if (CanShootAtTarget(monster))
        {
            float dist = 9999999.0f;
            switch (m_target_mode)
            {
            case TargetMode::GearDistance:
                dist = GetTargetDistance(monster);
                break;
            case TargetMode::CrosshairDistance:                   
                D3DXVECTOR3 targetDir = monster->m_vPos - mousepos;
                D3DXVec3Normalize(&targetDir, &targetDir);
                // gets the angle between two vectors
                dist = acos(D3DXVec3Dot(&sourceDir, &targetDir));  
                break;
            }

            if (dist < min_distance)
            {
                min_distance = dist;
                newtarget = monster;
            }

            auto monsterinfo = FindGrindMonsterInfo(monster->m_pMonsterInfo->MonsterUnitKind);
            if (monsterinfo->second.priority && dist < min_distance_prio)
            {
                min_distance_prio = dist;
                newtarget_prio = monster;
            }
        }
    };    
           
    if (front_only)
    {
        for (auto& monster : OSR_API->GetSceneData()->m_vecMonsterRenderList)
        {   
            checkTarget(monster);
        }
    }
    else
    {
    // search all mobs
        for (auto& monster : OSR_API->GetSceneData()->m_mapMonsterList)
        {
            checkTarget(monster.second);
        }        
    } 
   
    return (newtarget_prio) ? newtarget_prio : newtarget;
}

void GrindBot::AimAtTarget(CMonsterData* m_target)
{
    if (m_target)
    {
        POINT curPos;
        m_buddy->GetCursorPosition(&curPos);

        POINT targetPos;
        targetPos.x = m_target->m_nObjScreenX;
        targetPos.y = m_target->m_nObjScreenY;

        ClientToScreen(OSR_API->GetAtumApplication()->m_hWnd, &targetPos);
           
        if (targetPos.x + TARGET_LOCK_THRESHOLD < curPos.x ||
            targetPos.x - TARGET_LOCK_THRESHOLD > curPos.x || 
            targetPos.y + TARGET_LOCK_THRESHOLD < curPos.y ||
            targetPos.y - TARGET_LOCK_THRESHOLD > curPos.y)
        { 
            
            D3DXVECTOR3 mousepos = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vMousePos;
            D3DXVECTOR3 mousedir = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vMouseDir;
 
            D3DXVECTOR3 target = m_target->m_vPos - mousepos;
            D3DXVec3Normalize(&target, &target);

            D3DXVECTOR3 source = mousedir;
            D3DXVec3Normalize(&source, &source);
            float angle = acos(D3DXVec3Dot(&source, &target));

            D3DXVECTOR3 rotAxis;
            D3DXVec3Cross(&rotAxis, &source, &target);
            D3DXVec3Normalize(&rotAxis, &rotAxis);
            static D3DXMATRIX rotationMatrix;
            D3DXMatrixIdentity(&rotationMatrix);

            SmoothDeltaAngle(angle);
            D3DXMatrixRotationAxis(&rotationMatrix, &rotAxis, angle);

            D3DXVECTOR3 endpoint;
            D3DXVec3TransformCoord(&endpoint, &mousedir, &rotationMatrix);

            // set weapon direction
            D3DXVec3Normalize(&OSR_API->GetAtumApplication()->m_pShuttleChild->m_vWeaponVel, &endpoint);  

            // center the mouse
            POINT pt;	                           
            auto atumapp = OSR_API->GetAtumApplication();
            pt.x = atumapp->m_d3dsdBackBuffer.Width / 2;
            pt.y = atumapp->m_d3dsdBackBuffer.Height / 2;    
            ClientToScreen(OSR_API->GetAtumApplication()->m_hWnd, &pt);
            m_buddy->SetCursorPosition(pt.x, pt.y);
            return;
        }
        else
        {
            m_on_target = true;
        }
    }
}     

void GrindBot::ToggleGrinding()
{
    switch (m_current_state)
    {
    case GrindBot::State::WAITING:
        m_buddy->EnableMouseEmulation(true);
        ChangeState(GrindBot::State::SIEGEING);   
        m_grinding_start = std::chrono::system_clock::now();
        break;
    case GrindBot::State::SIEGEING:
    case GrindBot::State::OVERHEATED:
        m_buddy->EnableMouseEmulation(false);
        ChangeState(GrindBot::State::WAITING);
        m_grinding_time_total = m_grinding_time;
        break;
    default:
        break;
    }  
}
  
void GrindBot::Reset_NewTargetDelayTime()
{
    m_shoot_new_target_delay = std::chrono::milliseconds(Utility::GetRandInt32(m_humanized_target_delay_min, m_humanized_target_delay_max));
}

void GrindBot::UpdateCheckTime()
{
    if (m_shoot_new_target_delay > 0ms) {
        m_shoot_new_target_delay -= std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
    }
    if (m_shoot_new_target_delay < 0ms) {
        m_shoot_new_target_delay = 0ms;
    }  
}

void GrindBot::UpdateGrindingTime()
{
    auto current = std::chrono::system_clock::now();
    m_grinding_time = m_grinding_time_total + std::chrono::duration_cast<std::chrono::milliseconds>(current - m_grinding_start);
}

void GrindBot::UpdateGrindMobInfo()
{   
    if (m_update_mobs_timer.IsReady())
    {
        if (m_grinding_map != 0 && m_grinding_map == OSR_API->GetCurrentMapChannelIndex().MapIndex)
        {
            for (auto& monster : OSR_API->GetSceneData()->m_mapMonsterList)
            {
                // check if mob is already in the map, if not -> insert it
                auto monsterinfo = m_mobs.find(monster.second->m_info.MonsterUnitKind);
                if (monsterinfo == m_mobs.end())
                {
                    GrindMonsterInfo gmi;
                    gmi.clean_name = std::string(monster.second->m_pMonsterInfo->MonsterName);
                    if (gmi.clean_name.find("Scout Guard") != string::npos) {
                        continue;
                    }

                    gmi.shoot = false;
                    gmi.priority = false;
                    gmi.goldy = false;
                    gmi.killed = 0;

                    if (gmi.clean_name[0] == '\\')
                    {
                        gmi.clean_name.erase(gmi.clean_name.begin(), gmi.clean_name.begin() + 2);
                        gmi.clean_name.erase(gmi.clean_name.end() - 2, gmi.clean_name.end());
                        gmi.goldy = true;

                        if (m_shoot_all_goldies) 
                        {
                            gmi.shoot = true;
                            gmi.priority = true;
                        }
                    }
              
                    m_mobs.insert({ monster.second->m_info.MonsterUnitKind, gmi });
                }
            }
        }
    }
}

std::map<INT, GrindMonsterInfo>::iterator GrindBot::FindGrindMonsterInfo(int monsterunitkind)
{
    return m_mobs.find(monsterunitkind);
}
     
bool GrindBot::IsMonsterDead(CMonsterData* monster)
{
    if (monster->m_dwState == _FALLING || monster->m_dwState == _FALLEN || monster->m_dwState == _EXPLODING || monster->m_dwState == _EXPLODED || monster->m_dwState == _AUTODESTROYED) {
        return true;
    }

    /*
    if (monster->m_info.CurrentHP == 0) {
        return true;
    }
    */
    return false;
}

void GrindBot::SmoothDeltaAngle(float& deltaAng)
{
    switch (m_smoothtype)
    {
    case SmoothType::Distance:
        deltaAng /= std::max(1.0f,(m_smooth_factor_distance * 50));
        break;
    case SmoothType::Time:
        float degree = RAD2DEG(deltaAng);  

        // new target
        if (m_aimtime_current == 0ms) {
            m_aimtime_final = std::chrono::milliseconds(static_cast<long>(std::max(degree, 30.0f)* std::max(0.1f, m_smooth_factor_time * 150)));
        }     
        m_aimtime_current += std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());

        if (m_aimtime_current > m_aimtime_final)
            m_aimtime_current = m_aimtime_final; 

        float percent = static_cast<float>(m_aimtime_current.count()) / static_cast<float>(m_aimtime_final.count());
        deltaAng *= percent;
        break;
    }
}

       
FeatureType GrindBot::GetType() const
{
	return FeatureType::GrindBot;
}

void GrindBot::OnEnable()
{
    if (OSR_API->GetPlayerGearType() != GearType::AGear) 
    {
        Enable(false); 
        return;
    }

    m_total_mobs_killed = 0;
    m_mobs.clear();

    // sommer event special, always add these monster to the list
    GrindMonsterInfo gmi;
    gmi.clean_name = "Dropped Ball";
    gmi.goldy = true;
    gmi.killed = 0;
    gmi.priority = true;
    gmi.shoot = true;
    m_mobs.insert({ 2098100 , gmi});
    gmi.clean_name = "Flying Ball";  
    m_mobs.insert({ 2098000 , gmi });  

    m_grinding_map = OSR_API->GetCurrentMapChannelIndex().MapIndex;    
                                   
    // reset grinding timer
    m_grinding_time = 0ms;
    m_grinding_time_total = 0ms;

    m_kitbot = static_cast<KitBuffBot*>(m_buddy->GetFeatureByType(FeatureType::KitBuffBot));
    if (m_kitbot)
    {   
        // set kit settings
        KitBuffBot::KitSettings kitbot_settings;
        ZeroMemory(&kitbot_settings, sizeof(KitBuffBot::KitSettings));

        kitbot_settings.kitmode = KitBuffBot::Mode::Humanized;
        kitbot_settings.use_energy_type_c = true;
        kitbot_settings.use_shield_type_c = true;
        kitbot_settings.use_ammobox       = true;

        kitbot_settings.use_spkit_type_c = true;
        kitbot_settings.spkit_type_c_minvalue = OSR_API->GetMaxSkillp() * 0.6f;

        kitbot_settings.use_spkit_type_b = true;
        kitbot_settings.spkit_type_b_minvalue = OSR_API->GetMaxSkillp()* 0.2f;

        m_kitbot->SetSettings(kitbot_settings);
        
        // add auto buffs
        m_kitbot->AddAutoBuff(SkillType::Fire_Shot);
        m_kitbot->AddAutoBuff(SkillType::Missile_Shot);
        m_kitbot->AddAutoBuff(SkillType::Concentration);

        m_kitbot->Enable(true);
    }

    m_miscfeatures = static_cast<Miscellaneous*>(m_buddy->GetFeatureByType(FeatureType::Miscellaneous));
    if (m_miscfeatures) {
        m_miscfeatures->ActivateInventoryCleaning(true);
    }

    OSR_API->UsePrimaryWeapon(false);
    OSR_API->UseSecondaryWeapon(false);
}

void GrindBot::OnDisable()
{
    OSR_API->UsePrimaryWeapon(false);
    OSR_API->UseSecondaryWeapon(false);

    m_grinding_map = 0;
    if (m_kitbot) {
        m_kitbot->Enable(false);
    }

    if (m_miscfeatures) {
        m_miscfeatures->ActivateInventoryCleaning(false);
    }
}

void GrindBot::Render(D3D9Renderer* renderer)
{
    /*
    if (IsEnabled() && m_target)
    {
        D3DXVECTOR3 mousepos = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vMousePos;
        D3DXVECTOR3 mousedir = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vMouseDir;
        D3DXVECTOR3 mouseUp = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vUp;
        D3DXVECTOR3 shuttlePos = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vPos;

        D3DXVECTOR3 weaponDir = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vWeaponVel;
        D3DXVECTOR3 weaponPos = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vWeaponPos;
        D3DXVECTOR3 weaponUp = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vWeaponUp;
                                                                                             
        D3DXVECTOR3 mousetarget = mousepos + mousedir;

        //QAngle targetAng = CalcAngle(mousepos, m_target->m_vPos);
        //QAngle localAng = CalcAngle(mousepos, mousetarget);
        //QAngle deltaAng = targetAng - localAng;

        D3DXVECTOR3 target = m_target->m_vPos - mousepos;
        D3DXVECTOR3 target_normalized;
        D3DXVec3Normalize(&target_normalized, &target);

        D3DXVECTOR3 source = mousedir;
        D3DXVec3Normalize(&source, &source);
        float angle = acos(D3DXVec3Dot(&source, &target_normalized));

        D3DXVECTOR3 rotAxis;
        D3DXVec3Cross(&rotAxis, &source, &target_normalized);
        D3DXVec3Normalize(&rotAxis, &rotAxis);
        
        D3DXMATRIX rot;

        for (int i = 1; i <= 100; i++)
        {
           
            QAngle new_localAng = localAng + (deltaAng / 100) * i;

            
            MathHelper::AngleVectors(new_localAng, &endpoint, NULL, NULL);
            
            
            float step = angle / 100 * i;
            D3DXMatrixRotationAxis(&rot, &rotAxis, step); 
            D3DXVECTOR3 endpoint;
            D3DXVec3TransformCoord(&endpoint, &mousedir, &rot);
            int screen_x, screen_y;
            OSR_API->WorldToScreen(mousepos + endpoint, screen_x, screen_y);

            D3D9Helper::SetRect(device, screen_x - 2, screen_y - 2, 5, 5, D3DCOLOR_ARGB(255, 0, 0, 255));
        }
    }
    */
}

void GrindBot::ChangeState(GrindBot::State newState)
{
    if (newState == m_current_state) {
        return;
    }

    switch (newState)
    {
    case GrindBot::State::WAITING:
        OSR_API->UsePrimaryWeapon(false);
        OSR_API->UseSecondaryWeapon(false);
        m_kitbot->ToggleSKill(SkillType::Siege_Mode, false);
        break;
    case GrindBot::State::SIEGEING:
        m_aimtime_current = 0ms;
        break;
    case GrindBot::State::OVERHEATED:
        OSR_API->UsePrimaryWeapon(false);
        OSR_API->UseSecondaryWeapon(false);
        m_kitbot->ToggleSKill(SkillType::Siege_Mode, false);
        break;
    default:
        break;
    }

    m_current_state = newState;
}

void GrindBot::ChangeTarget(CMonsterData* newTarget)
{
    m_target = newTarget;
    m_aimtime_current = 0ms;
    m_no_target_time = 0ms;
    m_on_target = false;
    OSR_API->SetTarget(m_target);
}

void GrindBot::GetNewTarget()
{
    if (m_get_new_target && m_shoot_new_target_delay <= 0ms)
    {
        CMonsterData* new_target = nullptr;
        // try to find a close target first, to prevent getting rammed
        if (m_anti_ram) {
            new_target = FindNewTarget(250, m_front_only);
        }

        if (!new_target) {
            new_target = FindNewTarget(OSR_API->GetRadarRangePrimary() * 1.30f - 50, m_front_only);
        }

        if (new_target)
        {
            ChangeTarget(new_target);
            m_get_new_target = false;
        }
    }
}
