// HistoryFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Stock.h"
#include "HistoryFrame.h"
#include "MainFrm.h"
#include <afxcmn.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CStockApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CHistoryFrame

IMPLEMENT_DYNCREATE(CHistoryFrame, CMDIChildWnd)

CHistoryFrame::CHistoryFrame():m_nFrameHeight(500),m_nFrameWidth(1000)
{
}

CHistoryFrame::~CHistoryFrame()
{
}


BEGIN_MESSAGE_MAP(CHistoryFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CHistoryFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryFrame message handlers

BOOL CHistoryFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* pMainFrame = (CMainFrame*)theApp.GetMainWnd();
	CString strName;
	(pMainFrame->m_pEditName)->GetWindowText(strName);
	CString strNo;
	(pMainFrame->m_pEditNo)->GetWindowText(strNo);
	m_strTitle = strName + "--" + strNo;
	cs.style &= ~FWS_ADDTOTITLE;
	cs.lpszName = m_strTitle;
	cs.style &= ~FWS_SNAPTOBARS;
	cs.cx = m_nFrameWidth;
	cs.cy = m_nFrameHeight;
	return CMDIChildWnd::PreCreateWindow(cs);

}


int CHistoryFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	m_wndDlgBar.Create(this,IDD_SLIDER,CBRS_BOTTOM,IDR_SLIDERCTRL);
	m_pSliderCtrl = (CSliderCtrl*)m_wndDlgBar.GetDlgItem(IDC_SLIDERCTRL);
	m_pSliderCtrl->SetRange(0,50);
	m_pSliderCtrl->SetLineSize(1);
	m_pSliderCtrl->SetPageSize(5);
	m_pSliderCtrl->SetPos(50);

	return 0;
}


void CHistoryFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if( IsWindow(m_wndDlgBar.m_hWnd) )
	{
		CRect rect;
		GetClientRect(&rect);
		m_pSliderCtrl = (CSliderCtrl*)m_wndDlgBar.GetDlgItem(IDC_SLIDERCTRL);
		m_pSliderCtrl->SetWindowPos(this,0,0,rect.Width(),50,SWP_NOZORDER);
	}
}

void CHistoryFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CMDIChildWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

int CHistoryFrame::GetSliderCtrlPos()
{
	m_pSliderCtrl = (CSliderCtrl*)m_wndDlgBar.GetDlgItem(IDC_SLIDERCTRL);
	return m_pSliderCtrl->GetPos();
}


