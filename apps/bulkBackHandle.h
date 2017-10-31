#ifndef _BULKBACKHANDLE_H_
#define _BULKBACKHANDLE_H_
#include "TimerHandler.h"
#include "Timer.h"
class bulkBackHandle;
class bulkBackHandleTimer : public TimerHandler
{
	public:
		bulkBackHandleTimer(bulkBackHandle* t): TimerHandler(), t_(t){}
		bulkBackHandleTimer(): TimerHandler(){}
		virtual void expire(Event*);
	protected:
		bulkBackHandle* t_;
};

class bulkBackHandle
{
	public:
		bulkBackHandle():running_(0){}
		virtual void handle(){}
		void start();
		void stop();
		void timeout();
		double next(double interval);
		double next();
		double getNowTime();
	protected:
		int running_;
		bulkBackHandleTimer timer_;
};
#endif
