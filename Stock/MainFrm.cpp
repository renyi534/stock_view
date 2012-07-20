// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "stock.h"
#include "stdlib.h"

#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SelectionDlg.h"
extern CStockApp theApp;

extern char *ppInstrumentID[30];			// ���鶩���б�
extern int iInstrumentID;									// ���鶩������
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL, OnItemchangedListctrl)
	ON_EN_UPDATE(IDC_EDITNO, OnUpdateEditno)
	ON_BN_CLICKED(IDC_BUTTONHISTORY, OnButtonhistory)
	ON_BN_CLICKED(IDC_BUTTONREALTIME, OnButtonrealtime)
	ON_BN_CLICKED(IDC_IS_DYNAMIC, OnButtonCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_nIndex = -1;
	m_isDynamic = false;
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//����DialogBar
	int nRezult = m_wndDlgBar.Create(this,IDD_SELECTION,CBRS_LEFT,IDD_DLGBAR);
	if(!nRezult)
		return -1;

	//��ÿؼ�ָ��
	GetControlls();

	//����ListCtrl	
	m_pListCtrl->SetExtendedStyle(1 | 32);
	m_pListCtrl->InsertColumn(0,"����",LVCFMT_CENTER,65);
	m_pListCtrl->InsertColumn(1,"���",LVCFMT_CENTER,65);
	//����EditNo	
	m_pEditNo->SetLimitText(6);

	//����Button	
	//pButtonHistory->EnableWindow(false);
	//pButtonRealTime->EnableWindow(false);
	//::SetWindowLong(pButtonHistory->m_hWnd,GWL_STYLE,WS_DISABLED);

	//��Ʊ��������
	char szStockCode[][7] = 
	{
		"IF1204", "IF1205", "IF1206", "IF1207", "IF1208"
	};

	//��Ʊ��������
	char szStockName[][9] = 
	{
		"4�º�Լ", "5�º�Լ","6�º�Լ", "7�º�Լ", "8�º�Լ"
	};

	for(int nI = 0;nI < iInstrumentID;nI++)
	{
		char tmp_buf[5];
		sprintf(tmp_buf, " %d", nI);
		m_pListCtrl->InsertItem(nI, "New");
		m_pListCtrl->SetItemText(nI, 0,ppInstrumentID[nI]);
		m_pListCtrl->SetItemText(nI, 1, tmp_buf);
	}	
	
	return 0;
}


void CMainFrame::OnItemchangedListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	GetControlls();
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	m_nIndex = m_pListCtrl->GetNextSelectedItem(pos);

	CString strNo = m_pListCtrl->GetItemText(m_nIndex,0);
	CString strName = m_pListCtrl->GetItemText(m_nIndex,1);	
	m_pEditNo->SetWindowText(strNo);
	m_pEditName->SetWindowText(strName);
	
	*pResult = 0;
}

void CMainFrame::OnUpdateEditno() 
{
	// TODO: Add your control notification handler code here
	//��ÿؼ�ָ��
/*	GetControlls();

	CString strNo;
	CString strName;
	m_pEditNo->GetWindowText(strNo);
	if(strNo.IsEmpty())
	{
		m_nIndex = -1;
		strName = "";
		m_pEditName->SetWindowText(strName);
		return;
	}

	//����ListCtrl�ؼ���ƥ����
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL; //| LVFI_STRING;
	info.psz = strNo;
	m_nIndex = m_pListCtrl->FindItem(&info,-1);
	if(m_nIndex != -1)
	{
		//ѡ��ƥ����
		//int nI = pListCtrl->SetSelectionMark(nIndex);		
		//����EditName�ؼ�����		
		strName = m_pListCtrl->GetItemText(m_nIndex,1);
		m_pEditName->SetWindowText(strName);
	}	*/
}

void CMainFrame::OnButtonhistory() 
{
	//TODO: Add your control notification handler code here
	GetControlls();
	CString strName = m_pListCtrl->GetItemText(m_nIndex,1);
	if( strName.IsEmpty() )
	{
		MessageBox("��ѡ��һֻ��Ʊ",NULL,MB_OK);
		return;
	}
	CHistoryDoc* pHistoryDoc = (CHistoryDoc*)theApp.CreateDocument("History");	
	pHistoryDoc->LoadData( m_pListCtrl->GetItemText(m_nIndex,0) );
}

void CMainFrame::OnButtonrealtime() 
{
	// TODO: Add your control notification handler code here
	GetControlls();
	CString strName = m_pListCtrl->GetItemText(m_nIndex,1);
	CTime date;
	this->m_pDate->GetTime(date);
    CString dateStr = date.Format("%Y%m%d");
	if( strName.IsEmpty() )
	{
		MessageBox("��ѡ��һֻ��Ʊ",NULL,MB_OK);
		return;
	}
	CString code = m_pListCtrl->GetItemText(m_nIndex,0);
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)theApp.CreateDocument("RealTime");	

	pRealTimeDoc->LoadData( code, dateStr, m_isDynamic );
	
}

void CMainFrame::OnButtonCheck() 
{
	m_isDynamic = !m_isDynamic;
	//m_pUpdateDynamic->SetCheck(m_isDynamic);
}

void CMainFrame::GetControlls()
{
	//��ÿؼ�ָ��
	m_pListCtrl = (CListCtrl*)m_wndDlgBar.GetDlgItem(IDC_LISTCTRL);
	m_pEditNo = (CEdit*)m_wndDlgBar.GetDlgItem(IDC_EDITNO);
	m_pEditName = (CEdit*)m_wndDlgBar.GetDlgItem(IDC_EDITNAME);
	m_pButtonHistory = (CButton*)m_wndDlgBar.GetDlgItem(IDC_BUTTONHISTORY);
	m_pButtonRealTime = (CButton*)m_wndDlgBar.GetDlgItem(IDC_BUTTONREALTIME);
	m_pDate = (CDateTimeCtrl*)m_wndDlgBar.GetDlgItem(IDC_DATE_PICKER);
	m_pUpdateDynamic = (CButton*)m_wndDlgBar.GetDlgItem(IDC_IS_DYNAMIC);
}


