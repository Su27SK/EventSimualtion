#ifndef _OVERLAYSIMULATION_H_
#define _OVERLAYSIMULATION_H_
#include "bulkOverlay.h"
#include "bulkOverlayAgent.h"
#include "bulkNetStitcher.h"
#include "Scheduler.h"
class overlaySimulation:public bulkNetStitcher
{
	private:
		bulkOverlay _overlay;
		vector<bulkOverlayAgent*> _agents;
		int _s;   //source
		int _v;   //sink
		void _init() {
			int n = overlay.getVertices();
			for (int i = 1; i < n; i++) {
				bulkOverlayAgent* pOverlayAgent = new bulkOverlayAgent(i);
				_agents.push_back(pOverlayAgent);
			}
		}
	public:
		overlaySimulation(bulkOverlay& overlay):bulkNetStitcher() {
			_overlay = overlay;
			_s = _v = 0;
		}
		overlaySimulation(int s, int v, bulkOverlay& overlay):bulkNetStitcher() {
			_overlay = overlay;
			_s = s;
			_v = v;
		}
	    virtual void send(int nbytes) {
			for (size_t i = 0; i < _agents.size(); i++) {
				_agents[i]->send();
			}
		}
	    virtual void recv(int nbytes) {
			for (size_t i = 0; i < _agents.size(); i++) {
				_agetns[i]->recv();
			}
		}
		void scheduling() {
			_overlay.scheduling(_s, _v);
			slist<bulkFlow*>::iterator iter;
			for (size_t i = 0; i < _agents.size(); i++) {
				int id = _agetns[i]->getOverlayId();
				slist<bulkFlow*>* pFlow = _overlay.getAdj(id);
				for (iter = pFlow->begin(); iter != pFlow->end(); iter++) {
					
					_agents[i]->setUplink();
				}
			}
		}
		void transfer(int vFile) {
			
		}
		void rescheduling() {
			
		}

		void updating() {
			_overlay.updating();
		}
		void run() {
			(Scheduler::instance()).run();
		}
		void start() {
			bulkNetStitcher::start();
		}
		void stop() {
			bulkNetStitcher::stop();
		}
};
#endif
