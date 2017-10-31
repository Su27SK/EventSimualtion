#ifndef _FORDFULKERSION_H_
#define _FORDFULKERSION_H_
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
#include "config.h"
#include "flowNetwork.h"
#include "bulkOverlay.h"
class bulkOverlay;
class fordFulkersion
{
	private:
		static vector<bool> _marked;
		static vector<int> _parent; //filled by BFS and to store path
		static double _value;
	    static bool _hasAugmentingPath(bulkOverlay G, int s, int t);
		static double rGraph[MAXMATRIX][MAXMATRIX];
		static double sGraph[MAXMATRIX][MAXMATRIX];
		static void _init(int n);
	public:
		static vector<vector<double> > _flow; //filled by the flow of path
		fordFulkersion() {_value = 0.0;}
		static void FordFulkersion(bulkOverlay G, int s, int t, int n);
		static double getValue();
		static vector<bulkFlow> getEdgeTo();
		static void setRGraph(bulkOverlay G, int n);
		static bool intCut(int v);
		static double getEdgeRateBySecond(int s, int e);
		static void clear();
};
#endif
