#include "Scheduler.h"
Scheduler* Scheduler::_instance;
int Scheduler::_uid = 1;
Scheduler::Scheduler():_clock(SCHED_START), _halted(0) 
{
}

Scheduler::~Scheduler()
{
	_instance = NULL;
}

/**
 * @brief schedule 
 * 对事件e进行调度，h是事件e处理的方式，delay是该事件耽误多少时间之后再执行
 * @param {Handler*} h
 * @param {Event*} e
 * @param {double} delay
 */
void Scheduler::schedule(Handler* h, Event* e, double delay)
{
	if (!h) {
		fprintf(stderr, "Scheduler: attempt to schedule an event with a NULL handler."
				"  Don't Do that at time %f\n", _clock);
		abort();
	}

	if (e->_uid <= 0) {
		printf("Scheduler: Event UID not valid!\n\n");
		abort();
	}

	if (delay < 0) {
		fprintf(stderr, "warning: Scheduler::schedule: scheduling event\n\t"
				"with negative delay (%f) at time %f.\n", delay, _clock);
	}

	if (_uid < 0) {
		fprintf(stderr, "Scheduler:: UID space exhausted!\n");
		abort();
	}

	e->_uid = _uid++;
	e->_handler = h;
	double t = _clock + delay;

	e->_time = t;
	insert(e);
}

/**
 * @brief run 
 * 事件运行
 */
void Scheduler::run()
{
	_instance = this;
	Event* p;
	

	while (!_halted && (p = deque())) {
		dispatch(p, p->_time);
	}
}

/**
 * @brief dispatch 
 * 事件分发处理
 * @param {Event*} p
 * @param {double} t
 */
void Scheduler::dispatch(Event* p, double t)
{
	if (t < _clock) {
		fprintf(stderr, "scheduler going backwards in time from %f to %f.\n", _clock, t);
		abort();
	}

	_clock = t;
	p->_uid = -p->_uid;    //being dispatched
	p->_handler->handle(p); //dispatch
}

/**
 * @brief dispatch 
 * 事件分发处理
 * @param {Event*} p
 */
void Scheduler::dispatch(Event* p)
{
	dispatch(p, p->_time);
}

/**
 * @brief reset 
 * 时钟重置函数
 */
void Scheduler::reset()
{
	_clock = SCHED_START;
}

/**
 * @brief dumpq 
 * 打印每个事件信息
 *
 */
void Scheduler::dumpq()
{
	Event* p;
	
	printf("Contents of scheduler queue (events) [cur time: %f]---\n", clock());
	while ((p = deque()) != NULL) {
		printf(" t:%f " , p->_time);
		printf(" uid:%d ", p->_uid);
		printf(" handler:%p ", reinterpret_cast<void *>(p->_handler));
	}
}


/**
 * @brief insert 
 * 事件链表中插入事件
 * @param {Event*} e
 */
void ListScheduler::insert(Event* e)
{
	double t = e->_time;
	Event** p;
	for (p = &_queue; *p != 0; p = &(*p)->_next) {
		if (t < (*p)->_time) {
			break;
		}
	}
	if (empty()) {
		_queue = e;
	} else {
		e->_next = *p;
		Event* prev = (*p)->_prev;
		prev->_next = e;
		e->_prev = prev;
		(*p)->_prev = e;
	}
}

/**
 * @brief cancel	
 * 事件链表中删除某一事件
 * @param {Event*} e
 */
void ListScheduler::cancel(Event* e)
{
	Event** p;
	if (e->_uid <= 0) {
		return ;
	}
	for (p = &_queue; *p != e; p = &(*p)->_next) {
		if (*p == 0) {
			abort();
		}
	}
	Event* prev = (*p)->_prev;
	prev->_next = (*p)->_next;
	(*p)->_next->_prev = prev;
	e->_uid = -e->_uid;
}

/**
 * @brief lookup 
 * 查找事件链表中的事件
 * @param {interge} uid
 *
 * @return {event}
 */
Event* ListScheduler::lookup(int uid)
{
	Event* e;
	for (e = _queue; e != 0; e = e->_next) {
		if (e->_uid == uid) {
			break;
		}
	}
	return (e);
}

/**
 * @brief deque 
 * 取出事件链表中的第一个事件(head),并删除
 * @return 
 */
Event* ListScheduler::deque()
{
	Event* e = _queue;
	if (e) {
		_queue = e->_next;
		e->_next->_prev = e->_next;
		e->_next = e->_prev = NULL;
	}
	return (e);
}

/**
 * @brief empty 
 * 判断事件链表是否为空
 * @return 
 */
bool ListScheduler::empty()
{
	if (this->_queue == 0) {
		return true;
	} else {
		return false;
	}
}

