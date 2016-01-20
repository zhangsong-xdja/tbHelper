
// tbHelperView.h : CtbHelperView 类的接口
//

#pragma once

#include "dbOperator.h"
#include "tbHelperDoc.h"


class CtbHelperView : public CListView
{
protected: // 仅从序列化创建
	CtbHelperView();
	DECLARE_DYNCREATE(CtbHelperView)

// 特性
public:
	CtbHelperDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CtbHelperView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	enum ViewStates
	{
		STAT_NULL,
		STAT_COMMODITY,
		STAT_TASK,
		STAT_TASKRECORD,
		STAT_MAX
	} m_currentState;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	void showCommodity(vector<commodity> & cl);
	void showTask(vector<task> & tl);
	int getSelectedCommodityID(void);
	int getSelectedTaskID(void);
};

#ifndef _DEBUG  // tbHelperView.cpp 中的调试版本
inline CtbHelperDoc* CtbHelperView::GetDocument() const
   { return reinterpret_cast<CtbHelperDoc*>(m_pDocument); }
#endif

