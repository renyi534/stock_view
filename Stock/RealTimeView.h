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
	const int m_nStartHour;//����ʱ��(Сʱ��)
	const int m_nStartMinute;//����ʱ��(���ӵ�)
	const CString m_strStartTime;//����ʱ��
	const CString m_strEndTime;//����ʱ��
	int m_nPreSel;//��ǰѡ����
	int m_nCurSel;//��ǰѡ����	
	CArray<int,int> m_arrayPointX;//�����Ʊ��ѯ��	
	const int m_nStockNumPerPage;//��Ʊ��ѯ������	
	double m_dbYPriceUnit;//�۸�����λ�۸�߶�ֵ
	double m_dbYWinUnit;
	double m_dbYQuantityUnit;//�ɽ�������λ���߶�ֵ
	double m_dbXStep;//	X���ѯ����
	const int m_nPenWidth;//��ͼ�߿�	
	const int m_nWindowHeight;//���ڸ߶�
	const int m_nWindowWidth;//���ڿ��
	CRect m_rectClient;//View����
	CRect m_rectFrame;//��ܾ���
	CRect m_rectTop;//����������
	CRect m_rectMid;//���׼۸�������
	CRect m_rectBottom;//�ɽ���������
	CRect m_rectRight;//������ʾ������
	int m_nTimer;
private:
	int TimeToInt(string time, int millisec);
	void DrawDenote(CDC* pDC,CPoint point);//����ָʾ��
	void DrawLineOfDealPrice(CDC* pDC);//���ƽ��׼۸�����
	void DrawLineOfWin(CDC* pDC);
	void SetVariable();//���û�ͼ��ر���
	void DrawQuantity(CDC* pDC);//���Ƴɽ�������
	void DrawDate(CDC* pDC);//����������
	void DrawTitle(CDC* pDC);//���Ʊ�����
	void DrawFrameText(CDC* pDC);//���ƿ��
	int  findSel(int sel);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEVIEW_H__70C8753F_6215_4475_A4FC_ABA2D6D12FD2__INCLUDED_)
