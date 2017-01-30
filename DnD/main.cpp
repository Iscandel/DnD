#include "CommonInterface.h"
#include "Tools/Logger.h"

#ifdef _DEBUG 
//#pragma comment(lib,"sfml-system-d.lib")
//#pragma comment(lib,"sfml-graphics-d.lib")
//#pragma comment(lib,"sfml-window-d.lib")
//#pragma comment(lib,"sfml-main-d.lib")
//#pragma comment(lib,"sfml-network-d.lib")
//#pragma comment(lib,"ws2_32.lib")
//#pragma comment(lib,"sfml-audio-d.lib")
//#pragma comment(lib, "./Dependencies/Gaia-s-d.lib")
//#pragma comment(lib, "./Dependencies/XMLLoader-s-d.lib")
//#pragma comment(lib, "./Dependencies/SFMLRenderer-s-d.lib")
#else
#pragma comment(lib,"sfml-system-s.lib")
#pragma comment(lib,"sfml-graphics-s.lib")
#pragma comment(lib,"sfml-window-s.lib")
#pragma comment(lib,"sfml-network-s.lib")
#pragma comment(lib,"sfml-audio-s.lib")
//#pragma comment(lib,"tinyxml_STL.lib")
#pragma comment(lib,"sfml-main.lib")
#endif
//#include "CreationFichierRessources.h"

int main()
{
	try
	{
		ILogger::setLogger(new ConsoleLog(std::cout));
		ILogger::setLogLevel(ILogger::ALL);
		CommonInterface comInterface;
		comInterface.run();
	}
	catch (const std::exception& e) //sometimes there's a pb. Exception not caught in main...
	{
		ILogger::log(ILogger::ERRORS) << e.what() << "\n";
		getchar();
	}
	catch (...)
	{
		ILogger::log(ILogger::ERRORS) << "Unknown exception...\n";
		getchar();
	}
	return 0;
}