#include "bulkOverlay.h"
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief init 
 */
void bulkOverlay::_init()
{
	size_t tSize = _adj[0].size();
	for (size_t i = 0; i < tSize; i++) {
		bulkOverlayAgent* pOverlayAgent = new bulkOverlayAgent(i);
		pOverlayAgent->setResidualStorage(INT_MAX);
		_agents.push_back(pOverlayAgent);
	}
}

/**
 * @brief _initVirtualNode 
 * 初始化为virtualNode
 * @param {interge} time (单位: /minute)
 */
void bulkOverlay::initVirtualNode(int baseTime, int time)
{
	size_t tSize = _adj[0].size();
	if (time <= 0 || tSize == 0) {
		return ;
	}
	clearVirtualAdj();
	size_t n = time * (tSize - 1);
	int i = 1, j = 0;
	_vAdj.resize(n + 1);
	while (j < time - 1) {
		while (i < tSize) {
			int index = baseTime + j + 1;
			//int index = j + 1;
			slist<bulkFlow*>::iterator iter = _adj[index][i]->begin();
			for (; iter != _adj[index][i]->end(); iter++) {
				bulkFlow e = **iter;
				int sourceId = e.getGraphEdgeSource() + j * (tSize - 1);
				int sinkId = e.getGraphEdgeSink() + (j + 1) * (tSize - 1);
				//cout<<"time:"<<j + 1<<" source:"<<sourceId<<" sink:"<<sinkId<<" capacity:"<<e.getCapacity()<<endl;
				cout<<"sourceId:"<<sourceId<<" sinkId:"<<sinkId<<endl;
				e.setSourceId(sourceId).setSinkId(sinkId);
				addEdge(e);
			}
			i++;
		}
		j++;
		i = 1;
	}
	//for (size_t i  = 1; i <= n - tSize + 1; i++) {
		//int nextId = i + (tSize - 1);
		//int index = nextId % (tSize - 1);
		//index = index != 0 ? index: index + 27;
		//double residualStorage = _agents[index]->getResidualStorage();
		//GraphEdge edge(i, nextId, residualStorage, residualStorage);
		//bulkFlow virtualLink(0.0, edge);
		//addEdge(virtualLink);
	//}
}

/**
 * @brief transmission 
 *
 * @param {interge} time (单位: /minute)
 */
void bulkOverlay::transmission(int baseTime, int v, int u, int time)
{
	if (time <= 0) {
		return ;
	}
	int tSize = _adj[0].size();
	vector<vector<bulkFlow> > vec;
	vec.resize(time);
	double recv[30] = {0};
	int count = 1;
	int preTime = 0;
	FILE* handle = fopen("transfer.txt", "w+");
	for (size_t i = 1; i < fordFulkersion::_flow.size(); i++) {
		for (size_t j = 0; j < fordFulkersion::_flow[i].size(); j++) {
			double flow = fordFulkersion::_flow[i][j];
			if (flow > 0) {
				int fromId = i; 
				int toId = j;
				if (fromId % (tSize - 1) == 0) {
					preTime = fromId / (tSize - 1);
				} else {
					preTime = fromId / (tSize - 1) + 1;
				}
				if (fromId > count * (tSize - 1)) {
					for (int k = 1; k < tSize; k++) {
						_agents[k]->recv(recv[k]);
					}
					setLog(count);
					count++;
					memset(recv, 0, sizeof(recv));
				}
				int indexFrom = fromId % (tSize - 1);
				int indexTo = toId % (tSize - 1);
				fromId = indexFrom != 0 ? indexFrom : 27;  
				toId = indexTo != 0 ? indexTo : 27;
				double trueFlow = _agents[fromId]->send(flow);
				fprintf(handle, "time:%d, fromId:%d, toId:%d, flow:%f, trueFlow:%f\n", preTime, fromId, toId, flow, trueFlow);
				//cout<<"time:"<< preTime << " fromId:"<<fromId<<" toId:"<<toId<<" flow:"<<flow<<" trueFlow:"<<trueFlow<<endl;
				recv[toId] += trueFlow;
			}
		}
	}
	for (int k = 1; k < tSize; k++) {
		_agents[k]->recv(recv[k]);
	}
	setLog(count);
	//for (size_t i = 0; i < vec.size(); i++) {
		//pushTrafficByMinute(vec[i]);
	//}
	double total = getAllStorage(v, u);
	fclose(handle);
	cout<<"total:"<<total<<endl;
}

/**
 * @brief pushTrafficByMinute 
 * 每分钟推送traffic
 * @param {vector<bulkFlow>} flows
 *
 * @return {boolean}
 */
bool bulkOverlay::pushTrafficByMinute(vector<bulkFlow> flows)
{
	for (int i = 1; i <= 60; i++) {
		int recv[30] = {0};
		vector<bulkFlow>::iterator iter = flows.begin();
		for (; iter != flows.end(); iter++) {
			int fromId = iter->getGraphEdgeSource();
			int toId = iter->getGraphEdgeSink();
			double require = 0.0;
			int trueFlow = _agents[fromId]->send(iter->getFlow() / 60);
			//cout<<"fromId:"<<fromId<<" toId:"<<toId<<" trueFlow:"<<trueFlow<<endl;
			recv[toId] += trueFlow;
		}
		for (int j = 1; j <= 27; j++) {
			_agents[j]->recv(recv[j]);
		}
	}
	return true;
}

/**
 * @brief initVirtualSource 
 *
 * @param {interge} F
 * @param {interge} v
 * @param {interge} u
 *
 * @return {interge} 需要发送的总数据
 */
int bulkOverlay::initVirtualSource(int F, int v, int u)
{
	size_t tSize = _adj[0].size();
	for (int k = 1; k < tSize; k++) {
		if (k != u) {
			double storage = _agents[k]->getStorage();
			if (storage != 0) { //S链接w(1), v(1)
				GraphEdge edge(0, k, storage, storage);
				bulkFlow vLinkFromS(0.0, edge);
				addEdge(vLinkFromS);
			}
		}
	}
	return 0;
}

/**
 * @brief setLog 
 *
 * @param {interge} time
 */
void bulkOverlay::setLog(int time)
{
	size_t tSize = _adj[0].size();
	FILE* handle = fopen("StorageInfo.txt", "a+");  
	for (int id = 0; id < tSize; id++) {
		int storage = _agents[id]->getStorage();
		fprintf(handle, "time:%d, NodeId:%d, StoreNum:%d\n", time, id, storage);
	}
	fclose(handle);
}

/**
 * @brief clearVirtualAdj 
 */
void bulkOverlay::clearVirtualAdj()
{
	vector<slist<bulkFlow> >::iterator iter = _vAdj.begin();
	for (; iter != _vAdj.end(); iter++) {
		iter->clear();
	}
}

/**
 * @brief addEdge 
 * 为adj增加virtual node
 * @param {bulkFlow} e
 */
void bulkOverlay::addEdge(bulkFlow e)
{
	int v = e.getGraphEdgeSource();
	int w = e.getGraphEdgeSink();
	_vAdj[v].push_front(e);
}

/**
 * @brief scheduling 
 *
 * @param {interge} v
 * @param {interge} u
 * @param {interge} F
 *
 * @return {double}
 */
double bulkOverlay::scheduling(int baseTime, int v, int u, int F)
{
	_agents[v]->setStorage(F + _agents[v]->getStorage());
	return initNetBottlenecksWithT(baseTime, v, u, F);
}

/**
 * @brief setAllStorage 
 *
 * @param {interge} v
 * @param {interge} u
 *
 * @return 
 */
void bulkOverlay::setAllStorage(int v, int u)
{
	for (int i = 1; i <= 27; i++) {
		if (i != v && i != u) {
			_agents[i]->setStorage(100000);
		}
	}
}

/**
 * @brief updating 
 * 获得预测信息之后，更新每条边数据
 * @param {interge} interval
 * @param {string}  path
 * @param {interge} flag  {0: forecase; 1: true limit}
 *
 * @return {boolean}
 */
bool bulkOverlay::updating(int interval, string path, int flag)
{
	slist<bulkFlow*>::iterator iter;
	FILE* handle = NULL;
	string dir = path;
	try {
		for (size_t i = 1; i < _adj[interval].size(); i++) {
			for (iter = _adj[interval][i]->begin(); iter != _adj[interval][i]->end(); iter++) {
				int sourceId = (*iter)->getGraphEdgeSource();
				int sinkId = (*iter)->getGraphEdgeSink();
				stringstream fromId, toId;
				fromId << sourceId;
				toId << sinkId;
				string filename = string(fromId.str()) + string("_To_") + string(toId.str()) + string("_link.txt");
				string fullPath = dir + filename;
				handle = fopen(fullPath.c_str(), "r");
				char buf[10];
				int count = 1;
				while (!feof(handle) && count <= interval) {
					fgets(buf, 1024, handle);
					count++;
				}
				double capacity = atoi(buf);
				if (flag) {
					(*iter)->setCapacity(capacity);
				} else {
					(*iter)->setPredictiveCapacity(capacity);
				}
				fclose(handle);
			}
		}
	} catch(exception e) {
		cout<<"updating error"<<endl;
	}
	return true;
}

/**
 * @brief initNetBottlenecksWithT
 * 将拓扑按时间T扩充
 * @param {interge} v
 * @param {interge} u
 * @param {interge} F 
 *
 * @return {double} min(Max(T))
 */
double bulkOverlay::initNetBottlenecksWithT(int baseTime, int v, int u, int F)
{
	//二分查找法寻找寻找min(T_max) for the volume F
	F = 0;
	for (size_t i = 0; i < _agents.size(); i++) {
		if (i != u) {
			F += _agents[i]->getStorage(); 
		}
	}
	cout<<"F:"<<F<<endl;
	double value = 0.0;
	int ans = 3;
	if (ans <= 720) {
		cout<<"ans:"<<ans<<endl;
	}
	initVirtualNode(baseTime, ans);
	//initVirtualSource(F, v, u);
	//int t = u + (ans - 1) * (_adj[0].size() - 1);
	////cout<<"t:"<<t<<endl;
	//fordFulkersion::FordFulkersion(*this, 0, t, getVirtualVertices());
	//cout<<"value:"<<fordFulkersion::getValue()<<endl;
	return ans;
}

/**
 * @brief getVirtualVertices 
 * (include the S* virtual Node)
 *
 * @return {interge}
 */
int bulkOverlay::getVirtualVertices()
{
	return _vAdj.size();
}

/**
 * @brief getVirtualAdj
 *
 * @param {interge} v
 *
 * @return {slist<bulkFlow>} 
 */
slist<bulkFlow> bulkOverlay::getVirtualAdj(int v)
{
	return _vAdj[v];
}


/**
 * @brief getAllStorage 
 *
 * @param {interge} v
 * @param {interge} u
 *
 * @return 
 */
int bulkOverlay::getAllStorage(int v, int u) const
{
	vector<bulkOverlayAgent*>::const_iterator iter = _agents.begin();
	int index = 0;
	int total = 0;
	for (; iter != _agents.end(); iter++) {
		//cout<<"index:"<<index<<" storage:"<<(*iter)->getStorage()<<endl;
		total += (*iter)->getStorage();
		index++;
	}
	return total;
}

