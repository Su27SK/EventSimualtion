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

/**
 * @brief inputPackets 
 *
 * @param {interge} sId
 */
void bulkBackPressure::inputPackets(int sId)
{
	try {
		check(sId, 1, MAXSESSION + 1);
		int m = sToDemand[sId];
		int nPacket = RandomGenerator::genPoissonInt(m);
		
	} catch (bulkException e) {
		handleOverException(e);
	}
}

/**
 * @brief setSession 
 *
 * @param {interge} sId
 * @param {double} demand
 *
 * @return {bulkBackPressure}
 */
bulkBackPressure& bulkBackPressure::setSession(int sId, double demand)
{
	try {
		check(sId, 1, MAXSESSION + 1);
		if (demand < 0) {
			demand = 0;
		}
		sToDemand[sId] = demand;
		return *this;
	} catch (bulkException e) {
		handleOverException(e);
	}
}
