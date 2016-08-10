#include <stdlib.h>
#include "TimerHandler.h"

/**
 * @brief cancel 
 * 取消不是准备状态的事件
 */
void TimerHandler::cancel()
{
	if (status_ != TIMER_PENDING) {
		fprintf(stderr, "Attempting to cancel timer at %p which is not scheduled\n",
				reinterpret_cast<void *>(this));
		abort();
	}
	_cancel();
	status_ = TIMER_IDLE;
}

/**
 * @brief sched 
 * 与Scheduler交互的函数, 安排空闲的事件进入调度类
 * @param {double} delay
 */
void TimerHandler::sched(double delay)
{
	if (status_ != TIMER_IDLE) {
		fprintf(stderr, "Couldn't schedule timer");
	}
	_sched(delay);
	status_ = TIMER_PENDING;
}

/**
 * @brief resched 
 * 重新安排事件Event进入调度类
 * @param {double} delay
 */
void TimerHandler::resched(double delay)
{
	if (status_ == TIMER_PENDING) {
		_cancel();
	}
	_sched(delay);
	status_ = TIMER_PENDING;
}

/**
 * @brief handle 
 * 事件处理函数
 * @param {event} e
 */
void TimerHandler::handle(Event* e)
{
	if (status_ != TIMER_PENDING) {
		abort();
	}
	status_ = TIMER_HANDLING;
	expire(e);
	//if it wasn't rescheduled, it's done
	if (status_ == TIMER_HANDLING) {
		status_ = TIMER_IDLE;
	}
}

