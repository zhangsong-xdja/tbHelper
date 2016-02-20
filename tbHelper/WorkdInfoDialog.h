#pragma once
#include "afxcmn.h"

#include "dbOperator.h"
#include "taobaoController.h"
#include "commandManager.h"
#include "vpnController.h"
#include "netQuality.h"

#include "resource.h"


// CWorkdInfoDialog 对话框

class CWorkdInfoDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkdInfoDialog)

public:
	CWorkdInfoDialog(task & t, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkdInfoDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_WORK_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	task & m_t;
	taobaoController tc;
	commandManager cm;
	vpnController vc;

	CString taskName;
	BOOL is_random;
	int tims;
	int tims_1;
	int times_2;
	int times_3;
	CString commodityName;
	CListCtrl matchList;
	CListCtrl conditionList;
	virtual BOOL OnInitDialog();
	CProgressCtrl process;
	CListCtrl log;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void outputInfor(const char * str);
	void beginWork(void);
	void finishWork(void);
	void addProcessPos(void);
	BOOL m_mbVpn;
};
