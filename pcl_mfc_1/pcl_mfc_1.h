
// pcl_mfc_1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cpcl_mfc_1App:
// �йش����ʵ�֣������ pcl_mfc_1.cpp
//

class Cpcl_mfc_1App : public CWinApp
{
public:
	Cpcl_mfc_1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cpcl_mfc_1App theApp;