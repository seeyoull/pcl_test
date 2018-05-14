#include "StdAfx.h"
#include "View2.h"


CView2::CView2(void)
{
}


CView2::~CView2(void)
{
}

void CView2::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	CRect rt(0, 50, 200, 200);
	pDC->DrawText(_T("这是在对话框上创建的视图"), &rt, DT_LEFT);
}