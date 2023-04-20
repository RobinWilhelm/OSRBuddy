#pragma once

#include "Weapon.h"

// 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)
#define BLIND_INTERVAL	100
// end 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)

class CWSlowData : public CWeapon
{
public:
	virtual ~CWSlowData();

public:
	INT					m_nClientIndex;
	INT					m_nItemIndex;
	USHORT				m_nRemainedBulletFuel;		// ���� �Ѿ� ��
	USHORT				m_nWeaponIndex;				// �������� ������ �Ѿ��� ���� ��ȣ

	BOOL				m_bEvasion;					// ȸ��
	float				m_fWarheadSpeed;			// 2007-06-15 by dgwoo �ӵ� �߰�.

	// 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)
	DWORD				m_nBlindSpeedDownTime;

	int					m_nBlindCumulate;
	// end 2010. 03. 18 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� ��ų �߰�)
};