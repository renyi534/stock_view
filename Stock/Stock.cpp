// Stock.cpp : Defines the class behaviors for the application.
//

#include "StdAfx.h"
#include "Stock.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "StockDoc.h"
#include "StockView.h"
#include "HistoryDoc.h"
#include "HistoryFrame.h"
#include "HistoryView.h"
#include "RealTimeDoc.h"
#include "RealTimeFrame.h"
#include "RealTimeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockApp

BEGIN_MESSAGE_MAP(CStockApp, CWinApp)
	//{{AFX_MSG_MAP(CStockApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockApp construction

CStockApp::CStockApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStockApp object

CStockApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStockApp initialization

BOOL CStockApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	m_pDocTemplateHistory = new CMultiDocTemplate(
		IDR_STOCKTYPE,
		RUNTIME_CLASS(CStockDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CStockView));
	AddDocTemplate(m_pDocTemplateHistory);

	/*------------------------------------------------------------*/
	m_pDocTemplateHistory = new CMultiDocTemplate( IDR_HISTORY, 
											RUNTIME_CLASS(CHistoryDoc),
											RUNTIME_CLASS(CHistoryFrame), // custom MDI child frame
											RUNTIME_CLASS(CHistoryView));
	AddDocTemplate(m_pDocTemplateHistory);

	m_pDocTemplateRealTime = new CMultiDocTemplate( IDR_REALTIME,
											RUNTIME_CLASS(CRealTimeDoc),
											RUNTIME_CLASS(CRealTimeFrame),
											RUNTIME_CLASS(CRealTimeView));
	AddDocTemplate(m_pDocTemplateRealTime);

	/*------------------------------------------------------------*/

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CStockApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CStockApp message handlers


CDocument* CStockApp::CreateDocument(CString strDocTemplateType)
{
	CDocTemplate* pDocTemplate;
	POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
	while(pos != NULL)
	{
		CDocTemplate* pDocTemplate1 = m_pDocManager->GetNextDocTemplate(pos);
		CString strType;
		pDocTemplate1->GetDocString(strType,CDocTemplate::fileNewName);
		if(strType == strDocTemplateType)
		{
			pDocTemplate = pDocTemplate1;
			break;
		}
	}
	return  pDocTemplate->OpenDocumentFile(NULL);
	// 在 CMultiDocTemplate::OpenDocumentFile 作了3件事:
	/* 
	   1) 创建一个文档 new Docuemnt;
	   2) 创建本文档的一个子框架   new CMDIChildWnd ==> 创建其视 new View
	   3) 将新建的Document对象放入到 本文档模板中
	   4) 将视图-子框架 窗口 初始化显示
	  
	*/	
}
