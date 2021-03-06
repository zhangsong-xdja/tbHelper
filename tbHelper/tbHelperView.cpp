
// tbHelperView.cpp : CtbHelperView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CtbHelperView 构造/析构

CtbHelperView::CtbHelperView()
{
	// TODO: 在此处添加构造代码

}

CtbHelperView::~CtbHelperView()
{
}

BOOL CtbHelperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CtbHelperView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。

	{
		CListCtrl & m_list = GetListCtrl();

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
	}

	m_currentState = STAT_NULL;
}


// CtbHelperView 诊断

#ifdef _DEBUG
void CtbHelperView::AssertValid() const
{
	CListView::AssertValid();
}

void CtbHelperView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CtbHelperDoc* CtbHelperView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtbHelperDoc)));
	return (CtbHelperDoc*)m_pDocument;
}
#endif //_DEBUG


// CtbHelperView 消息处理程序


void CtbHelperView::showCommodity(vector<commodity> & cl)
{
	m_currentState = STAT_COMMODITY;

	CListCtrl & l = GetListCtrl();

	l.DeleteAllItems();

	while ( l.DeleteColumn (0));

	l.InsertColumn(0, "商品ID", LVCFMT_CENTER, 38);
	l.InsertColumn(1, "商品名称", LVCFMT_CENTER, 68);
	l.InsertColumn(2, "搜索关键字", LVCFMT_CENTER, 168);
	l.InsertColumn(3, "匹配关键字", LVCFMT_CENTER, 168);
	l.InsertColumn(4, "商品分享", LVCFMT_CENTER, 168);
	l.InsertColumn(5, "商品连接", LVCFMT_CENTER, 168);

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
		l.SetItemText(i, 4, cl[i].share.c_str());
		l.SetItemText(i, 5, cl[i].link.c_str());

		l.SetItemData(i, cl[i].id);
	}
}


void CtbHelperView::showTask(vector<task> & tl)
{
	m_currentState = STAT_TASK;

	CListCtrl & l = GetListCtrl();

	l.DeleteAllItems();

	while ( l.DeleteColumn (0));

	l.InsertColumn(0, "任务ID", LVCFMT_CENTER, 88);
	l.InsertColumn(1, "任务名称", LVCFMT_CENTER, 68);
	l.InsertColumn(2, "是否随机浏览商品", LVCFMT_CENTER, 188);
	l.InsertColumn(3, "商品浏览次数", LVCFMT_CENTER, 88);
	l.InsertColumn(4, "商品详情翻动次数", LVCFMT_CENTER, 188);
	l.InsertColumn(5, "商品评价翻动次数", LVCFMT_CENTER, 188);
	l.InsertColumn(6, "随机商品翻动次数", LVCFMT_CENTER, 188);
	l.InsertColumn(7, "任务进度", LVCFMT_CENTER, 88);
	l.InsertColumn(7, "商品名称", LVCFMT_CENTER, 88);

	for(int i = 0; i < tl.size(); i++)
	{
		CString tmp;

		tmp.Format("%lld", tl[i].id);
		l.InsertItem(i, tmp);

		l.SetItemText(i, 1, tl[i].name.c_str());

		tmp.Format("%s", tl[i].random == 0 ? "不随机浏览" : "随机浏览");
		l.SetItemText(i, 2, tmp);

		tmp.Format("%d", tl[i].times);
		l.SetItemText(i, 3, tmp);

		tmp.Format("%d", tl[i].times_1);
		l.SetItemText(i, 4, tmp);

		tmp.Format("%d", tl[i].times_2);
		l.SetItemText(i, 5, tmp);

		tmp.Format("%d", tl[i].times_3);
		l.SetItemText(i, 6, tmp);

		tmp.Format("%d %%100", tl[i].rate_of_progress);
		l.SetItemText(i, 7, tmp);

		l.SetItemText(i, 8, tl[i].c.name.c_str());

		l.SetItemData(i, tl[i].id);
	}
}


int CtbHelperView::getSelectedCommodityID(void)
{
	if(m_currentState != STAT_COMMODITY)
		return -1;
	
	CListCtrl & l = GetListCtrl();

	for(int i=0; i<l.GetItemCount(); i++)
	{
		if( l.GetCheck(i))
		{
			return l.GetItemData(i);
		}
	}

	return -1;
}


int CtbHelperView::getSelectedTaskID(void)
{
	if(m_currentState != STAT_TASK)
		return -1;
	
	CListCtrl & l = GetListCtrl();

	for(int i=0; i<l.GetItemCount(); i++)
	{
		if( l.GetCheck(i))
		{
			return l.GetItemData(i);
		}
	}

	return -1;

}


void CtbHelperView::showRecord(vector<taskRecord> & rl)
{
	m_currentState = STAT_TASK;

	CListCtrl & l = GetListCtrl();

	l.DeleteAllItems();

	while ( l.DeleteColumn (0));

	l.InsertColumn(0, "任务开始时间", LVCFMT_CENTER, 88);
	l.InsertColumn(1, "任务完成时间", LVCFMT_CENTER, 88);
	l.InsertColumn(2, "任务执行结果", LVCFMT_CENTER, 188);
	l.InsertColumn(3, "任务执行描述", LVCFMT_CENTER, 288);
	
	for(int i = 0; i < rl.size(); i++)
	{
		CString tmp;

		l.InsertItem(i, rl[i].begin_time.c_str());

		l.SetItemText(i, 1, rl[i].finish_time.c_str());

		tmp.Format("%s", rl[i].status == 0 ? "执行失败" : "执行成功");
		l.SetItemText(i, 2, tmp);

		l.SetItemText(i, 3, rl[i].describe.c_str());
	}
}
