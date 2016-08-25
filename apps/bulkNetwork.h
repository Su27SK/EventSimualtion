#ifndef  _BULKNETWORK_H_ 
#define  _BULKNETWORK_H_
#define  MAXNODE 300
#include "Graph.h"
#include "bulkNode.h"
#include "bulkException.h"
#include "RandomGenerator.h"
#include <map>
class bulkNetwork
{
	protected:
		int nSource_; //有几个Source流入点
		int nSink_;   //有几个Sink流出点
		map<int, bulkNode*> sourceList_; //具体流入source数据包节点索引
		map<int, bulkNode*> sinkList_;   //具体流出sink数据包节点索引
		vector<bulkNode> nList_;         //node节点
		Graph* topology_;
	public:
		bulkNetwork():nSource_(0), nSink_(0) {
			topology_ = NULL;
		}
		void init();
		void check(int id, int min, int Max) const throw(bulkException);
		void handleOverException(bulkException e) const;
		void setGraph(Graph* graph);
		virtual void handle() = 0;
		bulkNetwork(Graph* graph);
		bulkNetwork& setSourceNode(int id, int sId);
		bulkNetwork& setSinkNode(int id, int sId);
		const bulkNode& getNodeById(int id) const;
		bulkNode* getSourceNodeById(int id) const;
		bulkNode* getSinkNodeById(int id) const;
		~bulkNetwork(){};
};
#endif
