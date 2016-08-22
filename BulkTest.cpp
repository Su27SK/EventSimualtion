#include <iostream>
#include <stdlib.h>
#include "File.h"
#include "bulkBackPressure.h"
using namespace std;
int main(int argc, char* argv[])
{
	Graph* graph = Graph::importGraph("../Bulk_Config_File/graph.txt");
	bulkBackPressure* backPressure = new bulkBackPressure(graph);
	cout<<"Hello World"<<endl;
	return 0;
}
