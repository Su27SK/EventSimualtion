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
		double _route[MAXROUTE][MAXROUTE];
	public:
		bulkOverlay():flowNetwork() {
			_init();
			cout<<"Default BulkOverlay Network"<<endl;
		}
		bulkOverlay(Graph* graph): flowNetwork(graph) {
			_init();
		}
		void initVirtualNode(int baseTime, int time);
		int initVirtualSource(int F, int v, int u);
		void setAllStorage(int v, int u);
		void addEdge(bulkFlow e);
		void transmission(int baseTime, int v, int u, int time);
		bool pushTrafficByMinute(vector<bulkFlow> flows);
		double scheduling(int baseTime, int v, int u, int F);
		bool updating(int interval, string path, int flag);
		double initNetBottlenecksWithT(int baseTime, int v, int u, int F);
		int getAllStorage(int v, int u) const;
		int getVirtualVertices();
		slist<bulkFlow> getVirtualAdj(int v);
		void setLog(int time);
		void clearVirtualAdj();
};
#endif
