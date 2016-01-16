
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������

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
	// TODO: �ڴ���������������
	CCommodityInfoDialog dlg;
	if(dlg.DoModal() != IDOK)
	{
		return ;
	}

	commodity & c = dlg.getCommodity();

	AfxMessageBox(db.insertCommodity(c) ? "�����Ʒ�ɹ�" : "�����Ʒʧ��");
}


void CMainFrame::OnUpdateCreateCommodity(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	
}


void CMainFrame::OnShowCommodity()
{
	// TODO: �ڴ���������������
	vector<commodity> cl;
	if(!db.getAllCommodity(cl))
	{
		AfxMessageBox("��ѯ������Ʒʧ��");
		return ;
	}

	CtbHelperView * pview = (CtbHelperView *)GetActiveView();
	pview->showCommodity(cl);

}


void CMainFrame::OnUpdateShowCommodity(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CMainFrame::OnCreateTask()
{
	// TODO: �ڴ���������������
	CTaskInfoDialog dlg;
	if(dlg.DoModal() != IDOK)
		return ;

	task t = dlg.getTask();
	AfxMessageBox(db.insertTask(t) ? "�������ɹ�" : "�������ʧ��");
}


void CMainFrame::OnUpdateCreateTask(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CMainFrame::OnShowTask()
{
	// TODO: �ڴ���������������
}


void CMainFrame::OnUpdateShowTask(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CMainFrame::OnShowTaskrecord()
{
	// TODO: �ڴ���������������
}


void CMainFrame::OnUpdateShowTaskrecord(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CMainFrame::OnRunTask()
{
	// TODO: �ڴ���������������
}


void CMainFrame::OnUpdateRunTask(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}


void CMainFrame::OnStopTask()
{
	// TODO: �ڴ���������������
}


void CMainFrame::OnUpdateStopTask(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
}
