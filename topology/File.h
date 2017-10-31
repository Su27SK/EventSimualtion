#ifndef _FILE_H_
#define _FILE_H_
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <map>
#include "baseException.h"
using namespace std;
typedef struct aPathInfo
{
	string sDirname;  //目录名(/home/paul/File)
	string sBasename; //文件基本名字(file.odf, file.dat)
	string sExtension; //文件后缀(.odf, .dat)
	string filename;   //文件名(file)
}pathInfo;

class File
{
	private:
		string _defaultDirname; //默认文件夹
		string _sFilePath; //当前文件全路径
		string _sTempDirname; //临时文件夹
		string _sTempPath; //临时路径
		map<string, bool> _arr; //存放文件信息的数组
		FILE* _fileHandle; //文件句柄
		pathInfo* _pathinfo(string sDirname, string sBasename, string sExtension = ".dat");
		void _setFileName(pathInfo* fileNameInfo, string sFileName);
		string _getFileFullPath(pathInfo* fileNameInfo);
		string _removeForbiddenChar(string* s);
		bool _fileMkdir(string dirname);
		string _ItoS(int source);
		bool _fileExisted(string filePath);
	public:
		File();
		File(string dirname);
		File& setTempDirname(string tempDir);
		string getTempDirname() const;
		string getFilePath() const;
		void getlines(char** buff, int nSize, string filePath);
		void addFile(string sBasename, string sDirname = NULL);
		void init();
};
#endif
