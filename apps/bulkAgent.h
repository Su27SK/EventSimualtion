#ifndef _BULKAGENT_H_
#define _BULKAGENT_H_a
#include <ext/slist>
#include <vector>
#include "agent.h"
#include "bulkNode.h"
#include "bulkBuffer.h"
using namespace __gnu_cxx;
class bulkAgent:public agent
{
	private:
		bulkNode _node;
		vector<bulkBuffer> _sendbuf; //tail
		vector<bulkBuffer> _recvbuf; //head
		vector<int> _requestBuf(MAXSESSION);     //各个session需要发送的数据量
		int _aId;
	public:
		bulkAgent(int aId, bulkNode node):agent()
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
		void recvToAgent(bulkLink& link);
		void sendFromAgent(bulkLink& link);
		int getStoreAmount(int sId);
		int reallocPackets(int sId);
		void reallocAll();
};
#endif
