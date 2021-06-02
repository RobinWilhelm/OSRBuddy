// Interface.h: interface for the CInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERFACE_H__6912F02E_DF5A_4009_BE9A_D988E4C7386B__INCLUDED_)
#define AFX_INTERFACE_H__6912F02E_DF5A_4009_BE9A_D988E4C7386B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"
#include "INFInvenExtend.h"
#include "INFGameMain.h"
#include "INFImage.h"
#include "INFImageBtn.h"


// 2008-02-27 by bhsohn 아레나 이동시 채팅정보 뺵업
//#include "ChatTab_t.h"

// 게임 윈도우창 우선순위 적용 구조체
typedef struct {
	int		nWindowIndex;		// 윈도우 인덱스
	int		nWindowOrder;		// 윈도우 처리 우선순위
} GameWindowWnd;


class CINFTarget;
class CINFGameMain;
class CINFPilotFace;
class CINFSelect;
class CINFMapLoad;
class CINFImage;
class CINFCityBase;
class CINFChannelList;
class CINFFadeEffect;
class CINFStageEffectData;
class CINFMapName;
class CGlobalImage;
class CINFCityBazaar;
class CINFCityBazaarOpen;
class CINFCityBazaarVisit;
class CINFGameArena;

// 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템
class CINFInfinity;
// end 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템

// 2010. 03. 03 by ckPark 인피니티 필드 2차(입장 UI변경)
class CINFCityInfinityFieldPopUp;
// end 2010. 03. 03 by ckPark 인피니티 필드 2차(입장 UI변경)


// 2007-07-04 by bhsohn 오퍼레이터 추가
class CINFOpMain;
// 2007-07-23 by bhsohn 오퍼레이터 추가작업
class CSetupConfig;

class CINFToolTip;

class DataHeader;	// 2008-10-15 by bhsohn 리소스 메모리 보호 기능 추가

// 2007-07-04 by bhsohn 오퍼레이터 추가
// 오퍼레이터 모드
#define	OPERATOR_USER_HELPER_NONE			0
#define	OPERATOR_USER_HELPER_FREESKA	1
#define	OPERATOR_USER_TUTORIAL_COMPLETE		2
#define	OPERATOR_USER_TUTORIAL_FAIL			3
#define	OPERATOR_USER_TUTORIAL_HELPER		4
#define	OPERATOR_USER_TUTORIAL_ALL_COMPLETE	5
#define	OPERATOR_USER_SEL_VCU				6
#define	OPERATOR_USER_SEL_ANI				7
#define	OPERATOR_USER_TUTORIAL_NOT_L10		8



class CInterface : public CAtumNode
{
public:
	CInterface();
	virtual ~CInterface();

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	
	virtual void Tick();

public:
	CINFTarget* m_pTarget;
	CINFGameMain* m_pGameMain;
	CINFPilotFace* m_pPilotFace;
	CINFMapName* m_pMapNameImg;
	BOOL					m_bShowInterface;
	CGlobalImage* m_pGameGlobalImage;

	CINFSelect* m_pSelect;
	D3DLIGHT9				m_light0;
	D3DLIGHT9				m_light1;

	CINFMapLoad* m_pMapLoad;
	CINFImage* m_pNormalMouse[2];

	CINFCityBase* m_pCityBase;
	CINFChannelList* m_pChannelList;
	CINFFadeEffect* m_pFadeEffect;
	CINFStageEffectData* m_pStageEffectData;		// 성우 스크립트

	CINFCityBazaar* m_pBazaarShop;			// 2006-07-25 by ispark, 개인 상점
	CINFGameArena* m_pGameArena;

	// 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템
	CINFInfinity* m_pInfinity;
	// end 2009. 11. 02 by ckPark 인피니티 필드 인스턴스 던젼 시스템

	// 2010. 03. 03 by ckPark 인피니티 필드 2차(입장 UI변경)
	CINFCityInfinityFieldPopUp* m_pInfinityPopup;
	// end 2010. 03. 03 by ckPark 인피니티 필드 2차(입장 UI변경)

	// 2007-07-04 by bhsohn 오퍼레이터 추가
	CINFOpMain* m_pINFOpMain;

	// 2007-07-23 by bhsohn 오퍼레이터 추가작업
	CSetupConfig* m_pSetupConfig;
	CINFToolTip* m_pToolTip;

	// 2008-11-13 by bhsohn 조이스틱 작업
	CSetupConfig* m_pJoySticConfig;
	structJoystickKey			m_struJoystickOption[MAX_JOSTICK_OPTION][MAX_JOSTICK_OPTION_BEHAVIOR];
	structJoystickSetupKeyTable* m_pJoystickSetupKeyTable;


	//////////////////////////////////////////////////////////////////////////
	// 이하 윈도우 창 우선 순위 렌더링, 메세지 처리 적용
	// ydkim 2005.10.28
	//
	// 메세지 입력 구조체 사용 우선순위와 메시지 INDEX 입력.
	// 구조체 형식은 Int형 변수 2개사용 
	// 추후 추가 및 변경
	// m_vecGameWindowWnd			정방향 저장(렌더링용)
	// m_vecGameWindowWndReverse	역방향 저장(처리용)
	//////////////////////////////////////////////////////////////////////////
	vector<GameWindowWnd>	m_vecGameWindowWnd;
	vector<GameWindowWnd>	m_vecGameWindowWndReverse;


private:
	// 2007-11-28 by bhsohn 스크린 샷 모드 추가
	BOOL		m_bScreenShotMode;

	// 2008-02-27 by bhsohn 아레나 이동시 채팅정보 뺵업
	//ChatLine_t	m_chatBackup[CHAT_BUFFER_NUMBER];

	// 2008-10-15 by bhsohn 리소스 메모리 보호 기능 추가
	DataHeader* m_pDummyDataHeader;
	// end 2008-10-15 by bhsohn 리소스 메모리 보호 기능 추가
};



#endif // !defined(AFX_INTERFACE_H__6912F02E_DF5A_4009_BE9A_D988E4C7386B__INCLUDED_)