// RealTimeFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Stock.h"
#include "RealTimeFrame.h"
#include "MainFrm.h"
extern CStockApp theApp;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRealTimeFrame

IMPLEMENT_DYNCREATE(CRealTimeFrame, CMDIChildWnd)

CRealTimeFrame::CRealTimeFrame():m_nFrameHeight(500),m_nFrameWidth(1000)
{
}

CRealTimeFrame::~CRealTimeFrame()
{
}


BEGIN_MESSAGE_MAP(CRealTimeFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRealTimeFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeFrame message handlers

BOOL CRealTimeFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* pMainFrame = (CMainFrame*)theApp.GetMainWnd();
	CString strName;
	(pMainFrame->m_pEditName)->GetWindowText(strName);
	CString strNo;
	(pMainFrame->m_pEditNo)->GetWindowText(strNo);
	m_strTitle =  strName + "--" + strNo;
	cs.style &= ~FWS_ADDTOTITLE;
	cs.lpszName = m_strTitle;
	cs.style &= ~FWS_SNAPTOBARS;
	cs.cx = m_nFrameWidth;
	cs.cy = m_nFrameHeight;
	return CMDIChildWnd::PreCreateWindow(cs);
}
