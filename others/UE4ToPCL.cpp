#pragma warning(disable : 4996)
#include<pcl/visualization/cloud_viewer.h>  
#include<pcl/io/io.h>  
#include<pcl/io/pcd_io.h>
#include<pcl/io/ply_io.h>  
#include<pcl/io/obj_io.h>
#include<pcl/point_types.h> 
#include<pcl/common/transforms.h>
#include<iostream>
#include <fstream>
#include<math.h>
#include<utility>
#include<Eigen/src/Core/Matrix.h>
#define print(a) cout<<#a<<":"<<a<<std::endl
#define PI 3.1415926
using std::cout;

Eigen::Matrix2f m;

void transformPolygonMesh(pcl::PolygonMesh *inMesh, Eigen::Matrix4f&transform)
{
	pcl::PointCloud<pcl::PointXYZ>cloud;
	pcl::fromPCLPointCloud2(inMesh->cloud, cloud);
	pcl::transformPointCloud(cloud, cloud, transform);
	pcl::toPCLPointCloud2(cloud, inMesh->cloud);
}

int main() {
	float x, y, z, rx, ry,
		rz, sx, sy, sz;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("Viewer"));
	pcl::PolygonMesh mesh;

	if (-1 == pcl::io::loadOBJFile("D://cup.obj", mesh)) {
		cout << "error obj file!" << endl;
		return -1;
	}
	if (-1 == pcl::io::loadPCDFile("D://ue4capt//cup0.pcd", *cloud)) {
	//if (-1 == pcl::io::loadPCDFile("D://Skull.pcd", *cloud)) {
		cout << "error pcd file!" << endl;
		return -1;
	}
	ifstream obj("D://cup.txt");
	obj >> x >> y >> z >> rx >> ry >> rz >> sx >> sy >> sz;

	using namespace Eigen;
	//ZYX intrinsic
	auto q = AngleAxisf(-rz / 180 * PI, Vector3f::UnitZ()) * AngleAxisf(ry / 180 * PI, Vector3f::UnitY()) * AngleAxisf(-rx / 180 * PI, Vector3f::UnitX());

	Eigen::Matrix4f transform;
	Eigen::AlignedScaling3f scale(sx, sy, sz);
	Eigen::Affine3f rot(q);
	Eigen::Translation3f t(z, y, x);
	//ReOrdering the axis to match UE4 coordinate
	Eigen::Matrix3f toUE;
	toUE << 1, 0, 0,
		    0, 0, 1,
		    0, -1, 0;
	transform = (t*toUE*rot*scale).matrix();

	transformPolygonMesh(&mesh, transform);
	viewer->addPointCloud(cloud);
	viewer->addPolygonMesh(mesh);

	viewer->addCoordinateSystem(500);
	viewer->spin();
	return 0;
}

