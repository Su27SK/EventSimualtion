#include "bulkBuffer.h"
/**
 * @brief pushPacketsToBuf 
 * 将数据包移入session id下的缓存
 * @param {interge} sId
 * @param {bulkPacket} packet
 */
void bulkBuffer::pushPacketsToBuf(int sId, bulkPacket& packet)
{
	_buffers[sId]->push_front(packet);
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
	while (!_buffers[sId]->empty() && count < num) {
		bulkPacket& packet = _buffers[sId]->front();
		pPackets->push_front(packet);
		_buffers[sId]->pop_front();
		count++;
	}
	return pPackets;
}

/**
 * @brief getPacketsAmount 
 * 获得session id下的数据包数量
 * @param {interge} sId
 *
 * @return {interge}
 */
int bulkBuffer::getPacketsAmount(int sId)
{
	return _buffers[sId]->size();
}

/**
 * @brief getBuffers 
 * 获得缓存buffers
 * @return {vector<slist<bulkPacket>* >}
 */
vector<slist<bulkPacket>* >& bulkBuffer::getBuffers()
{
	return _buffers;
}
