#pragma once

#include "AtumParam.h"
#include "AtumNode.h"
#include "d3dx9.h"


#define		WEAPON_FLYTYPE_STRAIGHT1X	0	// �������� ���� ����
#define		WEAPON_FLYTYPE_STRAIGHT2X	1	// �������� ����(2��) ����
#define		WEAPON_FLYTYPE_DOWN			2	// �Ʒ��� �ϰ� ����
#define		WEAPON_FLYTYPE_SIN1X		3	// �ϰ��Ͽ� Ÿ������ ���ư� - Sin �
#define		WEAPON_FLYTYPE_SIN2X		4	// �ϰ��Ͽ��ٰ� ����Ͽ� Ÿ������ ���ư� - Sin �
#define		WEAPON_FLYTYPE_DOWNSTRAIGHT	5	// ������(0.5f) �ϰ��ϴٰ� �������� Ÿ������ ����
#define		WEAPON_FLYTYPE_DOWNGUIDE	6	// Ÿ���� �ְ� Ÿ���� �̻��Ϻ��� ��ǥ�� ���������� ���ݿ� �������� ���� �°� �ȴ�.
#define		WEAPON_FLYTYPE_GUIDEBASIC	7	// �⺻ ���� �̻���-Ÿ������ �����Ǹ鼭 �ٰ�����. �־����� �ӵ� ����
#define		WEAPON_FLYTYPE_GUIDETWIST	8	// ���� �̻��� - ����������� ����
#define		WEAPON_FLYTYPE_GUIDEBACK	9	// ���� �̻��� - �ĸ����� �����ϴٰ� ����Ͽ� ������
#define		WEAPON_FLYTYPE_DOWNX		10	// X-���·� �������� �߻�
#define		WEAPON_FLYTYPE_DOWNLR		11	// �¿�� - ���·� �������� �߻�
//#define		WEAPON_FLYTYPE_GUIDEBACK	12	

// 2005-01-19 by jschoi - Ÿ�� Ÿ�� ����
#define TARGET_TYPE_NONE		0
#define TARGET_TYPE_ENEMY		1
#define TARGET_TYPE_MONSTER		2

class CAtumData;
class CCharacterInfo;
class CWeapon : public CAtumNode
{
public:
	CWeapon();
	virtual ~CWeapon();
	void MoveWeapon(BYTE bType);
	CAtumData* m_pAttacker;				// ������ ������(Parent)
	CAtumData* m_pTarget;					// Ÿ��
	D3DXVECTOR3			m_vPos;						// Position
	D3DXVECTOR3			m_vEffectPos;				// SkillEffectPosition
	D3DXVECTOR3			m_vOldPos;					// ���� Position
	D3DXVECTOR3			m_vOriPos;					// ��� ��ǥ�� ���ر� ���� ������ǥ Position-�Ϲ������� m_vPos �� m_vOriPos�� ���� ��ǥ�̴�
	D3DXVECTOR3			m_vVel;						// ����
	D3DXVECTOR3			m_vUp;						// Position
	D3DXMATRIX			m_mMatrix;					// Matrix
	//	D3DXMATRIX			m_mFireMatrix;				// Fire-Matrix
	D3DXVECTOR3			m_vTargetPos;				// Target Position
	D3DXVECTOR3			m_vStartPos;				// �߻� ������
	D3DXVECTOR3			m_vFirePos;
	DWORD				m_dwWeaponState;			// Weapon�� ���� : 0:normal, 1:exploding
	FLOAT				m_fWeaponLifeTime;			// �Ѿ� Ÿ��
	FLOAT				m_fWeaponLifeCheckTime;		// �Ѿ� üũ Ÿ��
	FLOAT				m_fWeaponSpeed;				// �Ѿ� ���� �ӵ�
	FLOAT				m_fTargetDistance;			// ���� ���õ� Ÿ�� ��ġ���� �Ÿ�(�浹 üũ�� ���ؼ� �̸� ���س��´�)
	BOOL				m_bSetTarget;				// Target �缳�� ����
	//	CAtumNode	*		m_pTraceList1;				// ���� 1
	//	CAtumNode	*		m_pTraceList2;				// ���� 2
	BYTE				m_bWeaponFlyType;			// ����Ÿ��
	ITEM* m_pItemData;				// ������ ������ ���� ������

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	ClientIndex_t		m_nDelegateClientIdx;		// ���� 2�� ���� ���ӵ� Ŭ���̾�Ʈ �ε���
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���


public:
	BodyCond_t			m_bodyCondition;
	CCharacterInfo* m_pCharacterInfo;
	int					m_nSkillNum;				// ������ ���� Ÿ���� ����
};
