#ifndef _BULKPACKET_H_
#define _BULKPACKET_H_
#include "Packet.h"
class bulkPacket: public Packet
{
	public:
		//标签，会话id, 起始Node id, 到达Node id, 起始时间
		int _sId;
		int _sourceId;
		int _sinkId;
		double _bTime;  

		bulkPacket():Packet() {
			_sId = _sourceId = _sinkId = -1;
			_bTime = -1;
		}
		~bulkPacket(){}
};
#endif
