// StoreData.h: interface for the CStoreData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_)
#define AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 2008-08-19 by bhsohn 세력 마크 시스템 추가
struct struInfluenceWarBackupWaingInfo
{
	UID64_t		UniqueNumber;					// 아이템 고유번호
	INT			nRealItemNum;					// 기존 아이템 번호
	INT			nInfluenceItemNum;				// 세력전 아이템 번호
};
// end 2008-08-19 by bhsohn 세력 마크 시스템 추가

// 2008-08-22 by bhsohn EP3 인벤토리 처리
//class CINFInven;
class CINFInvenExtend;
// end 2008-08-22 by bhsohn EP3 인벤토리 처리
class CINFTrade;
///////////////////////////////////////////////////////////////////////////////
/// \class		CStoreData
///
/// \brief		Item table, enchant, store
/// \author		dhkwon
/// \version	
/// \date		2004-04-28 ~ 2004-04-28
/// \warning	
///////////////////////////////////////////////////////////////////////////////
class CStoreData
{
	// 2008-08-22 by bhsohn EP3 인벤토리 처리
	//friend CINFInven;
	friend CINFInvenExtend;
	friend CINFTrade;
public:
	CStoreData();
	virtual ~CStoreData();

	

	CItemInfo* FindItemInInventoryByItemNum(INT nItemNum)
	{
		//CMapItemWindowInventoryIterator it = m_mapItemUniqueNumber.begin();
		CMapItemInventoryIterator it = m_mapItemUniqueNumber.begin();
		while (it != m_mapItemUniqueNumber.end())
		{
			if (it->second->ItemNum == nItemNum)
			{
				return it->second;
			}
			it++;
		}
		return NULL;
	}

public:
	int SearchEmpty()
	{
		// m_mapItemWindowPosition의 비어있는 인덱스를 찾는다.
		int InventoryIndex = POS_ITEMWINDOW_OFFSET;

		for (;;)
		{
			if (m_mapItemWindowPosition.find(InventoryIndex) == m_mapItemWindowPosition.end())
				return InventoryIndex;

			InventoryIndex++;
		}

		return 0;
	}

	CItemInfo* unknown;
#ifndef _DEBUG
	char m_padMap[8];
#endif // _DEBUG

	//	CMapItemInInventoryList	m_mapItemInInventory;	// 아이템 인벤토리
	CMapItemWindowInventory	m_mapItemWindowPosition;  	
	CMapItemInventory		m_mapItemUniqueNumber;		// new 아이템 인벤토리
		
	CMapItemWindowInventory	m_mapItemWindowPositionBackUp;	
	CMapItemInventory		m_mapItemUniqueNumberBackUp;		// new 아이템 인벤토리
	
protected:

	//	CMapItemEnchantList		m_mapEnchantItem;		// 인챈트 아이템 정보
	float					m_fWeight;
	BOOL					m_bTutorialBackUp;		// 2007-07-02 by dgwoo 튜토리얼용 아이템으로 셋팅하였는가.?

	// 2008-08-19 by bhsohn 세력 마크 시스템 추가
	BYTE					m_byMarkInfluence;
	struInfluenceWarBackupWaingInfo	m_struInfluenceWarBackupWaingInfo;
	BOOL					m_bInfluenceMarkWar;

	// deleted
	//	VOID	SetItemNumber(UINT uniqueNumber, int itemNumber);

		// 2009-01-12 by bhsohn 일본 추가 수정사항
		// 채팅 표시 적재량
	float					m_fGearChatWeight;
	BOOL					m_bRqChangeItemPos;
	// end 2009-01-12 by bhsohn 일본 추가 수정사항

};

#endif // !defined(AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_)
