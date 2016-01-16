#pragma once


// CTaskInfoDialog 对话框

class CTaskInfoDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskInfoDialog)

public:
	CTaskInfoDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskInfoDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_TASK_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
