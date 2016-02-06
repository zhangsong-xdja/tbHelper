#pragma once
#include "androiddebugbridge.h"
class vpnController :
	public AndroidDebugBridge
{
public:
	vpnController(void);
	virtual ~vpnController(void);

	virtual void bufferCallback(std::string & strLine);
};

