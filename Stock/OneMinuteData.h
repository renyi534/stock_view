// OneMinuteData.h: interface for the COneMinuteData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONEMINUTEDATA_H__E94EB5C6_5DC6_4F4A_84DA_CE509C87668D__INCLUDED_)
#define AFX_ONEMINUTEDATA_H__E94EB5C6_5DC6_4F4A_84DA_CE509C87668D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class COneMinuteData  
{
public:
	string m_Day;
	string m_Time;
	string m_InstrumentID;
	double m_OpenPrice;
	double m_ClosePrice;
	double m_HighPrice;
	double m_LowPrice;
	double m_Volume;
	double m_OpenInterest;
	COneMinuteData();
	virtual ~COneMinuteData();

};

#endif // !defined(AFX_ONEMINUTEDATA_H__E94EB5C6_5DC6_4F4A_84DA_CE509C87668D__INCLUDED_)
