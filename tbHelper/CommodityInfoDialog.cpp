// CommodityInfoDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tbHelper.h"
#include "CommodityInfoDialog.h"
#include "afxdialogex.h"
#include "InputDialog.h"


// CCommodityInfoDialog �Ի���

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


// CCommodityInfoDialog ��Ϣ�������


void CCommodityInfoDialog::OnBnClickedButtonAddCondition()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CInputDialog dlg("���������ؼ���", this);

	if(dlg.DoModal() == IDOK)
	{
		conditionList.InsertItem(0, dlg.getResult());
	}
}


void CCommodityInfoDialog::OnBnClickedButtonDelCondition()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CInputDialog dlg("����ƥ��ؼ���", this);

	if(dlg.DoModal() == IDOK)
	{
		matchList.InsertItem(0, dlg.getResult());
	}
}


void CCommodityInfoDialog::OnBnClickedButtonDelMatch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
		lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
		lStyle |= LVS_REPORT; //����style
		SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//����style

		DWORD dwStyle = m_list.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
		dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
		m_list.SetExtendedStyle(dwStyle); //������չ���

		m_list.InsertColumn( 0, "�����ؼ���", LVCFMT_CENTER, 168);//������

		m_list.InsertItem(0, "��������");
	}

	{
		CListCtrl & m_list = matchList;

		LONG lStyle;
		lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
		lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
		lStyle |= LVS_REPORT; //����style
		SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//����style

		DWORD dwStyle = m_list.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
		dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
		m_list.SetExtendedStyle(dwStyle); //������չ���

		m_list.InsertColumn( 0, "ƥ��ؼ���", LVCFMT_LEFT, 168);//������

		m_list.InsertItem(0, "����ƥ��");
	}

	name = "������Ʒ";
	UpdateData(0);

	return TRUE;
}


void CCommodityInfoDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(name.GetLength() == 0 || matchList.GetItemCount() == 0 || conditionList.GetItemCount() == 0)
	{
		AfxMessageBox("��Ϣ��������");

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
