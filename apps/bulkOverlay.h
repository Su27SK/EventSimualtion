#ifndef _BULKOVERLAY_H_
#define _BULKOVERLAY_H_
#include "flowNetwork.h"
#include "bulkOverlayAgent.h"
class bulkOverlay:public flowNetwork 
{
	private:
		vector<bulkOverlayAgent*> _oAgents;
	public:
		bulkOverlay():flowNetwork() {
			RandomGenerator::init(time(NULL));
		}
		bulkOverlay(Graph* graph): flowNetwork(graph) {
			RandomGenerator::init(time(NULL));
		}
		bulkOverlay& join(bulkOverlayAgent& v);
		bulkOverlay& leave(bulkOverlayAgent& v);
		void initEdgenecks();
		void initNetBottlenecks();
};
#endif
