#include "bulkOverlayAgent.h"

/**
 * @brief getPredictedVolume 
 * 获得预测函数
 * @param {interge} time
 *
 * @return 
 */
double bulkOverlayAgent::getPredictedVolume(int time)
{
	
}

/**
 * @brief transmission 
 * 传输函数
 */
void bulkOverlayAgent::transmission()
{
	
}

/**
 * @brief schedule 
 * 调度函数
 */
void bulkOverlayAgent::schedule()
{
	
}

/**
 * @brief getOverlayId 
 * 获得Overlay Id
 * @return {interge}
 */
int bulkOverlayAgent::getOverlayId()
{
	return _vId;
}

/**
 * @brief initDownEdgenecks 
 * init Down edge necks
 * @return {slist<bulkOverlayAgent*>}
 */
slist<bulkOverlayAgent*>* bulkOverlayAgent::initDownEdgenecks()
{
	slist<bulkOverlayAgent*>* pOverlayAgents = new slsit<bulkOverlayAgent*>(0);
	slist<bulkLink*>* input = _node.getInputLink();
	slist<bulkLink*>::iterator iter = input->begin();
	if (!_node.getOriginal()) {
		for (; iter != input->end(); iter++) {
			int nodeId = _node.getNodeId();
			bulkNode* pNode = new bulkNode(nodeId);	
			bulkLink* downLink = new bulkLink(nodeId, nodeId);
			downLink->setCapacity((*iter)->getCapacity());
			pNode->addOutputLink(downLink);
			bulkOverlayAgent* downAgent = new bulkOverlayAgent(-1, *pNode);
			downAgent->type_ = MINUS;
			pOverlayAgents.push_back(downAgent);
			input->erase(iter);
		}
	}
	return pOverlayAgents;
}

/**
 * @brief initUpEdgenecks 
 * init up edge necks
 * @return {slist<bulkOverlayAgent*>}
 */
slist<bulkOverlayAgent*>* bulkOverlayAgent::initUpEdgenecks()
{
	slist<bulkOverlayAgent*>* pOverlayAgents = new slsit<bulkOverlayAgent*>(0);
	slist<bulkLink*>* output = _node.getOutputLink();
	slist<bulkLink*>::iterator iter = output->begin();
	if (!_node.getTerminal()) {
		for (; iter != output->end(); iter++) {
			int nodeId = _node.getNodeId();
			bulkNode* pNode = new bulkNode(nodeId);	
			bulkLink* downLink = new bulkLink(nodeId, nodeId);
			downLink->setCapacity((*iter)->getCapacity());
			pNode->addInputLink(downLink);
			bulkOverlayAgent* upAgent = new bulkOverlayAgent(-1, *pNode);
			upAgent->type_ = PLUS;
			pOverlayAgents.push_back(upAgent);
			output->erase(iter);
		}
	}
	return pOverlayAgents;
}

