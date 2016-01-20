
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "dbOperator.h"

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	dbOperator db;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCreateCommodity();
	afx_msg void OnUpdateCreateCommodity(CCmdUI *pCmdUI);
	afx_msg void OnShowCommodity();
	afx_msg void OnUpdateShowCommodity(CCmdUI *pCmdUI);
	afx_msg void OnCreateTask();
	afx_msg void OnUpdateCreateTask(CCmdUI *pCmdUI);
	afx_msg void OnShowTask();
	afx_msg void OnUpdateShowTask(CCmdUI *pCmdUI);
	afx_msg void OnShowTaskrecord();
	afx_msg void OnUpdateShowTaskrecord(CCmdUI *pCmdUI);
	afx_msg void OnRunTask();
	afx_msg void OnUpdateRunTask(CCmdUI *pCmdUI);
	afx_msg void OnStopTask();
	afx_msg void OnUpdateStopTask(CCmdUI *pCmdUI);
	afx_msg void OnDeleteCommodity();
	afx_msg void OnUpdateDeleteCommodity(CCmdUI *pCmdUI);
	afx_msg void OnDeleteTask();
	afx_msg void OnUpdateDeleteTask(CCmdUI *pCmdUI);
};


