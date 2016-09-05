#ifndef _BULKOVERLAYAGENT_H_
#define _BULKOVERLAYAGENT_H_
#include "bulkNode.h"
class bulkOverlayAgent:public Agent
{
	private:
		enum {MINUS = 1, PLUS = 2, CAP = 3, DEFAULT = 4};
		bulkNode _node;
		int _time;
		int _oId;
	public:
		double storage_;
		int type_;
		bulkOverlayAgent(int oId, bulkNode node):_oId(oId), _node(node), Agent() 
	    {
			storage_ = 0.0;
			type_ = DEFAULT;
			_time = -1;
		}
		double predictedVolume(int time);
		void transmission();
		void schedule();
		int getOverlayId();
		virtual bool recv();
		virtual bool send();
		bulkOverlayAgent& setOverlayId(int id);
		slist<bulkOverlayAgent*>* initDownEdgenecks();
		slist<bulkOverlayAgent*>* initUpEdgenecks();
		void initBottlenecks();
};
#endif
