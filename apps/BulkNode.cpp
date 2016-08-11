#include "BulkNode.h"

/**
 * @brief _defaultInit 
 * 缺省初始化函数
 */
void BulkNode::_defaultInit()
{
	output_ = new slist<BulkLink*>(0);
	input_ = new slist<BulkLink*>(0);
	_isTerminal = false;
	_isOriginal = false;
	time_ = 0.0;
	demand_ = new double* [MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++) {
		demand_[i] = new double;
	}
}


/**
 * @brief _getAllWeight 
 * 获得所有E[c(e)(t)]期望倒数之和
 * @return 
 */
double BulkNode::_getAllWeight()
{
	slist<BulkLink*>::iterator iter;
	double sumWeight = 0;
	double singleWeight;
	int i = 0;
	slist<BulkLink*>* pLink = output_;
	while (i < 2) {
		for (iter = pLink->begin(); iter != pLink->end(); iter++) {
			if ((singleWeight = (*iter)->getWeight()) != 0) {
				sumWeight  += 1/singleWeight;
			}
		}
		pLink = input_;
		i++;
	}
	//cout<<"sumWeight:"<<sumWeight<<endl;
	return sumWeight;
}

/**
 * @brief BulkNode 
 * construct function
 * @param {GraphNode} node
 */
BulkNode::BulkNode(const GraphNode& node):GraphNode(node)
{
	this->_defaultInit();
}

/**
 * @brief BulkNode 
 * construct function
 * @param {GraphNode} node
 */
BulkNode::BulkNode(GraphNode& node):GraphNode(node)
{
	this->_defaultInit();
}

/**
 * @brief getStoreSize 
 * get the session's Store Size(the explicit size)
 * @param {interge} sId
 * @param {unit} type = Kb
 *
 * @return {interge}
 */
double BulkNode::getStoreSize(int sId, unit type)
{
	double amount = 0;
	int i = 0;
	slist<BulkLink*>::iterator sIter;
	for (sIter = input_->begin(); sIter != input_->end(); sIter++) {
		queue<BulkPackets>* pHead = (*sIter)->getHead(sId);
		int nSize = pHead->size();
		while (i < nSize) {
			BulkPackets& p = pHead->front();
			pHead->pop();
			amount += p.getBulkPacketsSize(type);
			pHead->push(p);
			i++;
		}
	}
	i = 0;
	for (sIter = output_->begin(); sIter != output_->end(); sIter++) {
		queue<BulkPackets>* pTail = (*sIter)->getTail(sId);
		int nSize = pTail->size();
		while (i < nSize) {
			BulkPackets& p = pTail->front();
			pTail->pop();
			amount += p.getBulkPacketsSize(type);
			pTail->push(p);
			i++;
		}
	}
	return amount;
}

/**
 * @brief getStore 
 * get the session's Store Packets, and re-realloc the packets
 * @param {interge} sId
 * @return {queue<BulkPackets>*}
 */
queue<BulkPackets>* BulkNode::getStore(int sId)
{
	//double amount = 0;
	queue<BulkPackets>* q = new queue<BulkPackets>;
	slist<BulkLink*>::iterator sIter;
	int i = 0;
	slist<BulkLink*>* pLink = input_;
	while (i < 2) {
		for (sIter = pLink->begin(); sIter != pLink->end(); sIter++) {
			queue<BulkPackets>* p; 
			if (i) {
				p = (*sIter)->tail_[sId];
				//amount += p->size();
			} else {
				p = (*sIter)->head_[sId];
				//amount += p->size();
			}
			while (!p->empty()) {
				BulkPackets& packets = p->front();
				q->push(packets);
				p->pop();
			}
		}
		pLink = output_;
		i++;
	}
	//cout<<"amount:"<<amount<<endl;
	return q;
}

/**
 * @brief getStoreAmount 
 * 获得node节点中存储数据包的数量
 * @param {interge} sId
 * @return {interge}
 */
int BulkNode::getStoreAmount(int sId)
{
	int amount = 0;
	slist<BulkLink*>::iterator sIter;
	int i = 0;
	slist<BulkLink*>* pLink = input_;
	while (i < 2) {
		for (sIter = pLink->begin(); sIter != pLink->end(); sIter++) {
			queue<BulkPackets>* p; 
			if (i) {
				p = (*sIter)->tail_[sId];
				amount += p->size();
			} else {
				p = (*sIter)->head_[sId];
				amount += p->size();
			}
		}
		pLink = output_;
		i++;
	}
	return amount;
}

/**
 * @brief setOriginal 
 * 设置该节点为session起点
 * @return {BulkNode}
 */
BulkNode& BulkNode::setOriginal()
{
	this->_isOriginal = true;
	return *this;
}

/**
 * @brief setTerminal 
 * 设置该节点为session终节点
 * @return {BulkNode}
 */
BulkNode& BulkNode::setTerminal()
{
	this->_isTerminal = true;
	return *this;
}

/**
 * @brief sIdExisted 
 * 检查sId是否存在该节点中
 * @param {interge} sId
 * @return {boolean}
 */
bool BulkNode::sIdExisted(int sId)
{
	vector<int>::iterator result = find(sVector.begin(), sVector.end(), sId);
	if (result == sVector.end()) {
		return false;
	} else {
		return true;
	}
}

/**
 * @brief getTerminal 
 * 获得flag, 判断是否是出口点
 * @return {boolean}
 */
bool BulkNode:: getTerminal()
{
	return this->_isTerminal;
}

/**
 * @brief getOriginal 
 * 获得flag, 判断是否是起始点
 * @return {boolean}
 */
bool BulkNode::getOriginal()
{
	return this->_isOriginal;
}

/**
 * @brief getOutputLink 
 * get the link that to the next route
 * @return slist<BulkLink>
 */
slist<BulkLink*>* BulkNode::getOutputLink()
{
	return output_;
}

/**
 * @brief getInputLink 
 * get the link that from the prev route
 * @return slist<BulkLink>
 */
slist<BulkLink*>* BulkNode::getInputLink()
{
	return input_;
}

/**
 * @brief reallocSize 
 * 对在BulkNode中的特定session重新分配size大小
 * @param {interge} sId
 */
void BulkNode::reallocSize(int sId)
{
	unit type = Kb;
	double qsv = this->getStoreSize(sId, type);
	slist<BulkLink*>::iterator iter;
	double singleWeight;
	double allWeight = this->_getAllWeight();
	for (iter = output_->begin(); iter != output_->end(); iter++) {
		if ((singleWeight = (*iter)->getWeight()) != 0) {
			double proportion = (1/singleWeight) / allWeight;
			double size = ROUND(qsv * proportion);
			if ((*iter)->tail_[sId]->size() == 0) {
				(*iter)->setTailPackets(sId, 4);
			}
			this->_reallocSize((*iter)->tail_[sId], size, type); 
		} else {
			(*iter)->clearTailPackets(sId);
		}
	}
	for (iter = input_->begin(); iter != input_->end(); iter++) {
		if ((singleWeight = (*iter)->getWeight()) != 0) {
			double proportion = (1/singleWeight) / allWeight;
			double size = ROUND(qsv * proportion);
			if ((*iter)->head_[sId]->size() == 0) {
				(*iter)->setHeadPackets(sId, 4);
			}
			this->_reallocSize((*iter)->head_[sId], size, type); 
		} else {
			(*iter)->clearHeadPackets(sId);
		}
	}
}

/**
 * @brief reallocPackets 
 * 对在BulkNode中特定的session重新分配packets数量
 * @param {interge} sId
 */
int BulkNode::reallocPackets(int sId)
{
	//cout<<"sId:"<<sId<<endl;
	queue<BulkPackets>* qsv = this->getStore(sId);
	queue<BulkPackets>* p;
	double sum = qsv->size();
	//cout<<"sum:"<<sum<<endl;
	slist<BulkLink*>::iterator sIter;
	double singleWeight;
	double allWeight = this->_getAllWeight();
	int i = 0, j;
	slist<BulkLink*>* pLink = input_;
	//cout<<"allWeight:"<<allWeight<<endl;
	while (i < 2) {
		for (sIter = pLink->begin(); sIter != pLink->end(); sIter++) {
			if ((singleWeight = (*sIter)->getWeight()) != 0) {
				double proportion = (1/singleWeight) / allWeight;
				double num = ROUND(sum * proportion);
				if (i) {
					p = (*sIter)->tail_[sId];
				} else {
					p = (*sIter)->head_[sId];
				}
				j = 0;
				while (j < num && !qsv->empty()) {
					BulkPackets& packets = qsv->front(); 
					p->push(packets);
					qsv->pop();
					j++;
				}
			}
		}
		pLink = output_;
		i++;
	}
	while (!qsv->empty()) {
		BulkPackets& packets = qsv->front(); 
		p->push(packets);
		qsv->pop();
	}

	i = 0;
	pLink = input_;
	while (i < 2) {
		for (sIter = pLink->begin(); sIter != pLink->end(); sIter++) {
			singleWeight = (*sIter)->getWeight();
			//cout<<"singleWeight:"<<singleWeight<<" ";
			if (i) {
				p = (*sIter)->tail_[sId];
			} else {
				p = (*sIter)->head_[sId];
			}
			//cout<<"num:"<<p->size()<<endl;
		}
		pLink = output_;
		i++;
	}
	return sum;
}

/**
 * @brief initNodePackets 
 * 初始化节点
 * @param {interge} sId
 * @param {queue<BulkPackets>*} recv
 */
void BulkNode::initNodePackets(int sId, queue<BulkPackets>* recv)
{
	if (!sIdExisted(sId)) {
		sVector.push_back(sId);
	}
	int numLink = this->getNumHeadQueue() + this->getNumTailQueue();   
	int numPackets = recv->size();
	queue<BulkPackets>* p;
	double mean = 0;
	double more = 0;
	if (numPackets < numLink) { //分配数据包
		mean = 1.0;
	} else {
		mean = numPackets / numLink;
		more = numPackets % numLink;
	}
	slist<BulkLink*>* pLink = input_;
	slist<BulkLink*>::iterator iter;
	int i = 0, count = 1;
	bool flag = false;
	while (i < 2) {
		for (iter = pLink->begin(); iter != pLink->end(); iter++) {
			if (i) {
				p = (*iter)->tail_[sId];
			} else {
				p = (*iter)->head_[sId];
			}
			for (int j = 0; j < mean; j++) {
				if (more != 0.0 && count == numLink && !flag) {
					mean = mean + more;
					flag = true;
				}
				if (!recv->empty()) {
					BulkPackets& packets = recv->front();
					p->push(packets);
					recv->pop();
				} else {
					break;
				}
			}
			count++;
		}
		pLink = output_;
		i++;
	}
}

/**
 * @brief reallocAll 
 */
void BulkNode::reallocAll(FILE* handle)
{
	int id = getNodeId();
	vector<int>::iterator iterId;
	for (iterId = sVector.begin(); iterId != sVector.end(); iterId++) {
		//reallocSize(*iterId);
		int sum = reallocPackets(*iterId);
		fprintf(handle, "time:%f, NodeId:%d, sId:%d, StoreNum:%d\n", time_, id, *iterId, sum);
	}
}

/**
 * @brief _reallocSize 
 * 在队列queue上重新分配packets
 * @param {queue<BulkPackets>} p(packets队列)
 * @param {double} size (该队列下总的传输数据大小)
 * @param {unit} type
 */
void BulkNode::_reallocSize(queue<BulkPackets>* p, double size, unit type)
{
	double meanSize = size / p->size();
	int nSize = p->size();
	int i = 0;
	while (i < nSize) {
		BulkPackets& q = p->front();
		BulkPacket* pBag = q.getModel();
		pBag->setPacketSize(meanSize/100).setPacketType(type);
		q.setTransmitNum(100);	
		p->pop();
		p->push(q);
		i++;
	}
}

/**
 * @brief addOutputLink 
 * 增加下一跳链路
 * @param {BulkLink*} edge
 */
void BulkNode::addOutputLink(BulkLink* link)
{
	//BulkLink* link = new BulkLink(*edge);
	this->output_->push_front(link);
}

/**
 * @brief addInputLink 
 * 增加进到该点链路
 * @param {BulkLink*} edge
 */
void BulkNode::addInputLink(BulkLink* link)
{
	//BulkLink* link = new BulkLink(*edge);
	this->input_->push_front(link);
}

