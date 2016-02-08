#include "stdafx.h"
#include "stringTransform.h"

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
