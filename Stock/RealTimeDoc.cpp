// RealTimeDoc.cpp : implementation file
//

#include "stdafx.h"
#include "Stock.h"
#include "DbConn.h"
#include "RealTimeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
DbAccessorPool dbAccessPool;
/////////////////////////////////////////////////////////////////////////////
// CRealTimeDoc

IMPLEMENT_DYNCREATE(CRealTimeDoc, CDocument)

CRealTimeDoc::CRealTimeDoc()
{

}

BOOL CRealTimeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CRealTimeDoc::~CRealTimeDoc()
{

}


BEGIN_MESSAGE_MAP(CRealTimeDoc, CDocument)
	//{{AFX_MSG_MAP(CRealTimeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDoc diagnostics

#ifdef _DEBUG
void CRealTimeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRealTimeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDoc serialization

void CRealTimeDoc::Serialize(CArchive& ar)
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
// CRealTimeDoc commands

void CRealTimeDoc::LoadData(CString strNo, CString day, bool is_dynamic)
{
	m_strNo= strNo;
	m_Day = day;
	m_isDynamic = is_dynamic;
	LoadData();
}

void CRealTimeDoc::LoadData()
{
	DbConn conn(dbAccessPool);
	vector<CThostFtdcDepthMarketDataField> result;
    m_RealTimeInfo.clear();
	
	string startTime= "09:14:59";
	if( !m_RealTimeInfo.empty() )
	{
		int nCount = m_RealTimeInfo.size();
		startTime = m_RealTimeInfo[nCount-1].UpdateTime;
	}

    conn.m_db->getData((LPCSTR)m_strNo, (LPCSTR)m_Day, startTime, (LPCSTR)m_Day,
            "15:15:01", result);

	for (int i=0; i < result.size(); i++)
	{
		m_RealTimeInfo.push_back(result[i]);
	}
	/*
    for( int i=m_RealTimeInfo.size()-1; i>0; i--)
    {
        m_RealTimeInfo[i].Volume-=m_RealTimeInfo[i-1].Volume;
        m_RealTimeInfo[i].Turnover-=m_RealTimeInfo[i-1].Turnover;
        m_RealTimeInfo[i].OpenInterest-=m_RealTimeInfo[i-1].OpenInterest;
    }*/

    conn.m_db->getData((LPCSTR)m_strNo, (LPCSTR)m_Day, startTime, (LPCSTR)m_Day,
            "15:15:01", m_OrderInfo);
/*
	OrderInfo order;
	order.amount=2;
	order.day=m_Day;
	order.m_instrumentID=m_strNo;
	order.milliSec=0;
	order.time="09:45:00";
	this->m_OrderInfo.push_back(order);

	order.amount=-3;
	order.day=m_Day;
	order.m_instrumentID=m_strNo;
	order.milliSec=0;
	order.time="14:01:00";
	this->m_OrderInfo.push_back(order);*/

	GetPriceRange();
}

void CRealTimeDoc::GetPriceRange()
{
	int nCount = m_RealTimeInfo.size();
	if (nCount != 0)
	{
		m_dbClosePrice = m_RealTimeInfo[0].LastPrice; 
		m_dbHiPrice =    m_dbClosePrice; 
		m_dbLowPrice =   m_dbClosePrice; 
	} 
	m_nHiQuantity = 0; 
	m_PointWin.push_back(0);
	m_HiWin=0;
	m_LowWin=0;
	int orderIndex=0;
	int orderNum=m_OrderInfo.size();
	int order_amount=0;
	for (int nI = 0;nI < nCount;nI++) 
	{ 
		if (m_nHiQuantity < m_RealTimeInfo[nI].Volume) 
		{ 
			m_nHiQuantity = m_RealTimeInfo[nI].Volume; 
		} 

		if (m_dbHiPrice<m_RealTimeInfo[nI].LastPrice)
		{
			m_dbHiPrice = m_RealTimeInfo[nI].LastPrice;
		}

		if (m_dbLowPrice>m_RealTimeInfo[nI].LastPrice)
		{
			m_dbLowPrice = m_RealTimeInfo[nI].LastPrice;
		}

		if( nI>0)
			m_PointWin.push_back(m_PointWin[nI-1]+
				order_amount*(m_RealTimeInfo[nI].LastPrice-m_RealTimeInfo[nI-1].LastPrice));

		if( m_HiWin < m_PointWin[nI])
			m_HiWin = m_PointWin[nI];

		if( m_LowWin > m_PointWin[nI])
			m_LowWin = m_PointWin[nI];

		if( orderIndex < orderNum )
		{
			if(m_OrderInfo[orderIndex].time<=m_RealTimeInfo[nI].UpdateTime)
			{
				if(  m_OrderInfo[orderIndex].is_buy == 0 )
					m_OrderInfo[orderIndex].amount = -m_OrderInfo[orderIndex].amount;

				order_amount+= m_OrderInfo[orderIndex].amount;
				orderIndex++;
			}
		}
	} 

	m_dbHiPrice+=10;
	m_dbLowPrice-=10;

	m_HiWin+=3;
	m_LowWin-=3;
}
