#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "bulkNetwork.h"
#include "bulkAgent.h"
#include <string.h>
#define THRESHOLD 0.1 //ε
class bulkBackPressure:public bulkNetwork
{
	private:
		double _computeS(map<double, int>& sorted, bulkLink link, double capacity);
		vector<bulkAgent> _agents;
	public:
		bulkBackPressure():bulkNetwork() {
			vector<bulkNode>::iterator iter = nList_.begin();
			for (; iter != nList_end(); iter++) {
				bulkAgent* agent = new bulkAgent(iter->getNodeId(), *iter);
				_agents.push_back(*agent);
			}
		}
		virtual void handle();
};
#endif
