#include "stdafx.h"
#include "taobaoController.h"
#include "WorkdInfoDialog.h"

taobaoController::taobaoController(CWorkdInfoDialog * p)
{
	m_pwnd = p;
}


taobaoController::~taobaoController(void)
{
}

extern CString Vpn;

void taobaoController::bufferCallback(std::string & strLine)
{
	static int taskID;
	static string begin_time;

	m_pwnd->outputInfor(strLine.c_str());
	const char * str = strLine.c_str();
	if(strstr(str, "<TO COMPUTER>:"))
	{
		//<TO COMPUTER>:TASK BEGIN[taskID [2]]
		//<TO COMPUTER>:TASK SUCCESS[taskID [2]]
		//<TO COMPUTER>:TASK FALURE[taskID [2]entrySearchResultActivity]

		int pos[4] = {0};
		for(int i = 0, j = 0; i < strLine.size(); i++)
		{
			if(str[i] == '[' || str[i] == ']')
				pos[j++] = i;
		}
		if(pos[0] != pos[1] != pos[2] != pos[3] != 0)
		{
			if(strstr(str, "TASK BEGIN"))
			{
				string strID = string(&str[pos[1] + 1], pos[2] - pos[1] - 1);
				taskID = atoi(strID.c_str());
				begin_time = db.getDatabaseTime();
			}
			else if(strstr(str, "TASK SUCCESS"))
			{
				db.recordTask((sqlite_int64)taskID, begin_time, 1, string(Vpn.GetBuffer(0)));
				m_pwnd->addProcessPos();
			}
			else
			{
				string status = string(&str[pos[2] + 1], pos[3] - pos[2] - 1);
				db.recordTask((sqlite_int64)taskID, begin_time, 0, status);
				m_pwnd->addProcessPos();
			}
			
		}
	}
}

const char * taobaoController::getCommand(void)
{
	return "adb shell uiautomator runtest tbContainer.jar -c com.container.container#runContainer";
}


void taobaoController::finishCallback(void)
{
	//m_pwnd->finishWork();
}
