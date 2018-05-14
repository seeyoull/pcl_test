
// pcl_mfc_1Dlg.h : ͷ�ļ�
//
#include "View2.h"
//#include "PCLlabView.h"

#pragma once


// Cpcl_mfc_1Dlg �Ի���
class Cpcl_mfc_1Dlg : public CDialogEx
{
// ����
public:
	Cpcl_mfc_1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	CView2 *m_pView1;  
	//CPCLlabView *m_pView2;  

// �Ի�������
	enum { IDD = IDD_PCL_MFC_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButton2();
};
