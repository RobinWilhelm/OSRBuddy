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

	CFieldWinSocket* m_pMainFieldWinSocket;				// 메인 서버 소켓
	CFieldWinSocket* m_pArenaFieldWinSocket;				// 아레나 서버 소켓

	HWND						m_hMainWnd;

	BOOL						m_bRequestArenaSocketClose;			// 소켓 요청에 의한 클로우즈냐?

};

#endif // !defined(AFX_FIELDWINSOCKETMANAGER_H__52C754A0_683B_4C24_B626_84476785ADFA__INCLUDED_)
