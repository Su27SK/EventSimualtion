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
 * @return {bulkNode}
 */
bulkNode& bulkNode::setOriginal()
{
	_isOriginal = true;
	return *this;
}

/**
 * @brief setTerminal 
 * 设置该节点为session终节点
 * @return {bulkNode}
 */
bulkNode& bulkNode::setTerminal()
{
	_isTerminal = true;
	return *this;
}

/**
 * @brief getTerminal 
 * 获得flag, 判断是否是出口点
 * @return {boolean}
 */
bool bulkNode:: getTerminal()
{
	return _isTerminal;
}

/**
 * @brief getOriginal 
 * 获得flag, 判断是否是起始点
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
 * @brief addOutputLink 
 * 增加下一跳链路
 * @param {bulkLink*} link
*/
void bulkNode::addOutputLink(bulkLink* link)
{
	link->setTailId(output->size());
	output_->push_front(link);
}

/**
 * @brief addInputLink 
 * 增加进到该点链路
 * @param {bulkLink*} link
 */
void bulkNode::addInputLink(bulkLink* link)
{
	link->setHeadId(input->size());
	input_->push_front(link);
}
