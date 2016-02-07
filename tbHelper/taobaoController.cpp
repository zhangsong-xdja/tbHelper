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

void taobaoController::bufferCallback(std::string & strLine)
{
	m_pwnd->outputInfor(strLine.c_str());
}

const char * taobaoController::getCommand(void)
{
	return "adb shell uiautomator runtest tbContainer.jar -c com.container.container#runContainer";
}


void taobaoController::finishCallback(void)
{
	//m_pwnd->finishWork();
}
