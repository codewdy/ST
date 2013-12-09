#ifndef ST_8932849283_Exception_Exception
#define ST_8932849283_Exception_Exception
#include <string>
#include <iostream>
namespace Exception
{
	extern std::ostream* LogFile;
	class Exception
	{
	public:
		virtual std::string message()
		{
			return "";
		}
	};
}

#ifdef DEBUG
#define Raise(TYPE, ...) do{\
	Exception::TYPE ex = Exception::TYPE(__VA_ARGS__);\
	*(Exception::LogFile) << "Exception[" << #TYPE << "] Raise At " << __FILE__ << "." << __LINE__ \
		<< ":" << ex.message() << std::endl;\
	throw ex;\
}while(0)
#else
#define Raise(TYPE, ...) do{\
	Exception::TYPE ex = Exception::TYPE(__VA_ARGS__);\
	throw ex;\
}while(0)
#endif

#ifdef DEBUG
#define Warn(Warning) do{\
	Exception::LogFile << "Waring at " << __FILE__ << "." << __LINE__ \
		<< ":" << Warning << std::endl;\
}while(0)
#else
#define Warn(Warning) do{}while(0)
#endif

#endif

