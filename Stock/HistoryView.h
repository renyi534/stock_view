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
	void DrawFrameText(CDC* pDC);			//���ƿ��
	void DrawQuantity(CDC* pDC);			//���Ƴɽ�����״ͼ
	void DrawLineOfAverageFiveDay(CDC* pDC);//�������վ���ͼ
	void DrawLineOfK(CDC* pDC);				//����K��ͼ
	void SetVariable();	//���û�ͼ��س�Ա����
	void DarwDenote(CDC* pDC,CPoint point);	//���ƹ�Ʊ��ѯ��ָʾ��
	void DrawTitle(CDC* pDC);
private:
	const int m_nWindowHeight;//���ڸ߶�
	const int m_nWindowWidth;//���ڿ��
	int m_nPreSel;//�ϴ�ѡ�еĹ�Ʊ��ѯ��(��ʼλ��Ϊ1)
	int m_nCurSel;//��ǰѡ�еĹ�Ʊ��ѯ��(��ʼλ��Ϊ1)
	CArray<CRect,CRect> m_ArrayRect;	//�����Ʊÿ�����߶�Ӧ�ľ�������
	const int m_nStockNumPerPage;		//ÿҳ��ʾ��Ʊ������
	double m_dbYPriceUnit;				//��Ʊ�۸�(ÿԪ)��Ӧ���߼���λ�߶�
	double m_dbYQuantityUnit;			//��Ʊ��������Ӧ���߼���λ�߶�
	double m_dbXStep;						//��Ʊ������ʾ���
	int m_nPenWidth;					//��ͼ���ʿ��
	CRect m_rectClient;					//��ͼ��С
	//���ο�
	CRect m_rectBottom;					//���������ο�
	CRect m_rectMid;					//K��ͼ���ο�
	CRect m_rectTop;					//���������ο�
	CRect m_rectFrame;					//��ܾ��ο�
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYVIEW_H__F00F297E_16B9_48D1_9666_D98515DF4F65__INCLUDED_)
