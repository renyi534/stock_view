// HistoryRecord.h: interface for the CHistoryRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYRECORD_H__AD4D5C03_1BD9_42C8_B608_36B0B433F6B2__INCLUDED_)
#define AFX_HISTORYRECORD_H__AD4D5C03_1BD9_42C8_B608_36B0B433F6B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHistoryRecord : public CObject  
{
public:
	CHistoryRecord();
	virtual ~CHistoryRecord();

	public:
	char m_cDealDate[100];		//��������
	int m_nQuantity;			//�ɽ���
	double m_dbLowPrice;		//��ͼ�
	double m_dbHiPrice;			//��߼�
	double m_dbOpenPrice;		//���̼�
	double m_dbClosePrice;		//���̼�
	char m_cStockName[100];		//��Ʊ����
	char m_cStockNo[100];		//��Ʊ����
};
	

#endif // !defined(AFX_HISTORYRECORD_H__AD4D5C03_1BD9_42C8_B608_36B0B433F6B2__INCLUDED_)
