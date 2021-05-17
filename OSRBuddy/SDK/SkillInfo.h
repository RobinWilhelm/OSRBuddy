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
/// \brief		CSkill �� ��ų ��ü�� �����ϴ� Ŭ�������, CSkillInfo�� ��ų �ϳ��� ���� ������ ����ϴ� Ŭ������.
///				��, CSkillInfo �� ��ų 1���� ���Ѵ�.
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

	float	m_fCheckWaitingTime;		// ������ ������ ��ٸ��� �ð�
	float	m_fCheckWaitingPrepareTime;	// ������ ������ ��ٸ��� �ð�
	float	m_fCheckReattackTime;		// �� ���� ���� �ð�
	float	m_fCheckEnableTime;			// �ð� �� ��ų�� �����ȴ�.
	float	m_fCheckPrepareTime;		// �ߵ� �ð�
	float	m_fCheckAckWaitingTime;		// 2005-12-05 by ispark, ���ѵ� �ð� üũ(�ð��� ������ �ϸ� �ڵ� ��ų ���)
	int		m_dwState;					// ��ų ����
	BOOL	m_bSetParamFactor;			// ParamFactor�� ����Ǿ�����.
	BOOL	m_bApprovalEnd;				// 2006-07-30 by ispark, ���� ����

	ClientIndex_t	m_AttackIndex;
	ClientIndex_t	m_TargetIndex;		// target�� ���� skill�� ��� 0

	// 2008-12-26 by bhsohn ����� ��� ���� ����
	BOOL	m_bSkillEnable;

	// 2010. 10. 11. ������ Ÿ�� ������ ��ų ���� ����.
	ClientIndex_t	m_ClickTargetIndex;
	UID32_t			m_nClickTargetUID;

};

#endif // !defined(AFX_SKILLINFO_H__7B90C53A_7DEA_4545_A5DC_CB8A64A154AD__INCLUDED_)
