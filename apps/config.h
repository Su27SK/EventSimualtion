#ifndef	_CONFIG_H_
#define	_CONFIG_H_
#define MAXSESSION 2
#include <vector>
#include "bulkPool.h"
#include "db.h"

#define MAXMATRIX 20000
#define MAXROUTE 30

extern std::vector<double> sToDemand;

extern bulkPool pool;

extern db db_;

const int M = 4;

extern int simTime_;

extern int interval_;

extern vector<string> log_packet[MAXSESSION];
extern vector<string> log_nodeInfo[MAXROUTE];
#endif
