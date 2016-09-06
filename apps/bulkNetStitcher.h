#ifndef _BULKNETSTITCHER_H_
#define _BULKNETSTITCHER_H_
#include "TimerHandler.h"
class bulkNetStitcher;

class bulkNetStitcherTimer: public TimerHandler
{
	public:
		bulkNetStitcherTimer(bulkNetStitcher* t):TimerHandler(), t_(t) {}
		inline virtual void expire(Event*);
	protected:
		bulkNetStitcher* t_;
};

class bulkNetStitcher: public Application
{
	public:
		bulkNetStitcher();
		void timeout();
	protected:
		void start();
		void stop();
		inline double next();

		double interval_;
		int running_;
		bulkNetStitcherTimer timer_;
};
#endif
