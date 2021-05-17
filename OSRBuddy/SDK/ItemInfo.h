// ItemInfo.h: interface for the CItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMINFO_H__1B0BB4FA_5A16_4585_8186_2F1C911EE29C__INCLUDED_)
#define AFX_ITEMINFO_H__1B0BB4FA_5A16_4585_8186_2F1C911EE29C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




// 2010. 02. 11 by ckPark �ߵ��� ����������
struct ENCHANT_PARAM
{
	DestParam_t		m_nDesParam;		// �����Ķ�
	ParamValue_t	m_fDesValue;		// �����Ķ� ��

	ENCHANT_PARAM(DestParam_t nDesParam = 0, ParamValue_t fDesValue = 0.0f) : m_nDesParam(nDesParam), m_fDesValue(fDesValue)
	{

	}
};
// end 2010. 02. 11 by ckPark �ߵ��� ����������

///////////////////////////////////////////////////////////////////////////////
/// \class		CItemInfo
///
/// \brief		������(������ ���� ����ũ�ѹ� ����)�� ���� ���̺�
///				CStoreData�� m_mapItemInInventory�� �� ������ ��� �־�� �Ѵ�. 
/// \author		dhkwon
/// \version	
/// \date		2004-06-14 ~ 2004-06-14
/// \warning	
///////////////////////////////////////////////////////////////////////////////
class CItemInfo : public ITEM_GENERAL
{
public:
	CItemInfo(ITEM_GENERAL* pItem);
	virtual ~CItemInfo();	  	

public:
	RARE_ITEM_INFO* m_pRefPrefixRareInfo;
	RARE_ITEM_INFO* m_pRefSuffixRareInfo;
	CParamFactor* m_pEnchantParamFactor;
	int				m_nEnchantNumber;
	CParamFactor* m_pAllParamFactor;
	ITEM* m_pItemInfo;			// m_pAllParamFactor �� ����� ������

	float			m_fItemPassTime;		// 2006-03-31 by ispark, �ð����� ������ ����� �ð�
	int				m_nReUsable;			// �� ���ð�.
	BOOL			m_bUse;					// ����Ҽ� �ִ� �����ΰ�?

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	INT				m_nCoolElapsedTime;		// ��Ÿ��

	std::vector<ENCHANT_PARAM> m_vecDefEnchant;		// �⺻ ��æƮ ����Ʈ

	std::vector<ENCHANT_PARAM> m_vecInvokeEnchant;	// �ߵ��� ��æƮ ����Ʈ
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	// 2010-06-15 by shcho&hslee ��ý��� - �ŷ� ����
	int				m_nPetLevel;
	BOOL			m_bReName;
	BOOL			m_bEnableLevelUp;
	Experience_t	m_dPetExp;
	// end 2010-06-15 by shcho&hslee ��ý��� - �ŷ� ����

};

#endif // !defined(AFX_ITEMINFO_H__1B0BB4FA_5A16_4585_8186_2F1C911EE29C__INCLUDED_)
