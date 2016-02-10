#include "stdafx.h"
#include "vpnController.h"
#include "WorkdInfoDialog.h"

vpnController::vpnController(CWorkdInfoDialog * p)
{
	m_pwnd = p;
	m_netQuality = m_vpnConnected = false;
}


vpnController::~vpnController(void)
{
}

CString Vpn;

void vpnController::bufferCallback(std::string & strLine)
{
	m_pwnd->outputInfor(strLine.c_str());

	const char * str = strLine.c_str();
	if(strstr(str, "<TO COMPUTER>:"))
	{
		int pos[4] = {0};
		for(int i = 0, j = 0; i < strLine.size(); i++)
		{
			if(str[i] == '[' || str[i] == ']')
				pos[j++] = i;
		}
		if(pos[0] != pos[1] != pos[2] != pos[3] != 0)
		{
			m_vpnConnected = false;

			std::string output = "vpn connect status is ";
			std::string address = std::string(&str[pos[0] + 1], pos[1] - pos[0] - 1);
			output += address;
			output += "   ";
			std::string status = std::string(&str[pos[2] + 1], pos[3] - pos[2] - 1);
			output += status;
			m_pwnd->outputInfor(output.c_str());

			if(strcmp(status.c_str(), "true") == 0)
			{
				m_vpnConnected = true;
				Vpn = address.c_str();
			}
		}

		if(m_vpnConnected == true)
		{
			const char * strTmp = strLine.c_str() + strlen("<TO COMPUTER>:");

			int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
			sscanf(strTmp, "%d packets transmitted, %d received, %d%% packet loss, time %dms", &n1, &n2, &n3, &n4);
			if(n1 != 0 && n4 != 0)
			{
				m_netQuality = false;
				CString tmp;
				tmp.Format("net quality is %d%%", n3);
				m_pwnd->outputInfor(tmp.GetBuffer());

				if(n3 < 30)
					m_netQuality = true;
			}
		}
	}
}


const char * vpnController::getCommand(void)
{
	return "adb shell uiautomator runtest tbScript.jar -c com.uiautomatortest.setVpn2#takeVpnConnect";
}


bool vpnController::getResult(void)
{
	m_pwnd->outputInfor(m_vpnConnected && m_netQuality ? "******* vpn connect success *********" : "------------- vpn connect falure ---------------");

	return m_vpnConnected && m_netQuality;
}
