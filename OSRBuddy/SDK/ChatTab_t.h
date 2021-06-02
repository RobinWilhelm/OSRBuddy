#ifndef _CHATTAB_T_H_
#define _CHATTAB_T_H_

#include "AtumParam.h"

#define CHAT_BUFFER_NUMBER					200							// ä�� �ִ� ���� ���ۼ�


typedef struct ChatTab
{
	char* pszChatString;											// �Ѷ����� ä�� ������ ����
	DWORD		dwColorType;											// �̶����� Color
	DWORD		dwType;													// ä���� ����(��ü, ����, �Ʒ���, ��Ƽ��)
	ChatTab()
	{
		pszChatString = NULL;
		dwColorType = 0;
		dwType = 0;
	}
} ChatLine_t;

class ChatTab_t
{
public:
	ChatTab_t() : m_nStoreStartIndex(0), m_nStoreEndIndex(0), m_nRenderStartIndex(0), m_nStoredLineCounts(0)
	{
		//		memset(m_ArrChatLine, 0x00, sizeof(m_ArrChatLine[0])*CHAT_BUFFER_NUMBER);
	}
	virtual ~ChatTab_t();

	ChatLine_t		m_ArrChatLine[CHAT_BUFFER_NUMBER];
	int				m_nStoredLineCounts;								// ����� ä���� ���μ�
	int				m_nStoreStartIndex;									// ����� ä���� ���� �ε���
	int				m_nStoreEndIndex;									// ����� ä���� ������ �ε���
	int				m_nRenderStartIndex;								// ä�� â�� Render�ϱ� ���� ���� �ε���
};



#endif// _CHATTAB_T_H_endif