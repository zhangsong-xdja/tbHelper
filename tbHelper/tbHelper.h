
// tbHelper.h : tbHelper Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CtbHelperApp:
// �йش����ʵ�֣������ tbHelper.cpp
//

class CtbHelperApp : public CWinApp
{
public:
	CtbHelperApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtbHelperApp theApp;
