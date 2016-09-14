#include <iostream>
#include <stdlib.h>
#include "File.h"
#include "bulkBackPressure.h"
#include "flowNetwork.h"
#include "fordFulkersion.h"
#include "overlaySimulation.h"
using namespace std;
int main(int argc, char* argv[])
{
	//Graph* graph = Graph::importGraph("../Bulk_Config_File/graph.txt");
	Graph* graph = Graph::importGraph("../Bulk_Config_File/world.txt");
	//flowNetwork* pNetwork = new flowNetwork(graph);
	//fordFulkersion::FordFulkersion(*pNetwork, 1, 8);
	//cout<<"value:"<<fordFulkersion::getValue()<<endl;
	//bulkBackPressure* backPressure = new bulkBackPressure(graph);
	//backPressure->setSession(1, 1, 4, 4);
	//backPressure->setSession(2, 1, 4, 5);
	//backPressure->handle();
	bulkOverlay* overlay = new bulkOverlay(graph);
	//overlay->updating(2);
	overlaySimulation* pSimulation = new overlaySimulation(1, 16, overlay, 60);
	pSimulation->updatingPrediction(1);
	pSimulation->scheduling();
	pSimulation->transmission(40);
	//overlay->initVirtual(1);
	//overlay->scheduling(1, 13, 10);
	//overlay->getVirtualAdj(1);
	//cout<<overlay->getVertices()<<endl;
	//overlaySimulation* pSimulation = new overlaySimulation(overlay);
	//slist<bulkFlow*>* pFlow = pNetwork->getAdj(1);
	//slist<bulkFlow*>::iterator iter = pFlow->begin();
	//for (; iter != pFlow->end(); iter++) {
		//cout<<(*iter)->getCapacity()<<endl;
	//}
	//pSimulation->start();
	//pSimulation->run();

	cout<<"Hello World"<<endl;
	return 0;
}
