#ifndef	_BULKPOOL_H_
#define _BULKPOOL_H_
#include <ext/slist>
#include "bulkPacket.h"
using namespace __gnu_cxx;
class bulkPool
{
	private:
		slist<bulkPacket>* _pool;
		static const int MAXSIZE = 1000;
		static const int INITSIZE = 1000;
	public:
		bulkPool();
		~bulkPool();
		void init();
		void destroy();
		void placePacketsToPool(bulkPacket* packets);
		bulkPacket& getPacketsFromPool();
};
#endif
