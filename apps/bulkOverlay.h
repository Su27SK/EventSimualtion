#ifndef _BULKOVERLAY_H_
#define _BULKOVERLAY_H_
#include "bulkOverlayAgent.h"
#include "bulkNetwork.h"
class bulkOverlay: public bulkNetwork
{
	private:
		vector<bulkOverlayAgent*> _agents;
		vector<bulkOverlayAgent*> _edgeVAgents;
		vector<bulkOverlayAgent*> _capacityVAgents;
	public:
		bulkOverlay():bulkNetwork() {
			RandomGenerator::init(time(NULL));
		}
		bulkOverlay(Graph* graph): bulkNetwork(graph) {
			RandomGenerator::init(time(NULL));
		}
		bulkOverlay& join(bulkOverlayAgent& v);
		bulkOverlay& leave(bulkOverlayAgent& v);
		void initEdgenecks();
		void initNetBottlenecks();
};
#endif
