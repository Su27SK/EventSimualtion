#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <stdlib.h>
template<class T>
class Process
{
	public:
		Process():target_(0) {}
		inline Process*& target() {
			return target_;
		}
		virtual void processData(double size);
		virtual T* getData(double size);
		virtual void sendData(double size) {
			if (target_) {
				target_->processData(size);
			}
		}
	protected:
		Process<T>* target_;
};
#endif
