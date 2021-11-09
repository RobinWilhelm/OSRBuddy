#pragma once
#include "Utility.h"
#include <exception>
#include <vector>
#include "OSRBuddyDefine.h"

#define OFFSET_ATUMAPPLICATION	(0x47D230)	//			
#define OFFSET_DATABASE			OFFSET_ATUMAPPLICATION - 0x20
#define OFFSET_STOREDATA		OFFSET_ATUMAPPLICATION - 0x2C
#define OFFSET_GAMEMAIN			OFFSET_ATUMAPPLICATION + 0x04
#define OFFSET_SHUTTLECHILD		OFFSET_ATUMAPPLICATION + 0x30
#define OFFSET_FIELDWINSOCKET	OFFSET_ATUMAPPLICATION - 0x50

enum class OffsetIdentifier
{
	CINFCityLab__OnButtonClicked,
	CINFInvenExtend__SendUseItem,
	CINFCharacterInfoExtend__SendUseSkill,
	CINFCityLab__InvenToSourceItem,
	CAtumDatabase__GetServerRareItemInfo,
	Pointer_CD3DApplication,
	CAtumApplication__OnRecvFieldSocketMessage,
	CWinSocket__Write,
	CSkillInfo__ChangeSkillState,
	CAtumApplication__CalcObjectSourceScreenCoords,
	CINFInvenExtend__DeleteSelectItem,
	CINFInvenExtend__SendChangeWearWindowPos,
	CINFInven__SetSelectItem,
	CStoreData__UpdateItemCount,
};
		

struct PatternInfo
{
	OffsetIdentifier identifier;
	const char* pattern; // IDA style
	int offset;
	byte* address;
	int trampoline_length;
};

class PatternManager
{
public:
	static void Init()
	{
		m_patterninfos.push_back({ OffsetIdentifier::CINFCityLab__OnButtonClicked, "83 E8 00 74 ?? 83 E8 01 74 ?? 83 E8 01 0F 85 ?? ?? ?? ?? E8 ?? ?? ?? ?? E9" , -0x4C, nullptr, 6 } );
		m_patterninfos.push_back({ OffsetIdentifier::CINFInvenExtend__SendUseItem, "8B F1 89 B5 90 F3 FF FF 8B 7B 08 89 BD 94 F3 FF FF 0F B6 07 83 C0 EE 3D E7 00 00 00" , -0x41, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFCharacterInfoExtend__SendUseSkill, "A1 ?? ?? ?? ?? 53 8B 5D 08 56 83 B8 ?? ?? ?? ?? 00 57 89 ?? ?? ?? 74 ?? 8B 43 14 33 D2 83 C0 78" , -0x1A, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFCityLab__InvenToSourceItem, "8B D9 8A 4D 10 8B 7D 08 84 C9 0F 85 ?? ?? ?? ?? 8A 47 08 3C 15 0F 84 ?? ?? ?? ?? 3C 1B 0F 84" , -0x2E, nullptr, 5 });
		m_patterninfos.push_back({ OffsetIdentifier::CAtumDatabase__GetServerRareItemInfo, "53 55 56 57 33 FF 8B F1 39 BC ?? ?? ?? ?? ?? 0F 84 ?? ?? ?? ?? A1 ?? ?? ?? ?? 05 60 C2 02 00 50 FF 15" , -0x14, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::Pointer_CD3DApplication, "89 3D ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 04 50 E8 ?? ?? ?? ?? 83 C4 04 C7 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 20 03 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 58 02" , 2, nullptr, 0 });
		m_patterninfos.push_back({ OffsetIdentifier::CAtumApplication__OnRecvFieldSocketMessage, "8B F1 89 B5 EC F3 FF FF 8B 96 D0 C1 02 00 85 D2 0F 84 ?? ?? ?? ?? 81 ?? ?? E2 04 00 00 75" , -0x41, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CWinSocket__Write, "8B F9 83 7F 08 FF C7 45 F0 00 00 00 00 0F 84 ?? ?? ?? ?? 83 7F 14 00 0F 84 ?? ?? ?? ?? 68 E4 05 00 00 6A 40" , -0x28, nullptr, 5 });
		m_patterninfos.push_back({ OffsetIdentifier::CSkillInfo__ChangeSkillState, "8B 45 08 56 48 8B F1 89 74 24 18 57 83 F8 05 0F 87 ?? ?? ?? ?? FF 24 85", -0x1A, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CAtumApplication__CalcObjectSourceScreenCoords, "0F 11 44 24 14 53 66 0F 6E C8 8B C1 F7 D8 C7 44 24 3C 00 00 80 3F", -0x2D, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFInvenExtend__DeleteSelectItem, "56 8B F1 57 8B 86 98 01 00 00 8B BE 9C 01 00 00 85 C0 75 08 85 FF 0F 84 63 01 00 00", -0x1A, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFInvenExtend__SendChangeWearWindowPos, "85 D2 74 75 8A 42 3C 84 C0 74 28 3C 01 74 24 3C 02 74 20 3C 03 74 1C", -0x39, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFInven__SetSelectItem, "85 FF 74 51 83 BE 4C 07 00 00 00 75 7C 85 FF 74 44 8B 8E EC 00 00 00", -0x9, nullptr,7 });
		m_patterninfos.push_back({ OffsetIdentifier::CStoreData__UpdateItemCount, "53 8B 5D 0C 56 57 8B 7D 08 51 8D 4C 24 20", -0x12, nullptr,6 });


		uintptr_t ace_modulebase = (uintptr_t)GetModuleHandle("ACEonline.atm");
		if (!ace_modulebase) {
			throw std::exception("Module ACEonline.atm not found");
		}

		size_t ace_module_size = Utility::GetModuleSize((HMODULE)ace_modulebase);
		const PBYTE rangeStart = (PBYTE)ace_modulebase;
		const PBYTE rangeEnd = (PBYTE)(ace_modulebase + ace_module_size);


		for (auto& pinfo : m_patterninfos)
		{
			pinfo.address = Utility::FindPattern(rangeStart, rangeEnd, pinfo.pattern);
			if (!pinfo.address)
			{
				std::string msg = "Pattern not found: " + std::to_string(TO_INT(pinfo.identifier));
				throw std::exception(msg.c_str());
			}

			pinfo.address += pinfo.offset;
		}									   
	}

	static PatternInfo Get(OffsetIdentifier identifier)
	{
		for (auto& pattern : m_patterninfos)
		{
			if (pattern.identifier == identifier) {
				return pattern;
			}
		}		
		std::string msg = "Offset not found: " + std::to_string(TO_INT(identifier));
		throw std::exception(msg.c_str());
	}

private:
	static std::vector<PatternInfo> m_patterninfos;
};


