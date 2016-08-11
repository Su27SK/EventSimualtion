#ifndef _BULKAGENT_H_
#define _BULKAGENT_H_
#include <map>
#include "agent.h"
#include "BulkNode.h"
class bulkAgent:public agent
{
	private:
		BulkNode _node;
		map<int, slist<Packet>* > _buffers;
		int _aId;
	public:
		bulkAgent(int aId):agent()
		{
			_aId = aId;
		}
		virtual bool recv(slist<Packet>* list);
		virtual bool send(slist<Packet>* list);
		void recv(slist<Packet>* list, BulkLink& link);
		void send(slist<Packet>* list, BulkLink& link);
		int getStoreAmount(int sId);
		int reallocPackets(int sId);
		void reallocAll();
};
#endif
