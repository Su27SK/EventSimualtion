#ifndef _AGENT_H_
#define _AGENT_H_
#include "Packet.h"
class Agent
{
	protected:
		int aId_;
		double time_;
	public:
		Agent() {
			aId_ = -1;
			time_ = -1; 
		}
		virtual bool recv() = 0;
		virtual bool send() = 0;
};
#endif
