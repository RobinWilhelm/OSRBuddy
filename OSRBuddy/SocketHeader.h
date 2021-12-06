#pragma once
///////////////////////////////////////////////////////////////////////////////
//  SocketHeader.h : ���� ���� ����� CIOCP�� CWinPacket���� include�Ѵ�
//  
//  Date	: 2004-03-17 by cmkwon
///////////////////////////////////////////////////////////////////////////////

#ifndef _SOCKET_HEADER_H_
#define _SOCKET_HEADER_H_

#include <winsock2.h>
#include <Mmsystem.h>

#pragma comment(lib, "Ws2_32.lib")

///////////////////////////////////////////////////////////////////////////////
// Socket ���� define
#define SIZE_MAX_IPADDRESS					16		// string IP Address 

///////////////////////////////////////////////////////////////////////////////
// Packet Header ���� define
typedef USHORT MessageType_t;						// ��Ŷ Ÿ���� ����
typedef USHORT Err_t;								// ���� Ÿ���� ����
#define SIZE_PACKET_HEADER					4		// �� ��Ŷ�� ������ ��� ������
#define SIZE_BODY_LENGTH					2		// �� ��Ŷ�� ������ ��� ������
#define SIZE_ENCODE_FLAG					1		// ��ȣȭ ���� flag ������
#define SIZE_CHECKSUM						1		// checksum�� byte ��
#define SIZE_SEQ_NUM						1		// sequence number�� byte ��
#define SIZE_MAX_DUMMY_DATA					3		// dummy data�� �ִ� ����
#define SIZE_FIELD_TYPE_HEADER				2		// �ϳ��� ��Ŷ�� �������� �ʵ�� �����ȴ�. �� �ʵ��� Ÿ�� ��� ������
#define SIZE_MAX_PACKET						1492	// ��Ŷ �ִ� ������(�������� �޼����� �ϳ��� ��Ŷ���� ���۵ɼ� ����)
#define SIZE_MAX_SOCKET_BUFFER				1500	// Receve Buffer �ִ� ������

#define COUNT_MAX_SOCKET_SESSION			3000	// �������� ������ �ִ� ���� Ŭ���̾�Ʈ��
#define SIZE_MAX_PRESERVER_SESSION			3000	// Pre Server���� ������ �ִ� ���� Ŭ���̾�Ʈ��, COUNT_MAX_SOCKET_SESSION ����
#define SIZE_MAX_FIELDSERVER_SESSION		1000	// Field Server���� ������ �ִ� ���� Ŭ���̾�Ʈ��, COUNT_MAX_SOCKET_SESSION ����
#define SIZE_MAX_IMSERVER_SESSION			3000	// IM Server���� ������ �ִ� ���� Ŭ���̾�Ʈ��, COUNT_MAX_SOCKET_SESSION ����
#define SIZE_MAX_NPCSERVER_SESSION			50		// NPC Server���� ������ �ִ���� ��, COUNT_MAX_SOCKET_SESSION ����
#define SIZE_MAX_LOGSERVER_SESSION			100		// Log �������� ������ �ִ� ���� ������, COUNT_MAX_SOCKET_SESSION ����

///////////////////////////////////////////////////////////////////////////////
// Declare Variable, Set Message Buffer & Type
//		_MSG_STRUCT	: �޼��� ����ü Ÿ��
//		_VAR_NAME	: ���� �̸�
//		_BUFFER		: ����
//		_MSG_TYPE	: �޼��� Ÿ��
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
	- Sequence Number ����
		(1)
		ù SeqNumber := Random �Լ��� ������ Number (0~127)

		(2)
		NewSeqNumber := ( SeqNumber + A ) * B
		if ( NewSeqNumber > C ) {
			NextSeqNumber := NewSeqNumber % C
		} else {
			NextSeqNumber := SeqNumber
		}

  * encoding rule 2
	- Dummy Data ���� �� packet �ںκп� �߰�
	  Dummy Data�� ���̴� 0~3B = (seq. #) % 4, ������ ���Ƿ� ����

  * encoding rule 3
	- checksum ���� �� �߰�

  * encoding rule 4
	- XOR_DATA[128]�� �̸� �����ص�.
	- (seq. #)�� XOR_DATA[N-1]�� xor ������ ��
	- (MSGs + checksum)�� XOR_DATA[N]���� XOR_DATA[127]������ xor ������ ��
	  XOR_DATA[127] �������� XOR_DATA[0]���� �ٽ� ������
	- N ���� ȿ������ ���� �׻� 4�� ���, N���� ������ 4, 8, ... , 124

  * invalid packet�� ���ǵ�
	- sequence number�� ���� ����
	- checksum�� ���� ����
	- dummy data�� ���̰� ���� ������, checksum�� Ʋ���ų�, MSG�� ���� �ʰ� ��
	- XOR_DATA�� ������ �� ���� MSGs�� protocol�� ���� ����

/////////////////////////////////////////////////////////////////////////////*/

#define ENCODE_MASK		0x80		// 10000000
#define XOR_N_MASK		0x7F		// 01111111

#define SEQNO_VAR_A		1
#define SEQNO_VAR_B		2
#define SEQNO_VAR_C		119			// MAX Sequence Number

#define SIZE_XOR_ENCODE_BYTES	128
//#define XOR_ENCODE_BYTES "vmdlfjhud830pwkldlkv[]f\20jdmvld;sk,mcuie8rijmfvkidfo340-pflcl,;dsd]u03u40jvconvn08892h0nnlsnldsf/,;vms[pf-2fjd]u03u40jvconvn082"

#define XOR_ENCODE_BYTES "045-8101F0253#4F850+20A075900445C54145B534/?^?066C65164F19%015E4F5?C0152E@05C1C1?{4075C114B16504D9D00445F001455}580B4407150051" //2014-07-30, St0rmy changed packet key

// sequence number�� connection�� �ϳ��� �����ؾ� �ϱ� ������, IOCPSocket���� �����Ѵ�.
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
	RES_BREAK = 0,	// ����� ������. ������ ���� �ʴ´�.
	RES_PACKET_ERROR = 1,	// ��Ŷ�� �ջ�� ���. ���� packet�� ó������ �ʰ� �ٷ� �����Ѵ�. ������ ���ῡ�� ���.
	RES_RETURN_TRUE = 2,	// ����
	RES_RETURN_FALSE = 3		// ������ ������ϴ� ���. �������� ���� ��
} ProcessResult;

// ����׿� - For PrintExchangeMsg()
#define RECV_TYPE 0
#define SEND_TYPE 1

#define PRINTLEVEL_ALL				0
#define PRINTLEVEL_WO_ALIVE			1
#define PRINTLEVEL_WO_MOVE_BATTLE	2
#define PRINTLEVEL_A_FEW			3
#define PRINTLEVEL_FEW				4
#define PRINTLEVEL_NO_MSG			5

//////////////////////////////////////////////////////////////////////////
// Socket ���� Global Variable
//////////////////////////////////////////////////////////////////////////
extern BYTE			g_exchangeMsgPrintLevel;	// check: MSG�� print�ϴ� level�� �����ϱ� ����(AtumMonitor�� ���� ����), by kelovon



#endif	// _SOCKET_HEADER_H_endif
