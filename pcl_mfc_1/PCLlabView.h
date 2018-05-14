#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "afxext.h"
#include "afx.h"
#include <pcl/visualization/cloud_viewer.h>  
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h> 
#include <pcl/visualization/pcl_visualizer.h>


class CPCLlabView :	public CScrollView
{
public:
       //pcl::PCLPointCloud2::Ptr m_cloud;
	   //pcl::PointCloud<pcl::PointXYZ> m_cloud;
       pcl::visualization::PCLVisualizer m_viewer("PCL", false);
       vtkSmartPointer<vtkRenderWindow> m_win;
       vtkSmartPointer<vtkRenderWindowInteractor> m_iren;
public:
	CPCLlabView(void);
	~CPCLlabView(void);
	void OnDraw(CDC* pDC);
};