#ifndef _BULKBACKPRESSURE_H_
#define _BULKBACKPRESSURE_H_
#include "bulkBackHandle.h"
#include "bulkNetwork.h"
#include <string.h>
#define THRESHOLD 0.1 //ε
class bulkBackPressure:public bulkNetwork
{
	private:
		double _computeS(map<double, int>& sorted, bulkLink link, double capacity);
		void _realloc();
	public:
		bulkBackPressure():bulkNetwork() {}
		virtual void handle();
		//virtual void dynamicPush(BulkLink& link);
		virtual float dynamicPush(bulkLink& link);
		void propagate(queue<int>* q, int* visited);
		void pushPacketsOut(int nodeId);
		double getCapacityFromFile(double time, int source, int sink);
};
#endif
