#pragma once
#include "afxwin.h"

#include "dbOperator.h"


// CTaskInfoDialog �Ի���

class CTaskInfoDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskInfoDialog)

public:
	CTaskInfoDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskInfoDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_TASK_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_random;
	int m_times;
	int m_times_1;
	int m_times_2;
	int m_times_3;
	CComboBox m_infos;
	vector<commodity> cl;

	task result;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	task & getTask(void);
	CString taskName;
};
