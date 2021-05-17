// FieldWinSocketManager.h: interface for the CFieldWinSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDWINSOCKETMANAGER_H__52C754A0_683B_4C24_B626_84476785ADFA__INCLUDED_)
#define AFX_FIELDWINSOCKETMANAGER_H__52C754A0_683B_4C24_B626_84476785ADFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "FieldWinSocket.h"

class CFieldWinSocketManager
{
public:
	CFieldWinSocketManager(HWND hwnd);
	virtual ~CFieldWinSocketManager();

	CFieldWinSocket* m_pMainFieldWinSocket;				// ���� ���� ����
	CFieldWinSocket* m_pArenaFieldWinSocket;				// �Ʒ��� ���� ����

	HWND						m_hMainWnd;

	BOOL						m_bRequestArenaSocketClose;			// ���� ��û�� ���� Ŭ�ο����?

};

#endif // !defined(AFX_FIELDWINSOCKETMANAGER_H__52C754A0_683B_4C24_B626_84476785ADFA__INCLUDED_)
