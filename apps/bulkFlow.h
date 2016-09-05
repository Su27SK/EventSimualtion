#ifndef _BULKFLOW_H_
#define _BULKFLOW_H_
#include "GraphEdge.h"
#include "bulkException.h"
class bulkFlow: public GraphEdge
{
	private:
		double _flow;
	public:
		bulkFlow(double flow):GraphEdge() {
			_flow = flow;
		}
		bulkFlow():GraphEdge() {
			_flow = 0.0;
		}
		bulkFlow(double flow, GraphEdge& edge):GraphEdge(edge) {
			_flow = flow;
		}
		double getFlow() const;
		int other(int vertex);
		//v中残留流量
		double residualCapacityTo(int vertex);
		void addResidualFlowTo(int vertex, double delta);
};
#endif
