#include "pch.h"
#include ".\Soulworker Packet\SWPacket.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Damage Meter\MySQLite.h"
#include ".\Soulworker Packet\SWPacketOtherUseSkill.h"
#include ".\UI\UtillWindow.h"

SWPacketOtherUseSkill::SWPacketOtherUseSkill(SWHEADER* swheader, BYTE* data) : SWPacket(swheader, data) {

}

VOID SWPacketOtherUseSkill::Do() {
	//	SWPACKETCHAT_HEADER* chat_header = (SWPACKETCHAT_HEADER*)(_data + sizeof(SWHEADER));

	//	BYTE* p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETCHAT_HEADER);

	SWPACKET_OTHERUSESKILL* otherSkill = (SWPACKET_OTHERUSESKILL*)(_data + sizeof(SWHEADER));

	DAMAGEMETER.AddSkillUsed(otherSkill->_playerId, otherSkill->_skillId);

	UINT32 userId = otherSkill->_playerId;
	if (!DAMAGEMETER.CheckPlayer(userId)) {
		UINT32 ownerId = DAMAGEMETER.GetOwnerID(userId);
		if (!DAMAGEMETER.CheckPlayer(ownerId)) {
			SW_DB2_STRUCT* db = DAMAGEMETER.GetMonsterDB(userId);
			UINT32 db2 = 0;
			if (db != nullptr) {
				db2 = db->_db2;
			}

			if (db2 == 31310101) {
				//Log::MyLog(_T("1"));
				ZeroMemory(_skillName, SKILL_NAME_LEN);
			//	Log::MyLog(_T("2"));
				SWDB.GetSkillName(otherSkill->_skillId, _skillName, SKILL_NAME_LEN);
				//Log::MyLog(_T("3"));
				string test = u8"테네브리스가 [";
				test.append(_skillName);
				test.append(u8"]를 사용");
				UTILLWINDOW.AddLog(test);
				//Log::MyLog(test.c_str());
			}
		}
	}


}

VOID SWPacketOtherUseSkill::Log() {

}

VOID SWPacketOtherUseSkill::Debug() {

	//Log::MyLog(_T("UseSkill Packet\n"));
	//for (int i = sizeof(SWHEADER); i < _swheader->_size; i++)
	//	Log::MyLog(_T("%02x "), _data[i]);
	//Log::MyLog(_T("\n"));

	//SWPACKET_OTHERUSESKILL* otherSkill = (SWPACKET_OTHERUSESKILL*)(_data + sizeof(SWHEADER));

	//Log::MyLog(_T("id : %08x / skill : %u / x : %f / y : %f / z : %f\n"), otherSkill->_playerId, otherSkill->_skillId, otherSkill->_locationX, otherSkill->_locationY, otherSkill->_locationZ);

	//Log::MyLog(_T("Unknown01 : "));
	//for (int i = 0; i < sizeof(otherSkill->_unknown01); i++) {
	//	Log::MyLog(_T("%02x "), otherSkill->_unknown01[i]);
	//}
	//Log::MyLog(_T("\n"));


	//SWPACKETCHAT_HEADER* chat_header = (SWPACKETCHAT_HEADER*)(_data + sizeof(SWHEADER));

	//BYTE* p_data = _data + sizeof(SWHEADER) + sizeof(SWPACKETCHAT_HEADER);

	//WCHAR utf16[MAX_NAME_LEN] = { 0 };
	//memcpy_s(utf16, MAX_NAME_LEN * sizeof(WCHAR), p_data, chat_header->_chatSize);

	//CHAR utf8[MAX_NAME_LEN] = { 0 };
	//if (!UTF16toUTF8(utf16, utf8, MAX_NAME_LEN)) {
	//	//Log::WriteLog(const_cast<LPTSTR>(_T("Error in SWPacketChat : UTF16toUTF8 FAILED")));
	//	return;
	//}



	//Log::MyLog(const_cast<LPTSTR>(_T("[DEBUG] [CHAT] [ID %d] [ChatType = %d] [unknown1 = %02x] [unknown2 = %04x] [chatSize = %d] [chat = %s]\n")), 
	//chat_header->_playerID, chat_header->_chatType, chat_header->_unknown01, chat_header->_unknown02, chat_header->_chatSize, utf16);

}