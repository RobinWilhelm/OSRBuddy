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


// 2008-02-27 by bhsohn �Ʒ��� �̵��� ä������ ����
//#include "ChatTab_t.h"

// ���� ������â �켱���� ���� ����ü
typedef struct {
	int		nWindowIndex;		// ������ �ε���
	int		nWindowOrder;		// ������ ó�� �켱����
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

// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
class CINFInfinity;
// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

// 2010. 03. 03 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� UI����)
class CINFCityInfinityFieldPopUp;
// end 2010. 03. 03 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� UI����)


// 2007-07-04 by bhsohn ���۷����� �߰�
class CINFOpMain;
// 2007-07-23 by bhsohn ���۷����� �߰��۾�
class CSetupConfig;

class CINFToolTip;

class DataHeader;	// 2008-10-15 by bhsohn ���ҽ� �޸� ��ȣ ��� �߰�

// 2007-07-04 by bhsohn ���۷����� �߰�
// ���۷����� ���
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
	CINFStageEffectData* m_pStageEffectData;		// ���� ��ũ��Ʈ

	CINFCityBazaar* m_pBazaarShop;			// 2006-07-25 by ispark, ���� ����
	CINFGameArena* m_pGameArena;

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	CINFInfinity* m_pInfinity;
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���

	// 2010. 03. 03 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� UI����)
	CINFCityInfinityFieldPopUp* m_pInfinityPopup;
	// end 2010. 03. 03 by ckPark ���Ǵ�Ƽ �ʵ� 2��(���� UI����)

	// 2007-07-04 by bhsohn ���۷����� �߰�
	CINFOpMain* m_pINFOpMain;

	// 2007-07-23 by bhsohn ���۷����� �߰��۾�
	CSetupConfig* m_pSetupConfig;
	CINFToolTip* m_pToolTip;

	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	CSetupConfig* m_pJoySticConfig;
	structJoystickKey			m_struJoystickOption[MAX_JOSTICK_OPTION][MAX_JOSTICK_OPTION_BEHAVIOR];
	structJoystickSetupKeyTable* m_pJoystickSetupKeyTable;


	//////////////////////////////////////////////////////////////////////////
	// ���� ������ â �켱 ���� ������, �޼��� ó�� ����
	// ydkim 2005.10.28
	//
	// �޼��� �Է� ����ü ��� �켱������ �޽��� INDEX �Է�.
	// ����ü ������ Int�� ���� 2����� 
	// ���� �߰� �� ����
	// m_vecGameWindowWnd			������ ����(��������)
	// m_vecGameWindowWndReverse	������ ����(ó����)
	//////////////////////////////////////////////////////////////////////////
	vector<GameWindowWnd>	m_vecGameWindowWnd;
	vector<GameWindowWnd>	m_vecGameWindowWndReverse;


private:
	// 2007-11-28 by bhsohn ��ũ�� �� ��� �߰�
	BOOL		m_bScreenShotMode;

	// 2008-02-27 by bhsohn �Ʒ��� �̵��� ä������ ����
	//ChatLine_t	m_chatBackup[CHAT_BUFFER_NUMBER];

	// 2008-10-15 by bhsohn ���ҽ� �޸� ��ȣ ��� �߰�
	DataHeader* m_pDummyDataHeader;
	// end 2008-10-15 by bhsohn ���ҽ� �޸� ��ȣ ��� �߰�
};



#endif // !defined(AFX_INTERFACE_H__6912F02E_DF5A_4009_BE9A_D988E4C7386B__INCLUDED_)