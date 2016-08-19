#ifndef _BULKAGENT_H_
#define _BULKAGENT_H_
#define ROUND(x) ((x) > 0.0 ? floor((x) + 0.5) : ceil((x) - 0.5));
#include <ext/slist>
#include <vector>
#include "agent.h"
#include "bulkNode.h"
#include "bulkBuffer.h"
using namespace __gnu_cxx;
class bulkAgent:public Agent
{
	private:
		enum {OUT = 1, IN = 2, DEFAULT = 3};
		bulkNode _node;
		vector<bulkBuffer> _sendbuf; //tail
		vector<bulkBuffer> _recvbuf; //head
		vector<vector<int> > _requestBuf;     //每条发送链路上各个session需要发送的数据量
		int _aId;
	public:
		vector<vector<int> > outBufSum_;      //出去链路目前缓存数据包数量
		vector<vector<int> > inBufSum_;       //进入链路目前缓存数据包数量
		bulkAgent(int aId, bulkNode node):Agent()
		{
			_aId = aId;
			_node = node;
			for (int i = 0; i < _node.getOutputNum(); i++) {
				vector<int> temp(MAXSESSION);
				_requestBuf.push_back(temp);
				outBufSum_.push_back(temp);
			}
			for (int i = 0; i < _node.getInputNum(); i++) {
				vector<int> temp(MAXSESSION);
				inBufSum_.push_back(temp);
			}
			setSendBuf(_node.getOutputNum()); 
			setRecvBuf(_node.getInputNum());
		}
		virtual bool recv();
		virtual bool send();
		void setSendBuf(int num);
		void setRecvBuf(int num);
		void recvToAgent(bulkLink& link);
		void sendFromAgent(bulkLink& link);
		slist<bulkPacket>* getStore(int sId);
		double getAllWeight();
		int reallocPackets(int sId);
		void reallocAll();
};
#endif
