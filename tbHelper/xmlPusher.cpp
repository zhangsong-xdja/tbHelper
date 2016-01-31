#include "stdafx.h"
#include "xmlPusher.h"


xmlPusher::xmlPusher(void)
{
}


xmlPusher::~xmlPusher(void)
{
}


const char * xmlPusher::getCommand(void)
{
	return "apdb push ./work.xml /data/local/tmp/test.xml";
}


void xmlPusher::bufferCallback(std::string & strLine)
{
	OutputDebugString(strLine.c_str());
}
