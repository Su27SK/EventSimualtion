#include<iostream>
#include<string>
#include"db.h"
using namespace std;
int main()
{ 
	db db_;
	db_.initDB("localhost", "root", "", "simulation");
	db_.exeSQL(" insert into packet(session_id, start_time, end_time, hop_num, source_id, sink_id) values(1, 1, 2, 1, 1, 4);");
	db_.exeSQL(" select * from packet");
	return 0;
}
