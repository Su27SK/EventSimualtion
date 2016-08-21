#include "bulkBackPressure.h"
/**
 * @brief handle 
 */
void bulkBackPressure::handle()
{
	vector<bulkNode>::iterator iter = _agents.begin();
	
	for (; iter != _agents.end(); iter++) {
		iter->reallocAll();
		iter->send();
	}
	for (iter = _agents.begin(); iter != _agents.end(); iter++) {
		iter->recv();
	}
}
