#include "fordFulkersion.h"
vector<bool> fordFulkersion:: _marked;
vector<int> fordFulkersion::_parent;
double fordFulkersion::rGraph[MAXMATRIX][MAXMATRIX];
double fordFulkersion::_value;
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
	vector<bool>::iterator iter = _marked.begin();
	for (; iter != _marked.end(); iter++) {
		*iter = 0;
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (size_t w = 0; w < _marked.size(); w++) {
			if (rGraph[v][w] > 0 && !_marked[w]) {
				_parent[w] = v;
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
 * @param {interge} n
 */
void fordFulkersion::FordFulkersion(bulkOverlay G, int s, int t, int n)
{
	if (n <= 0) {
		return;
	}
	_parent.clear();
	setRGraph(G, n);
	_marked.resize(n + 1);
	_parent.resize(n + 1);
	_value = 0.0;
	while (_hasAugmentingPath(G, s, t)) {
		double bottle = INT_MAX;
		for (int v = t; v != s; v = _parent[v]) {
			int w = _parent[v];
			bottle = min(bottle, rGraph[w][v]);
		}
		for (int v = t; v != s; v = _parent[v]) {
			int w = _parent[v];
			rGraph[w][v] -= bottle;
			rGraph[v][w] += bottle;
		}
		_value += bottle;
	}
	cout<<"value:"<<_value<<endl;
}

/**
 * @brief getEdgeTo 
 *
 * @return {vector<bulkFlow>}
 */
//vector<bulkFlow> fordFulkersion::getEdgeTo()
//{
	//return _edgeTo;
//}

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

/**
 * @brief setRGraph 
 *
 * @param {bulkOverlay} G
 * @param {interge} n
 */
void fordFulkersion::setRGraph(bulkOverlay G, int n)
{
	for (int i = 0; i < MAXMATRIX; i++) {
		for (int j = 0; j < MAXMATRIX; j++) {
			rGraph[i][j] = 0;
		}
	}
	for (int v = 0; v < n; v++) {
		slist<bulkFlow> pFlow = G.getVirtualAdj(v);
		slist<bulkFlow>::iterator iter = pFlow.begin();
		for (; iter != pFlow.end(); iter++) {
			int fromId = iter->getGraphEdgeSource();
			int toId = iter->getGraphEdgeSink();
			rGraph[fromId][toId] = iter->getCapacity();
		}
	}
}
