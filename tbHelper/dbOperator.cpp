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
		c_id是所属商品id
		link是商品链接
	*/
	const char * str_cmd_of_create_link_table = "create table if not exists link(c_id integer, link string);";

	/*
		c_id是所属商品id
		share是商品分享
	*/
	const char * str_cmd_of_create_share_table = "create table if not exists share(c_id integer, share string);";

	/*
		id是任务的唯一标识
		c_id是所属商品id
		random是否随机流量另外一个商品
		times是该任务执行次数
		times_1是商品翻动次数
		times_2是评论翻动次数
		times_3是随机浏览商品翻动次数
	*/
	const char * str_cmd_of_create_task_table = "create table if not exists task(id integer primary key, name string unique, c_id integer, random boolean, times integer, times_1 integer, "
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
		db.execDML(str_cmd_of_create_share_table);
		db.execDML(str_cmd_of_create_link_table);
	}
	catch (CppSQLite3Exception & e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
    }
}


bool dbOperator::insertCommodity(string name, vector<string> conditions, vector<string> matchs, string share, string link)
{
	if(name.size() <= 0)
		return false;

	if(
		(conditions.size() <= 0 || matchs.size() <= 0) &&
		link.size() <= 0 &&
		share.size() <= 0
		)
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

		if(share.size())
		{
			char str_cmd_of_insert_share_tmp[128] = {0};
			sprintf(str_cmd_of_insert_share_tmp, "insert into share(c_id, share) values(%lld, '", c_id);
			string str_cmd_of_insert_share = str_cmd_of_insert_share_tmp;
			str_cmd_of_insert_share += share;
			str_cmd_of_insert_share += "');";
			db.execDML(str_cmd_of_insert_share.c_str());
		}

		if(link.size())
		{
			char str_cmd_of_insert_link_tmp[128] = {0};
			sprintf(str_cmd_of_insert_link_tmp, "insert into link (c_id, link) values(%lld, '", c_id);
			string str_cmd_of_insert_link = str_cmd_of_insert_link_tmp;
			str_cmd_of_insert_link += link;
			str_cmd_of_insert_link += "');";
			db.execDML(str_cmd_of_insert_link.c_str());
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
		char tmp[512] = {0};
		sprintf(tmp, "insert into taskRecord (task_id, begintime, endtime, status, describe) values(%lld, '%s', datetime('now','+8 hour'), %d, '", 
			task_id, begin_time.c_str(), status);
		string str_cmd_of_record_task = tmp;
		str_cmd_of_record_task += describe;
		str_cmd_of_record_task += "');";
	
		return db.execDML(str_cmd_of_record_task.c_str()) > 0;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
	return false;
}


bool dbOperator::insertTask(string name, sqlite_int64 c_id, bool random, int times, int times_1, int times_2, int times_3)
{
	try{
		char str_cmd_of_insert_task[128] = {0};
		sprintf(str_cmd_of_insert_task, "insert into task (name, c_id, random, times, times_1, times_2, times_3) values('%s', %lld, %d, %d, %d, %d, %d);", 
			name.c_str(), c_id, random, times, times_1, times_2, times_3);
		

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
	return insertCommodity(c.name, c.conditions, c.matchs, c.share, c.link);
}


bool dbOperator::insertTask(task t)
{
	return insertTask(t.name, t.c.id, t.random, t.times, t.times_1, t.times_2, t.times_3);
}



bool dbOperator::getCommodityExtInfo(commodity & c)
{
	try{
		sqlite_int64 id = c.id;
		
		char str_cmd_query_condition[128] = {0};
		sprintf(str_cmd_query_condition, "select condition from condition where c_id = %lld;", id);
		CppSQLite3Query q2 = db.execQuery(str_cmd_query_condition);
		if(q2.numFields() != 1)
			return false;

		while(!q2.eof())
		{
			c.conditions.push_back(q2.getStringField("condition"));
			q2.nextRow();
		}

		char str_cmd_of_query_match[128] = {0};
		sprintf(str_cmd_of_query_match, "select match from match where c_id = %lld;", id);
		CppSQLite3Query q3 = db.execQuery(str_cmd_of_query_match);
		if(q3.numFields() != 1)
			return false;

		while(!q3.eof())
		{
			c.matchs.push_back(q3.getStringField("match"));
			q3.nextRow();
		}

		char str_cmd_of_query_share[128] = {0};
		sprintf(str_cmd_of_query_share, "select share from share where c_id = %lld;", id);
		CppSQLite3Query q4 = db.execQuery(str_cmd_of_query_share);
		if(q4.numFields() != 1)
			return false;

		while(!q4.eof())
		{
			c.share = q4.getStringField("share");
			q4.nextRow();
		}

		char str_cmd_of_query_link[128] = {0};
		sprintf(str_cmd_of_query_link, "select link from link where c_id = %lld;", id);
		CppSQLite3Query q5 = db.execQuery(str_cmd_of_query_link);
		if(q5.numFields() != 1)
			return false;

		while(!q5.eof())
		{
			c.link = q5.getStringField("link");
			q5.nextRow();
		}

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return false;
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
		c.name = name;

		return getCommodityExtInfo(c);
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
		sprintf(str_cmd_of_query_task, "select id, random, times, times_1, times_2, times_3, name from task where c_id = %lld", t.c.id);
		CppSQLite3Query q = db.execQuery(str_cmd_of_query_task);
		if(q.numFields() != 7 || q.eof())
			return false;

		t.id = q.getInt64Field("id", -1);
		t.random = q.getIntField("random", 0) != 0;
		t.times = q.getIntField("times", -1);
		t.times_1 = q.getIntField("times_1", -1);
		t.times_2 = q.getIntField("times_2", -1);
		t.times_3 = q.getIntField("times_3", -1);
		t.name = q.getStringField("name");

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
		sprintf(str_cmd_of_select_datetime, "select datetime('now','+8 hour');");
		CppSQLite3Query q = db.execQuery(str_cmd_of_select_datetime);
		if(q.numFields() != 1 || q.eof())
			return false;
		const char * name = q.fieldName(0);
		const char * time = q.fieldValue(name);
		
		return string(time);
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
		sprintf(str_cmd_of_query_all_task, "select id, c_id, random, times, times_1, times_2, times_3, name from task;");

		CppSQLite3Query q3 = db.execQuery(str_cmd_of_query_all_task);

		if(q3.numFields() != 8 || q3.eof())
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
			t.name = q3.getStringField("name");

			if(!getCommodity(t.c.id, t.c))
				return false;

			int rop = getTaskRecordCountByID(t.id);
			if(rop < 0)
				return false;

			t.rate_of_progress = (double)rop / t.times * 100;

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

		return getCommodityExtInfo(c);
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return false;
}


bool dbOperator::deleteTask(int id)
{
	try{
		char str_cmd_of_delete_task[128] = {0};
		sprintf(str_cmd_of_delete_task, "delete from task where id = %d;delete from taskRecord where task_id = %d;", id, id);

		db.execDML(str_cmd_of_delete_task);

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return false;
}

int dbOperator::getTaskRecordCountByID(sqlite_int64 id)
{
	try{
		char str_cmd_of_get_record_count_by_id[128] = {0};
		sprintf(str_cmd_of_get_record_count_by_id, "select count(*) from taskRecord where task_id = %lld;", id);

		CppSQLite3Query q = db.execQuery(str_cmd_of_get_record_count_by_id);
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


bool dbOperator::deleteCommodity(int id)
{
	try{
		char str_cmd_of_delete_task[128] = {0};
		sprintf(str_cmd_of_delete_task, "delete from task where c_id = %d;", id);

		db.execDML(str_cmd_of_delete_task);

		char str_cmd_of_delete_commodity[128] = {0};
		sprintf(str_cmd_of_delete_commodity, "delete from commodity where id = %d;delete from match where c_id = %d;delete from condition where c_id = %d;", id, id, id);

		db.execDML(str_cmd_of_delete_commodity);
		
		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	return false;
}

bool dbOperator::getTaskRecordByID(sqlite_int64 id, vector<taskRecord> &rl)
{
	//id integer primary key, task_id integer, begintime datetime, endtime datetime, "
	//	"status boolean, describe string);";

	try{
		char str_cmd_of_query_taskRecord[128] = {0};
		sprintf(str_cmd_of_query_taskRecord, "select begintime, endtime, status, describe from taskRecord where task_id = %lld;", id);
		CppSQLite3Query q = db.execQuery(str_cmd_of_query_taskRecord);
		if(q.numFields() != 4 || q.eof())
			return false;

		while(!q.eof())
		{
			taskRecord tr;
			tr.begin_time = q.getStringField("begintime");
			tr.finish_time = q.getStringField("endtime");
			tr.status = q.getIntField("status") != 0;
			tr.describe = q.getStringField("describe");

			rl.push_back(tr);

			q.nextRow();
		}
		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
	return false;
}


bool dbOperator::getTask(int ID, task & t)
{
	try{
		char str_cmd_of_query_task[128] = {0};
		sprintf(str_cmd_of_query_task, "select id, random, times, times_1, times_2, times_3, name, c_id from task where id = %d;", ID);
		CppSQLite3Query q = db.execQuery(str_cmd_of_query_task);
		if(q.numFields() != 8 || q.eof())
			return false;

		t.id = q.getInt64Field("id", -1);
		t.random = q.getIntField("random", 0) != 0;
		t.times = q.getIntField("times", -1);
		t.times_1 = q.getIntField("times_1", -1);
		t.times_2 = q.getIntField("times_2", -1);
		t.times_3 = q.getIntField("times_3", -1);
		t.name = q.getStringField("name");
		t.c.id = q.getIntField("c_id", -1);

		if(!getCommodity(t.c.id, t.c))
			return false;

		return true;
	}
	catch (CppSQLite3Exception & e)
	{
		cerr << e.errorCode() << ":" << e.errorMessage() << endl;
	}
	return false;
}
