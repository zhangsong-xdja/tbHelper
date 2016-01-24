// TaskInfoDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "tbHelper.h"
#include "TaskInfoDialog.h"
#include "afxdialogex.h"

#include "dbOperator.h"


// CTaskInfoDialog 对话框

IMPLEMENT_DYNAMIC(CTaskInfoDialog, CDialogEx)

CTaskInfoDialog::CTaskInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTaskInfoDialog::IDD, pParent)
	, m_random(TRUE)
	, m_times(1)
	, m_times_1(15)
	, m_times_2(10)
	, m_times_3(5)
	, taskName(_T("测试任务"))
{

}

CTaskInfoDialog::~CTaskInfoDialog()
{
}

void CTaskInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_random);
	DDX_Text(pDX, IDC_EDIT1, m_times);
	DDV_MinMaxInt(pDX, m_times, 1, 500);
	DDX_Text(pDX, IDC_EDIT2, m_times_1);
	DDV_MinMaxInt(pDX, m_times_1, 1, 600);
	DDX_Text(pDX, IDC_EDIT3, m_times_2);
	DDV_MinMaxInt(pDX, m_times_2, 1, 600);
	DDX_Text(pDX, IDC_EDIT4, m_times_3);
	DDV_MinMaxInt(pDX, m_times_3, 1, 600);
	DDX_Control(pDX, IDC_COMBO1, m_infos);
	DDX_Text(pDX, IDC_EDIT5, taskName);
	DDV_MaxChars(pDX, taskName, 60);
}


BEGIN_MESSAGE_MAP(CTaskInfoDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTaskInfoDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CTaskInfoDialog 消息处理程序


BOOL CTaskInfoDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	dbOperator db;

	if(!db.getAllCommodity(cl))
	{
		AfxMessageBox("没有可用商品");
		return FALSE;
	}

	for(int i = 0; i < cl.size(); i++)
		m_infos.AddString(cl[i].name.c_str());

	m_infos.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CTaskInfoDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_infos.GetCurSel();

	if(index < 0)
	{
		AfxMessageBox("必须选择一个商品");
		CDialogEx::OnCancel();
		return ;
	}
	UpdateData();

	result.name = taskName.GetBuffer(0);
	result.c.id = cl[index].id;
	result.c.name = cl[index].name;
	result.random = m_random;
	result.times = m_times;
	result.times_1 = m_times_1;
	result.times_2 = m_times_2;
	result.times_3 = m_times_3;

	CDialogEx::OnOK();
}


task & CTaskInfoDialog::getTask(void)
{
	//TODO: insert return statement here

	return result;
}
