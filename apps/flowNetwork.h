#ifndef _FLOWNETWORK_H_
#define _FLOWNETWORK_H_
#include "Graph.h"
#include "bulkFlow.h"
class flowNetwork
{
	private:
		vector<slist<bulkFlow*>* > _adj;
		Graph* _topology;
		void _initAdj();
	public:
		flowNetwork() {
			_topology = NULL;
		}
		flowNetwork(Graph* graph): _topology(graph) {
			_initAdj();
		}
		slist<bulkFlow*>* getAdj(int v);
		void addEdge(bulkFlow* e);
};
#endif
