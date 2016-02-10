#pragma once
#include "androiddebugbridge.h"
#include "commandManager.h"

class CWorkdInfoDialog;

class netQuality :	public AndroidDebugBridge
{
public:
	netQuality(CWorkdInfoDialog * p, AndroidDebugBridge * vc, commandManager * cm);
	virtual ~netQuality(void);
	virtual void bufferCallback(std::string & strLine);
	virtual const char * getCommand(void);
	virtual bool getResult(void);

private:
	CWorkdInfoDialog * m_pwnd;
	bool m_netQuality;

	AndroidDebugBridge * m_vc;
	commandManager * m_cm;
};

