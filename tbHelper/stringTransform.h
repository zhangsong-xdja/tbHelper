#pragma once

#include <string>

void string2wstring(const std::string& _str, std::wstring& _wstr );
std::string& wstring2string(const std::wstring& _wstr, std::string& _str ) ;
void UTF8string2wstring(const std::string& _str, std::wstring& _wstr);
std::string& wstring2utf8string( const std::wstring& _wstr, std::string& _str );
