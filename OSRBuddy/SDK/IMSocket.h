#pragma once

#include "Winsocket.h"

// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
// Arena Chat
#define WM_IM_ARENA_ASYNC		(WM_USER_BASE + 772)
#define WM_IM_ARENA_NOTIFY		(WM_USER_BASE + 773)
// end 2007-11-22 by bhsohn �Ʒ��� ���ռ���

class CIMSocket : public CWinSocket
{
public:
	virtual ~CIMSocket();

public:
	int m_nLoginType;
	BOOL m_bLogin;
	int		m_nOldType;
public:
	CHARACTER m_character;
public:
	virtual BOOL OnRecvdPacket(LPSTR pPacket, int nLength, BYTE nSeq);

};
