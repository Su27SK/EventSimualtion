#ifndef _BULKNODE_H_
#define _BULKNODE_H_
#include <math.h>
#include "GraphNode.h"
#include "bulkLink.h"
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
class bulkNode:public GraphNode
{
	private:
		void _defaultInit();   //缺省初始化函数
		bool _isTerminal;      //是否是终点
		bool _isOriginal;      //是否是起点
	protected:
		slist<bulkLink*>* output_; //链路出去
		slist<bulkLink*>* input_;  //链路进来
	public: 
		set<int> originalIds_; //进口session起点
		set<int> terminalIds_; //出口session终点
		bulkNode():GraphNode() {
			this->_defaultInit();
		}
		bulkNode(int _id):GraphNode(_id) {
			this->_defaultInit();
		}
		bulkNode(const GraphNode& node);
		bulkNode(GraphNode& node);
		slist<bulkLink*>* getOutputLink();
		slist<bulkLink*>* getInputLink();
		void addOutputLink(bulkLink* link);
		void addInputLink(bulkLink* link);
		int getOutputNum();
		int getInputNum();
		bulkNode& setTerminal(int sId);
		bulkNode& setOriginal(int sId);
		bool getTerminal();
		bool getOriginal();
};
#endif
