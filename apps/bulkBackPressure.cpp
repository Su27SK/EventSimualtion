#include "bulkBackPressure.h"

/**
 * @brief handle 
 */
void bulkBackPressure::handle()
{
	map<int, BulkNode>::iterator mIter;
	queue<int> q;
	int visited[MAXNODE];
	for (int i = 1; i <= MAXNODE; i++) {
		visited[i] = 0;
	}
	for (mIter = _lSourceList->begin(); mIter != _lSourceList->end(); mIter++) {
		q.push(mIter->first); 
		visited[mIter->first] = 1;
	}
	_realloc();
	this->propagate(&q, visited);
}

/**
 * @brief _realloc 
 */
void bulkBackPressure::_realloc()
{
	if (_nodeHandle == NULL) {
		_nodeHandle = fopen("Bulk_Log/NodeInfo.txt", "w+");
	}
	if (this->_topology != NULL) {
		int N = this->_topology->getVertices();
		for (int nodeId = 1; nodeId <= N; nodeId++) {
			BulkNode* pNode = nList_[nodeId];
			pNode->time_ = timer.getTime();
			pNode->reallocAll(_nodeHandle);
		}
	}
}

double bulkBackPressure::getCapacityFromFile(double time, int source, int sink)
{
	char buff[1024];
	if (_lHandle == NULL) {
		_lHandle = fopen("Bulk_Log/dealedLinkInfo_2.txt", "r");
	}
	int curTime = int(time / 60);
	while (!feof(_lHandle)) {
		fgets(buff, 1024, _lHandle);
		string message(buff);
		int len = message.find(" ");
		int ftime = atoi(message.substr(0, len).c_str());
		message = message.substr(len + 1);
		
		len = message.find(" ");
		int iSource = atoi(message.substr(0, len).c_str());
		message = message.substr(len + 1);

		len = message.find(" ");
		int iSink = atoi(message.substr(0, len).c_str());
		message = message.substr(len + 1);

		len = message.find(" ");
		double capacity = atoi(message.substr(0, len).c_str());
		message = message.substr(len + 1);
		if ((curTime == ftime) && (source == iSource) && (sink == iSink)) {
			fseek(_lHandle, 0l, 0);
			return capacity;
		}
	}
	return 0;
}

/**
 * @brief dynamicPush 
 * 对每条链路动态推送数据包
 * @param {Bulklink} link
 */
//void bulkBackPressure::dynamicPush(BulkLink& link)
float bulkBackPressure::dynamicPush(BulkLink& link)
{
	int iSource = link.getGraphEdgeSource();
	int iSink = link.getGraphEdgeSink();
	slist<BulkSession*>* pSession = link.session_;
	slist<BulkSession*>::iterator iter;
	double time = timer.getTime();
	int M = this->_topology->getVertices();
	double nowCapacity;
	if (_lHandle == NULL) {
		_lHandle = fopen("Bulk_Log/LinkInfo.txt", "w+"); 
	}
	if (!((int)time % 60)) {
		nowCapacity = link.getVaryCapacity();
		double linktime = (int)time / 60;
		fprintf(_lHandle, "time:%f, iSource:%d, iSink:%d, capacity:%f\n", linktime, iSource, iSink, nowCapacity);
	} else {
		nowCapacity = link.getCapacity();
	}
	//double nowCapacity = getCapacityFromFile(time, iSource, iSink);
	//if (nowCapacity != 0) {
		//cout<<"nowCapacity:"<<nowCapacity<<endl;
		//cout<<"time:"<<time<<endl;
	//}
	if (_packetHandle == NULL) {
		_packetHandle = fopen("Bulk_Log/PacketsInfo.txt", "w+"); 
	}
	double fiNum = 0;
	map<double, int> sorted;
	//遍历session
	for (iter = pSession->begin(); iter != pSession->end(); iter++) {
		(*iter)->time_ = time;
		double difference = link.diffPackets((*iter)->id_);
		double demand = (*iter)->getDemand();
		double value;
		if (nowCapacity > (THRESHOLD * demand / M) && difference > 0) {
			value = difference / pow(demand, 2);
			sorted.insert(pair<double, int>(value, (*iter)->id_)); //存储 diff/demand^2 => sId
		}
	}
	double s = _computeS(sorted, link, nowCapacity);
	map<double, int>::reverse_iterator iterS;
	float fsum = 0;
	for (iterS = sorted.rbegin(); iterS != sorted.rend(); iterS++) {
		int sId = iterS->second;
		BulkSession* qSession;
		if ((qSession = link.findSession(sId)) != 0 && iterS->first != 0) { 
			double difference = link.diffPackets(sId);
			double demand = qSession->getDemand();
			int fi = ROUND((difference - s * pow(demand, 2)) / 2);
			if (fi <= 0) {
				fi = 0;
			}
			fiNum += fi;
			while (fiNum > nowCapacity) {
				fi--;
				fiNum--;
			}
		    fsum += fi * (difference - fi) / pow (demand, 2);
			if (_sinkHandle == NULL) {
				_sinkHandle = fopen("Bulk_Log/SinkInfo.txt", "w+"); 
			}
			qSession->send(fi, link, _sinkHandle, _packetHandle);
		}
	}
	return fsum;
}

/**
 * @brief _computeS 
 * back算法配套的排序函数(求出S+集合域), 并求出s
 * @param {map<double, int>} sorted //map遍历，从小到大
 * @param {BulkLink} link //边
 * @param {double} capacity //传输带宽
 * @return {double} 返回计算之后的s
 */
double bulkBackPressure::_computeS(map<double, int>& sorted, BulkLink link, double capacity)
{
	map<double, int>::reverse_iterator rIter;
	float sum = 0.0, over = 0.0, low = 0.0;
	vector<double> unsearch;
	int* difference = new int[sorted.size()];
	double* demand = new double[sorted.size()];
	int i = 0;
	for (rIter = sorted.rbegin(); rIter != sorted.rend(); rIter++) {
		unsearch.push_back(rIter->first);   //从大到小排序
		int sId = rIter->second;
		difference[i] = link.diffPackets(sId);
		BulkSession* p =  link.findSession(sId);
		demand[i] = p->getDemand();
		i++;
	}
	int lowIndex = 0, highIndex = i - 1, mid = 0;
	while (lowIndex <= highIndex) {  //二分查找法
		mid = lowIndex + ((highIndex - lowIndex) / 2);
		sum = 0.0; 
		float sfake = unsearch.at(mid);
		for (int j = 0 ; j <= mid; j++) {
			float temp = (difference[j] - sfake * pow(demand[j], 2)) / 2;
			if (temp >= 0) {
				sum += temp;
			} else {
				break;
			}
		}
		if (sum < capacity) {
			lowIndex = mid + 1;
		} else if (sum > capacity) {
			highIndex = mid - 1;
		} else {
			break;
		}
	}
	if (sum > capacity) {
		mid = mid - 1;
	} 
	for (int j = 0; j <= mid; j++) {
		over += difference[j];
		low  += pow(demand[j], 2);
	}
	over -= 2 * capacity;
	if (low == 0.0) {
		return 0.0;
	}
	return over/low <= 0.0 ? 0.0 : over/low;
}

/**
	vector<slist<bulkPacket>* >& buffers = _sendbuf[tailId].getBuffers();
 * @brief propagate 
 * 每个节点传送数据包(递推)
 * 类似BFS算法
 * @param {queue<int>} q
 * @param {interge*} visited
 */
void bulkBackPressure::propagate(queue<int>* q, int* visited)
{
	slist<BulkLink*>::iterator iter;
	while (!q->empty()) {
		int u = q->front();  //get the front
		pushPacketsOut(u);   //push the packets out of the node 
		slist<BulkLink*>* pLink = nList_[u]->getOutputLink();
		for (iter = pLink->begin(); iter != pLink->end(); iter++) {
			int iSink = (*iter)->getGraphEdgeSink();
			if (!visited[iSink]) {
				q->push(iSink);
				visited[iSink] = 1;
			}
		}
		q->pop();
	}
}

/**
 * @brief pushPacketsOut 
 * 将节点中的数据全部传输出去
 * @param {interge} nodeId
 */
void bulkBackPressure::pushPacketsOut(int nodeId)
{
	BulkNode* pSourceNode = nList_[nodeId];
	//pSourceNode->reallocAll();
	slist<BulkLink*>* outlink = pSourceNode->getOutputLink();
	slist<BulkLink*>::iterator iterLink; //遍历link
	vector<int>::iterator iterId;        //遍历sId (session id)
	//遍历outlink
	for (iterLink = outlink->begin(); iterLink != outlink->end(); iterLink++) {
		int iSinkId = (*iterLink)->getGraphEdgeSink();
		BulkNode* pSinkNode = nList_[iSinkId];
		//outlink上的session
		for (iterId = pSourceNode->sVector.begin(); iterId != pSourceNode->sVector.end(); iterId++) {
			BulkSession* nSession = (*iterLink)->findSession(*iterId);
			int nStore = pSourceNode->getStoreAmount(*iterId); //增加或者删除session
			if (nStore != 0) {
				if (nSession == NULL) {
					nSession = new BulkSession(*iterId, pSourceNode, pSinkNode);
					double demand = *pSourceNode->demand_[*iterId];
					nSession->setDemand(demand);
					(*iterLink)->addSession(*nSession);
				}
				nSession->start();
			} else {
				if (nSession != NULL) {
					nSession->stop();
					//pSourceNode->sVector.erase(iterId);
				}
			} //启动session(use the start and stop functions in session)
			
			if (!pSinkNode->sIdExisted(*iterId)) {
				pSinkNode->sVector.push_back(*iterId);
			}
		}
		dynamicPush(**iterLink);
	}
}
