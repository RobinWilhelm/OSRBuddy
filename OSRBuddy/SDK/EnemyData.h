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
	// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 아래와 같이 필드 순서를 정렬한다.
	BodyCond_t		BodyCondition;
	INT				Propensity;			// 2005-12-27 by cmkwon, 성향(선,악)이 아니고 명성으로 사용중
	UID32_t			CharacterUniqueNumber;
	// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 사용하지 않으므로 삭제
	//	INT				RacingPoint;		// Racing 결과 Point
	UID32_t			GuildUniqueNumber;
	MAP_CHANNEL_INDEX	MapChannelIndex;		// 캐릭터가 속한 맵 및 채널, 2006-01-18 by cmkwon, 추가함
	AVECTOR3		PositionVector;
	AVECTOR3		TargetVector;
	AVECTOR3		UpVector;
	ClientIndex_t	ClientIndex;
	USHORT			Race;
	USHORT			UnitKind;
	USHORT			PKWinPoint;			// PK 승리 수치
	USHORT			PKLossPoint;		// PK 패배 수치
	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	char			szCharacterMent[SIZE_STRING_32];
	BYTE			Gender;				// false(0) : 여, true(1) : 남
	BYTE			PilotFace;			// 화면에 나타나는 인물 캐릭터
	BYTE			CharacterMode0;		// 2005-07-13 by cmkwon, 현재 캐릭터 상태 플래그
	BYTE			InfluenceType;		// 세력 타입, 2005-06-23 by cmkwon
	BYTE			Level1;				//
	BYTE			CityWarTeamType;	// 
	BYTE			Status;				// 신분
};


typedef struct
{
	INT		RI_Prow;			// POS_PROW의 ItemNum, 선두 (라이트계열 + 방어계열 or 레이다)
	INT		RI_ProwIn;			// 2005-03-17 by cmkwon (CPU 컴퓨터)
	INT		RI_ProwOut;			// POS_PROWOUT의 ItemNum, 선두의 바깥쪽, 장전 (1형무기 - 빔계열 or 캐논계열)
	INT		RI_WingIn;			// 2005-03-17 by cmkwon (마크)
	INT		RI_WingOut;			// POS_WINGOUT의 ItemNum, 날개의 바깥쪽, 장전(2형무기 - 로켓계열 or 미사일계열)
	INT		RI_Center;			// POS_CENTER의 ItemNum, 중앙 (방어계열 - 아머) 고려
// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 필요 없음
//	INT		RI_ArmorColorCode;	// 2005-12-08 by cmkwon, 아머의 색상칼라
	INT		RI_Rear;			// POS_REAR의 ItemNum, 후미 (엔진계열)

	// 2010-06-15 by shcho&hslee 펫시스템
	//INT		RI_Attachment;		// POS_ATTACHMENT의 ItemNum, 부착물 (컨테이너계열<연료탱크/기타계열> or 지도자의 광휘)
	INT		RI_AccessoryUnLimited;

	// 2010-06-15 by shcho&hslee 펫시스템
	//INT		RI_Pet;				// 2005-03-17 by cmkwon (시간제한 악세사리)
	INT		RI_AccessoryTimeLimit;

	BOOL	RI_Invisible;		// 2006-11-27 by dhjin, 캐릭터 보이지 않는 플래그
	INT		RI_Prow_ShapeItemNum;			// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 레이더 ShapeItemNum
	INT		RI_WingIn_ShapeItemNum;			// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 마크 ShapeItemNum
	INT		RI_Center_ShapeItemNum;			// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 아머 ShapeItemNum
	INT		RI_ProwOut_ShapeItemNum;		// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 1형무기 ShapeItemNum
	INT		RI_WingOut_ShapeItemNum;		// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 2형무기 ShapeItemNum
	INT		RI_ProwOut_EffectItemNum;		// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 1형무기 탄두 EffectItemNum
	INT		RI_WingOut_EffectItemNum;		// 2009-08-26 by cmkwon, 그래픽 리소스 변경 시스템 구현 - 2형무기 탄두 EffectItemNum
	INT		RI_MonsterUnitKind_ForTransformer;	// 2010-03-18 by cmkwon, 몬스터변신 구현 - 변신상태의 몬스터 변신카드

	INT		RI_Pet;							// 2010-06-15 by shcho&hslee 펫시스템 - 펫 아이템.
	INT		RI_Pet_ShapeItemNum;			// 2010-06-15 by shcho&hslee 펫시스템 - ShapeItemNum. 	 

	
} CHARACTER_RENDER_INFO;
*/

typedef struct _ENEMYINFO
{
	MEX_OTHER_CHARACTER_INFO CharacterInfo;
	CHARACTER_RENDER_INFO	 CharacterRenderInfo;			// 장착아이템의 정보
 	MAP_CHANNEL_INDEX		 MapChannelIndex;
	
	char dunno0[40];
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
	// 2009. 08. 27 by ckPark 그래픽 리소스 변경 시스템 구현

	//void ChangeItemPoint(BYTE bPos,INT nItemNum, INT nColorNum);
	void	ChangeItemPoint(BYTE bPos, INT nItemNum, INT nShapeItemNum, INT nEffectItemNum);

	// end 2009. 08. 27 by ckPark 그래픽 리소스 변경 시스템 구현


	void MoveSkill();
	//	void UseSkillFromServer(INT nSkillItemNumber, ClientIndex_t nTargetIndex);
	float RollingSystem(float fElapsedTime);

	// remodeling, 2004-03-21 by dhkwon
	void ChangeBodyConditionFromServer(BodyCond_t hyBodyCondition);
	virtual USHORT GetShiftWeaponBodyconditionByUnitKind();

	// 2009. 08. 27 by ckPark 그래픽 리소스 변경 시스템 구현
	//virtual void CheckAttack(ATTACK_DATA &attackData, BOOL bReset, ITEM* pWeaponITEM=NULL);
	virtual void CheckAttack(ATTACK_DATA& attackData, BOOL bReset, ITEM* pWeaponITEM = NULL, ITEM* pEffectItem = NULL);
	// end 2009. 08. 27 by ckPark 그래픽 리소스 변경 시스템 구현

	virtual void CreateSecondaryShieldDamage(D3DXVECTOR3 vCollPos);

	// 2005-07-28 by ispark
	void SetPilotNumber(BYTE PilotFace);

	void DeleteChatMoveShop();

	// 2006-11-27 by ispark, 스킬 정보 셋팅
	void UseSkillFromServer(INT ItemNum);
	void CancelUsingSkill(INT ItemNum);

	void SetAlphaData();
	void InitAlphaData();

	// 2007-05-17 by bhsohn 오브젝트 뒤에 숨었을시 에 대한 처 검사 처리
	virtual BOOL	IsCheckObjectShow();
	virtual BOOL	IsCheckObjectColl();

	// 2007-06-13 by bhsohn 메모리 버그 디버깅
	ENEMYINFO		GetEnemyInfo();

	// 2008-08-19 by bhsohn 세력 마크 시스템 추가
	void RefreshMarkItem();

protected:
	void CheckCharacterPos();								// 2005-08-04 by ispark
	void TickCharacter(float fElapsedTime);
	void TickUnit(float fElapsedTime);
	void CheckShadowPos();
	void LoadEnemyCharacterInfo(char* strFileName);

	// 2007-05-17 by bhsohn 오브젝트 뒤에 숨었을시 에 대한 처 검사 처리
	void TickCheckObjectTOEnemy();
	void UpdateCheckObjectTOEnemy(BOOL bTarget);
	void InitCheckInfo();

	// 2008-07-14 by bhsohn 캐릭터 상태 버그 수정
	BOOL IsSameInfluence(BYTE	myInfluenceType, BYTE	emenyInfluenceType);

public:
	CAtumData* m_pTarget;
	///////////////// 궤적 테스트를 위한 리스트  /////////////////////
	BOOL					m_bUseMoveSkill;
	BYTE					m_bSkillMoveType;
	FLOAT					m_fSkillMoveTime;

	FLOAT					m_fTargetCheckTime;
	//	DWORD				m_dwType;				// 캐릭터, 몬스터 종류

	D3DXVECTOR3				m_vNextUp;
	D3DXVECTOR3				m_vOriNextUp;
	D3DXVECTOR3				m_vNextVel;
	D3DXVECTOR3				m_vOriNextVel;
	D3DXVECTOR3				m_vExpectPos;		// NextPos로 두배의 벡터.

	D3DXVECTOR3				m_vMovepos;			// 가야할 벡터.
	D3DXVECTOR3				m_vMoveUp;

	FLOAT					m_fLifeTime;
	BOOL					m_bCheckColl;
	BOOL					m_bIsRender;
	BOOL					m_bIsInit;

	BOOL					m_bRequestMove;
	POINT					m_ptCurRegion;					// 속한 블럭 포지션
	POINT					m_ptOldRegion;					// 이전 속한 블럭 포지션
	///////////////// Party  /////////////////////
	PartyID_t				m_nPartyID;

	// PK 종료시 FALSE 세팅
	BOOL					m_bZBuffer;						// 부스터에 적용하기 위해
	CUnitRender* m_pRender;						// Enemy 의 Rendering 을 처리

	ENEMYINFO				m_infoCharacter;
	BOOL					m_bIsItemPointSet;				// 장착아이템 정보를 셋팅했는가

	CAppEffectData* m_pEffectTarget;
	float					m_fCheckItemInfoTime;

	float					m_fRollStartTime;				// 롤링이 시작한 시간
	float					m_fRollAngle;					// 롤링 각도
	BOOL					m_bRollStart;					// 롤링 시작함
	BOOL					m_bRollLeft;					// 롤링 LEFT
	BOOL					m_bRollRight;					// 롤링 RIGHT
	D3DXVECTOR3				m_vRollStart;					// 롤링 시작한 위치

	BOOL					m_bRender;						// 2011-07-18 by jhahn 인피3차 시네마 타캐릭터 안보이기

	//////////////////////////////////////////////////////////////////////////
	// 2005-07-26 by ispark
	// 적 캐릭터
	BOOL					m_bEnemyCharacter;				// 적 캐릭터 // 2005-07-21 by ispark
	CCharacterInfo* m_pEnemyCharacterInfo;			// 적 캐릭터 정보
	CCharacterRender* m_pCharacterRender;				// 캐릭터 Rendering
	BodyCond_t				m_hyBodyCondition;

	// 이전 좌표 : 바디컨디션을 내가 직접 한다.
	D3DXVECTOR3				m_vOldPos;						// 적 캐릭터 이전 좌표

	// 2005-11-03 by ispark
	///////////////// PK /////////////////////
	CPkNormalTimer* m_pPkNormalTimer;				// PK 타임


	BOOL					m_bSetPosition;

	//////////////////////////////////////////////////////////////////////////
	// 개인 상점용
	CChatMoveData* m_pMoveChatShop;
	BYTE					m_byBazaarType;
	char					m_szBazaarName[SIZE_MAX_BAZAAR_FULL_NAME];

#ifdef _DEBUG
	int						m_nDebugMoveCount;
	float					m_fCheckMoveTime;
#endif

};

#endif // !defined(AFX_ENEMYDATA_H__F5A0B417_10F7_42CF_AF08_22552909F46E__INCLUDED_)


