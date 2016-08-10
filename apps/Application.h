#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "Process.h"
class Application : public Process
{
	public:
		Application():enableRecv_(0), enableResume_(0){};
		virtual void send(int nbytes) = 0;
		virtual void recv(int nbytes) = 0;
	protected:
		virtual void start(){};
		virtual void stop(){};

		int enableRecv_;
		int enableResume_;
};
#endif
