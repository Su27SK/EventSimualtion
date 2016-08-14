#include "GraphNode.h"
GraphNode::GraphNode(int id): _id(id), _numEdge(0)
{
	if (this->_id < 1) {
		this->_id = -1;
	}
	this->_edge = new slist<GraphEdge>(0);
}

/**
 * @brief GraphNode 
 * 显式深拷贝构造函数
 * @param {GraphNode} node
 */
GraphNode::GraphNode(const GraphNode& node)
{
	this->_id = node._id;
	this->_numEdge = node._numEdge;
	slist<GraphEdge>::iterator iterS;
	slist<GraphEdge>::iterator iterE;
	iterS = node._edge->begin();
	iterE = node._edge->end();
	this->_edge = new slist<GraphEdge>(iterS, iterE);
}

/**
 * @brief GraphNode 
 * 深拷贝构造函数
 * @param {GraphNode} node
 */
GraphNode::GraphNode(GraphNode& node)
{
	this->_id = node._id;
	this->_numEdge = node._numEdge;
	slist<GraphEdge>::iterator iterS;
	slist<GraphEdge>::iterator iterE;
	iterS = node._edge->begin();
	iterE = node._edge->end();
	this->_edge = new slist<GraphEdge>(iterS, iterE);
}

/**
 * @brief operator==
 * 重载操作符
 * @param {GraphNode} node
 *
 * @return {boolean}
 */
bool GraphNode::operator==(const GraphNode& node)
{
	return _id == node._id;
}


/**
 * @brief getNumEdge 
 * 获得该节点中的edge数量
 * @return {integer}
 */
int GraphNode::getNumEdge() const
{
	return _numEdge;
}

/**
 * @brief getNodeId 
 * 获得node的id号
 * @return {interger}
 */
int GraphNode::getNodeId() const
{
	return _id;
}


/**
 * @brief getEdge 
 *
 * @return slist<GraphEdge>*
 */
slist<GraphEdge>* GraphNode::getEdge() const
{
	return _edge;
}

/**
 * @brief addEdge 
 * 节点中增加与节点相连的边
 * @param {GraphEdge} edge
 *
 * @return {boolean}
 */
bool GraphNode::addEdge(GraphEdge* edge)
{
	if (_id == edge->getGraphEdgeSource() || _id == edge->getGraphEdgeSink()) {
		_edge->push_front(*edge);
		_numEdge++;
		return true;
	} else {
		return false;
	}
}

/**
 * @brief removeEdge 
 * 节点中删除与节点相连的边
 * @param {GraphEdge} edge
 *
 * @return {boolean}
 */
bool GraphNode::removeEdge(GraphEdge* edge)
{
	GraphEdge* pEdge = getEdge(edge);
	if (pEdge != NULL) {
		_edge->erase(remove(_edge->begin(), _edge->end(), *pEdge), _edge->end());
		return true;
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
		this->_id = nodeTemp._id;
		this->_numEdge = nodeTemp._numEdge;
		slist<GraphEdge>* pTemp = nodeTemp._edge;
		nodeTemp._edge = this->_edge;
		this->_edge = pTemp;
	}
	return *this;
}

/**
 * @brief getEdge 
 * 通过edge 返回向量边,包含具体信息，比如weight, capacity信息
 * (*iter == *edge) 主要比较(from, to)的数值
 * @param {GraphEdge} edge
 *
 * @return {GraphEdge}
 */
GraphEdge* GraphNode::getEdge(GraphEdge* edge) const
{
	slist<GraphEdge>::iterator iter = _edge->begin();
	slist<GraphEdge>::iterator iterEnd = _edge->end();
	for (; iter != iterEnd; iter++) {
		if (*iter == *edge) {
			return &(*iter);
		}
	}
	return NULL;
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
	_id = id;
	return *this;
}
