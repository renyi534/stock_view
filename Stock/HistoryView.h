#if !defined(AFX_HISTORYVIEW_H__F00F297E_16B9_48D1_9666_D98515DF4F65__INCLUDED_)
#define AFX_HISTORYVIEW_H__F00F297E_16B9_48D1_9666_D98515DF4F65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistoryView.h : header file
//
#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CHistoryView view
#define NOSELECTION -1
class CHistoryView : public CView
{
public:
	CHistoryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHistoryView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHistoryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistoryView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCustomdrawSliderctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawFrameText(CDC* pDC);			//绘制框架
	void DrawQuantity(CDC* pDC);			//绘制成交量柱状图
	void DrawLineOfAverageFiveDay(CDC* pDC);//绘制五日均线图
	void DrawLineOfK(CDC* pDC);				//绘制K线图
	void SetVariable();	//设置绘图相关成员变量
	void DarwDenote(CDC* pDC,CPoint point);	//绘制股票查询点指示线
	void DrawTitle(CDC* pDC);
private:
	const int m_nWindowHeight;//窗口高度
	const int m_nWindowWidth;//窗口宽度
	int m_nPreSel;//上次选中的股票查询点(起始位置为1)
	int m_nCurSel;//当前选中的股票查询点(起始位置为1)
	CArray<CRect,CRect> m_ArrayRect;	//保存股票每日曲线对应的矩形区域
	const int m_nStockNumPerPage;		//每页显示股票的天数
	double m_dbYPriceUnit;				//股票价格(每元)对应的逻辑单位高度
	double m_dbYQuantityUnit;			//股票交易量对应的逻辑单位高度
	double m_dbXStep;						//股票曲线显示间隔
	int m_nPenWidth;					//绘图画笔宽度
	CRect m_rectClient;					//视图大小
	//矩形框
	CRect m_rectBottom;					//交易量矩形框
	CRect m_rectMid;					//K线图矩形框
	CRect m_rectTop;					//标题栏矩形框
	CRect m_rectFrame;					//框架矩形框
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYVIEW_H__F00F297E_16B9_48D1_9666_D98515DF4F65__INCLUDED_)
