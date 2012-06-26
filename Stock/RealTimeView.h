#if !defined(AFX_REALTIMEVIEW_H__70C8753F_6215_4475_A4FC_ABA2D6D12FD2__INCLUDED_)
#define AFX_REALTIMEVIEW_H__70C8753F_6215_4475_A4FC_ABA2D6D12FD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealTimeView.h : header file
//
#include <afxtempl.h>
#include <string>
using namespace std;
#include ".\\ThostTraderApi\\ThostFtdcUserApiStruct.h"
/////////////////////////////////////////////////////////////////////////////
// CRealTimeView view
#define NOSELECTION -1
class CRealTimeView : public CView
{
protected:
	CRealTimeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRealTimeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRealTimeView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRealTimeView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:	
	const int m_nStartHour;//开盘时间(小时点)
	const int m_nStartMinute;//开盘时间(分钟点)
	const CString m_strStartTime;//开盘时间
	const CString m_strEndTime;//收盘时间
	int m_nPreSel;//先前选中项
	int m_nCurSel;//当前选中项	
	CArray<int,int> m_arrayPointX;//保存股票查询点	
	const int m_nStockNumPerPage;//股票查询点总数	
	double m_dbYPriceUnit;//价格区单位价格高度值
	double m_dbYWinUnit;
	double m_dbYQuantityUnit;//成交量区单位量高度值
	double m_dbXStep;//	X轴查询点间隔
	const int m_nPenWidth;//绘图线宽	
	const int m_nWindowHeight;//窗口高度
	const int m_nWindowWidth;//窗口宽度
	CRect m_rectClient;//View矩形
	CRect m_rectFrame;//框架矩形
	CRect m_rectTop;//标题栏矩形
	CRect m_rectMid;//交易价格区矩形
	CRect m_rectBottom;//成交量区矩形
	CRect m_rectRight;//数据显示区矩形
	int m_nTimer;
private:
	int TimeToInt(string time, int millisec);
	void DrawDenote(CDC* pDC,CPoint point);//绘制指示线
	void DrawLineOfDealPrice(CDC* pDC);//绘制交易价格曲线
	void DrawLineOfWin(CDC* pDC);
	void SetVariable();//设置绘图相关变量
	void DrawQuantity(CDC* pDC);//绘制成交量曲线
	void DrawDate(CDC* pDC);//绘制数据区
	void DrawTitle(CDC* pDC);//绘制标题栏
	void DrawFrameText(CDC* pDC);//绘制框架
	int  findSel(int sel);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEVIEW_H__70C8753F_6215_4475_A4FC_ABA2D6D12FD2__INCLUDED_)
