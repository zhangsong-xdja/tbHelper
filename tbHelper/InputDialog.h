#pragma once


// CInputDialog �Ի���

class CInputDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog)

public:
	CInputDialog(CString c, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_INPUT };

private:
	CString caption;
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString content;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString getResult(void);
};
