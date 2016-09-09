#ifndef _OVERLAYSIMULATION_H_
#define _OVERLAYSIMULATION_H_
#include "bulkOverlay.h"
#include "bulkOverlayAgent.h"
#include "bulkNetStitcher.h"
#include "Scheduler.h"
class overlaySimulation:public bulkNetStitcher
{
	private:
		bulkOverlay* _overlay;
		vector<bulkOverlayAgent*> _agents;
		int _s;   //source
		int _v;   //sink
		void _init();
	public:
		overlaySimulation(bulkOverlay* overlay):bulkNetStitcher() {
			_overlay = overlay;
			_s = _v = 0;
		}
		overlaySimulation(int s, int v, bulkOverlay* overlay):bulkNetStitcher() {
			_overlay = overlay;
			_s = s;
			_v = v;
		}
	    virtual void send(int nbytes);
	    virtual void recv(int nbytes);
		void scheduling();
		void transfer(int vFile);
		void rescheduling();
		void updating();
		void run();
		void start();
		void stop();
};
#endif
