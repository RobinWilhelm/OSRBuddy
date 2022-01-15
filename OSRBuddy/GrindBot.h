#pragma once
#include "BuddyFeatureBase.h" 	  
#include "OSRAPI.h"

#include "MathHelper.h" 
#include "BuddyTimer.h"
#include "AceColouredString.h"

#include <chrono>
#include <map>
#include <vector>
#include <string>	

#define UPDATE_GRINDMOBS_TIME 1000ms
#define NO_TARGET_SIEGE_DISABLE_TIME 1000ms

#define MIN_NEW_TARGET_DELAY_TIME 50ms
#define MAX_NEW_TARGET_DELAY_TIME 300ms

#define ANTI_RAM_CHECK_RADIUS 250



namespace Features
{
	class KitBuffBot;
	class Miscellaneous;
	class InventoryManager;

	struct GrindMonsterInfo
	{
		AceColouredString name;
		std::string clean_name;
		bool shoot = false;
		bool priority = false;
		uint32_t killed = 0;
		bool goldy = false;
		uint32_t count = 0;
		std::string count_text;
	};

	enum class SmoothType
	{
		Distance,
		Time
	};

	enum class TargetMode
	{
		GearDistance = 0,
		CrosshairDistance = 1,
	};

	class GrindBot : public BuddyFeatureBase
	{
	public:
		enum class State
		{
			WAITING,
			SIEGEING,
			OVERHEATED,
		};

		GrindBot(OSRBuddyMain* buddy);
		// Geerbt über BuddyFeatureBase
		virtual void Tick() override;
		virtual void RenderImGui() override;
		virtual std::string GetName() const override;
		virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
		virtual int WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
		virtual FeatureType GetType() const override;
		virtual void OnEnable() override;
		virtual void OnDisable() override;
		virtual void Render(D3D9Renderer* renderer) override;

		void ChangeState(GrindBot::State newState);
		void ChangeTarget(CMonsterData* newTarget);
		void GetNewTarget();
		void Reset();

	private:
		float GetTargetDistance(CAtumData* target);
		bool CanShootAtTarget(CUnitData* target);
		bool IsValidTargetMonster(CMonsterData* m_target);
		CMonsterData* FindNewTarget(float max_distance, bool front_only = false);
		void AimAtTarget(CMonsterData* target);
		void ToggleGrinding();

		void Reset_NewTargetDelayTime();

		void UpdateCheckTime();
		void UpdateGrindingTime();
		void UpdateGrindMobInfo();

		std::map<INT, GrindMonsterInfo>::iterator FindGrindMonsterInfo(int monsterunitkind);

		bool IsMonsterDead(CMonsterData* monster);
		void SmoothDeltaAngle(float& deltaAng);

		bool IsValidPrimaryWeapon(ITEM_BASE* item);
		bool Swap();



	private:
		CMonsterData* m_target;
		GrindBot::State m_current_state;
		KitBuffBot* m_kitbot;
		Miscellaneous* m_miscfeatures;
		InventoryManager* m_invenmanager;

		std::chrono::milliseconds m_grinding_time;
		std::chrono::milliseconds m_grinding_time_total;
		std::chrono::time_point<std::chrono::system_clock> m_grinding_start;
		std::string m_grind_time_string;

		std::chrono::milliseconds m_aimtime_current;
		std::chrono::milliseconds m_aimtime_final;


		uint32_t m_vkc_toggle;	// virtual key code to toggle on/off
		std::string m_vkc_description; 
		bool m_wait_for_hotkey; // next key press is the new toggle hotkey

		MapIndex_t m_grinding_map;
		bool m_awaiting_siege_toggle_ok;
		bool m_on_target;
		bool m_get_new_target;
		bool m_visible_only;
		bool m_shoot_all_goldies;
		bool m_prioritise_closer_mobs;
		bool m_anti_ram;
		bool m_prio_bossmonster;
		bool m_enable_bs_hotswap;
		bool m_select_swapbs;
		bool m_swapped;
		bool m_selected;

		TargetMode m_target_mode;

		bool m_keep_shooting;
		int m_target_delay_min;
		int m_target_delay_max;

		SmoothType m_smoothtype;
		float m_smooth_factor_distance;
		float m_smooth_factor_time;


		BuddyTimer m_update_mobs_timer;
		std::chrono::milliseconds m_no_target_time;
		std::chrono::milliseconds m_shoot_new_target_delay;

		std::map<INT, GrindMonsterInfo> m_mobs;
		uint32_t m_total_mobs_killed;

		UID64_t m_currentBS;
		UID64_t m_nextBS;
	};
}