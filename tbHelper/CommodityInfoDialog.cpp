// CommodityInfoDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "tbHelper.h"
#include "CommodityInfoDialog.h"
#include "afxdialogex.h"
#include "InputDialog.h"


// CCommodityInfoDialog 对话框

IMPLEMENT_DYNAMIC(CCommodityInfoDialog, CDialogEx)

CCommodityInfoDialog::CCommodityInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommodityInfoDialog::IDD, pParent)
	, name(_T(""))
{

}

CCommodityInfoDialog::~CCommodityInfoDialog()
{
}

void CCommodityInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, conditionList);
	DDX_Control(pDX, IDC_LIST2, matchList);
	DDX_Text(pDX, IDC_EDIT_NAME, name);
}


BEGIN_MESSAGE_MAP(CCommodityInfoDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CONDITION, &CCommodityInfoDialog::OnBnClickedButtonAddCondition)
	ON_BN_CLICKED(IDC_BUTTON_DEL_CONDITION, &CCommodityInfoDialog::OnBnClickedButtonDelCondition)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MATCH, &CCommodityInfoDialog::OnBnClickedButtonAddMatch)
	ON_BN_CLICKED(IDC_BUTTON_DEL_MATCH, &CCommodityInfoDialog::OnBnClickedButtonDelMatch)
	ON_BN_CLICKED(IDOK, &CCommodityInfoDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCommodityInfoDialog 消息处理程序


void CCommodityInfoDialog::OnBnClickedButtonAddCondition()
{
	// TODO: 在此添加控件通知处理程序代码
	CInputDialog dlg("输入搜索关键字", this);

	if(dlg.DoModal() == IDOK)
	{
		conditionList.InsertItem(0, dlg.getResult());
	}
}


void CCommodityInfoDialog::OnBnClickedButtonDelCondition()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl & m_list = conditionList;

	CString str;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if( m_list.GetCheck(i))
		{
			m_list.DeleteItem(i);
			i--;
		}
	}
}


void CCommodityInfoDialog::OnBnClickedButtonAddMatch()
{
	// TODO: 在此添加控件通知处理程序代码
	CInputDialog dlg("输入匹配关键字", this);

	if(dlg.DoModal() == IDOK)
	{
		matchList.InsertItem(0, dlg.getResult());
	}
}


void CCommodityInfoDialog::OnBnClickedButtonDelMatch()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl & m_list = matchList;

	CString str;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if( m_list.GetCheck(i))
		{
			m_list.DeleteItem(i);
			i--;
		}
	}
}


BOOL CCommodityInfoDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	{
		CListCtrl & m_list = conditionList;

		LONG lStyle;
		lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//获取当前窗口style
		lStyle &= ~LVS_TYPEMASK; //清除显示方式位
		lStyle |= LVS_REPORT; //设置style
		SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//设置style

		DWORD dwStyle = m_list.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
		dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
		dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
		m_list.SetExtendedStyle(dwStyle); //设置扩展风格

		m_list.InsertColumn( 0, "搜索关键字", LVCFMT_CENTER, 168);//插入列

		m_list.InsertItem(0, "测试搜索");
	}

	{
		CListCtrl & m_list = matchList;

		LONG lStyle;
		lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//获取当前窗口style
		lStyle &= ~LVS_TYPEMASK; //清除显示方式位
		lStyle |= LVS_REPORT; //设置style
		SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//设置style

		DWORD dwStyle = m_list.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
		dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
		dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
		m_list.SetExtendedStyle(dwStyle); //设置扩展风格

		m_list.InsertColumn( 0, "匹配关键字", LVCFMT_LEFT, 168);//插入列

		m_list.InsertItem(0, "测试匹配");
	}

	name = "测试商品";
	UpdateData(0);

	return TRUE;
}


void CCommodityInfoDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(name.GetLength() == 0 || matchList.GetItemCount() == 0 || conditionList.GetItemCount() == 0)
	{
		AfxMessageBox("信息不完整！");

		return ;
	}

	c.id = 0;
	c.name = name.GetBuffer(0);

	for(int i = 0; i < conditionList.GetItemCount(); i++)
	{
		c.conditions.push_back(conditionList.GetItemText(i, 0).GetBuffer(0));
	}

	for(int i = 0; i < matchList.GetItemCount(); i++)
	{
		c.matchs.push_back(matchList.GetItemText(i, 0).GetBuffer(0));
	}

	CDialogEx::OnOK();
}


commodity & CCommodityInfoDialog::getCommodity(void)
{
	return c;
}
