#include "GraphNode.h"
GraphNode::GraphNode(int _id):id(_id), numHeadQueue(0), numTailQueue(0)
{
	if (this->id < 1) {
		this->id = -1;
	}
	this->headEdge = new slist<GraphEdge>(0);
	this->tailEdge = new slist<GraphEdge>(0);
}

/**
 * @brief GraphNode 
 * 显式深拷贝构造函数
 * @param {GraphNode} Node
 */
GraphNode::GraphNode(const GraphNode& Node)
{
	this->id = Node.id;
	this->numHeadQueue = Node.numHeadQueue;
	this->numTailQueue = Node.numTailQueue;
	slist<GraphEdge>::iterator iterS;
	slist<GraphEdge>::iterator iterE;
	iterS = Node.headEdge->begin();
	iterE = Node.headEdge->end();
	this->headEdge = new slist<GraphEdge>(iterS, iterE);
	iterS = Node.tailEdge->begin();
	iterE = Node.tailEdge->end();
	this->tailEdge = new slist<GraphEdge>(iterS, iterE);
}

/**
 * @brief GraphNode 
 * 深拷贝构造函数
 * @param {GraphNode} Node
 */
GraphNode::GraphNode(GraphNode& Node)
{
	this->id = Node.id;
	this->numHeadQueue = Node.numHeadQueue;
	this->numTailQueue = Node.numTailQueue;
	slist<GraphEdge>::iterator iterS;
	slist<GraphEdge>::iterator iterE;
	iterS = Node.headEdge->begin();
	iterE = Node.headEdge->end();
	this->headEdge = new slist<GraphEdge>(iterS, iterE);
	iterS = Node.tailEdge->begin();
	iterE = Node.tailEdge->end();
	this->tailEdge = new slist<GraphEdge>(iterS, iterE);
}

bool GraphNode::operator == (const GraphNode& node)
{
	return id == node.id;
}


/**
 * @brief getNumHeadQueue 
 * 获得该节点中的head queues的数量
 * @return {integer}
 */
int GraphNode::getNumHeadQueue() const
{
	return this->numHeadQueue;
}

/**
 * @brief getNumTailQueue 
 * 获得该节点中的tail queues的数量
 * @return {integer}
 */
int GraphNode::getNumTailQueue() const
{
	return this->numTailQueue;
}

/**
 * @brief getNodeId 
 * 获得node的id号
 * @return {interger}
 */
int GraphNode::getNodeId() const
{
	return this->id;
}

/**
 * @brief getHeadEdge 
 *
 * @return slist<GraphEdge>*
 */
slist<GraphEdge>* GraphNode::getHeadEdge() const
{
	return this->headEdge;
}

/**
 * @brief getTailEdge 
 *
 * @return slist<GraphEdge>*
 */
slist<GraphEdge>* GraphNode::getTailEdge() const
{
	return this->tailEdge;
}

/**
 * @brief addBulkEdge 
 * 节点中增加与节点相连的边
 * @param {GraphEdge} edge
 *
 * @return {boolean}
 */
bool GraphNode::addBulkEdge(GraphEdge* edge)
{
	if (this->id == edge->getGraphEdgeSource()) {
		this->tailEdge->push_front(*edge);
		this->numHeadQueue++;
		return true;
	} else if (this->id == edge->getGraphEdgeSink()) {
		this->headEdge->push_front(*edge);
		this->numTailQueue++;
		return true;
	} else {
		return false;
	}
}

/**
 * @brief removeBulkEdge 
 * 节点中删除与节点相连的边
 * @param {GraphEdge} edge
 *
 * @return {boolean}
 */
bool GraphNode::removeBulkEdge(GraphEdge* edge)
{
	slist<GraphEdge>::iterator iter;
	slist<GraphEdge>::iterator iterEnd;
	if (this->id == edge->getGraphEdgeSource()) {
		iter = this->headEdge->begin();
		iterEnd = this->headEdge->end();
		for (; iter != iterEnd; iter++) {
			if (*iter == *edge) {
				this->headEdge->erase(iter);
				return true;
			}
		}
	} else if (this->id == edge->getGraphEdgeSink()) {
		iter = this->tailEdge->begin();
		iterEnd = this->tailEdge->end();
		for (; iter != iterEnd; iter++) {
			if (*iter == *edge) {
				this->headEdge->erase(iter);
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief operator= 
 * 重载操作符
 * @param {GraphNode} node
 *
 * @return {GraphNode}
 */
GraphNode& GraphNode::operator=(const GraphNode &node)
{
	if (this != &node) {
		GraphNode nodeTemp(node);
		this->id = nodeTemp.id;
		this->numHeadQueue = nodeTemp.numHeadQueue;
		this->numTailQueue = nodeTemp.numTailQueue;
		slist<GraphEdge>* pHTemp = nodeTemp.headEdge;
		nodeTemp.headEdge = this->headEdge;
		this->headEdge = pHTemp;

		slist<GraphEdge>* pTTemp = nodeTemp.tailEdge;
		nodeTemp.tailEdge = this->tailEdge;
		this->tailEdge = pTTemp;
	}
	return *this;
}

/**
 * @brief getBulkEdge 
 * 通过edge 返回向量边,包含具体信息，比如weight, capacity信息
 * (*iter == *edge) 主要比较(from, to)的数值
 * @param {GraphEdge} edge
 *
 * @return {GraphEdge}
 */
GraphEdge* GraphNode::getBulkEdge(GraphEdge* edge) const
{
	slist<GraphEdge>::iterator iter;
	slist<GraphEdge>::iterator iterEnd;
	if (this->id == edge->getGraphEdgeSource()) {
		iter = this->headEdge->begin();
		iterEnd = this->headEdge->end();
		for (; iter != iterEnd; iter++) {
			if (*iter == *edge) {
				return &(*iter);
			}
		}
	} else if (this->id == edge->getGraphEdgeSink()) {
		iter = this->tailEdge->begin();
		iterEnd = this->tailEdge->end();
		for (; iter != iterEnd; iter++) {
			if (*iter == *edge) {
				return &(*iter);
			}
		}
	} 
	if (iter == iterEnd) {
		return NULL; 
	}
	return NULL;
}

int GraphNode::Print()
{
	slist<GraphEdge>::iterator iter;
	iter = this->headEdge->begin();
	return iter->getGraphEdgeSource();
}

/**
 * @brief setId 
 * 设置节点ID号
 * @param {interge} id
 *
 * @return {GraphNode}
 */
GraphNode& GraphNode::setId(int id)
{
	this->id = id;
	return *this;
}

