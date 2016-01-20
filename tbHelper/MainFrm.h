
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "dbOperator.h"

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	dbOperator db;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
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


