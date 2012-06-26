#if !defined(AFX_HISTORYFRAME_H__DC764DFE_ABF3_423D_B3AD_C99C0F669040__INCLUDED_)
#define AFX_HISTORYFRAME_H__DC764DFE_ABF3_423D_B3AD_C99C0F669040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistoryFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistoryFrame frame

class CHistoryFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CHistoryFrame)
public:
	CHistoryFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHistoryFrame();

	// Generated message map functions
	//{{AFX_MSG(CHistoryFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int GetSliderCtrlPos();
	CSliderCtrl* m_pSliderCtrl;		//CSliderCtrl控件
	CDialogBar m_wndDlgBar;			//对话框对象
	//CString m_strTitle;//
private:
	CString m_strTitle;//窗口标题
	const int m_nFrameHeight;//框架高度
	const int m_nFrameWidth;//框架宽度
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYFRAME_H__DC764DFE_ABF3_423D_B3AD_C99C0F669040__INCLUDED_)
