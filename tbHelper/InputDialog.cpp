// InputDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tbHelper.h"
#include "InputDialog.h"
#include "afxdialogex.h"


// CInputDialog �Ի���

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


// CInputDialog ��Ϣ�������


BOOL CInputDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(caption);

	return TRUE;
}


void CInputDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	CDialogEx::OnOK();
}


CString CInputDialog::getResult(void)
{
	return content;
}
