#pragma once
#include <Windows.h>

class IPacketWatcher
{
	friend class OSRBuddyMain;
public:
	virtual bool OnReadPacket(unsigned short msgtype, byte* packet) { return false; };
	virtual bool OnWritePacket(unsigned short msgtype, byte* packet) { return false; };
};

