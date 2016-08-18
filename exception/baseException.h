#ifndef	_BASEEXCEPTION_H_
#define _BASEEXCEPTION_H_
#include <exception>
#include <string>

class baseException: public exception
{
	public:
		baseException(const string& msg = "") throw();
		virtual ~baseException() throw();
		void init(const char* file, const char* func, int line);
		virtual string getClassName() const;
		virtual string getMessage() const;
		const char* what() const throw();
		const string& ToString() const;
		string getStackTrace() const;
	protected:
		string mMsg_;
		const char* mFile_;
		const char* mFunc_;
		int mLine_;
	private:
		enum {MAX_STACK_TRACE_SIZE = 50};
		void* _mStackTrace[MAX_STACK_TRACE_SIZE];
		size_t _mStackTraceSize;
		mutable string _mWhat;
};
#endif
