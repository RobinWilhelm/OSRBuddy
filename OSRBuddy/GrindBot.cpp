#include "GrindBot.h"
#include "OSRAPI.h"
#include "SDK/AtumApplication.h"
#include "OSRBuddy.h"
#include <string> 
#include "KitBot.h"

#define TARGET_LOCK_THRESHOLD    45.0f
#define TARGETING_SPEED 0.1f

  
GrindBot::GrindBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
    m_current_state = GrindBot::State::WAITING;
    m_on_target = false;
    m_target = nullptr;
    m_kitbot = nullptr;
    m_get_new_target = true;   
    m_inv_action_check_time = 0ms;
    m_update_mob_list_check_time = 0ms;
    m_mobs.clear(); 
    m_clean_inventory = false;
    m_only_clean_while_overheat = false;
    m_only_clean_while_stopped = false;
    m_open_watermelongift = true;
    m_open_spicapsule = true;
    m_open_fantasyglobemineralcapsule = true;
    m_open_mineralcapsule = true;
    m_open_wpcapsule = true;

    m_shoot_all_goldies = true;
    m_front_only = true;
    m_humanized_overshoot = true;
    m_humanized_target_delay_min = MIN_NEW_TARGET_DELAY_TIME.count();
    m_humanized_target_delay_max = MAX_NEW_TARGET_DELAY_TIME.count();
    m_target_mode = TargetMode::CrosshairDistance;
}   

void GrindBot::Tick()
{                           
    UpdateCheckTime();
    TickInventoryCleaning();

    if (!IsEnabled() || OSR_API->GetPlayerGearType() != GearType::AGear) {
        return;
    }  

    UpdateGrindMobInfo();


    if (OSR_API->IsShuttleDead()) {
        return;
    }

    if (m_get_new_target && m_shoot_new_target_delay <= 0ms)
    { 
        // try to find a close target first, to prevent getting rammed
        m_target = FindNewTarget(250, m_front_only);
        if (!m_target)
        {
            m_target = FindNewTarget(OSR_API->GetRadarRangePrimary() * 1.30f - 50, m_front_only);
        }      

        if (m_target)
        {
            OSR_API->SetTarget(m_target);
            m_on_target = false;
            m_get_new_target = false;
            m_no_target_time = 0ms;
        }
    }  
 
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
            CMonsterData* closetarget = FindNewTarget(250, m_front_only);
            if (closetarget) 
            {
                m_target = closetarget;
                OSR_API->SetTarget(m_target);
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
                //ImGui::BeginColumns("SettingsColumns", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
                //{
                    //ImGui::SetColumnWidth(0, 250);
                    const char* items[] = { "Gear distance", "Crosshair distance" };
                    ImGui::ComboEx("Target Mode:", reinterpret_cast<int*>(&m_target_mode), items, 2, -1, true, 150);
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("Gear distance: Will shoot the nearest mob first.\nCrosshair distance: Will shoot the mob closest to the crosshair first.");
                    }
                    ImGui::Checkbox("Shoot and prio all goldies", &m_shoot_all_goldies);
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("Will shoot an prioritise all gold mobs, even if they are not in the monster selection list yet.");
                    }  
                //}
                //ImGui::NextColumn();
                //{
                    ImGui::Checkbox("Visible only", &m_front_only);
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("Will shoot only visible mobs in front of the player.");
                    }
                    ImGui::Checkbox("Overshoot", &m_humanized_overshoot);
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("Will continue to shoot for some time after a mob died.");
                    }
                //}
                //ImGui::EndColumns();     

                ImGui::NewLine();
                ImGui::Text("Targeting delay in milliseconds:");
                ImGui::PushItemWidth(125);
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
            }
            ImGui::EndDisabledMode();

            ImGui::NewLine();
            ImGui::Separator();
            ImGui::Text("Inventory Cleaning");
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("This works for all gears. Grindbot does not have to be enabled for this to work.");
            }
            ImGui::Separator();

            ImGui::Checkbox("Active", &m_clean_inventory);
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Will automatically open the below specified items.");
            }
            ImGui::SameLine();
            ImGui::Checkbox("Stopped", &m_only_clean_while_stopped);
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Only clean inventory while gear is stopped.");
            }
            ImGui::SameLine();
            ImGui::Checkbox("Overheated", &m_only_clean_while_overheat);
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Only clean inventory standard weapon is overheated.");
            }

            ImGui::NewLine();
            ImGui::BeginColumns("InventoryCleaningColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
            {
                ImGui::Checkbox("Watermelon Gifts", &m_open_watermelongift);
                ImGui::Checkbox("SPI Capsules", &m_open_spicapsule);
                ImGui::Checkbox("Fantasy Globe MC", &m_open_fantasyglobemineralcapsule);
            }
            ImGui::NextColumn();
            {
                ImGui::Checkbox("Mineral Capsules", &m_open_mineralcapsule);
                ImGui::Checkbox("WP Capsules", &m_open_wpcapsule);
            }
            ImGui::EndColumns(); 
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

            ImGui::SetNextWindowSize(ImVec2(200.0f, 320.0f));
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
                if (monsterinfo != m_mobs.end())                 {
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

    POINT curPos;
    m_buddy->GetCursorPosition(&curPos);
    ScreenToClient(OSR_API->GetAtumApplication()->m_hWnd, &curPos);  

    if (front_only)
    {
        for (auto& monster : OSR_API->GetSceneData()->m_vecMonsterRenderList)
        {
            if (!IsValidTargetMonster(monster)) {
                continue;
            }

            if (GetTargetDistance(monster) > max_distance) {
                continue;
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
                    POINT delta;
                    delta.x = curPos.x - monster->m_nObjScreenX;
                    delta.y = curPos.y - monster->m_nObjScreenY;
                    dist = static_cast<float>(sqrt(delta.x * delta.x + delta.y * delta.y));
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
        }
    }
    else
    {
    // search all mobs
        for (auto& monster : OSR_API->GetSceneData()->m_mapMonsterList)
        {
            if (!IsValidTargetMonster(monster.second)) {
                continue;
            } 

            if (GetTargetDistance(monster.second) > max_distance) {
                continue;
            }

            if (CanShootAtTarget(monster.second))
            {
                float dist = 9999999.0f;
                switch (m_target_mode)
                {
                case TargetMode::GearDistance:
                    dist = GetTargetDistance(monster.second);
                    break;
                case TargetMode::CrosshairDistance:
                    POINT delta;
                    delta.x = curPos.x - monster.second->m_nObjScreenX;
                    delta.y = curPos.y - monster.second->m_nObjScreenY;
                    dist = static_cast<float>(sqrt(delta.x * delta.x + delta.y * delta.y));
                    break;
                }

                if (dist < min_distance)
                {
                    min_distance = dist;
                    newtarget = monster.second;
                }

                auto monsterinfo = FindGrindMonsterInfo(monster.second->m_pMonsterInfo->MonsterUnitKind);
                if (monsterinfo->second.priority && dist < min_distance_prio)
                {
                    min_distance_prio = dist;
                    newtarget_prio = monster.second;
                }                  
            }
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

        int delta_x = (targetPos.x - curPos.x) * TARGETING_SPEED;
        int delta_y = (targetPos.y - curPos.y) * TARGETING_SPEED; 

        if (targetPos.x + TARGET_LOCK_THRESHOLD < curPos.x ||
            targetPos.x - TARGET_LOCK_THRESHOLD > curPos.x || 
            targetPos.y + TARGET_LOCK_THRESHOLD < curPos.y ||
            targetPos.y - TARGET_LOCK_THRESHOLD > curPos.y)
        {   
            // aim to target slowly
            m_buddy->SetCursorPosition(curPos.x + delta_x, curPos.y + delta_y);
        }
        else
        {
            // lock target
            m_buddy->SetCursorPosition(targetPos.x, targetPos.y);
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

bool GrindBot::InventoryActionCheckTimeReady()
{
    return m_inv_action_check_time <= 0ms;
}

void GrindBot::ResetInventoryActionCheckTime()
{
    m_inv_action_check_time = CAPSULE_OPEN_REATTACK + std::chrono::milliseconds(m_buddy->GetRandInt32(0, 300));
}

bool GrindBot::ShouldCheck_GrindMobs()
{
    return m_update_mob_list_check_time <= 0ms;
}

void GrindBot::Reset_GrindMobsCheckTime()
{
    m_inv_action_check_time = UPDATE_GRINDMOBS_TIME;
}

void GrindBot::Reset_NewTargetDelayTime()
{
    m_shoot_new_target_delay = std::chrono::milliseconds(m_buddy->GetRandInt32(m_humanized_target_delay_min, m_humanized_target_delay_max));
}

void GrindBot::UpdateCheckTime()
{   
    if (m_inv_action_check_time > 0ms) {
        m_inv_action_check_time -= std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
    }
    if (m_inv_action_check_time < 0ms) {
        m_inv_action_check_time = 0ms;
    }

    if (m_update_mob_list_check_time > 0ms) {
        m_update_mob_list_check_time -= std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
    }
    if (m_update_mob_list_check_time < 0ms) {
        m_update_mob_list_check_time = 0ms;
    }
    
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
    if (ShouldCheck_GrindMobs())
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

void GrindBot::TickInventoryCleaning()
{   
    if (m_clean_inventory && (!m_only_clean_while_stopped || OSR_API->GetAtumApplication()->m_pShuttleChild->m_bUnitStop)
        && (!m_only_clean_while_overheat || m_current_state == GrindBot::State::OVERHEATED))
    {  
        if (InventoryActionCheckTimeReady())
        {
            if (m_open_mineralcapsule && TryOpenCapsule(ItemNumber::Mineral_Capsule)) {
                return;
            }

            if (m_open_fantasyglobemineralcapsule && TryOpenCapsule(ItemNumber::Fantasy_Globe_Mineral_Capsule)) {
                return;
            }

            if (m_open_watermelongift && TryOpenCapsule(ItemNumber::Square_Watermelon_Gift)) {
                return;
            }

            if (m_open_spicapsule && TryOpenCapsule(ItemNumber::SPI_capsule)) {
                return;
            }

            if (m_open_wpcapsule)
            {
                if (TryOpenCapsule(ItemNumber::WP_Capsule_100)) {
                    return;
                }

                if (TryOpenCapsule(ItemNumber::WP_Capsule_500)) {
                    return;
                }

                if (TryOpenCapsule(ItemNumber::WP_Capsule_1000)) {
                    return;
                }
            }
        }
    }
}

bool GrindBot::TryOpenCapsule(ItemNumber capsule)
{
    CItemInfo* item = OSR_API->FindItemInInventoryByItemNum(capsule);
    if (item)
    {
        OSR_API->SendUseItem(item);
        ResetInventoryActionCheckTime();
        return true;
    }
    return false;
}

bool GrindBot::IsMonsterDead(CMonsterData* monster)
{
    if (monster->m_dwState == _FALLING || monster->m_dwState == _FALLEN || monster->m_dwState == _EXPLODING || monster->m_dwState == _EXPLODED || monster->m_dwState == _AUTODESTROYED) {
        return true;
    }

    if (monster->m_info.CurrentHP == 0) {
        return true;
    }

    return false;
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

    m_mobs.clear();

    // sommer event special, always add these monster to the list
    GrindMonsterInfo gmi;
    gmi.clean_name = "Dropped Ball";
    gmi.goldy = true;
    gmi.killed = 0;
    gmi.priority = false;
    gmi.shoot = false;              
    m_mobs.insert({ 2098100 , gmi});
    gmi.clean_name = "Flying Ball";  
    m_mobs.insert({ 2098000 , gmi });  

    m_grinding_map = OSR_API->GetCurrentMapChannelIndex().MapIndex;    

    m_clean_inventory = true;

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

    OSR_API->UsePrimaryWeapon(false);
    OSR_API->UseSecondaryWeapon(false);
}

void GrindBot::OnDisable()
{
    m_grinding_map = 0;
    if (m_kitbot) {
        m_kitbot->Enable(false);
    }
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
