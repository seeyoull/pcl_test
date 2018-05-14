#include "stdafx.h"
#include <pcl/visualization/cloud_viewer.h>  
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h> 
#include <boost\thread\thread.hpp>  
#include <stdlib.h>
#include <math.h>

using namespace boost;  

int user_data;  
  
void viewerOneOff (pcl::visualization::PCLVisualizer& viewer)  
{  
    viewer.setBackgroundColor (1.0, 0.5, 1.0);  
    pcl::PointXYZ o;  
    o.x = 1.0;  
    o.y = 0;  
    o.z = 0;  
    //viewer.addSphere (o, 0.25, "sphere", 0);  
    std::cout << "i only run once" << std::endl;  
  
}  
  
void viewerPsycho (pcl::visualization::PCLVisualizer& viewer)  
{  
    static unsigned count = 0;  
    std::stringstream ss;  
    ss << "Once per viewer loop: " << count++;  
    viewer.removeShape ("text", 0);  
    viewer.addText (ss.str(), 200, 300, "text", 0);  
  
    //FIXME: possible race condition here:  
    user_data++;  
} 

int numofPoints(char* fname){  
	int n=0;  
	int c=0;  
	FILE *fp;  
	fp = fopen(fname,"r");  
	do{  
		c = fgetc(fp);  
		if(c == '\n'){  
			++n;  
		}  
	}  
	while(c != EOF);  
	fclose(fp);  
	return n;  
}  
int txt2Pcd(char *fileName)  
{  
    int n = 1; //n用来计文件中点个数      
	FILE *fp_1;  
	fp_1 = fopen(fileName,"r");  
	n = numofPoints(fileName);//使用numofPoints函数计算文件中点个数  
	std::cout << "there are "<<n<<" points in the file..." <<std::endl;  
	//新建一个点云文件，然后将结构中获取的xyz值传递到点云指针cloud中。  
	pcl::PointCloud<pcl::PointXYZ> cloud;  
	cloud.width    = n;  
	cloud.height   = 1;  
	cloud.is_dense = false;  
	cloud.points.resize (cloud.width * cloud.height);  
	//将点云读入并赋给新建点云指针的xyz      
	double x,y,z;  
	int i = 0;  
	//int num = fscanf(fp_1,"%lf,%lf,%lf\n",&x,&y,&z);
	while(3 == fscanf(fp_1,"%lf%*c%lf%*c%lf\n",&x,&y,&z)){  
		//cout<<x<<" "<<y<<" "<<z<<endl;  
		cloud.points[i].x = x;  
		cloud.points[i].y = y;  
		cloud.points[i].z = z;  
		++i;  
	}  
	fclose(fp_1);  
	//将点云指针指向的内容传给pcd文件  
  
	pcl::io::savePCDFileASCII ("tmp.pcd", cloud);  
  
	std::cerr <<"Saved " << cloud.points.size () <<" data points to test_pcd.pcd." << std::endl;  
	//system("pause");  
  return 0;  

}

double myMax(double x, double y, double z)
{
	double maxValue, maxTmp1, maxTmp2;
	double x1, y1, z1;
	x1 = abs(x);
	y1 = abs(y);
	z1 = abs(z);

	maxTmp1 = (x1 > y1 ? x1 : y1);
	maxTmp2 = (x1 > z1 ? x1 : z1);
	maxValue = (maxTmp1 > maxTmp2 ? maxTmp1 : maxTmp2);

	return maxValue;
}
int txt2PcdNormalize(char *fileName)  
{  
    int n = 1; //n用来计文件中点个数    
	double maxValue = 0;
	double maxValueTmp;
	double ratio;

	FILE *fp_1;  
	fp_1 = fopen(fileName,"r");  
	n = numofPoints(fileName);//使用numofPoints函数计算文件中点个数  
	std::cout << "there are "<<n<<" points in the file..." <<std::endl;  
	//新建一个点云文件，然后将结构中获取的xyz值传递到点云指针cloud中。  
	pcl::PointCloud<pcl::PointXYZ> cloud;  
	cloud.width    = n;  
	cloud.height   = 1;  
	cloud.is_dense = false;  
	cloud.points.resize (cloud.width * cloud.height);  
	//将点云读入并赋给新建点云指针的xyz      
	double x,y,z;  
	int i = 0;  
	//int num = fscanf(fp_1,"%lf,%lf,%lf\n",&x,&y,&z);
	while(3 == fscanf(fp_1,"%lf%*c%lf%*c%lf\n",&x,&y,&z)){  
		//cout<<x<<" "<<y<<" "<<z<<endl;  
		cloud.points[i].x = x;  
		cloud.points[i].y = y;  
		cloud.points[i].z = z;  
		++i;  

		maxValueTmp = myMax(x, y, z);
		if(maxValue < maxValueTmp)
		{
			maxValue = maxValueTmp;
		}
	}

	ratio = 1 / maxValue * 0.25;

	for(int j = 0; j < i; j++)
	{
		cloud.points[j].x = cloud.points[j].x * ratio;
		cloud.points[j].y = cloud.points[j].y * ratio;
		cloud.points[j].z = cloud.points[j].z * ratio;
	}

	fclose(fp_1);  
	//将点云指针指向的内容传给pcd文件  
  
	pcl::io::savePCDFileASCII ("tmp.pcd", cloud);  
  
	std::cerr <<"Saved " << cloud.points.size () <<" data points to test_pcd.pcd." << std::endl;  
	//system("pause");  
  return 0;  

}

int txt2PcdNormalize4Color(char *fileName)  
{  
    int n = 1; //n用来计文件中点个数    
	double maxValue = 0;
	double maxValueZ = 0;
	double minValueZ = 0;
	double maxValueTmp;
	double ratio;
	double deltaRgb = 0;
	double tmpA;

	FILE *fp_1;  
	fp_1 = fopen(fileName,"r");  
	n = numofPoints(fileName);//使用numofPoints函数计算文件中点个数  
	std::cout << "there are "<<n<<" points in the file..." <<std::endl;  
	//新建一个点云文件，然后将结构中获取的xyz值传递到点云指针cloud中。  
	//pcl::PointCloud<pcl::PointXYZ> cloud; 
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	cloud->width    = n;  
	cloud->height   = 1;  
	cloud->is_dense = false;  
	cloud->points.resize (cloud->width * cloud->height);  
	//将点云读入并赋给新建点云指针的xyz      
	double x,y,z;  
	int i = 0;  
	uint8_t r(255), g(0), b(15);
	//int num = fscanf(fp_1,"%lf,%lf,%lf\n",&x,&y,&z);
	while(3 == fscanf(fp_1,"%lf%*c%lf%*c%lf\n",&x,&y,&z)){  
		//cout<<x<<" "<<y<<" "<<z<<endl;  
		cloud->points[i].x = x;  
		cloud->points[i].y = y;  
		cloud->points[i].z = z;  
		++i;  

		maxValueTmp = myMax(x, y, z);
		if(maxValue < maxValueTmp)
		{
			maxValue = maxValueTmp;
		}

		if(maxValueZ < z)
		{
			maxValueZ = z;
		}
		if(minValueZ > z)
		{
			minValueZ = z;
		}
	}

	tmpA = maxValueZ - minValueZ;

	ratio = 1 / maxValue * 0.25;
	deltaRgb = 255/tmpA;

	for(int j = 0; j < i; j++)
	{
		r = 255 * (-minValueZ / tmpA) + deltaRgb * cloud->points[j].z;
		g = 255 * (minValueZ / tmpA) - deltaRgb * cloud->points[j].z;

		cloud->points[j].x = cloud->points[j].x * ratio;
		cloud->points[j].y = cloud->points[j].y * ratio;
		cloud->points[j].z = cloud->points[j].z * ratio;

		//if (cloud->points[j].z < 0.0)

		//printf("%f %f %f\r\n", r, g, b);
		uint32_t rgb = (static_cast<uint32_t>(r) << 16 |
        static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
		cloud->points[j].rgb = *reinterpret_cast<float*>(&rgb);
	}

	fclose(fp_1);  
	//将点云指针指向的内容传给pcd文件  
  
	pcl::io::savePCDFileASCII ("tmp.pcd", *cloud);  
  
	std::cerr <<"Saved " << cloud->points.size () <<" data points to test_pcd.pcd." << std::endl;  
	//system("pause");  
    return 0;  

}

void showViewer()
{
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new (pcl::PointCloud<pcl::PointXYZRGBA>));  
	pcl::io::loadPCDFile ("tmp.pcd", *cloud);  
	//pcl::io::loadPCDFile ("my_point_cloud.pcd", *cloud);  
  
	pcl::visualization::CloudViewer viewer("Cloud Viewer");  
      
	//blocks until the cloud is actually rendered  
	viewer.showCloud(cloud);  
  
	//use the following functions to get access to the underlying more advanced/powerful  
	//PCLVisualizer  
  
	//This will only get called once  
	viewer.runOnVisualizationThreadOnce (viewerOneOff);  
  
	//This will get called once per visualization iteration  
	viewer.runOnVisualizationThread (viewerPsycho);  
	while (!viewer.wasStopped ())  
	{  
		//you can also do cool processing here  
		//FIXME: Note that this is running in a separate thread from viewerPsycho  
		//and you should guard against race conditions yourself...  
		user_data++;  
	} 
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> rgbVis (pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud)
{
	// --------------------------------------------
	// -----Open 3D viewer and add point cloud-----
	// --------------------------------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
	viewer->setBackgroundColor (0, 0, 0);
	/***************************************************************************************************************
	设置窗口的背景颜色后，创建一个颜色处理对象，PointCloudColorHandlerRGBField利用这样的对象显示自定义颜色数据，PointCloudColorHandlerRGBField
	对象得到每个点云的RGB颜色字段，
	**************************************************************************************************************/
  
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
	viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
	//viewer->addCoordinateSystem (1.0);
	viewer->initCameraParameters ();
	return (viewer);
}

boost::mutex updateModelMutex;

boost::shared_ptr<pcl::visualization::PCLVisualizer> simpleVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
        // --------------------------------------------
        // -----Open 3D viewer and add point cloud-----
        // --------------------------------------------
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
        //viewer->setCameraPosition(-2, -2, -2, -2, -2, -2, -1);
        viewer->setBackgroundColor(0, 0, 0);
		//viewer->setFullScreen(true);
        viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
        viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
        //viewer->addCoordinateSystem (1);
		viewer->initCameraParameters ();
        return (viewer);
}

void viewerRunner(boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer)
{
        while (!viewer->wasStopped ())
        {
               viewer->spinOnce (100);
               boost::this_thread::sleep (boost::posix_time::microseconds (100));
        }
}

bool iteration_flag = false;
bool leftMouse = false;

void keyboardEventOccurred(const pcl::visualization::KeyboardEvent& event, void* nothing){
    if(event.getKeySym() == "space" && event.keyDown()){
        iteration_flag = true;
    }
}

void rotateCloudPoint(
						pcl::PointCloud<pcl::PointXYZ>::Ptr src_cloud, 
						pcl::PointCloud<pcl::PointXYZ>::Ptr dst_cloud,
						float angle) //45度
{
	int i;
	double x,y,z;
	float theta = angle;
	//pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new (pcl::PointCloud<pcl::PointXYZRGBA>));  
	//pcl::io::loadPCDFile ("tmp.pcd", *src_cloud); 
	dst_cloud->points.clear();
	for(i =0; i < src_cloud->width; i++)
	{

		x = src_cloud->points[i].x;
		y = src_cloud->points[i].y * cos(theta) - src_cloud->points[i].z * sin(theta);
		z = src_cloud->points[i].y * sin(theta) + src_cloud->points[i].z * cos(theta);
		dst_cloud->points.push_back( pcl::PointXYZ(x,y,z) );
	}
	dst_cloud->width = i;
}

void showRtViewer()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr1 (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ> &pcloud1 = *cloud_ptr;
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
        
    pcloud1.points.push_back( pcl::PointXYZ(10, 10, 80) );
    pcloud1.width = cloud_ptr->size();
    pcloud1.height = 1;
    pcloud1.is_dense = true;

	pcl::io::loadPCDFile ("tmp.pcd", *cloud_ptr);  
    viewer = simpleVis(cloud_ptr);

	viewer->registerKeyboardCallback(&keyboardEventOccurred, (void*)NULL);
    //boost::thread vthread(&viewerRunner,viewer);
       
	viewer->spinOnce (200, true);
	boost::this_thread::sleep (boost::posix_time::milliseconds (1000));

	rotateCloudPoint(cloud_ptr, cloud_ptr1, 0);
	int angel = 20;
	while(1)
	{
		rotateCloudPoint(cloud_ptr1, cloud_ptr, angel);
		angel += 20;
		angel = angel % 360;
		//viewer->updatePointCloud<pcl::PointXYZ>(cloud_ptr,"sample cloud");
		viewer->removeAllPointClouds();
		viewer->spinOnce (200, true);
		viewer->addPointCloud(cloud_ptr);
		viewer->spinOnce (200, true);
		boost::this_thread::sleep (boost::posix_time::milliseconds (1000));
		if(!(iteration_flag != true && (!viewer->wasStopped())))
		{
			break;
		}
	}
	viewer->close();
    //vthread.join();
}


void showViewerNew()
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr (new pcl::PointCloud<pcl::PointXYZRGB>);
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));

	pcl::io::loadPCDFile ("tmp.pcd", *point_cloud_ptr);  
    viewer = rgbVis(point_cloud_ptr);

	viewer->registerKeyboardCallback(&keyboardEventOccurred, (void*)NULL);
    //boost::thread vthread(&viewerRunner,viewer);

	while (1)
    {
		viewer->spinOnce (200);
		boost::this_thread::sleep (boost::posix_time::microseconds (1000));		
		if(iteration_flag == true)
		{
			break;			
		}
    }
	viewer->close();
}