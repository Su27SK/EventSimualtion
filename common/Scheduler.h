#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include <stdio.h>
#include <stdlib.h>
class Event;
class Handler
{
	public:
		virtual ~Handler() {}
		virtual void handle(Event* event) = 0;
};

class Event
{
	public:
		Event* _next;      /* event list */
		Event* _prev;
		Handler* _handler; /* handler to call when event ready */
		double _time;
		int _uid;
		Event():_time(0), _uid(0) {
			this->_prev = this;
			this->_next = NULL;
		}
};

#define SCHED_START 0.0  /* start time (secs) */

class Scheduler
{
	public:
		static Scheduler& instance() {
			return (*_instance);
		}
		void schedule(Handler*, Event*, double delay);
		virtual void run();
		virtual void cancel(Event*) = 0;
		virtual void insert(Event*) = 0;
		virtual Event* lookup(int uid) = 0;
		virtual Event* deque() = 0;  //next event (removes from q)
		virtual const Event* head() = 0; //next event (not removed from q)
		double clock() const {
			return (_clock);
		}
		virtual void sync(){};
		virtual double start() {     //start time
			return SCHED_START;
		}
		virtual void reset();
	protected:
		void dumpq(); //for debug: remove + print remaining events
		void dispatch(Event* );  //execute an event
		void dispatch(Event*, double); //execute event, set _clock
		Scheduler();
		virtual ~Scheduler();
		//int command(int argc, const char* const* argv);
		double _clock;
		int _halted;  //暂停
		static Scheduler* _instance;
		static int _uid;
};

class ListScheduler:public Scheduler
{
	public:
		ListScheduler():_queue(0){}
		void cancel(Event*);
		void insert(Event*);
		bool empty();
		Event* deque();
		const Event* head() {return _queue;}
		Event* lookup(int uid);
	protected:
		Event* _queue;
};
#endif
