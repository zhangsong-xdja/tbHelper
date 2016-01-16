#pragma once


// CInputDialog 对话框

class CInputDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog)

public:
	CInputDialog(CString c, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_INPUT };

private:
	CString caption;
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString content;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString getResult(void);
};
