#pragma once
#include ".\Language\Region.h"
#include ".\Soulworker Packet\PacketType.h"
#include ".\Soulworker Packet\SWPacket.h"

#define SWSPACKETMAKER SWSPacketMaker::getInstance()

#define NO_SEGMENTATION 0
#define YES_SEGMENTATION 1
#define REASSAMBLY 2
#define NO_SWHEADER 3
#define NO_SWDATA 4
#define SEGMENTATION_SUCCESS 5
#define SEGMENTATION_FAILED 6

#define DEBUG_SEGMENTATION 0
#define DEBUG_CREATESPACKET 0
#define DEBUG_RESIZEPACKET 0

class SWSPacketMaker : public Singleton<SWSPacketMaker> {
private:
	class SegmentationPacket {
	private:
		BYTE* _data;
		SIZE_T _size;

		SIZE_T _curSize;
		SIZE_T _packetSize;

		IPv4Packet _packet;

	public:
		SegmentationPacket() {
			_data = nullptr;
			_size = 0;
			_curSize = 0;
			_packetSize = 0;
		}

		~SegmentationPacket() {

			if (_data != nullptr)
				delete[] _data;

			_data = nullptr;
		}

		VOID Init(SIZE_T size) {

			if (_data == nullptr) {
				_data = new BYTE[size];
				_size = size;
			}

			if (_size < size) {
				delete[] _data;
				_data = new BYTE[size];
				_size = size;
			}

			_curSize = 0;
			_packetSize = size;

#if DEBUG_SEGMENTATION == 1
			Log::WriteLogA(const_cast<CHAR*>("[segmentationPacket Init] [curSize = %d] [packetSize = %d]"), _curSize, _packetSize);
#endif

		}

		SIZE_T GetRemainSize() {
#if DEBUG_SEGMENTATION == 1
			Log::WriteLogA(const_cast<CHAR*>("[segmentationPacket RemainSize = %d]"), _packetSize - _curSize);
#endif

			return _packetSize - _curSize;
		}

		DWORD AppendData(BYTE* data, SIZE_T size) {

			memcpy(_data + _curSize, data, size);

			int temp_debug = _curSize;
			_curSize += size;

#if DEBUG_SEGMENTATION == 1
			Log::WriteLogA(const_cast<CHAR*>("[segmentationPacket AppendData Before curSize = %d After curSize = %d]"), temp_debug, _curSize);

			for (int i = temp_debug; i < _curSize; i++)
				printf("%02x ", _data[i]);
			printf("\n");
#endif

			if (_curSize == _packetSize)
				return SEGMENTATION_SUCCESS;
			else if (_curSize < _packetSize)
				return SEGMENTATION_FAILED;
		}

		IPv4Packet* GetData() {
			_packet._data = _data;
			_packet._datalength = _packetSize;

			return &_packet;
		}
	};


	VOID Decrypt(BYTE* data, const UINT size, const UINT start);

#ifndef SERVER_STEAM
	BYTE _keyTable[15] = { 0xee, 0x1b, 0xde, 0xa6, 0x46, 0xe9, 0x2a, 0xdb, 0x97, 0x67, 0x9c, 0x02, 0x3c, 0xce, 0x9a };
#else
	BYTE _keyTable[15] = { 0xd4, 0x59, 0xef, 0x2d, 0x22, 0x24, 0xb0, 0xc5, 0x0a, 0xa0, 0xd9, 0xad, 0x63, 0x9d, 0x0f };
#endif


	SWSHEADER* GetSWSHeader(IPv4Packet* packet);
	BYTE* GetSWData(IPv4Packet* packet);

	VOID ResizePacket(IPv4Packet* packet);
	VOID ResizePacket(SIZE_T remainsize, IPv4Packet* packet);

	DWORD CheckSegmentation(IPv4Packet* packet);
	BOOL _isSegmentation;

	VOID StartReassambly(IPv4Packet* packet);
	VOID Reassambly(IPv4Packet* packet);
	SegmentationPacket _segmentationPacket;

	VOID CreateSWPacket(IPv4Packet* packet);

	VOID CheckRemainPacket(IPv4Packet* packet);

public:
	SWSPacketMaker();
	~SWSPacketMaker();

	DWORD Parse(IPv4Packet* packet);
};