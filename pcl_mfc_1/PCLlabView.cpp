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
    m_iren = vtkRenderWindowInteractor::New();//���������ַ
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
	//m_viewer.removeAllPointClouds();//�ú�����������ʾ

	//��ʾ��ͬ����pcd�ļ�
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
	m_viewer.resetCamera();//ʹ������ʾ����Ļ�м䣬�������Ĳ���
 
	CRect rect;
	GetClientRect(&rect);//ʵʱ��ȡMFC���ڴ�С
	m_win = m_viewer.getRenderWindow();
	m_win->SetSize(rect.right-rect.left,rect.bottom-rect.top);
	m_win->SetParentId(this->m_hWnd);//��vtk���ڽ�ϵ�MFC������
	m_iren->SetRenderWindow(m_win);
	m_viewer.createInteractor();//���ڳ�ʼ������Ϊfalse���ô����´���PCL����Interactor
 
	m_win->Render();
}


