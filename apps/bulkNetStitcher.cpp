#include "bulkNetStitcher.h"
inline void bulkNetStitcherTimer::expire(Event*)
{
	t_->timeout();
}

/**
 * @brief start 
 */
void bulkNetStitcher::start()
{
	running_ = 1;
	double t = next();
	timer_.sched(t);
}

/**
 * @brief stop 
 */
void bulkNetStitcher::stop()
{
	running_ = 0;
}

/**
 * @brief time 
 *
 * @return {double}
 */
double bulkNetStitcher::time()
{
	return (Scheduler::instance()).clock();
}

/**
 * @brief run 
 */
void bulkNetStitcher::run()
{
	(Scheduler::instance()).run();
}

/**
 * @brief next 
 *
 * @return {double}
 */
inline double bulkNetStitcher::next()
{
	return _delaytime;
}

/**
 * @brief setDelayTime 
 *
 * @param {double} time
 */
bool bulkNetStitcher::setDelayTime(double time)
{
	_delaytime = time;
	return true;
}
