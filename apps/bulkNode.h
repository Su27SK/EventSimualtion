#ifndef _BULKNODE_H_
#define _BULKNODE_H_
#include <math.h>
#include "GraphNode.h"
#include "bulkLink.h"
#include <queue>
#include <vector>
#include <algorithm>
class bulkNode:public GraphNode
{
	private:
		bool _isTerminal;    //是否是终点
		bool _isOriginal;    //是否是起点
		void _defaultInit(); //缺省初始化函数
	protected:
		slist<bulkLink*>* output_; //链路出去
		slist<bulkLink*>* input_;  //链路进来
	public: 
		bulkNode():GraphNode() {
			this->_defaultInit();
		}
		bulkNode(int _id):GraphNode(_id) {
			this->_defaultInit();
		}
		bulkNode(const GraphNode& node);
		bulkNode(GraphNode& node);
		bool getTerminal();
		bool getOriginal();
		slist<bulkLink*>* getOutputLink();
		slist<bulkLink*>* getInputLink();
		void addOutputLink(bulkLink* link);
		void addInputLink(bulkLink* link);
		int getOutputNum();
		int getInputNum();
		bulkNode& setTerminal();
		bulkNode& setOriginal();
};
#endif
