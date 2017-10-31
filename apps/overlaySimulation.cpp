#include "overlaySimulation.h"

/**
 * @brief scheduling 
 */
double overlaySimulation::scheduling()
{
	if (_s <= 0 || _v <= 0) {
		return 0.0;
	}
	double time = _overlay->scheduling(0, _s, _v, 800);
	return time;
}

/**
 * @brief timeout 
 */
void overlaySimulation::timeout(double time)
{
	if (running_) {
		if (_slot == 0) {
			stop();
			return;
		}
		int F = 2000000;
		int baseTime = 0;
		int temp = 3;
		//_overlay->setAllStorage(_s, _v);
		for (int k = 1; k <= 1; k++) {
			//baseTime = (k - 1) * 60;
			baseTime = (k - 1) * temp;
			//for (int i = baseTime; i <= 60 * k; i++) {
			for (int i = baseTime; i <= temp * k; i++) {
				updatingReal(i);
			}
			int interval = _overlay->scheduling(baseTime, 1, 16, F);
			//_overlay->transmission(baseTime, 1, 16, interval);
		}
	}
}

/**
 * @brief setLog 
 *
 * @param {interge} time
 */
void overlaySimulation::setLog(int time)
{
	_overlay->setLog(time);
}

/**
 * @brief timeout 
 *
 */
void overlaySimulation::timeout()
{
	cout<<"Hello World"<<endl;
}

/**
 * @brief send 
 *
 * @param {interge} nbytes
 */
void overlaySimulation::send(int nbytes)
{
	
}

/**
 * @brief recv 
 *
 * @param {interge} nbytes
 */
void overlaySimulation::recv(int nbytes)
{
	
}

/**
 * @brief transmission 
 *
 * @param {interge} time
 */
void overlaySimulation::transmission(int time)
{
	if (_s <= 0 || _v <= 0) {
		return ;
	}
	_overlay->transmission(0, _s, _v, time);
}

/**
 * @brief updatingPrediction
 *
 * @param {interge} interval
 */
void overlaySimulation::updatingPrediction(int interval)
{
	string dir = "../Bulk_Config_File/link/5_error/";
	_overlay->updating(interval, dir, 0);
}

/**
 * @brief updatingReal 
 *
 * @param {interge} interval
 */
void overlaySimulation::updatingReal(int interval)
{
	string dir = "../Bulk_Config_File/link/";
	_overlay->updating(interval, dir, 1);
}
