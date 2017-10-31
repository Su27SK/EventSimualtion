#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "File.h"
#include "bulkBackPressure.h"
#include "flowNetwork.h"
#include "fordFulkersion.h"
#include "overlaySimulation.h"
#include"db.h"
using namespace std;
void f(string s)
{
	try {
		throw bulkException(s);
	} catch(bulkException e) {
		cout<<e.getStackTrace()<<endl;
	}
};

int main(int argc, char* argv[])
{
	if (argc != 5) {
		cout<<"Simulation #time #interval #topology #session_file"<<endl;
		return 0;
	}
	int time = atoi(argv[1]);
	int interval = atoi(argv[2]);
	char* topology = argv[3];

	bulkBackPressure* handle = new bulkBackPressure();
	handle->setGraph(Graph::importGraph(topology));
	handle->init();

	char* session_file_path = argv[4]; 
	FILE* fp = fopen(session_file_path, "r");
	char buf[4];
	fgets(buf, 4, fp);
	int n = atoi(buf);
	
	for (int i = 0; i < n; i++) {
		char line[20];
		fgets(line, 20, fp);
		int sessionId = atoi(line);
		fgets(line, 20, fp);
		int p = 0;
		string s;
		while (line[p] != '\0') {
			s.push_back(line[p++]);
		}
		int sourceId = atoi((s.substr(0, s.find(','))).c_str());
		s = s.substr(s.find(',') + 1);
		int sinkId = atoi((s.substr(0, s.find(','))).c_str());
		int flow = atoi(s.substr(s.find(',') + 1).c_str());
		handle->setSession(sessionId, sourceId, sinkId, flow).setIntervalVary(interval);
	}

	handle->initVirtualAgents();
	handle->initAgents();
	for (int t = 0; t < time; t++) { 
		simTime_ = t;
		cout<<"t:"<<t<<endl;
		handle->handle();
		if (!(t % 1000)) {
			handle->writeLog();
		}
	}

	//db db_;
	//db_.initDB("localhost", "root", "", "simulation");
	//db_.exeSQL(" insert into packet(session_id, start_time, end_time, hop_num, source_id, sink_id) values(1, 1, 2, 1, 1, 4);");
	//db_.exeSQL(" select * from packet");
	return 0;
}
