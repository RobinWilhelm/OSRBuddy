#pragma once
#include "IPacketWatcher.h"
#include <unordered_map>
#include "SDK/AtumError.h"
#include "SDK/AtumParam.h"
#include <chrono>

#define PACKET_RESEND_ALLOW_TIME 300ms

struct PacketDebugLog
{
	unsigned int total_sent;
	unsigned int use_energy_sent;
	unsigned int use_item_sent;
	unsigned int use_skill_sent;
	unsigned int cancel_skill_sent;
	unsigned int throw_away_item_sent;
	unsigned int sell_item_sent;
	unsigned int use_randombox_sent;
	unsigned int change_window_postion_sent;

	unsigned int errors_recieved;
	unsigned int total_recieved;
};

class IOPacketManager : public IPacketWatcher
{
public:
	IOPacketManager();

	virtual bool OnReadPacket(unsigned short msgtype, byte* packet) override;
	virtual bool OnWritePacket(unsigned short msgtype, byte* packet) override;

	bool UseItemWaitingOk(int itemnumber);
	void SetWaitingUseItem(int itemnumber, bool waiting);

	bool SellItemWaitingOk() { return m_sell_sent != 0; };
	bool DeleteItemWaitingOk() { return m_delete_sent != 0; };
	bool OpenRandomBoxWaitingOk() { return m_randombox_open_sent != 0; };
	bool ChangeWindowPositionWaitingOk() { return m_change_window_position_sent != 0; };

	void SetWaitingUseItemAll(bool waiting);

	PacketDebugLog GetDebugInfo();

private:
	struct PacketState
	{
		bool waiting;
		std::chrono::system_clock::time_point last_send;
	};

	std::unordered_map<int, PacketState> m_useitem_packetstate;
	UID64_t m_delete_sent; // unique item number of the last sent delete item packet
	UID64_t m_sell_sent;	// unique item number of the last sent sell item packet
	UID64_t m_randombox_open_sent;
	UID64_t m_change_window_position_sent;

	PacketDebugLog m_debug_info;
};