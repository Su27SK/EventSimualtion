#ifndef _GRAPHNODE_H_
#define _GRAPHNODE_H_
#include <algorithm>
#include <ext/slist>
#include "GraphEdge.h"
using namespace __gnu_cxx;
using namespace std;
class GraphNode
{
	private:
		int _id;		//id of the end node of the edge
		int _numEdge;   
		slist<GraphEdge>* _edge;  //node点为sink点
	public:
		//constructors
		GraphNode():_id(-1), _numEdge(0)
		{
			_edge = new slist<GraphEdge>(0);
		}
		explicit GraphNode(const GraphNode& node);
		GraphNode(GraphNode& node);
		GraphNode(int id);
		bool operator == (const GraphNode& node);
		bool addEdge(GraphEdge* edge);
		bool removeEdge(GraphEdge* edge);
		int getNumEdge() const;
		int getNodeId() const;
		GraphEdge* getEdge(GraphEdge* edge) const;
		slist<GraphEdge>* getEdge() const;
		GraphNode& setId(int id);
		GraphNode& operator = (const GraphNode &node);
		//destructor
		virtual ~GraphNode()
		{
			_edge->~slist();
			_edge = NULL;
		}
};
#endif
