// SkillInfo.h: interface for the CSkillInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILLINFO_H__7B90C53A_7DEA_4545_A5DC_CB8A64A154AD__INCLUDED_)
#define AFX_SKILLINFO_H__7B90C53A_7DEA_4545_A5DC_CB8A64A154AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumParam.h"


///////////////////////////////////////////////////////////////////////////////
/// \class		class CSkillInfo : public ITEM_SKILL 
///
/// \brief		CSkill 이 스킬 전체를 관리하는 클래스라면, CSkillInfo는 스킬 하나에 대한 관리를 담당하는 클래스다.
///				즉, CSkillInfo 는 스킬 1개를 말한다.
/// \author		jschoi
/// \version	
/// \date		2004-10-19 ~ 2004-10-19
/// \warning	
///////////////////////////////////////////////////////////////////////////////

class CSkillInfo : public ITEM_SKILL
{
public:
	CSkillInfo(ITEM_SKILL* pItemSkill);
	virtual ~CSkillInfo();

	float	m_fCheckWaitingTime;		// 서버로 보내고 기다리는 시간
	float	m_fCheckWaitingPrepareTime;	// 서버로 보내고 기다리는 시간
	float	m_fCheckReattackTime;		// 재 가동 예비 시간
	float	m_fCheckEnableTime;			// 시간 후 스킬이 해제된다.
	float	m_fCheckPrepareTime;		// 발동 시간
	float	m_fCheckAckWaitingTime;		// 2005-12-05 by ispark, 제한된 시간 체크(시간이 오버를 하면 자동 스킬 취소)
	int		m_dwState;					// 스킬 상태
	BOOL	m_bSetParamFactor;			// ParamFactor가 적용되었는지.
	BOOL	m_bApprovalEnd;				// 2006-07-30 by ispark, 종료 승인

	ClientIndex_t	m_AttackIndex;
	ClientIndex_t	m_TargetIndex;		// target이 없는 skill인 경우 0

	// 2008-12-26 by bhsohn 엠기어 편대 버그 수정
	BOOL	m_bSkillEnable;

	// 2010. 10. 11. 딜레이 타겟 시전형 스킬 버그 수정.
	ClientIndex_t	m_ClickTargetIndex;
	UID32_t			m_nClickTargetUID;

};

#endif // !defined(AFX_SKILLINFO_H__7B90C53A_7DEA_4545_A5DC_CB8A64A154AD__INCLUDED_)
