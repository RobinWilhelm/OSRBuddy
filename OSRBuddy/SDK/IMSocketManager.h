#pragma once
#include "IMSocket.h"

class CIMSocketManager
{
public:
	virtual ~CIMSocketManager();

public:
	CIMSocket* m_pMainIMSocket;					// ä�� ����
	CIMSocket* m_pArenaIMSocket;					// �Ʒ��� ä�� ����

	HWND				m_hwnd;

	// 2008-07-11 by bhsohn ������ ä�ý�, ä�ñ��� �ý��� �߰�
	ATUM_DATE_TIME		m_timeLastSendChat;
	ATUM_DATE_TIME		m_timeForbidSendChat;
	int					m_nMinChatCount;

};