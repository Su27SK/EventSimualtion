#include "fordFulkersion.h"
bool* fordFulkersion:: _marked;
bulkFlow* fordFulkersion::_edgeTo;
double fordFulkersion::_value;
/**
 * @brief _hasAugmentingPath 
 * 是否还存在增广路径
 * @param {flowNetwork} G
 * @param {interge} s
 * @param {interge} t
 *
 * @return {boolean}
 */
bool fordFulkersion::_hasAugmentingPath(flowNetwork G, int s, int t)
{
	queue<int> q;
	q.push(s);
	_marked[s] = true;
	cout<<"s:"<<s<<endl;
	cout<<"t:"<<t<<endl;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		slist<bulkFlow*>* pFlow = G.getAdj(v);
		slist<bulkFlow*>::iterator iter = pFlow->begin();
		for (; iter != pFlow->end(); iter++) {
			int w = (*iter)->other(v);
			if ((*iter)->residualCapacityTo(w) > 0 && !_marked[w]) {
				_edgeTo[w] = **iter;
				_marked[w] = true;
				q.push(w);
			}
		}
	}
	return _marked[t];
}

/**
 * @brief FordFulkersion 
 * 
 * @param {flowNetwork} G
 * @param {interge} s
 * @param {interge} t
 */
void fordFulkersion::FordFulkersion(flowNetwork G, int s, int t)
{
	int v = G.getVertices();
	//_marked.resize(v + 1);
	//_edgeTo.resize(v + 1);
	_marked = new bool[v + 1];
	_edgeTo = new bulkFlow[v + 1];
	_value = 0.0;
	while (_hasAugmentingPath(G, s, t)) {
		double bottle = MAX;
		for (int v = t; v != s; v = _edgeTo[v].other(v)) { //计算最大流量
			cout<<"residualCapacityTo:"<<_edgeTo[v].residualCapacityTo(v)<<endl;
			bottle = min(bottle, _edgeTo[v].residualCapacityTo(v));
		}
		for (int v = t; v != s; v = _edgeTo[v].other(v)) {
			_edgeTo[v].addResidualFlowTo(v, bottle);
		}
		_value += bottle;
	}
}

/**
 * @brief getEdgeTo 
 *
 * @return {bulkFlow*}
 */
bulkFlow* fordFulkersion::getEdgeTo()
{
	return _edgeTo;
}

/**
 * @brief getValue 
 *
 * @return {double}
 */
double fordFulkersion::getValue()
{
	return _value;
}

/**
 * @brief intCut 
 * s => v 在残留网络中是否可达
 * @param {interge} v
 *
 * @return 
 */
bool fordFulkersion::intCut(int v)
{
	return _marked[v];	
}
