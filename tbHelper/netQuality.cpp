#include "stdafx.h"
#include "netQuality.h"
#include "WorkdInfoDialog.h"


netQuality::netQuality(CWorkdInfoDialog * p, AndroidDebugBridge * vc, commandManager * cm)
{
	m_pwnd = p;
	m_netQuality = false;
}


netQuality::~netQuality(void)
{
}


void netQuality::bufferCallback(std::string & strLine)
{
	m_pwnd->outputInfor(strLine.c_str());
	
	if(strstr(strLine.c_str(), "packets transmitted"))
	{
		m_netQuality = false;

		int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
		sscanf(strLine.c_str(), "%d packets transmitted, %d received, %d%% packet loss, time %dms", &n1, &n2, &n3, &n4);
		if(n1 != 0)
		{
			CString tmp;
			tmp.Format("net quality is %d%%", n3);
			m_pwnd->outputInfor(tmp.GetBuffer());

			if(n3 < 30)
				m_netQuality = true;
		}
	}

}


const char * netQuality::getCommand(void)
{
	return "adb shell \"ping -c 10 8.8.8.8\"";		//115.239.210.27
}


bool netQuality::getResult(void)
{
	if(m_netQuality == false)
	{
		m_cm->insertAdb(this);
		m_cm->insertAdb(m_vc);

		m_pwnd->outputInfor("vpn too bad, choose other one");
	}

	return m_netQuality;
}
