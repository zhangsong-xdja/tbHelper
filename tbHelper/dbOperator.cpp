#include "dbOperator.h"


dbOperator::dbOperator(void)
{
	strDbPath = "./database.db";
	db.open(strDbPath.c_str());
}


dbOperator::~dbOperator(void)
{
}


void dbOperator::createDatabase(void)
{
	/*
		主键唯一标识商品
		name 为商品描述
	*/
	const char * str_cmd_of_create_commdity_table = "create table if not exists commodity(id integer primary key, name char(30) unique);";

	/*
		c_id是所属商品id
		describe是所属商品的一个搜索条件
	*/
	const char * str_cmd_of_create_condition_table = "create table if not exists condition(c_id integer, condition string);";

	/*
		c_id是所属商品id
		match是所属商品的一个匹配条件
	*/
	const char * str_cmd_of_create_match_table = "create table if not exists match(c_id integer, match string);";

	/*
		id是任务的唯一标识
		c_id是所属商品id
		random是否随机流量另外一个商品
		times是该任务执行次数
		times_1是商品翻动次数
		times_2是评论翻动次数
		times_3是随机浏览商品翻动次数
	*/
	const char * str_cmd_of_create_task_table = "create table if not exists task(id integer primary key, c_id integer, random boolean, times integer, times_1 integer, "
		"times_2 integer, times_3 integer);";

	/*
		id主键
		task_id执行了哪个任务
		begintime开始时间
		endtime结束时间
		status执行结果
		describe执行结果描述
	*/
	const char * str_cmd_of_create_taskRecord_table = "create table if not exists taskRecord(id integer primary key, task_id integer, begintime datetime, endtime datetime, "
		"status boolean, describe string);";

	try{
		db.execDML(str_cmd_of_create_commdity_table);
		db.execDML(str_cmd_of_create_condition_table);
		db.execDML(str_cmd_of_create_match_table);
		db.execDML(str_cmd_of_create_task_table);
		db.execDML(str_cmd_of_create_taskRecord_table);
	}
	catch (CppSQLite3Exception & e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
    }
}


bool dbOperator::insertCommodity(string name, vector<string> conditions, vector<string> matchs)
{
	if(name.size() <= 0 || conditions.size() <= 0 || matchs.size() <= 0)
		return false;

	string str_cmd_of_insert_commodity = "insert into commodity (name) values (\"";
	str_cmd_of_insert_commodity += name;
	str_cmd_of_insert_commodity += "\");";

	try{
		db.execDML(str_cmd_of_insert_commodity.c_str());
		sqlite_int64 c_id = db.lastRowId();
		if(c_id < 1)
			return false;


		for(unsigned int i = 0; i < conditions.size(); i++)
		{
			char tmp[128] = {0};
			sprintf(tmp, "insert into condition (c_id, condition) values(%lld, \"", c_id);

			string str_cmd_of_insert_condition = tmp;
			str_cmd_of_insert_condition += conditions[i];
			str_cmd_of_insert_condition += "\");";

			db.execDML(str_cmd_of_insert_condition.c_str());
		}

		for(unsigned int i = 0; i < matchs.size(); i++)
		{
			char tmp[128] = {0};
			sprintf(tmp, "insert into match (c_id, match) values(%lld, \"", c_id);

			string str_cmd_of_insert_match = tmp;
			str_cmd_of_insert_match += matchs[i];
			str_cmd_of_insert_match += "\");";

			db.execDML(str_cmd_of_insert_match.c_str());
		}

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return false;
}


bool dbOperator::recordTask(sqlite_int64 task_id, string begin_time, bool status, string describe)
{
	try{
		char tmp[128] = {0};
		sprintf(tmp, "insert into task (task_id, begintime, endtime, status, describe) values(%lld, \"%s\", datetime(), %d, \"", 
			task_id, begin_time.c_str(), status);
		string str_cmd_of_record_task = tmp;
		str_cmd_of_record_task += describe;
		str_cmd_of_record_task += "\");";

		return db.execDML(str_cmd_of_record_task.c_str()) > 0;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
	return false;
}


bool dbOperator::insertTask(sqlite_int64 c_id, bool random, int times, int times_1, int times_2, int times_3)
{
	try{
		char str_cmd_of_insert_task[128] = {0};
		sprintf(str_cmd_of_insert_task, "insert into task (c_id, random, times, times_1, times_2, times_3) values(%lld, %d, %d, %d, %d, %d);", 
			c_id, random, times, times_1, times_2, times_3);
		

		return db.execDML(str_cmd_of_insert_task) > 0;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
	return false;
}


bool dbOperator::insertCommodity(commodity c)
{
	return insertCommodity(c.name, c.conditions, c.matchs);
}


bool dbOperator::insertTask(task t)
{
	return insertTask(t.c.id, t.random, t.times, t.times_1, t.times_2, t.times_3);
}


bool dbOperator::getCommodity(string name, commodity & c)
{
	try{
		
		string str_cmd_of_query_commodity = "select id from commodity where name = '";
		str_cmd_of_query_commodity += name;
		str_cmd_of_query_commodity += "';";
		
		CppSQLite3Query q = db.execQuery(str_cmd_of_query_commodity.c_str());
		if(q.numFields() != 1 || q.eof())
			return false;

		sqlite_int64 id = q.getInt64Field("id", -1);
		if(id < 0)
			return false;

		c.id = id;

		char str_cmd_query_condition[128] = {0};
		sprintf(str_cmd_query_condition, "select condition from condition where c_id = %lld;", id);
		CppSQLite3Query q2 = db.execQuery(str_cmd_query_condition);
		if(q2.numFields() != 1 || q2.eof())
			return false;

		while(!q2.eof())
		{
			c.conditions.push_back(q2.getStringField("condition"));
			q2.nextRow();
		}

		char str_cmd_of_query_match[128] = {0};
		sprintf(str_cmd_of_query_match, "select match from match where c_id = %lld;", id);
		CppSQLite3Query q3 = db.execQuery(str_cmd_of_query_match);
		if(q3.numFields() != 1 || q3.eof())
			return false;

		while(!q3.eof())
		{
			c.matchs.push_back(q3.getStringField("match"));
			q3.nextRow();
		}

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return false;
}


bool dbOperator::getTask(string name, task & t)
{
	try{
		if(!getCommodity(name, t.c))
			return false;

		char str_cmd_of_query_task[128] = {0};
		sprintf(str_cmd_of_query_task, "select id, random, times, times_1, times_2, times_3 from task where c_id = %lld", t.c.id);
		CppSQLite3Query q = db.execQuery(str_cmd_of_query_task);
		if(q.numFields() != 6 || q.eof())
			return false;

		t.id = q.getInt64Field("id", -1);
		t.random = q.getIntField("random", 0) != 0;
		t.times = q.getIntField("times", -1);
		t.times_1 = q.getIntField("times_1", -1);
		t.times_2 = q.getIntField("times_2", -1);
		t.times_3 = q.getIntField("times_3", -1);

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
	return false;
}


string dbOperator::getDatabaseTime(void)
{
	try{
		char str_cmd_of_select_datetime[128] = {0};
		sprintf(str_cmd_of_select_datetime, "select datetime();");
		CppSQLite3Query q = db.execQuery(str_cmd_of_select_datetime);
		if(q.numFields() != 1 || q.eof())
			return false;

		return string(q.getStringField(0));
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return string();
}


int dbOperator::getTaskRecordCount(string begin_time, sqlite_int64 task_id)
{
	try{
		char str_cmd_of_select_task_rocord_time[128] = {0};
		sprintf(str_cmd_of_select_task_rocord_time, "select count(*) from taskRecord where begintime > '%s' and endtime < datetime();", begin_time.c_str());

		CppSQLite3Query q = db.execQuery(str_cmd_of_select_task_rocord_time);
		if(q.numFields() != 1 || q.eof())
			return -1;

		return q.getIntField(0, -1);
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return -1;
}


bool dbOperator::getAllCommodity(vector<commodity> & l)
{
	try{
		char str_cmd_of_query_commodity_name[128] = {0};
		sprintf(str_cmd_of_query_commodity_name, "select name from commodity;");

		CppSQLite3Query q3 = db.execQuery(str_cmd_of_query_commodity_name);

		if(q3.numFields() != 1 || q3.eof())
			return false;

		vector<string> namelist;
		while(!q3.eof())
		{
			namelist.push_back(q3.getStringField("name"));
			q3.nextRow();
		}

		for(int i = 0; i < namelist.size(); i++)
		{
			commodity c;
			c.name = namelist[i];
			if(!getCommodity(namelist[i], c))
				return false;

			l.push_back(c);
		}

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
	return false;
}


bool dbOperator::getAllTask(vector<task> & tl)
{
	try{
		char str_cmd_of_query_all_task[128] = {0};
		sprintf(str_cmd_of_query_all_task, "select id, c_id, random, times, times_1, times_2, times_3 from task;");

		CppSQLite3Query q3 = db.execQuery(str_cmd_of_query_all_task);

		if(q3.numFields() != 7 || q3.eof())
			return false;

		vector<string> namelist;
		while(!q3.eof())
		{
			task t;

			t.id = q3.getInt64Field("id", -1);
			t.random = q3.getIntField("random", 0) != 0;
			t.times = q3.getIntField("times", -1);
			t.times_1 = q3.getIntField("times_1", -1);
			t.times_2 = q3.getIntField("times_2", -1);
			t.times_3 = q3.getIntField("times_3", -1);
			t.c.id = q3.getIntField("c_id", -1);

			if(!getCommodity(t.c.id, t.c))
				return false;

			tl.push_back(t);

			q3.nextRow();
		}

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
	return false;
}


bool dbOperator::getCommodity(sqlite_int64 id, commodity & c)
{
	try{
		
		char str_cmd_of_query_commodity[128] = {0};
		sprintf(str_cmd_of_query_commodity, "select name from commodity where id = %lld", id);
		
		CppSQLite3Query q = db.execQuery(str_cmd_of_query_commodity);
		if(q.numFields() != 1 || q.eof())
			return false;

		c.id = id;
		c.name = q.getStringField("name");

		char str_cmd_query_condition[128] = {0};
		sprintf(str_cmd_query_condition, "select condition from condition where c_id = %lld;", id);
		CppSQLite3Query q2 = db.execQuery(str_cmd_query_condition);
		if(q2.numFields() != 1 || q2.eof())
			return false;

		while(!q2.eof())
		{
			c.conditions.push_back(q2.getStringField("condition"));
			q2.nextRow();
		}

		char str_cmd_of_query_match[128] = {0};
		sprintf(str_cmd_of_query_match, "select match from match where c_id = %lld;", id);
		CppSQLite3Query q3 = db.execQuery(str_cmd_of_query_match);
		if(q3.numFields() != 1 || q3.eof())
			return false;

		while(!q3.eof())
		{
			c.matchs.push_back(q3.getStringField("match"));
			q3.nextRow();
		}

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return false;
}
