#include "bulkBuffer.h"

/**
 * @brief _check 
 * 检查sId是否越界
 * @param {interge} sId
 * @return {interge}
 */
int bulkBuffer::_check(int sId)
{
	if (sId < 1 || sId >= MAXSESSION) {
		throw new bulkException("sId is overstep the boundary in buffers module");
	}
	return sId;
}

/**
 * @brief _handleOverException 
 * 处理异常函数
 * @param {bulkException} e
 */
void bulkBuffer::_handleOverException(bulkException e) const
{
	e.init(__FILE__, __PRETTY_FUNCTION__, __LINE__);
	cout<<e.what()<<endl;
}

/**
 * @brief pushPacketsToBuf 
 * 将数据包移入session id下的缓存
 * @param {interge} sId
 * @param {bulkPacket} packet
 */
void bulkBuffer::pushPacketsToBuf(int sId, bulkPacket& packet)
{
	try {
		sId = _check(sId);
		_buffers[sId]->push_front(packet);
	} catch (bulkException e) {
		_handleOverException(e);
	}
}

/**
 * @brief pullPacketsFromBuf 
 * 将数据包移出session id下的缓存
 * @param {interge} sId
 * @param {interge} num 
 *
 * @return {slist<bulkPacket>}
 */
slist<bulkPacket>* bulkBuffer::pullPacketsFromBuf(int sId, int num)
{
	slist<bulkPacket>* pPackets = new slist<bulkPacket>();
	int count = 0;
	try {
		sId = _check(sId);
	} catch (bulkException e) {
		_handleOverException(e);
	}
	while (!_buffers[sId]->empty() && count < num) {
		bulkPacket& packet = _buffers[sId]->front();
		pPackets->push_front(packet);
		_buffers[sId]->pop_front();
		count++;
	}
	return pPackets;
}

/**
 * @brief getPacketsStore 
 * 获得具体数据包
 * @param {interge} sId
 *
 * @return slist<bulkPacket>* 
 */
slist<bulkPacket>* bulkBuffer::getPacketsStore(int sId)
{
	try {
		sId = _check(sId);
		return _buffers[sId];
	} catch (bulkException e) {
		_handleOverException(e);
	}
}

