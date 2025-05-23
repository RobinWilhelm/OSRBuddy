#pragma once
///////////////////////////////////////////////////////////////////////////////
//  SocketHeader.h : 소켓 관련 헤더로 CIOCP와 CWinPacket에서 include한다
//  
//  Date	: 2004-03-17 by cmkwon
///////////////////////////////////////////////////////////////////////////////

#ifndef _SOCKET_HEADER_H_
#define _SOCKET_HEADER_H_

#include <winsock2.h>
#include <Mmsystem.h>

#pragma comment(lib, "Ws2_32.lib")

///////////////////////////////////////////////////////////////////////////////
// Socket 관련 define
#define SIZE_MAX_IPADDRESS					16		// string IP Address 

///////////////////////////////////////////////////////////////////////////////
// Packet Header 관련 define
typedef USHORT MessageType_t;						// 패킷 타입을 위해
typedef USHORT Err_t;								// 에러 타입을 위해
#define SIZE_PACKET_HEADER					4		// 각 패킷간 사이즈 헤더 사이즈
#define SIZE_BODY_LENGTH					2		// 각 패킷간 사이즈 헤더 사이즈
#define SIZE_ENCODE_FLAG					1		// 암호화 정보 flag 사이즈
#define SIZE_CHECKSUM						1		// checksum의 byte 수
#define SIZE_SEQ_NUM						1		// sequence number의 byte 수
#define SIZE_MAX_DUMMY_DATA					3		// dummy data의 최대 길이
#define SIZE_FIELD_TYPE_HEADER				2		// 하나의 패킷은 여러개의 필드로 구성된다. 각 필드의 타입 헤더 사이즈
#define SIZE_MAX_PACKET						1492	// 패킷 최대 사이즈(여러개의 메세지가 하나의 패킷으로 전송될수 있음)
#define SIZE_MAX_SOCKET_BUFFER				1500	// Receve Buffer 최대 사이즈

#define COUNT_MAX_SOCKET_SESSION			3000	// 서버에서 지원할 최대 접속 클라이언트수
#define SIZE_MAX_PRESERVER_SESSION			3000	// Pre Server에서 지원할 최대 접속 클라이언트수, COUNT_MAX_SOCKET_SESSION 이하
#define SIZE_MAX_FIELDSERVER_SESSION		1000	// Field Server에서 지원할 최대 접속 클라이언트수, COUNT_MAX_SOCKET_SESSION 이하
#define SIZE_MAX_IMSERVER_SESSION			3000	// IM Server에서 지원할 최대 접속 클라이언트수, COUNT_MAX_SOCKET_SESSION 이하
#define SIZE_MAX_NPCSERVER_SESSION			50		// NPC Server에서 지원할 최대맵의 수, COUNT_MAX_SOCKET_SESSION 이하
#define SIZE_MAX_LOGSERVER_SESSION			100		// Log 서버에서 지원할 최대 접속 서버수, COUNT_MAX_SOCKET_SESSION 이하

///////////////////////////////////////////////////////////////////////////////
// Declare Variable, Set Message Buffer & Type
//		_MSG_STRUCT	: 메세지 구조체 타입
//		_VAR_NAME	: 변수 이름
//		_BUFFER		: 버퍼
//		_MSG_TYPE	: 메세지 타입
///////////////////////////////////////////////////////////////////////////////
#define INIT_MSG(_MSG_STRUCT, _MSG_TYPE, _VAR_NAME, _BUFFER)				 \
	_MSG_STRUCT *_VAR_NAME = (_MSG_STRUCT*)((_BUFFER)+SIZE_FIELD_TYPE_HEADER); \
	*(MessageType_t*)(_BUFFER) = _MSG_TYPE;
#define INIT_MSG_WITH_BUFFER(_MSG_STRUCT, _MSG_TYPE, _VAR_NAME, _BUFFER)	 \
	BYTE _BUFFER[SIZE_MAX_PACKET];											 \
	_MSG_STRUCT *_VAR_NAME = (_MSG_STRUCT*)((_BUFFER)+SIZE_FIELD_TYPE_HEADER); \
	*(MessageType_t*)(_BUFFER) = _MSG_TYPE;
#define SET_MSG_TYPE(_BUFFER, _MSG_TYPE)	*(MessageType_t*)_BUFFER = _MSG_TYPE;
#define MSG_SIZE(_MSG_STRUCT)				(SIZE_FIELD_TYPE_HEADER + sizeof(_MSG_STRUCT))



///////////////////////////////////////////////////////////////////////////////
// Encode/Decode Protocol
/*/////////////////////////////////////////////////////////////////////////////

	<------------------- 4B --------------->
	-----------------------------------------------------------------------
	| size | encode_flag +   N    | seq. # | MSGs ... | checksum |  dummy  |
	| (2B) |   (1bit)    + (7bit) |  (1B)  |          |   (1B)   |  (0~3B) |
	-----------------------------------------------------------------------
								  <- XOR -><------- XOR --------->

  * encoding rule 1
	- Sequence Number 생성
		(1)
		첫 SeqNumber := Random 함수로 생성된 Number (0~127)

		(2)
		NewSeqNumber := ( SeqNumber + A ) * B
		if ( NewSeqNumber > C ) {
			NextSeqNumber := NewSeqNumber % C
		} else {
			NextSeqNumber := SeqNumber
		}

  * encoding rule 2
	- Dummy Data 생성 및 packet 뒤부분에 추가
	  Dummy Data의 길이는 0~3B = (seq. #) % 4, 내용은 임의로 결정

  * encoding rule 3
	- checksum 생성 및 추가

  * encoding rule 4
	- XOR_DATA[128]을 미리 생성해둠.
	- (seq. #)는 XOR_DATA[N-1]과 xor 연산을 함
	- (MSGs + checksum)는 XOR_DATA[N]부터 XOR_DATA[127]까지와 xor 연산을 함
	  XOR_DATA[127] 다음에는 XOR_DATA[0]부터 다시 시작함
	- N 값은 효율성을 위해 항상 4의 배수, N값의 범위는 4, 8, ... , 124

  * invalid packet의 조건들
	- sequence number가 맞지 않음
	- checksum이 맞지 않음
	- dummy data의 길이가 맞지 않으면, checksum이 틀리거나, MSG가 맞지 않게 됨
	- XOR_DATA와 연산을 한 후의 MSGs가 protocol과 맞지 않음

/////////////////////////////////////////////////////////////////////////////*/

#define ENCODE_MASK		0x80		// 10000000
#define XOR_N_MASK		0x7F		// 01111111

#define SEQNO_VAR_A		1
#define SEQNO_VAR_B		2
#define SEQNO_VAR_C		119			// MAX Sequence Number

#define SIZE_XOR_ENCODE_BYTES	128
//#define XOR_ENCODE_BYTES "vmdlfjhud830pwkldlkv[]f\20jdmvld;sk,mcuie8rijmfvkidfo340-pflcl,;dsd]u03u40jvconvn08892h0nnlsnldsf/,;vms[pf-2fjd]u03u40jvconvn082"

#define XOR_ENCODE_BYTES "045-8101F0253#4F850+20A075900445C54145B534/?^?066C65164F19%015E4F5?C0152E@05C1C1?{4075C114B16504D9D00445F001455}580B4407150051" //2014-07-30, St0rmy changed packet key

// sequence number는 connection당 하나를 관리해야 하기 때문에, IOCPSocket에서 관리한다.
typedef struct
{
	BYTE	nSeqNumber;
	BYTE	nXOR_N;
	BOOL	bIsPacketEncoded;	// default: FALSE
	BOOL	bIsVaildPacket;		// default: FALSE
}  DECODING_INFO, * PDECODING_INFO;

#ifndef	RESET_DECOING_INFO
#define RESET_DECOING_INFO(x) { memset(&x, 0x00, sizeof(DECODING_INFO)); }
#endif

typedef enum
{
	ST_NORMAL_SERVER = 0,
	ST_PRE_SERVER = 1,
	ST_IM_SERVER = 2,
	ST_LOG_SERVER = 3,
	ST_MONITOR_SERVER = 4,
	ST_FIELD_SERVER = 5,
	ST_NPC_SERVER = 6,
	ST_CLIENT_TYPE = 7,
	ST_INVALID_TYPE = 8
} ENServerType;

typedef enum
{
	RES_BREAK = 0,	// 경미한 에러들. 연결을 끊지 않는다.
	RES_PACKET_ERROR = 1,	// 패킷이 손상된 경우. 남은 packet을 처리하지 않고 바로 리턴한다. 서버간 연결에만 사용.
	RES_RETURN_TRUE = 2,	// 정상
	RES_RETURN_FALSE = 3		// 연결을 끊어야하는 경우. 프로토콜 에러 등
} ProcessResult;

// 디버그용 - For PrintExchangeMsg()
#define RECV_TYPE 0
#define SEND_TYPE 1

#define PRINTLEVEL_ALL				0
#define PRINTLEVEL_WO_ALIVE			1
#define PRINTLEVEL_WO_MOVE_BATTLE	2
#define PRINTLEVEL_A_FEW			3
#define PRINTLEVEL_FEW				4
#define PRINTLEVEL_NO_MSG			5

//////////////////////////////////////////////////////////////////////////
// Socket 관련 Global Variable
//////////////////////////////////////////////////////////////////////////
extern BYTE			g_exchangeMsgPrintLevel;	// check: MSG를 print하는 level을 조정하기 위해(AtumMonitor로 조절 가능), by kelovon



#endif	// _SOCKET_HEADER_H_endif
