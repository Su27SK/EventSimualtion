#ifndef _TIMERHANDLER_H_
#define _TIMERHANDLER_H_
#include "Scheduler.h"
#define TIMER_HANDLED -1.0 
class TimerHandler: public Handler
{
	public:
		TimerHandler():status_(TIMER_IDLE) {}
		void sched(double delay);   //cannot be pending, 与Scheduler交互的函数
		void resched(double delay); //may or may not be pending, if you don't know the pending status, call resched()
		void cancel();
		inline void forceCancel() { //cancel!
			if (status_ == TIMER_PENDING) {
				_cancel();
			}
		}
		enum TimerStatus {TIMER_IDLE, TIMER_PENDING, TIMER_HANDLING};
		//TIMER_IDLE: 空闲
		//TIMER_PENDING: 准备
		//TIMER_HANDLING: 处理中(运行)
		int status() {return status_;}
	protected:
		virtual void expire(Event*) = 0;  //must be filled
		virtual void handle(Event*); 
		int status_;
		Event event_;
	private:
		inline void _sched(double delay) {
			(void)Scheduler::instance().schedule(this, &event_, delay);
		}
		inline void _cancel() {
			(void)Scheduler::instance().cancel(&event_);
		} //no need to free event_ since it's statically allocated
};
#endif
