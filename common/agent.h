#ifndef _AGENT_H_
#define _AGENT_H_
#include "Packet.h"
class Agent
{
	protected:
		int aId_;
		double time_;
	public:
		Agent():Agent() {
			aId_ = -1;
			time_ = -1; 
		}
		virtual bool recv(slist<Packet>* list) = 0;
		virtual bool send(slist<Packet>* list) = 0;
};
#endif
