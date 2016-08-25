#ifndef _BULKLINK_H_
#define _BULKLINK_H_
#include "GraphEdge.h"
#include "RandomGenerator.h"
#include "bulkBuffer.h"
class bulkLink:public GraphEdge
{
	private:
		int _tailId; //node中
		int _headId; //node中
		void _init();
	public:
		bulkBuffer headbuf_;
		bulkBuffer tailbuf_;
		vector<int> tailBufNum_;  //the agent which link the buf of tail (number packets)
		vector<int> headBufNum_;  //the agent which link the buf of head (number packets) 
		bulkLink():GraphEdge() {
			_init();
		}
		bulkLink(int from, int to):GraphEdge(from, to){_init();}
		bulkLink(int from, int to, double weight, double capacity):GraphEdge(from, to, weight, capacity) {_init();}
		bulkLink(GraphEdge& edge):GraphEdge(edge){_init();}
		double getVaryCapacity();
		void transfer();
		bulkLink& setTailId(int id);
		bulkLink& setHeadId(int id);
		int getTailId();
		int getHeadId();
		int diffPackets(int sId);
		~bulkLink(){};
};
#endif
