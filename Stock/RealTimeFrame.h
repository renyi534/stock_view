#if !defined(AFX_REALTIMEFRAME_H__F773981B_6253_44C8_B68C_D55A158A06CC__INCLUDED_)
#define AFX_REALTIMEFRAME_H__F773981B_6253_44C8_B68C_D55A158A06CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealTimeFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRealTimeFrame frame

class CRealTimeFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRealTimeFrame)
protected:
	CRealTimeFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRealTimeFrame();

	// Generated message map functions
	//{{AFX_MSG(CRealTimeFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strTitle;//窗口标题
	const int m_nFrameHeight;//窗口高度
	const int m_nFrameWidth;//窗口宽度
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEFRAME_H__F773981B_6253_44C8_B68C_D55A158A06CC__INCLUDED_)
