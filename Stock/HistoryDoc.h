#if !defined(AFX_HISTORYDOC_H__EC3CB43F_0DF1_49B4_BB54_70CACFF75D92__INCLUDED_)
#define AFX_HISTORYDOC_H__EC3CB43F_0DF1_49B4_BB54_70CACFF75D92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistoryDoc.h : header file
//
#include <afxtempl.h>
#include "HistoryRecord.h"
/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc document

class CHistoryDoc : public CDocument
{
public:
	CHistoryDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHistoryDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadData(CString strStockNo);
	virtual ~CHistoryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistoryDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void GetPriceRange(int nSel,int nCount);
	double m_dbHiPrice;//��ʷ��߼�
	double m_dbLowPrice;//��ʷ��ͼ�
	int m_nHiQuantity;//��ʷ���ɽ���
	CArray<CHistoryRecord*,CHistoryRecord*> m_arrayHistoryInfo;	//������ʷ����
	CArray<double,double> m_arrayHistoryPriceOfFiveDay;			//����ÿ�����վ���

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYDOC_H__EC3CB43F_0DF1_49B4_BB54_70CACFF75D92__INCLUDED_)
