#include "GraphEdge.h"
GraphEdge::GraphEdge(int v1, int v2, double weight, double capacity)
{
	this->_v1 = v1;
	this->_v2 = v2;
	this->_weight = weight;
	this->_capacity = capacity;
}

GraphEdge::GraphEdge(GraphEdge& edge)
{
	_v1 = edge._v1;
	_v2 = edge._v2;
	_weight = edge._weight;
	//_capacity = edge._weight;
	_capacity = edge._capacity;
}

GraphEdge::GraphEdge(const GraphEdge& edge)
{
	_v1 = edge._v1;
	_v2 = edge._v2;
	_weight = edge._weight;
	//_capacity = edge._weight;
	_capacity = edge._capacity;
}

/**
 * @brief operator == 
 * 是否为同一条边(有向边)
 * @param {GraphEdge} edge
 * 
 * @return {boolean}
 */
bool GraphEdge::operator == (const GraphEdge& edge)
{
	return (this->_v1 == edge._v1) && (this->_v2 == edge._v2);
}

/**
 * @brief setWeight 
 * 设置该边的权值(数学期望)
 * @param {double} weight (权值)
 *
 * @return {GraphEdge}
 */
GraphEdge& GraphEdge::setWeight(double weight)
{
	this->_weight = weight;
	return *this;
}

/**
 * @brief setCapacity 
 * 设置改变的带宽,当前传输能力
 * @param {double} capacity
 *
 * @return {GraphEdge}
 */
GraphEdge& GraphEdge::setCapacity(double capacity)
{
	this->_capacity = capacity;
	return *this;
}

/**
 * @brief getWeight 
 * 获得权值(数学期望)
 * @return {double}
 */
double GraphEdge::getWeight() const
{
	return this->_weight;
}

/**
 * @brief getCapacity 
 * 获得当前带宽
 * @return {double}
 */
double GraphEdge::getCapacity() const
{
	return this->_capacity;
}

/**
 * @brief getGraphEdgeSource 
 *
 * @return {interge}
 */
int GraphEdge::getGraphEdgeSource() const
{
	return _v1;
}

/**
 * @brief getGraphEdgeSink 
 *
 * @return {interge}
 */
int GraphEdge::getGraphEdgeSink() const
{
	return this->_v2;
}
