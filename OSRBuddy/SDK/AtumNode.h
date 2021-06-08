// AtumNode.h: interface for the CAtumNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATUMNODE_H__C4F6F8E5_CA48_46AF_8E84_DD50489CBCF1__INCLUDED_)
#define AFX_ATUMNODE_H__C4F6F8E5_CA48_46AF_8E84_DD50489CBCF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Windows.h>

class CAtumNode
{
public:
	CAtumNode();
	CAtumNode(CAtumNode* pParent);
	virtual ~CAtumNode();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual void Render();
	virtual void Tick();   

public:
	CAtumNode* m_pPrev;		// ������ ���
	CAtumNode* m_pNext;		// ������ ���
	CAtumNode* m_pChild;		// ���ϵ� ���
	CAtumNode* m_pParent;		// �θ��� ���
	DWORD			m_dwStateBlock;	// ���������º�
	BOOL			m_bUsing;
	DWORD			m_dwPartType; //32
};

#endif // !defined(AFX_ATUMNODE_H__C4F6F8E5_CA48_46AF_8E84_DD50489CBCF1__INCLUDED_)
