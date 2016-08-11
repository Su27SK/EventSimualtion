#ifndef _BULKAGENT_H_
#define _BULKAGENT_H_a
#include <ext/slist>
#include <map>
#include <vector>
#include "agent.h"
#include "BulkNode.h"
using namespace __gnu_cxx;
class bulkAgent:public agent
{
	private:
		BulkNode _node;
		vector<bulkBuffer> _sendbuf; //tail
		vector<bulkBuffer> _recvbuf; //head
		int _aId;
	public:
		bulkAgent(int aId, BulkNode node):agent()
		{
			_aId = aId;
			_node = node;
			setSendBuf(_node->getNumHeadQueue()); 
			setRecvBuf(_node->getNumTailQueue());
		}
		virtual bool recv();
		virtual bool send();
		void setSendBuf(int num);
		void setRecvBuf(int num);
		void recv(BulkLink& link);
		void send(BulkLink& link, int num);
		int getStoreAmount(int sId);
		int reallocPackets(int sId);
		void reallocAll();
};
#endif
