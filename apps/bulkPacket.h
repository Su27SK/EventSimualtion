#ifndef _BULKPACKET_H_
#define _BULKPACKET_H_
#include "Packet.h"
class bulkPacket: public Packet
{
	public:
		//标签，会话id, 起始Node id, 到达Node id, 起始时间
		int _sId;
		int _sourceId;
		double _bTime;
		int _hopCount;
		int _nowId;

		bulkPacket():Packet() {
			_sId = _sourceId = -1;
			_bTime = -1;
			_nowId = -1;
			_hopCount = 0;
		}
		~bulkPacket(){}
};
#endif
