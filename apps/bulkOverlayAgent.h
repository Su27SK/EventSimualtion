#ifndef _BULKOVERLAYAGENT_H_
#define _BULKOVERLAYAGENT_H_
#include "bulkNode.h"
class bulkOverlayAgent:public Agent
{
	private:
		bulkNode _node;
		int _time;
		int _vId;
	public:
		double _storage;
		bulkOverlayAgent(int vId, bulkNode node):Agent() 
	    {
			_vId = vId;
			_node = node;
			_storage = 0.0;
			_time = 1;
		}
		double getPredictedVolume(int time);
		void transmission();
		void schedule();
		int getOverlayId();
		double getPhysicalUplink(int nextId);
		double getPhysicalDownlink(int nextId);
};
#endif
