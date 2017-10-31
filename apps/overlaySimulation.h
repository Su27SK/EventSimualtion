#ifndef _OVERLAYSIMULATION_H_
#define _OVERLAYSIMULATION_H_
#include "bulkOverlay.h"
#include "bulkNetStitcher.h"
#include "Scheduler.h"
class overlaySimulation:public bulkNetStitcher
{
	private:
		bulkOverlay* _overlay;
		int _s;   //source
		int _v;   //sink
		int _slot; //slot
	public:
		overlaySimulation(bulkOverlay* overlay, int slot):bulkNetStitcher() {
			_overlay = overlay;
			_s = _v = 0;
			_slot = slot;
		}
		overlaySimulation(int s, int v, bulkOverlay* overlay, int slot):bulkNetStitcher() {
			_overlay = overlay;
			_s = s;
			_v = v;
			_slot = slot;
		}
		virtual void timeout(double time);
		virtual void timeout();
	    virtual void send(int nbytes);
	    virtual void recv(int nbytes);
		double scheduling();
		void setLog(int time);
		void transmission(int time);
		void rescheduling();
		void updatingPrediction(int interval);
		void updatingReal(int interval);
};
#endif
