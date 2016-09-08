#ifndef _FLOWNETWORK_H_
#define _FLOWNETWORK_H_
#include "Graph.h"
#include "bulkFlow.h"
#include <vector>
#include <ext/slist>
using namespace __gnu_cxx;
using namespace std;
class flowNetwork
{
	private:
		void _initAdj();
	protected:
		vector<slist<bulkFlow*>* > _adj;
		Graph* _topology;
	public:
		flowNetwork() {
			_topology = NULL;
		}
		flowNetwork(Graph* graph): _topology(graph) {
			_initAdj();
		}
		slist<bulkFlow*>* getAdj(int v);
		void addEdge(bulkFlow* e);
		int getVertices();
};
#endif
