#include "pch.h"
#include ".\Soulworker Packet\SWSPacketMySkillUsed.h"
#include ".\Damage Meter\Damage Meter.h"

SWSPacketMySkillUsed::SWSPacketMySkillUsed(SWSHEADER* swheader, BYTE* data) {
	_swheader = swheader;
	_data = data;
}

VOID SWSPacketMySkillUsed::Do() {
	SWPACKET_MYSKILLUSED* skillUsed = (SWPACKET_MYSKILLUSED*)(_data + sizeof(SWSHEADER));

	DAMAGEMETER.AddSkillUsed(skillUsed->_playerId, skillUsed->_skillId);

	//Log::MyLog(_T("skillId : %u / playerId : %08x / x : %f / y : %f / z : %f / direct : %f")
	//	, skillUsed->_skillId, skillUsed->_playerId, skillUsed->_locationX, skillUsed->_locationY, skillUsed->_locationZ, skillUsed->_direction);
	return;
}

VOID SWSPacketMySkillUsed::Log() {
	return;
}

VOID SWSPacketMySkillUsed::Debug() {
	return;
}