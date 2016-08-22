#include "bulkBackPressure.h"
/**
 * @brief handle 
 */
void bulkBackPressure::handle()
{
	vector<bulkAgent>::iterator iter = _agents.begin();
	
	for (; iter != _agents.end(); iter++) {
		iter->reallocAll();
		iter->send();
	}
	for (iter = _agents.begin(); iter != _agents.end(); iter++) {
		iter->recv();
	}
}

/**
 * @brief _initAgent 
 */
void bulkBackPressure::_initAgents()
{
	vector<bulkNode>::iterator iter = nList_.begin();
	for (; iter != nList_.end(); iter++) {
		bulkAgent* agent = new bulkAgent(iter->getNodeId(), *iter);
		_agents.push_back(*agent);
	}
}
