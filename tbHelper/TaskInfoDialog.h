#pragma once


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
};
