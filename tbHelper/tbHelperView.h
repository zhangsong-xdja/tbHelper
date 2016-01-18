
// tbHelperView.h : CtbHelperView ��Ľӿ�
//

#pragma once

#include "dbOperator.h"
#include "tbHelperDoc.h"


class CtbHelperView : public CListView
{
protected: // �������л�����
	CtbHelperView();
	DECLARE_DYNCREATE(CtbHelperView)

// ����
public:
	CtbHelperDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CtbHelperView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	void showCommodity(vector<commodity> & cl);
	void showTask(vector<task> & tl);
};

#ifndef _DEBUG  // tbHelperView.cpp �еĵ��԰汾
inline CtbHelperDoc* CtbHelperView::GetDocument() const
   { return reinterpret_cast<CtbHelperDoc*>(m_pDocument); }
#endif

