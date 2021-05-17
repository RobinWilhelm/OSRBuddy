#pragma once


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


#define SIZE_PACKET_HEADER					4		// �� ��Ŷ�� ������ ��� ������
#define SIZE_MAX_PACKET						1492	// ��Ŷ �ִ� ������(�������� �޼����� �ϳ��� ��Ŷ���� ���۵ɼ� ����)
#define SIZE_MAX_SOCKET_BUFFER				1500	// Receve Buffer �ִ� ������

typedef struct
{
	BYTE	nSeqNumber;
	BYTE	nXOR_N;
	BOOL	bIsPacketEncoded;	// default: FALSE
	BOOL	bIsVaildPacket;		// default: FALSE
}  DECODING_INFO, * PDECODING_INFO;

class CSendPacket
{  
public:
	// Attributes
	char			m_pPacket[SIZE_MAX_SOCKET_BUFFER];
	int				m_nPacketLength;
	BOOL			m_bEncodingFlag;						// is packet encoded
	static char* m_pXOR_ENCODE_BYTES;
};


class CRecvPacket
{
public:
	// Attributes
	char 	 	 	m_pPacket[SIZE_MAX_SOCKET_BUFFER];
	char			m_pPacketHeader[SIZE_PACKET_HEADER];
	int	            m_nPacketLength;
	int				m_nCurrentLength;
	int				m_nRemainedHeaderSize;

	// decoding
	DECODING_INFO	m_DecodingInfo;
	static char* m_pXOR_ENCODE_BYTES;
};