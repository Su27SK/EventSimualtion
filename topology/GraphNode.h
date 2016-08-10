#ifndef _GRAPHNODE_H_
#define _GRAPHNODE_H_
#include <ext/slist>
#include "GraphEdge.h"
using namespace __gnu_cxx;
class GraphNode
{
	private:
		int id;		//id of the end node of the edge
		int numHeadQueue; //number of the head queues
		int numTailQueue; //number of the tail queues
		slist<GraphEdge>* headEdge;  //Node点为sink点
		slist<GraphEdge>* tailEdge;  //Node点为source点
	public:
		//constructors
		GraphNode():id(-1), numHeadQueue(0), numTailQueue(0) 
		{
			this->headEdge = new slist<GraphEdge>(0);
			this->tailEdge = new slist<GraphEdge>(0);
		}
		explicit GraphNode(const GraphNode& Node);
		GraphNode(GraphNode& Node);
		GraphNode(int _id);
		bool operator == (const GraphNode& node);
		bool addBulkEdge(GraphEdge* edge);
		bool removeBulkEdge(GraphEdge* edge);
		int getNumHeadQueue() const;
		int getNumTailQueue() const;
		int getNodeId() const;
		GraphEdge* getBulkEdge(GraphEdge* edge) const;
		slist<GraphEdge>* getHeadEdge() const;
		slist<GraphEdge>* getTailEdge() const;
		GraphNode& setId(int id);
		GraphNode& operator = (const GraphNode &node);
		int Print();
		//destructor
		virtual ~GraphNode()
		{
			this->headEdge->~slist();
			this->tailEdge->~slist();
			this->headEdge = NULL;
			this->tailEdge = NULL;
		}
};
#endif
