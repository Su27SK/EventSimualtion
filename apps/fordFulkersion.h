#ifndef _FORDFULKERSION_H_
#define _FORDFULKERSION_H_
#include <vector>
#include <queue>
#include <algorithm>
#include "config.h"
#include "flowNetwork.h"
class fordFulkersion
{
	private:
		static bool* _marked;
		static bulkFlow* _edgeTo;
		static double _value;
	    static bool _hasAugmentingPath(flowNetwork G, int s, int t);
	public:
		fordFulkersion() {_value = 0.0;}
		static void FordFulkersion(flowNetwork G, int s, int t);
		static double getValue();
		static bulkFlow* getEdgeTo();
		static bool intCut(int v);
		static void clear();
};
#endif
