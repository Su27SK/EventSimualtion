#ifndef _BULKOVERLAYAGENT_H_
#define _BULKOVERLAYAGENT_H_
#include "fordFulkersion.h"
#include "agent.h"
#include <vector>
#include <ext/slist>
using namespace __gnu_cxx;
using namespace std;
class bulkOverlayAgent:public Agent
{
	private:
		double _uplink;   //上传速率Gb/s
		double _downlink; //下载速率Gb/s
		double _limitUplink; //实际上传限制
		double _limitDownlink; //实际下载限制
		double _residualStorage;  //存储空间  
		double _storage; //已经存储
		int _oId;
	public:
		int time_;        //持续时间 s
		bulkOverlayAgent(int oId):_oId(oId), Agent() 
	    {
			_uplink = _downlink = _storage = 0.0;
			_limitUplink = _limitDownlink = INT_MAX;
			_residualStorage = MAXCAPACITY;
			time_ = 1;
		}
		virtual bool recv();
		virtual bool send();
		double getResidualStorage();
		double getStorage();
		int getOverlayId();
		bulkOverlayAgent& setOverlayId(int id);
		bulkOverlayAgent& setStorage(int nbytes);
		bulkOverlayAgent& setResidualStorage(int nbytes);
		bulkOverlayAgent& setUplink(double flow);
		bulkOverlayAgent& setDownlink(double flow);
		bulkOverlayAgent& setLimitUplink(double flow);
		bulkOverlayAgent& setLimitDownlink(double flow);
};
#endif
