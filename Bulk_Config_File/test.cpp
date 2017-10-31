#include<iostream>
#include<sstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
using namespace std;
string int_to_String(int n)
{
	ostringstream stream;
	stream<<n;
	return stream.str();
}

int main()
{
	char buff[1024];
	int from = 1;
	int to = 2;
	string file_path = string("file/") + int_to_String(from) + string("_") + int_to_String(to) + string(".txt");
	FILE* handle = fopen(file_path.c_str(), "r");
	int count = ceil(float(from) / float(to));
	int i = 0;
	char* file_path_getcwd = (char*) malloc(80);
	getcwd(file_path_getcwd, 80);
	char file_name;
	strcat(str, "../");
	string file_name = string("../") + file_path_getcwd.str(); 
	printf("%s", file_name);
	//while (!feof(handle) && i < count) {
		//fgets(buff, 1024, handle);
		//string message(buff);
		//int len = message.find(" ");
		//int ftime = atoi(message.substr(0, len).c_str());
		//double capacity = atoi(message.substr(len + 1).c_str());
		//i++;
		//cout<<capacity<<endl;
	//}
	return 0;
}
