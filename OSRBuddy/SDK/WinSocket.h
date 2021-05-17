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

// socket HWND에서 받는 메시지(아래 메시지는 재정의해서 필요한 메시지로 바꿀 수 있다.)
#define	WM_USER_BASE				(WM_USER + 222)
#define	WM_ASYNC_EVENT				(WM_USER_BASE + 1)				//
#define	WM_PACKET_NOTIFY			(WM_USER_BASE + 2)				// HWND에 전달되는 메시지




class CWinSocket
{
public:
	enum
	{
		WS_ERROR = 0x0001,
		WS_CONNECTED = 0x0002,
		WS_ACCEPTED = 0x0003,		// 2007-06-21 by cmkwon, 클라이언트의 소스와 통합
		WS_RECEIVED = 0x0004,
		WS_CLOSED = 0x0005
	};
	CWinSocket(HWND hWnd, UINT wmSock = WM_ASYNC_EVENT, UINT wmNotify = WM_PACKET_NOTIFY, BOOL bEncoding = FALSE);
	virtual ~CWinSocket();

public:
	HWND					m_hMsgWnd;							// Socket Event와 Notify 메시지 전송 윈도우
	SOCKET					m_Socket;							// 소켓의 핸들
	UINT					m_wmSocket;							// HWND에서 Socket 처리 메시지(WSAAsyncSelect함수 메지시)
	UINT					m_wmNotify;							// HWND에 통보되는 메시지(HWND에 소켓 처리결과 통보)
	BOOL					m_bConnected;						// 소켓이 remote와 연결되었는지의 플래그
	int						m_nLastError;						// 마지막 Error code
	int						m_nAsyncFlag;						// WSAAsyncSelect Event parameter
	BOOL					m_bEncodingFlag;

	SOCKADDR_IN				m_SockAddrLocal;					// local을 위한 소켓 주소 구조체(Bind시에 필요)
	SOCKADDR_IN				m_SockAddrRemote;					// remote을 위한 소켓 주소 구조체(Accetp와 Connect시에 필요)
	
	list<CSendPacket*>		m_listSendPacket;					// Send Packet Pointer list
	CRITICAL_SECTION		m_criticalSendList;					// Send Packet List 의 동기화를 위해
	char					m_RecvBuffer[SIZE_MAX_SOCKET_BUFFER];	// Receive Buffer
	CRecvPacket				m_RecvPacket;						//
	queue<char*>			m_queueRecvMessage;					// Received Message를 저장해 놓을 큐
	CRITICAL_SECTION		m_criticalRecvMessageQueue;			// Received Message Queue의 동기화를 위해

	BYTE					m_byHostSequenceNumber;
	BYTE					m_byPeerSequenceNumber;
	BOOL					m_bPeerSequenceNumberInitFlag;		// 상대방의 받아야할 Sequence Number의 초기화 여부 플래그

	// 2009. 06. 17 by ckPark Frost System
	BOOL					m_bFrostEnable;
	// end 2009. 06. 17 by ckPark Frost System

public:
	int						m_nPeerPort;						// UDP 통신을 위한 상대방 Port
	char					m_szPeerIP[SIZE_MAX_IPADDRESS];		// TCP : 현재 연결된 Client의 IP Address,  UDP : 통신을 위한 상대방 IP Address
	ENServerType			m_PeerSocketType;
	BOOL					m_bSendNotify;						// Send just one time Notify message 20060514 by dhkwon	   
	

public:	
	virtual BOOL OnConnect(int nErrorCode);						// 소켓이 연결된후에 발생
	virtual BOOL OnRecvdPacket(LPSTR pPacket, int nLength, BYTE nSeq);		// 하나의 패킷이 도착했을 때 발생
	virtual BOOL OnCloseSocket(int nErrorCode);					// 소켓이 닫히고 발생

	// end 2009. 06. 17 by ckPark Frost System
};



#endif // !defined(AFX_WINSOCKET_H__22EBB374_73E5_4603_A72D_9B79226CA850__INCLUDED_)
