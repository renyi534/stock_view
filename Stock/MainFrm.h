// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B196BC71_2EBF_4675_8206_FCA843FEE555__INCLUDED_)
#define AFX_MAINFRM_H__B196BC71_2EBF_4675_8206_FCA843FEE555__INCLUDED_

#include "ChildFrm.h"	// Added by ClassView
#include "StockView.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SelectionDlg.h"
#include "HistoryDoc.h"
#include "HistoryFrame.h"
#include "HistoryView.h"
#include "RealTimeDoc.h"
#include "RealTimeFrame.h"
#include "RealTimeView.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetControlls();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemchangedListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditno();
	afx_msg void OnButtonhistory();
	afx_msg void OnButtonrealtime();
	afx_msg void OnButtonCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton* m_pButtonRealTime;	//ʵʱ���װ�ť
	CButton* m_pButtonHistory;	//��ʷ���װ�ť
	CEdit* m_pEditName;			//��Ʊ������ʾ�༭�ؼ�
	CEdit* m_pEditNo;			//��Ʊ������ʾ�༭�ؼ�
	CListCtrl* m_pListCtrl;		//�б��ؼ�
	int m_nIndex;				//��ǰ�б��ѡ��������
	CDialogBar m_wndDlgBar;		//�Ի������
	CDateTimeCtrl* m_pDate;
	CButton* m_pUpdateDynamic;
	bool m_isDynamic;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B196BC71_2EBF_4675_8206_FCA843FEE555__INCLUDED_)
