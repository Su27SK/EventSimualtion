#ifndef _BULKOVERLAYAGENT_H_
#define _BULKOVERLAYAGENT_H_
#include "bulkOverlay.h"
class bulkOverlayAgent:public Agent
{
	private:
		enum {MINUS = 1, PLUS = 2, CAP = 3, DEFAULT = 4};
		bulkNode _node;
		double _uplink;
		double _downlink;
		double _storage;
		int _time;
		int _oId;
		bool _updated;
	public:
		double demandFlow_;
		double slist<vector<int> > timeSeries_;
		int type_;
		bulkOverlayAgent(int oId, bulkNode node):_oId(oId), _node(node), Agent() 
	    {
			_uplink = _downlink = 0.0;
			_storage = 0.0;
			type_ = DEFAULT;
			_time = -1;
			_updated = false;
		}
		double predictedVolume(int time);
		void transmission(int amount);
		int getOverlayId();
		virtual bool recv();
		virtual bool send();
		bool getUpdated();
		void setUpdated();
		void send(int v, int u, int F);
		bulkOverlayAgent& setOverlayId(int id);
		void initBottlenecks();
};
#endif
