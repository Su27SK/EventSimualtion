#include "bulkBackPressure.h"
/**
 * @brief handle 
 */
void bulkBackPressure::handle()
{
	_inputPackets();
	if (_vAgents.empty()) {
		cout<<"No Virtual Node, Must initVirtualAgents Function"<<endl;
		return;
	}
	if (_agents.empty()) {
		cout<<"No Agents Node, Must initAgents Function"<<endl;
		return;
	}
	for (int i = 0; i < _vAgents.size(); i++) {
		_vAgents[i]->send();
	}
	for (int i = 0; i < _agents.size(); i++) {
		_agents[i]->send();
	}
	for (int i = 0; i < _agents.size(); i++) {
		_agents[i]->recv();
		int num = _agents[i]->reallocAll();
		//cout<<"aId:"<<_agents[i]->getAId()<<" num:"<<num<<endl;
	}
}

/**
 * @brief initAgent 
 */
void bulkBackPressure::initAgents()
{
	vector<bulkNode>::iterator iter = nList_.begin();
	for (; iter != nList_.end(); iter++) {
		bulkAgent* agent = new bulkAgent(iter->getNodeId(), *iter);
		_agents.push_back(agent);
	}
}

/**
 * @brief initVirtualAgents 
 */
void bulkBackPressure::initVirtualAgents()
{
	map<int, bulkNode*>::iterator mIter = sourceList_.begin();
	for (; mIter != sourceList_.end(); mIter++) {
		bulkNode* vNode = new bulkNode(mIter->first);
		bulkLink* vLink = new bulkLink(mIter->first, mIter->first);
		bulkAgent* vAgent = new bulkAgent(mIter->first, *vNode);
		vAgent->fake_ = true;
		vAgent->addVirtualOutputLink(vLink);
		_vAgents.push_back(vAgent);
		(mIter->second)->addInputLink(vLink);
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
		check(sId, 1, MAXSESSION);
		int m = sToDemand[sId];
		if (m > 0) {
			//int nPackets = RandomGenerator::genPoissonInt(m);
			if (_handle == NULL) {
				_handle = fopen("../Bulk_Config_File/InputPackets.txt", "r");
			}
			char buf[10];
			fgets(buf, 9, _handle);
			cout<<"Hello World"<<endl;
			int nPackets = buf[0] - '0';
			cout<<"nPacket:"<<nPackets<<endl;
			int count = 0;
			while (count < nPackets) {
				bulkPacket& packet = pool.getPacketsFromPool();
				vAgent->inputVirtualNode(packet, sId);
				count++;
			}
		}
	} catch (bulkException e) {
		handleOverException(e);
	}
}

/**
 * @brief _inputPackets 
 */
void bulkBackPressure::_inputPackets() 
{
	vector<bulkAgent*>::iterator vIter = _vAgents.begin(); 
	for (; vIter != _vAgents.end(); vIter++) {
		int id = (*vIter)->getAId();
		bulkNode node = *(sourceList_[id]);
		set<int>::iterator sIter = node.originalIds_.begin();
		for (; sIter != node.originalIds_.end(); sIter++) {
			_inputPackets(*vIter, *sIter);
		}
	}
}

/**
 * @brief setSession 
 *
 * @param {interge} sId
 * @param {interge} sourceId
 * @param {interge} sinkId
 * @param {double} demand
 *
 * @return {bulkBackPressure}
 */
bulkBackPressure& bulkBackPressure::setSession(int sId, int sourceId, int sinkId, double demand)
{
	try {
		check(sId, 1, MAXSESSION);
		if (demand < 0) {
			demand = 0;
		}
		sToDemand[sId] = demand;
		setSourceNode(sourceId, sId);
		setSinkNode(sinkId, sId);
		return *this;
	}
	catch (bulkException e) {
		handleOverException(e);
	}
}
