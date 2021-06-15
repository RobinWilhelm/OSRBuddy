#pragma once
#include "BuddyFeatureBase.h"
#include <vector>
#include <string>		  
#include "OSRAPI.h"
#include <chrono>
   
#define CAPSULE_OPEN_REATTACK 500ms

class KitBuffBot; 



struct GrindMonsterInfo
{
	INT monsterunitkind;
	std::string clean_name;
	bool shoot;
	uint32_t killed;
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
	void UpdateCheckTime();
	void UpdateGrindingTime();

	void TickInventoryCleaning();
	bool TryOpenCapsule(ItemNumber capsule);

private:
	CMonsterData* m_target;
	GrindBot::State m_current_state;
	KitBuffBot* m_kitbot;

	std::chrono::milliseconds m_grinding_time;
	std::chrono::milliseconds m_grinding_time_total;
	std::chrono::time_point<std::chrono::system_clock> m_grinding_start;

	bool m_awaiting_siege_toggle_ok;
	bool m_on_target;	 
	bool m_get_new_target;

	std::vector<int, uint32_t> m_killed_mobs;	  	  
	std::chrono::milliseconds m_inv_action_check_time;

	bool m_clean_inventory;
	bool m_only_clean_while_stopped;
	bool m_only_clean_while_overheat;

	bool m_open_watermelongift;
	bool m_open_spicapsule;
	bool m_open_fantasyglobemineralcapsule;
	bool m_open_mineralcapsule;
	bool m_open_wpcapsule;
};