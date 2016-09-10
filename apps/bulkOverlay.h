#ifndef _BULKOVERLAY_H_
#define _BULKOVERLAY_H_
#include "fordFulkersion.h"
#include "flowNetwork.h"
class bulkOverlay:public flowNetwork 
{
	private:
		vector<bulkFlow> _routeToOId;
		double _flow;
	public:
		bulkOverlay():flowNetwork() {
			cout<<"Default BulkOverlay Network"<<endl;
		}
		bulkOverlay(Graph* graph): flowNetwork(graph) {}
		bool scheduling(int v, int u);
		bool updating();
		void initNetBottlenecks();
};
#endif
