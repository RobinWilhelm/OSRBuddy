// EnemyData.h: interface for the CEnemyData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYDATA_H__F5A0B417_10F7_42CF_AF08_22552909F46E__INCLUDED_)
#define AFX_ENEMYDATA_H__F5A0B417_10F7_42CF_AF08_22552909F46E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UnitData.h"
#include "AtumProtocol.h"

class CUnitRender;
class CCharacterRender;						// 2005-07-21 by ispark
class CShuttleRender;
class CPkNormalTimer;
class CChatMoveData;

/*
struct MEX_OTHER_CHARACTER_INFO
{
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - �Ʒ��� ���� �ʵ� ������ �����Ѵ�.
	BodyCond_t		BodyCondition;
	INT				Propensity;			// 2005-12-27 by cmkwon, ����(��,��)�� �ƴϰ� ������ �����
	UID32_t			CharacterUniqueNumber;
	// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ������� �����Ƿ� ����
	//	INT				RacingPoint;		// Racing ��� Point
	UID32_t			GuildUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;		// ĳ���Ͱ� ���� �� �� ä��, 2006-01-18 by cmkwon, �߰���
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	AVECTOR3		UpVector;
	ClientIndex_t	ClientIndex;
	USHORT			Race;
	USHORT			UnitKind;
	USHORT			PKWinPoint;			// PK �¸� ��ġ
	USHORT			PKLossPoint;		// PK �й� ��ġ
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	char			szCharacterMent[SIZE_STRING_32];
	BYTE			Gender;				// false(0) : ��, true(1) : ��
	BYTE			PilotFace;			// ȭ�鿡 ��Ÿ���� �ι� ĳ����
	BYTE			CharacterMode0;		// 2005-07-13 by cmkwon, ���� ĳ���� ���� �÷���
	BYTE			InfluenceType;		// ���� Ÿ��, 2005-06-23 by cmkwon
	BYTE			Level1;				//
	BYTE			CityWarTeamType;	// 
	BYTE			Status;				// �ź�
};


typedef struct
{
	INT		RI_Prow;			// POS_PROW�� ItemNum, ���� (����Ʈ�迭 + ���迭 or ���̴�)
	INT		RI_ProwIn;			// 2005-03-17 by cmkwon (CPU ��ǻ��)
	INT		RI_ProwOut;			// POS_PROWOUT�� ItemNum, ������ �ٱ���, ���� (1������ - ���迭 or ĳ��迭)
	INT		RI_WingIn;			// 2005-03-17 by cmkwon (��ũ)
	INT		RI_WingOut;			// POS_WINGOUT�� ItemNum, ������ �ٱ���, ����(2������ - ���ϰ迭 or �̻��ϰ迭)
	INT		RI_Center;			// POS_CENTER�� ItemNum, �߾� (���迭 - �Ƹ�) ���
// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - �ʿ� ����
//	INT		RI_ArmorColorCode;	// 2005-12-08 by cmkwon, �Ƹ��� ����Į��
	INT		RI_Rear;			// POS_REAR�� ItemNum, �Ĺ� (�����迭)

	// 2010-06-15 by shcho&hslee ��ý���
	//INT		RI_Attachment;		// POS_ATTACHMENT�� ItemNum, ������ (�����̳ʰ迭<������ũ/��Ÿ�迭> or �������� ����)
	INT		RI_AccessoryUnLimited;

	// 2010-06-15 by shcho&hslee ��ý���
	//INT		RI_Pet;				// 2005-03-17 by cmkwon (�ð����� �Ǽ��縮)
	INT		RI_AccessoryTimeLimit;

	BOOL	RI_Invisible;		// 2006-11-27 by dhjin, ĳ���� ������ �ʴ� �÷���
	INT		RI_Prow_ShapeItemNum;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ���̴� ShapeItemNum
	INT		RI_WingIn_ShapeItemNum;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - ��ũ ShapeItemNum
	INT		RI_Center_ShapeItemNum;			// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - �Ƹ� ShapeItemNum
	INT		RI_ProwOut_ShapeItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 1������ ShapeItemNum
	INT		RI_WingOut_ShapeItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 2������ ShapeItemNum
	INT		RI_ProwOut_EffectItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 1������ ź�� EffectItemNum
	INT		RI_WingOut_EffectItemNum;		// 2009-08-26 by cmkwon, �׷��� ���ҽ� ���� �ý��� ���� - 2������ ź�� EffectItemNum
	INT		RI_MonsterUnitKind_ForTransformer;	// 2010-03-18 by cmkwon, ���ͺ��� ���� - ���Ż����� ���� ����ī��

	INT		RI_Pet;							// 2010-06-15 by shcho&hslee ��ý��� - �� ������.
	INT		RI_Pet_ShapeItemNum;			// 2010-06-15 by shcho&hslee ��ý��� - ShapeItemNum. 	 

	
} CHARACTER_RENDER_INFO;
*/

typedef struct _ENEMYINFO
{
	MEX_OTHER_CHARACTER_INFO CharacterInfo;
	CHARACTER_RENDER_INFO	 CharacterRenderInfo;			// ������������ ����
 	MAP_CHANNEL_INDEX		 MapChannelIndex;
	SHORT			HP;
	float			CurrentHP;
	SHORT			DP;
	float			CurrentDP;
	SHORT			SP;
	SHORT			CurrentSP;
	SHORT			EP;
	SHORT			CurrentEP;
	BYTE			Level;

	//	UINT			CharacterUniqueNumber;
	//	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	//	ClientIndex_t	ClientIndex;					// 
	//	BYTE			PilotFace;
	//	USHORT			UnitKind;
	//	USHORT			Race;
	//	UINT			GuildUniqueNumber;
	//	BodyCond_t		BodyCondition;
}ENEMYINFO;

class CEnemyData : public CUnitData
{
public:
	virtual ~CEnemyData();
	virtual void Tick();
	virtual void Render();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	//void ChangeItemPoint(BYTE bPos,INT nItemNum, INT nColorNum);
	void	ChangeItemPoint(BYTE bPos, INT nItemNum, INT nShapeItemNum, INT nEffectItemNum);

	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


	void MoveSkill();
	//	void UseSkillFromServer(INT nSkillItemNumber, ClientIndex_t nTargetIndex);
	float RollingSystem(float fElapsedTime);

	// remodeling, 2004-03-21 by dhkwon
	void ChangeBodyConditionFromServer(BodyCond_t hyBodyCondition);
	virtual USHORT GetShiftWeaponBodyconditionByUnitKind();

	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
	//virtual void CheckAttack(ATTACK_DATA &attackData, BOOL bReset, ITEM* pWeaponITEM=NULL);
	virtual void CheckAttack(ATTACK_DATA& attackData, BOOL bReset, ITEM* pWeaponITEM = NULL, ITEM* pEffectItem = NULL);
	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	virtual void CreateSecondaryShieldDamage(D3DXVECTOR3 vCollPos);

	// 2005-07-28 by ispark
	void SetPilotNumber(BYTE PilotFace);

	void DeleteChatMoveShop();

	// 2006-11-27 by ispark, ��ų ���� ����
	void UseSkillFromServer(INT ItemNum);
	void CancelUsingSkill(INT ItemNum);

	void SetAlphaData();
	void InitAlphaData();

	// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��
	virtual BOOL	IsCheckObjectShow();
	virtual BOOL	IsCheckObjectColl();

	// 2007-06-13 by bhsohn �޸� ���� �����
	ENEMYINFO		GetEnemyInfo();

	// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
	void RefreshMarkItem();

protected:
	void CheckCharacterPos();								// 2005-08-04 by ispark
	void TickCharacter(float fElapsedTime);
	void TickUnit(float fElapsedTime);
	void CheckShadowPos();
	void LoadEnemyCharacterInfo(char* strFileName);

	// 2007-05-17 by bhsohn ������Ʈ �ڿ� �������� �� ���� ó �˻� ó��
	void TickCheckObjectTOEnemy();
	void UpdateCheckObjectTOEnemy(BOOL bTarget);
	void InitCheckInfo();

	// 2008-07-14 by bhsohn ĳ���� ���� ���� ����
	BOOL IsSameInfluence(BYTE	myInfluenceType, BYTE	emenyInfluenceType);

public:
	CAtumData* m_pTarget;
	///////////////// ���� �׽�Ʈ�� ���� ����Ʈ  /////////////////////
	BOOL					m_bUseMoveSkill;
	BYTE					m_bSkillMoveType;
	FLOAT					m_fSkillMoveTime;

	FLOAT					m_fTargetCheckTime;
	//	DWORD				m_dwType;				// ĳ����, ���� ����

	D3DXVECTOR3				m_vNextUp;
	D3DXVECTOR3				m_vOriNextUp;
	D3DXVECTOR3				m_vNextVel;
	D3DXVECTOR3				m_vOriNextVel;
	D3DXVECTOR3				m_vExpectPos;		// NextPos�� �ι��� ����.

	D3DXVECTOR3				m_vMovepos;			// ������ ����.
	D3DXVECTOR3				m_vMoveUp;

	FLOAT					m_fLifeTime;
	BOOL					m_bCheckColl;
	BOOL					m_bIsRender;
	BOOL					m_bIsInit;

	BOOL					m_bRequestMove;
	POINT					m_ptCurRegion;					// ���� �� ������
	POINT					m_ptOldRegion;					// ���� ���� �� ������
	///////////////// Party  /////////////////////
	PartyID_t				m_nPartyID;

	// PK ����� FALSE ����
	BOOL					m_bZBuffer;						// �ν��Ϳ� �����ϱ� ����
	CUnitRender* m_pRender;						// Enemy �� Rendering �� ó��

	ENEMYINFO				m_infoCharacter;
	BOOL					m_bIsItemPointSet;				// ���������� ������ �����ߴ°�

	CAppEffectData* m_pEffectTarget;
	float					m_fCheckItemInfoTime;

	float					m_fRollStartTime;				// �Ѹ��� ������ �ð�
	float					m_fRollAngle;					// �Ѹ� ����
	BOOL					m_bRollStart;					// �Ѹ� ������
	BOOL					m_bRollLeft;					// �Ѹ� LEFT
	BOOL					m_bRollRight;					// �Ѹ� RIGHT
	D3DXVECTOR3				m_vRollStart;					// �Ѹ� ������ ��ġ

	BOOL					m_bRender;						// 2011-07-18 by jhahn ����3�� �ó׸� Ÿĳ���� �Ⱥ��̱�

	//////////////////////////////////////////////////////////////////////////
	// 2005-07-26 by ispark
	// �� ĳ����
	BOOL					m_bEnemyCharacter;				// �� ĳ���� // 2005-07-21 by ispark
	CCharacterInfo* m_pEnemyCharacterInfo;			// �� ĳ���� ����
	CCharacterRender* m_pCharacterRender;				// ĳ���� Rendering
	BodyCond_t				m_hyBodyCondition;

	// ���� ��ǥ : �ٵ�������� ���� ���� �Ѵ�.
	D3DXVECTOR3				m_vOldPos;						// �� ĳ���� ���� ��ǥ

	// 2005-11-03 by ispark
	///////////////// PK /////////////////////
	CPkNormalTimer* m_pPkNormalTimer;				// PK Ÿ��


	BOOL					m_bSetPosition;

	//////////////////////////////////////////////////////////////////////////
	// ���� ������
	CChatMoveData* m_pMoveChatShop;
	BYTE					m_byBazaarType;
	char					m_szBazaarName[SIZE_MAX_BAZAAR_FULL_NAME];

#ifdef _DEBUG
	int						m_nDebugMoveCount;
	float					m_fCheckMoveTime;
#endif

};

#endif // !defined(AFX_ENEMYDATA_H__F5A0B417_10F7_42CF_AF08_22552909F46E__INCLUDED_)


