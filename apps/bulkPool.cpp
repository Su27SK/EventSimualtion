#include "BulkPool.h"
BulkPool::BulkPool():_packets(new BulkPackets())
{
	this->_pool = new slist<BulkPackets>(0);
}

BulkPool::BulkPool(BulkPackets* packetsModel)
{
	this->_pool = new slist<BulkPackets>(0);
	this->_packets = packetsModel;
	this->_packets->addPtr();
}

/**
 * @brief init 
 * 初始化100个数据包
 */
void BulkPool::init()
{
	for (int i = 0; i < this->INITSIZE; i++) {
		BulkPackets* newPackets = new BulkPackets();
		*newPackets  = *this->_packets;
		this->_pool->push_front(*newPackets);
	}
}

/**
 * @brief destroy
 * 销毁所有的数据包
 */
void BulkPool::destroy()
{
	slist<BulkPackets>::iterator iterStart;
	slist<BulkPackets>::iterator iterEnd;
	iterStart = this->_pool->begin();
	iterEnd = this->_pool->end();
	if (iterStart != iterEnd) {
		this->_pool->erase(iterStart, iterEnd);
	}
}

/**
 * @brief placePacketsToPool 
 *
 * @param {BulkPackets*} packets
 */
void BulkPool::placePacketsToPool(BulkPackets* packets)
{
	this->_pool->push_front(*packets);
}

/**
 * @brief getPacketsFromPool 
 * 从内存池中获得数据包
 * @return {BulkPackets*}
 */
BulkPackets* BulkPool::getPacketsFromPool()
{
	if (!this->_pool->empty()) {
		BulkPackets* packets = new BulkPackets();
		*packets = *this->_pool->begin();
		this->_pool->pop_front();
		return packets;
	} else {
		this->init();
		return this->getPacketsFromPool();
	}
}

void BulkPool::setPacketsType(BulkPackets* type)
{
	this->_packets = type;
}

BulkPool::~BulkPool()
{
	if (this->_packets->getPtr() == 1) {
		delete this->_packets;
	} else {
		this->_packets->reducePtr();
	}
	//cout<<"Delete Pool"<<endl;
	this->_pool->~slist();
	this->_packets = NULL;
	this->_pool = NULL;
}

