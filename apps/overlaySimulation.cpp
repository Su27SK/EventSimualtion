#include "overlaySimulation.h"

/**
 * @brief scheduling 
 */
double overlaySimulation::scheduling()
{
	if (_s <= 0 || _v <= 0) {
		return 0.0;
	}
	double time = _overlay->scheduling(_s, _v, 50);
	return time;
}

/**
 * @brief timeout 
 */
void overlaySimulation::timeout()
{
	if (running_) {
		if (_slot == 0) {
			stop();
			return;
		} 
		int now = time();
		double time;
		if (!(now %  (_slot - 1))) {
			int interval = now / (_slot - 1) + 1;
			updating(interval);
			double time = scheduling();
			setDelayTime(1);
		} else {
			setDelayTime(time);
			transmission(time);
		}
		double t = next();
		timer_.resched(t);
		stop();
	}
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
	_overlay->transmission(time);
}

/**
 * @brief updating 
 *
 * @param {interge} interval
 */
void overlaySimulation::updating(int interval)
{
	_overlay->updating(interval);
}

