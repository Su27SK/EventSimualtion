#ifndef _FORDFULKERSION_H_
#define _FORDFULKERSION_H_
#include <vector>
#include <queue>
#include <algorithm>
#include "config.h"
#include "bulkOverlay.h"
class fordFulkersion
{
	private:
		static vector<bool> _marked;
		static vector<bulkFlow> _edgeTo;
		static double _value = 0.0;
		static bool _hasAugmentingPath(bulkOverlay G, int s, int t);
	public:
		fordFulkersion(int v) {
			_marked.resize(v + 1);
			_edgeTo.resize(v + 1);
		}
		static void FordFulkersion(bulkOverlay G, int s, int t);
		static double getValue();
		static bool intCut(int v);
};
#endif
