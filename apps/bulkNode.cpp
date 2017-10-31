#include "bulkNode.h"
/**
 * @brief _defaultInit 
 * 缺省初始化函数
 */
void bulkNode::_defaultInit()
{
	output_ = new slist<bulkLink*>(0);
	input_ = new slist<bulkLink*>(0);
	_isTerminal = false;
	_isOriginal = false;
}

/**
 * @brief bulkNode 
 * construct function
 * @param {GraphNode} node
 */
bulkNode::bulkNode(const GraphNode& node):GraphNode(node)
{
	_defaultInit();
}

/**
 * @brief bulkNode 
 * construct function
 * @param {GraphNode} node
 */
bulkNode::bulkNode(GraphNode& node):GraphNode(node)
{
	_defaultInit();
}

/**
 * @brief setOriginal 
 * 设置该节点为session起点
 * @param {interge} sId
 *
 * @return {bulkNode}
 */
bulkNode& bulkNode::setOriginal(int sId)
{
	_isOriginal = true;
	originalIds_.insert(sId);
	return *this;
}

/**
 * @brief setTerminal 
 * 设置该节点为session终节点
 * @param {interge} sId
 *
 * @return {bulkNode}
 */
bulkNode& bulkNode::setTerminal(int sId)
{
	_isTerminal = true;
	terminalIds_.insert(sId);
	return *this;
}

/**
 * @brief getTerminal 
 *
 * @return {boolean}
 */
bool bulkNode::getTerminal()
{
	return _isTerminal;
}

/**
 * @brief getOriginal 
 *
 * @return {boolean}
 */
bool bulkNode::getOriginal()
{
	return _isOriginal;
}

/**
 * @brief getOutputLink 
 * get the link that to the next route
 * @return slist<bulkLink>
 */
slist<bulkLink*>* bulkNode::getOutputLink()
{
	return output_;
}

/**
 * @brief getInputLink 
 * get the link that from the prev route
 * @return slist<bulkLink>
 */
slist<bulkLink*>* bulkNode::getInputLink()
{
	return input_;
}

/**
 * @brief getOutputNum
 *
 * @return {interge}
 */
int bulkNode::getOutputNum()
{
	return output_->size();
}

/**
 * @brief getInputLink 
 *
 * @return {interge}
 */
int bulkNode::getInputNum()
{
	return input_->size();
}

/**
 * @brief addOutputLink 
 * 增加下一跳链路
 * @param {bulkLink*} link
*/
void bulkNode::addOutputLink(bulkLink* link)
{
	link->setTailId(output_->size());
	output_->push_front(link);
}

/**
 * @brief addInputLink 
 * 增加进到该点链路
 * @param {bulkLink*} link
 */
void bulkNode::addInputLink(bulkLink* link)
{
	link->setHeadId(input_->size());
	input_->push_front(link);
}
