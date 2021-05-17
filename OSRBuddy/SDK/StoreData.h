// StoreData.h: interface for the CStoreData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_)
#define AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
struct struInfluenceWarBackupWaingInfo
{
	UID64_t		UniqueNumber;					// ������ ������ȣ
	INT			nRealItemNum;					// ���� ������ ��ȣ
	INT			nInfluenceItemNum;				// ������ ������ ��ȣ
};
// end 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�

// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
//class CINFInven;
class CINFInvenExtend;
// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
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
	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
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
		// m_mapItemWindowPosition�� ����ִ� �ε����� ã�´�.
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

	//	CMapItemInInventoryList	m_mapItemInInventory;	// ������ �κ��丮
	CMapItemWindowInventory	m_mapItemWindowPosition;  	
	CMapItemInventory		m_mapItemUniqueNumber;		// new ������ �κ��丮
		
	CMapItemWindowInventory	m_mapItemWindowPositionBackUp;	
	CMapItemInventory		m_mapItemUniqueNumberBackUp;		// new ������ �κ��丮
	
protected:

	//	CMapItemEnchantList		m_mapEnchantItem;		// ��æƮ ������ ����
	float					m_fWeight;
	BOOL					m_bTutorialBackUp;		// 2007-07-02 by dgwoo Ʃ�丮��� ���������� �����Ͽ��°�.?

	// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
	BYTE					m_byMarkInfluence;
	struInfluenceWarBackupWaingInfo	m_struInfluenceWarBackupWaingInfo;
	BOOL					m_bInfluenceMarkWar;

	// deleted
	//	VOID	SetItemNumber(UINT uniqueNumber, int itemNumber);

		// 2009-01-12 by bhsohn �Ϻ� �߰� ��������
		// ä�� ǥ�� ���緮
	float					m_fGearChatWeight;
	BOOL					m_bRqChangeItemPos;
	// end 2009-01-12 by bhsohn �Ϻ� �߰� ��������

};

#endif // !defined(AFX_STOREDATA_H__0D996EFC_1166_485D_9F11_608DD1565445__INCLUDED_)
