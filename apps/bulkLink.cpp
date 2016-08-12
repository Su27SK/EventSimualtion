#include "bulkLink.h"
/**
 * @brief getCapacity 
 * 获得时刻改变的链路带宽
 * @return {double}
 */
double bulkLink::getVaryCapacity()
{
	double w = getWeight();
	if (w > 0) {
		double c = RandomGenerator::genGaussianDouble(30);
		w = w == 14 ? 5 : 10;
		c = (int)(w + c);
		if (c <= 0) {
			c = 1.0;
		} else if (c > 95) {
			c = 95.0;
		}
		setCapacity(c);
		return c;
	} else {
		return GraphEdge::getCapacity();
	}
}

/**
 * @brief setTailId 
 *
 * @param {interge} id
 *
 * @return {bulkLink}
 */
bulkLink& bulkLink::setTailId(int id)
{
	_tailId = id;
	return *this;
}
		
/**
 * @brief setHeadId 
 *
 * @param {interge} id
 *
 * @return {bulkLink}
 */
bulkLink& bulkLink::setHeadId(int id)
{
	_headId = id;
	return *this;
}

/**
 * @brief getTailId 
 *
 * @return {interge}
 */
int bulkLink::getTailId()
{
	return _tailId;
}

/**
 * @brief getHeadId 
 *
 * @return {interge}
 */
int bulkLink::getHeadId()
{
	return _headId;
}