#include "bulkFlow.h"
#include <iostream>
using namespace std;
/**
 * @brief getFlow 
 *
 * @return {double}
 */
double bulkFlow::getFlow() const
{
	return _flow;
}

/**
 * @brief other 
 *
 * @param {interge} vertex
 *
 * @return {interge}
 */
int bulkFlow::other(int vertex)
{
	if (vertex == _v1) {
		return _v2;
	} else if (vertex == _v2) {
		return _v1;
	} else {
		throw new bulkException("bulkFlow other function inconsistent edge");
	}
}

/**
 * @brief residualCapacityTo 
 *
 * @param {interge} vertex
 *
 * @return {double}
 */
double bulkFlow::residualCapacityTo(int vertex)
{
	if (vertex == _v1) {
		return _flow; //反向边
	} else if (vertex == _v2) {
		return _capacity - _flow; //正向边
	} else {
		throw new bulkException("bulkFlow residualCapacityTo function inconsistent edge");
	}
}

/**
 * @brief addResidualFlowTo 
 *
 * @param {interge} vertex
 * @param {double}  delta
 */
void bulkFlow::addResidualFlowTo(int vertex, double delta)
{
	if (vertex == _v1) {
		_flow -= delta;
	} else if (vertex == _v2) {
		_flow += delta;
	} else {
		throw new bulkException("bulkFlow addResidualFlowTo function inconsistent edge");
	}
}

/**
 * @brief setSourceId 
 *
 * @param {interge} id
 *
 * @return 
 */
bulkFlow& bulkFlow::setSourceId(int id)
{
	_v1 = id;
	return *this;
}

/**
 * @brief setSinkId 
 *
 * @param {interge} id
 *
 * @return 
 */
bulkFlow& bulkFlow::setSinkId(int id)
{
	_v2 = id;
	return *this;
}

/**
 * @brief setPredictiveCapacity 
 *
 * @param {double} capacity
 *
 * @return 
 */
bulkFlow& bulkFlow::setPredictiveCapacity(double capacity)
{
	_predictiveCapacity = capacity;
	return *this;
}

/**
 * @brief getPredictiveCapacity 
 *
 * @return {double}
 */
double bulkFlow::getPredictiveCapacity()
{
	return _predictiveCapacity;
}
