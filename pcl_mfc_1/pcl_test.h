#include "stdafx.h"
#include <pcl/visualization/cloud_viewer.h>  
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h> 

extern int user_data;  

extern void viewerOneOff (pcl::visualization::PCLVisualizer& viewer);
extern void viewerPsycho (pcl::visualization::PCLVisualizer& viewer);
extern int numofPoints(char* fname);
extern int txt2Pcd(char *fileName);
extern int txt2PcdNormalize(char *fileName);
extern void showViewer();
extern void showRtViewer();
extern void showViewerNew();
extern int txt2PcdNormalize4Color(char *fileName, int scale);

