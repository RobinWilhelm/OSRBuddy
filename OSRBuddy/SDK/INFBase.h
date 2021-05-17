// INFBase.h: interface for the CINFBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFBASE_H__945C37CC_0842_4739_98D3_F4085A935FCC__INCLUDED_)
#define AFX_INFBASE_H__945C37CC_0842_4739_98D3_F4085A935FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"

struct SCITY_WARINFO_OUTPOST
{// 2007-12-03 by dhjin, �������� ���� 
	BYTE			Influence;
	MapIndex_t		MapIndex;
	UID32_t			GuildUID;
	CHAR			GuildCommander[SIZE_MAX_CHARACTER_NAME];
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME	OutpostDate;
};

// �Ʒ��� ���.
enum {
	ARENA_WAR_MODE_DEATHMATCH,				// ������ġ.
	ARENA_WAR_MODE_ROUND,					// ����.
	ARENA_WAR_MODE_END
};
struct ST_WARINFO_OUTPOST : public SCITY_WARINFO_OUTPOST
{

	//	BYTE			Influence;
	//	MapIndex_t		MapIndex;
	//	UID32_t			GuildUID;
	CINFImage* pGuildMark;
	//	CHAR			GuildCommander[SIZE_MAX_CHARACTER_NAME];
	//	CHAR			GuildName[SIZE_MAX_GUILD_NAME];
	//	ATUM_DATE_TIME	OutpostDate;

};



// 2010-06-15 by shcho&hslee ��ý��� - ��ǥ ó�� ���� Ŭ���� �߰�.

class CPosData
{

public:

	CPosData();
	virtual ~CPosData();


	float	_fPosx;
	float	_fPosy;

	float	_fWid;
	float	_fHgt;

	RECT	_rcRECT;

};

// End 2010-06-15 by shcho&hslee ��ý��� - ��ǥ ó�� ���� Ŭ���� �߰�.


class DataHeader;
class CGameData;
class CINFBase : public CAtumNode
{
public:
	CINFBase();
	virtual ~CINFBase();

	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	
public:
	CGameData* m_pGameData;
	float			m_fTexRate;			// ���������� ���

};

#endif // !defined(AFX_INFBASE_H__945C37CC_0842_4739_98D3_F4085A935FCC__INCLUDED_)


