#ifndef	_TIMER_H_
#define _TIMER_H_
class Timer
{
	protected:
		static double now_;
		static double interval_;
	public:
		Timer(){}
		static void reset() {
			now_ = 0.0;
		}
		static double getTime() {
			return now_;
		}
		static void next() {
			now_ += interval_;
		}

		static void next(double interval) {
			now_ += interval;
		}
};
#endif
