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
	for (int i = 0; i < MAXSESSION; i++) {
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
	for (int i = 0; i < MAXSESSION; i++) {
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
					bufSum = &outBufSum_[index][sId];
					pBuf = &_sendbuf[index];
				} else if (tag == IN) {
					index = (*iter)->getHeadId();
					bufSum = &inBufSum_[index][sId];			
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

void bulkAgent::reallocAll()
{
	
}
