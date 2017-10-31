#include <execinfo.h>
#include <stdlib.h>
#include <cxxabi.h>

#include <iostream>
#include <sstream>

#include "baseException.h"

baseException::baseException(const string& msg) throw() : mMsg_(msg), mFile_("<unknow file>"), mFunc_("<unknow func>"), mLine_(-1), _mStackTraceSize(0) 
{}

baseException::~baseException() throw()
{}

/**
 * @brief init 
 * 初始化函数(当前出现exception的信息)
 * @param {const char*} file {文件名}
 * @param {const char*} func {文件中函数名}
 * @param {interge} line {行号}
 */
void baseException::init(const char* file, const char* func, int line)
{
	mFile_ = file;
	mFunc_ = func;
	mLine_ = line;
	_mStackTraceSize = backtrace(_mStackTrace, MAX_STACK_TRACE_SIZE);
}

/**
 * @brief getClassName 
 * 获得类的名字
 * @return {string}
 */
string baseException::getClassName() const
{
	return "baseException";
}

/**
 * @brief getMessage 
 * 获得message信息
 * @return {string}
 */
string baseException::getMessage() const
{
	return mMsg_;
}

/**
 * @brief what 
 * 集成自exception函数
 * @return {char*}
 */
const char* baseException::what() const throw()
{
	return ToString().c_str();
}

/**
 * @brief ToString 
 * 获得详细错误信息
 * @return {string}
 */
const string& baseException::ToString() const
{
	if (_mWhat.empty()) {
		stringstream sstr("");
		if (mLine_ > 0) {
			sstr<<mFile_<<"("<<mLine_<<")";
		}
		sstr<<": "<<getClassName();
		if (!getMessage().empty()) {
			sstr<<": "<<getMessage();
		}
		sstr<<"\nStack Trace:\n";
		sstr<<getStackTrace();
		_mWhat = sstr.str();
		return _mWhat;
	}
}

/**
 * @brief getStackTrace 
 * 获得栈信息
 * @return {string}
 */
string baseException::getStackTrace() const
{
	if (_mStackTraceSize == 0) {
		return "<No stack trace>\n";
	}
	char** strings = backtrace_symbols(_mStackTrace, 10);
	if (strings == NULL) {
		return "Unknown error: backtrace_symbols returned NULL>\n";
	}
	string result;
	for (size_t i = 0; i < _mStackTraceSize; i++) {
		string mangledName = strings[i];
		string::size_type begin = mangledName.find('(');
		string::size_type end = mangledName.find('+', begin);
		if (begin == string::npos || end == string::npos) {
			result += mangledName;
			result += '\n';
			continue;
		}
		++begin;
		int status;
		//获取函数类型
		char* s = abi::__cxa_demangle(mangledName.substr(begin, end-begin).c_str(), NULL, 0, &status);

		if (status != 0) {
			result += mangledName;
			result += '\n';
			continue;
		}
		string demangledName(s);
		free(s);

		result += mangledName.substr(0, begin);
		result += demangledName;
		result += mangledName.substr(end);
		result += '\n';
	}
	free(strings);
	return result;
}
