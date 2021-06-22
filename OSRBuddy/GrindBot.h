#pragma once
#include "BuddyFeatureBase.h"
#include <vector>
#include <string>		  
#include "OSRAPI.h"
#include <chrono>
#include <map>
#include "MathHelper.h" 

#define UPDATE_GRINDMOBS_TIME 500ms
#define NO_TARGET_SIEGE_DISABLE_TIME 1500ms
#define NO_TARGET_STOP_SHOOTING_TIME 600ms

#define MIN_NEW_TARGET_DELAY_TIME 50ms
#define MAX_NEW_TARGET_DELAY_TIME 300ms

class KitBuffBot; 
class Miscellaneous;


struct GrindMonsterInfo
{
	std::string clean_name;
	bool shoot;
	bool priority;
	uint32_t killed;
	bool goldy;				
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
	virtual void Render(IDirect3DDevice9* device) override;

	void ChangeState(GrindBot::State newState);
	void ChangeTarget(CMonsterData* newTarget);
	void GetNewTarget();
								
private:
	float GetTargetDistance(CAtumData* m_target);
	bool CanShootAtTarget(CUnitData* target);
	bool IsValidTargetMonster(CMonsterData* m_target);
	CMonsterData* FindNewTarget(float max_distance, bool front_only = false);
	void AimAtTarget(CMonsterData* m_target);
	void ToggleGrinding();
	
	bool ShouldCheck_GrindMobs();
	void Reset_GrindMobsCheckTime();
	void Reset_NewTargetDelayTime();

	void UpdateCheckTime();
	void UpdateGrindingTime();
	void UpdateGrindMobInfo();

	std::map<INT, GrindMonsterInfo>::iterator FindGrindMonsterInfo(int monsterunitkind);

	bool IsMonsterDead(CMonsterData* monster);
	QAngle CalcAngle(const D3DXVECTOR3& source, const D3DXVECTOR3& target);
	void SmoothDeltaAngle(float& deltaAng);

private:
	CMonsterData* m_target;
	GrindBot::State m_current_state;
	KitBuffBot* m_kitbot;
	Miscellaneous* m_miscfeatures;

	std::chrono::milliseconds m_grinding_time;
	std::chrono::milliseconds m_grinding_time_total;
	std::chrono::time_point<std::chrono::system_clock> m_grinding_start;

	std::chrono::milliseconds m_aimtime_current;
	std::chrono::milliseconds m_aimtime_final;


	MapIndex_t m_grinding_map;
	bool m_awaiting_siege_toggle_ok;
	bool m_on_target;	 
	bool m_get_new_target;
	bool m_front_only;
	bool m_shoot_all_goldies;
	bool m_prioritise_closer_mobs;
	bool m_anti_ram;
	TargetMode m_target_mode;

	bool m_humanized_overshoot;
	int m_humanized_target_delay_min;
	int m_humanized_target_delay_max;

	SmoothType m_smoothtype;  
	float m_smooth_factor_distance;
	float m_smooth_factor_time;		

	std::chrono::milliseconds m_update_mob_list_check_time;
	std::chrono::milliseconds m_no_target_time;
	std::chrono::milliseconds m_shoot_new_target_delay;

	std::map<INT, GrindMonsterInfo> m_mobs;
	int m_total_mobs_killed;

};