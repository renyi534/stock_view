// StockDoc.h : interface of the CStockDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOCKDOC_H__C9B13075_031C_41AB_BA52_C7128E4A4659__INCLUDED_)
#define AFX_STOCKDOC_H__C9B13075_031C_41AB_BA52_C7128E4A4659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStockDoc : public CDocument
{
protected: // create from serialization only
	CStockDoc();
	DECLARE_DYNCREATE(CStockDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStockDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStockDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKDOC_H__C9B13075_031C_41AB_BA52_C7128E4A4659__INCLUDED_)
