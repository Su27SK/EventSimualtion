#ifndef _BULKFLOW_H_
#define _BULKFLOW_H_
#include "GraphEdge.h"
#include "bulkException.h"
#include <limits.h>
class bulkFlow: public GraphEdge
{
	private:
		double _flow;
		double _predictiveCapacity;
		double _t;
	public:
		bulkFlow(double flow):GraphEdge() {
			_flow = flow;
			_predictiveCapacity = INT_MAX;
			_t = 0.0;
		}
		bulkFlow():GraphEdge() {
			_flow = 0.0;
			_predictiveCapacity = INT_MAX;
			_t = 0.0;
		}
		bulkFlow(double flow, GraphEdge& edge):GraphEdge(edge) {
			_flow = flow;
			_predictiveCapacity = INT_MAX;
			_t = 0.0;
		}
		double getFlow() const;
		int other(int vertex);
		//v中残留流量
		double residualCapacityTo(int vertex);
		void addResidualFlowTo(int vertex, double delta);
		bulkFlow& setSourceId(int id);
		bulkFlow& setSinkId(int id);
		bulkFlow& setPredictiveCapacity(double capacity);
		double getPredictiveCapacity();
};
#endif
