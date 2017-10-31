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
 * @brief recv 
 *
 * @param {double} amount
 *
 * @return {double}
 */
double bulkOverlayAgent::recv(double amount)
{
	_residualStorage -= amount;
	_storage += amount;
	return amount;
}

/**
 * @brief send 
 *
 * @param {double} amount
 *
 * @return {double}
 */
double bulkOverlayAgent::send(double amount)
{
	double check = _storage - amount;
	if (check < 0.0) {
		amount = _storage;
	}
	_storage -= amount;
	_residualStorage += amount;
	return amount;
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
