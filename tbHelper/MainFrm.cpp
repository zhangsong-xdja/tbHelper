
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "tbHelper.h"

#include "MainFrm.h"
#include "CommodityInfoDialog.h"
#include "TaskInfoDialog.h"

#include "tbHelperView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_CREATE_COMMODITY, &CMainFrame::OnCreateCommodity)
	ON_UPDATE_COMMAND_UI(ID_CREATE_COMMODITY, &CMainFrame::OnUpdateCreateCommodity)
	ON_COMMAND(ID_SHOW_COMMODITY, &CMainFrame::OnShowCommodity)
	ON_UPDATE_COMMAND_UI(ID_SHOW_COMMODITY, &CMainFrame::OnUpdateShowCommodity)
	ON_COMMAND(ID_CREATE_TASK, &CMainFrame::OnCreateTask)
	ON_UPDATE_COMMAND_UI(ID_CREATE_TASK, &CMainFrame::OnUpdateCreateTask)
	ON_COMMAND(ID_SHOW_TASK, &CMainFrame::OnShowTask)
	ON_UPDATE_COMMAND_UI(ID_SHOW_TASK, &CMainFrame::OnUpdateShowTask)
	ON_COMMAND(ID_SHOW_TASKRECORD, &CMainFrame::OnShowTaskrecord)
	ON_UPDATE_COMMAND_UI(ID_SHOW_TASKRECORD, &CMainFrame::OnUpdateShowTaskrecord)
	ON_COMMAND(ID_RUN_TASK, &CMainFrame::OnRunTask)
	ON_UPDATE_COMMAND_UI(ID_RUN_TASK, &CMainFrame::OnUpdateRunTask)
	ON_COMMAND(ID_STOP_TASK, &CMainFrame::OnStopTask)
	ON_UPDATE_COMMAND_UI(ID_STOP_TASK, &CMainFrame::OnUpdateStopTask)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	db.createDatabase();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}



void CMainFrame::OnCreateCommodity()
{
	// TODO: 在此添加命令处理程序代码
	CCommodityInfoDialog dlg;
	if(dlg.DoModal() != IDOK)
	{
		return ;
	}

	commodity & c = dlg.getCommodity();

	AfxMessageBox(db.insertCommodity(c) ? "添加商品成功" : "添加商品失败");
}


void CMainFrame::OnUpdateCreateCommodity(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	
}


void CMainFrame::OnShowCommodity()
{
	// TODO: 在此添加命令处理程序代码
	vector<commodity> cl;
	if(!db.getAllCommodity(cl))
	{
		AfxMessageBox("查询所有商品失败");
		return ;
	}

	CtbHelperView * pview = (CtbHelperView *)GetActiveView();
	pview->showCommodity(cl);

}


void CMainFrame::OnUpdateShowCommodity(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnCreateTask()
{
	// TODO: 在此添加命令处理程序代码
	CTaskInfoDialog dlg;
	if(dlg.DoModal() != IDOK)
		return ;

	task t = dlg.getTask();
	AfxMessageBox(db.insertTask(t) ? "添加任务成功" : "添加任务失败");
}


void CMainFrame::OnUpdateCreateTask(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnShowTask()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateShowTask(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnShowTaskrecord()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateShowTaskrecord(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnRunTask()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateRunTask(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnStopTask()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateStopTask(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
