#pragma once

#define END_FLAG '\n'
#define END_FLAG2 '\r'

#include <list>

class AndroidDebugBridge
{
public:
	AndroidDebugBridge(void);
	virtual ~AndroidDebugBridge(void);
	virtual bool run();
private:
	char curPath[MAX_PATH];
	char adbPath[MAX_PATH];
	std::list<char> buffer;
public:
	virtual void bufferCallback(std::string & strLine) = 0;
private:
	void lineParser(void);
public:
	virtual const char * getCommand(void) = 0;
};

