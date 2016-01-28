// WorkdInfoDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tbHelper.h"
#include "WorkdInfoDialog.h"
#include "afxdialogex.h"

#include "taobaoController.h"

// CWorkdInfoDialog �Ի���

IMPLEMENT_DYNAMIC(CWorkdInfoDialog, CDialogEx)

CWorkdInfoDialog::CWorkdInfoDialog(task & t, CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkdInfoDialog::IDD, pParent)
	, m_t(t)
	, taskName(t.name.c_str())
	, is_random((BOOL)t.random)
	, tims(t.times)
	, tims_1(t.times_1)
	, times_2(t.times_2)
	, times_3(t.times_3)
	, commodityName(t.c.name.c_str())
{

}

CWorkdInfoDialog::~CWorkdInfoDialog()
{
}

void CWorkdInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, taskName);
	DDX_Check(pDX, IDC_CHECK1, is_random);
	DDX_Text(pDX, IDC_EDIT2, tims);
	DDX_Text(pDX, IDC_EDIT3, tims_1);
	DDX_Text(pDX, IDC_EDIT4, times_2);
	DDX_Text(pDX, IDC_EDIT6, times_3);
	DDX_Text(pDX, IDC_EDIT1, commodityName);
	DDX_Control(pDX, IDC_LIST2, matchList);
	DDX_Control(pDX, IDC_LIST3, conditionList);
	DDX_Control(pDX, IDC_PROGRESS1, process);
	DDX_Control(pDX, IDC_LIST1, log);
}


BEGIN_MESSAGE_MAP(CWorkdInfoDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CWorkdInfoDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWorkdInfoDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWorkdInfoDialog ��Ϣ�������


BOOL CWorkdInfoDialog::OnInitDialog()
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
		m_list.SetExtendedStyle(dwStyle); //������չ���

		m_list.InsertColumn( 0, "�����ؼ���", LVCFMT_CENTER, 168);//������

		for(int i = 0; i < m_t.c.conditions.size(); i++)
			m_list.InsertItem(i, m_t.c.conditions[i].c_str());
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
		m_list.SetExtendedStyle(dwStyle); //������չ���

		m_list.InsertColumn( 0, "ƥ��ؼ���", LVCFMT_LEFT, 168);//������

		for(int i = 0; i < m_t.c.matchs.size(); i++)
			m_list.InsertItem(i, m_t.c.matchs[i].c_str());
	}

	{
		CListCtrl & m_list = log;

		LONG lStyle;
		lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
		lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
		lStyle |= LVS_REPORT; //����style
		SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//����style

		DWORD dwStyle = m_list.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
		m_list.SetExtendedStyle(dwStyle); //������չ���

		m_list.InsertColumn( 0, "������־", LVCFMT_LEFT, 368 * 2 + 16);//������

	}
	
	return TRUE;
}


void CWorkdInfoDialog::OnBnClickedOk()
{
	//��ʼˢ�ձ��Ĵ���
	taobaoController tc(this);
	tc.run();
}


void CWorkdInfoDialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CWorkdInfoDialog::outputInfor(const char * str)
{
	log.InsertItem(log.GetItemCount(), str);
	log.EnsureVisible(log.GetItemCount(), true);
}
