#pragma once

#include "WSlowData.h"

class CItemData;
class CAtumData;
class CCinema;
struct ITEM;
struct ATTACK_DATA;

class CWeaponMissileData : public CWSlowData
{
public:
	virtual ~CWeaponMissileData();
	virtual void Tick();
	virtual void SkillTick();

public:
	INT					m_nTargetIndex;
	INT					m_nTargetItemFieldIndex;
	// 2005-07-19 by ispark
	INT					m_nTargetMe;
	CCinema* m_pCinema;
	float				m_fFireTime;
	// 2007-06-12 by dgwoo ���� �ݰ�(������ : �̻����� ���ݿ� ���� �̸� ������.
	//								 ������ : ���� ������� ���ݾȿ� ������ �������� �Դ´�.)
	float				m_fExplosionRange;

	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	ITEM* m_pEffectItem;
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	int					m_LoadingPriority;
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	// 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���
	int m_nMultiTargetIndex;
	// end 2011. 03. 08 by jskim ����3�� ���� - �� Ÿ�� �ý���	 
};