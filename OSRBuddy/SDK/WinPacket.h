#pragma once
#include "SocketHeader.h"

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