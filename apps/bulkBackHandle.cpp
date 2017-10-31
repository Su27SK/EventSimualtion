#include "bulkBackHandle.h"

/**
 * @brief expire 
 * handle function
 */
void bulkBackHandleTimer::expire(Event*)
{
	t_->handle();
	t_->timeout();
}

/**
 * @brief start 
 */
void bulkBackHandle::start()
{
	running_ = 1;
	double t = next();
	timer_.sched(t);
}

/**
 * @brief stop 
 */
void bulkBackHandle::stop()
{
	running_ = 0;
}

/**
 * @brief timeout 
 */
void bulkBackHandle::timeout()
{
	if (running_) {
		double t = next();
		timer_.resched(t);
	} 
}

/**
 * @brief next 
 * 下一个时间点
 * @param {double} interval
 * @return {double}
 */
double bulkBackHandle::next(double interval)
{
	Timer::next(interval);
	return getNowTime();
}

/**
 * @brief next 
 * 下一个时间点
 * @return {double}
 */
double bulkBackHandle::next()
{
	Timer::next();
	return getNowTime();
}

/**
 * @brief getNowTime 
 * 获得当前时间
 * @return 
 */
double bulkBackHandle::getNowTime()
{
	return Timer::getTime();
}
