#include "stdafx.h"
#include <pcl/visualization/cloud_viewer.h>  
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h> 
#include <pcl/visualization/pcl_visualizer.h>
#include "PCLlabView.h"

CPCLlabView::CPCLlabView()
{
    // TODO: addconstruction code here
	m_win = m_viewer.getRenderWindow();
    m_iren = vtkRenderWindowInteractor::New();//重新申请地址
}


CPCLlabView::~CPCLlabView(void)
{
}

void CPCLlabView::OnDraw(CDC* pDC)
{
	// TODO: adddraw code for native data here
	std::string filename ="tmp.pcd";
	pcl::PointCloud<pcl::PointXYZ>::Ptr m_cloud (new (pcl::PointCloud<pcl::PointXYZ>));
	if(pcl::io::loadPCDFile(filename,m_cloud ) == -1)// load the file
	{
			PCL_ERROR ("Couldn't read file");
	}
	m_viewer.setBackgroundColor( 0.0, 0.0,0.0 );
	//m_viewer.removeAllPointClouds();//该函数不加则不显示

	//显示不同类型pcd文件
	//Eigen::Vector4f sensor_origin =Eigen::Vector4f::Zero();
	//Eigen::Quaternionf sensor_orientation =Eigen::Quaternionf::Identity();
	//if(pcl::getFieldIndex(*m_cloud,"rgb") > 0)
	//{                         
	//	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGBA>::Ptr rgb_handler
	//			(new pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGBA>(m_cloud));
	//	m_viewer.addPointCloud(&m_cloud,rgb_handler, sensor_origin, sensor_orientation);
	//}
	//else
	{
		//pcl::visualization::PointCloudGeometryHandlerXYZ<pcl::PointXYZRGBA>::Ptr xyz_handler
		//			(new pcl::visualization::PointCloudGeometryHandlerXYZ<pcl::PointXYZRGBA>(*m_cloud));
		//m_viewer.addPointCloud(m_cloud,xyz_handler, sensor_origin, sensor_orientation);
		m_viewer.addPointCloud<pcl::PointXYZ> ((pcl::PointCloud<pcl::PointXYZ>::ConstPtr)&m_cloud,"sample cloud");
	}
	m_viewer.resetCamera();//使点云显示在屏幕中间，并绕中心操作
 
	CRect rect;
	GetClientRect(&rect);//实时获取MFC窗口大小
	m_win = m_viewer.getRenderWindow();
	m_win->SetSize(rect.right-rect.left,rect.bottom-rect.top);
	m_win->SetParentId(this->m_hWnd);//将vtk窗口结合到MFC窗口中
	m_iren->SetRenderWindow(m_win);
	m_viewer.createInteractor();//由于初始化设置为false，该处重新创建PCL风格的Interactor
 
	m_win->Render();
}


