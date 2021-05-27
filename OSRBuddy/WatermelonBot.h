#pragma once
#include "BuddyFeatureBase.h"
#include <vector>
#include <string>		  
#include "OSRAPI.h"
#include <chrono>



class KitBuffBot;

class WatermelonBot : public BuddyFeatureBase
{
public:
	enum class State
	{
		WAITING,
		SIEGEING,
		OVERHEATED,	
	};

	WatermelonBot(OSRBuddyMain* buddy);
	// Geerbt über BuddyFeatureBase
	virtual void Tick() override;
	virtual void RenderImGui() override;
	virtual const char* GetName() const override;
	virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
	virtual int WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;	
	virtual FeatureType GetType() const override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;

	void ChangeState(WatermelonBot::State newState);
								
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

private:
	CMonsterData* m_target;
	WatermelonBot::State m_current_state;
	KitBuffBot* m_kitbot;

	std::chrono::milliseconds m_grinding_time;
	std::chrono::milliseconds m_grinding_time_total;
	std::chrono::time_point<std::chrono::system_clock> m_grinding_start;

	bool m_awaiting_siege_toggle_ok;
	bool m_on_target;	 
	bool m_get_new_target;
	bool m_auto_clean_inventory;

	std::chrono::milliseconds m_inv_action_check_time;

	uint32_t m_killed_watermelon_tanks;
	uint32_t m_killed_watermelon_z;
	uint32_t m_killed_easter_egg;
};