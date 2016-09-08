#include <iostream>
#include <stdlib.h>
#include "File.h"
#include "bulkBackPressure.h"
#include "flowNetwork.h"
#include "fordFulkersion.h"
using namespace std;
int main(int argc, char* argv[])
{
	//Graph* graph = Graph::importGraph("../Bulk_Config_File/graph.txt");
	Graph* graph = Graph::importGraph("../Bulk_Config_File/world.txt");
	flowNetwork* pNetwork = new flowNetwork(graph);
	fordFulkersion::FordFulkersion(*pNetwork, 1, 8);
	cout<<fordFulkersion::getValue()<<endl;
	//bulkBackPressure* backPressure = new bulkBackPressure(graph);
	//backPressure->setSession(1, 1, 4, 4);
	//backPressure->setSession(2, 1, 4, 5);
	//backPressure->handle();
	slist<bulkFlow*>* pFlow = pNetwork->getAdj(1);
	slist<bulkFlow*>::iterator iter = pFlow->begin();
	for (; iter != pFlow->end(); iter++) {
		cout<<(*iter)->getCapacity()<<endl;
	}
	cout<<"Hello World"<<endl;
	return 0;
}
