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
		static vector<bool> _marked;
		static vector<bulkFlow> _edgeTo;
		static double _value = 0.0;
		static bool _hasAugmentingPath(flowNetwork G, int s, int t);
	public:
		fordFulkersion() {}
		static void FordFulkersion(flowNetwork G, int s, int t);
		static double getValue();
		static vector<bulkFlow> getEdgeTo();
		static bool intCut(int v);
};
#endif
