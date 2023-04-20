#pragma once
#include "Utility.h"
#include "OSRBuddyDefine.h"

#include <exception>
#include <vector>

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
	CAtumDatabase__GetServerItemInfo,
	CINFCommuPartyInvite__RqInvitePartyInfo,
	CAtumApplication__OnRecvIMSocketMessage, 
	CWSlowData__SendFieldSocketBattleAttackEvasion,
	CWeaponMissileData__CheckWeaponCollision,
	CWeaponRocketData__CheckWeaponCollision,
	CWeaponMissileData__CheckTargetByBomb
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
		m_patterninfos.push_back({ OffsetIdentifier::CINFCityLab__OnButtonClicked, "83 E8 00 74 ?? 83 E8 01 74 ?? 83 E8 01 0F 85 ?? ?? ?? ?? E8 ?? ?? ?? ?? E9" , -0x29, nullptr, 6 } );
		m_patterninfos.push_back({ OffsetIdentifier::CINFInvenExtend__SendUseItem, "8B BC 24 7C 0C 00 00 8B E9 0F B6 47 04 83 C0 EE 3D E7 00 00 00" , -0x18, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFCharacterInfoExtend__SendUseSkill, "A1 ?? ?? ?? ?? 53 8B 5D 08 56 83 B8 6C C6 02 00 00 57 ?? ?? 8B 43 08" , -0x1A, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFCityLab__InvenToSourceItem, "53 56 57 50 8D 45 F4 64 A3 00 00 00 00 8B F9 8A 4D 10 8B 75 08 84 C9" , -0x21, nullptr, 5 });
		//m_patterninfos.push_back({ OffsetIdentifier::CAtumDatabase__GetServerRareItemInfo, "53 55 56 57 33 FF 8B F1 39 BC ?? ?? ?? ?? ?? 0F 84 ?? ?? ?? ?? A1 ?? ?? ?? ?? 05 60 C2 02 00 50 FF 15" , -0x14, nullptr, 6 }); no need for now
		m_patterninfos.push_back({ OffsetIdentifier::Pointer_CD3DApplication, "83 C4 04 50 E8 9B F7 2C 00 C7 87 BC BA 02 00 00 00 00 00 8D 87 30 DB 02 00 83 C4 04 C7 87" , -0x9, nullptr, 0 });
		m_patterninfos.push_back({ OffsetIdentifier::CAtumApplication__OnRecvFieldSocketMessage, "56 57 50 8D 45 F4 64 A3 00 00 00 00 8B F9 89 BD 64 F8 FF FF 8B 8F D4 C1 02 00" , -0x35, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CWinSocket__Write, "8B F9 83 7F 08 FF C7 45 F0 00 00 00 00 0F 84 ?? ?? ?? ?? 83 7F 14 00 0F 84 ?? ?? ?? ?? 68 E4 05 00 00 6A 40" , -0x28, nullptr, 5 });
		m_patterninfos.push_back({ OffsetIdentifier::CSkillInfo__ChangeSkillState, "8B 45 08 56 48 8B F1 89 74 24 10 57 83 F8 05", -0x1A, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CAtumApplication__CalcObjectSourceScreenCoords, "66 0F 6E C8 8B C1 F7 D8", -0x3D, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFInvenExtend__DeleteSelectItem, "56 8B F1 57 8B 86 98 01 00 00 8B BE 9C 01 00 00 85 C0 75 08 85 FF 0F 84 63 01 00 00", -0x1A, nullptr, 6 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFInvenExtend__SendChangeWearWindowPos, "85 D2 74 75 8A 42 3C 84 C0 74 28 3C 01 74 24 3C 02 74 20 3C 03 74 1C", -0x39, nullptr, 6 });
		//m_patterninfos.push_back({ OffsetIdentifier::CINFInven__SetSelectItem, "85 FF 74 51 83 BE 4C 07 00 00 00 75 7C 85 FF 74 44 8B 8E EC 00 00 00", -0x9, nullptr,7 }); no need
		m_patterninfos.push_back({ OffsetIdentifier::CStoreData__UpdateItemCount, "53 8B 5D 08 56 89 44 24 10 8D 71 1C 57 8D 44 24 10", -0x12, nullptr,6 });
		m_patterninfos.push_back({ OffsetIdentifier::CAtumDatabase__GetServerItemInfo, "8D 44 24 24 50 8D 44 24 18 50 8D 4B 14 E8", -0x26, nullptr,8 });
		m_patterninfos.push_back({ OffsetIdentifier::CINFCommuPartyInvite__RqInvitePartyInfo, "8B 41 5C 3B 41 60 74 03 89 41 60 8B 41 68", -0x2E, nullptr,5 });
		m_patterninfos.push_back({ OffsetIdentifier::CAtumApplication__OnRecvIMSocketMessage, "8B F1 89 B5 EC F1 FF FF 8B 86 DC C1 02 00 85 C0", -0x41, nullptr,6 });
		m_patterninfos.push_back({ OffsetIdentifier::CWSlowData__SendFieldSocketBattleAttackEvasion, "89 84 24 0C 06 00 00 66 8B 84 24 18 06 00 00", -0xD, nullptr,6 });
		m_patterninfos.push_back({ OffsetIdentifier::CWeaponRocketData__CheckWeaponCollision, "8B F9 89 44 24 18 89 44 24 20 0F B7 82 D8 08 00 00", -0x20, nullptr,6 });
		m_patterninfos.push_back({ OffsetIdentifier::CWeaponMissileData__CheckWeaponCollision, "89 4C 24 10 89 4C 24 18 8B 0D 28 79 AB 00", -0x1B, nullptr,6 });
		m_patterninfos.push_back({ OffsetIdentifier::CWeaponMissileData__CheckTargetByBomb, "F3 0F 11 4C 24 24 8B D9 89 5C 24 18", -0x18, nullptr, 6 });

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


