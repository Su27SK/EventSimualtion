#ifndef	_CONFIG_H_
#define	_CONFIG_H_
#define MAXSESSION 5
#include <vector>
#include "bulkPool.h"

extern std::vector<double> sToDemand;

static bulkPool pool;

const int M = 4;

#endif
