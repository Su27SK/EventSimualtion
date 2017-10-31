#ifndef _BULKAGENT_H_
#define _BULKAGENT_H_
#define ROUND(x) ((x) > 0.0 ? floor((x) + 0.5) : ceil((x) - 0.5));
#define THRESHOLD 0.1 //ε
#include <ext/slist>
#include <vector>
#include <map>
#include <sstream>
#include "agent.h"
#include "bulkNode.h"
#include "bulkBuffer.h"
using namespace __gnu_cxx;
class bulkAgent:public Agent
{
	private:
		enum {OUT = 1, IN = 2, DEFAULT = 3};
		bulkNode _node;
		vector<bulkBuffer> _sendbuf; //tail buffers
		vector<bulkBuffer> _recvbuf; //head buffers
		vector<vector<int> > _requestBuf;     //每条发送链路上各个session需要发送的数据量
		double _computeS(map<double, int>& sorted, bulkLink link, double capacity);
		int _aId;
	public:
		bool fake_; //判断是否是伪Agent;
		bulkAgent(int aId, bulkNode node):Agent()
		{
			_aId = aId;
			_node = node;
			for (int i = 0; i < _node.getOutputNum(); i++) {
				vector<int> temp(MAXSESSION + 1);
				_requestBuf.push_back(temp);
			}
			setSendBuf(_node.getOutputNum()); 
			setRecvBuf(_node.getInputNum() + 1);
			fake_ = false;
		}
		string toString(int n);
		virtual bool recv();
		virtual bool send();
		void setSendBuf(int num);
		void setRecvBuf(int num);
		void recvToAgent(bulkLink& link);
		void sendFromAgent(bulkLink& link);
		void addVirtualOutputLink(bulkLink* link);
		void inputVirtualNode(bulkPacket& packet, int sId);
		slist<bulkPacket>* getStore(int sId);
		double getAllWeight();
		int reallocPackets(int sId);
		float reallocRequests(bulkLink& link);
		double getCapacityFromFile(bulkLink link);
		int getAId() const;
		int reallocAll();
		void reallocAllRequests();
		void handle();
};
#endif
