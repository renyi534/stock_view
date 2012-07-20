// Stock.h : main header file for the STOCK application
//

#if !defined(AFX_STOCK_H__BF95122C_232D_4FBD_8243_656F50C35466__INCLUDED_)
#define AFX_STOCK_H__BF95122C_232D_4FBD_8243_656F50C35466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStockApp:
// See Stock.cpp for the implementation of this class
//

class CStockApp : public CWinApp
{
public:
	void LoadConfig();
	CDocument* CreateDocument(CString strDocTemplateType);
	CStockApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CStockApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMultiDocTemplate* m_pDocTemplateRealTime;
	CMultiDocTemplate* m_pDocTemplateHistory;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCK_H__BF95122C_232D_4FBD_8243_656F50C35466__INCLUDED_)
