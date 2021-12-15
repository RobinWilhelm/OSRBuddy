#include "osrb_pch.h"
#include "GrindBot.h"

#include "OSRAPI.h"
#include "OSRBuddy.h"
#include "KitBot.h"
#include "Miscellaneous.h"
#include "InventoryManager.h"
#include "D3D9Renderer.h"
#include "Utility.h"

#include "SDK/AtumApplication.h"

#include <cmath>
#include <string> 

#define TARGET_LOCK_THRESHOLD    45.0f

namespace Features
{
    GrindBot::GrindBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
    {
        m_current_state = GrindBot::State::WAITING;
        m_on_target = false;
        m_target = nullptr;
        m_kitbot = nullptr;
        m_get_new_target = true;   

        m_mobs.clear(); 

        m_shoot_all_goldies = true;
        m_visible_only = true;
        m_keep_shooting = true;
        m_target_delay_min = MIN_NEW_TARGET_DELAY_TIME.count();
        m_target_delay_max = MAX_NEW_TARGET_DELAY_TIME.count();
        m_target_mode = TargetMode::CrosshairDistance;


        m_smoothtype = SmoothType::Time;
        m_smooth_factor_distance = 0.5f;
        m_smooth_factor_time = 0.5f;

        m_aimtime_current = 0ms;
        m_aimtime_final = 0ms;
        m_anti_ram = true;

        m_awaiting_siege_toggle_ok = false;
        m_grinding_map = 0;
        m_grinding_time = 0s;
        m_grinding_time_total = 0s;
        m_miscfeatures = nullptr;
        m_no_target_time = 0s;
        m_prio_bossmonster = true;
        m_prioritise_closer_mobs = false;
        m_shoot_new_target_delay = 0s;
        m_total_mobs_killed = 0;

        m_currentBS = 0;
        m_nextBS = 0;
        m_selected = false;
        m_enable_bs_hotswap = false;
        m_select_swapbs = false;
        m_swapped = false;

        m_invenmanager = nullptr;
        m_update_mobs_timer = BuddyTimer(UPDATE_GRINDMOBS_TIME);
        m_vkc_toggle = VK_CONTROL;
        m_vkc_description = Utility::VirtualKeyCodeToString(m_vkc_toggle);
        m_wait_for_hotkey = false;
    }   

    void GrindBot::Tick()
    {                           
        UpdateCheckTime();

        if (!IsEnabled() || OSR_API->GetPlayerGearType() != GearType::AGear) {
            return;
        }  

        UpdateGrindMobInfo();    
        GetNewTarget();
 
        switch (m_current_state)
        {
        case GrindBot::State::WAITING:   
            // show the user what the next targets would be
            m_get_new_target = true;   
            if (m_select_swapbs)
            {
                CItemInfo* current = OSR_API->GetPrimaryWeapon()->m_pItemInfo;
                INVEN_DISPLAY_INFO* selected = OSR_API->GetSelectedItem();
                if (selected && selected->pItem->UniqueNumber != current->UniqueNumber && IsValidPrimaryWeapon(selected->pItem)) // didnt select the current bs	
                {
                    m_currentBS = current->UniqueNumber;
                    m_nextBS = selected->pItem->UniqueNumber;
                    m_select_swapbs = false;
                    m_selected = true;
                }
            }
            break;

        case GrindBot::State::SIEGEING:
            UpdateGrindingTime();
            if (OSR_API->IsShuttleDead() || !OSR_API->IsLanded())// turn of grind when gear is not landed anymore
            {
                ToggleGrinding();
                return;
            }

            // check for overheat and valid target first
            if (OSR_API->GetPrimaryWeapon()->m_bOverHeat) 
            {
                if (m_enable_bs_hotswap) {
                    m_swapped = false;
                }
                ChangeState(GrindBot::State::OVERHEATED);
                return;
            }

            // ------------------------ 
            // re-think this
            if (!m_target)
            {
                m_no_target_time += std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
                if (m_no_target_time >= NO_TARGET_SIEGE_DISABLE_TIME) 
                {
                    OSR_API->UsePrimaryWeapon(false);
                    OSR_API->UseSecondaryWeapon(false);
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
                OSR_API->UseSecondaryWeapon(GetTargetDistance(m_target) <= OSR_API->GetRadarRangeSecondary(true));        
            } 
            else
            {
                if (!m_keep_shooting) 
                {
                    OSR_API->UsePrimaryWeapon(false);
                    OSR_API->UseSecondaryWeapon(false);
                }
            }
            break;

        case GrindBot::State::OVERHEATED: 
            UpdateGrindingTime();
            if (OSR_API->IsShuttleDead() || !OSR_API->IsLanded())// turn of grind when gear is not landed anymore
            {
                ToggleGrinding();
                return;
            }
            if (m_enable_bs_hotswap && m_selected) {
                if (!m_swapped) 
                {
                    m_swapped = Swap();
                }
            }
            if (!OSR_API->GetPrimaryWeapon()->m_bOverHeat) 
            {
                // check if a monster has come close to the player  
                if (m_anti_ram)
                {
                    CMonsterData* closetarget = FindNewTarget(250, m_visible_only);
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
            ImGui::SetColumnWidth(0, 350);
            ImGui::BeginChild("GrindBotColumn1", ImVec2(), false);
            {              
                ImGui::BeginDisabledMode(OSR_API->GetPlayerGearType() != GearType::AGear || !IsEnabled());
                {   
                    //ImGui::Separator();
                    ImGui::Text("Settings");
                    ImGui::Separator();               

                    ImGui::Text("Start / Stop hotkey:");
                    ImGui::SameLine();
                    if (!m_wait_for_hotkey)
                    {
                        ImGui::Text(m_vkc_description.c_str());
                        ImGui::SameLine();
                        if (ImGui::Button("Select New")) {
                            m_wait_for_hotkey = true;
                        }
                    }
                    else
                    {
                        ImGui::Text("Waiting for keypress...");
                    }

                    const char* items[] = { "Gear distance", "Crosshair distance" };
                    ImGui::ComboEx("Target Mode:", reinterpret_cast<int*>(&m_target_mode), items, 2, -1, true, 150);
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("Gear distance: Will shoot the nearest mob first.\nCrosshair distance: Will shoot the mob closest to the crosshair first.");
                    }
                    ImGui::NewLine();

                    ImGui::BeginColumns("GrindBotFlagsColumns", 2, ImGuiColumnsFlags_NoResize);
                    {
                        ImGui::Checkbox("Auto goldies", &m_shoot_all_goldies);
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Will shoot an prioritise all gold mobs, even if they are not in the monster selection list yet.");
                        }
                        ImGui::Checkbox("Auto bosses", &m_prio_bossmonster);
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Will shoot an prioritise boss mobs, even if they are not in the monster selection list yet.");
                        }
                        ImGui::Checkbox("Visible only", &m_visible_only);
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Will shoot only visible mobs in front of the player.");
                        }
                    }
                    ImGui::NextColumn();
                    {
                        ImGui::Checkbox("Keep shooting", &m_keep_shooting);
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Will continue to shoot while aiming at the next target.");
                        }
                        ImGui::Checkbox("Anti ram", &m_anti_ram);
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Will prioritise close targets (250m).");
                        }
                    }
                    ImGui::EndColumns();
                    ImGui::NewLine();

   

                    //ImGui::NewLine();
                    ImGui::Text("Targeting delay:");
                    //ImGui::Separator();
                    ImGui::BeginColumns("TargetDelayColumns", 2, ImGuiColumnsFlags_NoBorder | ImGuiColumnsFlags_NoResize);
                    { 
                        if(ImGui::SliderInt("Min", &m_target_delay_min, 0, 500))
                        {
                            if (m_target_delay_min > m_target_delay_max) {
                                m_target_delay_min = m_target_delay_max;
                            }
                        }
                    }
                    ImGui::NextColumn();
                    {
                        if (ImGui::SliderInt("Max", &m_target_delay_max, 0, 500)) 
                        { 
                            if (m_target_delay_min > m_target_delay_max) {
                                m_target_delay_max = m_target_delay_min;
                            }
                        }
                    }
                    ImGui::EndColumns();

                    ImGui::NewLine();
                    ImGui::Text("Aim smoothing:");
                    //ImGui::Separator();
                    const char* smoothitems[] = { "Distance", "Time" };
                    ImGui::ComboEx("Type:", reinterpret_cast<int*>(&m_smoothtype), smoothitems, 2, -1, true, 80);
                    ImGui::SameLine();
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
                                         
                    ImGui::NewLine();
                    ImGui::Checkbox("Activate BS HotSwap", &m_enable_bs_hotswap);
                    if (m_enable_bs_hotswap)
                    {
                        if (ImGui::Button("Select New"))
                        {
                            m_select_swapbs = true;
                        }
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Press the \"Select New\" button and then click on a weapon to swap to while overheated");
                        }
                        ImGui::SameLine();
                        if (m_select_swapbs) {
                            ImGui::Text("waiting for selection...");
                        }
                        else if (m_nextBS == 0) {
                            ImGui::Text("Select an AG-Weapon");
                        }
                    }
                    if (m_selected && m_enable_bs_hotswap)
                    {
                        ImGui::Text("Weapon selected!");
                    }
                }
                ImGui::EndDisabledMode();
            }
            ImGui::EndChild();
        }
        ImGui::NextColumn();
        {
            ImGui::BeginChild("GrindBotColumn2", ImVec2(), false);
            {   
                //ImGui::Separator();
                ImGui::Text("Statistics");
                ImGui::Separator();

                ImGui::Text(("Grinding Time: " + m_grind_time_string).c_str());

                std::string mobskilled = "Mobs killed: " + std::to_string(m_total_mobs_killed);
                ImGui::Text(mobskilled.c_str());

                ImGui::SetNextWindowSize(ImVec2(300.0f, 200.0f));
                if (ImGui::BeginPopup("GrindBotStatisticsPopup"/*, &m_popup_statistics_open*/, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar))
                {  
                    ImGui::BeginMenuBar();
                    {
                        ImGui::Text("Killed monsters");
                    }
                    ImGui::EndMenuBar();
                    ImGui::BeginColumns("MonsterStatisticColumns", 2, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
                    {
                        for (auto& monsterinfo : m_mobs)
                        {
                            if (monsterinfo.second.killed > 0)
                            {
                                //ImGui::Text(monsterinfo.second.clean_name.c_str());
                                monsterinfo.second.name.RenderImGui();
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

                    ImGui::BeginColumns("MonsterSelectColumns", 3, ImGuiColumnsFlags_NoResize | ImGuiColumnsFlags_NoBorder);
                    {
                        ImGui::SetColumnWidth(0, 200);
                        ImGui::SetColumnWidth(1, 80);
                        ImGui::Text("Shoot at");
                        ImGui::NextColumn();
                        ImGui::Text("Prioritise");
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Prioritised targets will be shot first if possible.");
                        }
                        ImGui::NextColumn();
                        ImGui::Text("Count");
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Amount of monsters in range and currently hitable.");
                        }
                        ImGui::NextColumn();
                        for (auto& monsterinfo : m_mobs)
                        {                             
                            ImGui::Checkbox(("###" + monsterinfo.second.name.GetOriginalText()).c_str(), &monsterinfo.second.shoot);
                            ImGui::SameLine();
                            monsterinfo.second.name.RenderImGui();
                            ImGui::NextColumn();
                            ImGui::Checkbox(("###" "_Prio_"+ monsterinfo.second.name.GetOriginalText()).c_str(), &monsterinfo.second.priority);
                            ImGui::NextColumn();
                            ImGui::Text(monsterinfo.second.count_text.c_str());
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
            if (m_wait_for_hotkey)
            {
                m_vkc_toggle = TO_UINT(wParam);
                m_vkc_description = Utility::VirtualKeyCodeToString(m_vkc_toggle);
                m_wait_for_hotkey = false;
            }
            else
            {
                if (TO_UINT(wParam) == m_vkc_toggle /* && !m_buddy->GetMenu()->IsOpen()*/)
                {
                    ToggleGrinding();
                    return 1;
                }
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

        if (GetTargetDistance(target) > OSR_API->GetRadarRangePrimary() * 1.3f /*siege mode range boost (we need the max range here, not the current range)*/) {
            return false;
        }
 
        return OSR_API->IsHitablePrimary(target);
    }

    bool GrindBot::IsValidTargetMonster(CMonsterData* monster)
    {
        if (!monster) {
            return false;
        }  

        if (IsMonsterDead(monster)) {
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

        float min_distance_anitram = 999999;
        CMonsterData* newtarget_antiram = nullptr;

        D3DXVECTOR3 mousepos = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vMousePos;
        D3DXVECTOR3 mousedir = OSR_API->GetAtumApplication()->m_pShuttleChild->m_vMouseDir;

        D3DXVECTOR3 sourceDir = mousedir;
        D3DXVec3Normalize(&sourceDir, &sourceDir);

        auto checkTarget = [&](CMonsterData* monster) -> bool
        {
            if (!IsValidTargetMonster(monster)) {
                return false;
            }

            float target_dist = GetTargetDistance(monster);
            if (target_dist > max_distance) {
                return false;
            }

            if (CanShootAtTarget(monster))
            {
                float dist = 9999999.0f;
                if (m_anti_ram && target_dist <= ANTI_RAM_CHECK_RADIUS)
                {
                    if (target_dist < min_distance_anitram)
                    {
                        min_distance_anitram = target_dist;
                        newtarget_antiram = monster;
                        return true;
                    }
                }

                switch (m_target_mode)
                {
                case TargetMode::GearDistance:
                    dist = target_dist;
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
                if ((monsterinfo->second.priority || (m_prio_bossmonster && OSR_API->IsGoodBossMonster(monster))) && dist < min_distance_prio)
                {
                    min_distance_prio = dist;
                    newtarget_prio = monster;
                }
            }
            return true;
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

        return  (newtarget_antiram) ? newtarget_antiram : ((newtarget_prio) ? newtarget_prio : newtarget);
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
            if (OSR_API->IsLanded()) // only allow grinding when gear is on ground
            {
                m_buddy->EnableMouseEmulation(true);
                ChangeState(GrindBot::State::SIEGEING);
                m_grinding_start = std::chrono::system_clock::now();
            }
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
        m_shoot_new_target_delay = std::chrono::milliseconds(Utility::GetRandInt32(m_target_delay_min, m_target_delay_max));
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
        static auto last_time = m_grinding_time;
        m_grinding_time = m_grinding_time_total + std::chrono::duration_cast<std::chrono::milliseconds>(current - m_grinding_start);
        if (m_grinding_time - last_time >= 1s) {
            m_grind_time_string = Utility::GetTimeString(m_grinding_time);
        }
    }

    void GrindBot::UpdateGrindMobInfo()
    {   
        if (m_update_mobs_timer.IsReady())
        {
            if (m_grinding_map != 0 && m_grinding_map == OSR_API->GetCurrentMapChannelIndex().MapIndex)
            {
                for (auto& monsterinfo : m_mobs) {
                    monsterinfo.second.count = 0;
                }

                for (auto& monster : OSR_API->GetSceneData()->m_mapMonsterList)
                {
                    // check if mob is already in the map, if not -> insert it
                    auto monsterinfo = m_mobs.find(monster.second->m_info.MonsterUnitKind);
                    if (monsterinfo == m_mobs.end())
                    {
                        GrindMonsterInfo gmi;
                        gmi.name = std::string(monster.second->m_pMonsterInfo->MonsterName);
                        //gmi.clean_name = std::string(monster.second->m_pMonsterInfo->MonsterName);
                        if (std::string(monster.second->m_pMonsterInfo->MonsterName).find("Scout Guard") != string::npos) {
                            continue;
                        }

                        gmi.shoot = false;
                        gmi.priority = false;
                        gmi.goldy = false;
                        gmi.killed = 0;

                        DEBUG_CHRISTMAS_EVENT_CRASH(monster.second);

                        if(CanShootAtTarget(monster.second))
                            gmi.count = 1;
                        else
                            gmi.count = 0;

                        if (monster.second->m_pMonsterInfo->MonsterName[0] == '\\' && monster.second->m_pMonsterInfo->MonsterName[1] != 'w')
                        {
                            //gmi.clean_name.erase(gmi.clean_name.begin(), gmi.clean_name.begin() + 2);
                            //gmi.clean_name.erase(gmi.clean_name.end() - 2, gmi.clean_name.end());
                            gmi.goldy = true;

                            if (m_shoot_all_goldies) 
                            {
                                gmi.shoot = true;
                                gmi.priority = true;
                            }
                        }
              
                        m_mobs.insert({ monster.second->m_info.MonsterUnitKind, gmi });
                    }
                    else
                    {
                        if (CanShootAtTarget(monster.second))
                            monsterinfo->second.count++;
                    }
                }
                for (auto& monsterinfo : m_mobs) {
                    monsterinfo.second.count_text = std::to_string(monsterinfo.second.count);
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
            {
                m_aimtime_current = m_aimtime_final;
                return;
            }


            float percent = static_cast<float>(m_aimtime_current.count()) / static_cast<float>(m_aimtime_final.count());
            deltaAng *= percent;
            break;
        }
    }

    bool GrindBot::IsValidPrimaryWeapon(ITEM_BASE* item)
    {
        return (IS_PRIMARY_WEAPON(item->Kind) && IS_AGEAR(item->ItemInfo->ReqUnitKind));
    }

    bool GrindBot::Swap()
    {
        CItemInfo* swapBS = OSR_API->FindItemInInventoryByUniqueNumber(m_nextBS);
        if (swapBS)
        {
            if (OSR_API->TryEquipItem(swapBS))
            {
                m_nextBS = m_currentBS;
                m_currentBS = swapBS->UniqueNumber;
                return true;
            }
        }
        return false;
    }
#pragma optimize( "", off )
    void GrindBot::DEBUG_CHRISTMAS_EVENT_CRASH(CMonsterData* monster)
    {
        std::string monstername = monster->m_pMonsterInfo->MonsterName;
        int i = 123;
    }
#pragma optimize( "", on ) 
       
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

    #ifdef SUMMER_EVENT
        // sommer event special, always add these monster to the list
        GrindMonsterInfo gmi;
        gmi.name = "Dropped Ball";
        gmi.goldy = true;
        gmi.killed = 0;
        gmi.priority = true;
        gmi.shoot = true;
        m_mobs.insert({ TO_INT(MonsterUnitKind::Dropped_Ball) , gmi});
        gmi.name = "Flying Ball";
        m_mobs.insert({ TO_INT(MonsterUnitKind::Flying_Ball) , gmi });
    #endif
          
        // halloween event special, always add these monster to the list
    #ifdef HALLOWEEN_EVENT
        GrindMonsterInfo gmi;
        gmi.name = "Halloween Bat";
        gmi.goldy = true;
        gmi.killed = 0;
        gmi.priority = true;
        gmi.shoot = true;
        m_mobs.insert({ TO_INT(MonsterUnitKind::Halloween_Bat) , gmi});
        gmi.name = "Mutant Pumpkin";
        m_mobs.insert({ TO_INT(MonsterUnitKind::Mutant_Pumpkin) , gmi });
    #endif

#ifdef CHRISTMAS_EVENT
        GrindMonsterInfo gmi;
        gmi.name = "Santa Cat";
        gmi.goldy = true;
        gmi.killed = 0;
        gmi.priority = true;
        gmi.shoot = true;
        m_mobs.insert({ TO_INT(MonsterUnitKind::Santa_Cat) , gmi });
        gmi.name = "\\cSnowman\\c";
        m_mobs.insert({ TO_INT(MonsterUnitKind::Snowman_blue) , gmi });
#endif

        m_grinding_map = OSR_API->GetCurrentMapChannelIndex().MapIndex;    
                                   
        // reset grinding timer
        m_grinding_time = 0ms;
        m_grinding_time_total = 0ms;
        m_grind_time_string = Utility::GetTimeString(m_grinding_time);

        m_kitbot = static_cast<KitBuffBot*>(m_buddy->GetFeatureByType(FeatureType::KitBuffBot));
        if (m_kitbot)
        {   
            // set kit settings
            KitBuffBot::KitSettings kitbot_settings;
            ZeroMemory(&kitbot_settings, sizeof(KitBuffBot::KitSettings));

            kitbot_settings.kitmode = KitBuffBot::Mode::Humanized;
            kitbot_settings.use_energy_type_b = true;
            kitbot_settings.use_shield_type_b = true;
            kitbot_settings.use_energy_type_c = true;
            kitbot_settings.use_shield_type_c = true;


            //kitbot_settings.use_spkit_type_c = true;
            //kitbot_settings.spkit_type_c_minvalue = TO_INT(OSR_API->GetMaxSkillp() * 0.6f);

            kitbot_settings.use_spkit_type_b = true;
            kitbot_settings.spkit_type_b_minvalue = TO_INT(OSR_API->GetMaxSkillp()* 0.2f);

            m_kitbot->SetSettings(kitbot_settings);
        
            // add auto buffs
            m_kitbot->AddAutoBuff(SkillType::Fire_Shot);
            m_kitbot->AddAutoBuff(SkillType::Missile_Shot);
            m_kitbot->AddAutoBuff(SkillType::Concentration);

            m_kitbot->Enable(true);
        }

        m_miscfeatures = dynamic_cast<Miscellaneous*>(m_buddy->GetFeatureByType(FeatureType::Miscellaneous));
        if (m_miscfeatures)
        {
            m_miscfeatures->Enable(true);
            m_miscfeatures->ActivateAutoAmmo(true);
            m_miscfeatures->ActivateAutoFlip(true);
        }

        m_invenmanager = dynamic_cast<InventoryManager*>(m_buddy->GetFeatureByType(FeatureType::InventoryManager));
        if (m_invenmanager)
        {
            m_invenmanager->Enable(true);
            m_invenmanager->ActivateInventoryCleaning(true);
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

        if (m_miscfeatures) 
        {
            m_miscfeatures->Enable(false);
            m_miscfeatures->ActivateAutoAmmo(false);
            m_miscfeatures->ActivateAutoFlip(false);
        }

        if (m_invenmanager)
        {
            m_invenmanager->Enable(false);
            m_invenmanager->ActivateInventoryCleaning(false);
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
            float radar_paramfactors = OSR_API->GetRadarRangePrimaryParamfactors();
            if (!m_kitbot->IsSkillActive(SkillType::Siege_Mode))
            {                                                                           
                radar_paramfactors += 0.3f; //get the range with the siege mode active, even if it is not active right now
            }
            CMonsterData* new_target = FindNewTarget(OSR_API->GetRadarRangePrimary(radar_paramfactors), m_visible_only);
           
            if (new_target)
            {
                ChangeTarget(new_target);
                m_get_new_target = false;
            }
        }
    }
}
