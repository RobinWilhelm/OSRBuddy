// UnitData.h: interface for the CUnitData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNITDATA_H__2D386C99_DEB3_45E7_A7B5_A88B6CB2666D__INCLUDED_)
#define AFX_UNITDATA_H__2D386C99_DEB3_45E7_A7B5_A88B6CB2666D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumData.h"




// 2007-04-02 by bhsohn Move패킷으로 적기 상태 체크
#define	UNIT_STATE_INVISIBLE	0
#define	UNIT_STATE_CHARINGSHOT	1
#define	UNIT_STATE_HYPERSHOT	2
#define	UNIT_STATE_MAX			3

#define	BGEAR_STATE_CHARINGSHOT		7800060		// 차징샷 
#define	AGEAR_STATE_HYPERSHOT		7823060		// 하이퍼샷 

// 2007-05-17 by bhsohn 오브젝트 뒤에 숨었을시 에 대한 처 검사 처리
#define	CHECK_OBJECT_TIME		1.0f

///////////////////////////////////////////////////////////////////////////////
/// \class		CUnitData
///
/// \brief		CShuttleChild, CEnemyData, CMonsterData의 부모로서, 공통부분 처리
/// \author		dhkwon
/// \version	
/// \date		2004-03-20 ~ 2004-03-20
/// \warning	
///////////////////////////////////////////////////////////////////////////////
class CSkillEffect;
class CItemData;
class CPetManager;		// 2010-06-15 by shcho&hslee 펫시스템 - 클래스 추가
class CUnitData : public CAtumData
{
	friend class CAtumApplication;	// 차후에 지울 것.
	friend class CUnitRender;		// m_pVBShadow 만 쓸것
	friend class CCharacterRender;	// 2005-07-13 by ispark
	friend class CMonsterRender;	// m_pVBShadow 만 쓸것
public:
	CUnitData();
	virtual ~CUnitData();
public:

	// 무기
	virtual void CreateSecondaryShieldDamage(D3DXVECTOR3 vCollPos) {};	 		

	// 2009. 08. 27 by ckPark 그래픽 리소스 변경 시스템 구현
	//virtual void CheckAttack(ATTACK_DATA &attackData, BOOL bReset, ITEM* pWeaponITEM);
	virtual void CheckAttack(ATTACK_DATA& attackData, BOOL bReset, ITEM* pWeaponITEM = NULL, ITEM* pEffectItem = NULL);
	// end 2009. 08. 27 by ckPark 그래픽 리소스 변경 시스템 구현
	

	// 2007-05-17 by bhsohn 오브젝트 뒤에 숨었을시 에 대한 처 검사 처리
	virtual BOOL	IsCheckObjectShow();
	virtual BOOL	IsCheckObjectColl();
	// 2010. 03. 18 by jskim 몬스터변신 카드  

protected:		 	
	// 무기
	virtual USHORT GetShiftWeaponBodyconditionByUnitKind();

	// end 2009. 07. 07 by ckPark 로봇기어 요청사항(롤링, 선택화면, 무기, A기어포대)

public:
	CParamFactor			m_paramFactor;			// ParamFactor( Enemy인 경우 1형의 샷넘,리어택타임만 관리)
	LPDIRECT3DVERTEXBUFFER9 m_pVBShadow;			// 그림자 버퍼
	char		m_pad1[16];
	char		m_pad2[16];
#ifndef _DEBUG
	char m_padVector[4];
#endif // !_DEBUG


	//////////////////////////////////////////////////////////////////////////
	// 스킬
	vector<CItemData*>		m_pChaffData;			// 2006-12-04 by ispark
	CSkillEffect* m_pSkillEffect;
	int						m_nAlphaValue;			// 알파값
	BYTE					m_bySkillStateFlag;		// 스킬 상태 (위장, 인비지블...)
	ClientIndex_t			m_nTargetIndex;					// Enemy의 타겟 인덱스

	// 2009. 11. 23 by jskim 리소스 로딩 구조 변경
	int						m_LoadingPriority;
	//end 2009. 11. 23 by jskim 리소스 로딩 구조 변경
							  	
	

protected:
	int						m_nUnitNum;				// ex> 12030100 ( 12 : degree, 03 : amor, 01 : unitKind )
	int						m_nPilotNum;			// 2005-07-13 by ispark	파일롯트 넘버
	BOOL					m_bCharacter;			// 2005-07-13 by ispark (Unit : FALSE, Character : TRUE)
	DWORD					m_dwPkState;
	BOOL					m_bPkAttack;			// 2005-11-03 by ispark PK 공격 가능한가, m_dwPkState가 Normal이어도 이것이 TRUE이면 락온 된 상태

	// 2007-04-02 by bhsohn Move패킷으로 적기 상태 체크
	BYTE					m_byUnitState;
	FLOAT					m_fUnitStateChgCap[UNIT_STATE_MAX];		// 유닛 상태가 변경되어있었던 시간 

	// 2007-05-17 by bhsohn 오브젝트 뒤에 숨었을시 에 대한 처 검사 처리
	BOOL					m_bCheckObjectEnemyShow;		// 오브젝트 뒤에 숨었을시 에 대한 처 검사 처리
	BOOL					m_bCheckObject;					// 오브젝트 체크
	float					n_fCheckObjectTime;
	// 2010. 03. 18 by jskim 몬스터변신 카드
	int						m_MonsterTransformer;
	D3DXVECTOR3				m_MonsterTransPrimarySidePos;
	D3DXVECTOR3				m_MonsterTransSecondarySidePos;
	float					m_MonsterTransScale;
	//end 2010. 03. 18 by jskim 몬스터변신 카드
							   	
	CPetManager* m_pPetManager;
};

#endif // !defined(AFX_UNITDATA_H__2D386C99_DEB3_45E7_A7B5_A88B6CB2666D__INCLUDED_)
