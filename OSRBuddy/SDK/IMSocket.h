#pragma once

#include "Winsocket.h"

// 2007-11-22 by bhsohn 아레나 통합서버
// Arena Chat
#define WM_IM_ARENA_ASYNC		(WM_USER_BASE + 772)
#define WM_IM_ARENA_NOTIFY		(WM_USER_BASE + 773)
// end 2007-11-22 by bhsohn 아레나 통합서버

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
