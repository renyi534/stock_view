// StockDoc.cpp : implementation of the CStockDoc class
//

#include "stdafx.h"
#include "Stock.h"

#include "StockDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockDoc

IMPLEMENT_DYNCREATE(CStockDoc, CDocument)

BEGIN_MESSAGE_MAP(CStockDoc, CDocument)
	//{{AFX_MSG_MAP(CStockDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockDoc construction/destruction

CStockDoc::CStockDoc()
{
	// TODO: add one-time construction code here

}

CStockDoc::~CStockDoc()
{
}

BOOL CStockDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStockDoc serialization

void CStockDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStockDoc diagnostics

#ifdef _DEBUG
void CStockDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStockDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStockDoc commands
