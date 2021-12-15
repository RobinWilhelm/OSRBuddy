#pragma once
#include "BuddyFeatureBase.h"

#include "SDK/SkillInfo.h"
#include "SDk/AtumDefine.h"
#include "SDK/AtumParam.h"
#include "SDK/AtumProtocol.h"

#include <chrono>
#include <algorithm>
#include <queue>


 
class CSkillInfo;	 

namespace Features
{
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

	struct PlayerSkillInfo
	{
		SkillType type = SkillType::Unknown;
		CSkillInfo* skillinfo = nullptr;
		std::string clean_name;
		bool final = false;
		bool autobuff = false;
		std::chrono::milliseconds last_send = 0s;

		inline bool IsWaiting() {
			return skillinfo->m_dwState == SKILL_STATE_WAITING || skillinfo->m_dwState == SKILL_STATE_PREPARE;
		}
	};


	class KitBuffBot : public BuddyFeatureBase
	{
	public:
		enum class Mode
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
				use_fuel = other.use_fuel;

				field_healings_active = other.field_healings_active;
				field_repair_active = other.field_repair_active;
				target_healings_active = other.target_healings_active;
				target_repair_active = other.target_repair_active;
				target_heal_prio_myself = other.target_heal_prio_myself;

				use_spkit_type_a = other.use_spkit_type_a;
				use_spkit_type_b = other.use_spkit_type_b;
				use_spkit_type_c = other.use_spkit_type_c;

				spkit_type_a_minvalue = other.spkit_type_a_minvalue;
				spkit_type_b_minvalue = other.spkit_type_b_minvalue;
				spkit_type_c_minvalue = other.spkit_type_c_minvalue;
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
			bool use_fuel;

			bool field_healings_active;
			bool field_repair_active;
			bool target_healings_active;
			bool target_repair_active;
			bool target_heal_prio_myself;

			bool use_spkit_type_a;
			bool use_spkit_type_b;
			bool use_spkit_type_c;

			int spkit_type_a_minvalue;
			int spkit_type_b_minvalue;
			int spkit_type_c_minvalue;
		};

	public:
		KitBuffBot(OSRBuddyMain* buddy);

		// Returns true when the kit usage request has been sent to the server, false when not.
		// The reason for false could be that requiered kits are not in inventory or the server has not answered the last request yet
		bool TryUseKit(KitType type, KitCategory category);
		bool KitTimerReady(KitType kittype);

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
		bool IsSkillActive(SkillType skill);

		PlayerSkillInfo* FindPlayerSkill(SkillType skill) const;
		PlayerSkillInfo* FindPlayerSkill(int itemnum) const;
		bool AutoBuffCheckTimerReady();
		bool AutoHealCheckTimerReady();

	protected:
		// Geerbt über IBuddyFeature
		virtual void Tick() override;
		virtual void RenderImGui() override;
		virtual std::string GetName() const override;
		virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
		virtual bool OnWritePacket(unsigned short msgtype, byte* packet) override;
		virtual FeatureType GetType() const override;

	private:
		void TickAutoKit();
		void TickAutoBuff();
		void TickAutoHeals();

		void GrabPlayerSkills();
		void OnUseSkillAnswer(int itemnum);
		void OnUseEnergyError(MSG_ERROR* error);
		void OnUseSkillError(MSG_ERROR* error);

		bool ShouldUseRepairField();	// shield
		bool ShouldUseHealingField();	// energy

		UID32_t GetBestRepairTarget();	// shield
		UID32_t GetBestHealTarget();	// energy


	private:
		KitSettings m_settings;

		bool m_awaiting_server_ok_shield;
		bool m_awaiting_server_ok_energy;
		bool m_awaiting_server_ok_skill;
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

		std::chrono::milliseconds m_mgear_targetheal_last_send;
	};
}