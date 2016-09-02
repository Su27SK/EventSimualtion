#include "bulkOverlay.h"
/**
 * @brief join 
 * 加入Overlay
 * @param {bulkOverlayAgent} v
 */
bulkOverlay& bulkOverlay::join(bulkOverlayAgent& v)
{
	_oAgents.push_back(&v);
	return *this;
}

/**
 * @brief leave 
 * 离开Overlay
 * @param {bulkOveralyAgent} v
 */
bulkOverlay& bulkOverlay::leave(bulkOverlayAgent& v)
{
	vector<bulkOveralyAgent*>::iterator iter = _oAgents.begin();
	for (; iter != _oAgents.end();) {
		if ((*iter)->getOverlayId() == v.getOverlayId()) {
			iter = _oAgents.erase(iter);
		} else {
			iter++;
		}
	}
	return *this;
}

/**
 * @brief initEdgenecks
 */
void bulkOverlay::initEdgenecks()
{
	
}

/**
 * @brief initNetBottlenecks 
 */
void bulkOverlay::initNetBottlenecks()
{
	
}







