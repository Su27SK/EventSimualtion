#ifndef _BULKOVERLAYAGENT_H_
#define _BULKOVERLAYAGENT_H_
#include "bulkNode.h"
class bulkOverlayAgent:public Agent
{
	private:
		bulkNode  _node;
		int _time;
		int _vId;
		double _uplinkBottleneck;
		double _downlinkBottleneck;
		double _storage;
		double _backboneneck;
	public:
		bulkOverlayAgent(int vId, bulkNode node):Agent() 
	    {
			_vId = vId;
			_node = node;
			_uplinkBottleneck = _downlinkBottleneck = _storage = _backboneneck = 0.0;
		}
		double getPredictedVolume(int time);
		void transmission();
		void schedule();
		int getOverlayId();
};
#endif
