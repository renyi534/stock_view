// RealTimeView.cpp : implementation file
//

#include "stdafx.h"
#include "Stock.h"
#include "RealTimeView.h"
#include "RealTimeRecord.h"
#include "RealTimeFrame.h"
#include "RealTimeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView

IMPLEMENT_DYNCREATE(CRealTimeView, CView)

CRealTimeView::CRealTimeView():m_nPenWidth(2),m_nStockNumPerPage(3600*4.5*2+1),m_nWindowWidth(1000),m_nWindowHeight(500),
m_nPreSel(NOSELECTION),m_nCurSel(NOSELECTION),m_nStartHour(9),m_nStartMinute(30),m_strStartTime("09:30"),m_strEndTime("11:30")
{
	m_rectClient.left = 0;
	m_rectClient.right = m_nWindowWidth;
	m_rectClient.top = m_nWindowHeight;
	m_rectClient.bottom = 0;

	m_rectFrame.left = m_rectClient.left + 5;
	m_rectFrame.right = m_rectClient.right - 5;
	m_rectFrame.top = m_rectClient.top - 5;
	m_rectFrame.bottom = m_rectClient.bottom + 5;

	m_rectTop.left	= 70;	
	m_rectTop.right	= m_nWindowWidth - 200;
	m_rectTop.top	= m_nWindowHeight - 10;
	m_rectTop.bottom	= m_rectTop.top - 30;
	
	m_rectMid.left		= 70;	
	m_rectMid.right		= m_nWindowWidth - 200;
	m_rectMid.top		= m_rectTop.bottom - 5;
	m_rectMid.bottom	= m_rectTop.bottom - m_nWindowHeight / 2;	
	
	m_rectBottom.left		= 70;
	m_rectBottom.right		= m_nWindowWidth - 200;
	m_rectBottom.top		= m_rectMid.bottom - 30;	
	m_rectBottom.bottom		= 10;

	m_rectRight.left = m_rectMid.right + 70;
	m_rectRight.right = m_nWindowWidth - 10;
	m_rectRight.top = m_rectTop.top;
	m_rectRight.bottom = m_rectBottom.bottom;


}

CRealTimeView::~CRealTimeView()
{

}


BEGIN_MESSAGE_MAP(CRealTimeView, CView)
	//{{AFX_MSG_MAP(CRealTimeView)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView drawing

void CRealTimeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)pDoc;
	if( pRealTimeDoc->m_RealTimeInfo.size() <=0 )
		return;
	// TODO: add draw code here
	SetVariable();//设置绘图相关变量值
	DrawFrameText(pDC);//绘制框架
	DrawTitle(pDC);//绘制标题
	DrawDate(pDC);//绘制数据区
	DrawQuantity(pDC);//绘制成交量曲线图
	DrawLineOfDealPrice(pDC);//绘制成交价格区线图	
	DrawLineOfWin(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView diagnostics

#ifdef _DEBUG
void CRealTimeView::AssertValid() const
{
	CView::AssertValid();
}

void CRealTimeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRealTimeView message handlers



void CRealTimeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnPrepareDC(pDC, pInfo);
	
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(m_nWindowWidth,-m_nWindowHeight);
	pDC->SetViewportExt(rect.Width(),rect.Height());
	pDC->SetViewportOrg(0,rect.Height());

}

//绘制框架
void CRealTimeView::DrawFrameText(CDC *pDC)
{
	CPen pen( PS_SOLID,m_nPenWidth,RGB(255,0,0) );
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);
	//绘制矩形框
	pDC->Rectangle(&m_rectFrame);
	pDC->Rectangle(&m_rectTop);
	pDC->Rectangle(&m_rectMid);
	pDC->Rectangle(&m_rectBottom);
	pDC->Rectangle(&m_rectRight);
	pDC->SelectObject(pOldPen);

	//绘制虚线
	double dbXTimeStart = m_rectMid.left;//时间起始X坐标
	double dbXTimeStep = (m_rectMid.right - m_rectMid.left) / 4.00;//时间坐标间隔
	double dbYPriceStart = m_rectMid.bottom;//价格起始Y坐标
	double dbYPriceStep = (m_rectMid.top - m_rectMid.bottom) / 6.00;//价格坐标间隔
	CPen penDash(PS_DOT,0,RGB(255,0,0) );
	CPen* pOldPen1 = pDC->SelectObject(&penDash);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetBkColor( RGB(0,0,0) );
	for (int nI = 0;nI < 5;nI++)//绘制横向虚线
	{		
		dbYPriceStart += dbYPriceStep;
		pDC->MoveTo(m_rectMid.left,(int)dbYPriceStart);
		pDC->LineTo(m_rectMid.right,(int)dbYPriceStart);		
	}
	for (int nJ = 0;nJ < 3;nJ++)//绘制纵向虚线
	{
		dbXTimeStart += dbXTimeStep;
		pDC->MoveTo((int)dbXTimeStart,m_rectMid.bottom);
		pDC->LineTo((int)dbXTimeStart,m_rectMid.top);
	}
	pDC->SelectObject(pOldPen1);

	//绘制文本
	COLORREF crOldText = pDC->SetTextColor( RGB(0,255,0) );
	COLORREF crOldBk = pDC->SetBkColor( RGB(0,0,0) );

	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	//pRealTimeDoc->GetPriceRange();
	CString str;
	str.Format("%.2f",pRealTimeDoc->m_nHiQuantity);
	CRect rect;
	rect.left = m_rectBottom.left - 100;
	rect.right = m_rectBottom.left - 5; 
	rect.top = m_rectBottom.top;
	rect.bottom = m_rectBottom.bottom;
	pDC->DrawText(str,&rect,DT_RIGHT);//绘制今日最大交易量

	str.Format("%.2lf",pRealTimeDoc->m_dbLowPrice);
	rect.left = m_rectMid.left - 100;
	rect.right = m_rectMid.left - 5; 
	rect.bottom = m_rectMid.bottom;
	rect.top = m_rectMid.top;
	pDC->DrawText(str,&rect,DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);//绘制今日最低成交价0

	str.Format("%.2lf",pRealTimeDoc->m_LowWin);
	rect.left = m_rectMid.right + 5;
	rect.right = m_rectMid.right+50; 
	rect.bottom = m_rectMid.bottom;
	//rect.top += dbYStep;
	pDC->DrawText(str,&rect,DT_SINGLELINE | DT_BOTTOM | DT_LEFT);//绘制成交价中间线1

	double dbYStep = (m_rectMid.top - m_rectMid.bottom) / 6.00;//价格坐标间隔
	double dbPriceStep = (pRealTimeDoc->m_dbHiPrice - pRealTimeDoc->m_dbLowPrice) / 6.00;//1/4均价
	double dbWinStep = (pRealTimeDoc->m_HiWin - pRealTimeDoc->m_LowWin) / 6.00;//1/4均价

	double dbPrice = pRealTimeDoc->m_dbLowPrice + dbPriceStep;//1/4均价
	str.Format("%.2lf",dbPrice);
	rect.left = m_rectMid.left - 100;
	rect.right = m_rectMid.left - 5; 
	rect.bottom = m_rectMid.bottom;
	rect.top = m_rectMid.bottom + (int)dbYStep + 10;
	pDC->DrawText(str,&rect,DT_RIGHT);//绘制成交价中间线1

	double dbWin = pRealTimeDoc->m_LowWin + dbWinStep;//1/4均价
	str.Format("%.2lf",dbWin);
	rect.left = m_rectMid.right + 5;
	rect.right = m_rectMid.right+50; 
	rect.bottom = m_rectMid.bottom;
	rect.top = m_rectMid.bottom + (int)dbYStep + 10;
	pDC->DrawText(str,&rect,DT_LEFT);//绘制成交价中间线1

	dbPrice += dbPriceStep;
	str.Format("%.2lf",dbPrice);
	rect.left = m_rectMid.left - 100;
	rect.right = m_rectMid.left - 5; 
	rect.bottom = m_rectMid.bottom;
	rect.top += (int)dbYStep;
	pDC->DrawText(str,&rect,DT_RIGHT);//绘制成交价中间线2

	dbWin += dbWinStep;//1/4均价
	str.Format("%.2lf",dbWin);
	rect.left = m_rectMid.right + 5;
	rect.right = m_rectMid.right+50; 
	rect.bottom = m_rectMid.bottom;
	//rect.top += dbYStep;
	pDC->DrawText(str,&rect,DT_LEFT);//绘制成交价中间线1

	pDC->SetTextColor( RGB(255,255,0) );
	double dbAverPrice = (pRealTimeDoc->m_dbLowPrice + pRealTimeDoc->m_dbHiPrice) / 2;//平均价
	str.Format("%.2lf",dbAverPrice);
	rect.left = m_rectMid.left - 100;
	rect.right = m_rectMid.left - 5; 
	rect.bottom = m_rectMid.bottom;
	rect.top += (int)dbYStep;
	pDC->DrawText(str,&rect,DT_RIGHT);//绘制成交价平均值3

	dbWin = (pRealTimeDoc->m_HiWin + pRealTimeDoc->m_LowWin) / 2;
	str.Format("%.2lf",dbWin);
	rect.left = m_rectMid.right + 5;
	rect.right = m_rectMid.right+50; 
	rect.bottom = m_rectMid.bottom;
	//rect.top += dbYStep;
	pDC->DrawText(str,&rect,DT_LEFT);//绘制成交价中间线1

	pDC->SetTextColor( RGB(255,0,0) );

	dbPrice = dbAverPrice + dbPriceStep;
	str.Format("%.2lf",dbPrice);
	rect.left = m_rectMid.left - 100;
	rect.right = m_rectMid.left - 5; 
	rect.bottom = m_rectMid.bottom;
	rect.top += (int)dbYStep;
	pDC->DrawText(str,&rect,DT_RIGHT);//绘制成交价中间线4
	
	dbWin += dbWinStep;
	str.Format("%.2lf",dbWin);
	rect.left = m_rectMid.right + 5;
	rect.right = m_rectMid.right+50; 
	rect.bottom = m_rectMid.bottom;
	//rect.top += dbYStep;
	pDC->DrawText(str,&rect,DT_LEFT);//绘制成交价中间线1

	dbPrice += dbPriceStep;
	str.Format("%.2lf",dbPrice);
	rect.left = m_rectMid.left - 100;
	rect.right = m_rectMid.left - 5; 
	rect.bottom = m_rectMid.bottom;
	rect.top += (int)dbYStep;
	pDC->DrawText(str,&rect,DT_RIGHT);//绘制成交价中间线5
	
	dbWin += dbWinStep;
	str.Format("%.2lf",dbWin);
	rect.left = m_rectMid.right + 5;
	rect.right = m_rectMid.right+50; 
	rect.bottom = m_rectMid.bottom;
	//rect.top += dbYStep;
	pDC->DrawText(str,&rect,DT_LEFT);//绘制成交价中间线1

	str.Format("%.2lf",pRealTimeDoc->m_dbHiPrice);
	rect.left = m_rectMid.left - 100;
	rect.right = m_rectMid.left - 5; 
	rect.top = m_rectMid.top;
	rect.bottom = m_rectMid.bottom;
	pDC->DrawText(str,&rect,DT_RIGHT);//绘制今日最高成交价6


	str.Format("%.2lf",pRealTimeDoc->m_HiWin);
	rect.left = m_rectMid.right + 5;
	rect.right = m_rectMid.right+50; 
	rect.bottom = m_rectMid.bottom;
	//rect.top += dbYStep;
	pDC->DrawText(str,&rect,DT_LEFT);//绘制成交价中间线1

	pDC->SetTextColor( RGB(255,255,0) );
	str.Format("%s","09:15:00");
	rect.left = m_rectMid.left;
	rect.right = m_rectMid.right; 
	rect.top = m_rectMid.bottom;
	rect.bottom = m_rectBottom.top;
	pDC->DrawText(str,&rect,DT_LEFT);//绘制开盘时间
	
	int nXTimeMid = (m_rectMid.left + m_rectMid.right) / 2;
	str.Format("%s","10:22:30");
	rect.left = m_rectMid.left;
	rect.right = nXTimeMid; 
	rect.top = m_rectMid.bottom;
	rect.bottom = m_rectBottom.top;
	pDC->DrawText(str,&rect,DT_CENTER);//绘制中间时间1
	
	str.Format("%s","11:30:00");
	rect.left = m_rectMid.left;
	rect.right = m_rectMid.right; 
	rect.top = m_rectMid.bottom;
	rect.bottom = m_rectBottom.top;
	pDC->DrawText(str,&rect,DT_CENTER);//绘制中间时间2
	
	str.Format("%s","14:07:30");
	rect.left = nXTimeMid;
	rect.right = m_rectMid.right; 
	rect.top = m_rectMid.bottom;
	rect.bottom = m_rectBottom.top;
	pDC->DrawText(str,&rect,DT_CENTER);//绘制中间时间3
	
	str.Format("%s","15:15:00");
	rect.left = m_rectMid.left;
	rect.right = m_rectMid.right; 
	rect.top = m_rectMid.bottom;
	rect.bottom = m_rectBottom.top;
	pDC->DrawText(str,&rect,DT_RIGHT);//绘制收盘时间
	
	
	pDC->SetBkColor(crOldBk);
	pDC->SetTextColor(crOldText);
	
	
}

BOOL CRealTimeView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
	CRect rect;
	GetClientRect(&rect);//得到客户区设备坐标系大小
	CBrush brush( RGB(0,0,0) );
	pDC->FillRect(&rect,&brush);

	return 1;
}

//绘制标题栏
int CRealTimeView::findSel(int sel)
{	
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	int nCount = pRealTimeDoc->m_RealTimeInfo.size();
	int high= nCount-1;
	int low=0;
	int middle=0;

	while(low<=high)
	{
		middle=(high+low)>>1;
		int currTime = TimeToInt(pRealTimeDoc->m_RealTimeInfo[middle].UpdateTime,
				pRealTimeDoc->m_RealTimeInfo[middle].UpdateMillisec);

		if(currTime<sel+1)
			low=middle+1;
		else if(currTime>sel+1)
			high=middle-1;
		else
			return middle;
	}

	return -1;
}

//绘制标题栏
void CRealTimeView::DrawTitle(CDC *pDC)
{	
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	CString str[] = {"期货代码:","交易日期:","当前价格:","交易时间:","成交量:"};

	CString strAdd;
	strAdd.Format("%s",pRealTimeDoc->m_RealTimeInfo[0].InstrumentID);
	str[0] += strAdd;
	strAdd.Format("%s",pRealTimeDoc->m_RealTimeInfo[0].TradingDay);
	str[1] += strAdd;

	if (m_nPreSel != NOSELECTION)
	{
		int nI = findSel(m_nPreSel);
		/*int nCount = pRealTimeDoc->m_RealTimeInfo.size();
		for (int nI = 0;nI < nCount;nI++)
		{
			int currTime = TimeToInt(pRealTimeDoc->m_RealTimeInfo[nI].UpdateTime,
				pRealTimeDoc->m_RealTimeInfo[nI].UpdateMillisec);
			if (currTime == m_nPreSel + 1)
			{
				strAdd.Format("%.2lf",pRealTimeDoc->m_RealTimeInfo[nI].LastPrice);
				str[2] += strAdd;

				strAdd = pRealTimeDoc->m_RealTimeInfo[nI].UpdateTime;
				str[3] += strAdd;	

				strAdd.Format("%.2f",(double)pRealTimeDoc->m_RealTimeInfo[nI].Volume);
				str[4] += strAdd;

				break;
			}
		}*/
		if(nI>=0)
		{
					strAdd.Format("%.2lf",pRealTimeDoc->m_RealTimeInfo[nI].LastPrice);
					str[2] += strAdd;

					strAdd = pRealTimeDoc->m_RealTimeInfo[nI].UpdateTime;
					str[3] += strAdd;	

					strAdd.Format("%.2f",(double)pRealTimeDoc->m_RealTimeInfo[nI].Volume);
					str[4] += strAdd;
		}
	}	
	
	CRect rect;
	rect.left = m_rectTop.left + m_nPenWidth;
	rect.right = m_rectTop.right;
	rect.top = m_rectTop.top;
	rect.bottom = m_rectTop.bottom;
	double dbX = (m_rectTop.right - m_rectTop.left) / 5.0;

	COLORREF crOldText = pDC->SetTextColor( RGB(255,255,0) );
	COLORREF crOldBk = pDC->SetBkColor( RGB(0,0,0) );
	CString eraseStr="                                ";
	int nI;
	long origLeft=rect.left;
	for ( nI = 0;nI < 5;nI++)
	{
		pDC->DrawText(eraseStr,&rect,DT_LEFT | DT_SINGLELINE | DT_VCENTER);
		rect.left += (int)dbX;	
	}

	rect.left=origLeft;
	for ( nI = 0;nI < 5;nI++)
	{
		pDC->DrawText(str[nI],&rect,DT_LEFT | DT_SINGLELINE | DT_VCENTER);
		rect.left += (int)dbX;	
	}
	pDC->SetTextColor(crOldText);
	pDC->SetBkColor(crOldBk);	
}


//绘制数据区
void CRealTimeView::DrawDate(CDC *pDC)
{
	double dbY = (m_rectRight.top - m_rectRight.bottom) / (double)10;
	CRect rect;
	rect.left = m_rectRight.left + m_nPenWidth;
	rect.right = m_rectRight.right - m_nPenWidth;
	rect.top = m_rectRight.top - m_nPenWidth;
	rect.bottom = m_rectRight.bottom;
	COLORREF crOldText = pDC->SetTextColor( RGB(255,255,0) );
	COLORREF crOldBk = pDC->SetBkColor( RGB(0,0,0) );

	CString str;
	CString eraseStr="                                        ";
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	if (m_nPreSel != NOSELECTION)
	{
		int nCount = pRealTimeDoc->m_RealTimeInfo.size();
		int nI = findSel(m_nPreSel);
		if(nI>=0)
		{
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("买一价:%.2f",pRealTimeDoc->m_RealTimeInfo[nI].BidPrice1);
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("买一量:%.2f",(double)pRealTimeDoc->m_RealTimeInfo[nI].BidVolume1);
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("卖一价:%.2f",pRealTimeDoc->m_RealTimeInfo[nI].AskPrice1);
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("卖一量:%.2f",(double)pRealTimeDoc->m_RealTimeInfo[nI].AskVolume1);
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("持仓量:%.2f",pRealTimeDoc->m_RealTimeInfo[nI].OpenInterest);	
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("收益:%.2f",pRealTimeDoc->m_PointWin[nI]);	
				pDC->DrawText(str,&rect,DT_LEFT);
		}
		/*
		for (int nI = 0;nI < nCount;nI++)
		{
			int currTime = TimeToInt(pRealTimeDoc->m_RealTimeInfo[nI].UpdateTime,
				pRealTimeDoc->m_RealTimeInfo[nI].UpdateMillisec);
			if (currTime == m_nPreSel + 1)
			{
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("买一价:%.2f",pRealTimeDoc->m_RealTimeInfo[nI].BidPrice1);
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("买一量:%.2f",(double)pRealTimeDoc->m_RealTimeInfo[nI].BidVolume1);
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("卖一价:%.2f",pRealTimeDoc->m_RealTimeInfo[nI].AskPrice1);
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("卖一量:%.2f",(double)pRealTimeDoc->m_RealTimeInfo[nI].AskVolume1);
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("持仓量:%.2f",pRealTimeDoc->m_RealTimeInfo[nI].OpenInterest);	
				pDC->DrawText(str,&rect,DT_LEFT);

				rect.top -= (int)dbY;
				pDC->DrawText(eraseStr,&rect,DT_LEFT);
				str.Format("收益:%.2f",pRealTimeDoc->m_PointWin[nI]);	
				pDC->DrawText(str,&rect,DT_LEFT);
				break;
			}
		}*/
	}
	pDC->SetTextColor(crOldText);
	pDC->SetBkColor(crOldBk);
}

//绘制成交量曲线
void CRealTimeView::DrawQuantity(CDC *pDC)
{
	CPen pen( PS_SOLID,m_nPenWidth / 2,RGB(255,255,255) );
	CPen* pOldPen = pDC->SelectObject(&pen);

	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	int nX = m_rectBottom.left;
	int nY = m_rectBottom.bottom + m_nPenWidth;
	int nCount = pRealTimeDoc->m_RealTimeInfo.size();
	for (int nI = 0;nI < nCount;nI++)
	{
		int currTime = TimeToInt(pRealTimeDoc->m_RealTimeInfo[nI].UpdateTime,
			pRealTimeDoc->m_RealTimeInfo[nI].UpdateMillisec);
		double dbX = (currTime) * m_dbXStep + nX;
		double dbY = pRealTimeDoc->m_RealTimeInfo[nI].Volume * m_dbYQuantityUnit + nY;
		pDC->MoveTo( int(dbX),nY );
		pDC->LineTo( int(dbX),int(dbY) );
	}

	pDC->SelectObject(&pOldPen);		
}

//设置绘图相关变量
void CRealTimeView::SetVariable()
{
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	
	double dbX = (m_rectBottom.right - m_rectBottom.left) / (m_nStockNumPerPage + 1.0) ;
	double dbY =  pRealTimeDoc->m_nHiQuantity;
	dbY = (m_rectBottom.top - m_rectBottom.bottom - 2 * m_nPenWidth) / dbY;
	//股票价格(每元)对应的逻辑单位高度
	m_dbYPriceUnit = (m_rectMid.top - m_rectMid.bottom  - 2 * m_nPenWidth) / (pRealTimeDoc->m_dbHiPrice - pRealTimeDoc->m_dbLowPrice);
	m_dbYWinUnit = (m_rectMid.top - m_rectMid.bottom  - 2 * m_nPenWidth) / (pRealTimeDoc->m_HiWin - pRealTimeDoc->m_LowWin);
	m_dbYQuantityUnit = dbY;//股票交易量对应的逻辑单位高度
	m_dbXStep = dbX;//X轴间隔
	
	//设置股票每日曲线对应的X点
	double dbPointX = m_rectBottom.left;
	m_arrayPointX.RemoveAll();
	for(int nI = 0;nI < m_nStockNumPerPage;nI++)
	{
		dbPointX += m_dbXStep;
		m_arrayPointX.Add( int(dbPointX) );
	}
}

//绘制交易价格曲线
void CRealTimeView::DrawLineOfDealPrice(CDC *pDC)
{
	
	CPen pen( PS_SOLID,m_nPenWidth / 2,RGB(255,255,255) );
	CPen* pOldPen = pDC->SelectObject(&pen);
	
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	double dbX0 = m_rectMid.left;
	double dbY0 = m_rectMid.bottom + m_nPenWidth;
	int nCount = pRealTimeDoc->m_RealTimeInfo.size();

	int orderIndex=0;
	int orderNum=pRealTimeDoc->m_OrderInfo.size();
	int order_amount=0;

	for (int nI = 0;nI < nCount;nI++)
	{
		int currTime = TimeToInt(pRealTimeDoc->m_RealTimeInfo[nI].UpdateTime,
			pRealTimeDoc->m_RealTimeInfo[nI].UpdateMillisec);
		double dbX = (currTime) * m_dbXStep + dbX0;
		double dbY = (pRealTimeDoc->m_RealTimeInfo[nI].LastPrice -  pRealTimeDoc->m_dbLowPrice) * m_dbYPriceUnit + dbY0;
		if (nI == 0)
		{
			pDC->MoveTo( int(dbX),int(dbY) );
		}
		else
		{
			pDC->LineTo( int(dbX),int(dbY) );
		}	
		if( orderIndex < orderNum )
		{
			if(pRealTimeDoc->m_OrderInfo[orderIndex].time<=pRealTimeDoc->m_RealTimeInfo[nI].UpdateTime)
			{
				CPen* pTempOldPen = NULL;
				CPen red_pen( PS_SOLID,m_nPenWidth,RGB(255,0,0) );
				CPen green_pen( PS_SOLID,m_nPenWidth,RGB(0,255,0) );
				if( pRealTimeDoc->m_OrderInfo[orderIndex].amount>0 )
				{
					pTempOldPen = pDC->SelectObject(&red_pen);
				}
				else
				{
					pTempOldPen = pDC->SelectObject(&green_pen);
				}
				int circle_radius=5;
				pDC->Ellipse(dbX-circle_radius,dbY+circle_radius,dbX+circle_radius,dbY-circle_radius);
				orderIndex++;

				pDC->SelectObject(&pen);
			}
		}		
	}

	pDC->SelectObject(&pOldPen);	
}

//绘制交易价格曲线
void CRealTimeView::DrawLineOfWin(CDC *pDC)
{
	
	CPen pen( PS_SOLID,m_nPenWidth / 2,RGB(42,66,200) );
	CPen* pOldPen = pDC->SelectObject(&pen);
	
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	double dbX0 = m_rectMid.left;
	double dbY0 = m_rectMid.bottom + m_nPenWidth;
	int nCount = pRealTimeDoc->m_RealTimeInfo.size();
	for (int nI = 0;nI < nCount;nI++)
	{
		int currTime = TimeToInt(pRealTimeDoc->m_RealTimeInfo[nI].UpdateTime,
			pRealTimeDoc->m_RealTimeInfo[nI].UpdateMillisec);
		double dbX = (currTime) * m_dbXStep + dbX0;
		double dbY = (pRealTimeDoc->m_PointWin[nI] -  pRealTimeDoc->m_LowWin) * m_dbYWinUnit + dbY0;
		if (nI == 0)
		{
			pDC->MoveTo( int(dbX),int(dbY) );
		}
		else
		{
			pDC->LineTo( int(dbX),int(dbY) );
		}		
	}

	pDC->SelectObject(&pOldPen);	
}

//绘制指示线
void CRealTimeView::DrawDenote(CDC *pDC,CPoint point)
{
	m_nCurSel = NOSELECTION;
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	pDC->LPtoDP(&m_rectMid);
	pDC->LPtoDP(&m_rectBottom);
	int nCount = m_arrayPointX.GetSize();
	for (int nI = 0;nI < nCount;nI++)
	{
		CPoint point0(m_arrayPointX[nI],0);
		pDC->LPtoDP(&point0);
		if ( (m_rectMid.PtInRect(point) || m_rectBottom.PtInRect(point) ) && point0.x/*m_arrayPointX[nI] */== point.x )
		{
			m_nCurSel = nI;
			break;
		}	
	}
	pDC->DPtoLP(&m_rectMid);
	pDC->DPtoLP(&m_rectBottom);
	if (m_nCurSel != NOSELECTION)
	{
		if(m_nPreSel != NOSELECTION && m_nPreSel != m_nCurSel)
		{
			CRect rect1(m_arrayPointX[m_nPreSel] - 2,m_rectMid.top,m_arrayPointX[m_nPreSel] + 2,m_rectMid.bottom);
			CRect rect2(m_arrayPointX[m_nPreSel] - 2,m_rectBottom.top,m_arrayPointX[m_nPreSel] + 2,m_rectBottom.bottom);
			pDC->LPtoDP(&rect1);
			pDC->LPtoDP(&rect2);
			InvalidateRect(&rect1); 
			InvalidateRect(&rect2);
		}		

		CRect rect1(m_arrayPointX[m_nCurSel] - 2,m_rectMid.top,m_arrayPointX[m_nCurSel] + 2,m_rectMid.bottom);
		CRect rect2(m_arrayPointX[m_nCurSel] - 2,m_rectBottom.top,m_arrayPointX[m_nCurSel] + 2,m_rectBottom.bottom);
		CBrush brush( RGB(0,0,255) );
		pDC->FillRect(&rect1,&brush);
		pDC->FillRect(&rect2,&brush);
		m_nPreSel = m_nCurSel;
	}
}

void CRealTimeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDocument* pDoc = GetDocument();
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)pDoc;
	if( pRealTimeDoc->m_RealTimeInfo.size() <=0 )
		return;
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	OnPrepareDC(&dc);
	DrawDenote(&dc,point);
	DrawTitle(&dc);
	DrawDate(&dc);
	//InvalidateRect(m_rectTop);
	//InvalidateRect(m_rectRight);
	CView::OnMouseMove(nFlags, point);
}


//时间从整型转换成字符串
int CRealTimeView::TimeToInt(string time, int millisec)
{	
	int hour, minute, second;
	double result;

	sscanf(time.c_str(), "%2d:%2d:%2d", &hour, &minute, &second);
	
	if( hour>12 )
	{
		result= ((hour-13)*60+minute)*60+second+3600*2.25;
	}
	else
	{
		result= (hour*60+minute)*60+second-(9*60+15)*60;
	}

	if(millisec!=0)
	{
		result+=millisec/1000.0;
	}

	return 2*result;
}

void CRealTimeView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	InvalidateRect(NULL);
	
}

void CRealTimeView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRealTimeDoc* pRealTimeDoc = (CRealTimeDoc*)GetDocument();
	if( pRealTimeDoc->m_isDynamic )
	{
		pRealTimeDoc->LoadData();
		InvalidateRect(NULL);
	}

	CView::OnTimer(nIDEvent);
}

BOOL CRealTimeView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	//m_nTimer = SetTimer(1, 5000, 0);	
	return CView::PreCreateWindow(cs);
}

void CRealTimeView::OnInitialUpdate() 
{

	CView::OnInitialUpdate();
	m_nTimer = SetTimer(1, 30000, 0);	
	// TODO: Add your specialized code here and/or call the base class
	
}

void CRealTimeView::OnDestroy() 
{

	CView::OnDestroy();
	KillTimer(m_nTimer);	
	// TODO: Add your message handler code here
	
}
