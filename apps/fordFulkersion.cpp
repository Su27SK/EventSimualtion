#include "fordFulkersion.h"
/**
 * @brief _hasAugmentingPath 
 * 是否还存在增广路径
 * @param {bulkOverlay} G
 * @param {interge} s
 * @param {interge} t
 *
 * @return {boolean}
 */
bool fordFulkersion::_hasAugmentingPath(bulkOverlay G, int s, int t)
{
	queue<int> q;
	q.push(s);
	_marked[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		slist<bulkFlow*>* pFlow = G.getAdj(v);
		slist<bulkFlow*>::iterator iter = pFlow->begin();
		for (; iter != pFlow->end(); iter++) {
			int w = (*iter)->other(v);
			if ((*iter)->residualCapacityTo(w) > 0 && _marked[w]) {
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
 * @param {bulkOverlay} G
 * @param {interge} s
 * @param {interge} t
 */
void fordFulkersion::FordFulkersion(bulkOverlay G, int s, int t)
{
	_value = 0.0;
	while (_hasAugmentingPath(G, s, t)) {
		double bottle = MAX;
		for (int v = t; v != s; v = _edgeTo[v].other(v)) { //计算最大流量
			bottle = min(bottle, _edgeTo[v].residualCapacityTo(v));
		}
		for (int v = t; v != s; v = _edgeTo[v].other(v)) {
			_edgeTo[v].addResidualFlowTo(v, bottle);
		}
		_value += bottle;
	}
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
