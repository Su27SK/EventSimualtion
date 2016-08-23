#ifndef	CONFIG_H_
#define	CONFIG_H_
#define MAXSESSION 20
#include <vector>
#include "bulkPool.h"

static std::vector<double> sToDemand(MAXSESSION + 1);

static bulkPool pool;

const int M = 4;

#endif
