#ifndef	_CONFIG_H_
#define	_CONFIG_H_
#define MAXSESSION 1
#include <vector>
#include "bulkPool.h"

#define MAXMATRIX 3000

extern std::vector<double> sToDemand;

extern bulkPool pool;

const int M = 4;

const double MAX = 100000; 

const double MAXCAPACITY = 100000; //可以存储的容量

#endif
