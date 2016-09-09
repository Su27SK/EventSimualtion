#include "overlaySimulation.h"
/**
 * @brief _init 
 */
void overlaySimulation::_init()
{
	int n = _overlay->getVertices();
	for (int i = 1; i < n; i++) {
		bulkOverlayAgent* pOverlayAgent = new bulkOverlayAgent(i);
		_agents.push_back(pOverlayAgent);
	}
}

/**
 * @brief run 
 */
void overlaySimulation::run()
{
	(Scheduler::instance()).run();
}

/**
 * @brief scheduling 
 */
void overlaySimulation::scheduling()
{
	_overlay->scheduling(_s, _v);
	slist<bulkFlow*>::iterator iter;
	for (size_t i = 0; i < _agents.size(); i++) {
		int id = _agents[i]->getOverlayId();
		slist<bulkFlow*>* pFlow = _overlay->getAdj(id);
		for (iter = pFlow->begin(); iter != pFlow->end(); iter++) {
			int s = (*iter)->getGraphEdgeSource();
			int v = (*iter)->getGraphEdgeSink();
			_agents[s - 1]->setUplink((*iter)->getFlow());
			_agents[v - 1]->setDownlink((*iter)->getFlow());
		}
	}
}

/**
 * @brief send 
 *
 * @param {interge} nbytes
 */
void overlaySimulation::send(int nbytes)
{
	for (size_t i = 0; i < _agents.size(); i++) {
		_agents[i]->send();
	}
}

/**
 * @brief recv 
 *
 * @param {interge} nbytes
 */
void overlaySimulation::recv(int nbytes)
{
	for (size_t i = 0; i < _agents.size(); i++) {
		_agents[i]->recv();
	}
}

/**
 * @brief start 
 */
void overlaySimulation::start()
{
	bulkNetStitcher::start();
}

/**
 * @brief stop 
 */
void overlaySimulation::stop() 
{
	bulkNetStitcher::stop();
}

/**
 * @brief updating 
 */
void overlaySimulation::updating()
{
	_overlay->updating();
}
