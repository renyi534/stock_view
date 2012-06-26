// RealTimeRecord.h: interface for the CRealTimeRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REALTIMERECORD_H__28F39250_1B65_495C_8160_405F7F858EAA__INCLUDED_)
#define AFX_REALTIMERECORD_H__28F39250_1B65_495C_8160_405F7F858EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;
struct OrderInfo 
{
	string m_instrumentID;//¹ÉÆ±´úÂë
	int	   amount;
	int    is_buy;
	int    is_open;
	double price;
	string day;
	string time;
	int	   milliSec;
};

#endif // !defined(AFX_REALTIMERECORD_H__28F39250_1B65_495C_8160_405F7F858EAA__INCLUDED_)
