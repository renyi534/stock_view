// StockView.cpp : implementation of the CStockView class
//

#include "stdafx.h"
#include "Stock.h"

#include "StockDoc.h"
#include "StockView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockView

IMPLEMENT_DYNCREATE(CStockView, CView)

BEGIN_MESSAGE_MAP(CStockView, CView)
	//{{AFX_MSG_MAP(CStockView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockView construction/destruction

CStockView::CStockView()
{
	// TODO: add construction code here

}

CStockView::~CStockView()
{
}

BOOL CStockView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStockView drawing

void CStockView::OnDraw(CDC* pDC)
{
	CStockDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CStockView diagnostics

#ifdef _DEBUG
void CStockView::AssertValid() const
{
	CView::AssertValid();
}

void CStockView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStockDoc* CStockView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStockDoc)));
	return (CStockDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStockView message handlers
