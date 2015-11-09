#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>

#include "items.h"


extern IpItem items[];
extern int itemslen;

bool compare_item ( const IpItem &lhs,const IpItem &rhs)
{
	return lhs.toip<=rhs.toip;
}

//IpItem *lbfind(IpItem *first, IpItem *last, unsigned long ipaddr)
//{
//	IpItem *it;
//	int count = std::distance(first,last);
//	int step=0;
//	while (count > 0)
//	{
//		it = first;
//		step = count / 2;
//		std::advance(it, step);
//
//		//如果这个地方还是小于当前地址，就从当前地址开始向后推
//		if (it->toip<ipaddr)
//		{
//			first = ++it;
//			count -= step + 1;
//		}
//		else
//		{
//			//只需要查找当前的这一半
//			count = step;
//		}
//	}
//	return first;
//}

extern "C"
{
	const char *ipwry_search_hostbyte(unsigned long ip)
	{
		//二分查找
		IpItem item={ip,ip,""};
		IpItem* Result=std::lower_bound(items, items+itemslen-1,item,compare_item); 
		if(Result==items+itemslen)
			return "";
		return Result->addr;
	}

	const char *ipwry_search(unsigned long ip)
	{
		unsigned long ip2=_byteswap_ulong(ip);
		return ipwry_search_hostbyte(ip2);
	}

	const char *ipwry_search2(const char *ip)
	{
		unsigned long value=inet_addr(ip);
		return ipwry_search(value);
	}
}


int main(int argc,char *argv[])
{
	//WSADATA wd;
	//WSAStartup(MAKEWORD(2,2),&wd);
	const char *addr=ipwry_search2("211.167.97.67");
	return 0;
}


#pragma comment(lib,"ws2_32")