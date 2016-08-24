#include "bulkBackPressure.h"
/**
 * @brief handle 
 */
void bulkBackPressure::handle()
{
	vector<bulkAgent*>::iterator iter = _agents.begin();
	
	for (; iter != _agents.end(); iter++) {
		(*iter)->reallocAll();
		(*iter)->send();
	}
	for (iter = _agents.begin(); iter != _agents.end(); iter++) {
		(*iter)->recv();
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
		_agents.push_back(agent);
	}
}

/**
 * @brief _initVirtualAgents 
 */
void bulkBackPressure::_initVirtualAgents()
{
	map<int, bulkNode>::iterator mIter = sourceList_->begin();
	for (; mIter != sourceList_->end(); mIter++) {
		bulkNode* vNode = new bulkNode(mIter->first);
		bulkLink* vLink = new bulkLink(mIter->first, mIter->first);
		bulkAgent* vAgent = new bulkAgent(mIter->first, *vNode);
		vAgent->fake_ = true;
		vAgent->addVirtualInputLink(vLink);
		_vAgents.push_back(vAgent);
		nList_[mIter->first].addInputLink(vLink);
	}
}

/**
 * @brief _inputPackets 
 *
 * @param {bulkAgent*} vAgent
 * @param {interge} sId
 */
void bulkBackPressure::_inputPackets(bulkAgent* vAgent, int sId)
{
	try {
		check(sId, 1, MAXSESSION + 1);
		int m = sToDemand[sId];
		if (m > 0) {
			int nPacket = RandomGenerator::genPoissonInt(m);
			int count = 0;
			while (count < m) {
				bulkPacket& packet = pool.getPacketsFromPool();
				vAgent->inputVirualNode(packet, sId);
				count++;
			}
		}
	} catch (bulkException e) {
		handleOverException(e);
	}
}

/**
 * @brief inputPackets 
 */
void bulkBackPressure::inputPackets() 
{
	vector<bulkAgent*>::iterator bIter = _vAgents.begin(); 
	for (; bIter != _vAgents.end(); bIter++) {
		int id = (*bIter)->getAId();
		bulkNode node = (*sourceList_)[id];
		set<int>::iterator sIter = node.originalIds_.begin();
		for (; sIter != node.originalIds_.end(); sIter++) {
			_inputPackets(*bIter, *sIter);
		}
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
	}
	catch (bulkException e) {
		handleOverException(e);
	}
}
