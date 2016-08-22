#include "bulkPool.h"
bulkPool::bulkPool()
{
	_pool = new slist<bulkPacket>(0);
}

/**
 * @brief init 
 * 初始化INITSIZE个数据包
 */
void bulkPool::init()
{
	for (int i = 0; i < INITSIZE; i++) {
		bulkPacket* packet = new bulkPacket();
		_pool->push_front(*packet);
	}
}

/**
 * @brief destroy
 * 销毁所有的数据包
 */
void bulkPool::destroy()
{
	slist<bulkPacket>::iterator iterStart;
	slist<bulkPacket>::iterator iterEnd;
	iterStart = _pool->begin();
	iterEnd = _pool->end();
	if (iterStart != iterEnd) {
		_pool->erase(iterStart, iterEnd);
	}
}

/**
 * @brief placePacketsToPool 
 *
 * @param {bulkPacket*} packets
 */
void bulkPool::placePacketsToPool(bulkPacket* packets)
{
	_pool->push_front(*packets);
}

/**
 * @brief getPacketsFromPool 
 * 从内存池中获得数据包
 * @return {bulkPacket&}
 */
bulkPacket& bulkPool::getPacketsFromPool()
{
	if (!this->_pool->empty()) {
		bulkPacket& packet = _pool->front();
		_pool->pop_front();
		return packet;
	} else {
		init();
		return getPacketsFromPool();
	}
}

/**
 * @brief ~bulkPool 
 * 析构函数
 */
bulkPool::~bulkPool()
{
	//cout<<"Delete Pool"<<endl;
	this->_pool->~slist();
	this->_pool = NULL;
}

