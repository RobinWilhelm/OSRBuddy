#pragma once
#include "BuddyFeatureBase.h"
#include "OSRImGuiMenu.h"
#include <chrono>
#include <algorithm>
#include <queue>
#include "SDK/SkillInfo.h"

#define AUTOBUFF_CHECK_TIME 1s
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

struct SkillpSettings
{
	byte min_percentage;
	KitCategory category;

	bool operator < (const SkillpSettings& other) const
	{
		return (min_percentage < other.min_percentage);
	}
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

			spkit_usage = other.spkit_usage;
			std::sort(spkit_usage.begin(), spkit_usage.end());
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
		std::vector<SkillpSettings> spkit_usage;
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

	// returns true if skill is already toggled on, false when not
	bool ToggleSKill(SkillType toggleskill, bool on);
	

	PlayerSkillInfo* FindPlayerSkill(SkillType skill) const;
	PlayerSkillInfo* FindPlayerSkill(int itemnum) const;
	bool AutoBuffCheckTimerReady();

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
	bool TryUseSkill(PlayerSkillInfo* skillinfo);
	void OnUseSkillAnswer(int itemnum);
	void OnUseEnergyError(MSG_ERROR* error);
	void OnUseSkillError(MSG_ERROR* error);

private:   
	KitSettings m_settings;

	bool m_awaiting_Ok_shield;
	bool m_awaiting_Ok_energy;
	bool m_awaiting_Ok_skill;		   
	bool m_awaiting_Ok_ammobox;
	bool m_awaiting_Ok_fuel;   

	std::vector<PlayerSkillInfo*> m_playerskills;
	std::chrono::milliseconds m_lastAutoBuffCheck;

	std::chrono::milliseconds m_shieldkit_firstuse_delay;
	std::chrono::milliseconds m_energykit_firstuse_delay;
	std::chrono::milliseconds m_skillpkit_firstuse_delay;

	std::chrono::milliseconds m_shieldkit_reattack_time;
	std::chrono::milliseconds m_energykit_reattack_time;
	std::chrono::milliseconds m_skillpkit_reattack_time;
	std::chrono::milliseconds m_fuelkit_reattack_time;

	std::chrono::milliseconds m_lastUseShieldKitTime;
	std::chrono::milliseconds m_lastUseEnergyKitTime;
	std::chrono::milliseconds m_lastUseSkillKitTime;	   
	std::chrono::milliseconds m_lastUseFuelKitTime;


	std::chrono::milliseconds m_lastSendShieldKitTime;
	std::chrono::milliseconds m_lastSendEnergyKitTime;
	std::chrono::milliseconds m_lastSendSkillKitTime;
	std::chrono::milliseconds m_lastSendFuelKitTime;

	bool m_field_healings_active;
	bool m_target_healings_active;
	bool m_target_heal_prio_myself;
};
