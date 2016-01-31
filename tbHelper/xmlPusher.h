#pragma once
#include "androiddebugbridge.h"

class xmlPusher :
	public AndroidDebugBridge
{
public:
	xmlPusher(void);
	virtual ~xmlPusher(void);
	virtual const char * getCommand(void);
	virtual void bufferCallback(std::string & strLine);
};

