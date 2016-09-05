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
	vector<bulkOveralyAgent*>::iterator vIter = _oAgents.begin();
	for (; vIter != _oAgents.end();) {
		int i = 1;
		slist<bulkOverlayAgent*>* pOverlayAgents = (*vIter)->initDownEdgenecks();
		while (i <= 2) {
			while (!pOverlayAgents->empty()) {
				bulkOverlayAgent* pAgent = pOverlayAgents->pop_front();
				_oAgents.push(pAgent);
			}
			pOverlayAgents = (*vIter)->initUpEdgenecks();
			i++;
		}
	}
}

/**
 * @brief initNetBottlenecks 
 */
void bulkOverlay::initNetBottlenecks()
{

}
