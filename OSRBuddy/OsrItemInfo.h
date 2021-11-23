#pragma once
#include "ImGuiBase.h"
#include "AceColouredString.h"

#include "SDK/AtumParam.h"

#include <string>

class CItemInfo;

class OsrItemInfo
{
public:
	OsrItemInfo();
	OsrItemInfo(UID64_t uid);
	~OsrItemInfo();

	bool Update(UID64_t uid = 0);
	bool UpdateItemInfo();

	bool IsWeapon() const;
	bool IsArmor() const;

	UID64_t GetUID() const;
	CItemInfo* GetItemInfo() const;

	std::string GetCleanName() const;			  
	std::string GetCleanPrefixName() const;
	std::string GetCleanSuffixName() const;
	std::string GetEnchantText() const;

	ImColor GetItemNameColor() const;
	ImColor GetPrefixColor() const;
	ImColor GetSuffixColor() const;

	void RenderImGui() const;

private:
	UID64_t		m_UID;
	CItemInfo*	m_item_info;
	std::string m_clean_item_name;
	ImColor		m_name_color;

	std::string	m_clean_prefix_name;
	std::string	m_clean_suffix_name;
	ImColor		m_prefix_color;
	ImColor		m_suffix_color;
							   
	AceColouredString m_name;
	AceColouredString m_prefix;
	AceColouredString m_suffix;

	std::string	m_enchant_count_string;
};