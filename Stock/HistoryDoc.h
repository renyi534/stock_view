#if !defined(AFX_HISTORYDOC_H__EC3CB43F_0DF1_49B4_BB54_70CACFF75D92__INCLUDED_)
#define AFX_HISTORYDOC_H__EC3CB43F_0DF1_49B4_BB54_70CACFF75D92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistoryDoc.h : header file
//
#include <afxtempl.h>
#include "HistoryRecord.h"
/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc document

class CHistoryDoc : public CDocument
{
public:
	CHistoryDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHistoryDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadData(CString strStockNo);
	virtual ~CHistoryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistoryDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void GetPriceRange(int nSel,int nCount);
	double m_dbHiPrice;//历史最高价
	double m_dbLowPrice;//历史最低价
	int m_nHiQuantity;//历史最大成交量
	CArray<CHistoryRecord*,CHistoryRecord*> m_arrayHistoryInfo;	//保存历史数据
	CArray<double,double> m_arrayHistoryPriceOfFiveDay;			//保存每个五日均价

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYDOC_H__EC3CB43F_0DF1_49B4_BB54_70CACFF75D92__INCLUDED_)
