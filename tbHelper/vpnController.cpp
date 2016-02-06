#include "stdafx.h"
#include "vpnController.h"


vpnController::vpnController(void)
{
}


vpnController::~vpnController(void)
{
}


void vpnController::bufferCallback(std::string & strLine)
{
}


const char * vpnController::getCommand(void)
{
	return "adb shell uiautomator runtest tbScript.jar -c com.uiautomatortest.setVpn2#takeVpnConnect";
}
