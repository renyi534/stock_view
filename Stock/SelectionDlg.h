#if !defined(AFX_SELECTIONDLG_H__5D154E17_43B2_4417_9877_342647E4EF0D__INCLUDED_)
#define AFX_SELECTIONDLG_H__5D154E17_43B2_4417_9877_342647E4EF0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectionDlg dialog

class CSelectionDlg : public CDialog
{
// Construction
public:
	CSelectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectionDlg)
	enum { IDD = IDD_SELECTION };
	CButton	m_wndRealTimeButton;
	CButton	m_wndHistoryButton;
	CListCtrl	m_wndListCtrl;
	CString	m_strNameEdit;
	CString	m_strNoEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectionDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIONDLG_H__5D154E17_43B2_4417_9877_342647E4EF0D__INCLUDED_)
