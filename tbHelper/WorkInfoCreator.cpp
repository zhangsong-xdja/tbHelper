#include "stdafx.h"
#include "WorkInfoCreator.h"

#include <stdio.h>

#include "tinyxml2.h"

using namespace tinyxml2;

WorkInfoCreator::WorkInfoCreator(void)
{
}


WorkInfoCreator::~WorkInfoCreator(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////
void string2wstring(const std::string& _str, std::wstring& _wstr )
{  
	if(_str == "") 
		return; 

	_wstr = L"";  

	int wlen = MultiByteToWideChar( CP_ACP, 0, _str.c_str(), -1, NULL, 0 ); 
	wchar_t * pwc = new wchar_t[wlen]; 
	memset((char*)pwc, 0, wlen*2);  
	MultiByteToWideChar( CP_ACP, 0, _str.c_str(), -1, pwc, wlen ); 
	_wstr = pwc;  

	/*unsigned char* p = (unsigned char*)pwc;
	for ( int i=0; i<wlen*2; ++i )
		cout<<uppercase<<hex<<int(p[i])<<" ";
	cout<<endl;*/

	delete []pwc; 
}  

std::string& wstring2string(const std::wstring& _wstr, std::string& _str ) 
{  
	if( _wstr == L"") 
		return _str; 

	_str = "";  
	int len = WideCharToMultiByte( CP_ACP, 0, _wstr.c_str(), -1, NULL, 0, NULL, NULL );  
	unsigned char * pc = new unsigned char[len]; 
	memset( pc, 0, len );  
	WideCharToMultiByte( CP_ACP, 0, _wstr.c_str(), -1, (char*)pc, len, NULL, NULL );  
	_str = (char*)pc;  

	/*for ( int i=0; i<len; ++i )
	cout<<uppercase<<hex<<int(pc[i])<<" ";
	cout<<endl;*/

	delete []pc; 

	return _str; 
}  

void UTF8string2wstring(const std::string& _str, std::wstring& _wstr)
{  
	if( _str == "") 
		return; 

	std::string str;  
	if( _str.size() > 3 && (unsigned char)_str[0] == 0xEF && (unsigned char)_str[1] == 0xBB && (unsigned char)_str[2] == 0xBF) 
		str = _str.substr( 3 ); 
	else
		str = _str; 

	_wstr = L"";  
	int len = _str.size() + 1;  
	int wlen = MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, NULL, 0 ); 
	wchar_t * pwc = new wchar_t[wlen]; 

	memset( (char*)pwc, 0, wlen*2 );  
	MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, pwc, wlen ); 
	_wstr = pwc;  

	/*unsigned char* p = (unsigned char*)pwc;
	for ( int i=0; i<wlen*2; ++i )
	cout<<uppercase<<hex<<int(p[i])<<" ";
	cout<<endl;
	*/

	delete []pwc;  
}  

std::string& wstring2utf8string( const std::wstring& _wstr, std::string& _str ) 
{  
	if( _wstr == L"") 
		return _str; 
	
	_str = "";  
	int len = WideCharToMultiByte( CP_UTF8, 0, _wstr.c_str(), -1, NULL, 0, NULL, NULL );  
	unsigned char * pc = new unsigned char [len]; 
	memset( pc, 0, len );  
	WideCharToMultiByte( CP_UTF8, 0, _wstr.c_str(), -1, (char *)pc, len, NULL, NULL );  
	_str = (char*)pc; 

	/*
	for ( int i=0; i<len; ++i )
	cout<<uppercase<<hex<<int(pc[i])<<" ";
	cout<<endl;*/

	delete []pc; 

	return _str; 
} 
////////////////////////////////////////////////////////////////////////////////////////////
/**/

bool WorkInfoCreator::create(task & t)
{
	//先检测任务信息
	
	if(t.id <= 0)
		return false;
	if(t.c.id <= 0)
		return false;
	if(t.name.length() <= 0)
		return false;
	if(t.c.name.length() <= 0)
		return false;
	if(t.c.conditions.size() <= 0)
		return false;
	if(t.c.matchs.size() <= 0)
		return false;
		
	//开始生成xml（此时还不是utf8）
	tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();

    XMLDeclaration *declaration = doc->NewDeclaration();
    doc->InsertFirstChild(declaration);

	XMLElement * Commoditys = doc->NewElement("Commoditys");
	XMLNode * root = doc->InsertEndChild(Commoditys);

	XMLElement * Commodity = doc->NewElement("Commodity");
	XMLNode *element = root->InsertEndChild(Commodity);
	Commodity->SetAttribute("id", (int)t.id);

	XMLNode * conditions = element->InsertEndChild(doc->NewElement("SearchCondition"));
	for(int i = 0; i < t.c.conditions.size(); i++)
	{
		XMLElement *sub = doc->NewElement("SubSearchCondition");
		XMLText *text = doc->NewText(t.c.conditions[i].c_str());
		sub->InsertFirstChild(text);
		conditions->InsertEndChild(sub);
	}

	XMLNode * matchs = element->InsertEndChild(doc->NewElement("Match"));
	for(int i = 0; i < t.c.matchs.size(); i++)
	{
		XMLElement *sub = doc->NewElement("SubMatch");
		XMLText *text = doc->NewText(t.c.matchs[i].c_str());
		sub->InsertFirstChild(text);
		matchs->InsertEndChild(sub);
	}

	{
		XMLNode * times = element->InsertEndChild(doc->NewElement("times"));
		CString tmp;
		tmp.Format("%d", 1/*t.times*/); //这里刻意不处理次数
		XMLText *text = doc->NewText(tmp.GetBuffer(0));
		times->InsertEndChild(text);
	}

	{
		XMLNode * Address = element->InsertEndChild(doc->NewElement("Address"));
		//CString tmp;
		//tmp.Format("%d", 10);
		//XMLText *text = doc->NewText(tmp.GetBuffer(0));
		//Address->InsertEndChild(text);
	}

	{
		XMLNode * Price = element->InsertEndChild(doc->NewElement("Price"));
		//CString tmp;
		//tmp.Format("%d", 10);
		//XMLText *text = doc->NewText(tmp.GetBuffer(0));
		//Price->InsertEndChild(text);
	}

	{
		XMLNode * Postfee = element->InsertEndChild(doc->NewElement("Postfee"));
		//CString tmp;
		//tmp.Format("%d", 10);
		//XMLText *text = doc->NewText(tmp.GetBuffer(0));
		//Postfee->InsertEndChild(text);
	}

	{
		XMLNode * Goon = element->InsertEndChild(doc->NewElement("Goon"));
		CString tmp;
		tmp.Format("%s", "TRUE");
		XMLText *text = doc->NewText(tmp.GetBuffer(0));
		Goon->InsertEndChild(text);
	}

	//xml转换为UTF8格式进行存储
	XMLPrinter printer;
	doc->Accept(&printer);

	std::string param_string = printer.CStr();
	std::wstring param_wstring;
	string2wstring(param_string, param_wstring);
	std::string param_utf8;
	wstring2utf8string(param_wstring,param_utf8);

	CFile theFile; 
	theFile.Open(_T("./work.xml"),CFile::modeCreate|CFile::modeWrite); 
	theFile.Write((LPCSTR)param_utf8.c_str(),param_utf8.length()); 
	theFile.Close(); 

    delete doc;

	return true;
}
