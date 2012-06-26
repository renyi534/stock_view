// HistoryView.cpp : implementation file
//

#include "stdafx.h"
#include "Stock.h"
#include "HistoryView.h"
#include "HistoryDoc.h"
#include "HistoryFrame.h"
#include <stdio.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistoryView

IMPLEMENT_DYNCREATE(CHistoryView, CView)

CHistoryView::CHistoryView():m_nPenWidth(2),m_nStockNumPerPage(50),m_nPreSel(NOSELECTION),m_nCurSel(NOSELECTION),
m_nWindowWidth(1000),m_nWindowHeight(500)
{
	
	m_rectClient.right = m_nWindowWidth;
	m_rectClient.left = 0;
	m_rectClient.top = m_nWindowHeight;
	m_rectClient.bottom = 0;

	m_rectFrame = m_rectClient;
	m_rectFrame.left += 5;
	m_rectFrame.right -= 5;
	m_rectFrame.top -= 5;	
	m_rectFrame.bottom += 5;

	m_rectTop.left	= 70;	
	m_rectTop.right	= m_nWindowWidth - 70;
	m_rectTop.top	= m_nWindowHeight - 10;
	m_rectTop.bottom	= m_rectTop.top - 30;

	m_rectMid.left		= 70;	
	m_rectMid.right		= m_nWindowWidth - 70;
	m_rectMid.top		= m_rectTop.bottom - 5;
	m_rectMid.bottom	= m_rectTop.bottom - m_nWindowHeight / 2;	
	
	m_rectBottom.left		= 70;
	m_rectBottom.right		= m_nWindowWidth - 70;
	m_rectBottom.top		= m_rectMid.bottom - 30;	
	m_rectBottom.bottom		= 10;

	
}

CHistoryView::~CHistoryView()
{
}


BEGIN_MESSAGE_MAP(CHistoryView, CView)
	//{{AFX_MSG_MAP(CHistoryView)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERCTRL, OnCustomdrawSliderctrl)
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryView drawing

void CHistoryView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	
	SetVariable();
	DrawFrameText(pDC);
	DrawQuantity(pDC);
	DrawLineOfAverageFiveDay(pDC);
	DrawLineOfK(pDC);	
}

/////////////////////////////////////////////////////////////////////////////
// CHistoryView diagnostics

#ifdef _DEBUG
void CHistoryView::AssertValid() const
{
	CView::AssertValid();
}

void CHistoryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistoryView message handlers

BOOL CHistoryView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	CBrush brush( RGB(0,0,0) );
	pDC->FillRect(&rect,&brush);
	return 1;
}

//绘制框架
void CHistoryView::DrawFrameText(CDC* pDC)
{
	CHistoryDoc* pHistoryDoc = (CHistoryDoc*)GetDocument();	
	//Draw矩形框
	CPen pen( PS_SOLID,m_nPenWidth,RGB(255,0,0) );
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(&m_rectFrame);
	pDC->Rectangle(&m_rectTop);
	pDC->Rectangle(&m_rectMid);
	pDC->Rectangle(&m_rectBottom);
	pDC->SelectObject(&pOldPen);

	DrawTitle(pDC);

	//绘制数据
	COLORREF colorOldText = pDC->SetTextColor( RGB(255, 255, 0) );
	COLORREF colorOldBk = pDC->SetBkColor( RGB(0,0,0) );
	int nSel = (  (CHistoryFrame*)GetParentFrame() )->GetSliderCtrlPos();
	pHistoryDoc->GetPriceRange(nSel,m_nStockNumPerPage);
	CRect rect;
	CString str;
	rect.left	= m_rectMid.left - 100;
	rect.right	= m_rectMid.left - 5;
	rect.top	= m_rectMid.top;
	rect.bottom = rect.top - 100;
	str.Format("%.4lf",pHistoryDoc->m_dbHiPrice);
	pDC->DrawText(str,&rect,DT_SINGLELINE | DT_RIGHT);		//历史最高价

	rect.left	= m_rectMid.left - 100;
	rect.right	= m_rectMid.left - 5;
	rect.top	= m_rectMid.top;
	rect.bottom = m_rectMid.bottom;
	str.Format("%.4lf",pHistoryDoc->m_dbLowPrice);
	pDC->DrawText(str,&rect,DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);		//历史最低价

	rect.left	= m_rectMid.left - 100;
	rect.right	= m_rectMid.left - 5;
	rect.top	= (m_rectMid.top + m_rectMid.bottom) / 2 + 10;
	rect.bottom = rect.top - 100;
	double dbAverPrice = ( pHistoryDoc->m_dbHiPrice 
						 + pHistoryDoc->m_dbLowPrice ) / 2;
	str.Format("%.4lf",dbAverPrice);
	pDC->DrawText(str,&rect,DT_SINGLELINE | DT_RIGHT);		//历史平均价
	CPen pen1(PS_SOLID,m_nPenWidth,RGB(255,255,0));
	CPen* pOldPen1 = pDC->SelectObject(&pen1);
	pDC->MoveTo(m_rectMid.left,rect.top);
	pDC->LineTo(m_rectMid.right,rect.top);
	pDC->SelectObject(pOldPen1);

	rect.left	= m_rectMid.left;
	rect.right	= m_rectMid.right;
	rect.top	= m_rectMid.bottom;
	rect.bottom = m_rectBottom.top;
	str.Format("%s",pHistoryDoc->m_arrayHistoryInfo[nSel]->m_cDealDate);
	pDC->DrawText(str,&rect,DT_SINGLELINE | DT_LEFT);		//交易日期
	str.Format("%s",pHistoryDoc->m_arrayHistoryInfo[nSel + m_nStockNumPerPage - 1]->m_cDealDate);
	pDC->DrawText(str,&rect,DT_SINGLELINE | DT_RIGHT);		//交易日期

	pDC->SetTextColor( RGB(0, 255, 0) );
	pDC->SetBkColor( RGB(0,0,0) );
	rect.left = m_rectBottom.left - 100;
	rect.right = m_rectBottom.left - 5;
	rect.top = m_rectBottom.top;
	rect.bottom = m_rectBottom.bottom;	
	str.Format("%d",pHistoryDoc->m_nHiQuantity);
	pDC->DrawText(str,&rect,DT_SINGLELINE | DT_RIGHT);		//最大成交量
	
	pDC->SetTextColor(colorOldText);
	pDC->SetBkColor(colorOldBk);


}

//绘制成交量柱状图
void CHistoryView::DrawQuantity(CDC* pDC)
{
	CHistoryDoc* pHistoryDoc = (CHistoryDoc*)GetDocument();	
	int nSel = (  (CHistoryFrame*)GetParentFrame() )->GetSliderCtrlPos();	
	pHistoryDoc->GetPriceRange(nSel,m_nStockNumPerPage);
	
	double dbLeft = (double)m_rectBottom.left;
	for(int nI = 0;nI < m_nStockNumPerPage;nI++)
	{
		int nQuantity = pHistoryDoc->m_arrayHistoryInfo[nI + nSel]->m_nQuantity;
		dbLeft += m_dbXStep;
		double dbRight = dbLeft + m_dbXStep / 2;
		double dbBottom = m_rectBottom.bottom + m_nPenWidth;
		double dbTop = dbBottom  + (nQuantity * m_dbYQuantityUnit);
		CRect rect((int)dbLeft,(int)dbTop,(int)dbRight,(int)dbBottom);
		
		double dbOpenPrice = pHistoryDoc->m_arrayHistoryInfo[nI + nSel]->m_dbOpenPrice;//当日开盘价
		double dbClosePrice	= pHistoryDoc->m_arrayHistoryInfo[nI + nSel]->m_dbClosePrice;//当日收盘价
		if(dbClosePrice >= dbOpenPrice)//收盘价高于开盘价
		{
			CPen pen(PS_SOLID,m_nPenWidth / 2,RGB(255,0,0) );
			CPen* pOldPen = pDC->SelectObject(&pen);
			pDC->Rectangle(&rect);	
			pDC->SelectObject(pOldPen);
		}
		else
		{
			CBrush brush( RGB(0,255,0) );
			pDC->FillRect(&rect,&brush);
		}
	}
}


void CHistoryView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class	
	CView::OnPrepareDC(pDC, pInfo);
	CRect rect;
	GetClientRect(&rect);//得到客户区设备坐标系大小
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportOrg(rect.left,rect.bottom);
	pDC->SetWindowExt(m_rectClient.Width(),m_rectClient.Height());
	pDC->SetViewportExt(rect.Width(),rect.Height());
}

//SliderCtrl控件重绘消息响应
void CHistoryView::OnCustomdrawSliderctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here	
	InvalidateRect(NULL);
	*pResult = 0;
}

//绘制五日均线图
void CHistoryView::DrawLineOfAverageFiveDay(CDC* pDC)
{
	CHistoryDoc* pHistoryDoc = (CHistoryDoc*)GetDocument();	
	int nSel = (  (CHistoryFrame*)GetParentFrame() )->GetSliderCtrlPos();
	pHistoryDoc->GetPriceRange(nSel,m_nStockNumPerPage);

	//设置画笔
	CPen pen(PS_SOLID,m_nPenWidth / 2,RGB(255,255,0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	double dbLowPrice = pHistoryDoc->m_dbLowPrice;
	double dbX = m_rectMid.left + m_dbXStep / 4;
	int nY = m_rectMid.bottom + m_nPenWidth;
	for(int nI = 0;nI < m_nStockNumPerPage;nI++)
	{	
		dbX += m_dbXStep;
		if(nI == 0)
		{
			double dbPrice = pHistoryDoc->m_arrayHistoryPriceOfFiveDay[nI + nSel];
			pDC->MoveTo( (int)dbX,(int)( (dbPrice - dbLowPrice) * m_dbYPriceUnit ) + nY );
			continue;
		}
		double dbPrice = pHistoryDoc->m_arrayHistoryPriceOfFiveDay[nI + nSel];
		pDC->LineTo( (int)dbX,(int)( (dbPrice - dbLowPrice) * m_dbYPriceUnit ) + nY );	
	}

	pDC->SelectObject(pOldPen);
}

//设置绘图相关成员变量
void CHistoryView::SetVariable()
{
	CHistoryDoc* pHistoryDoc = (CHistoryDoc*)GetDocument();	
	int nSel = ( (CHistoryFrame*)GetParentFrame() )->GetSliderCtrlPos();
	pHistoryDoc->GetPriceRange(nSel,m_nStockNumPerPage);

	double dbX = (m_rectBottom.right - m_rectBottom.left) / (m_nStockNumPerPage) ;
	double dbY =  pHistoryDoc->m_nHiQuantity;
	dbY = (m_rectBottom.top - m_rectBottom.bottom - 2 * m_nPenWidth) / dbY;
	//股票价格(每元)对应的逻辑单位高度
	m_dbYPriceUnit = (m_rectMid.top - m_rectMid.bottom  - 2 * m_nPenWidth) / (pHistoryDoc->m_dbHiPrice - pHistoryDoc->m_dbLowPrice);
	m_dbYQuantityUnit = dbY;//股票交易量对应的逻辑单位高度
	m_dbXStep = dbX;//X轴间隔

	//设置股票每日曲线对应的矩形区域
	double dbLeft = m_rectBottom.left;
	m_ArrayRect.RemoveAll();
	for(int nI = 0;nI < m_nStockNumPerPage;nI++)
	{
		dbLeft += m_dbXStep;
		CRect rect;
		rect.left = (int)dbLeft;
		rect.right = rect.left + int(m_dbXStep / 2);
		rect.top = m_rectMid.top;
		rect.bottom = m_rectBottom.bottom;
		m_ArrayRect.Add(rect);
	}
}

//绘制K线图
void CHistoryView::DrawLineOfK(CDC *pDC)
{
	CHistoryDoc* pHistoryDoc = (CHistoryDoc*)GetDocument();
	int nSel = ( (CHistoryFrame*)GetParentFrame() )->GetSliderCtrlPos();

	int nCount = pHistoryDoc->m_arrayHistoryInfo.GetSize();
	double dbLeft = m_rectMid.left;//X起始位置
	double dbBottom = m_rectMid.bottom + m_nPenWidth;//Y起始位置
	CPen pen1( PS_SOLID,m_nPenWidth / 2,RGB(255,0,0) );
	CPen pen2( PS_SOLID,m_nPenWidth / 2,RGB(0,255,0) );
	CPen* pOldPen;
	for(int nI = 0;nI < m_nStockNumPerPage;nI++)
	{
		double dbHiPrice = pHistoryDoc->m_arrayHistoryInfo[nI + nSel]->m_dbHiPrice;//当日最高价
		double dbLowPrice = pHistoryDoc->m_arrayHistoryInfo[nI + nSel]->m_dbLowPrice;//当日最低价
		double dbOpenPrice = pHistoryDoc->m_arrayHistoryInfo[nI + nSel]->m_dbOpenPrice;//当日开盘价
		double dbClosePrice	= pHistoryDoc->m_arrayHistoryInfo[nI + nSel]->m_dbClosePrice;//当日收盘价
		double dbLowestPrice = pHistoryDoc->m_dbLowPrice;//历史最低价
		
		//绘制矩形
		dbLeft += m_dbXStep;
		CRect rect;
		rect.left = (int)dbLeft;
		rect.right = rect.left + int(m_dbXStep / 2);
		if(dbClosePrice >= dbOpenPrice)//收盘价高于开盘价
		{
			rect.top = int( (dbClosePrice - dbLowestPrice) * m_dbYPriceUnit + dbBottom );
			rect.bottom = int( (dbOpenPrice - dbLowestPrice) * m_dbYPriceUnit + dbBottom );
			CPen pen( PS_SOLID,m_nPenWidth / 2,RGB(255,0,0) );
			pOldPen = pDC->SelectObject(&pen1);
			pDC->Rectangle(&rect);
		}
		else//收盘价低于开盘价
		{
			rect.top = int( (dbOpenPrice - dbLowestPrice) * m_dbYPriceUnit + dbBottom );
			rect.bottom = int( (dbClosePrice - dbLowestPrice) * m_dbYPriceUnit + dbBottom );
			CBrush brush( RGB(0,255,0) );
			pDC->FillRect(&rect,&brush);
			pOldPen = pDC->SelectObject(&pen2);
		}	

		//绘制直线
		pDC->MoveTo( int(dbLeft + m_dbXStep / 4),rect.top);
		pDC->LineTo( int(dbLeft + m_dbXStep / 4),int( (dbHiPrice - dbLowestPrice) * m_dbYPriceUnit + dbBottom ) );
		pDC->MoveTo( int(dbLeft + m_dbXStep / 4),rect.bottom);
		pDC->LineTo( int(dbLeft + m_dbXStep / 4),int( (dbLowPrice - dbLowestPrice) * m_dbYPriceUnit + dbBottom ) );

		pDC->SelectObject(pOldPen);
	}

}

void CHistoryView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	OnPrepareDC(&dc);
	DarwDenote(&dc,point);
	DrawTitle(&dc);
	CView::OnMouseMove(nFlags, point);
}

//绘制股票查询点指示线
void CHistoryView::DarwDenote(CDC *pDC,CPoint point)
{
	OnPrepareDC(pDC);
	pDC->LPtoDP(&m_rectMid);
	pDC->LPtoDP(&m_rectBottom);

	m_nCurSel = NOSELECTION;
	int nCount = m_ArrayRect.GetSize();
	for (int nI = 0;nI < nCount;nI++)
	{
		pDC->LPtoDP(&m_ArrayRect[nI]);
		if( (m_rectMid.PtInRect(point) || m_rectBottom.PtInRect(point)) && m_ArrayRect[nI].PtInRect(point) )
		{
			m_nCurSel = nI;
			pDC->DPtoLP(&m_ArrayRect[nI]);
			break;
		}
		pDC->DPtoLP(&m_ArrayRect[nI]);		
	}

	pDC->DPtoLP(&m_rectMid);
	pDC->DPtoLP(&m_rectBottom);

	if(m_nCurSel != NOSELECTION)
	{			
		if(m_nPreSel != NOSELECTION && m_nPreSel != m_nCurSel)
		{
		
			
			double dbX = m_rectMid.left + (m_nPreSel + 1) * m_dbXStep + m_dbXStep / 4 ;			
			CRect rect1(int(dbX) - 2,m_rectMid.top,int(dbX) + 2,m_rectMid.bottom);
			CRect rect2(int(dbX) - 2,m_rectBottom.top,int(dbX) + 2,m_rectBottom.bottom);
			pDC->LPtoDP(&rect1);
			pDC->LPtoDP(&rect2);
			InvalidateRect(&rect1);
			InvalidateRect(&rect2);
		}
		
		double dbX = m_rectMid.left + (m_nCurSel + 1) * m_dbXStep + m_dbXStep / 4 ;		
		CRect rect1(int(dbX) - 2,m_rectMid.top,int(dbX) + 2,m_rectMid.bottom);
		CRect rect2(int(dbX) - 2,m_rectBottom.top,int(dbX) + 2,m_rectBottom.bottom);		
		CBrush brush( RGB(0,0,255) );
		pDC->FillRect(&rect1,&brush);
		pDC->FillRect(&rect2,&brush);
		
		m_nPreSel = m_nCurSel;
	}

}

void CHistoryView::DrawTitle(CDC *pDC)
{
	CHistoryDoc* pHistoryDoc = (CHistoryDoc*)GetDocument();
	int nSel = ( (CHistoryFrame*)GetParentFrame() )->GetSliderCtrlPos();
	CString strText[] = {"最高价:","最低价:","开盘价:","收盘价:","成交量:","交易日期:"};
	if(m_nPreSel != NOSELECTION)
	{
		nSel += m_nPreSel;
		char cC[100];
		strText[5] += pHistoryDoc->m_arrayHistoryInfo[nSel]->m_cDealDate;
		::sprintf(cC,"%d",pHistoryDoc->m_arrayHistoryInfo[nSel]->m_nQuantity);
		strText[4] += cC;
		::sprintf(cC,"%.4lf",pHistoryDoc->m_arrayHistoryInfo[nSel]->m_dbClosePrice);
		strText[3] += cC;
		::sprintf(cC,"%.4lf",pHistoryDoc->m_arrayHistoryInfo[nSel]->m_dbOpenPrice);
		strText[2] += cC;
		::sprintf(cC,"%.4lf",pHistoryDoc->m_arrayHistoryInfo[nSel]->m_dbLowPrice);
		strText[1] += cC;
		::sprintf(cC,"%.4lf",pHistoryDoc->m_arrayHistoryInfo[nSel]->m_dbHiPrice);
		strText[0] += cC;
	}
	


	int nX = (m_rectTop.right - m_rectTop.left) / 7;
	CRect rect;
	rect.left	= m_rectTop.left + m_nPenWidth;
	rect.right	= m_rectTop.right;
	rect.top	= m_rectTop.top;
	rect.bottom = m_rectTop.bottom;

	COLORREF colorOldText = pDC->SetTextColor( RGB(255, 255, 0) );
	COLORREF colorOldBk = pDC->SetBkColor( RGB(0,0,0) );
	
	pDC->DrawText(strText[5],&rect,DT_SINGLELINE | DT_VCENTER | DT_LEFT);//绘制交易日期
	rect.left	+= 2 * nX;
	rect.right	+= 2 * nX;	
	for(int nI = 0;nI < 5;nI++)
	{
		pDC->DrawText(strText[nI],&rect,DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		rect.left	+= nX;
	}

	pDC->SetTextColor(colorOldText);
	pDC->SetBkColor(colorOldBk);
}

int CHistoryView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}
