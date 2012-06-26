#if !defined(AFX_REALTIMEDOC_H__B91803C2_316B_4784_BD9C_B6F87E1B3A1C__INCLUDED_)
#define AFX_REALTIMEDOC_H__B91803C2_316B_4784_BD9C_B6F87E1B3A1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealTimeDoc.h : header file
//
#include "RealTimeRecord.h"
#include "DbConn.h"
#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CRealTimeDoc document

class CRealTimeDoc : public CDocument
{
protected:
	CRealTimeDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRealTimeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	vector<CThostFtdcDepthMarketDataField> m_RealTimeInfo;//保存股票实时信息
	vector<OrderInfo>	m_OrderInfo;
	vector<double> m_PointWin;
	void LoadData(CString strNo, CString, bool is_dynamic=false);//加载实时数据
	void LoadData();
	virtual ~CRealTimeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRealTimeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	double m_dbClosePrice;
	void GetPriceRange();
	CString m_strNo;
	CString m_Day;
	bool    m_isDynamic;
public:
	
	double m_nHiQuantity;
	double m_dbLowPrice;
	double m_dbHiPrice;
	double m_HiWin;
	double m_LowWin;
	friend class CRealTimeView;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEDOC_H__B91803C2_316B_4784_BD9C_B6F87E1B3A1C__INCLUDED_)
