#include "stdafx.h"
#include "vpnController.h"
#include "WorkdInfoDialog.h"

vpnController::vpnController(CWorkdInfoDialog * p)
{
	m_pwnd = p;
}


vpnController::~vpnController(void)
{
}


void vpnController::bufferCallback(std::string & strLine)
{
	m_pwnd->outputInfor(strLine.c_str());
}


const char * vpnController::getCommand(void)
{
	return "adb shell uiautomator runtest tbScript.jar -c com.uiautomatortest.setVpn2#takeVpnConnect";
}
