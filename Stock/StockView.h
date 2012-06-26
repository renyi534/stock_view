// StockView.h : interface of the CStockView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOCKVIEW_H__444F1785_4E78_4648_B049_BFB79634D861__INCLUDED_)
#define AFX_STOCKVIEW_H__444F1785_4E78_4648_B049_BFB79634D861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StockDoc.h"

class CStockView : public CView
{
protected: // create from serialization only
	CStockView();
	DECLARE_DYNCREATE(CStockView)

// Attributes
public:
	CStockDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStockView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StockView.cpp
inline CStockDoc* CStockView::GetDocument()
   { return (CStockDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKVIEW_H__444F1785_4E78_4648_B049_BFB79634D861__INCLUDED_)
