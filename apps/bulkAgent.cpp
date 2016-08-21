#include "bulkAgent.h"
/**
 * @brief recv 
 * @return {boolean} 
 */
bool bulkAgent::recv()
{
	slist<bulkLink*>* pLink = _node.getInputLink();
	slist<bulkLink*>::iterator iter = pLink->begin();
	for (; iter != pLink->end(); iter++) {
		recvToAgent(**iter);
	}
	return true;
}

/**
 * @brief send 
 * @return {boolean}
 */
bool bulkAgent::send()
{
	slist<bulkLink*>* pLink = _node.getOutputLink();
	slist<bulkLink*>::iterator iter = pLink->begin();
	for (; iter != pLink->end(); iter++) {
		sendFromAgent(**iter);
		(*iter)->transfer();
	}
	return true;
}

/**
 * @brief recv 
 * 通过link接收数据, 从link缓存发送到Agent缓存
 * @param {bulkLink&} link
 */
void bulkAgent::recvToAgent(bulkLink& link)
{
	int headId = link.getHeadId();
	for (int i = 1; i <= MAXSESSION; i++) {
		slist<bulkPacket>*  packets = link.headbuf_.getPacketsStore(i);
		while (!packets->empty()) {
			bulkPacket& packet = packets->front();
			_recvbuf[headId].pushPacketsToBuf(i, packet);
			packets->pop_front();
		}
		packets->~slist();
		packets = NULL;
	}
}

/**
 * @brief send 
 * 通过link发送数据, 从Agent缓存发送到link缓存
 * @param {bulkLink&} link
 */
void bulkAgent::sendFromAgent(bulkLink& link)
{
	int tailId = link.getTailId();
	for (int i = 1; i <= MAXSESSION; i++) {
		slist<bulkPacket>* packets = _sendbuf[tailId].pullPacketsFromBuf(i, _requestBuf[tailId][i]);
		while (!packets->empty()) {
			bulkPacket& packet = packets->front();
			link.tailbuf_.pushPacketsToBuf(i, packet);
			packets->pop_front();
		}
		packets->~slist();
		packets = NULL;
	}
}

/**
 * @brief getStore 
 * 获得该节点存储的数据包
 * @param {interge} sId
 *
 * @return {slist<bulkPacket>*}
 */
slist<bulkPacket>* bulkAgent::getStore(int sId)
{
	vector<bulkBuffer>::iterator iter;
	slist<bulkPacket>* sum;
	int tag = OUT; 
	vector<bulkBuffer>* pBuf = &_sendbuf;
	while (tag != DEFAULT) {
		for (iter = pBuf->begin(); iter != pBuf->end(); iter++) {
			slist<bulkPacket>* pPacket = iter->getPacketsStore(sId);
			while (!pPacket->empty()) {
				bulkPacket& packet = pPacket->front();
				sum->push_front(packet);
				pPacket->pop_front();
			}
		}
		pBuf = &_recvbuf;
		tag++;
	}
	return sum;
}

/**
 * @brief getAllWeight 
 * 获得所有E[c(e)(t)]期望倒数之和
 * @return {double}
 */
double bulkAgent::getAllWeight()
{
	slist<bulkLink*>::iterator iter;
	double sumWeight = 0, singleWeight;
	int tag = OUT;
	slist<bulkLink*>* pLink = _node.getOutputLink();
	while (tag != DEFAULT) {
		for (iter = pLink->begin(); iter != pLink->end(); iter++) {
			if ((singleWeight = (*iter)->getWeight()) != 0) {
				sumWeight += 1 / singleWeight;
			}
		}
		pLink = _node.getInputLink();
		tag++;
	}
	return sumWeight;
}

/**
 * @brief reallocPackets 
 * 重新分配数据包,根据各条链路
 * @param {interge} sId
 *
 * @return {interge}
 */
int bulkAgent::reallocPackets(int sId)
{
	slist<bulkPacket>* qsv = getStore(sId);
	double sum = qsv->size();
	double allWeight = getAllWeight();
	double singleWeight;
	int tag = OUT;
	slist<bulkLink*>::iterator iter;
	slist<bulkLink*>* pLink = _node.getOutputLink();
	while (tag != DEFAULT) {
		for (iter = pLink->begin(); iter != pLink->end(); iter++) {
			if ((singleWeight = (*iter)->getWeight()) != 0) { 
				int count = 0, index;
				double proportion = (1/singleWeight) / allWeight;
				double num = ROUND(sum * proportion);
				bulkBuffer* pBuf;
				int* bufSum;
				if (tag == OUT) {
					index = (*iter)->getTailId();
					bufSum = &(iter->tailBufNum_[sId]);
					pBuf = &_sendbuf[index];
				} else if (tag == IN) {
					index = (*iter)->getHeadId();
					bufSum = &(iter->headBufNum_[sId]);
					pBuf = &_recvbuf[index];
				}
				while (!qsv->empty() && count < num) {
					bulkPacket& packet = qsv->front();
					pBuf->pushPacketsToBuf(sId, packet);
					qsv->pop_front();
					count++;
				}
				*bufSum = count;
			}
			pLink = _node.getInputLink();
			tag++;
		}
	}
	return (int)sum;
}

/**
 * @brief reallocRequests 
 * 对每个发送链路中的session分配发送数据包数量
 * @param {bulkLink} link
 *
 * @return {interge}
 */
float bulkAgent::reallocRequests(bulkLink& link)
{
	double nowCapacity = link.getCapacity();
	double fiNum = 0;
	map<double, int> sorted;
	//遍历session
	for (int i = 1; i <= MAXSESSION; i++) {
		double difference = link.diffPackets(i);
		double demand = sToDemand[i];
		if (nowCapacity > (THRESHOLD * demand / M) && difference > 0 && demand != 0) {
			double value = difference / pow(demand, 2);
			sorted.insert(pair<double, int>(value, i)); //存储 diff/demand^2 => sId
		}
	}
	double s = _computeS(sorted, link, nowCapacity);
	map<double, int>::reverse_iterator iterS;
	float fsum = 0;
	int tailId = link.getTailId();
	for (iterS = sorted.rbegin(); iterS != sorted.rend(); iterS++) {
		int sId = iterS->second;
		if (sToDemand[sId] != 0 && iterS->first != 0) { 
			double difference = link.diffPackets(sId);
			double demand = sToDemand[sId];
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
			_requestBuf[tailId] = fi;
		}
	}
	return fsum;
}

/**
 * @brief _computeS 
 * back算法配套的排序函数(求出S+集合域), 并求出s
 * @param {map<double, int>} sorted //map遍历，从小到大
 * @param {bulkLink} link //边
 * @param {double} capacity //传输带宽
 * @return {double} 返回计算之后的s
 */
double bulkAgent::_computeS(map<double, int>& sorted, bulkLink link, double capacity)
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
		demand[i] = sToDemand[sId];
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
 * @brief getAId 
 * 
 * @return {interge}
 */
int bulkAgent::getAId() const
{
	return _aId;
}

/**
 * @brief setSendBuf 
 * 设置发送缓存
 * @param {interge} num
 */
void bulkAgent::setSendBuf(int num)
{
	for(int i = 0; i < num; i++) {
		bulkBuffer* buf = new bulkBuffer();
		_sendbuf.push_back(*buf);
	}
}

/**
 * @brief setRecvBuf 
 * 设置接收缓存
 * @param {interge} num
 */
void bulkAgent::setRecvBuf(int num)
{
	for (int i = 0; i < num; i++) {
		bulkBuffer* buf = new bulkBuffer();
		_recvbuf.push_back(*buf);
	}
}

/**
 * @brief reallocAll 
 */
void bulkAgent::reallocAll()
{
	for (int i = 1; i <= MAXSESSION; i++) {
		reallocPackets(i);
	}
}

/**
 * @brief reallocAllRequests 
 */
void bulkAgent::reallocAllRequests()
{
	slist<bulkLink*>* pLink = _node.getOutputLink();
	slist<bulkLink*>::iterator iter = pLink->begin();
	for (; iter != pLink->end(); iter++) {
		reallocRequests(**iter);
	}
}
