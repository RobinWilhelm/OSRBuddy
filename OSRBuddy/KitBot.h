#pragma once
#include "BuddyFeatureBase.h"
#include "OSRImGuiMenu.h"
#include <chrono>
#include <algorithm>
#include <queue>
#include "SDK/SkillInfo.h"

#define AUTOBUFF_CHECK_TIME 1s
#define AUTOHEAL_CHECK_TIME 200ms

#define FUEL_KIT_THRESHOLD 20

#define SKILL_STATE_READY			0
#define SKILL_STATE_WAITING_PREPARE	1
#define SKILL_STATE_PREPARE			2
#define SKILL_STATE_WAITING			3
#define SKILL_STATE_USING			4
#define SKILL_STATE_WAIT_REATTACK	5
#define SKILL_STATE_RELEASE			6

#define SKILLTYPE_PERMANENT		0	// Áö¼ÓÇü
#define SKILLTYPE_CLICK			1	// Å¬¸¯Çü
#define SKILLTYPE_TIMELIMIT		2	// ½Ã°£Çü
#define SKILLTYPE_TOGGLE		3	// Åä±ÛÇü
#define SKILLTYPE_CHARGING		4	// Â÷Â¡Çü, ½ºÅ³ »ç¿ë ÀÌÈÄ ¹Ù·Î ´ÙÀ½ÀÇ µ¿ÀÛ(¹ß»ç µî)¿¡¸¸ 1È¸ Àû¿ëµÇ´Â ½ºÅ³

typedef struct
{
	MessageType_t	MsgType;	// ¿¡·¯°¡ ÀÏ¾î³µÀ» ¶§ Ã³¸®ÁßÀÌ¾ú´ø Message Type
	Err_t			ErrorCode;			// 2 bytes
	BOOL			CloseConnection;	// Client¿¡¼­ ¿¬°áÀ» ²÷À»Áö¿¡ ´ëÇÑ ¿©ºÎ
	INT				ErrParam1;			// general-purpose err parameter 1
	INT				ErrParam2;			// general-purpose err parameter 2
	USHORT			StringLength;		// 2 bytes
	//char*	String;				// error string
} MSG_ERROR;

enum class KitType : unsigned short
{	 
	NONE = 0,
	SHIELD,
	ENERGY,
	SKILLPOINT,
	FUEL,
	
};

enum class KitCategory : unsigned short
{
	S_TYPE = 0,
	A_TYPE,
	B_TYPE,
	C_TYPE,
};
 

class CSkillInfo;	 

struct PlayerSkillInfo
{
	SkillType type;
	CSkillInfo* skillinfo;
	std::string clean_name;
	bool final;			 
	bool autobuff;
	std::chrono::milliseconds last_use;

	inline bool IsWaiting() {
		return skillinfo->m_dwState == SKILL_STATE_WAITING || skillinfo->m_dwState == SKILL_STATE_PREPARE;
	}
};

			   
class KitBuffBot : public BuddyFeatureBase
{
public:	 
	enum Mode
	{
		Rage,
		Humanized,
		Sleepy,
	};

	struct KitSettings
	{
		KitSettings& operator=(const KitSettings& other)
		{
			kitmode = other.kitmode;
			use_shield_type_s = other.use_shield_type_s;
			use_shield_type_a = other.use_shield_type_a;
			use_shield_type_b = other.use_shield_type_b;
			use_shield_type_c = other.use_shield_type_c;
			use_energy_type_s = other.use_energy_type_s;
			use_energy_type_a = other.use_energy_type_a;
			use_energy_type_b = other.use_energy_type_b;
			use_energy_type_c = other.use_energy_type_c;
			use_ammobox = other.use_ammobox;
			use_fuel = other.use_fuel;

			field_healings_active = other.field_healings_active; 
			field_repair_active = other.field_repair_active; 
			target_healings_active = other.target_healings_active;						
			target_repair_active = other.target_repair_active;	 
			target_heal_prio_myself = other.target_heal_prio_myself;

			use_spkit_type_a = other.use_spkit_type_a;
			use_spkit_type_b = other.use_spkit_type_b;
			use_spkit_type_c = other.use_spkit_type_c;

			spkit_type_a_percentage = other.spkit_type_a_percentage;
			spkit_type_b_percentage = other.spkit_type_b_percentage;
			spkit_type_c_percentage = other.spkit_type_c_percentage;
			return *this;
		}

		Mode kitmode;
		bool use_shield_type_s;
		bool use_shield_type_a;
		bool use_shield_type_b;
		bool use_shield_type_c;
		bool use_energy_type_s;
		bool use_energy_type_a;
		bool use_energy_type_b;
		bool use_energy_type_c;
		bool use_ammobox;
		bool use_fuel;

		bool field_healings_active;
		bool field_repair_active;
		bool target_healings_active;
		bool target_repair_active;
		bool target_heal_prio_myself; 

		bool use_spkit_type_a;
		bool use_spkit_type_b;
		bool use_spkit_type_c;
							 
		int spkit_type_a_percentage;
		int spkit_type_b_percentage;
		int spkit_type_c_percentage;
	};

public:
	KitBuffBot(OSRBuddyMain* buddy); 

	// Returns true when the kit usage request has been sent to the server, false when not.
	// The reason for false could be that requiered kits are not in inventory or the server has not answered the last request yet
	bool TryUseKit(KitType type, KitCategory category);
	bool KitTimerReady(KitType kittype);
	bool TryUseAmmunitionBox();

	KitType	GetKitTypeFromItem(CItemInfo* item);

	void SetSettings(KitSettings& settings);

	// Returns true when the skill has been registerd as autobuff. Returns false when the skill was not found.
	bool AddAutoBuff(SkillType skill);
	void RemoveAutoBuff(SkillType skill);
	void ClearAutoBuff();			  

	bool IsAutoBuff(SkillType skill);
	SkillType ResolveSkillItemName(const char* itemname);

	// returns true when the skill usage has been sent to the server. This does not mean the skill has been successfully used.
	// returns false when the skill is not available or the server has not answered the last request yet
	bool TryUseSkill(SkillType skill);	
	bool TryUseSkill(PlayerSkillInfo* skillinfo);

	bool TryUseTargetSkill(PlayerSkillInfo* skillinfo, ClientIndex_t target);
	bool TryUseTargetSkill(PlayerSkillInfo* skillinfo, UID32_t characterUID);

	// returns true if skill is already toggled on, false when not
	bool ToggleSKill(SkillType toggleskill, bool on);
	

	PlayerSkillInfo* FindPlayerSkill(SkillType skill) const;
	PlayerSkillInfo* FindPlayerSkill(int itemnum) const;
	bool AutoBuffCheckTimerReady();
	bool AutoHealCheckTimerReady();

protected:
	// Geerbt über IBuddyFeature
	virtual void Tick() override;
	virtual void RenderImGui() override;
	virtual const char* GetName() const override;
	virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
	virtual bool OnWritePacket(unsigned short msgtype, byte* packet) override;
	virtual FeatureType GetType() const override;

private:
	void TickAutoKit();
	void TickAutoBuff();
	void TickAutoAmmo();
	void TickAutoHeals();

	void GrabPlayerSkills();
	void OnUseSkillAnswer(int itemnum);
	void OnUseEnergyError(MSG_ERROR* error);
	void OnUseSkillError(MSG_ERROR* error);

	bool ShouldUseHealingField();
	bool ShouldUseEnergizeField();

	UID32_t GetBestHealTarget();
	UID32_t GetBestRepairTarget();

private:   
	KitSettings m_settings;

	bool m_awaiting_server_ok_shield;
	bool m_awaiting_server_ok_energy;
	bool m_awaiting_server_ok_skill;		   
	bool m_awaiting_server_ok_ammobox;
	bool m_awaiting_server_ok_fuel;   

	std::vector<PlayerSkillInfo*> m_playerskills;
	std::chrono::milliseconds m_last_autobuff_check;
	std::chrono::milliseconds m_last_autoheal_check;

	std::chrono::milliseconds m_shieldkit_firstuse_delay;
	std::chrono::milliseconds m_energykit_firstuse_delay;
	std::chrono::milliseconds m_skillpkit_firstuse_delay;

	std::chrono::milliseconds m_shieldkit_reattack_time;
	std::chrono::milliseconds m_energykit_reattack_time;
	std::chrono::milliseconds m_skillpkit_reattack_time;
	std::chrono::milliseconds m_fuelkit_reattack_time;

	std::chrono::milliseconds m_shieldkit_last_use;
	std::chrono::milliseconds m_energykit_last_use;
	std::chrono::milliseconds m_skillkit_last_use;	   
	std::chrono::milliseconds m_fuelkit_last_use;			   

	std::chrono::milliseconds m_shieldkit_last_send;
	std::chrono::milliseconds m_energykit_last_send;
	std::chrono::milliseconds m_skillkit_last_send;
	std::chrono::milliseconds m_fuelkit_last_send;
};
