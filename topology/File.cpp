#include "File.h"
File::File() 
{
	this->_defaultDirname = this->_sFilePath = this->_sTempDirname = this->_sTempPath = string("");
	//this->_arr = new map<string, pathInfo>;
}

File::File(string dirname)
{
	this->_defaultDirname = dirname;
}

/**
 * @brief _pathinfo 
 * 分解文件路径信息，过滤掉文件名非法字符
 * @param {string} sDirname
 * @param {string} sBasename
 * @param {string} sExtension
 *
 * @return {struct aPathInfo}
 */
pathInfo* File:: _pathinfo(string sDirname, string sBasename, string sExtension)
{
	if (sDirname == "") {
		if (this->_defaultDirname == "") {
			this->init();
		}
		sDirname = this->_defaultDirname;
	}
	pathInfo* newPathInfo = new pathInfo();
	sDirname.erase(sDirname.find_last_not_of('/') + 1);
	newPathInfo->sDirname = sDirname;
	newPathInfo->sBasename = this->_removeForbiddenChar(&sBasename);
	if (this->_sTempDirname != "") {
		newPathInfo->sDirname = newPathInfo->sDirname + string("/") + this->_sTempDirname;
		this->_sTempPath = newPathInfo->sDirname;
	}
	if (!this->_fileMkdir(newPathInfo->sDirname)) {
		//printf("路径%s不可创建，文件路径夹格式不对"， newPathInfo->sDirname.c_str());
		cout<<"路径"<<newPathInfo->sDirname<<"不可创建，文件路径夹格式不对"<<endl;
	}
	int len = strlen(newPathInfo->sBasename.c_str());
	basic_string<char>subExtension = newPathInfo->sBasename.substr(len - 5, 4);
	if (sExtension == subExtension) {
		newPathInfo->filename = newPathInfo->sBasename.substr(0, len - 4);
	} else {
		newPathInfo->filename = newPathInfo->sBasename;
	}
	newPathInfo->sExtension = sExtension;
	return newPathInfo;
}

/**
 * @brief _fileMkdir 
 *
 * @param {string} dirname
 *
 * @return {boolean}
 */
bool File::_fileMkdir(string dirname)
{
	string cmd = string("mkdir ") + dirname;
	struct stat fileStat;
	if ((stat(dirname.c_str(), &fileStat) == 0) && S_ISDIR(fileStat.st_mode)) {
		return true;
	} else {
		const char* c_s = cmd.c_str();
		int erron = system(c_s);
		if (erron) {
			return false;
		}
	}
	return true;
}

/**
 * @brief _removeForbiddenChar 
 * 删除文件名中的一些不规则符号
 * @param {string} s
 */
string File::_removeForbiddenChar(string* s)
{
	string illegalChars = "\\/:?\"<>|";
	string::iterator it;
	for (it = s->begin() ; it < s->end() ; ++it) {
		bool found = illegalChars.find(*it) != string::npos;
		if (found) {
			*it = '_';
		}
	}
	return *s;
}

/**
 * @brief _setFileName 
 * 设置文件名
 * @param {pathInfo} fileNameInfo
 * @param {string} sFileName
 */
void File::_setFileName(pathInfo* fileNameInfo, string sFileName)
{
	fileNameInfo->filename = sFileName;
	fileNameInfo->sBasename = fileNameInfo->filename + fileNameInfo->sExtension;
}

/**
 * @brief _getFileFullPath 
 * 拼装文件全路径
 * @param {pathInfo} fileNameInfo
 *
 * @return {string}
 */
string File::_getFileFullPath(pathInfo* fileNameInfo)
{
	return fileNameInfo->sDirname + string("/") + fileNameInfo->filename + fileNameInfo->sExtension; 
}

/**
 * @brief _ItoS 
 * interge transform to string
 * @param {interge} source
 *
 * @return {string}
 */
string File::_ItoS(int source)
{
	stringstream ss;
	string str;
	ss<<source;
	ss>>str;
	return str;
}

/**
 * @brief _fileExisted 
 * file is or not existed
 * @param {string} filePath
 *
 * @return {boolean}
 */
bool File::_fileExisted(string filePath)
{
	std::fstream foo;
	foo.open(filePath.c_str());
	if (foo.is_open() == true) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief addFile 
 * 添加文件
 * @param {string} sBasename (文件名)
 * @param {string} sDirname (文件目录)
 */
void File::addFile(string sBasename, string sDirname)
{
	pathInfo* aPathInfo = this->_pathinfo(sDirname, sBasename);
	string sFileName = aPathInfo->filename;
	int iCount = 1;
	string sFilePath = this->_getFileFullPath(aPathInfo);
	while (this->_arr[sFilePath]) {
		sFileName = sFileName + string("(") + this->_ItoS(iCount) + string(")");
		this->_setFileName(aPathInfo, sFileName);
		sFilePath = this->_getFileFullPath(aPathInfo);
		iCount++;
	}
	this->_arr.insert(pair<string, bool>(sFilePath, true));
	this->_sFilePath = sFilePath;
	if (this->_fileExisted(this->_sFilePath)) {
		unlink(this->_sFilePath.c_str());
	}
	if (this->_fileHandle) {
		fclose(this->_fileHandle);
		this->_fileHandle = NULL;
	}
	this->_fileHandle = fopen(this->_sFilePath.c_str(), "w+");
	if (this->_fileHandle == NULL) {
		//printf("file open error, the file path is %s", this->_sFilePath.c_str());
		cout<<"file open error, the file path is "<<this->_sFilePath<<endl;
	}
}

/**
 * @brief init 
 * 初始化函数,默认文件夹
 */
void File::init()
{
	DIR* dir;
	struct dirent* ptr;
	dir = opendir(".");
	bool isDefaultExisted = false;
	while ((ptr = readdir(dir)) != NULL) {
		if (!strcmp(ptr->d_name, "config")) {
			isDefaultExisted = true;
		}
	}
	if (!isDefaultExisted) {
		system("mkdir config");
	}
	closedir(dir);
	this->_defaultDirname = "config";
}


/**
 * @brief setTempDirname 
 * set TempDirname
 * @param {string} tempDir
 *
 * @return {File}
 */
File& File::setTempDirname(string tempDir)
{
	this->_sTempDirname = tempDir;
	return *this;
}

/**
 * @brief getTempDirname 
 *
 * @return {string}
 */
string File::getTempDirname() const
{
	return this->_sTempDirname;
}

/**
 * @brief getlines 
 * 读取几行数据
 * @param {char**} buff
 * @param {interge} nSize
 * @param {string} filePath
 *
 */
void File::getlines(char** buff, int nSize, string filePath)
{
	int n = 0;
	this->_fileHandle = fopen(filePath.c_str(), "r");
	try {
		if (this->_fileHandle == NULL) {
			throw baseException("The filePath is error");
			//fprintf(stderr, "The filePath is error");
			//abort();
		}
		while (!feof(this->_fileHandle) && n < nSize) {
			fgets(buff[n], 50, this->_fileHandle);
			n++;
		}
	} catch (baseException e) {
		cout<<e.getMessage()<<endl;
		exit(0);
	}
}

/**
 * @brief getFilePath 
 *
 * @return {string}
 */
string File::getFilePath() const
{
	return this->_sFilePath;
}
