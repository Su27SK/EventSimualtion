#ifndef __DB__
#define __DB__
#include "/usr/include/mysql/mysql.h"
#include<iostream>
#include<string>
using namespace std;
class db
{
	public:
		db();
		~db();
		bool initDB(string host, string user, string pwd, string db_name);
		bool exeSQL(string sql);
	private:
		MYSQL* connection;
		MYSQL_RES *result;
		MYSQL_ROW row;
};
#endif
