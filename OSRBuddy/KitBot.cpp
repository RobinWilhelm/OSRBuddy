#include "KitBot.h"
#include "OSRAPI.h"
#include "SDK/AtumApplication.h"
#include "OSRBuddy.h"
#include "OSRBuddyDefine.h"
#include <chrono>
#include <algorithm>

#include "AtumError.h"

#define KIT_RESEND_TIME 100ms

#define T0_FC_SKILL					0x41
#define T0_FC_BATTLE				0x12		// 2008-02-13 by cmkwon, «¡∑Œ≈‰ƒ› ∫Ø∞Ê, ≤¿ ≈¨∂Û¿Ãæ∆ÆøÕ ∞∞¿Ã æ˜µ•¿Ã∆Æ «ÿæﬂ«‘
#define T0_FC_ITEM					0x39
                                                    
// FN_SKILL
#define T1_FN_SKILL_USE_SKILL				0x00
#define T1_FN_SKILL_USE_SKILL_OK			0x01
#define T1_FC_ITEM_USE_ENERGY							0x0D       
#define T1_FC_ITEM_USE_ENERGY_OK						0x0E	// F->C
#define T1_FC_BATTLE_PRI_BULLET_RELOADED		0x23
#define T1_FC_BATTLE_SEC_BULLET_RELOADED		0x24

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


#define T_FC_ITEM_USE_ENERGY_OK					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_ENERGY_OK)    
#define T_FC_BATTLE_PRI_BULLET_RELOADED			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_PRI_BULLET_RELOADED)	// 1«¸ π´±‚¿« ≈∫æÀ¿Ã ∏Æ∑ŒµÂµ«æ˙¿Ω
#define T_FC_BATTLE_SEC_BULLET_RELOADED			(MessageType_t)((T0_FC_BATTLE<<8)|T1_FC_BATTLE_SEC_BULLET_RELOADED)	// 2«¸ π´±‚¿« ≈∫æÀ¿Ã ∏Æ∑ŒµÂµ«æ˙¿Ω

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

#define T_FC_ITEM_USE_ENERGY					(MessageType_t)((T0_FC_ITEM<<8)|T1_FC_ITEM_USE_ENERGY)


#define T1_ERROR								0x00
#define T0_ERROR					0xFE
#define T_ERROR									(MessageType_t)((T0_ERROR<<8)|T1_ERROR)

#define BULLET_RECHARGE_TYPE_NORMAL			((BYTE)0)
#define BULLET_RECHARGE_TYPE_REPAIR_SHOP	((BYTE)1)
#define BULLET_RECHARGE_TYPE_BULLET_ITEM	((BYTE)2)
#define BULLET_RECHARGE_TYPE_ADMIN_COMMAND	((BYTE)3)

// FC_TIMER
#define T1_FC_TIMER_START_TIMER					0x00	// F->C, TIMER_EVENT Ω√¿€
#define T1_FC_TIMER_STOP_TIMER					0x01	// F->C, TIMER_EVENT ¡§¡ˆ
#define T1_FC_TIMER_UPDATE_TIMER				0x02	// F->C, TIMER_EVENT ∞ªΩ≈(Ω√∞£ ø¨¿Â)
#define T1_FC_TIMER_PAUSE_TIMER					0x03	// F->C, TIMER_EVENT ¿œΩ√ ¡§¡ˆ
#define T1_FC_TIMER_CONTINUE_TIMER				0x04	// F->C, TIMER_EVENT ¿ÁΩ√¿€
#define T1_FC_TIMER_TIMEOUT						0x05	// C->F, Ω√∞£¿Ã ¥Ÿ µ ¿ª æÀ∏≤

#define T0_FC_TIMER					0x44
#define T_FC_TIMER_START_TIMER					(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_START_TIMER)		// F->C, TIMER_EVENT Ω√¿€
#define T_FC_TIMER_STOP_TIMER					(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_STOP_TIMER)		// F->C, TIMER_EVENT ¡§¡ˆ
#define T_FC_TIMER_UPDATE_TIMER					(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_UPDATE_TIMER)		// F->C, TIMER_EVENT ∞ªΩ≈(Ω√∞£ ø¨¿Â)
#define T_FC_TIMER_PAUSE_TIMER					(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_PAUSE_TIMER)		// F->C, TIMER_EVENT ¿œΩ√ ¡§¡ˆ
#define T_FC_TIMER_CONTINUE_TIMER				(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_CONTINUE_TIMER)	// F->C, TIMER_EVENT ¿ÁΩ√¿€
#define T_FC_TIMER_TIMEOUT						(MessageType_t)((T0_FC_TIMER<<8)|T1_FC_TIMER_TIMEOUT)			// C->F, Ω√∞£¿Ã ¥Ÿ µ ¿ª æÀ∏≤


#define TE_TYPE_DELETE_DUMMY			(TimerEventType)6
#define TE_TYPE_DELETE_FIXER			(TimerEventType)7
#define TE_TYPE_DELETE_DECOY			(TimerEventType)8		// µƒ⁄¿Ã¥¬ TimeOutπﬂª˝ Ω√ CurrentCount∏¶ ¡Ÿ¿Ã∞Ì, CurrentCount=0±Ó¡ˆ π›∫π«‘
#define TE_TYPE_GRADUAL_SHIELD_UP		(TimerEventType)9		// 2-2«¸ π´±‚ ΩØµÂ, interval¿∫ π´¡∂∞« 1000 ms
#define TE_TYPE_RECOVER_HP				(TimerEventType)10		// ¬¯∑˙«ﬂ¿ª ∂ß∏∏ √§øÚ(5√ ¥Á 3)
#define TE_TYPE_RECOVER_DP				(TimerEventType)11		// ¬¯∑˙«ﬂ¿ª ∂ß∏∏ √§øÚ
#define TE_TYPE_RECOVER_SP				(TimerEventType)12
#define TE_TYPE_GRADUAL_HP_UP			(TimerEventType)13		// interval¿∫ π´¡∂∞« 1000 ms, ITEM_GENERAL.Endurance∞° 0¿Ã µ… ∂ß±Ó¡ˆ π›∫π«‘
#define TE_TYPE_GRADUAL_DP_UP			(TimerEventType)14		// interval¿∫ π´¡∂∞« 1000 ms, ITEM_GENERAL.Endurance∞° 0¿Ã µ… ∂ß±Ó¡ˆ π›∫π«‘
#define TE_TYPE_GRADUAL_SP_UP			(TimerEventType)15		// interval¿∫ π´¡∂∞« 1000 ms, ITEM_GENERAL.Endurance∞° 0¿Ã µ… ∂ß±Ó¡ˆ π›∫π«‘, not used yet: SP¥¬ ¿⁄µø¿∏∑Œ »∏∫πµ , TE_TYPE_RECOVER_SP∏¶ ªÁøÎ
#define TE_TYPE_GRADUAL_EP_UP			(TimerEventType)16		// interval¿∫ π´¡∂∞« 1000 ms, ITEM_GENERAL.Endurance∞° 0¿Ã µ… ∂ß±Ó¡ˆ π›∫π«‘
#define TE_TYPE_IMMEDIATE_HP_UP			(TimerEventType)17		// ªÁøÎΩ√ πŸ∑Œ √§øÏ∞Ì Time µøæ» ¿ÁªÁøÎ¿Ã æ»µ»¥Ÿ
#define TE_TYPE_IMMEDIATE_DP_UP			(TimerEventType)18		// ªÁøÎΩ√ πŸ∑Œ √§øÏ∞Ì Time µøæ» ¿ÁªÁøÎ¿Ã æ»µ»¥Ÿ
#define TE_TYPE_IMMEDIATE_SP_UP			(TimerEventType)19		// ªÁøÎΩ√ πŸ∑Œ √§øÏ∞Ì Time µøæ» ¿ÁªÁøÎ¿Ã æ»µ»¥Ÿ
#define TE_TYPE_IMMEDIATE_EP_UP			(TimerEventType)20		// ªÁøÎΩ√ πŸ∑Œ √§øÏ∞Ì Time µøæ» ¿ÁªÁøÎ¿Ã æ»µ»¥Ÿ
#define TE_TYPE_REQUEST_TIMEOUT			(TimerEventType)21		// ∞≈∑°, ∆ƒ∆º¿¸, ¿œ¥Î¿œ¥Î∞· µÓ¿« ø‰√ªø° ¥Î«— TimeOut
#define TE_TYPE_DECREASE_SP				(TimerEventType)22		// TOGGLE«¸ Ω∫≈≥ ªÁøÎ Ω√, SP∏¶ ReqSP∏∏≈≠ º“∏, SP º“¡¯ Ω√ Ω∫≈≥ ¿⁄µø √Îº“
#define TE_TYPE_DO_MINUTELY_WORK		(TimerEventType)23		// 1∫–ø° «—π¯æø πﬂ«‡«œ¥¬ ≈∏¿Ã∏”

typedef struct
{
    ItemID_t		SkillItemID;
} MSG_FC_SKILL_PREPARE_USE;

typedef struct
{
    ClientIndex_t	ClientIndex;
    ItemID_t		SkillItemID;
} MSG_FC_SKILL_PREPARE_USE_OK;

typedef struct
{
    ItemID_t		SkillItemID;			// ¡æ∑·µ«¥¬ Ω∫≈≥ ¡§∫∏
    INT				AttackSkillItemNum0;	// 2006-12-12 by cmkwon, «ˆ¿Á Ω∫≈≥¿ª ¡æ∑·µ«∞‘ «œ¥¬ ∞¯∞›Ω∫≈≥ æ∆¿Ã≈€≥—πˆ 
} MSG_FC_SKILL_CANCEL_SKILL;

typedef struct
{
    ItemID_t		SkillItemID;
    ClientIndex_t	AttackIndex;
    ClientIndex_t	TargetIndex;	// target¿Ã æ¯¥¬ skill¿Œ ∞ÊøÏ 0
    UID32_t			TargetCharUID;	// 2005-11-24 by cmkwon, target¿÷¡ˆ∏∏ TargetIndex∞° 0¿œ∂ß ªÁøÎµ , TargetIndex∞° ∆Ì¥Îø¯ 1∏Ì º“»Ø Ω∫≈≥Ω√ ªÁøÎ«—¥Ÿ.
} MSG_FC_SKILL_USE_SKILL;

typedef struct
{
    ItemID_t		SkillItemID;
    ClientIndex_t	AttackIndex;
    ClientIndex_t	TargetIndex;	// target¿Ã æ¯¥¬ skill¿Œ ∞ÊøÏ 0
    ATUM_DATE_TIME	UseTime;		// 2006-11-17 by dhjin, 2¬˜ Ω∫≈≥ ªÁøÎ Ω√∞£
//	BOOL			UseSkillTimeOk;	// 2006-11-17 by dhjin, 0 -> 2¬˜ Ω∫≈≥ ªÁøÎ ¥Î±‚ Ω√∞£, 1 -> 2¬˜ Ω∫≈≥ ªÁøÎ«“ ºˆ ¿÷¥Ÿ.
} MSG_FC_SKILL_USE_SKILL_OK;
  
typedef struct
{
    ClientIndex_t	ClientIndex;
    ItemID_t		SkillItemID;
    INT				AttackSkillItemNum0;	// 2006-12-12 by cmkwon, «ˆ¿Á Ω∫≈≥¿ª ¡æ∑·µ«∞‘ «œ¥¬ ∞¯∞›Ω∫≈≥ æ∆¿Ã≈€≥—πˆ
} MSG_FC_SKILL_CANCEL_SKILL_OK;

typedef struct
{
    ItemID_t		SkillItemID;
    ClientIndex_t	ClientIndex;
} MSG_FC_SKILL_INVALIDATE_SKILL;	//
     
struct MSG_FC_ITEM_USE_ENERGY_OK
{
    ClientIndex_t	ClientIndex;
    INT				ItemNum;
};

struct  MSG_FC_BATTLE_PRI_BULLET_RELOADED
{
    USHORT			BulletCount;		// π´±‚¿« reloadµ» √—æÀ¿« √÷¡æ ∞≥ºˆ
    USHORT			RechargeCount;		// 2007-08-07 by cmkwon, 1«¸/2«¸ π´±‚ √—æÀ √Ê¿¸ æ∆¿Ã≈€ ±∏«ˆ - √ﬂ∞°µ» « µÂ
    BYTE			RechargeType;		// 2007-08-07 by cmkwon, 1«¸/2«¸ π´±‚ √—æÀ √Ê¿¸ æ∆¿Ã≈€ ±∏«ˆ - √ﬂ∞°µ» « µÂ(BULLET_RECHARGE_TYPE_XXX)
};
typedef MSG_FC_BATTLE_PRI_BULLET_RELOADED		 MSG_FC_BATTLE_SEC_BULLET_RELOADED;

typedef struct
{
    ClientIndex_t	ClientIndex;
    UID64_t			ItemUniqueNumber;
    INT				nParam1;				//
} MSG_FC_ITEM_USE_ENERGY;



typedef struct
{
    MEX_TIMER_EVENT		TimerEvent;
} MSG_FC_TIMER_START_TIMER;			// F->C, TIMER_EVENT Ω√¿€

KitBuffBot::KitBuffBot(OSRBuddyMain* buddy) : BuddyFeatureBase(buddy)
{       
    ZeroMemory(&m_settings, sizeof(KitBuffBot::KitSettings));

    m_shieldkit_reattack_time = 0ms;
    m_energykit_reattack_time = 0ms;
    m_skillpkit_reattack_time = 0ms;

    m_lastUseShieldKitTime = 0ms;
    m_lastUseEnergyKitTime = 0ms;
    m_lastUseSkillKitTime = 0ms;

    m_lastUseShieldKitTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    m_lastUseEnergyKitTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    m_lastUseSkillKitTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    GrabPlayerSkills();

}

bool KitBuffBot::TryUseKit(KitType type, KitCategory category)
{   
    CItemInfo* invkit = nullptr;
    bool used_shieldkit = false, used_energykit = false, used_spkit = false;
    bool is_mgear = OSR_API->GetPlayerGearType() == GearType::MGear;

    switch (type)
    {
    case KitType::SHIELD:
        if (m_awaiting_Ok_shield) {
            return false;
        }

        switch (category)
        {
        case KitCategory::S_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::S_Type_ShieldKit_1);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            else
            {
                invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::S_Type_ShieldKit_2);
                if (invkit) 
                {
                    OSR_API->SendUseItem(invkit);
                    return true;
                }
            }
            break;
        case KitCategory::A_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::A_Type_ShieldKit_1);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            else
            {
                invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::A_Type_ShieldKit_2);
                if (invkit) 
                {
                    OSR_API->SendUseItem(invkit);
                    return true;
                }
            }
            break;
        case KitCategory::B_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::B_Type_ShieldKit);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            break;
        case KitCategory::C_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::C_Type_ShieldKit);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            break;  
        } 
        break;
    case KitType::ENERGY:
        if (m_awaiting_Ok_energy) {
            return false;
        }

        switch (category)
        {
        case KitCategory::S_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::S_Type_RepairKit_1);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            else
            {
                invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::S_Type_RepairKit_2);
                if (invkit) 
                {
                    OSR_API->SendUseItem(invkit);
                    return true;
                }
            }
            break;
        case KitCategory::A_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::A_Type_RepairKit_1);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            else
            {
                invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::A_Type_RepairKit_2);
                if (invkit) 
                {
                    OSR_API->SendUseItem(invkit);
                    return true;
                }
            }
            break;
        case KitCategory::B_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::B_Type_RepairKit);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            break;
        case KitCategory::C_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::C_Type_RepairKit);
            if (invkit)  
            {
                OSR_API->SendUseItem(invkit);           
                return true;
            }
            break;       
        } 
        break;
    case KitType::SKILLPOINT:
        if (m_awaiting_Ok_skill) {
            return false;
        }      
        switch (category)
        {
        case KitCategory::S_TYPE:
            break;
        case KitCategory::A_TYPE:
            if (is_mgear)
            {
                invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::A_Type_SkillPit_MG);
                if (invkit) 
                {
                    OSR_API->SendUseItem(invkit);
                    return true;
                }
            } 

            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::A_Type_SkillPKit_1);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            else
            {
                invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::A_Type_SkillPKit_2);
                if (invkit) 
                {
                    OSR_API->SendUseItem(invkit);
                    return true;
                }
            }
            break;
        case KitCategory::B_TYPE:
            if (is_mgear)
            {
                invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::B_Type_SkillPKit_MG);
                if (invkit)
                {
                    OSR_API->SendUseItem(invkit);
                    return true;
                }
            }

            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::B_Type_SkillPKit);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            break;
        case KitCategory::C_TYPE:
            if (is_mgear)
            {
                invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::C_Type_SkillPKit_MG);
                if (invkit)
                {
                    OSR_API->SendUseItem(invkit);
                    return true;
                }
            }

            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::C_Type_SkillPKit);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            break;    
        }
        break;
    case KitType::FUEL:
        if (m_awaiting_Ok_fuel) {
            return false;
        }
        switch (category)
        {
        case KitCategory::S_TYPE:
            break;
        case KitCategory::A_TYPE:
            break;
        case KitCategory::B_TYPE:
            invkit = OSR_API->FindItemInInventoryByItemNum(ItemNumber::B_Type_CondensedFuel);
            if (invkit) 
            {
                OSR_API->SendUseItem(invkit);
                return true;
            }
            break;
        case KitCategory::C_TYPE:
            break;    
        }   
        break;     
    }

    return false;
}

bool KitBuffBot::KitTimerReady(KitType kittype)
{
    std::chrono::milliseconds current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    switch (kittype)
    {
    case KitType::SHIELD:
        return ((current - m_lastUseShieldKitTime) >= m_shieldkit_reattack_time);
        break;
    case KitType::ENERGY:
        return ((current - m_lastUseEnergyKitTime) >= m_energykit_reattack_time);
        break;
    case KitType::SKILLPOINT:
        return ((current - m_lastUseSkillKitTime) >= m_skillpkit_reattack_time);
        break;
    case KitType::FUEL:
        return ((current - m_lastUseFuelKitTime) >= m_fuelkit_reattack_time);
        break;
    default:
        return false;
        break;
    }      
}

bool KitBuffBot::TryUseAmmunitionBox()
{
    CItemInfo* ammobox = OSR_API->FindItemInInventoryByItemNum(ItemNumber::AmmunitionRechargeBox);
    if (!ammobox)
        return false;
 
    OSR_API->SendUseItem(ammobox);
    m_awaiting_Ok_ammobox = true;
    return true;
}

KitType KitBuffBot::GetKitTypeFromItem(CItemInfo* item)
{
    switch (TO_ENUM(ItemNumber, item->ItemInfo->ItemNum))
    {
    case ItemNumber::S_Type_ShieldKit_1:
    case ItemNumber::S_Type_ShieldKit_2:
    case ItemNumber::A_Type_ShieldKit_1:
    case ItemNumber::A_Type_ShieldKit_2:
    case ItemNumber::B_Type_ShieldKit:
    case ItemNumber::C_Type_ShieldKit:
        return KitType::SHIELD;
    case ItemNumber::S_Type_RepairKit_1:
    case ItemNumber::S_Type_RepairKit_2:
    case ItemNumber::A_Type_RepairKit_1:
    case ItemNumber::A_Type_RepairKit_2:
    case ItemNumber::B_Type_RepairKit:
    case ItemNumber::C_Type_RepairKit:
        return KitType::ENERGY;
    case ItemNumber::A_Type_SkillPKit_1:
    case ItemNumber::A_Type_SkillPKit_2:
    case ItemNumber::A_Type_SkillPit_MG:
    case ItemNumber::B_Type_SkillPKit:
    case ItemNumber::B_Type_SkillPKit_MG:
    case ItemNumber::C_Type_SkillPKit:
    case ItemNumber::C_Type_SkillPKit_MG:
        return KitType::SKILLPOINT;
    case ItemNumber::B_Type_CondensedFuel:
        return KitType::FUEL;
    default:
        return KitType::NONE;
    }
}

void KitBuffBot::SetSettings(KitSettings& settings)
{
    m_settings = settings;
}

bool KitBuffBot::AddAutoBuff(SkillType skilltype)
{
    // check if skill is already in autobuff list             
    for (auto& pskill : m_playerskills)
    {
        if (pskill->type == skilltype)
        {
            pskill->autobuff = true;
            return true;
        }
    }
    return false;
}

void KitBuffBot::RemoveAutoBuff(SkillType skilltype)
{       
    for (auto& pskill : m_playerskills)
    {
        if (pskill->type == skilltype)
        {
            pskill->autobuff = false;
            return;
        }
    }
}

void KitBuffBot::ClearAutoBuff()
{
    for (auto& pskill : m_playerskills)
    {
        pskill->autobuff = false;
    }
}

bool KitBuffBot::IsAutoBuff(SkillType skilltype)
{
    for (auto pskill : m_playerskills)
    {
        if (pskill->type == skilltype) {
            return true;
        }
    }
    return false;
}

SkillType KitBuffBot::ResolveSkillItemName(const char* itemname)
{
    if (!itemname) {
        return SkillType::Unknown;
    }

    if (strstr(itemname, "Raging Evasion"))         return SkillType::Raging_Evasion;
    if (strstr(itemname, "Raging defense"))         return SkillType::Raging_Defense;
    if (strstr(itemname, "Raging fire"))            return SkillType::Raging_Fire;
    if (strstr(itemname, "Siege defense"))          return SkillType::Siege_Defense;
    if (strstr(itemname, "Turnaround"))             return SkillType::Turnaround;
    if (strstr(itemname, "Back Move Mach"))         return SkillType::Back_Move_Mach;
    if (strstr(itemname, "Defense Up"))             return SkillType::Defense_Up;
    if (strstr(itemname, "Concentration"))          return SkillType::Concentration;
    if (strstr(itemname, "Frenzy"))                 return SkillType::Frenzy;
    if (strstr(itemname, "Berserker"))              return SkillType::Berserker;
    if (strstr(itemname, "Silence"))                return SkillType::Silence;
    if (strstr(itemname, "Purchasing Shop"))        return SkillType::Purchasing_Shop;
    if (strstr(itemname, "Selling Shop"))           return SkillType::Selling_Shop;
    if (strstr(itemname, "Hyper Moving"))           return SkillType::Hyper_Moving;
    if (strstr(itemname, "Chain Rolling"))          return SkillType::Chain_Rolling;
    if (strstr(itemname, "Overbooster"))            return SkillType::Overbooster;
    if (strstr(itemname, "Evasion"))                return SkillType::Evasion_Up;
    if (strstr(itemname, "Missile Shot"))           return SkillType::Missile_Shot;
    if (strstr(itemname, "Fire Shot"))              return SkillType::Fire_Shot;
    if (strstr(itemname, "Hyper Shot"))             return SkillType::Hyper_Shot;
    if (strstr(itemname, "Shield Paralyze"))        return SkillType::Shield_Paralyze;
    if (strstr(itemname, "Camouflage"))             return SkillType::Camouflage;
    if (strstr(itemname, "Snare Shot"))             return SkillType::Snare_Shot;
    if (strstr(itemname, "Ground Accelerator"))     return SkillType::Ground_Accelerator;
    if (strstr(itemname, "Barrier"))                return SkillType::Barrier;
    if (strstr(itemname, "Remedy"))                 return SkillType::Remedy;
    if (strstr(itemname, "Collision Absorption"))   return SkillType::Collision_Absorption;
    if (strstr(itemname, "Air Seige"))              return SkillType::Air_Siege_Mode;
    if (strstr(itemname, "Siege mode"))             return SkillType::Siege_Mode;
    if (strstr(itemname, "Purify"))                 return SkillType::Purify;
    if (strstr(itemname, "Full Recovery"))          return SkillType::Full_Recovery;
    if (strstr(itemname, "Scanning"))               return SkillType::Scanning;
    if (strstr(itemname, "Call of Hero"))           return SkillType::Call_of_Hero;
    if (strstr(itemname, "Smart SP"))               return SkillType::Smart_SP;
    if (strstr(itemname, "Fuel replenish"))         return SkillType::Fuel_Replenish;
    if (strstr(itemname, "Reverse engine"))         return SkillType::Reverse_Engine;
    if (strstr(itemname, "Invincible"))             return SkillType::Invincible;
    if (strstr(itemname, "Repair target"))          return SkillType::Energize_Target;
    if (strstr(itemname, "Repair field"))           return SkillType::Energizing_Field;
    if (strstr(itemname, "Healing target"))         return SkillType::Heal_Target;
    if (strstr(itemname, "Release"))                return SkillType::Release;
    if (strstr(itemname, "Deploy Chaff"))           return SkillType::Deploy_Chaff;
    if (strstr(itemname, "Reduce Damage"))          return SkillType::Reduce_Damage;
    if (strstr(itemname, "Air Bombing Mode"))       return SkillType::Air_Bombing_Mode;
    if (strstr(itemname, "Charge Shot"))            return SkillType::Charge_Shot;
    if (strstr(itemname, "Healing field"))          return SkillType::Healing_Field;
    if (strstr(itemname, "Elevation"))              return SkillType::Elevation;
    if (strstr(itemname, "Big Boom"))               return SkillType::Big_Boom;
    if (strstr(itemname, "Invisible"))              return SkillType::Invisible;
    if (strstr(itemname, "Deploy Chaffs"))          return SkillType::Deploy_Chaffs;
    if (strstr(itemname, "Multitarget Mode"))       return SkillType::Multitarget_Mode;
    if (strstr(itemname, "Ground Bombing Mode"))    return SkillType::Ground_Bombing_Mode;
    return SkillType::Unknown;
}

bool KitBuffBot::TryUseSkill(SkillType skilltype)
{
    PlayerSkillInfo* playerskill = FindPlayerSkill(skilltype);
    return TryUseSkill(playerskill);
}

bool KitBuffBot::ToggleSKill(SkillType toggleskill, bool toggle_on)
{
    PlayerSkillInfo* pskill = FindPlayerSkill(toggleskill);

    if (!pskill || pskill->IsWaiting() || pskill->skillinfo->ItemInfo->SkillType != SKILLTYPE_TOGGLE) {
        return false;
    }

    if (toggle_on == (pskill->skillinfo->m_dwState == SKILL_STATE_USING) ) {
        return true;
    }
    else
    {
        TryUseSkill(pskill);
        return false;
    }
}

bool KitBuffBot::TryUseSkill(PlayerSkillInfo* skillinfo)
{
    if (!skillinfo || !skillinfo->skillinfo || skillinfo->IsWaiting()) {
        return false;
    }

    // only allow the same skill to be used every 400ms because quickslot bar can only be used every 400ms
    std::chrono::milliseconds current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());  
    if ((current - skillinfo->last_use) < 400ms) {
        return false;
    }

    OSR_API->SendUseSkill(skillinfo->skillinfo);
    return true;
}

bool KitBuffBot::TryUseTargetSkill(PlayerSkillInfo* skillinfo, ClientIndex_t target)
{
    if (!TryUseSkill(skillinfo)) {
        return false;
    }
    auto skill = OSR_API->GetAtumApplication()->m_pShuttleChild->m_pSkill;
    skill->m_bSkillTargetState = FALSE;
    skill->m_nTargetIndex = target; 
    return true;
}

bool KitBuffBot::TryUseTargetSkill(PlayerSkillInfo* skillinfo, UID32_t characterUID)
{
    if (!TryUseSkill(skillinfo)) {
        return false;
    }
    auto skill = OSR_API->GetAtumApplication()->m_pShuttleChild->m_pSkill;
    skill->m_bSkillTargetState = FALSE;
    skill->m_nTargetIndex = 0;
    skill->m_nCharacterUID = characterUID;
    return true;
}

void KitBuffBot::OnUseSkillAnswer(int itemnum)
{
    // todo smartsp?


}

void KitBuffBot::OnUseEnergyError(MSG_ERROR* error)
{
    switch (error->ErrorCode)
    {
        // HP item
        case ERR_PROTOCOL_AREADY_FULL_HP:
        case ERR_DEBUFF_SKILL_APPLYING_NOT_HP_RECOVERY:
            m_awaiting_Ok_energy = false;
            break; 
        // DP item
        case ERR_PROTOCOL_AREADY_FULL_DP:
        case ERR_DEBUFF_SKILL_APPLYING_NOT_DP_RECOVERY:
            m_awaiting_Ok_shield = false;
            break;
        // EP item
        case ERR_PROTOCOL_AREADY_FULL_EP:
            m_awaiting_Ok_fuel = false;
            break;                     
        // SP item
        case ERR_DEBUFF_SKILL_APPLYING_NOT_SP_RECOVERY:
        case ERR_PROTOCOL_AREADY_FULL_SP:
            m_awaiting_Ok_skill = false;
            break;
        // no number
        case ERR_USING_BAZAAR:
        case ERR_INFINITY_CANNOT_USE_ITEM:
        case ERR_INFINITY_ONLY_USE_ITEM:
        case ERR_PROTOCOL_ITEM_CANNOT_TRANSFER: 
        case ERR_PROTOCOL_CANNOT_USE_ITEM_IN_ARENA:  
        case ERR_PROTOCOL_CANNOT_USE_ITEM: 
            m_awaiting_Ok_energy = false;
            m_awaiting_Ok_shield = false;
            m_awaiting_Ok_fuel   = false;
            m_awaiting_Ok_skill  = false;
            break;
        // unique itemnum
        case ERR_ITEM_TRADING:
        case ERR_PROTOCOL_NO_SUCH_ITEM:
            break;

        // itemnum
        case ERR_PROTOCOL_INVALID_ITEM_KIND:
        case ERR_PROTOCOL_NO_SUCH_ITEM_INFO:    
        case ERR_ALREADY_USE_ITEMPARAM:
        case ERR_PROTOCOL_NO_SUCH_DES_PARAM:
        {
            CItemInfo* item = OSR_API->FindItemInInventoryByItemNum(error->ErrParam1);
            if (item)
            {
                switch (GetKitTypeFromItem(item))
                {
                case KitType::SHIELD:
                    m_awaiting_Ok_shield = false;
                    break;
                case KitType::ENERGY:
                    m_awaiting_Ok_energy = false;
                    break;
                case KitType::FUEL:
                    m_awaiting_Ok_fuel = false;
                    break;
                case KitType::SKILLPOINT:
                    m_awaiting_Ok_skill = false;
                    break;
                }
            }
            break;
        }
        // itemname
        case ERR_PROTOCOL_INVALID_ITEM_COUNT:
        {
            char* errorstr = new char[error->StringLength + 1];
            ZeroMemory((void*)errorstr, error->StringLength + 1);                        
            strncpy_s(errorstr, error->StringLength, (char*)error + sizeof(MSG_ERROR) + 2, error->StringLength);
            errorstr[error->StringLength] = '\0';

            if (strstr(errorstr, "Shield")) {
                m_awaiting_Ok_shield = false;
            }                    
            else if (strstr(errorstr, "Energy") || strstr(errorstr, "Repair")) {
                m_awaiting_Ok_energy = false;
            }
            else if (strstr(errorstr, "SP kit")) {
                m_awaiting_Ok_skill = false;
            }
            else if (strstr(errorstr, "fuel")) {
                m_awaiting_Ok_fuel = false;
            }
        }
    }
}

void KitBuffBot::OnUseSkillError(MSG_ERROR* error)
{
    switch (error->ErrorCode)
    {
    case ERR_PROTOCOL_NO_SUCH_SKILL:
    case ERR_PROTOCOL_CANNOT_USE_SKILL:
    case ERR_PROTOCOL_INVALID_SKILLTYPE:
    case ERR_PROTOCOL_NOT_ENOUGH_SP:
        break;
        // do something
    }
}

bool KitBuffBot::ShouldUseHealingField()
{
    // check if any party member in range has missing energy
    int shield_missing = 0;
    auto playerpos = OSR_API->GetShuttlePosition();
    if (OSR_API->GetMaxShield() - OSR_API->GetCurrentShield() >= 750) 
    {
        if (OSR_API->GetAtumApplication()->m_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo.size() == 0) {
            return true;
        }
        shield_missing++;
    }

    for (auto& partymember : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo)
    {
        if (!partymember->m_bUserLogOn || !partymember->m_pEnemyData) {
            continue;
        }

        // first check if the member is in range for heals
        D3DXVECTOR3 delta = partymember->m_pEnemyData->m_vPos - playerpos;
        float distance = D3DXVec3Length(&delta);
        if (distance <= 3000.0f)  // hardcoded for now, this value is accurate for all field healings above level 54
        {
            if (partymember->m_pEnemyData->m_infoCharacter.DP - partymember->m_pEnemyData->m_infoCharacter.CurrentDP >= 750)
            {
                shield_missing++;
            }
        }
    }
    // only use healing field if at two or more party members in range are missing energy
    if (shield_missing < 2) {
        return false;
    }

    return true;
}

bool KitBuffBot::ShouldUseEnergizeField()
{
    // check if any party member in range has missing energy
    int energy_missing = 0;
    auto playerpos = OSR_API->GetShuttlePosition();
    if (OSR_API->GetMaxEnergy() - OSR_API->GetCurrentEnergy() >= 500) 
    {
        if (OSR_API->GetAtumApplication()->m_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo.size() == 0) {
            return true;
        }
        energy_missing++;
    }

    for (auto& partymember : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo)
    {
        if (!partymember->m_bUserLogOn || !partymember->m_pEnemyData) {
            continue;
        }

        // first check if the member is in range for heals
        D3DXVECTOR3 delta = partymember->m_pEnemyData->m_vPos - playerpos;
        float distance = D3DXVec3Length(&delta);
        if (distance <= 3000.0f) // hardcoded for now, this value is accurate for all field healings above level 54
        {
            if (partymember->m_pEnemyData->m_infoCharacter.HP - partymember->m_pEnemyData->m_infoCharacter.CurrentHP >= 500)
            {
                energy_missing++;
            }
        }
    }
    // only use energize field if at two or more party members in range are missing energy
    if (energy_missing < 2) {
        return false;
    }

    return true;
}

UID32_t KitBuffBot::GetBestHealTarget()
{
    UID32_t target = 0;
    UID32_t prio_target = 0;

    // get healing target based on missing hp
    int most_missing_energy = 500;
    for (auto member : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo)
    {
        if (!member->m_bUserLogOn || !member->m_pEnemyData) {
            continue;
        }

        int member_energy_missing = member->m_pEnemyData->m_infoCharacter.HP - member->m_pEnemyData->m_infoCharacter.CurrentHP;
        if (member_energy_missing > most_missing_energy)
        {
            most_missing_energy = member_energy_missing;
            target = member->m_nUniqueNumber;

            if (member->m_bSpeakingAuth) {
                prio_target = member->m_nUniqueNumber;
            }
        }
    }

    if (OSR_API->GetMaxEnergy() - OSR_API->GetCurrentEnergy() >= 500)
    {
        target = OSR_API->GetAtumApplication()->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
        if (m_settings.target_heal_prio_myself) {
            return OSR_API->GetAtumApplication()->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
        }
    }

    if (prio_target != 0) {
        return prio_target;
    } 
    return target;
}

UID32_t KitBuffBot::GetBestEnergizeTarget()
{
    UID32_t target = 0;
    UID32_t prio_target = 0;

    // get healing target based on missing shield
    int most_missing_shield = 0;
    for (auto member : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo)
    {
        if (!member->m_bUserLogOn || !member->m_pEnemyData) {
            continue;
        }

        int member_shield_missing = member->m_pEnemyData->m_infoCharacter.DP - member->m_pEnemyData->m_infoCharacter.CurrentDP;
        if (member_shield_missing > most_missing_shield)
        {
            most_missing_shield = member_shield_missing;
            target = member->m_nUniqueNumber;

            if (member->m_bSpeakingAuth) {
                prio_target = member->m_nUniqueNumber;
            }
        }
    }

    if (OSR_API->GetMaxShield() - OSR_API->GetCurrentShield() >= 500)
    {
        target = OSR_API->GetAtumApplication()->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
        if (m_settings.target_heal_prio_myself) {
            return OSR_API->GetAtumApplication()->m_pShuttleChild->m_myShuttleInfo.CharacterUniqueNumber;
        }
    }

    if (prio_target != 0) {
        return prio_target;
    }
    return target;
}
       
PlayerSkillInfo* KitBuffBot::FindPlayerSkill(SkillType skilltype) const
{
    for (auto playerskill : m_playerskills)
    {
        if (playerskill->type == skilltype)
        {
            return playerskill;
        }
    }
    return nullptr;
}

PlayerSkillInfo* KitBuffBot::FindPlayerSkill(int itemnum) const
{
    for (auto playerskill : m_playerskills)
    {
        if (playerskill->skillinfo->ItemInfo->ItemNum == itemnum)
        {
            return playerskill;
        }
    }
    return nullptr;
}

bool KitBuffBot::AutoBuffCheckTimerReady()
{
    std::chrono::milliseconds current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return (current - m_lastAutoBuffCheck >= AUTOBUFF_CHECK_TIME);
}

bool KitBuffBot::AutoHealCheckTimerReady()
{
    std::chrono::milliseconds current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return (current - m_last_auto_heal_check >= AUTOHEAL_CHECK_TIME);
}

void KitBuffBot::Tick()
{ 
    if (!IsEnabled() || OSR_API->IsShuttleDead())  {
        return;
    }  
    
    TickAutoKit();
    TickAutoBuff();
    TickAutoHeals();
    TickAutoAmmo();
}
     
void KitBuffBot::RenderImGui()
{   
    DrawEnableCheckBox();   
    ImGui::BeginGroupPanel("Kits");
    {  
        const char* items[] = { "Rage", "Humanized", "Sleepy" };
        ImGui::ComboEx("Mode:", reinterpret_cast<int*>(&m_settings.kitmode), items, 3, -1, true, 150);
        ImGui::Dummy(ImVec2(0, 5));

        ImGui::BeginGroupPanel("Shield", ImVec2(100, 200));
        {
            if (ImGui::Checkbox("S Type", &m_settings.use_shield_type_s))
            {
                if (m_settings.use_shield_type_s)
                {
                    m_settings.use_shield_type_a = true;
                    m_settings.use_shield_type_b = true;
                    m_settings.use_shield_type_c = true;
                }
            }
            if (ImGui::Checkbox("A Type", &m_settings.use_shield_type_a))
            {
                if (m_settings.use_shield_type_a)
                {
                    m_settings.use_shield_type_b = true;
                    m_settings.use_shield_type_c = true;
                }
            }
            if (ImGui::Checkbox("B Type", &m_settings.use_shield_type_b))
            {
                if (m_settings.use_shield_type_b) {
                    m_settings.use_shield_type_c = true;
                }
            }
            ImGui::Checkbox("C Type", &m_settings.use_shield_type_c);
        }
        ImGui::EndGroupPanel();
        ImGui::SameLine();
        ImGui::BeginGroupPanel("Energy", ImVec2(100, 200));
        {
            if (ImGui::Checkbox("S Type##", &m_settings.use_energy_type_s))
            {
                if (m_settings.use_energy_type_s)
                {
                    m_settings.use_energy_type_a = true;
                    m_settings.use_energy_type_b = true;
                    m_settings.use_energy_type_c = true;
                }
            }
            if (ImGui::Checkbox("A Type##", &m_settings.use_energy_type_a))
            {
                if (m_settings.use_energy_type_a)
                {
                    m_settings.use_energy_type_b = true;
                    m_settings.use_energy_type_c = true;
                }
            }
            if (ImGui::Checkbox("B Type##", &m_settings.use_energy_type_b))
            {
                if (m_settings.use_energy_type_b) {
                    m_settings.use_energy_type_c = true;
                }
            }
            ImGui::Checkbox("C Type##", &m_settings.use_energy_type_c);
        }
        ImGui::EndGroupPanel();
        ImGui::SameLine();
        ImGui::BeginGroupPanel("Other");
        {
            ImGui::Checkbox("Ammo", &m_settings.use_ammobox);
            ImGui::Checkbox("Fuel", &m_settings.use_fuel);
        }
        ImGui::EndGroupPanel();
        ImGui::BeginGroupPanel("Skillpoints", ImVec2(100, 200));
        {
            ImGui::Checkbox("A Type", &m_settings.use_spkit_type_a);
            ImGui::SameLine();
            ImGui::PushItemWidth(200);
            ImGui::SliderInt("%##spkit_a_slider", &m_settings.spkit_type_a_percentage, 0, 99);
            ImGui::PopItemWidth();

            ImGui::Checkbox("B Type", &m_settings.use_spkit_type_b);
            ImGui::SameLine();
            ImGui::PushItemWidth(200);
            ImGui::SliderInt("%##spkit_b_slider", &m_settings.spkit_type_b_percentage, 0, 99);
            ImGui::PopItemWidth();

            ImGui::Checkbox("C Type", &m_settings.use_spkit_type_c);
            ImGui::SameLine();
            ImGui::PushItemWidth(200);
            ImGui::SliderInt("%##spkit_c_slider", &m_settings.spkit_type_c_percentage, 0, 99);     
            ImGui::PopItemWidth();
        }                         
        ImGui::EndGroupPanel();    
    }
    ImGui::EndGroupPanel();
    ImGui::SameLine();
    ImGui::BeginGroupPanel("Buffs");
    {   
        //ImGui::EndGroupPanel();    
        ImGui::BeginGroupPanel("Autobuffs", ImVec2(300, 0));
        {
            ImGui::BeginGroup();
            for (auto skill : m_playerskills)
            {
                switch (skill->type)
                {
                case SkillType::Concentration:
                case SkillType::Missile_Shot:
                case SkillType::Fire_Shot:
                case SkillType::Evasion_Up:
                case::SkillType::Defense_Up:
                    if (skill->final) {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0x00, 0xFF, 0xFF).Value);
                    }
                    if (ImGui::Checkbox(skill->clean_name.c_str(), &skill->autobuff))
                    {
                        if (skill->autobuff) {
                            AddAutoBuff(skill->type);
                        }
                        else {
                            RemoveAutoBuff(skill->type);
                        }
                    }
                    if (skill->final) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::EndGroup();
            ImGui::SameLine();
            ImGui::BeginGroup();
            {
                for (auto skill : m_playerskills)
                {
                    switch (skill->type)
                    {
                    case SkillType::Frenzy:
                    case SkillType::Elevation:
                    case SkillType::Raging_Defense:
                    case SkillType::Raging_Evasion:
                    case SkillType::Raging_Fire:
                        if (skill->final) {
                            ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0x00, 0xFF, 0xFF).Value);
                        }
                        if (ImGui::Checkbox(skill->clean_name.c_str(), &skill->autobuff))
                        {
                            if (skill->autobuff) {
                                AddAutoBuff(skill->type);
                            }
                            else {
                                RemoveAutoBuff(skill->type);
                            }
                        }
                        if (skill->final) {
                            ImGui::PopStyleColor();
                        }
                    }
                }
            }
            ImGui::EndGroup();
        }
        ImGui::EndGroupPanel(); 
        ImGui::BeginGroupPanel("Autohealings");
        { 
            if (OSR_API->GetPlayerGearType() != GearType::MGear)
            {
                ImGui::Text("Only available for MG!");
            }
            else
            {
                ImGui::Text("Field: \t");
                ImGui::SameLine();
                ImGui::Checkbox("Shield", &m_settings.field_energizings_active);
                ImGui::SameLine();
                ImGui::Checkbox("Energy", &m_settings.field_healings_active);
                             
                ImGui::Text("Target:\t");
                ImGui::SameLine();
                ImGui::Checkbox("Shield##targetShield", &m_settings.target_energizing_active);
                ImGui::SameLine();
                ImGui::Checkbox("Energy##targetEnergy", &m_settings.target_healings_active);

                ImGui::NewLine();
                ImGui::BeginGroupPanel("Priority Healing", ImVec2(290, 400));
                {
                    ImGui::Checkbox(OSR_API->GetAtumApplication()->m_pShuttleChild->m_myShuttleInfo.CharacterName, &m_settings.target_heal_prio_myself);
                    for (auto& partymember : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pClientParty->m_vecPartyEnemyInfo) {
                        ImGui::Checkbox(partymember->m_ImPartyMemberInfo.CharacterName, (bool*)&partymember->m_bSpeakingAuth);
                    }
                }
                ImGui::EndGroupPanel();
            }             
        }
        ImGui::EndGroupPanel();
    }
    ImGui::EndGroupPanel();
}

const char* KitBuffBot::GetName() const
{
    return "KitBot";
}

bool KitBuffBot::OnReadPacket(unsigned short msgtype, byte* packet)
{  
    switch (msgtype)
    {    
    case  T_FC_ITEM_USE_ENERGY_OK:
    {
        MSG_FC_ITEM_USE_ENERGY_OK* msg = (MSG_FC_ITEM_USE_ENERGY_OK*)packet;
        CItemInfo* kit = nullptr;
        switch (TO_ENUM(ItemNumber, msg->ItemNum))
        {
        case ItemNumber::S_Type_RepairKit_1:
        case ItemNumber::S_Type_RepairKit_2:
        case ItemNumber::A_Type_RepairKit_1:
        case ItemNumber::A_Type_RepairKit_2:
        case ItemNumber::B_Type_RepairKit:
        case ItemNumber::C_Type_RepairKit:
            kit = OSR_API->FindItemInInventoryByItemNum(msg->ItemNum);
            if (kit)
            {
                // KitBot::Rage == no additional time
                std::chrono::milliseconds additional_time = 34ms;
                switch (m_settings.kitmode)
                {
                case KitBuffBot::Humanized:
                    additional_time = std::chrono::milliseconds(m_buddy->GetRandInt32(100, 700));
                    break;
                case KitBuffBot::Sleepy:
                    additional_time = std::chrono::milliseconds(m_buddy->GetRandInt32(500, 1500));
                    break;
                }
                m_energykit_reattack_time = std::chrono::milliseconds(kit->m_pItemInfo->ReAttacktime) + additional_time;
                m_lastUseEnergyKitTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
                m_awaiting_Ok_energy = false;
            }
            break;
        case ItemNumber::S_Type_ShieldKit_1:
        case ItemNumber::S_Type_ShieldKit_2:
        case ItemNumber::A_Type_ShieldKit_1:
        case ItemNumber::A_Type_ShieldKit_2:
        case ItemNumber::B_Type_ShieldKit:
        case ItemNumber::C_Type_ShieldKit:
            kit = OSR_API->FindItemInInventoryByItemNum(msg->ItemNum);
            if (kit)
            {
                // KitBot::Rage == no additional time
                std::chrono::milliseconds additional_time = 34ms;
                switch (m_settings.kitmode)
                {
                case KitBuffBot::Humanized:
                    additional_time = std::chrono::milliseconds(m_buddy->GetRandInt32(100, 700));
                    break;
                case KitBuffBot::Sleepy:
                    additional_time = std::chrono::milliseconds(m_buddy->GetRandInt32(500, 1500));
                    break;
                }
                m_shieldkit_reattack_time = std::chrono::milliseconds(kit->m_pItemInfo->ReAttacktime) + additional_time;
                m_lastUseShieldKitTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
                m_awaiting_Ok_shield = false;
            }
            break;
        case ItemNumber::A_Type_SkillPKit_1:
        case ItemNumber::A_Type_SkillPKit_2:
        case ItemNumber::B_Type_SkillPKit:
        case ItemNumber::C_Type_SkillPKit:
        case ItemNumber::A_Type_SkillPit_MG:
        case ItemNumber::B_Type_SkillPKit_MG:
        case ItemNumber::C_Type_SkillPKit_MG:
            kit = OSR_API->FindItemInInventoryByItemNum(msg->ItemNum);
            if (kit)
            {
                // KitBot::Rage == no additional time
                std::chrono::milliseconds additional_time = 33ms;
                switch (m_settings.kitmode)
                {
                case KitBuffBot::Humanized:
                    additional_time = std::chrono::milliseconds(m_buddy->GetRandInt32(100, 700));
                    break;
                case KitBuffBot::Sleepy:
                    additional_time = std::chrono::milliseconds(m_buddy->GetRandInt32(500, 2000));
                    break;
                }
                m_skillpkit_reattack_time = std::chrono::milliseconds(kit->m_pItemInfo->ReAttacktime) + additional_time;
                m_lastUseSkillKitTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
                m_awaiting_Ok_skill = false;
            }
            break;
    
        case ItemNumber::B_Type_CondensedFuel:
        case ItemNumber::C_Type_CondensedFuel:
        case ItemNumber::D_Type_CondensedFuel:
        case ItemNumber::E_Type_CondensedFuel:
            m_awaiting_Ok_fuel = false;
            break;
        }
        break;
    }
    case T_FC_BATTLE_PRI_BULLET_RELOADED:
    case T_FC_BATTLE_SEC_BULLET_RELOADED:
    {
        MSG_FC_BATTLE_PRI_BULLET_RELOADED* reloaded_msg = (MSG_FC_BATTLE_PRI_BULLET_RELOADED*)packet;
        if (reloaded_msg->RechargeType == BULLET_RECHARGE_TYPE_BULLET_ITEM && m_awaiting_Ok_ammobox) {
            m_awaiting_Ok_ammobox = false;
        }
        break;
    }   
    case T_FC_SKILL_USE_SKILL_OK: 
        {
            MSG_FC_SKILL_USE_SKILL_OK* use_skill_ok_msg = (MSG_FC_SKILL_USE_SKILL_OK*)packet;
           //OnUseSkillAnswer(use_skill_ok_msg->SkillItemID.ItemNum);
            break;
        }
    case  T_FC_SKILL_CANCEL_SKILL_OK:
        {
            MSG_FC_SKILL_CANCEL_SKILL_OK* cancel_skill_ok_msg = (MSG_FC_SKILL_CANCEL_SKILL_OK*)packet;
            //OnUseSkillAnswer(cancel_skill_ok_msg->SkillItemID.ItemNum);
            break;
        }
    case T_FC_SKILL_INVALIDATE_SKILL:
        {
            MSG_FC_SKILL_INVALIDATE_SKILL* invalidate_skill_msg = (MSG_FC_SKILL_INVALIDATE_SKILL*)packet;
            //OnUseSkillAnswer(invalidate_skill_msg->SkillItemID.ItemNum);
            break;
        } 
    case T_ERROR:  
        {
            MSG_ERROR* error_msg = (MSG_ERROR*)packet;
            switch (error_msg->MsgType)
            {
            case T_FC_ITEM_USE_ENERGY:
                OnUseEnergyError(error_msg);
                break;
            case T_FC_SKILL_USE_SKILL:
                OnUseSkillError(error_msg);
                break;
            }
        }
    }
  
    return false;
}

bool KitBuffBot::OnWritePacket(unsigned short msgtype, byte* packet)
{
    switch (msgtype)
    {
    case T_FC_ITEM_USE_ENERGY:
    {
        MSG_FC_ITEM_USE_ENERGY* msg_use_energy = (MSG_FC_ITEM_USE_ENERGY*)packet;
        CItemInfo* uitem = OSR_API->FindItemInInventoryByUniqueNumber(msg_use_energy->ItemUniqueNumber);
        if (uitem)
        {
            auto current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

            KitType kittype = GetKitTypeFromItem(uitem);
            switch (kittype)
            {
            case KitType::NONE:
                break;
            case KitType::SHIELD:
                m_awaiting_Ok_shield = true;
                m_lastSendShieldKitTime = current;
                break;
            case KitType::ENERGY:
                m_awaiting_Ok_energy = true;
                m_lastSendEnergyKitTime = current;
                break;
            case KitType::SKILLPOINT:
                m_awaiting_Ok_skill = true;
                m_lastSendSkillKitTime = current;
                break;
            case KitType::FUEL:
                m_awaiting_Ok_fuel = true;
                m_lastSendFuelKitTime = current;
                break;
            }
        }
    }                           
    case T_FC_SKILL_USE_SKILL:
        {
            MSG_FC_SKILL_USE_SKILL* msg_use_skill = (MSG_FC_SKILL_USE_SKILL*)packet;
            PlayerSkillInfo* pskill = FindPlayerSkill(msg_use_skill->SkillItemID.ItemNum);
            if (pskill) {
                pskill->last_use = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            }
            break;
        }    
    case T_FC_SKILL_CANCEL_SKILL:
        {
            MSG_FC_SKILL_CANCEL_SKILL* msg_cancel_skill = (MSG_FC_SKILL_CANCEL_SKILL*)packet;
            PlayerSkillInfo* pskill = FindPlayerSkill(msg_cancel_skill->SkillItemID.ItemNum);
            if (pskill) {
                pskill->last_use = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
            }
            break;
        }
    case T_FC_SKILL_PREPARE_USE:
    case T_FC_SKILL_SETUP_SKILL:
        {
            MSG_FC_SKILL_PREPARE_USE* msg_prepare_skill = (MSG_FC_SKILL_PREPARE_USE*)packet;
        }
    }
    return 0;
}

FeatureType KitBuffBot::GetType() const
{
    return FeatureType::KitBuffBot;
}
           
void KitBuffBot::TickAutoKit()
{
    std::chrono::milliseconds current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    bool shieldtimer_ready = ((current - m_lastUseShieldKitTime) > m_shieldkit_reattack_time);
    bool energytimer_ready = ((current - m_lastUseEnergyKitTime) > m_energykit_reattack_time);
    bool skillptimer_ready = ((current - m_lastUseSkillKitTime) > m_skillpkit_reattack_time);

    int missing_shield = OSR_API->GetMaxShield() - OSR_API->GetCurrentShield();
    int missing_energy = OSR_API->GetMaxEnergy() - OSR_API->GetCurrentEnergy();


    // m_awaiting_Ok == true => sent kit already but server did not aknowledge it yet or kit timer on server was slower -_-ˆ
    // try to send again after 25ms
    // this will account for lag, e.g. Mothership war
    if (m_awaiting_Ok_shield && ((current - m_lastSendShieldKitTime) > KIT_RESEND_TIME))
    {
        m_awaiting_Ok_shield = false;
    }
    if (m_awaiting_Ok_energy && ((current - m_lastSendEnergyKitTime) > KIT_RESEND_TIME))
    {
        m_awaiting_Ok_energy =  false;
    }
    if (m_awaiting_Ok_skill && ((current - m_lastSendSkillKitTime) > KIT_RESEND_TIME))
    {
        m_awaiting_Ok_skill = false;
    }

    // Shield Kits
    if (shieldtimer_ready)
    {
        if (missing_shield == 0 && m_shieldkit_firstuse_delay == 0ms)
        {
            switch (m_settings.kitmode)
            {
            case KitBuffBot::Humanized:
                m_shieldkit_firstuse_delay = std::chrono::milliseconds(m_buddy->GetRandInt32(200, 1000));
                break;
            case KitBuffBot::Sleepy:
                m_shieldkit_firstuse_delay = std::chrono::milliseconds(m_buddy->GetRandInt32(800, 2500));
                break;
            default:
                break;
            }
        }

        if (missing_shield > 0)
        {
            if (m_shieldkit_firstuse_delay > 0ms)
            {
                m_shieldkit_firstuse_delay -= std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
                if (m_shieldkit_firstuse_delay < 0ms) {
                    m_shieldkit_firstuse_delay = 0ms;
                }
            }
            else
            {
                bool used_kit = false;

                if (m_settings.use_shield_type_c && (missing_shield <= 654 || (!m_settings.use_shield_type_b && !m_settings.use_shield_type_a && !m_settings.use_shield_type_s))) {
                    used_kit = TryUseKit(KitType::SHIELD, KitCategory::C_TYPE);
                }

                if (!used_kit && m_settings.use_shield_type_b && (missing_shield <= 1253 || (!m_settings.use_shield_type_a && !m_settings.use_shield_type_s))) {
                    used_kit = TryUseKit(KitType::SHIELD, KitCategory::B_TYPE);
                }

                if (!used_kit && m_settings.use_shield_type_a && (missing_shield <= 2633 || !m_settings.use_shield_type_s)) {
                    used_kit = TryUseKit(KitType::SHIELD, KitCategory::A_TYPE);
                }

                if (!used_kit && m_settings.use_shield_type_s) {
                    used_kit = TryUseKit(KitType::SHIELD, KitCategory::S_TYPE);
                }
            }
        }
    }

    // Energy Kits
    if (energytimer_ready)
    {
        if (missing_energy == 0 && m_energykit_firstuse_delay == 0ms)
        {
            switch (m_settings.kitmode)
            {
            case KitBuffBot::Humanized:
                m_energykit_firstuse_delay = std::chrono::milliseconds(m_buddy->GetRandInt32(300, 700));
                break;
            case KitBuffBot::Sleepy:
                m_energykit_firstuse_delay = std::chrono::milliseconds(m_buddy->GetRandInt32(500, 2000));
                break;
            default:
                break;
            }
        }

        if (missing_energy > 0)
        {
            if (m_energykit_firstuse_delay > 0ms)
            {
                m_energykit_firstuse_delay -= std::chrono::duration_cast<std::chrono::milliseconds>(m_buddy->GetTickTime());
                if (m_energykit_firstuse_delay < 0ms) {
                    m_energykit_firstuse_delay = 0ms;
                }
            }
            else
            {
                bool used_kit = false;

                if (m_settings.use_energy_type_c && (missing_energy <= 327 || (!m_settings.use_energy_type_b && !m_settings.use_energy_type_a && !m_settings.use_energy_type_s))) {
                    used_kit = TryUseKit(KitType::ENERGY, KitCategory::C_TYPE);
                }

                if (!used_kit && m_settings.use_energy_type_b && (missing_energy <= 626 || (!m_settings.use_energy_type_a && !m_settings.use_energy_type_s))) {
                    used_kit = TryUseKit(KitType::ENERGY, KitCategory::B_TYPE);
                }

                if (!used_kit && m_settings.use_energy_type_a && (missing_energy <= 1317 || !m_settings.use_energy_type_s)) {
                    used_kit = TryUseKit(KitType::ENERGY, KitCategory::A_TYPE);
                }

                if (!used_kit && m_settings.use_energy_type_s) {
                    used_kit = TryUseKit(KitType::ENERGY, KitCategory::S_TYPE);
                }
            }
        }
    }

    // Skillpoint kits
    if (skillptimer_ready)
    {
        // todo: SmartSP

        bool sp_kit_used = false;
        int skillp_percentage = 100 * (static_cast<float>(std::max(OSR_API->GetCurrentSkillp(), 1)) / static_cast<float>(OSR_API->GetMaxSkillp()));

        if(m_settings.use_spkit_type_a && skillp_percentage <= m_settings.spkit_type_a_percentage)  
        { 
            sp_kit_used = TryUseKit(KitType::SKILLPOINT, KitCategory::A_TYPE);  
        }
        if (!sp_kit_used && m_settings.use_spkit_type_b && skillp_percentage <= m_settings.spkit_type_b_percentage) 
        {
            sp_kit_used = TryUseKit(KitType::SKILLPOINT, KitCategory::B_TYPE);
        }
        if (!sp_kit_used && m_settings.use_spkit_type_c && skillp_percentage <= m_settings.spkit_type_c_percentage)
        {
            sp_kit_used = TryUseKit(KitType::SKILLPOINT, KitCategory::C_TYPE);
        }   
    }         

    // Fuelkits
    if (m_settings.use_fuel && !m_awaiting_Ok_fuel && OSR_API->GetCurrentFuel() < FUEL_KIT_THRESHOLD) {
        TryUseKit(KitType::FUEL, KitCategory::B_TYPE);
    }
}       

void KitBuffBot::TickAutoBuff()
{                                     
    if (AutoBuffCheckTimerReady())
    {
        int currentsp = OSR_API->GetCurrentSkillp();
       
        for (auto pskill : m_playerskills)
        {
            if (pskill->autobuff && !pskill->IsWaiting() && pskill->skillinfo->ItemInfo->ReqSP <= currentsp && pskill->skillinfo->m_fCheckReattackTime <= 0.0f)
            {   
                TryUseSkill(pskill);
                currentsp -= pskill->skillinfo->ItemInfo->ReqSP;
            }
        } 
        m_lastAutoBuffCheck = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    }      
}

void KitBuffBot::TickAutoAmmo()
{
    if (m_settings.use_ammobox && !m_awaiting_Ok_ammobox && 
       (OSR_API->GetPrimaryWeaponAmmo() == 0 || OSR_API->GetSecondaryWeaponAmmo() == 0)) 
    {
        TryUseAmmunitionBox();
    }
}

void KitBuffBot::TickAutoHeals()
{
    if (OSR_API->GetPlayerGearType() == GearType::MGear  && AutoHealCheckTimerReady())
    {
        int currentsp = OSR_API->GetCurrentSkillp();

        if (m_settings.target_energizing_active)
        {
            UID32_t energize_target = GetBestEnergizeTarget();
            if (energize_target != 0)
            {
                PlayerSkillInfo* energize_skill = FindPlayerSkill(SkillType::Energize_Target);
                if (energize_skill && energize_skill->skillinfo->m_fCheckReattackTime <= 0.0f && energize_skill->skillinfo->ItemInfo->ReqSP <= currentsp) 
                {
                    TryUseTargetSkill(energize_skill, energize_target);
                    currentsp -= energize_skill->skillinfo->ItemInfo->ReqSP;
                }
            }
        }

        if (m_settings.target_healings_active)
        {
            UID32_t heal_target = GetBestHealTarget();
            if (heal_target != 0)
            {
                PlayerSkillInfo* heal_skill = FindPlayerSkill(SkillType::Heal_Target);
                if (heal_skill && heal_skill->skillinfo->m_fCheckReattackTime <= 0.0f && heal_skill->skillinfo->ItemInfo->ReqSP <= currentsp)
                {
                    TryUseTargetSkill(heal_skill, heal_target); 
                    currentsp -= heal_skill->skillinfo->ItemInfo->ReqSP;
                }
            } 
        } 

        if (m_settings.field_energizings_active) 
        {
            PlayerSkillInfo* energizefield = FindPlayerSkill(SkillType::Energizing_Field);
            if (energizefield && energizefield->skillinfo->m_fCheckReattackTime <= 0.0f && energizefield->skillinfo->ItemInfo->ReqSP <= currentsp && ShouldUseEnergizeField())
            {
                TryUseSkill(energizefield);
                currentsp -= energizefield->skillinfo->ItemInfo->ReqSP;
            }
        } 

        if (m_settings.field_healings_active)
        {
            PlayerSkillInfo* healingfield = FindPlayerSkill(SkillType::Healing_Field);
            if (healingfield && healingfield->skillinfo->m_fCheckReattackTime <= 0.0f && healingfield->skillinfo->ItemInfo->ReqSP <= currentsp && ShouldUseHealingField())
            {
                TryUseSkill(healingfield);
                currentsp -= healingfield->skillinfo->ItemInfo->ReqSP;
            }            
        }
    }
}

void KitBuffBot::GrabPlayerSkills()
{
    // Update the players skills
    m_playerskills.clear();
    ClearAutoBuff();
    for (auto& skillinfo : OSR_API->GetAtumApplication()->m_pShuttleChild->m_pSkill->m_mapSkill)
    {
        PlayerSkillInfo* skill = new PlayerSkillInfo();   
        skill->type = ResolveSkillItemName(skillinfo.second->ItemInfo->ItemName);

        if (skill->type != SkillType::Unknown)
        {
            skill->autobuff = false;
            skill->skillinfo = skillinfo.second;
            skill->last_use = 0ms;
            skill->clean_name = std::string(skill->skillinfo->ItemInfo->ItemName);
            if (skill->clean_name[0] == '\\')  // check if name has a colorcode
            {
                skill->clean_name.erase(skill->clean_name.begin(), skill->clean_name.begin() + 2);
                skill->clean_name.erase(skill->clean_name.end() - 2, skill->clean_name.end());
                skill->final = true;
            }
            m_playerskills.push_back(skill);
        }
    }
}
