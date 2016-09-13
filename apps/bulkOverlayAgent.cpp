#include "bulkOverlayAgent.h"
/**
 * @brief recv 
 *
 * @return {boolean}
 */
bool bulkOverlayAgent::recv()
{
	_residualStorage -= _downlink * time_;
	_storage += _downlink * time_;
	return true;
}

/**
 * @brief send 
 *
 * @return {boolean}
 */
bool bulkOverlayAgent::send()
{
	_residualStorage += _uplink * time_;
	if (_storage > 0) {
		_storage -= _uplink * time_;
	}
	return true;
}

/**
 * @brief getOverlayId 
 * 获得Overlay Id
 * @return {interge}
 */
int bulkOverlayAgent::getOverlayId()
{
	return _oId;
}

/**
 * @brief setOverlayId 
 *
 * @param {interge} id
 *
 * @return {bulkOverlayAgent}
 */
bulkOverlayAgent& bulkOverlayAgent::setOverlayId(int id)
{
	_oId = id;
	return *this;
}

/**
 * @brief getStorage 
 *
 * @return {double}
 */
double bulkOverlayAgent::getStorage()
{
	return _storage;
}

/**
 * @brief getResidualStorage 
 *
 * @return {double}
 */
double bulkOverlayAgent::getResidualStorage()
{
	return _residualStorage;
}

/**
 * @brief setStorage 
 *
 * @param {interge} nbytes
 *
 * @return {bulkOverlayAgent}
 */
bulkOverlayAgent& bulkOverlayAgent::setStorage(int nbytes)
{
	_storage = nbytes;
	return *this;
}

/**
 * @brief setResidualStorage 
 *
 * @param {interge} nbytes
 *
 * @return {bulkOverlayAgent}
 */
bulkOverlayAgent& bulkOverlayAgent::setResidualStorage(int nbytes)
{
	_residualStorage = nbytes;
	return *this;
}

/**
 * @brief setUplink 
 *
 * @param {double} flow
 *
 * @return {bulkOverlayAgent}
 */
bulkOverlayAgent& bulkOverlayAgent::setUplink(double flow)
{
	_uplink = flow;
	return *this;
}

/**
 * @brief setUplink 
 *
 * @param {double} flow
 *
 * @return {bulkOverlayAgent}
 */
bulkOverlayAgent& bulkOverlayAgent::setDownlink(double flow)
{
	_downlink = flow;
	return *this;
}
