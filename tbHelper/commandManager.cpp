#include "stdafx.h"
#include "commandManager.h"

#include "WorkdInfoDialog.h"

commandManager::commandManager(CWorkdInfoDialog * p)
{
	m_pwnd = p;

	::InitializeCriticalSection(&lock);
}


commandManager::~commandManager(void)
{
	::DeleteCriticalSection(&lock);
}


void commandManager::enterLock(void)
{
	::EnterCriticalSection(&lock);
}


void commandManager::leaveLock(void)
{
	::LeaveCriticalSection(&lock);
}

int commandManager::getSize(void)
{
	int size = 0;
	enterLock();
	size = adbList.size();
	leaveLock();

	return size;
}


AndroidDebugBridge* commandManager::getAdb(void)
{
	if(getSize() <= 0)
		return NULL;

	AndroidDebugBridge * result = NULL;

	enterLock();
	result = *adbList.begin();
	if(result)
		adbList.pop_front();
	leaveLock();

	return result;
}


void commandManager::insertAdb(AndroidDebugBridge* unit)
{
	enterLock();
	adbList.push_front(unit);
	leaveLock();
}


void* commandManager::workFunction(void* param)
{
	commandManager * pThis = (commandManager* )param;

	while(AndroidDebugBridge * adb = pThis->getAdb())
	{
		adb->run();

		if(!adb->getResult())
			pThis->insertAdb(adb);
	}

	pThis->finishCallback();

	return NULL;
}

void commandManager::finishCallback(void)
{
	m_pwnd->finishWork();
}


void commandManager::run(void)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->workFunction, (void*)this, 0, 0);
}
