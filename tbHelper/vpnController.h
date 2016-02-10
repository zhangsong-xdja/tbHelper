#pragma once
#include "androiddebugbridge.h"

class CWorkdInfoDialog;

class vpnController :
	public AndroidDebugBridge
{
public:
	vpnController(CWorkdInfoDialog * p);
	virtual ~vpnController(void);

	virtual void bufferCallback(std::string & strLine);
	virtual const char * getCommand(void);

private:
	CWorkdInfoDialog * m_pwnd;
	bool m_vpnConnected;
	bool m_netQuality;
public:
	virtual bool getResult(void);
};

