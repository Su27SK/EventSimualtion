#ifndef _BULKEXCEPTION_H_
#define _BULKEXCEPTION_H_
#include "baseException.h"
class bulkException: public baseException
{
	public:
		bulkException(string msg) throw(): baseException(msg){};
		~bulkException() throw() {}
		string getClassName() const
		{
			return "bulkException";
		}
};
#endif
