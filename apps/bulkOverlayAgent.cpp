#include "bulkOverlayAgent.h"

/**
 * @brief recv 
 *
 * @return {boolean}
 */
bool bulkOverlayAgent::recv()
{
	return true;
}

/**
 * @brief send 
 *
 * @return {boolean}
 */
bool bulkOverlayAgent::send()
{
	return true;
}

/**
 * @brief send 
 * 
 * @param {interge} v 起点
 * @param {interge} u 终点
 * @param {interge} F 发送大小
 */
void bulkOverlayAgent::send(int v, int u, int F)
{
	if (_updated) {
		bulkOverlay::scheduling(v, u);
		_updated = false;
	} else {
		
	}
}

/**
 * @brief getUpdated 
 *
 * @return {boolean}
 */
bool bulkOverlayAgent::getUpdated()
{
	return _updated;
}

/**
 * @brief setUpdated 
 *
 * @return {bulkOverlay}
 */
bulkOverlayAgent& bulkOverlayAgent::setUpdated()
{
	_updated = true;
	return *this;
}

/**
 * @brief predictedVolume 
 * 获得预测函数
 * @param {interge} time
 *
 * @return {double}
 */
double bulkOverlayAgent::predictedVolume(int time)
{
	return 0;
}

/**
 * @brief transmission 
 * 传输函数
 */
void bulkOverlayAgent::transmission(int amount)
{
	if (!_node.getTerminal()) {
		_storage -= amount;
	}
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
