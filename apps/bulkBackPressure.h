#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "bulkAgent.h"
#include "bulkNetwork.h"
#include <string.h>
#define THRESHOLD 0.1 //ε
class bulkBackPressure:public bulkNetwork
{
	private:
		void _initAgents();
		vector<bulkAgent> _agents;
	public:
		bulkBackPressure():bulkNetwork() {
			_initAgents();
		}
		bulkBackPressure(Graph* graph): bulkNetwork(graph) {
			_initAgents();
		}
		void inputPackets(int sId);
		bulkBackPressure& setSession(int sId, double demand);
		virtual void handle();
};
#endif
