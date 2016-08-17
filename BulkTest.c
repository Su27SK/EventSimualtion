#include <iostream>
#include <stdlib.h>
#include "File.h"
#include "bulkNetwork.h"
using namespace std;
int main(int argc, char* argv[])
{
	Graph* graph = Graph::importGraph("Bulk_Config_File/normalDis2.txt");
	bulkNetwork* network = new bulkNetwork(graph);
	return 0;
}
