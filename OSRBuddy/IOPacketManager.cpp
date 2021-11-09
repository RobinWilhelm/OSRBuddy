#include "IOPacketManager.h"
#include "SDK/AtumProtocol.h"	
#include "OSRAPI.h"
#include "OSRBuddyDefine.h"

#ifdef OSRBUDDY_DEBUG
#define DEBUG_INCREMENT(x) (x)++
#else
#define DEBUG_INCREMENT(x) (x)++
#endif



IOPacketManager::IOPacketManager()
{
	m_delete_sent = 0;
	m_sell_sent = 0;
	m_randombox_open_sent = 0;
	ZeroMemory(&m_debug_info, sizeof(PacketDebugLog));
}

bool IOPacketManager::OnReadPacket(unsigned short msgtype, byte* packet)
{
	DEBUG_INCREMENT(m_debug_info.total_recieved);
	switch (msgtype)
	{
	case T_FC_ITEM_USE_ENERGY_OK:
		{
			MSG_FC_ITEM_USE_ENERGY_OK* msg = (MSG_FC_ITEM_USE_ENERGY_OK*)packet;
			SetWaitingUseItem(msg->ItemNum, false);
		}
		break;
	case T_FC_ITEM_USE_ITEM_OK:
		{
			MSG_FC_ITEM_USE_ITEM_OK* msg = (MSG_FC_ITEM_USE_ITEM_OK*)packet;
			SetWaitingUseItem(msg->ItemNum, false);
		}
		break;
	// special case for ammoboxes
	// they dont get an OK message but these two messages:
	//case T_FC_BATTLE_PRI_BULLET_RELOADED:
	case T_FC_BATTLE_SEC_BULLET_RELOADED:
		{
			MSG_FC_BATTLE_PRI_BULLET_RELOADED* reloaded_msg = (MSG_FC_BATTLE_PRI_BULLET_RELOADED*)packet;
			if (reloaded_msg->RechargeType == BULLET_RECHARGE_TYPE_BULLET_ITEM) 
			{
				SetWaitingUseItem(TO_INT(ItemNumber::AmmunitionRechargeBox), false);  	
			}  			
		}
		break;
	case T_FC_SKILL_USE_SKILL_OK:
		{
			MSG_FC_SKILL_USE_SKILL_OK* msg_use_skill = (MSG_FC_SKILL_USE_SKILL_OK*)packet;
			SetWaitingUseItem(msg_use_skill->SkillItemID.ItemNum, false);
		}
		break;
	case T_FC_SKILL_CANCEL_SKILL_OK:
		{
			MSG_FC_SKILL_CANCEL_SKILL_OK* msg_cancel_skill = (MSG_FC_SKILL_CANCEL_SKILL_OK*)packet;
			SetWaitingUseItem(msg_cancel_skill->SkillItemID.ItemNum, false);
		}
		break;
	case T_FC_STORE_UPDATE_ITEM_COUNT:
		{
			MSG_FC_STORE_UPDATE_ITEM_COUNT* msg = (MSG_FC_STORE_UPDATE_ITEM_COUNT*)packet;
			if (msg->ItemUpdateType == IUT_GENERAL && msg->ItemUniqueNumber == m_delete_sent) {
				m_delete_sent = 0;
			}

			if (msg->ItemUpdateType == IUT_SHOP && msg->ItemUniqueNumber == m_sell_sent) {
				m_sell_sent = 0;
			}

			if (msg->ItemUpdateType == IUT_RANDOMBOX && msg->ItemUniqueNumber == m_randombox_open_sent) {
				m_randombox_open_sent = 0;
			}
		}
	break;
	case T_FC_STORE_DELETE_ITEM:
		{
			MSG_FC_STORE_DELETE_ITEM* msg = (MSG_FC_STORE_DELETE_ITEM*)packet;
			if (msg->ItemDeletionType == IUT_GENERAL && msg->ItemUniqueNumber == m_delete_sent)	{
				m_delete_sent = 0;
			}

			if (msg->ItemDeletionType == IUT_SHOP && msg->ItemUniqueNumber == m_sell_sent) {
				m_sell_sent = 0;
			}

			if (msg->ItemDeletionType == IUT_RANDOMBOX && msg->ItemUniqueNumber == m_randombox_open_sent) {
				m_randombox_open_sent = 0;
			}
		}
		break;
	case T_FC_SKILL_CANCEL_PREPARE_OK:
		{
			MSG_FC_SKILL_CANCEL_PREPARE_OK* msg_cancel_skill = (MSG_FC_SKILL_CANCEL_PREPARE_OK*)packet;
			SetWaitingUseItem(msg_cancel_skill->SkillItemID.ItemNum, false);
		}
		break;
	case T_FC_SKILL_CONFIRM_USE_ACK:
		{
			MSG_FC_SKILL_CONFIRM_USE_ACK* msg_cancel_skill = (MSG_FC_SKILL_CONFIRM_USE_ACK*)packet;
			SetWaitingUseItem(msg_cancel_skill->UsingSkillItemNum, false);
		}
		break;
	case T_FC_SKILL_PREPARE_USE_OK:
		{
			MSG_FC_SKILL_PREPARE_USE_OK* msg_cancel_skill = (MSG_FC_SKILL_PREPARE_USE_OK*)packet;
			SetWaitingUseItem(msg_cancel_skill->SkillItemID.ItemNum, false);
		}
		break;
	case T_FC_SKILL_SETUP_SKILL_OK:
		{
			MSG_FC_SKILL_SETUP_SKILL_OK* msg_cancel_skill = (MSG_FC_SKILL_SETUP_SKILL_OK*)packet;
			SetWaitingUseItem(msg_cancel_skill->ItemSkill.ItemNum, false);
		}
		break;
	case T_FC_SKILL_INVALIDATE_SKILL:
		{
			MSG_FC_SKILL_INVALIDATE_SKILL* msg_cancel_skill = (MSG_FC_SKILL_INVALIDATE_SKILL*)packet;
			SetWaitingUseItem(msg_cancel_skill->SkillItemID.ItemNum, false);
		}
		break;
	break;

	case T_ERROR:
		DEBUG_INCREMENT(m_debug_info.errors_recieved);

		MSG_ERROR* msg = (MSG_ERROR*)packet;
		switch (msg->MsgType)
		{
		case T_FC_ITEM_USE_ENERGY: 
		case T_FC_SKILL_USE_SKILL:	
			{
				SetWaitingUseItemAll(false);
			}
			break;
		case T_FC_SHOP_SELL_ITEM:
			{
				m_sell_sent = 0;
			}
			break;
		case T_FC_ITEM_USE_RANDOMBOX:
			{
				switch (msg->ErrorCode)
				{
					// sometimes it happens that client and server are not anymore in sync with the inventory items	while trying to open capsules
					// idk for sure why this happens, but to fix it we can just remove the items from clientside that dont exist anymore on the server
				case ERR_PROTOCOL_NO_SUCH_ITEM:
					{
						//remove item directly from client side item list
						CStoreData* storedata = OSR_API->GetAtumApplication()->m_pShuttleChild->m_pStoreData;
						CMapItemInventoryIterator it = storedata->m_mapItemUniqueNumber.find(msg->ErrParam1);
						if (it != storedata->m_mapItemUniqueNumber.end())
						{
							CItemInfo* pItemInfo = it->second;
							storedata->m_mapItemUniqueNumber.erase(it);
							CMapItemWindowInventoryIterator it2 = storedata->m_mapItemWindowPosition.find(pItemInfo->ItemWindowIndex);
							if (it2 != storedata->m_mapItemWindowPosition.end())
							{
								storedata->m_mapItemWindowPosition.erase(it2);
							}
						}
					}
					break;
				}
				break;
			}
		}
		break;
	}
	return false;
}

bool IOPacketManager::OnWritePacket(unsigned short msgtype, byte* packet)
{
	switch (msgtype)
	{
	case T_FC_ITEM_USE_ENERGY:
		{
			MSG_FC_ITEM_USE_ENERGY* msg_use_energy = (MSG_FC_ITEM_USE_ENERGY*)packet;
			CItemInfo* item = OSR_API->FindItemInInventoryByUniqueNumber(msg_use_energy->ItemUniqueNumber);
			SetWaitingUseItem(item->ItemNum, true);

			DEBUG_INCREMENT(m_debug_info.use_energy_sent);
		}
		break;
	case T_FC_ITEM_USE_ITEM:
		{
			MSG_FC_ITEM_USE_ITEM* msg = (MSG_FC_ITEM_USE_ITEM*)packet;
			CItemInfo* item = OSR_API->FindItemInInventoryByUniqueNumber(msg->ItemUniqueNumber);
			SetWaitingUseItem(item->ItemNum, true);

			DEBUG_INCREMENT(m_debug_info.use_item_sent);
		}
		break;
	case T_FC_SKILL_USE_SKILL:
		{
			MSG_FC_SKILL_USE_SKILL* msg_use_skill = (MSG_FC_SKILL_USE_SKILL*)packet;  		
			SetWaitingUseItem(msg_use_skill->SkillItemID.ItemNum, true);
			DEBUG_INCREMENT(m_debug_info.use_skill_sent);
		}
		break;
	case T_FC_SKILL_CANCEL_SKILL:
		{
			MSG_FC_SKILL_CANCEL_SKILL* msg_cancel_skill = (MSG_FC_SKILL_CANCEL_SKILL*)packet;	
			SetWaitingUseItem(msg_cancel_skill->SkillItemID.ItemNum, true);
			DEBUG_INCREMENT(m_debug_info.cancel_skill_sent);
		}
		break;
	case T_FC_ITEM_THROW_AWAY_ITEM:
		{
			MSG_FC_ITEM_THROW_AWAY_ITEM* msg = (MSG_FC_ITEM_THROW_AWAY_ITEM*)packet;
			m_delete_sent = msg->ItemUniqueNumber;
			DEBUG_INCREMENT(m_debug_info.throw_away_item_sent);
		}
		break;
	case T_FC_SHOP_SELL_ITEM:
		{
			MSG_FC_SHOP_SELL_ITEM* msg = (MSG_FC_SHOP_SELL_ITEM*)packet;
			m_sell_sent = msg->ItemUniqueNumber;
			DEBUG_INCREMENT(m_debug_info.sell_item_sent);
		}
		break;
	case T_FC_ITEM_USE_RANDOMBOX:
		{
			MSG_FC_ITEM_USE_RANDOMBOX* msg = (MSG_FC_ITEM_USE_RANDOMBOX*)packet;
			m_randombox_open_sent = msg->ItemUID;
			DEBUG_INCREMENT(m_debug_info.use_randombox_sent);
		}
		break;
	}

	DEBUG_INCREMENT(m_debug_info.total_sent);
    return false;
}

bool IOPacketManager::UseItemWaitingOk(int itemnumber)
{
	auto entry = m_useitem_packetstate.find(itemnumber);
	if (entry != m_useitem_packetstate.end()) {
		return entry->second;
	}
	else {
		return false;
	}
}

void IOPacketManager::SetWaitingUseItem(int itemnumber, bool waiting)
{
	auto entry = m_useitem_packetstate.find(itemnumber);
	if (entry != m_useitem_packetstate.end()) {
		entry->second = waiting;
	}
	else {
		m_useitem_packetstate.insert({ itemnumber, waiting });
	}
}

void IOPacketManager::SetWaitingUseItemAll(bool waiting)
{
	for (auto& item : m_useitem_packetstate) {
		item.second = waiting;
	}
}

PacketDebugLog IOPacketManager::GetDebugInfo()
{
	return m_debug_info;  	  	
}
