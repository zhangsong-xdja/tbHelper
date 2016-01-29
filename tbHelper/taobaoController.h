#pragma once
#include "androiddebugbridge.h"

class CWorkdInfoDialog;

class taobaoController :
	public AndroidDebugBridge
{
public:
	taobaoController(CWorkdInfoDialog * p);
	virtual ~taobaoController(void);
	virtual void bufferCallback(std::string & strLine);

private:
	CWorkdInfoDialog * m_pwnd;
public:
	virtual const char * getCommand(void);
	virtual void finishCallback(void);
};

