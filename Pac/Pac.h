
// Pac.h : Pac ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CPacApp:
// �� Ŭ������ ������ ���ؼ��� Pac.cpp�� �����Ͻʽÿ�.
//

class CPacApp : public CWinAppEx
{
public:
	CPacApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPacApp theApp;
