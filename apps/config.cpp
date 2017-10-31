#include "config.h"
std::vector<double> sToDemand(MAXSESSION + 1);

bulkPool pool;

int simTime_;

int interval_ = 1;

db db_;

vector<string> log_packet[MAXSESSION];
vector<string> log_nodeInfo[MAXROUTE];
