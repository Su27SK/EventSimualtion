#include "flowNetwork.h"
/**
 * @brief _initAdj
 */
void flowNetwork::_initAdj()
{
	_adj.resize(800);
	if (_topology != NULL) {
		int n = _topology->getVertices();
		for (int k = 0; k < 800; k++) {
			_adj[k].resize(n + 1);
			for (int i = 1; i < n + 1; i++) {
				_adj[k][i] = new slist<bulkFlow*>(0); 
			}
			GraphNode* aList = _topology->getList();
			for (int i = 1; i < n + 1; i++) {
				slist<GraphEdge>* edge = aList[i].getEdge();
				slist<GraphEdge>::iterator iter = edge->begin();
				for (; iter != edge->end(); iter++) {
					int sourceId = iter->getGraphEdgeSource();
					int sinkId = iter->getGraphEdgeSink();
					bulkFlow* flow = new bulkFlow(0.0, *iter);
					addEdge(k, flow);
				}
			}
			for (int i = 1; i < n + 1; i++) {
				slist<bulkFlow*>::iterator iter = _adj[k][i]->begin();
				int count = 0;
				for (; count < _adj[k][i]->size() / 2; iter++) {
					count++;
				}
				_adj[k][i]->erase(iter, _adj[k][i]->end());
			}
		}
	}
}

/**
 * @brief getAdj 
 *
 * @param {interge} time
 * @param {interge} v
 *
 * @return {slist<bulkFlow*>*}
 */
slist<bulkFlow*>* flowNetwork::getAdj(int time, int v)
{
	return _adj[time][v];
}

/**
 * @brief addEdge 
 *
 * @param {interge} time
 * @param {bulkFlow} e
 */
void flowNetwork::addEdge(int time, bulkFlow* e)
{
	int v = e->getGraphEdgeSource();
	int w = e->getGraphEdgeSink();
	_adj[time][v]->push_front(e);
	//_adj[v]->push_front(e);
}

int flowNetwork::getVertices()
{
	return _adj[0].size() - 1;
}

