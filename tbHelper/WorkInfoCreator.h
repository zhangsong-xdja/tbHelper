#pragma once

#include "dbOperator.h"

class WorkInfoCreator
{
public:
	WorkInfoCreator(void);
	~WorkInfoCreator(void);
	static bool create(task & t);
};

