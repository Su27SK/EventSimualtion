#include "fordFulkersion.h"
vector<bool> fordFulkersion:: _marked;
vector<int> fordFulkersion::_parent;
vector<vector<double> > fordFulkersion::_flow;
double fordFulkersion::rGraph[MAXMATRIX][MAXMATRIX];
double fordFulkersion::sGraph[MAXMATRIX][MAXMATRIX];
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
	vector<bool>::iterator iter = _marked.begin();
	for (; iter != _marked.end(); iter++) {
		*iter = 0;
	}
	queue<int> q;
	q.push(s);
	_marked[s] = true;
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

void fordFulkersion::_init(int n)
{
	_parent.resize(n);
	for (size_t i = 0; i < _parent.size(); i++) {
		_parent[i] = -1;
	}
	_flow.resize(n);
	for (size_t i = 0; i < _flow.size(); i++) {
		_flow[i].resize(n);
		for (size_t j = 0; j < _flow[i].size(); j++) {
			_flow[i][j] = 0;
		}
	}
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
	_init(n);
	setRGraph(G, n);
	_marked.resize(n + 1);
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
			_flow[w][v] += bottle;
			_flow[v][w] = -_flow[w][v];
		}
		_value += bottle;
		cout<<"value:"<<_value<<endl;
	}
	//for (size_t i = 0; i < _flow.size(); i++) {
		//for (size_t j = 0; j < _flow[i].size(); j++) {
			//if (_flow[i][j] != 0) {
				//cout<<"i:"<<i<<"=>j:"<<j<<" flow:"<<_flow[i][j]<<endl;
			//}
		//}
	//}
}

/**
 * @brief getEdgeTo 
 *
 * @return {vector<bulkFlow>}
 */
vector<bulkFlow> fordFulkersion::getEdgeTo()
{
	vector<bulkFlow> route;
	return route;
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
			sGraph[i][j] = 0;
		}
	}
	//int graph[9][9] = { 
		//{ 0, 140, 0, 0, 0, 0, 0, 0, 0}, 
		//{ 0, 0, 20, 40, 30, 2000, 0, 0, 0},
		//{ 0, 0, 0, 40, 30, 0, 2000, 0, 0},
		//{ 0, 0, 31, 0, 1, 0, 0, 2000, 0},
		//{ 0, 0, 0, 0, 0, 0, 0, 0, 2000},5
		//{ 0, 0, 0, 0, 0, 0, 20, 40, 30 },
		//{ 0, 0, 0, 0, 0, 0, 0, 40, 30 },
		//{ 0, 0, 0, 0, 0, 0, 31, 0, 1 },
		//{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//};

	//for (int i = 0; i < 9; i++) {
		//for (int j = 0; j < 9; j++) {
			//rGraph[i][j] = graph[i][j];
		//}
	//}

	for (int v = 0; v < n; v++) {
		slist<bulkFlow> pFlow = G.getVirtualAdj(v);
		slist<bulkFlow>::iterator iter = pFlow.begin();
		for (; iter != pFlow.end(); iter++) {
			int fromId = iter->getGraphEdgeSource();
			int toId = iter->getGraphEdgeSink();
			//cout<<"fromId:"<<fromId<<" toId:"<<toId<<endl;
			//cout<<"capacity:"<<iter->getCapacity()<<endl;
			rGraph[fromId][toId] = iter->getCapacity();
			sGraph[fromId][toId] = iter->getCapacity();
			//rGraph[fromId][toId] = iter->getPredictiveCapacity();
		}
	}
}

/**
 * @brief getRdgeRateBySecond 
 * 获得路径上的速率/秒
 * @param {int} s
 * @param {int} e
 *
 * @return {double}
 */
double fordFulkersion::getEdgeRateBySecond(int s, int e)
{
	return sGraph[s][e] / 60;
}
