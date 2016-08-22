#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "bulkAgent.h"
#include "bulkNetwork.h"
#include <string.h>
#define THRESHOLD 0.1 //ε
class bulkBackPressure:public bulkNetwork
{
	private:
		double _computeS(map<double, int>& sorted, bulkLink link, double capacity);
		void _initAgents();
		vector<bulkAgent> _agents;
	public:
		bulkBackPressure():bulkNetwork() {
			_initAgents();
		}
		bulkBackPressure(Graph* graph): bulkNetwork(graph) {
			_initAgents();
		}
		virtual void handle();
};
#endif
