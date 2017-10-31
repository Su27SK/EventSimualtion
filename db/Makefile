test:db.o
	g++ -g db.o -o test -g test.cpp -lmysqlclient
db.o:db.h db.cpp
	g++ -Wall -c -g db.cpp -lmysqlclient 
