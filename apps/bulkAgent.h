#ifndef _BULKAGENT_H_
#define _BULKAGENT_H_
#include <ext/slist>
#include <vector>
#include "agent.h"
#include "bulkNode.h"
#include "bulkBuffer.h"
using namespace __gnu_cxx;
class bulkAgent:public Agent
{
	private:
		bulkNode _node;
		vector<bulkBuffer> _sendbuf; //tail
		vector<bulkBuffer> _recvbuf; //head
		vector<int> _requestBuf;     //各个session需要发送的数据量
		int _aId;
	public:
		bulkAgent(int aId, bulkNode node):Agent()
		{
			_aId = aId;
			_node = node;
			_requestBuf.resize(MAXSESSION);
			setSendBuf(_node.getOutputNum()); 
			setRecvBuf(_node.getInputNum());
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
