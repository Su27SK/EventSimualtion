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

	#pragma omp parallel for
	for (int i = 0; i < _agents.size(); i++) {
		_agents[i]->recv();
		//_agents[i]->reallocAll();
		int num = _agents[i]->reallocAll();
		int nodeId = _agents[i]->getAId();
		//string sql = "insert into nodeInfo(nodeId, numbers, time) values(";
		string sql = "";
		//sql += _agents[i]->toString(nodeId) + "," + _agents[i]->toString(num) + "," + _agents[i]->toString(simTime_) + ");";
		sql += _agents[i]->toString(nodeId) + "," + _agents[i]->toString(num) + "," + _agents[i]->toString(simTime_);
		log_nodeInfo[nodeId].push_back(sql);
		//db_.exeSQL(sql);
		//cout<<"aId:"<<_agents[i]->getAId()<<" num:"<<num<<endl;
	}

	for (int i = 0; i < _vAgents.size(); i++) {
		_vAgents[i]->send();
	}

	#pragma omp parallel for
	for (int i = 0; i < _agents.size(); i++) {
		_agents[i]->send();
	}
}

void bulkBackPressure::init() 
{
	bulkNetwork::init();
	//db_.initDB("localhost", "root", "", "simulation");
	//initAgents();
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
		int aId = vAgent->getAId();
		if (m > 0) {
			int nPackets = RandomGenerator::genPoissonInt(m);
			nPackets = nPackets * 128;
			if (_handle == NULL) {
				_handle = fopen("../log/inputPackets.txt", "a+");
				fprintf(_handle, "sessionId,agentId,time,nPackets\n");
			}
			fprintf(_handle, "%d,%d,%d,%d\n", sId, aId, simTime_, nPackets); 
			int count = 0;
			while (count < nPackets) {
				bulkPacket& packet = pool.getPacketsFromPool();
				packet._sId = sId;
				packet._sourceId = aId;
				packet._bTime = simTime_;
				vAgent->inputVirtualNode(packet, sId);
				count++;
			}
		}
	} catch (bulkException e) {
		handleOverException(e, "inputPackets function");
		exit(0);
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
 * @brief setIntervalVary 
 *
 * @param {int} n
 *
 * @return {bulkBackPressure}
 */
bulkBackPressure& bulkBackPressure::setIntervalVary(int n)
{
	interval_ = n;
	return *this;
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
		handleOverException(e, "setSession function");
		exit(0);
	}
}

/**
 * @brief writeLog 
 */
void bulkBackPressure::writeLog()
{
	string dir_name = "../log/packet/";
	stringstream ss;
	string file_name;
	ss<<simTime_;
	ss>>file_name;
	string file_path = dir_name + file_name + "_log_time.txt";
	FILE* handle = fopen(file_path.c_str(), "a+");
	fprintf(handle, "packet_id,session_id,start_time,end_time,next_hop,source,sink\n");
	for (int i = 0; i < MAXSESSION; i++) {
		for (int j = 0; j < log_packet[i].size(); j++) {
			fprintf(handle, "%s\n", log_packet[i][j].c_str());
		}
		log_packet[i].resize(0);
	}
	fclose(handle);
	dir_name = "../log/node/";
	file_path = dir_name + file_name + "_log_time.txt";
	handle = fopen(file_path.c_str(), "a+");
	fprintf(handle, "nodeId,numbers,time\n");
	for (int i = 0; i < MAXROUTE; i++) {
		for (int j = 0; j < log_nodeInfo[i].size(); j++) {
			fprintf(handle, "%s\n", log_nodeInfo[i][j].c_str());
		}
		log_nodeInfo[i].resize(0);
	}
	fclose(handle);
}
