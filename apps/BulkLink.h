#ifndef _BULKLINK_H_
#define _BULKLINK_H_
#include "GraphEdge.h"
#include "BulkNode.h"
#include "RandomGenerator.h"
class BulkLink:public GraphEdge
{
	private:
		int tailId;
		int headId;
	public:
		bulkBuffer headbuf_;
		bulkBuffer tailbuf_;
		BulkLink():GraphEdge() {}
		BulkLink(int from, int to):GraphEdge(from, to){}
		BulkLink(int from, int to, double weight, double capacity):GraphEdge(from, to, weight, capacity){}
		BulkLink(GraphEdge& edge):GraphEdge(edge){}
		double getVaryCapacity();
		~BulkLink(){};
};
#endif
