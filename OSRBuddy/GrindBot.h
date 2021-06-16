#pragma once
#include "BuddyFeatureBase.h"
#include <vector>
#include <string>		  
#include "OSRAPI.h"
#include <chrono>
#include <map>
   
#define CAPSULE_OPEN_REATTACK 500ms
#define UPDATE_GRINDMOBS_TIME 500ms
#define NO_TARGET_SIEGE_DISABLE_TIME 1500ms
#define NO_TARGET_STOP_SHOOTING_TIME 600ms

#define MIN_NEW_TARGET_DELAY_TIME 100ms
#define MAX_NEW_TARGET_DELAY_TIME 300ms

class KitBuffBot; 



struct GrindMonsterInfo
{
	std::string clean_name;
	bool shoot;
	bool priority;
	uint32_t killed;
	bool goldy;				
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

	void ChangeState(GrindBot::State newState);
								
private:
	float GetTargetDistance(CAtumData* m_target);
	bool CanShootAtTarget(CUnitData* target);
	bool IsValidTargetMonster(CMonsterData* m_target);
	CMonsterData* FindNewTarget(float max_distance, bool front_only = false);
	void AimAtTarget(CMonsterData* m_target);

	void ToggleGrinding();
	
	bool InventoryActionCheckTimeReady();
	void ResetInventoryActionCheckTime();
	bool ShouldCheck_GrindMobs();
	void Reset_GrindMobsCheckTime();
	void Reset_NewTargetDelayTime();

	void UpdateCheckTime();
	void UpdateGrindingTime();
	void UpdateGrindMobInfo();

	std::map<INT, GrindMonsterInfo>::iterator FindGrindMonsterInfo(int monsterunitkind);

	void TickInventoryCleaning();
	bool TryOpenCapsule(ItemNumber capsule);

	bool IsMonsterDead(CMonsterData* monster);

private:
	CMonsterData* m_target;
	GrindBot::State m_current_state;
	KitBuffBot* m_kitbot;

	std::chrono::milliseconds m_grinding_time;
	std::chrono::milliseconds m_grinding_time_total;
	std::chrono::time_point<std::chrono::system_clock> m_grinding_start;

	MapIndex_t m_grinding_map;
	bool m_awaiting_siege_toggle_ok;
	bool m_on_target;	 
	bool m_get_new_target;
	bool m_front_only;
	bool m_shoot_all_goldies;
	bool m_prioritise_closer_mobs;
	TargetMode m_target_mode;

	bool m_humanized_overshoot;
	int m_humanized_target_delay_min;
	int m_humanized_target_delay_max;

	std::chrono::milliseconds m_inv_action_check_time;
	std::chrono::milliseconds m_update_mob_list_check_time;
	std::chrono::milliseconds m_no_target_time;
	std::chrono::milliseconds m_shoot_new_target_delay;

	std::map<INT, GrindMonsterInfo> m_mobs;
	int m_total_mobs_killed;

	bool m_clean_inventory;
	bool m_only_clean_while_stopped;
	bool m_only_clean_while_overheat;

	bool m_open_watermelongift;
	bool m_open_spicapsule;
	bool m_open_fantasyglobemineralcapsule;
	bool m_open_mineralcapsule;
	bool m_open_wpcapsule;
};