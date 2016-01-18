
// tbHelperView.cpp : CtbHelperView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "tbHelper.h"
#endif

#include "tbHelperDoc.h"
#include "tbHelperView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtbHelperView

IMPLEMENT_DYNCREATE(CtbHelperView, CListView)

BEGIN_MESSAGE_MAP(CtbHelperView, CListView)
END_MESSAGE_MAP()

// CtbHelperView ����/����

CtbHelperView::CtbHelperView()
{
	// TODO: �ڴ˴���ӹ������

}

CtbHelperView::~CtbHelperView()
{
}

BOOL CtbHelperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

void CtbHelperView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��

	{
		CListCtrl & m_list = GetListCtrl();

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
	}
}


// CtbHelperView ���

#ifdef _DEBUG
void CtbHelperView::AssertValid() const
{
	CListView::AssertValid();
}

void CtbHelperView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CtbHelperDoc* CtbHelperView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtbHelperDoc)));
	return (CtbHelperDoc*)m_pDocument;
}
#endif //_DEBUG


// CtbHelperView ��Ϣ�������


void CtbHelperView::showCommodity(vector<commodity> & cl)
{
	CListCtrl & l = GetListCtrl();

	l.DeleteAllItems();

	while ( l.DeleteColumn (0));

	l.InsertColumn(0, "��ƷID", LVCFMT_CENTER, 38);
	l.InsertColumn(1, "��Ʒ����", LVCFMT_CENTER, 68);
	l.InsertColumn(2, "�����ؼ���", LVCFMT_CENTER, 168);
	l.InsertColumn(3, "ƥ��ؼ���", LVCFMT_CENTER, 168);

	for(int i = 0; i < cl.size(); i++)
	{
		CString id;
		id.Format("%lld", cl[i].id);
		l.InsertItem(i, id);

		l.SetItemText(i, 1, cl[i].name.c_str());

		CString conditions;
		for(int j = 0; j < cl[i].conditions.size(); j++)
		{
			conditions += cl[i].conditions[j].c_str();
			if(j < cl[i].conditions.size())
				conditions += ";";
		}
		l.SetItemText(i, 2, conditions);
		
		CString matchs;
		for(int j = 0; j < cl[i].matchs.size(); j++)
		{
			matchs += cl[i].matchs[j].c_str();
			if(j < cl[i].matchs.size())
				matchs += ";";
		}
		l.SetItemText(i, 3, matchs);
	}
}


void CtbHelperView::showTask(vector<task> & tl)
{
	CListCtrl & l = GetListCtrl();

	l.DeleteAllItems();

	while ( l.DeleteColumn (0));

	l.InsertColumn(0, "����ID", LVCFMT_CENTER, 88);
	l.InsertColumn(1, "��Ʒ����", LVCFMT_CENTER, 68);
	l.InsertColumn(2, "�Ƿ���������Ʒ", LVCFMT_CENTER, 188);
	l.InsertColumn(3, "��Ʒ�������", LVCFMT_CENTER, 88);
	l.InsertColumn(4, "��Ʒ���鷭������", LVCFMT_CENTER, 188);
	l.InsertColumn(5, "��Ʒ���۷�������", LVCFMT_CENTER, 188);
	l.InsertColumn(6, "�����Ʒ��������", LVCFMT_CENTER, 188);

	for(int i = 0; i < tl.size(); i++)
	{
		CString tmp;

		tmp.Format("%lld", tl[i].id);
		l.InsertItem(i, tmp);

		l.SetItemText(i, 1, tl[i].c.name.c_str());

		tmp.Format("%s", tl[i].random == 0 ? "��������" : "������");
		l.SetItemText(i, 2, tmp);

		tmp.Format("%d", tl[i].times);
		l.SetItemText(i, 3, tmp);

		tmp.Format("%d", tl[i].times_1);
		l.SetItemText(i, 4, tmp);

		tmp.Format("%d", tl[i].times_2);
		l.SetItemText(i, 5, tmp);

		tmp.Format("%d", tl[i].times_3);
		l.SetItemText(i, 6, tmp);
	}
}
