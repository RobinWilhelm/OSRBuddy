#include "WatermelonBot.h"
#include "OSRAPI.h"
#include "SDK/AtumApplication.h"
#include "OSRBuddy.h"
#include <string> 
#include "KitBot.h"

#define TARGET_LOCK_THRESHOLD    45.0f
#define TARGETING_SPEED 1.0f
#define INVENTORY_CLEAN_ACTION_MIN_TIME 2000
  
WatermelonBot::WatermelonBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
    m_current_state = WatermelonBot::State::WAITING;
    m_on_target = false;
    m_killed_watermelon_tanks = 0;
    m_killed_watermelon_z = 0;
    m_target = nullptr;
    m_kitbot = nullptr;
    m_auto_clean_inventory = false;
    m_get_new_target = true;   
    m_inv_action_check_time = 0ms;
}   

void WatermelonBot::Tick()
{
    if (!IsEnabled() || OSR_API->GetPlayerGearType() != GearType::AGear) {
        return;
    }

    if (OSR_API->GetCurrentMap() != MapIndex::WatermelonIsland) {
        return;
    }

    UpdateCheckTime();

    if (OSR_API->IsShuttleDead()) {
        return;
    }

    if (m_get_new_target) 
    {
        // try to find a close target first, to prevent getting rammed
        m_target = FindNewTarget(250, false);
        if (!m_target)
        {
            m_target = FindNewTarget(OSR_API->GetRadarRangePrimary() - 50, false);
        }
        
        if (m_target)
        {
            OSR_API->SetTarget(m_target);
            m_on_target = false;
            m_get_new_target = false;
        }  
        else
        {
            OSR_API->UsePrimaryWeapon(false);
            OSR_API->UseSecondaryWeapon(false);
        }
    }  
 
    switch (m_current_state)
    {
    case WatermelonBot::State::WAITING:   
        // show the user what the next targets would be
        m_get_new_target = true;                             
        break;

    case WatermelonBot::State::SIEGEING:
        UpdateGrindingTime();
        // check for overheat and valid target first
        if (OSR_API->GetPrimaryWeapon()->m_bOverHeat) 
        {
            ChangeState(WatermelonBot::State::OVERHEATED);
            return;
        }
        
        if (!IsValidTargetMonster(m_target) || !CanShootAtTarget(m_target))
        {
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
            OSR_API->UsePrimaryWeapon(false);
            OSR_API->UseSecondaryWeapon(false);
        }
        break;

    case WatermelonBot::State::OVERHEATED: 
        UpdateGrindingTime();
        if (!OSR_API->GetPrimaryWeapon()->m_bOverHeat) 
        {
            // check if a monster has come close to the player  
            CMonsterData* closetarget = FindNewTarget(250);
            if (closetarget) 
            {
                m_target = closetarget;
                OSR_API->SetTarget(m_target);
            }
            
            ChangeState(WatermelonBot::State::SIEGEING);
        }
        else
        {      
            if (m_auto_clean_inventory && InventoryActionCheckTimeReady())
            {
                // Clean inventory of unneeded items         

                // first try to open all watermelon boxes
                CItemInfo* item = OSR_API->FindItemInInventoryByItemNum(ItemNumber::Square_Watermelon_Gift);
                if (item)
                {
                    OSR_API->SendUseItem(item);
                    ResetInventoryActionCheckTime();
                    return;
                }

                // delete marks 
            }
        }
        break;
    }
}
   	 
void WatermelonBot::RenderImGui()
{
    if (!DrawEnableCheckBox()) {
        //return;
    } 

    ImGui::NewLine();
    ImGui::BeginDisabledMode(OSR_API->GetPlayerGearType() != GearType::AGear || OSR_API->GetCurrentMap() != MapIndex::WatermelonIsland);
    {     
        switch (m_current_state)
        {
        case WatermelonBot::State::WAITING:
            ImGui::Text("Status: Standby");
            break;
        case WatermelonBot::State::SIEGEING:
            ImGui::Text("Status: Grinding");
            break;
        case WatermelonBot::State::OVERHEATED:
            ImGui::Text("Status: Overheated");
            break;
        default:
            break;
        }

        ImGui::NewLine();
        ImGui::Text("Start / Stop hotkey: \"U\"");
        ImGui::NewLine();
       
        ImGui::BeginColumns("WatermelonBotColumns", 2, ImGuiColumnsFlags_NoResize);
        {   
            ImGui::BeginChild("WatermelonBotCol1", ImVec2(0,0), false);
            {
                ImGui::Separator();
                ImGui::Text("Settings");
                ImGui::Separator();

                ImGui::Checkbox("Shoot Watermelon Tanks", &m_shoot_watermelon_tanks);
                ImGui::Checkbox("Shoot Watermelon Z", &m_shoot_watermelon_z);
                ImGui::NewLine();
                ImGui::Checkbox("Automatic Inventory Cleaning", &m_auto_clean_inventory);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Will automatically open watermelon gifts.");
                }
            }
            ImGui::EndChild();
        }
        ImGui::NextColumn();
        {
            ImGui::BeginChild("WatermelonBotCol2", ImVec2(0, 0), false);
            {
                ImGui::Separator();
                ImGui::Text("Statistics");
                ImGui::Separator();

                std::string grindtime = "Grinding Time: " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(m_grinding_time).count());
                ImGui::Text(grindtime.c_str());
                ImGui::Text("Watermelon Tanks killed:");
                ImGui::SameLine();
                ImGui::Text(std::to_string(m_killed_watermelon_tanks).c_str());
                ImGui::Text("Watermelon Z killed:");
                ImGui::SameLine();
                ImGui::Text(std::to_string(m_killed_watermelon_z).c_str());
            }
            ImGui::EndChild();
        }
        ImGui::EndColumns();
    }
    ImGui::EndDisabledMode();
}

const char* WatermelonBot::GetName() const
{
	return "Watermelon Bot";
}

bool WatermelonBot::OnReadPacket(unsigned short msgtype, byte* packet)
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
                m_target->m_info.CurrentHP = 0;

                switch (m_target->m_info.MonsterUnitKind)
                {
                case static_cast<UINT>(MonsterUnitKind::Watermelon_Tank) :
                    m_killed_watermelon_tanks++;
                    break;
                case static_cast<UINT>(MonsterUnitKind::Watermelon_Z) :
                    m_killed_watermelon_z++;
                    break;
                }         
                m_target = nullptr;
            }              
        }
        break;
    }
 
    return false;
}

int WatermelonBot::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

float WatermelonBot::GetTargetDistance(CAtumData* m_target)
{
    if (!m_target) {
        return 0.0f;
    }

    D3DXVECTOR3 delta = m_target->m_vPos - OSR_API->GetAtumApplication()->m_pShuttleChild->m_vPos;
    return D3DXVec3Length(&delta);  
}

bool WatermelonBot::CanShootAtTarget(CUnitData* target)
{
    if (!target || target->m_bIsUnderWater) {
        return false;
    }

    if (GetTargetDistance(target) > OSR_API->GetRadarRangePrimary()) {
        return false;
    }
 
    return OSR_API->IsHitablePrimary(target);
}

bool WatermelonBot::IsValidTargetMonster(CMonsterData* monster)
{
    if (!monster) {
        return false;
    }  

    if (monster->m_info.CurrentHP <= 0) {
        return false;
    }

    switch (monster->m_info.MonsterUnitKind)
    {
    case static_cast<UINT>(MonsterUnitKind::Watermelon_Tank):
        if (!m_shoot_watermelon_tanks) { 
            return false; 
        }
        break;
    case static_cast<UINT>(MonsterUnitKind::Watermelon_Z):
        if (!m_shoot_watermelon_z) {
            return false;
        }
        break;
    default:
        return false;
    } 

    return true;
}

CMonsterData* WatermelonBot::FindNewTarget(float max_distance, bool front_only)
{  
    float min_cursor_distance = 999999;
    CMonsterData* newtarget = nullptr;

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
                POINT delta;
                delta.x = curPos.x - monster->m_nObjScreenX;
                delta.y = curPos.y - monster->m_nObjScreenY;

                float cursor_dist = static_cast<float>(sqrt(delta.x * delta.x + delta.y * delta.y));

                if (cursor_dist < min_cursor_distance)
                {
                    min_cursor_distance = cursor_dist;
                    newtarget = monster;
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
                POINT delta;
                delta.x = curPos.x - monster.second->m_nObjScreenX;
                delta.y = curPos.y - monster.second->m_nObjScreenY;

                float cursor_dist = static_cast<float>(sqrt(delta.x * delta.x + delta.y * delta.y));

                if (cursor_dist < min_cursor_distance)
                {
                    min_cursor_distance = cursor_dist;
                    newtarget = monster.second;
                }
            }
        }        
    } 
    return newtarget;
}

void WatermelonBot::AimAtTarget(CMonsterData* m_target)
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
            //SetCursorPos(targetPos.x, targetPos.y);
            //SendMouseMove(delta_x, delta_y);
            //m_buddy->SetCursorPosition(targetPos.x, targetPos.y);
            m_buddy->SetCursorPosition(curPos.x + delta_x, curPos.y + delta_y);
        }
        else
        {
            m_on_target = true;
        }
    }
}

void WatermelonBot::ToggleGrinding()
{
    switch (m_current_state)
    {
    case WatermelonBot::State::WAITING:
        m_buddy->EnableMouseEmulation(true);
        ChangeState(WatermelonBot::State::SIEGEING);   
        m_grinding_start = std::chrono::system_clock::now();
        break;
    case WatermelonBot::State::SIEGEING:
    case WatermelonBot::State::OVERHEATED:
        m_buddy->EnableMouseEmulation(false);
        ChangeState(WatermelonBot::State::WAITING);
        m_grinding_time_total = m_grinding_time;
        break;
    default:
        break;
    }  
}

bool WatermelonBot::InventoryActionCheckTimeReady()
{
    return m_inv_action_check_time <= 0ms;
}

void WatermelonBot::ResetInventoryActionCheckTime()
{
    m_inv_action_check_time = std::chrono::milliseconds(INVENTORY_CLEAN_ACTION_MIN_TIME + m_buddy->GetRandInt32(0, 300));
}

void WatermelonBot::UpdateCheckTime()
{   
    if (m_inv_action_check_time > 0ms) {
        m_inv_action_check_time -= std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
    }
    if (m_inv_action_check_time < 0ms) {
        m_inv_action_check_time = 0ms;
    }
}

void WatermelonBot::UpdateGrindingTime()
{
    auto current = std::chrono::system_clock::now();
    m_grinding_time = m_grinding_time_total + std::chrono::duration_cast<std::chrono::milliseconds>(current - m_grinding_start);
}
       
FeatureType WatermelonBot::GetType() const
{
	return FeatureType::WatermelonBot;
}

void WatermelonBot::OnEnable()
{
    if (OSR_API->GetCurrentMap() != MapIndex::WatermelonIsland) 
    {
        Enable(false);
        return;
    }

    // reset grinding timer
    m_grinding_time = 0ms;
    m_grinding_time_total = 0ms;
    m_killed_watermelon_tanks = 0;
    m_killed_watermelon_z = 0;

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
        kitbot_settings.spkit_type_c_percentage = 66;  

        kitbot_settings.use_spkit_type_b = true;
        kitbot_settings.spkit_type_b_percentage = 33;

        m_kitbot->SetSettings(kitbot_settings);
        
        // add auto buffs
        m_kitbot->AddAutoBuff(SkillType::Fire_Shot);
        m_kitbot->AddAutoBuff(SkillType::Missile_Shot);
        m_kitbot->AddAutoBuff(SkillType::Concentration);

        m_kitbot->Enable(true);
    }
}

void WatermelonBot::OnDisable()
{
    if (m_kitbot) {
        m_kitbot->Enable(false);
    }
}

void WatermelonBot::ChangeState(WatermelonBot::State newState)
{
    if (newState == m_current_state) {
        return;
    }

    switch (newState)
    {
    case WatermelonBot::State::WAITING:
        OSR_API->UsePrimaryWeapon(false);
        OSR_API->UseSecondaryWeapon(false);
        m_kitbot->ToggleSKill(SkillType::Siege_Mode, false);
        break;
    case WatermelonBot::State::SIEGEING:
        break;
    case WatermelonBot::State::OVERHEATED:
        OSR_API->UsePrimaryWeapon(false);
        OSR_API->UseSecondaryWeapon(false);
        m_kitbot->ToggleSKill(SkillType::Siege_Mode, false);
        break;
    default:
        break;
    }

    m_current_state = newState;
}
