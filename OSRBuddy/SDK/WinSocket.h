// WinSocket.h: interface for the CWinSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINSOCKET_H__22EBB374_73E5_4603_A72D_9B79226CA850__INCLUDED_)
#define AFX_WINSOCKET_H__22EBB374_73E5_4603_A72D_9B79226CA850__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "WinPacket.h"
#include "mt_stl.h"
#include <queue>

using namespace std;

// socket HWND���� �޴� �޽���(�Ʒ� �޽����� �������ؼ� �ʿ��� �޽����� �ٲ� �� �ִ�.)
#define	WM_USER_BASE				(WM_USER + 222)
#define	WM_ASYNC_EVENT				(WM_USER_BASE + 1)				//
#define	WM_PACKET_NOTIFY			(WM_USER_BASE + 2)				// HWND�� ���޵Ǵ� �޽���




class CWinSocket
{
public:
	enum
	{
		WS_ERROR = 0x0001,
		WS_CONNECTED = 0x0002,
		WS_ACCEPTED = 0x0003,		// 2007-06-21 by cmkwon, Ŭ���̾�Ʈ�� �ҽ��� ����
		WS_RECEIVED = 0x0004,
		WS_CLOSED = 0x0005
	};
	CWinSocket(HWND hWnd, UINT wmSock = WM_ASYNC_EVENT, UINT wmNotify = WM_PACKET_NOTIFY, BOOL bEncoding = FALSE);
	virtual ~CWinSocket();

public:
	HWND					m_hMsgWnd;							// Socket Event�� Notify �޽��� ���� ������
	SOCKET					m_Socket;							// ������ �ڵ�
	UINT					m_wmSocket;							// HWND���� Socket ó�� �޽���(WSAAsyncSelect�Լ� ������)
	UINT					m_wmNotify;							// HWND�� �뺸�Ǵ� �޽���(HWND�� ���� ó����� �뺸)
	BOOL					m_bConnected;						// ������ remote�� ����Ǿ������� �÷���
	int						m_nLastError;						// ������ Error code
	int						m_nAsyncFlag;						// WSAAsyncSelect Event parameter
	BOOL					m_bEncodingFlag;

	SOCKADDR_IN				m_SockAddrLocal;					// local�� ���� ���� �ּ� ����ü(Bind�ÿ� �ʿ�)
	SOCKADDR_IN				m_SockAddrRemote;					// remote�� ���� ���� �ּ� ����ü(Accetp�� Connect�ÿ� �ʿ�)
	
	list<CSendPacket*>		m_listSendPacket;					// Send Packet Pointer list
	CRITICAL_SECTION		m_criticalSendList;					// Send Packet List �� ����ȭ�� ����
	char					m_RecvBuffer[SIZE_MAX_SOCKET_BUFFER];	// Receive Buffer
	CRecvPacket				m_RecvPacket;						//
	queue<char*>			m_queueRecvMessage;					// Received Message�� ������ ���� ť
	CRITICAL_SECTION		m_criticalRecvMessageQueue;			// Received Message Queue�� ����ȭ�� ����

	BYTE					m_byHostSequenceNumber;
	BYTE					m_byPeerSequenceNumber;
	BOOL					m_bPeerSequenceNumberInitFlag;		// ������ �޾ƾ��� Sequence Number�� �ʱ�ȭ ���� �÷���

	// 2009. 06. 17 by ckPark Frost System
	BOOL					m_bFrostEnable;
	// end 2009. 06. 17 by ckPark Frost System

public:
	int						m_nPeerPort;						// UDP ����� ���� ���� Port
	char					m_szPeerIP[SIZE_MAX_IPADDRESS];		// TCP : ���� ����� Client�� IP Address,  UDP : ����� ���� ���� IP Address
	ENServerType			m_PeerSocketType;
	BOOL					m_bSendNotify;						// Send just one time Notify message 20060514 by dhkwon	   
	

public:	
	virtual BOOL OnConnect(int nErrorCode);						// ������ ������Ŀ� �߻�
	virtual BOOL OnRecvdPacket(LPSTR pPacket, int nLength, BYTE nSeq);		// �ϳ��� ��Ŷ�� �������� �� �߻�
	virtual BOOL OnCloseSocket(int nErrorCode);					// ������ ������ �߻�

	// end 2009. 06. 17 by ckPark Frost System
};



#endif // !defined(AFX_WINSOCKET_H__22EBB374_73E5_4603_A72D_9B79226CA850__INCLUDED_)
