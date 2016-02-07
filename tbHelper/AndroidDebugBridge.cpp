#include "stdafx.h"
#include "AndroidDebugBridge.h"


AndroidDebugBridge::AndroidDebugBridge(void)
{
	memset(curPath, 0, sizeof(curPath));
	memset(adbPath, 0, sizeof(adbPath));

	::GetCurrentDirectory(sizeof(curPath), curPath);
	sprintf(adbPath, "%s/%s", curPath, "adb.exe");

	buffer.clear();
}


AndroidDebugBridge::~AndroidDebugBridge(void)
{
}


bool AndroidDebugBridge::run()
{
	char Buffer[4096];  
    STARTUPINFO sInfo;  
    PROCESS_INFORMATION pInfo;  
    SECURITY_ATTRIBUTES sa;  
    HANDLE hRead,hWrite;  
    DWORD bytesRead;  

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);  
    sa.lpSecurityDescriptor = NULL;  
    sa.bInheritHandle = TRUE;  
  
    if (!CreatePipe(&hRead,&hWrite,&sa,0)) //创建匿名管道  
    {  
        goto out;  
    }  
  
    GetStartupInfo(&sInfo);  
    sInfo.cb = sizeof(sInfo);  
    sInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;  
    sInfo.wShowWindow = SW_HIDE;  
    sInfo.hStdError = hWrite;   //将管道的写端交给子进程  
    sInfo.hStdOutput = hWrite;  
    memset(&pInfo, 0, sizeof(pInfo));  
  
	if(!CreateProcess((LPSTR)adbPath, (LPSTR)getCommand(), NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo)) //创建子进程  
    {  
        CloseHandle(hWrite);  
        CloseHandle(hRead);  

		goto out;  
    }  
    CloseHandle(hWrite); //关闭父进程的写端  
  
    while (1)  
    {  
        if (!ReadFile(hRead,Buffer,sizeof(Buffer)-1,&bytesRead,NULL)) //读取内容  
        {  
            break;  
        }  
        Buffer[bytesRead] = 0;  

		for(unsigned int i = 0; i < bytesRead; i++)
			buffer.push_back(Buffer[i]);

		lineParser();
    }  
  
    WaitForSingleObject(pInfo.hProcess, INFINITE);  
    CloseHandle(hRead);  

	lineParser();

	return true;
out:  
	return false;  
}


void AndroidDebugBridge::lineParser(void)
{
	while(true)
	{
		std::list<char>::iterator it = buffer.begin();
		for(; it != buffer.end(); it++)
		{
			if((*it) == END_FLAG)
				break;
		}

		if(it != buffer.end())
		{
			std::string line;

			std::list<char>::iterator end = ++it;
			for(it = buffer.begin(); it != end; it++)
			{
				if(*it != END_FLAG && *it != END_FLAG2)
					line.push_back(*it);
			}
			buffer.erase(buffer.begin(), end);

			bufferCallback(line);
		}
		else
			break;
	}
}


void AndroidDebugBridge::start(void)
{
	this->hThread = ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->workThread, (void*)this, 0, 0);
}


void* AndroidDebugBridge::workThread(void* param)
{
	AndroidDebugBridge * pThis = (AndroidDebugBridge *)param;

	pThis->run();

	pThis->finishCallback();

	return 0;
}


void AndroidDebugBridge::finishCallback(void)
{
}


bool AndroidDebugBridge::getResult(void)
{
	return true;
}
