#pragma once

#include "WSlowData.h"

class CItemData;
class CCinema;
class CAtumData;
struct ITEM;
struct ATTACK_DATA;
class CPkNormalTimer;

class CWeaponRocketData : public CWSlowData
{
public:
	virtual ~CWeaponRocketData();
	virtual void Tick();
	virtual void NormalTick();
	virtual void SkillTick();

public:
	INT					m_nTargetIndex;
	INT					m_nTargetItemFieldIndex;

	FLOAT				m_fTurnCheckTime;			// �׽�Ʈ : ���� �ð� ������ �������� �ֱ� ���� �׽�Ʈ ����
	BOOL				m_bSendData;				// Change Target �� ���� ��û�� ������ �ߴ���
	BYTE				m_bTraceColorRed;			// ���� ����(R)
	BYTE				m_bTraceColorGreen;			// ���� ����(G)
	BYTE				m_bTraceColorBlue;			// ���� ����(B)
	CCinema* m_pCinema;
	INT					m_nTargetMe;

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