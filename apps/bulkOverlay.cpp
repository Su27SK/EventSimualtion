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
	size_t tSize = _adj.size();
	for (size_t i = 0; i < tSize; i++) {
		bulkOverlayAgent* pOverlayAgent = new bulkOverlayAgent(i);
		pOverlayAgent->setResidualStorage(INT_MAX);
		_agents.push_back(pOverlayAgent);
	}
}

/**
 * @brief _initVirtual 
 * 初始化为virtualNode
 * @param {interge} time (单位: /s)
 */
void bulkOverlay::initVirtual(int time)
{
	size_t tSize = _adj.size();
	if (time <= 0 || tSize == 0) {
		return ;
	}
	clearVirtualAdj();
	size_t n = time * (tSize - 1);
	int i = 1, j = 0;
	_vAdj.resize(n + 1);
	while (j < time) {
		while (i < tSize) {
			slist<bulkFlow*>::iterator iter = _adj[i]->begin();
			for (; iter != _adj[i]->end(); iter++) {
				bulkFlow e = **iter;
				int sourceId = e.getGraphEdgeSource() + j * (tSize - 1);
				int sinkId = e.getGraphEdgeSink() + j * (tSize - 1);
				e.setSourceId(sourceId).setSinkId(sinkId);
				addEdge(e);
			}
			i++;
		}
		j++;
		i = 1;
	}
	for (size_t i  = 1; i <= n - tSize + 1; i++) {
		int nextId = i + (tSize - 1);
		int index = nextId % (tSize - 1);
		index = index != 0 ? index: index + 27;
		double residualStorage = _agents[index]->getResidualStorage();
		GraphEdge edge(i, nextId, residualStorage, residualStorage);
		bulkFlow virtualLink(0.0, edge);
		addEdge(virtualLink);
	}
}

/**
 * @brief transmission 
 *
 * @param {interge} time (单位: /s)
 */
void bulkOverlay::transmission(int time)
{
	if (time <= 0) {
		return ;
	}
	int tSize = _adj.size();
	for (size_t i = 0; i < fordFulkersion::_flow.size() ; i++) {
		for (size_t j = 0; j < fordFulkersion::_flow[i].size(); j++) {
			double flow = fordFulkersion::_flow[i][j];
			if ((i / tSize) <= (time - 1) && (j / tSize) <= (time - 1) && flow > 0) {
				int fromId = i; 
				int toId = j;
				//cout<<"fromId:"<<fromId<<endl;
				//cout<<"toId:"<<toId<<endl;
				fromId = fromId >= tSize ? fromId % (tSize - 1) : fromId;
				toId = toId >= tSize ? toId % (tSize - 1) : toId;
				if (toId == 0) {
					toId = toId + (tSize - 1);
				}
				//double limitLink = _agents[fromId]->get
				_agents[fromId]->setUplink(flow).send();
				_agents[toId]->setDownlink(flow).recv();
			}
		}
	}
	for (int i = 0; i < 27; i++) {
		cout<<"storage:"<<_agents[i]->getStorage()<<endl;
	}
}

/**
 * @brief initVirtualSource 
 *
 * @param {interge} F
 * @param {intergParentv
 *
 * @return {interge} 虚拟超级节点索引值
 */
int bulkOverlay::initVirtualSource(int F, int v)
{
	size_t tSize = _adj.size();
	for (int k = 1; k < tSize; k++) {
		double storage = _agents[k]->getStorage();
		if (k != v && storage != 0) { //S链接w(1)
			GraphEdge edge(0, k, storage, storage);
			bulkFlow vLinkFromS(0.0, edge);
			addEdge(vLinkFromS);
		} else if (k == v) { //S链接v
			GraphEdge edge(0, k, F, F);
			bulkFlow vLinkFromS(0.0, edge);
			addEdge(vLinkFromS);
		}
	}
	return 0;
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
 * @return {double}
 */
double bulkOverlay::scheduling(int v, int u, int F)
{
	return initNetBottlenecksWithT(v, u, F);
}

/**
 * @brief updating 
 * 获得预测信息之后，更新每条边数据
 * @param {interge} interval
 * @param {string} path
 * @return {boolean}
 */
bool bulkOverlay::updating(int interval, string path)
{
	slist<bulkFlow*>::iterator iter;
	FILE* handle;
	//string dir = "../Bulk_Config_File/link/";
	string dir = path;
	for (size_t i = 1; i < _adj.size(); i++) {
		for (iter = _adj[i]->begin(); iter != _adj[i]->end(); iter++) {
			int sourceId = (*iter)->getGraphEdgeSource();
			int sinkId = (*iter)->getGraphEdgeSink();
			stringstream fromId, toId;
			fromId << sourceId;
			toId << sinkId;
			string filename = string(fromId.str()) + string("_To_")+string(toId.str()) + string("_link.txt");
			string fullPath = dir + filename;
			handle = fopen(fullPath.c_str(), "r");
			char buf[10];
			int count = 1;
			while (!feof(handle) && count <= interval) {
				fgets(buf, 1024, handle);
				count++;
			}
			double capacity = atoi(buf);
			(*iter)->setCapacity(capacity);
		}
	}
	return true;
}

/**
 * @brief initNetBottlenecksWithT
 * 将拓扑按时间T扩充
 * @param {interge} v
 * @param {interge} u
 * @param {interge} F 
 * @return {double} min(Max(T))
 */
double bulkOverlay::initNetBottlenecksWithT(int v, int u, int F)
{
	//二分查找法寻找寻找min(T_max) for the volume F
	int lowIndex = 1, highIndex = 59, mid = 0;
	double value = 0.0;
	int count = INT_MAX;
	while (lowIndex <= highIndex) {
		mid = lowIndex + ((highIndex - lowIndex) / 2);
		cout<<"mid:"<<mid<<endl;
		initVirtual(mid);
		int s = initVirtualSource(F, v);
		int t = u + (mid - 1) * (_adj.size() - 1);
		fordFulkersion::FordFulkersion(*this, s, t, getVirtualVertices());
		value = fordFulkersion::getValue();
		if (value  >= F) {
			highIndex = mid - 1;
			if (mid < count) {
				count = mid;
			}
		} else if (value < F) {
			lowIndex = mid + 1;
		}
	}
	if (mid < count && F == value) {
		count = mid;
	}
	initVirtual(count);
	int s = initVirtualSource(F, v);
	int t = u + (count - 1) * (_adj.size() - 1);
	fordFulkersion::FordFulkersion(*this, s, t, getVirtualVertices());
	
	cout<<"count:"<<count<<endl;
	return count;
}

/**
 * @brief getVirtualVertices 
 * (include the S* virtual Node)
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
