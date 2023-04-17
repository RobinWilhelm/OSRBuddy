#pragma once
#include "IMSocket.h"

class CIMSocketManager
{
public:
	virtual ~CIMSocketManager();

public:
	CIMSocket* m_pMainIMSocket;					// 채팅 서버
	CIMSocket* m_pArenaIMSocket;					// 아레나 채팅 서버

	HWND				m_hwnd;

	// 2008-07-11 by bhsohn 과도한 채팅시, 채팅금지 시스템 추가
	ATUM_DATE_TIME		m_timeLastSendChat;
	ATUM_DATE_TIME		m_timeForbidSendChat;
	int					m_nMinChatCount;

};