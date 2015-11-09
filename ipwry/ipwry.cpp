#include "ipwry.h"

#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <algorithm>
#include <WinSock2.h>

#include "items.h"


extern IpItem items[];
extern int itemslen;

bool compare_item ( const IpItem &lhs,const IpItem &rhs)
{
	return lhs.toip<=rhs.toip;
}

const char *ipwry_search_hostbyte(unsigned long ip)
{
	//¶þ·Ö²éÕÒ
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