// ItemInfo.h: interface for the CItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMINFO_H__1B0BB4FA_5A16_4585_8186_2F1C911EE29C__INCLUDED_)
#define AFX_ITEMINFO_H__1B0BB4FA_5A16_4585_8186_2F1C911EE29C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




// 2010. 02. 11 by ckPark 발동류 장착아이템
struct ENCHANT_PARAM
{
	DestParam_t		m_nDesParam;		// 데스파람
	ParamValue_t	m_fDesValue;		// 데스파람 값

	ENCHANT_PARAM(DestParam_t nDesParam = 0, ParamValue_t fDesValue = 0.0f) : m_nDesParam(nDesParam), m_fDesValue(fDesValue)
	{

	}
};
// end 2010. 02. 11 by ckPark 발동류 장착아이템

///////////////////////////////////////////////////////////////////////////////
/// \class		CItemInfo
///
/// \brief		아이템(유저가 가진 유니크넘버 구분)의 정보 테이블
///				CStoreData의 m_mapItemInInventory는 이 정보를 들고 있어야 한다. 
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
	ITEM* m_pItemInfo;			// m_pAllParamFactor 가 적용된 아이템

	float			m_fItemPassTime;		// 2006-03-31 by ispark, 시간제한 아이템 경과된 시간
	int				m_nReUsable;			// 재 사용시간.
	BOOL			m_bUse;					// 사용할수 있는 상태인가?

	// 2010. 02. 11 by ckPark 발동류 장착아이템
	INT				m_nCoolElapsedTime;		// 쿨타임

	std::vector<ENCHANT_PARAM> m_vecDefEnchant;		// 기본 인챈트 리스트

	std::vector<ENCHANT_PARAM> m_vecInvokeEnchant;	// 발동류 인챈트 리스트
	// end 2010. 02. 11 by ckPark 발동류 장착아이템

	// 2010-06-15 by shcho&hslee 펫시스템 - 거래 툴팁
	int				m_nPetLevel;
	BOOL			m_bReName;
	BOOL			m_bEnableLevelUp;
	Experience_t	m_dPetExp;
	// end 2010-06-15 by shcho&hslee 펫시스템 - 거래 툴팁

};

#endif // !defined(AFX_ITEMINFO_H__1B0BB4FA_5A16_4585_8186_2F1C911EE29C__INCLUDED_)
