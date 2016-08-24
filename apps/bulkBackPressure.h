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
		void _initVirtualAgents();
		void _inputPackets(bulkAgent* vAgent, int sId);
		vector<bulkAgent*> _agents;
		vector<bulkAgent*> _vAgents; //虚拟Agents
	public:
		bulkBackPressure():bulkNetwork() {}
		bulkBackPressure(Graph* graph): bulkNetwork(graph) {
			_initVirtualAgents();
			_initAgents();
		}
		void inputPackets();
		bulkBackPressure& setSession(int sId, double demand);
		virtual void handle();
};
#endif
