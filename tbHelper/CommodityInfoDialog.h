#pragma once
#include "afxcmn.h"
#include "dbOperator.h"


// CCommodityInfoDialog �Ի���

class CCommodityInfoDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCommodityInfoDialog)

public:
	CCommodityInfoDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommodityInfoDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_COMMODITY_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	commodity c;

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl conditionList;
	CListCtrl matchList;
	CString name;
	afx_msg void OnBnClickedButtonAddCondition();
	afx_msg void OnBnClickedButtonDelCondition();
	afx_msg void OnBnClickedButtonAddMatch();
	afx_msg void OnBnClickedButtonDelMatch();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	commodity & getCommodity(void);
	CString share;
	CString link;
};
