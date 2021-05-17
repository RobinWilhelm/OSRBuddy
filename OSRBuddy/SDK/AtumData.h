// AtumData.h: interface for the CAtumData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMDATA_H__263209E9_D038_4DAB_81BC_C6634AC9921E__INCLUDED_)
#define AFX_ATUMDATA_H__263209E9_D038_4DAB_81BC_C6634AC9921E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"
#include "CharacterInfo.h"
#include "AppEffectData.h"



struct ATTACK_DATA
{
	MSG_FC_BATTLE_ATTACK_OK	AttackData;
	BOOL					bShootingWeapon;		// weapon�� ��� �ִ� �����̸� TRUE
	float					fCheckAutoMaticTimer;	// Automatic timer
	BOOL					bZigZagWeapon;			// ������� ���¿��� ������׷� ������ �ϱ� ���� ����
	FLOAT					fCheckAttackTime;		// �� �߻��ϱ����� üũ �ð�(���̹߻�)
	BYTE					nAttackCount;			// �߻�Ǿ���� �Ѿ˼�(ShotNum*MultiNum)
	BYTE					nMultiNumCount;			// MultiNum
	D3DXVECTOR3				vSidePos;				// ���� �¿���̵� ��ǥ
	D3DXVECTOR3				vSideBackPos;			// ���� �¿���̵� �� ��ǥ(���� ������ ���� ��� ����, A���� WeaponVel�� ���� ������ �ٸ� ��찡 ����)
	float					fExplosionRange;		// 2007-06-12 by dgwoo ���� �ݰ�.
	float					fWarheadSpeed;			// 2007-06-15 by dgwoo ��޹��� ź�� �ӵ�
};

// 2011. 03. 08 by jskim ����3�� ����
struct MULTI_TARGET_DATA
{
	INT			PointIndex;							// �߰��� ���� Ÿ���� ��ȣ
	D3DXMATRIX	TargetMatrix;						// ���� ��Ʈ����
};
// end 2011. 03. 08 by jskim ����3�� ����

class CAtumData : public CAtumNode
{
public:
	CAtumData();
	virtual ~CAtumData();

	D3DXVECTOR3			m_vPos;					// ������ ���� ��ǥ
	D3DXVECTOR3			m_vNextPos;				// ���� �� ��ĳ���� ���� ��ǥ
	D3DXVECTOR3			m_vUp;
	D3DXVECTOR3			m_vVel;
	D3DXVECTOR3			m_vSideVel;				// ������ ����
	D3DXVECTOR3			m_vLWPos;				// ���� ���� ��ġ
	D3DXVECTOR3			m_vLWBackPos;			// ���� ���� ����ǥ(A��� 1������)
	D3DXVECTOR3			m_vRWPos;				// ������ ���� ��ġ
	D3DXVECTOR3			m_vLWSecondaryPos;		// ���� 2�� ���� ��ġ
	D3DXVECTOR3			m_vRWSecondaryPos;		// ������ 2�� ���� ��ġ

	BOOL				m_bShadowIsRender;		// �׸��ڸ� ������ �Ұ��ΰ�
	D3DXVECTOR3			m_vShadowPos1;			// �׸��� ��ġ (�պκ� ����)
	D3DXVECTOR3			m_vShadowPos2;			// �׸��� ��ġ (�պκ� ������)
	D3DXVECTOR3			m_vShadowPos3;			// �׸��� ��ġ (�޺κ� ������)
	D3DXVECTOR3			m_vShadowPos4;			// �׸��� ��ġ (�޺κ� ����)
	D3DXVECTOR3			m_vMoveVel;
	INT					m_nObjScreenX;			// ��ũ���� X ��ǥ
	INT					m_nObjScreenY;			// ��ũ���� Y ��ǥ
	INT					m_nObjScreenW;			// ��ũ���� W ��ǥ
	FLOAT				m_fDistanceCamera;		// ī�޶�κ����� �Ÿ�
	FLOAT				m_fObjectSize;
	CAtumNode* m_pMoveChat;
	CAtumNode* m_pIDChat;
	DWORD				m_dwState;				// -1:initializing, 0:normal, 1:exploding, 2:close
	FLOAT				m_fCurrentTime;
	D3DXMATRIX			m_mMatrix;
	//	D3DXMATRIX			m_mMatrixEffect;		
	BOOL				m_bCheckBlend;
	BOOL				m_bIsUnderWater;
	BOOL				m_bAniColl;				// �浹 �ִϸ��̼� ����
	FLOAT				m_fAniCollTime;
	BOOL				m_bShielding;			// ���� �ߵ� ���ΰ�
	INT					m_bDegree;				// ������ ����
	BOOL				m_bItemDegree;			// ������ ����

	BYTE				m_bProgressiveRate;
	// 2003.4.23 by dhkwon, ĳ���� ����Ʈ �߰� ����
	CCharacterInfo* m_pCharacterInfo;
	// 2010. 03. 18 by jskim ���ͺ��� ī��
	//void LoadCharacterEffect(char* strFileName);
	void LoadCharacterEffect(char* strFileName, int nMonsterTransformer = 0, float nMonsterTransScale = 0.0f);
	//end 2010. 03. 18 by jskim ���ͺ��� ī��

	// 2010-06-15 by shcho&hslee ��ý��� - 1��, 2�� ������ ��Ʈ���� �Լ� �и�
	//void SetWeaponPosition();
	void SetPrimaryWeaponPosition();
	void SetSecondaryWeaponPosition();
	// 2010-06-15 by shcho&hslee ��ý��� - 1��, 2�� ������ ��Ʈ���� �Լ� �и�

	// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	void SetPetPosition();
	// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����

	// 2011-03-21 by jhAhn ��ũ�ý��� ��ũ ��ġ ����
	void SetMarkPosition();
	//end 2011-03-21 by jhAhn ��ũ�ý��� ��ũ ��ġ ����

	// 2011-07-20 by jhahn	����3�� �ó׸��÷����� Ÿĳ���� �Ⱥ��̱�
	void SetHideData();
	void SetShowData();
	//end 2011-07-20 by jhahn	����3�� �ó׸��÷����� Ÿĳ���� �Ⱥ��̱�

//	CAppEffectData *	m_pWeapon1_1;			// 1-1�� ������ ������(����Ʈ)
	CAppEffectData* m_pWeapon1_2;			// 1-2�� ������ ������(����Ʈ)
//	CAppEffectData *	m_pWeapon2_1;			// 2-1�� ������ ������(����Ʈ)
	CAppEffectData* m_pWeapon2_2;			// 2-2�� ������ ������(����Ʈ)
	CAppEffectData* m_pEngine;				// ������ ������ ������(����Ʈ)
	CAppEffectData* m_pRadar;				// ���̴ٿ� ������ ������(����Ʈ)
//	CAppEffectData *	m_pArmor;				// ������ ������ ������(����Ʈ)
	CAppEffectData* m_pContainer;			// �����̳�(�������_)�� ������ ������(����Ʈ) // 2006-06-28 by ispark, ������ �Ǽ��縮
	CAppEffectData* m_pAccessories;				// �ð� ���� ������(ITEMKIND_ACCESSORY_TIMELIMIT) // 2006-08-18 by ispark, �ð� ���� �Ǽ��縮
	CAppEffectData* m_pWingIn;				// 2006-08-18 by ispark, Ư��

// 2006-01-12 by ispark, ���� ���
	CAppEffectData* m_pWeapon1_1_1;			// 1-1�� ������ ������(����Ʈ)
	CAppEffectData* m_pWeapon1_1_2;			// 1-2�� ������ ������(����Ʈ)
	CAppEffectData* m_pWeapon2_1_1;			// 2-1�� ������ ������(����Ʈ)
	CAppEffectData* m_pWeapon2_1_2;			// 2-2�� ������ ������(����Ʈ)


	// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
	CAppEffectData* m_pRobotAGearWeapon_1;	// �κ� A���� ���� ����Ʈ
	// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)

	CAppEffectData* m_pPartner;				// 2010-06-08 by dgwoo, ��ý��� �߰�. 
	CAppEffectData* m_pPartner1;			// 2010-06-08 by dgwoo, ��ý��� �߰�. 
	CAppEffectData* m_pDummyPartner;		// 2010-06-08 by dgwoo, ��ý��� �߰�.(����) 
	CAppEffectData* m_pDummyPartner1;		// 2010-06-08 by dgwoo, ��ý��� �߰�.(����1) 

	ATTACK_DATA			m_PrimaryAttack;
	ATTACK_DATA			m_SecondaryAttack;

	ATTACK_DATA			m_PetAttack;			// 2010-06-15 by shcho&hslee ��ý��� - �� ����

	// 2003..12.09 
	D3DXMATRIX			m_mWeaponMatrix;					// A-Gear �� ���� ��Ʈ����
	D3DXVECTOR3			m_vWeaponPos;						// A-Gear �� ���� ��ġ(x->m_vSideVel,y->m_vUp,z->m_vVel)
	D3DXVECTOR3			m_vWeaponVel;						// A-Gear �� ���� �չ���
	D3DXVECTOR3			m_vWeaponUp;						// A-Gear �� ���� ������

	D3DXMATRIX			m_pMatWeaponPosition[4];// 2006-01-03 by ispark, ���� ������ ��Ʈ����

	D3DXMATRIX			m_pMatPetPosition[2]; // 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
	D3DXMATRIX			m_pMatMarkPosition; // 2011-03-21 by jhAhn ��ũ�ý��� ��ũ ��ġ ����

	D3DXMATRIX			m_vPetLeftMatrix;					// 2010-06-15 by shcho&hslee ��ý��� - A-Gear ������� left �� Matrix
	D3DXVECTOR3			m_vPetLeftPos;						// 2010-06-15 by shcho&hslee ��ý��� - A-Gear ������� left �� ��ġ
	D3DXVECTOR3			m_vPetLeftVel;						// 2010-06-15 by shcho&hslee ��ý��� - A-Gear ������� left �� ����
	D3DXVECTOR3			m_vPetLeftUp;						// 2010-06-15 by shcho&hslee ��ý��� - A-Gear ������� left �� �� ����

	D3DXMATRIX			m_vPetRightMatrix;					// 2010-06-15 by shcho&hslee ��ý��� - A-Gear ������� Right �� Matrix
	D3DXVECTOR3			m_vPetRightPos;						// 2010-06-15 by shcho&hslee ��ý��� - A-Gear ������� Right �� ��ġ
	D3DXVECTOR3			m_vPetRightVel;						// 2010-06-15 by shcho&hslee ��ý��� - A-Gear ������� Right �� ����
	D3DXVECTOR3			m_vPetRightUp;						// 2010-06-15 by shcho&hslee ��ý��� - A-Gear ������� Right �� �� ����
	// 1�� ������ ������� �����ֱ� ���� ���� ����Ÿ, ���� ������
//	MSG_FC_BATTLE_ATTACK_RESULT_PRIMARY			m_PrimaryAttackData1;		// �߻�� ���õ� ����Ÿ1
//	MSG_FC_BATTLE_ATTACK_ITEM_RESULT_PRIMARY	m_PrimaryAttackData2;		// �߻�� ���õ� ����Ÿ2

	// ������ ���� ������
//	BOOL										m_bIsItemAttack;			// �����ۿ� �߻��ߴ°�
//	CAtumData *									m_pPrimaryAttackTarget;		// Ÿ���� ������
//	FLOAT										m_fPrimaryAttackTime;		// 1���� �� �߻��ϱ����� üũ �ð�(���̹߻�)
};

#endif // !defined(AFX_ATUMDATA_H__263209E9_D038_4DAB_81BC_C6634AC9921E__INCLUDED_)
