#include "OsrItemInfo.h"
#include "OSRAPI.h"
#include "OSRImGuiMenu.h" 



OsrItemInfo::OsrItemInfo()
{
}

OsrItemInfo::OsrItemInfo(UID64_t uid)
{
	Update(uid);
}

OsrItemInfo::~OsrItemInfo()
{

}

bool OsrItemInfo::Update(UID64_t uid)
{
	if (uid != 0) {
		m_UID = uid;
	}  

	if (!UpdateItemInfo()) 
	{
		m_UID = 0;
		return false;
	}
			   
	m_clean_item_name = std::string(m_item_info->m_pItemInfo->ItemName);
	if (m_clean_item_name[0] == '\\')  // check if name has a colorcode in its name
	{
		m_name_color = OSRImGuiMenu::TranslateAceCharToColor(m_clean_item_name[1]);
		m_clean_item_name.erase(m_clean_item_name.begin(), m_clean_item_name.begin() + 2);
		//m_clean_item_name.erase(m_clean_item_name.end() - 2, m_clean_item_name.end());
	}
	else
	{
		m_name_color = 0xFFFFFFFF;
	}

	// determine the prefix and suffix colors
	if (m_item_info->m_pRefPrefixRareInfo)
	{
		m_clean_prefix_name = std::string(m_item_info->m_pRefPrefixRareInfo->Name);

		if (m_item_info->m_pRefPrefixRareInfo->Name[0] == '\\')  // check if prefix has a colorcode in its name
		{
			m_prefix_color = OSRImGuiMenu::TranslateAceCharToColor(m_item_info->m_pRefPrefixRareInfo->Name[1]);
			m_clean_prefix_name.erase(m_clean_prefix_name.begin(), m_clean_prefix_name.begin() + 2);
			m_clean_prefix_name.erase(m_clean_prefix_name.end() - 2, m_clean_prefix_name.end());
		}
		else
		{
			m_prefix_color = OSRImGuiMenu::TranslateAceCharToColor('g');
		}

		m_clean_prefix_name += " (" + std::to_string(m_item_info->m_pRefPrefixRareInfo->CodeNum) + ")";
	}
	else {
		m_clean_prefix_name.clear();
	}

	if (m_item_info->m_pRefSuffixRareInfo)
	{
		m_clean_suffix_name = std::string(m_item_info->m_pRefSuffixRareInfo->Name);

		if (m_item_info->m_pRefSuffixRareInfo->Name[0] == '\\')  // check if prefix has a colorcode in its name
		{
			m_suffix_color = OSRImGuiMenu::TranslateAceCharToColor(m_item_info->m_pRefSuffixRareInfo->Name[1]);
			m_clean_suffix_name.erase(m_clean_suffix_name.begin(), m_clean_suffix_name.begin() + 2);
			m_clean_suffix_name.erase(m_clean_suffix_name.end() - 2, m_clean_suffix_name.end());
		}
		else
		{
			m_suffix_color = OSRImGuiMenu::TranslateAceCharToColor('g');
		}

		m_clean_suffix_name += " (" + std::to_string(m_item_info->m_pRefSuffixRareInfo->CodeNum) + ")";
	}
	else {
		m_clean_suffix_name.clear();
	}

	m_enchant_count_string = "E:" + std::to_string(m_item_info->m_nEnchantNumber);	  	
	return true;
}

bool OsrItemInfo::UpdateItemInfo()
{  
	CItemInfo* iinfo = OSR_API->FindItemFromSource(m_UID);
	if (!iinfo) {
		iinfo = OSR_API->FindItemFromSource(m_UID);
		if (!iinfo) {
			iinfo = OSR_API->FindItemInInventoryByUniqueNumber(m_UID);
			if (!iinfo) {
				return false;
			}
		}
	}

	m_item_info = iinfo;
	return true;
}

bool OsrItemInfo::IsWeapon() const
{
	if (!m_item_info)
		return false;

	return IS_WEAPON(m_item_info->Kind);
}

bool OsrItemInfo::IsArmor() const
{
	return m_item_info->Kind == ITEMKIND_DEFENSE;
}

UID64_t OsrItemInfo::GetUID()  const
{
	return m_UID;
}

CItemInfo* OsrItemInfo::GetItemInfo()  const
{
	return m_item_info;
}

std::string OsrItemInfo::GetCleanName() const
{
	return m_clean_item_name;
}

std::string OsrItemInfo::GetCleanPrefixName() const
{
	return m_clean_prefix_name;
}

std::string OsrItemInfo::GetCleanSuffixName() const
{
	return m_clean_suffix_name;
}

std::string OsrItemInfo::GetEnchantText() const
{
	return m_enchant_count_string;
}

ImColor OsrItemInfo::GetItemNameColor() const
{
	return m_name_color;
}

ImColor OsrItemInfo::GetPrefixColor() const
{
	return m_prefix_color;
}

ImColor OsrItemInfo::GetSuffixColor() const
{
	return m_suffix_color;
}
