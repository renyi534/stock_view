// HistoryDoc.cpp : implementation file
//

#include "stdafx.h"
#include "Stock.h"
#include "HistoryDoc.h"
#include <fstream.h>


extern CStockApp theApp;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CStockApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc

IMPLEMENT_DYNCREATE(CHistoryDoc, CDocument)

CHistoryDoc::CHistoryDoc()
{
	
}

BOOL CHistoryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CHistoryDoc::~CHistoryDoc()
{
	int nCount = m_arrayHistoryInfo.GetSize();
	for (int nI = 0;nI < nCount;nI++)
	{
		delete m_arrayHistoryInfo[nI];
	}
}


BEGIN_MESSAGE_MAP(CHistoryDoc, CDocument)
	//{{AFX_MSG_MAP(CHistoryDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc diagnostics

#ifdef _DEBUG
void CHistoryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHistoryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc serialization

void CHistoryDoc::Serialize(CArchive& ar)
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

void CHistoryDoc::LoadData(CString strStockNo)
{
	m_arrayHistoryInfo.RemoveAll();
	ifstream inf("historyInfo.txt");
	
	char sTxt[100];
	inf >> sTxt;
	int nSize;
	inf >> nSize;
	
	for(int nI = 0; nI < nSize; nI++)
	{
		CHistoryRecord* pHistoryRecord = new CHistoryRecord;
		int nRecID;
		inf >> nRecID;		
		inf >> pHistoryRecord->m_cStockNo;		
		inf >> pHistoryRecord->m_cStockName;		
		inf >> pHistoryRecord->m_dbClosePrice;		
		inf >> pHistoryRecord->m_dbOpenPrice;		
		inf >> pHistoryRecord->m_dbHiPrice;		
		inf >> pHistoryRecord->m_dbLowPrice;		
		inf >> pHistoryRecord->m_nQuantity;		
		inf >> pHistoryRecord->m_cDealDate;		
		// 读取多余的时间标识,不作使用
		char cTemp[20];
		inf >> cTemp;

		if( strcmp(pHistoryRecord->m_cStockNo,strStockNo) == 0 )
		{
			m_arrayHistoryInfo.Add(pHistoryRecord);
		}
		else
		{
			delete pHistoryRecord;
		}
	}

	int nCount = m_arrayHistoryInfo.GetSize();
	for(int nJ = 0;nJ < nCount;nJ++)
	{
		double dbAverPrice = 0;
		if(nJ == 0)
		{
			for(int nI = 0;nI < 3;nI++)
			{
				dbAverPrice += m_arrayHistoryInfo[nJ + nI]->m_dbClosePrice;
			}
			dbAverPrice /= 3;
		}
		else if(nJ == 1)
		{
			for(int nI = -1;nI < 3;nI++)
			{
				dbAverPrice += m_arrayHistoryInfo[nJ + nI]->m_dbClosePrice;
			}
			dbAverPrice /= 4;
		}
		else if(nJ == nCount - 1)
		{
				for(int nI = - 2;nI < 1;nI++)
			{
				dbAverPrice += m_arrayHistoryInfo[nJ + nI]->m_dbClosePrice;
			}
				dbAverPrice /= 3;
		}
		else if(nJ == nCount - 2)
		{
			for(int nI = - 2;nI < 2;nI++)
			{
				dbAverPrice += m_arrayHistoryInfo[nJ + nI]->m_dbClosePrice;
			}
			dbAverPrice /= 4;
		}
		else
		{			
			for(int nI = -2;nI < 3;nI++)
			{
				dbAverPrice += m_arrayHistoryInfo[nJ + nI]->m_dbClosePrice;
			}	
			dbAverPrice /= 5;
		}
		m_arrayHistoryPriceOfFiveDay.Add(dbAverPrice);
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CHistoryDoc commands

void CHistoryDoc::GetPriceRange(int nSel, int nCount)
{
	m_nHiQuantity = -1;
	m_dbLowPrice = 99999999999999;
	m_dbHiPrice = -1;
	for(int nI = 0;nI < nCount;nI++)
	{
		double dbHiPrice = m_arrayHistoryInfo[nI + nSel]->m_dbHiPrice;
		double dbLowPrice = m_arrayHistoryInfo[nI + nSel]->m_dbLowPrice;
		int nQuantity = m_arrayHistoryInfo[nI + nSel]->m_nQuantity;

		if(nQuantity > m_nHiQuantity)
		{
			m_nHiQuantity = nQuantity;
		}
		if(dbHiPrice > m_dbHiPrice)
		{
			m_dbHiPrice = dbHiPrice;
		}
		if(dbLowPrice < m_dbLowPrice)
		{
			m_dbLowPrice = dbLowPrice;
		}
	}
}
