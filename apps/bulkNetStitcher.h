#ifndef _BULKNETSTITCHER_H_
#define _BULKNETSTITCHER_H_
#include "TimerHandler.h"
#include "bulkOverlay.h"
#include "Application.h"
class bulkNetStitcher;

class bulkNetStitcherTimer: public TimerHandler
{
	public:
		bulkNetStitcherTimer(bulkNetStitcher* t):TimerHandler(), t_(t) {}
		virtual void expire(Event*);
	protected:
		bulkNetStitcher* t_;
};

class bulkNetStitcher: public Application
{
	public:
		bulkNetStitcher():Application(), running_(0), timer_(this) {}
		void timeout();
	protected:
		void start();
		void stop();
		double next();
		double interval_;
		int running_;
		bulkNetStitcherTimer timer_;
};
#endif
