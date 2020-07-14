
// TestErrorStream.h : TestErrorStream 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CTestErrorStreamApp:
// 有关此类的实现，请参阅 TestErrorStream.cpp
//

class CTestErrorStreamApp : public CWinAppEx
{
public:
	CTestErrorStreamApp();


	// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	CWinThread* m_pThread_TCP;
	void TCPCreatThread(void);			
	friend UINT TCPThreadProc(LPVOID pm);
	static int CALLBACK TransformClass(int *pInfo); //par
};

extern CTestErrorStreamApp theApp;
