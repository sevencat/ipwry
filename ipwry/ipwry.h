#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

extern "C"
{
//IPWRY_API __declspec(dllexport)
	__declspec(dllexport) const char *ipwry_search2(const char *ip);
	__declspec(dllexport) const char *ipwry_search(unsigned long ip);
	__declspec(dllexport) const char *ipwry_search_hostbyte(unsigned long ip);
};