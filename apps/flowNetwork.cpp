#include "flowNetwork.h"
/**
 * @brief _initAdj
 */
void flowNetwork::_initAdj()
{
	if (_topology != NULL) {
		int n = _topology->getVertices();
		_adj.resize(n + 1);
		for (int i = 1; i < n + 1; i++) {
			_adj[i] = new slist<bulkFlow*>(0); 
		}
		GraphNode* aList = _topology->getList();
		for (int i = 1; i < n + 1; i++) {
			slist<GraphEdge>* edge = aList[i].getEdge();
			slist<GraphEdge>::iterator iter = edge->begin();
			for (; iter != edge->end(); iter++) {
				int sourceId = iter->getGraphEdgeSource();
				int sinkId = iter->getGraphEdgeSink();
				bulkFlow* flow = new bulkFlow(0.0, *iter);
				addEdge(flow);
			}
		}
	}
}

/**
 * @brief getAdj 
 *
 * @param {interge} v
 *
 * @return {slist<bulkFlow*>*}
 */
slist<bulkFlow*>* flowNetwork::getAdj(int v)
{
	return _adj[v];
}

/**
 * @brief addEdge 
 *
 * @param {bulkFlow} e
 */
void flowNetwork::addEdge(bulkFlow* e)
{
	int v = e.getGraphEdgeSource();
	int w = e.getGraphEdgeSink();
	_adj[v]->push_front(e);
	_adj[v]->push_front(e);
}

int flowNetwork::getVertices()
{
	return _adj.size() - 1;
}

