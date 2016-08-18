#ifndef _BULKBUFFER_H_
#define _BULKBUFFER_H_
#define MAXSESSION 20
#include <ext/slist>
#include <vector>
#include "bulkPacket.h"
using namespace __gnu_cxx;
class bulkBuffer
{
	private:
		//_buffers: session id对应缓存队列
		vector<slist<bulkPacket>* > _buffers; 
	public:
		bulkBuffer() {
			_buffers.resize(MAXSESSION);
			vector<slist<bulkPacket>* >::iterator iter;
			for (iter = _buffers.begin(); iter != _buffers.end(); iter++) {
				*iter = new slist<bulkPacket>();
			}
		}
		void pushPacketsToBuf(int sId, bulkPacket& packet);
		slist<bulkPacket>* pullPacketsFromBuf(int sId, int num);
		int getPacketsAmount(int sId);
		vector<slist<bulkPacket>* >& getBuffers();
};
#endif
