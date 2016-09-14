#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "bulkAgent.h"
#include "bulkNetwork.h"
#include <string.h>
#define THRESHOLD 0.1 //ε
class bulkBackPressure:public bulkNetwork
{
	private:
		void _inputPackets();
		void _inputPackets(bulkAgent* vAgent, int sId);
		vector<bulkAgent*> _agents;
		vector<bulkAgent*> _vAgents; //虚拟Agents
		FILE* _handle;
	public:
		bulkBackPressure():bulkNetwork() {
			RandomGenerator::init(time(NULL));
			_handle = NULL;
		}
		bulkBackPressure(Graph* graph): bulkNetwork(graph) {
			RandomGenerator::init(time(NULL));
			_handle = NULL;
		}
		void initVirtualAgents();
		void initAgents();
		bulkBackPressure& setSession(int sId, int sourceId, int sinkId, double demand);
		virtual void handle();
};
#endif
