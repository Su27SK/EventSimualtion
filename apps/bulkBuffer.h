#ifndef _BULKBUFFER_H_
#define _BULKBUFFER_H_
#include "config.h"
#include <ext/slist>
#include <vector>
#include "bulkPacket.h"
#include "bulkException.h"
using namespace __gnu_cxx;
using namespace std;
class bulkBuffer
{
	private:
		//_buffers: session id对应缓存队列
		vector<slist<bulkPacket>* > _buffers; 
		int _check(int sId);
		void _handleOverException(bulkException e) const;
	public:
		bulkBuffer() {
			_buffers.resize(MAXSESSION + 1);
			vector<slist<bulkPacket>* >::iterator iter;
			for (iter = _buffers.begin(); iter != _buffers.end(); iter++) {
				*iter = new slist<bulkPacket>();
			}
		}
		void pushPacketsToBuf(int sId, bulkPacket& packet);
		slist<bulkPacket>* pullPacketsFromBuf(int sId, int num);
		slist<bulkPacket>* getPacketsStore(int sId);
};
#endif
