#include "bulkOverlay.h"
/**
 * @brief join 
 * 加入Overlay
 * @param {bulkOverlayAgent} v
 */
bulkOverlay& bulkOverlay::join(bulkOverlayAgent& v)
{
	_agents.push_back(&v);
	return *this;
}

/**
 * @brief leave 
 * 离开Overlay
 * @param {bulkOveralyAgent} v
 */
bulkOverlay& bulkOverlay::leave(bulkOverlayAgent& v)
{
	vector<bulkOveralyAgent*>::iterator iter = _agents.begin();
	for (; iter != _agents.end();) {
		if ((*iter)->getOverlayId() == v.getOverlayId()) {
			iter = _agents.erase(iter);
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
	vector<bulkOveralyAgent*>::iterator iter = _agents.begin();
	for (; iter != _agents.end();) {
		
	}
}

/**
 * @brief initNetBottlenecks 
 */
void bulkOverlay::initNetBottlenecks()
{
	
}
