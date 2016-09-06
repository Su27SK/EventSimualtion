#include "bulkOverlay.h"
/**
 * @brief join 
 * 加入Overlay
 * @param {bulkNode} v
 *
 * @return {bulkOverlay}
 */
bulkOverlay& bulkOverlay::join(bulkNode& v)
{
	return *this;
}

/**
 * @brief leave 
 * 离开Overlay
 * @param {bulkNode} v
 *
 * @return {bulkOverlay}
 */
bulkOverlay& bulkOverlay::leave(bulkNode& v)
{
	return *this;
}

/**
 * @brief scheduling 
 *
 * @param {interge} v
 * @param {interge} u
 * @return {double}
 */
double bulkOverlay::scheduling(int v, int u)
{
	if ( ) {
		fordFulersion::FordFulersion(*this, v, u);
		_flowFromV = fordFulersion::getValue();
	}
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
