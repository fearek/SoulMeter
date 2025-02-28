#include "pch.h"
#include ".\Buff Meter\Buff.h"
#include ".\Buff Meter\Buff Meter.h"

_PLAYERBUFF::_PLAYERBUFF(UINT32 playerID, USHORT buffid, BYTE stack) : _playerID(playerID) {
	_buffInfo.push_back(new Buff(buffid, stack));
}

_PLAYERBUFF::~_PLAYERBUFF(){

	for (auto itr = _buffInfo.begin(); itr != _buffInfo.end(); itr++)
		delete *itr;

	_buffInfo.clear();
}

VOID _PLAYERBUFF::AddBuff(USHORT buffid, BYTE stack) {
	
	BOOL find = FALSE;

	for (auto itr = _buffInfo.begin(); itr != _buffInfo.end(); itr++) {
		if ((*itr)->GetBuffID() == buffid)
		{
			if (stack > (*itr)->GetStack())
				(*itr)->InActive();
			else if (stack == (*itr)->GetStack()) {
				(*itr)->Active();
				find = TRUE;
			}
		}
	}

	if (!find) 
		_buffInfo.push_back(new Buff(buffid, stack));
}

VOID _PLAYERBUFF::EndBuff(USHORT buffid) {

	for (auto itr = _buffInfo.begin(); itr != _buffInfo.end(); itr++) {
		if ((*itr)->GetBuffID() == buffid) {
			(*itr)->InActive();
		}
	}
}

const UINT32& _PLAYERBUFF::GetPlayerID() {
	return _playerID;
}

vector<Buff*>::const_iterator _PLAYERBUFF::begin() {
	return _buffInfo.begin();
}

vector<Buff*>::const_iterator _PLAYERBUFF::end() {
	return _buffInfo.end();
}

BuffMeter::BuffMeter() {

}

BuffMeter::~BuffMeter() {

	for (auto itr = _playerBuffInfo.begin(); itr != _playerBuffInfo.end(); itr++)
		delete* itr;

	_playerBuffInfo.clear();
	_mutex.unlock();
}

VOID BuffMeter::AddBuff(UINT32 playerID, USHORT buffid, BYTE stack) {

	for (auto itr = _playerBuffInfo.begin(); itr != _playerBuffInfo.end(); itr++) {
		if ((*itr)->GetPlayerID() == playerID) {
			(*itr)->AddBuff(buffid, stack);
			return;
		}
	}

	_playerBuffInfo.push_back(new PLAYERBUF(playerID, buffid, stack));
}

VOID BuffMeter::EndBuff(UINT32 playerID, USHORT buffid) {

	for (auto itr = _playerBuffInfo.begin(); itr != _playerBuffInfo.end(); itr++) {
		if ((*itr)->GetPlayerID() == playerID) {
			(*itr)->EndBuff(buffid);
			return;
		}
	}
}

vector<PLAYERBUF*>::const_iterator BuffMeter::find(UINT32 playerID) {

	auto itr = _playerBuffInfo.begin();

	for (; itr != _playerBuffInfo.end(); itr++) {
		if ((*itr)->GetPlayerID() == playerID)
			return itr;
	}

	return itr;
}

vector<PLAYERBUF*>::const_iterator BuffMeter::begin() {
	return _playerBuffInfo.begin();
}

vector<PLAYERBUF*>::const_iterator BuffMeter::end() {
	return _playerBuffInfo.end();
}

VOID BuffMeter::GetLock() {
	_mutex.lock();
}

VOID BuffMeter::FreeLock() {
	_mutex.unlock();
}