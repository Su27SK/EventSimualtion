#ifndef _BULKOVERLAY_H_
#define _BULKOVERLAY_H_
#include "fordFulkersion.h"
#include "flowNetwork.h"
#include "bulkOverlayAgent.h"
class bulkOverlayAgent;
class bulkOverlay:public flowNetwork 
{
	private:
		vector<slist<bulkFlow> > _vAdj;
		vector<bulkOverlayAgent*> _agents;
		void _init();
	public:
		bulkOverlay():flowNetwork() {
			_init();
			cout<<"Default BulkOverlay Network"<<endl;
		}
		bulkOverlay(Graph* graph): flowNetwork(graph) {
			_init();
		}
		void initVirtual(int time);
		int initVirtualSource(int F, int v);
		void addEdge(bulkFlow e);
		void transmission(int time);
		double scheduling(int v, int u, int F);
		bool updating(int interval, string path);
		double initNetBottlenecksWithT(int v, int u, int F);
		int getVirtualVertices();
		slist<bulkFlow> getVirtualAdj(int v);
		void clearVirtualAdj();
};
#endif
