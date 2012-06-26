// SelectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Stock.h"
#include "SelectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectionDlg dialog


CSelectionDlg::CSelectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectionDlg)
	m_strNameEdit = _T("");
	m_strNoEdit = _T("");
	//}}AFX_DATA_INIT
}


void CSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectionDlg)
	DDX_Control(pDX, IDC_BUTTONREALTIME, m_wndRealTimeButton);
	DDX_Control(pDX, IDC_BUTTONHISTORY, m_wndHistoryButton);
	DDX_Control(pDX, IDC_LISTCTRL, m_wndListCtrl);
	DDX_Text(pDX, IDC_EDITNAME, m_strNameEdit);
	DDX_Text(pDX, IDC_EDITNO, m_strNoEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectionDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectionDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectionDlg message handlers





BOOL CSelectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
