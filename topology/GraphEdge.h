#ifndef _GRAPHEDGE_H_
#define _GRAPHEDGE_H_
class GraphEdge
{
	protected:
		int _v1;		   //node id of the origin
		int _v2;		   //node id of the end
		double _weight;	   //(数学期望)
		double _capacity;  //链路带宽
	public:
		GraphEdge():_v1(-1), _v2(-1), _weight(0.0), _capacity(0.0){}
		GraphEdge(int v1, int v2, double weight = 0.0, double capacity = 0.0);
		GraphEdge(const GraphEdge& edge);
		GraphEdge(GraphEdge& edge);
		bool operator == (const GraphEdge& edge);
		GraphEdge& setWeight(double weight);
		GraphEdge& setCapacity(double capacity);
		int getGraphEdgeSource() const;
		int getGraphEdgeSink() const;
		double getWeight() const;
		double getCapacity() const;
		virtual ~GraphEdge(){}
};

#endif
