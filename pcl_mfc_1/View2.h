#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "afx.h"
class CView2 :	public CScrollView
{
public:
	CView2(void);
	~CView2(void);
	void OnDraw(CDC* pDC);
};

//IMPLEMENT_DYNCREATE(CView2,CView) 
