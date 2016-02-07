#pragma once

#include <list>

#include "AndroidDebugBridge.h"

class CWorkdInfoDialog;

class commandManager
{
public:
	commandManager(CWorkdInfoDialog * p);
	virtual ~commandManager(void);

private:
	std::list<AndroidDebugBridge *> adbList;
	::CRITICAL_SECTION lock;

	void enterLock(void);
	void leaveLock(void);

	CWorkdInfoDialog * m_pwnd;

public:
	static void* workFunction(void* param);
	int getSize(void);
	AndroidDebugBridge* getAdb(void);
	void insertAdb(AndroidDebugBridge* unit);
	void finishCallback(void);
	void run(void);
};

