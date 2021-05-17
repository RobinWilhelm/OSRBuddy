// FieldWinSocket.h: interface for the CFieldWinSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDWINSOCKET_H__CB2738BC_78A1_4334_A35F_5AB344D9BE08__INCLUDED_)
#define AFX_FIELDWINSOCKET_H__CB2738BC_78A1_4334_A35F_5AB344D9BE08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinSocket.h"

// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
// �Ʒ��� �̺�Ʈ 
#define	WM_ASYNC_ARENA_EVENT		(WM_USER_BASE + 3)				
#define	WM_PACKET_ARENA_NOTIFY		(WM_USER_BASE + 4)				// HWND�� ���޵Ǵ� �޽���


class CFieldWinSocket : public CWinSocket
{
public:
	CFieldWinSocket(HWND hWnd, UINT wmSock = WM_ASYNC_EVENT, UINT wmNotify = WM_PACKET_NOTIFY);
	virtual ~CFieldWinSocket();

	virtual BOOL OnRecvdPacket(LPSTR pPacket, int nLength, BYTE nSeq);		// �ϳ��� ��Ŷ�� �������� �� �߻�
public:
	int		m_nOldType;
};

#endif // !defined(AFX_FIELDWINSOCKET_H__CB2738BC_78A1_4334_A35F_5AB344D9BE08__INCLUDED_)
