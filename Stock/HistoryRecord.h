// HistoryRecord.h: interface for the CHistoryRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYRECORD_H__AD4D5C03_1BD9_42C8_B608_36B0B433F6B2__INCLUDED_)
#define AFX_HISTORYRECORD_H__AD4D5C03_1BD9_42C8_B608_36B0B433F6B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHistoryRecord : public CObject  
{
public:
	CHistoryRecord();
	virtual ~CHistoryRecord();

	public:
	char m_cDealDate[100];		//交易日期
	int m_nQuantity;			//成交量
	double m_dbLowPrice;		//最低价
	double m_dbHiPrice;			//最高价
	double m_dbOpenPrice;		//开盘价
	double m_dbClosePrice;		//收盘价
	char m_cStockName[100];		//股票名称
	char m_cStockNo[100];		//股票代码
};
	

#endif // !defined(AFX_HISTORYRECORD_H__AD4D5C03_1BD9_42C8_B608_36B0B433F6B2__INCLUDED_)
