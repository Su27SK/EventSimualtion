#ifndef _BULKLINK_H_
#define _BULKLINK_H_
#include "GraphEdge.h"
#include "bulkNode.h"
#include "RandomGenerator.h"
#include "bulkBuffer.h"
class bulkLink:public GraphEdge
{
	private:
		int _tailId; //node中
		int _headId; //node中
	public:
		bulkBuffer headbuf_;
		bulkBuffer tailbuf_;
		bulkLink():GraphEdge() {_tailId = _headId = -1;}
		bulkLink(int from, int to):GraphEdge(from, to){_tailId = _headId = -1;}
		bulkLink(int from, int to, double weight, double capacity):GraphEdge(from, to, weight, capacity) {_tailId = _headId = -1;}
		bulkLink(GraphEdge& edge):GraphEdge(edge){_tailId = _headId = -1;}
		double getVaryCapacity();
		bulkLink& setTailId(int id);
		bulkLink& setHeadId(int id);
		int getTailId();
		int getHeadId();
		~bulkLink(){};
};
#endif
