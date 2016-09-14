#include"bulkNetwork.h"
/**
 * @brief check
 * 检查参数是否正确
 * @param {interge} id
 *
 * @throw {bulkException}
 */
void bulkNetwork::check(int id, int min, int max) const throw(bulkException)
{
	if (topology_ == NULL) {
		throw new bulkException("topolog is not auloaded\n");
	}
	if (id > max && id < min) {
		throw new bulkException("id is out of range\n");
	}
}

/**
 * @brief handleOverException 
 * 处理异常函数
 * @param {bulkException} e
 */
void bulkNetwork::handleOverException(bulkException e) const
{
	e.init(__FILE__, __PRETTY_FUNCTION__, __LINE__);
	cout<<e.what()<<endl;
}

/**
 * @brief bulkNetwork 
 * construct function
 */
bulkNetwork::bulkNetwork(Graph* graph):nSource_(0), nSink_(0)
{
	if (graph != NULL) {
		topology_ = graph;
		init();
	}
}

/**
 * @brief init 
 * 初始化函数
 * 将GraphNode转化为bulkNode, nList中, key(nodeId) => value(bulkNode)
 */
void bulkNetwork::init()
{
	if (topology_ != NULL) {
		int n = topology_->getVertices();
		GraphNode* aList = topology_->getList();
		for (int i  = 1; i < n + 1; i++) {
			bulkNode* pNode = new bulkNode(aList[i]);
			slist<GraphEdge>* edge = aList[i].getEdge();
			slist<GraphEdge>::iterator iter = edge->begin();
			for (; iter != edge->end(); iter++) {
				if (aList[i].getNodeId() == iter->getGraphEdgeSource()) {
					bulkLink* link = new bulkLink(*iter);
					pNode->addOutputLink(link);
				} 
			}
			nList_.push_back(*pNode);
		}
		for (int i = 0; i < nList_.size(); i++) {
			slist<bulkLink*>* pLink = nList_[i].getOutputLink();
			slist<bulkLink*>::iterator iter = pLink->begin();
			for (; iter != pLink->end(); iter++) {
				int index = (*iter)->getGraphEdgeSink() - 1;
				bulkNode* pNode = &nList_[index]; 
				pNode->addInputLink(*iter);
			}
		}
	}
}

/**
 * @brief setSourceNode 
 * 设置packets数据包从Id节点进入
 * @param {interge} id
 * @param {interge} sId
 * 
 * @return {bulkNetwork}
 */
bulkNetwork& bulkNetwork::setSourceNode(int id, int sId)
{
	try {
		int n = topology_->getVertices();
		check(id, 1, n);
		check(sId, 1, MAXSESSION);
		int indexId = id - 1;
		nList_[indexId].setOriginal(sId);
		sourceList_.insert(pair<int, bulkNode*>(id, &nList_[indexId]));
		nSource_++;
		return *this;
	} catch (bulkException e) {
		handleOverException(e);
	}
}

/**
 * @brief setSinkNode 
 * 设置数据包packets从Id节点流出
 * @param {interge} id
 * @param {interge} sId
 *
 * @return {bulkNetwork}
 */
bulkNetwork& bulkNetwork::setSinkNode(int id, int sId)
{
	try {
		int n = topology_->getVertices();
		check(id, 1, n);
		check(sId, 1, MAXSESSION);
		int indexId = id - 1;
		nList_[indexId].setTerminal(sId);
		sinkList_.insert(pair<int, bulkNode*>(id, &nList_[indexId]));
		nSink_++;
		return *this;
	} catch (bulkException e) {
		handleOverException(e);
	}
}

/**
 * @brief getSourceNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return {bulkNode}
 */
bulkNode* bulkNetwork::getSourceNodeById(int id) const
{
	if (!sourceList_.empty()) {
		map<int, bulkNode*>::const_iterator iter;
		iter = sourceList_.find(id);
		if (iter != sourceList_.end()) {
			return iter->second;
		}
	}
	return NULL;
}

/**
 * @brief getSinkNodeById 
 * 通过节点ID获得关于该节点的相关信息，以及邻居信息
 * @param {integer} id
 *
 * @return {bulkNode}
 */
bulkNode* bulkNetwork::getSinkNodeById(int id) const
{
	if (!sinkList_.empty()) {
		map<int, bulkNode*>::const_iterator iter;
		iter = sinkList_.find(id);
		if (iter != sinkList_.end()) {
			return iter->second;
		}
	}
	return NULL;
}

/**
 * @brief getNodeById 
 * 通过节点id获得相应节点
 * @param {interge} id
 *
 * @return {bulkNode}
 */
const bulkNode& bulkNetwork::getNodeById(int id) const
{
	try {
		int n = topology_->getVertices();
		check(id, 1, n);
		id--;
		return nList_[id];
	} catch (bulkException e) {
		handleOverException(e);
	}
}

/**
 * @brief setGraph 
 * 设置Graph
 * @param {Graph} graph
 */
void bulkNetwork::setGraph(Graph* graph)
{
	if (graph != NULL) {
		topology_ = graph;
	}
}

