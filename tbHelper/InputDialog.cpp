// InputDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "tbHelper.h"
#include "InputDialog.h"
#include "afxdialogex.h"


// CInputDialog 对话框

IMPLEMENT_DYNAMIC(CInputDialog, CDialogEx)

CInputDialog::CInputDialog(CString c, CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputDialog::IDD, pParent)
	, content(_T(""))
	, caption(c)
{

}

CInputDialog::~CInputDialog()
{
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, content);
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputDialog 消息处理程序


BOOL CInputDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(caption);

	return TRUE;
}


void CInputDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	CDialogEx::OnOK();
}


CString CInputDialog::getResult(void)
{
	return content;
}
