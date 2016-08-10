#include "Graph.h"
Graph::Graph(int _n):n(_n)
{
	if (this->n < 0) {
		this->n = 0;
	}
	this->aList = new GraphNode[n + 1];
	this->e = 0;
}

/**
 * @brief setVertices 
 * 设置节点个数
 * @param {interge} n
 *
 * @return {Graph}
 */
Graph& Graph::setVertices(int n)
{
	this->n = n;
	if (this->aList == NULL) {
		this->aList = new GraphNode[this->n + 1];
	}
	return *this;
}

Graph::~Graph()
{
	delete [] aList;
	aList = NULL;
}

/**
 * @brief getVertices 
 * 获得节点的个数
 * @return {interge}
 */
int Graph::getVertices() const
{
	return this->n;
}


/**
 * @brief getEdges 
 * 获得边的数量
 * @return {interge}
 */
int Graph::getEdges() const
{
	return this->e;
}

/**
 * @brief capacity 
 * 获得当前链路(v1, v2)的带宽
 * @param {interge} v1
 * @param {interge} v2
 *
 * @return {double}
 */
double Graph::capacity(int v1, int v2) const
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n)
	{
		GraphEdge edge(v1, v2);
		GraphEdge* nowEdge = aList[v1].getBulkEdge(&edge);
		if (nowEdge != NULL) {
			return nowEdge->getCapacity();
		}
	}

	//if this edge doesn't exist
	return 0.0;
}

/**
 * @brief weight 
 * 返回两点之间的权值
 * @param {interge} v1
 * @param {interge} v2
 *
 * @return {boolean}
 */
double Graph::weight(int v1, int v2) const
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n)
	{
		GraphEdge edge(v1, v2);
		GraphEdge* nowEdge = aList[v1].getBulkEdge(&edge);
		if (nowEdge != NULL) {
			return nowEdge->getWeight();
		}
	}

	//if this edge doesn't exist
	return 0.0;
}

/**
 * @brief putEdge 
 * 图中增加边，以及权值，带宽
 * @param {interge} v1
 * @param {interge} v2
 * @param {double} weight
 * @param {double} capacity
 */
void Graph::putEdge(int v1, int v2, double weight, double capacity)
{	
	if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2) {
		return;
	}
	GraphNode node1(v1);
	if (aList[v1].getNodeId() == -1) {
		aList[v1] = node1;
	}
	GraphNode node2(v2);
	if (aList[v2].getNodeId() == -1) {
		aList[v2] = node2;
	}
	GraphEdge edge(v1, v2, weight, capacity);
	aList[v1].addBulkEdge(&edge);
	aList[v2].addBulkEdge(&edge);
	this->e++;
}

/**
 * @brief removeEdge 
 * 图中删除边，以及权值，带宽
 * @param {interge} v1
 * @param {interge} v2
 */
void Graph::removeEdge(int v1, int v2)
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n) {
		if (aList[v1].getNodeId() == -1 || 
			aList[v2].getNodeId() == -1) {
			return;
		} else {
			GraphEdge edge(v1, v2);
			if (aList[v1].removeBulkEdge(&edge) || 
				aList[v2].removeBulkEdge(&edge)) {
				this->e--;
			}
		}
	}
}

/**
 * @brief clearEdges 
 * 删除所有边
 */
void Graph::clearEdges()
{
	delete[] aList;
	this->e = 0;
}

/**
 * @brief connected 
 * 判断两点之间是否连通
 * @param {interge} v1
 * @param {interge} v2
 *
 * @return {boolean} 
 */
bool Graph::connected(int v1, int v2)
{
	if (v1 >= 1 && v2 >= 1 && v1 <= n && v2 <= n) {
		if (aList[v1].getNodeId() == -1 ||
			aList[v2].getNodeId() == -1) {
			return false;
		} else {
			int* visited = (int*)malloc(this->n + 1);
			if (!visited[v1]) {
				this->_dfsVisit(v1, visited, v2);
			}
			if (visited[v2]) {
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief _dfsVisit 
 * 深度优先搜索算法
 * @param {interge} uSource 
 * @param {interge[]} visited (存放已经访问过的节点id) 
 * @param {interge} vSink (存放已经访问过的节点id) 
 */
void Graph::_dfsVisit(int uSource, int* visited, int vSink)
{
	visited[uSource] = 1;
	slist<GraphEdge>* headEdge = aList[uSource].getHeadEdge();
	slist<GraphEdge>::iterator iter = headEdge->begin();
	slist<GraphEdge>::iterator iterEnd = headEdge->end();
	for (; iter != iterEnd; iter++) {
		if (visited[vSink]) {
			break;
		}
		int sink = iter->getGraphEdgeSink();
		if (!visited[sink] && sink != vSink) {
			this->_dfsVisit(sink, visited, vSink);
		} else {
			visited[sink] = 1;
			break;
		}
	}
}

/**
 * @brief importGraph 
 * 导入网路拓朴结构
 * @param {文件名} cfilename
 *
 * @return {Graph}
 */
Graph* Graph::importGraph(string cfilename)
{
	int i, nPos = 1;
	BulkFile* inFile = new BulkFile("Bulk_Config_File");
	//inFile->addFile(cfilename, "Bulk_Config_File");
	char** msgBuf = (char**)malloc(LINEMAX * sizeof(char*));
	for (i = 0; i < LINEMAX; i++) {
		msgBuf[i] = (char*)malloc(50 * sizeof(char));
	}
	inFile->getlines(msgBuf, LINEMAX, cfilename);

	Graph* g = new Graph();
	
	for (i = 0; i < nPos; i++) {
		int nTemp;
		nTemp = g->_filterInfo(msgBuf[i], g);
		if (nTemp == -1) {
			nPos ++;
		}  
	}
	return g;
}

/**
 * @brief _filterInfo 
 * 分析提取到的每一行数据
 * @param {char*} message
 * @param {Graph*} graph
 *
 * @return {size_t} 
 */
size_t Graph::_filterInfo(char* message, Graph* graph)
{
	string s(message);
	switch (s[0]) {
		case 't':
			int vertices;
			vertices = atoi(s.substr(2).c_str());
			//cout<<"vertices:"<<vertices<<endl;
			graph->setVertices(vertices);
			return -1;
		case 'T':
			int edges;
			edges = atoi(s.substr(2).c_str());
			//cout<<"edges:"<<edges<<endl;
			if (edges > 0) {
				return -1;
			} else {
				return -2;
			}
		case '?':
			{
				int index, id;
				GraphNode* list;
				string latter = s.substr(2);
				int len = latter.find(" ");
				index = atoi(latter.substr(0, len).c_str());
				id = atoi(latter.substr(len + 1).c_str());
				//cout<<"index:"<<index<<" id:"<<id<<endl;
				list = graph->getList();
				list[index].setId(id);
				return -1;
			}
		case 'L':
			{
				int source, sink;
				double weight, capacity;
				string latter = s.substr(2);
				int index = latter.find(" ");
				latter = s.substr(3 + index);

				int sourceLen = latter.find(" ");
				source = atoi(latter.substr(0, sourceLen).c_str());

				latter = s.substr(4 + index + sourceLen);
				int sinkLen = latter.find(" ");
				sink = atoi(latter.substr(0, sinkLen).c_str());

				latter = s.substr(5 + index + sourceLen + sinkLen);
				int wLen = latter.find(" ");
				weight = atoi(latter.substr(0, wLen).c_str());
				//cout<<"source:"<<source<<" sink:"<<sink<<" weight:"<<weight<<endl;
				capacity = 0;
				graph->putEdge(source, sink, weight, capacity);
				return -1;
			}
		default:break;
	}
	return -2;
}

GraphNode* Graph::getList()
{
	return aList;
}


