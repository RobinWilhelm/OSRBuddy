#include "WatermelonBot.h"
#include "OSRAPI.h"
#include "SDK/AtumApplication.h"
#include "OSRBuddy.h"
#include <string> 
#include "KitBot.h"

#define TARGET_LOCK_THRESHOLD    45.0f
#define TARGETING_SPEED 1.0f
#define INVENTORY_CLEAN_ACTION_MIN_TIME 2000

/*
#define SKILL_STATE_READY			0
#define SKILL_STATE_WAITING_PREPARE	1
#define SKILL_STATE_PREPARE			2
#define SKILL_STATE_WAITING			3
#define SKILL_STATE_USING			4
#define SKILL_STATE_WAIT_REATTACK	5
#define SKILL_STATE_RELEASE			6

#define T0_FC_SKILL					0x41
#define T0_FC_MONSTER				0x3A

#define T1_FC_MONSTER_CHANGE_HP							0x05

// FC_SKILL
#define T1_FC_SKILL_USE_SKILLPOINT			0x00
#define T1_FC_SKILL_USE_SKILLPOINT_OK		0x01
#define T1_FC_SKILL_SETUP_SKILL				0x02
#define T1_FC_SKILL_SETUP_SKILL_OK_HEADER	0x03
#define T1_FC_SKILL_SETUP_SKILL_OK			0x04
#define T1_FC_SKILL_SETUP_SKILL_OK_DONE		0x05
#define T1_FC_SKILL_USE_SKILL				0x06
#define T1_FC_SKILL_USE_SKILL_OK			0x07
#define T1_FC_SKILL_CANCEL_SKILL			0x08
#define T1_FC_SKILL_INVALIDATE_SKILL		0x09
#define T1_FC_SKILL_PREPARE_USE				0x0A
#define T1_FC_SKILL_PREPARE_USE_OK			0x0B
#define T1_FC_SKILL_CANCEL_PREPARE			0x0C
#define T1_FC_SKILL_CANCEL_PREPARE_OK		0x0D
#define T1_FC_SKILL_CONFIRM_USE				0x0F		// 2005-12-02 by cmkwon, C->F, F->C
#define T1_FC_SKILL_CONFIRM_USE_ACK			0x10		// 2005-12-02 by cmkwon, C->F, F->C
#define T1_FC_SKILL_CANCEL_SKILL_OK			0x11		// 2006-11-28 by dhjin, F->C

// FN_SKILL
#define T1_FN_SKILL_USE_SKILL				0x00
#define T1_FN_SKILL_USE_SKILL_OK			0x01

#define T_FC_MONSTER_CHANGE_HP						(MessageType_t)((T0_FC_MONSTER<<8)|T1_FC_MONSTER_CHANGE_HP)

#define T_FC_SKILL_USE_SKILLPOINT				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_USE_SKILLPOINT)
#define T_FC_SKILL_USE_SKILLPOINT_OK			(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_USE_SKILLPOINT_OK)
#define T_FC_SKILL_SETUP_SKILL					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_SETUP_SKILL)
#define T_FC_SKILL_SETUP_SKILL_OK_HEADER		(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_SETUP_SKILL_OK_HEADER)
#define T_FC_SKILL_SETUP_SKILL_OK				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_SETUP_SKILL_OK)
#define T_FC_SKILL_SETUP_SKILL_OK_DONE			(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_SETUP_SKILL_OK_DONE)
#define T_FC_SKILL_USE_SKILL					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_USE_SKILL)
#define T_FC_SKILL_USE_SKILL_OK					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_USE_SKILL_OK)
#define T_FC_SKILL_CANCEL_SKILL					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CANCEL_SKILL)
#define T_FC_SKILL_CANCEL_SKILL_OK				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CANCEL_SKILL_OK)
#define T_FC_SKILL_INVALIDATE_SKILL				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_INVALIDATE_SKILL)
#define T_FC_SKILL_PREPARE_USE					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_PREPARE_USE)
#define T_FC_SKILL_PREPARE_USE_OK				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_PREPARE_USE_OK)
#define T_FC_SKILL_CANCEL_PREPARE				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CANCEL_PREPARE)
#define T_FC_SKILL_CANCEL_PREPARE_OK			(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CANCEL_PREPARE_OK)
#define T_FC_SKILL_CONFIRM_USE					(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CONFIRM_USE)		// 2005-12-02 by cmkwon, C->F, F->C
#define T_FC_SKILL_CONFIRM_USE_ACK				(MessageType_t)((T0_FC_SKILL<<8)|T1_FC_SKILL_CONFIRM_USE_ACK)	// 2005-12-02 by cmkwon, C->F, F->C

#define T_FN_SKILL_USE_SKILL					(MessageType_t)((T0_FN_SKILL<<8)|T1_FN_SKILL_USE_SKILL)
#define T_FN_SKILL_USE_SKILL_OK					(MessageType_t)((T0_FN_SKILL<<8)|T1_FN_SKILL_USE_SKILL_OK)



typedef struct
{
    ClientIndex_t	ClientIndex;
    ItemID_t		SkillItemID;
    INT				AttackSkillItemNum0;	// 2006-12-12 by cmkwon, 현재 스킬을 종료되게 하는 공격스킬 아이템넘버
} MSG_FC_SKILL_CANCEL_SKILL_OK;

typedef struct
{
    ItemID_t		SkillItemID;
    ClientIndex_t	AttackIndex;
    ClientIndex_t	TargetIndex;	// target이 없는 skill인 경우 0
    ATUM_DATE_TIME	UseTime;		// 2006-11-17 by dhjin, 2차 스킬 사용 시간
//	BOOL			UseSkillTimeOk;	// 2006-11-17 by dhjin, 0 -> 2차 스킬 사용 대기 시간, 1 -> 2차 스킬 사용할 수 있다.
} MSG_FC_SKILL_USE_SKILL_OK;

typedef struct
{
    BYTE		ItemUpdateType;		// IUT_SHOP, IUT_LOADING, IUT_SKILL
    ITEM_SKILL	ItemSkill;
} MSG_FC_SKILL_SETUP_SKILL_OK;

typedef struct
{
    ClientIndex_t	MonsterIndex;
    INT				CurrentHP;
} MSG_FC_MONSTER_CHANGE_HP;					// F -> C, 몬스터의 현재 HP를 전송함

typedef struct
{
    ItemID_t		SkillItemID;
    ClientIndex_t	ClientIndex;
} MSG_FC_SKILL_INVALIDATE_SKILL;	//
*/

WatermelonBot::WatermelonBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{
    m_current_state = WatermelonBot::State::WAITING;
    m_on_target = false;
    m_killed_watermelon_tanks = 0;
    m_killed_watermelon_z = 0;
    m_killed_easter_egg = 0;
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

    if (OSR_API->GetCurrentMap() != MapNumber::WatermelonIsland) {
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

    if (OSR_API->GetPlayerGearType() != GearType::AGear) {
        ImGui::Text("Switch to an A-GEAR if you want to use the bot!");
    }

    if (OSR_API->GetCurrentMap() != MapNumber::WatermelonIsland) {
        ImGui::Text("Wrong Map!");
    }
        
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

    ImGui::Dummy(ImVec2(5, 0));
    ImGui::Text("Start / Stop hotkey: \"U\"");
    ImGui::Dummy(ImVec2(5, 0));

    ImGui::BeginGroupPanel("Settings", ImVec2(400, 400));

    ImGui::Checkbox("Automatic Inventory Cleaning", &m_auto_clean_inventory);

    ImGui::Dummy(ImVec2(5, 0));
    ImGui::EndGroupPanel();

    ImGui::BeginGroupPanel("Statistics", ImVec2(400, 400));
    std::string grindtime = "Grinding Time: " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(m_grinding_time).count());
    ImGui::Text(grindtime.c_str());

    ImGui::Text("Watermelon Tanks killed:");
    ImGui::SameLine();
    ImGui::Text(std::to_string(m_killed_watermelon_tanks).c_str());
    ImGui::Dummy(ImVec2(5, 0));
    ImGui::EndGroupPanel();
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
                m_target->m_info.CurrentHP = ((MSG_FC_MONSTER_CHANGE_HP*)packet)->CurrentHP;

                switch (m_target->m_pMonsterInfo->SourceIndex)
                {
                case static_cast<UINT>(MonsterIndex::Watermelon_Tank) :
                    m_killed_watermelon_tanks++;
                    break;
                case static_cast<UINT>(MonsterIndex::Watermelon_Z) :
                    m_killed_watermelon_z++;
                    break;
                case static_cast<UINT>(MonsterIndex::Easter_Egg) :
                    m_killed_easter_egg++;
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

    switch (monster->m_pMonsterInfo->SourceIndex)
    {
    case static_cast<UINT>(MonsterIndex::Watermelon_Tank) :
    //case static_cast<UINT>(MonsterIndex::Watermelon_Z) :
    //case static_cast<UINT>(MonsterIndex::Easter_Egg) :
        break;
    default:
        return false;
    }

    if (monster->m_info.CurrentHP <= 0) {
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
            //m_buddy->SetCursorPosition(delta_x, delta_y);
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
    if (OSR_API->GetCurrentMap() != MapNumber::WatermelonIsland) 
    {
        Enable(false);
        return;
    }

    // reset grinding timer
    m_grinding_time = 0ms;
    m_grinding_time_total = 0ms;
    m_killed_watermelon_tanks = 0;

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
