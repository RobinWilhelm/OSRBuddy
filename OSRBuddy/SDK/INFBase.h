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
{// 2007-12-03 by dhjin, 전진기지 정보 
	BYTE			Influence;
	MapIndex_t		MapIndex;
	UID32_t			GuildUID;
	CHAR			GuildCommander[SIZE_MAX_CHARACTER_NAME];
	CHAR			GuildName[SIZE_MAX_GUILD_NAME];
	ATUM_DATE_TIME	OutpostDate;
};

// 아레나 모드.
enum {
	ARENA_WAR_MODE_DEATHMATCH,				// 데스매치.
	ARENA_WAR_MODE_ROUND,					// 라운드.
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



// 2010-06-15 by shcho&hslee 펫시스템 - 좌표 처리 관련 클래스 추가.

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

// End 2010-06-15 by shcho&hslee 펫시스템 - 좌표 처리 관련 클래스 추가.


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
	float			m_fTexRate;			// 상점에서만 사용

};

#endif // !defined(AFX_INFBASE_H__945C37CC_0842_4739_98D3_F4085A935FCC__INCLUDED_)


