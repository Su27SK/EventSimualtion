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
 * @brief timeout 
 */
void bulkNetStitcher::timeout()
{
	if (running_) {
		cout<<"I Love You!"<<endl;
		double t = next();
		timer_.resched(t);
	}
}

/**
 * @brief next 
 *
 * @return {double}
 */
inline double bulkNetStitcher::next()
{
	return 1;
}
