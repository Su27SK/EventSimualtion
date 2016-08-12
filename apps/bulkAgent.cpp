#include "bulkAgent.h"

/**
 * @brief recv 
 * @return {boolean} 
 */
bool bulkAgent::recv()
{
	slist<bulkLink*>* pLink = _node->getInputLink();
	slist<bulkLink*>::iterator iter = pLink->begin();
	for (; iter != pLink->end(); iter++) {
		recvToAgent(*iter);
	}
	return true;
}

/**
 * @brief send 
 * @return {boolean}
 */
bool bulkAgent::send()
{
	slist<bulkLink*>* pLink = _node->getOutputLink();
	slist<bulkLink*>::iterator iter = pLink->begin();
	for (; iter != pLink->end(); iter++) {
		sendFromAgent(*iter);
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
	for (int i = 0; i < link.headbuf_.size(); i++) {
		slist<bulkPacket>*  packets = link.pullPacketsFromBuf(i, headbuf_[i]->size());
		while (!packets->empty()) {
			bulkPacket& packet = link.headbuf_[i]->front();
			_recvbuf[headId].push_back(packet);
			link.headbuf_[i]->pop_front();
		}
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
	for (int i = 0; i < MAXSESSION ; i++) {
		slist<bulkPacket>* pPacket = _sendbuf[tailId].pullPacketsFromBuf(i, _requestBuf[i]);
		while (!pPacket->empty()) {
			bulkPacket& packet = pPacket->front();
			link.tailbuf_.push_back(packet);
			pPacket->pop_front();
		}
	}
}

/**
 * @brief getStoreAmount 
 * 获得该节点存储的数据包总数
 * @param {interge} sId
 *
 * @return {interge}
 */
int bulkAgent::getStoreAmount(int sId)
{
	vector<bulkBuffer>::iterator iter;
	int num = 0;
	for (iter = _sendbuf.begin(); iter != _sendbuf.end(); iter++) {
		num += iter->getPacketsAmount(sId);
	}
	for (iter = _recvbuf.begin(); iter != _recvbuf.end(); iter++) {
		num += iter->getPacketsAmount(sId);
	}
	return num;
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
