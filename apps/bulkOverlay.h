#ifndef _BULKOVERLAY_H_
#define _BULKOVERLAY_H_
#include "fordFulersion.h"
#include "flowNetwork.h"
#include "bulkOverlayAgent.h"
class bulkOverlay:public flowNetwork 
{
	private:
		static int _time = 0;
		static double _flowFromV = 0.0;
	public:
		bulkOverlay():flowNetwork() {
			RandomGenerator::init(time(NULL));
		}
		bulkOverlay(Graph* graph): flowNetwork(graph) {
			RandomGenerator::init(time(NULL));
		}
		bulkOverlay& join(bulkNode& v);
		bulkOverlay& leave(bulkNode& v);
		double static scheduling(int v, int u);
		void initEdgenecks();
		void initNetBottlenecks();
};
#endif
