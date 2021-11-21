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
	
	m_name = AceColouredString(m_item_info->m_pItemInfo->ItemName);
	if (m_item_info->m_pRefPrefixRareInfo)
	{
	 	m_prefix = AceColouredString(m_item_info->m_pRefPrefixRareInfo->Name, ImColor(0x00, 0xFF, 0x00));
	}
	else 
	{
		m_prefix.Clear();
	}

	if (m_item_info->m_pRefSuffixRareInfo)
	{
		m_suffix = AceColouredString(m_item_info->m_pRefSuffixRareInfo->Name, ImColor(0x00, 0xFF, 0x00));
	}
	else
	{
		m_suffix.Clear();
	}
	m_enchant_count_string = "E:" + std::to_string(m_item_info->m_nEnchantNumber);	  	
	return true;
}

bool OsrItemInfo::UpdateItemInfo()
{  
	CItemInfo* iinfo = OSR_API->FindItemInInventoryByUniqueNumber(m_UID);
	if (!iinfo) {
		iinfo = OSR_API->FindItemFromTarget(m_UID);
		if (!iinfo) {
			iinfo = OSR_API->FindItemFromSource(m_UID);
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
	return m_name.GetCleanText();
}

std::string OsrItemInfo::GetCleanPrefixName() const
{
	return m_prefix.GetCleanText();
}

std::string OsrItemInfo::GetCleanSuffixName() const
{
	return m_suffix.GetCleanText();
}

std::string OsrItemInfo::GetEnchantText() const
{
	return m_enchant_count_string;
}

ImColor OsrItemInfo::GetItemNameColor() const
{
	return m_name.GetColor();
}

ImColor OsrItemInfo::GetPrefixColor() const
{
	return m_prefix.GetColor();
}

ImColor OsrItemInfo::GetSuffixColor() const
{
	return m_suffix.GetColor();
}

void OsrItemInfo::RenderImGui() const
{	
	if (GetUID() == 0) {
		return;
	}

	if (IsWeapon() && !GetCleanPrefixName().empty())
	{
		m_prefix.RenderImGui();
#ifdef RELEASE_DEBUG
		if (m_item_info->m_pRefPrefixRareInfo)
		{
			ImGui::SameLine();
			ImGui::Text(std::to_string(m_item_info->m_pRefPrefixRareInfo->CodeNum).c_str());
		}
#endif
		ImGui::SameLine();
	}

	m_name.RenderImGui();
	ImGui::SameLine();

	if (IsWeapon() || IsArmor())
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0xFF, 0xBB, 0x33).Value);
		ImGui::Text(GetEnchantText().c_str());
		ImGui::PopStyleColor();
	}

	if (IsWeapon() && !GetCleanSuffixName().empty())
	{
		ImGui::SameLine();
		m_suffix.RenderImGui();
#ifdef RELEASE_DEBUG
		if (m_item_info->m_pRefSuffixRareInfo)
		{
			ImGui::SameLine();
			ImGui::Text(std::to_string(m_item_info->m_pRefSuffixRareInfo->CodeNum).c_str());
		}
#endif
	}
}
