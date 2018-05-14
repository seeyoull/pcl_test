
// pcl_mfc_1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pcl_mfc_1.h"
#include "pcl_mfc_1Dlg.h"
#include "afxdialogex.h"
#include <pcl/visualization/cloud_viewer.h>  
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h> 
#include "pcl_test.h"
#include "myFunction.h"
#include "View2.h"
//#include "PCLlabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define CVIWER_MACRO

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Cpcl_mfc_1Dlg 对话框




Cpcl_mfc_1Dlg::Cpcl_mfc_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cpcl_mfc_1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cpcl_mfc_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cpcl_mfc_1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cpcl_mfc_1Dlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST2, &Cpcl_mfc_1Dlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON2, &Cpcl_mfc_1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cpcl_mfc_1Dlg 消息处理程序

BOOL Cpcl_mfc_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef CVIWER_MACRO
	UINT TargetCtrID = IDC_STATIC;
	CWnd * pWnd = this->GetDlgItem(TargetCtrID);
	CRect RectTargetCtrl;
	pWnd->GetWindowRect(RectTargetCtrl);
	pWnd->DestroyWindow();  
	this->ScreenToClient(RectTargetCtrl);

	//CRuntimeClass *pViewRuntimeClass=RUNTIME_CLASS(CView2);
	//m_pView1 = (CView2*)pViewRuntimeClass->CreateObject();
	//m_pView1 = (CView2*)RUNTIME_CLASS(CView2)->CreateObject();
	m_pView1 = new CView2;
	ASSERT(m_pView1 != NULL);

	if (!((CView*)m_pView1)->Create(NULL, NULL, WS_CHILD,
	CRect(0, 0, 0, 0), this, NULL, NULL))
	{
		AfxMessageBox(_T("Create view1 failed"));
		return TRUE;
	}

	m_pView1->ShowWindow(SW_HIDE);
	m_pView1->OnInitialUpdate();
	//m_pView1->DrawText(_T("blog.csdn.net/sjdev"));  
#endif
#ifdef CVIWER_MACRO1
	UINT TargetCtrID = IDC_STATIC;
	CWnd * pWnd = this->GetDlgItem(TargetCtrID);
	CRect RectTargetCtrl;
	pWnd->GetWindowRect(RectTargetCtrl);
	pWnd->DestroyWindow();  
	this->ScreenToClient(RectTargetCtrl);

	//CRuntimeClass *pViewRuntimeClass=RUNTIME_CLASS(CView2);
	//m_pView1 = (CView2*)pViewRuntimeClass->CreateObject();
	//m_pView1 = (CView2*)RUNTIME_CLASS(CView2)->CreateObject();
	m_pView2 = new CPCLlabView;
	ASSERT(m_pView2 != NULL);

	if (!((CView*)m_pView2)->Create(NULL, NULL, WS_CHILD,
	CRect(0, 0, 0, 0), this, NULL, NULL))
	{
		AfxMessageBox(_T("Create m_pView2 failed"));
		return TRUE;
	}
	CDC pDC;
	
	//m_pView2->ShowWindow(SW_HIDE);
	m_pView2->OnInitialUpdate();
	m_pView2->ShowWindow(SW_MAXIMIZE);
;
	//m_pView2->OnDraw(&pDC);
	//m_pView1->DrawText(_T("blog.csdn.net/sjdev"));  
#endif
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cpcl_mfc_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cpcl_mfc_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cpcl_mfc_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cpcl_mfc_1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here   
    // 设置过滤器   
    TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
    CString strFilePath;   
   
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
        strFilePath = fileDlg.GetPathName();   
        SetDlgItemText(IDC_STATIC, strFilePath);

		char preFileName[200];
		char postFileName[200];
		cstring2Char(strFilePath, preFileName);

		backslashCopy(preFileName, postFileName);

		//txt2Pcd(postFileName);
		txt2PcdNormalize(postFileName);
		//showViewer();
		showRtViewer();
    }   
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CDialogEx::OnOK();
}


void Cpcl_mfc_1Dlg::OnLbnSelchangeList2()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
}


void Cpcl_mfc_1Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here   
    // 设置过滤器   
    TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
    CString strFilePath;   
   
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
        strFilePath = fileDlg.GetPathName();   
        SetDlgItemText(IDC_STATIC, strFilePath);

		char preFileName[200];
		char postFileName[200];
		cstring2Char(strFilePath, preFileName);

		backslashCopy(preFileName, postFileName);

		//txt2Pcd(postFileName);
		txt2PcdNormalize4Color(postFileName);
		//showViewer();
		showViewerNew();
    }   
}
