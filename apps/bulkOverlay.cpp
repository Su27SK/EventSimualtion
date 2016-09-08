#include "bulkOverlay.h"
/**
 * @brief scheduling 
 *
 * @param {interge} v
 * @param {interge} u
 * @return {boolean}
 */
bool bulkOverlay::scheduling(int v, int u)
{
	fordFulkersion::FordFulkersion(*this, v, u);
	_flow = fordFulkersion::getValue();
	_routeToOId = fordFulkersion::getEdgeTo();
	return true;
}

/**
 * @brief updating 
 * 获得预测信息之后，更新每条边数据
 * @return {boolean}
 */
bool bulkOverlay::updating()
{
	slist<bulkFlow*>::iterator iter;
	for (size_t i = 1; i < _adj.size(); i++) {
		slist<bulkFlow*>* pFlow = _adj[i];
		for (iter = pFlow->begin(); iter != pFlow->end(); iter++) {
			int s = (*iter)->getGraphEdgeSource();
			int v = (*iter)->getGraphEdgeSink();
		}
	}
	return true;
}

/**
 * @brief initNetBottlenecks 
 */
void bulkOverlay::initNetBottlenecks()
{
	
}
