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
	private:
		double _delaytime;
	public:
		bulkNetStitcher():Application(), running_(0), timer_(this) {
			_delaytime = 1.0;
		}
		virtual void timeout() = 0;
		void start();
		void stop();
		void run();
		bool setDelayTime(double time);
	protected:
		double next();
		double time();
		int running_;
		bulkNetStitcherTimer timer_;
};
#endif
