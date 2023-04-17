#pragma once
// INFCommunity.h: interface for the CINFCommunity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFCOMMUNITY_H__518CBD3B_8B48_4BB5_B7F7_62E03BDA55FD__INCLUDED_)
#define AFX_INFCOMMUNITY_H__518CBD3B_8B48_4BB5_B7F7_62E03BDA55FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INFBase.h"
#include "INFCommuPartyInvite.h"

#define COMMUNITY_PARTY			0
#define COMMUNITY_FRIEND		1
#define COMMUNITY_GUILD			2
#define COMMUNITY_CHATROOM		3
#define COMMUNITY_MAIL			4
#define COMMUNITY_REJECT		5

// 길드 요청 윈도우
#define COMMUNITY_MEMINFO_MANAGER	0
#define COMMUNITY_MEMINFO_SEARCH	1

class CAtumNode;
class CINFCommunityParty;
class CINFCommunityGuild;
class CINFCommunityFriend;
class CINFCommunityReject;
class CINFCommunityChatRoom;
class CINFCommunityLetter;	// 2008-04-04 by bhsohn Ep3 커뮤니티 창
class CINFCommuPartyCre;	// 2008-04-04 by bhsohn Ep3 커뮤니티 창
class CINFCommunityGuildManager;// 2008-04-04 by bhsohn Ep3 커뮤니티 창
class CINFCommunityGuildSearch;// 2008-04-04 by bhsohn Ep3 커뮤니티 창
class CINFCommunityGuildIntroMe;// 2008-04-04 by bhsohn Ep3 커뮤니티 창
class CINFCommunityUserOpenSetup;
class CINFCommunityUserInfo;
class CINFImage;
class CINFImageBtn;
class CINFCommunity : public CINFBase
{
public:
	CINFCommunity(CAtumNode* pParent);
	virtual ~CINFCommunity();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual void Tick();
	virtual int WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	BOOL					m_bRestored;
	int						m_nCommunityType;	//	COMMUNITY_~

	//CINFImage	*			m_pLogo;

	CINFCommunityParty* m_pParty;
	CINFCommunityGuild* m_pGuild;
	CINFCommunityChatRoom* m_pChatRoom;
	CINFCommunityFriend* m_pFriend;
	CINFCommunityReject* m_pReject;
	// 2008-04-04 by bhsohn Ep3 커뮤니티 창
	CINFCommunityLetter* m_pLetter;		// 편지 


	// 2008-04-04 by bhsohn Ep3 커뮤니티 창
	POINT					m_ptCommunityBk;
	BOOL					m_bShowWnd;

	CINFCommuPartyCre* m_pCommuPartyCreate;	// 편대생성	
	CINFCommuPartyInvite* m_pCommuPartyInvite;	// 편대 초대
	CINFCommunityGuildManager* m_pCommunityGuildManager;
	CINFCommunityGuildSearch* m_pCommunityGuildSearch;	// 길드 찾기
	CINFCommunityGuildIntroMe* m_pCommunityGuildIntroMe;
	CINFCommunityUserOpenSetup* m_pCommunityUserOpenSetup;	// 공개 설정
	CINFCommunityUserInfo* m_pCommunityUserInfo;

	CINFImageBtn* m_pCloseBtn;	// 닫기 버튼
	int							m_nRqMemInfoWnd;

	int							m_nLastRqSecretInfoOption;

	BOOL						m_bMove;
	POINT						m_ptCommOpMouse;

};

#endif // !defined(AFX_INFCOMMUNITY_H__518CBD3B_8B48_4BB5_B7F7_62E03BDA55FD__INCLUDED_)
