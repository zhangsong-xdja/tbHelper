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
	tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();

    // use the standard declaration by default
    XMLDeclaration *declaration = doc->NewDeclaration();
    doc->InsertFirstChild(declaration);

    // insert 'element' node
    XMLNode *element = doc->InsertEndChild(doc->NewElement("element"));

	XMLNode * conditions = element->InsertEndChild(doc->NewElement("conditions"));
	for(int i = 0; i < 3; i++)
	{
		XMLElement *sub = doc->NewElement("subcondition");
		XMLText *text = doc->NewText("²âÊÔÓÃ Æ¥Åä¹Ø¼ü×Ö");
		sub->InsertFirstChild(text);
		conditions->InsertEndChild(sub);
	}

	XMLNode * matchs = element->InsertEndChild(doc->NewElement("matchs"));
	for(int i = 0; i < 3; i++)
	{
		XMLElement *sub = doc->NewElement("submatch");
		XMLText *text = doc->NewText("²âÊÔÓÃ ËÑË÷¹Ø¼ü×Ö");
		sub->InsertFirstChild(text);
		matchs->InsertEndChild(sub);
	}

	XMLElement *random = doc->NewElement("random");
	random->SetAttribute("value", 1);
	element->InsertEndChild(random);

	XMLElement *times = doc->NewElement("times");
	times->SetAttribute("value", 2);
	element->InsertEndChild(times);

	XMLElement *times_1 = doc->NewElement("times_1");
	times_1->SetAttribute("value", 2);
	element->InsertEndChild(times_1);

	XMLElement *times_2 = doc->NewElement("times_2");
	times_2->SetAttribute("value", 2);
	element->InsertEndChild(times_2);

	XMLElement *times_3 = doc->NewElement("times_3");
	times_3->SetAttribute("value", 2);
	element->InsertEndChild(times_3);


	/*
    for (int i = 0; i < 7; ++i) {
        XMLElement *sub = doc->NewElement(des[i]);
        //sub->SetAttribute("attr", i+1);
        element->InsertEndChild(sub);
        subs[i] = sub;
    }*/

    // insert text to 3rd 'sub' node
 //   XMLText *text = doc->NewText("& Text!");
    // text->SetCData(true);  // <![CDATA[& Text!]]>
 //   subs[2]->InsertFirstChild(text);


    // save xml, true for compact
    //XMLError error = doc->SaveFile("./work.xml", true);

	XMLPrinter printer;
	doc->Accept(&printer);

	std::string param_string = printer.CStr();
	std::wstring param_wstring;
	string2wstring(param_string, param_wstring);
	std::string param_utf8;
	wstring2utf8string(param_wstring,param_utf8);

	CFile theFile; 
	theFile.Open(_T("./work.xml"),CFile::modeCreate|CFile::modeWrite); 
	//theFile.Write(&UTF8BOM,3); 
	theFile.Write((LPCSTR)param_utf8.c_str(),param_utf8.length()); 
	theFile.Close(); 



    delete doc;

	return false;
}
