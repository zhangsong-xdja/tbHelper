#pragma once

#include <string>
#include <iostream>
#include <list>
#include <vector>

#include "CppSQLite3.h"

using namespace std;

class commodity
{
public:
	sqlite_int64 id;
	string name;
	vector<string> conditions;
	vector<string> matchs;
	string share;
	string link;

	void show()
	{
		cout << "\tcommodity: " << id << "|" << name.c_str();

		cout << "[condition : " ;
		for(unsigned int i = 0; i < conditions.size(); i++)
		{
			cout << "|" << conditions[i].c_str();
		}
		cout << "]";

		cout << "[matchs : ";
		for(unsigned int i = 0; i < matchs.size(); i++)
		{
			cout << "|" << matchs[i].c_str();
		}
		cout << "]" << endl;
		cout << "share : " << share << "]" << endl;
		cout << "link : " << link << "]" << endl;
	}
};

class task
{
public:
	sqlite_int64 id;

	commodity c;

	string name;
	int times;
	bool random;
	int times_1;
	int times_2;
	int times_3;

	int rate_of_progress;

	void show()
	{
		cout << "task_id : [" << id << "|" << times << "|" << random << "|" << times_1 << "|" << times_2 << "|" <<  times_3 << "]" << endl;
		c.show();
	}
};

class taskRecord
{
public :
	string begin_time;
	string finish_time;
	bool status;
	string describe;
};

class dbOperator
{
public:
	dbOperator(void);
	~dbOperator(void);
	void createDatabase(void);

private:
	string strDbPath;
	CppSQLite3DB db;

public:
	
	bool getCommodityExtInfo(commodity & c);

	bool insertCommodity(string name, vector<string> conditions, vector<string> matchs, string share, string link);
	bool insertCommodity(commodity c);
	bool getCommodity(string name, commodity & c);
	bool getAllCommodity(vector<commodity> & l);
	bool getCommodity(sqlite_int64 id, commodity & c);
	bool deleteCommodity(int id);

	bool insertTask(string name, sqlite_int64 c_id, bool random, int times, int times_1, int times_2, int times_3);
	bool insertTask(task t);
	bool getTask(string name, task & t);
	bool getTask(int ID, task & t);
	bool getAllTask(vector<task> & tl);
	bool deleteTask(int id);
	
	string getDatabaseTime(void);

	int getTaskRecordCount(string begin_time, sqlite_int64 task_id);
	bool recordTask(sqlite_int64 task_id, string begin_time, bool status, string describe);
	int getTaskRecordCountByID(sqlite_int64 id);
	bool getTaskRecordByID(sqlite_int64 id, vector<taskRecord> &rl);
	
};

