# Simulate
Sythesis the photorealistic images by using ue4 for training AI algorithm.
(As Simple As Possible For AI Training.)  
Features:  
·A Couple Of Realitic Scene Made By Myself.  
·Pointcloud.  
·Segment Pointcloud.   
·Instance Segmentation.    
·Semantic Segmentation.(TODO)  
·Depth.    
·RGB.  
·Poses.  
·Convert Coordinates System Between Unreal Engine and Pcl(Eigen).  
·Weather Controller.(TODO)  
·Simulate Soft Body.(TODO)  
·Procedural Random Mesh.(TODO)  
·Procedural Random Texture.(TODO)  
·Procedural Random Light.(TODO)  
·Realistic Camera Model.(TODO)  
·Generate realistic Text Fit in Scene.(Can be used for training OCR)  
·Project A Whole Picture Into The Scene.(Can be used for color a pointcloud)  
·3D Shape Matching.(Used for measure the difference of mesh)(TODO)   


 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/scene/scene%20(3).jpg)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/scene/scene%20(4).jpg)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/scene/scene%20(5).jpg)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/scene/scene%20(2).png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/scene/scene%20(7).jpg)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/pointcloud/pointcloud.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/pointcloud/pointcloud1.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/pointcloud/pointcloud2.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/pointcloud/pointcloud3.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/seg1261.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/color1261.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/depth1261.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/seg1281.png)   
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/color1281.png)   
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/depth1281.png)   
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/seg2911.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/color2911.png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/dataset/depth2911.png) 
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/ocr/OCR%20(2).png)  
 ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/ocr/OCR%20(3).png) 
  ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/ocr/OCR.png)  
  ![image](https://github.com/irichyoung/Simulate/blob/master/illustrate/ocr/OCR.jpg)  
  
(Unreal Engine adopted a intrinsic ZYX euler rotation and it's a left-hand coordinate system.Pcl is intrinsic XYZ and right-hand.)  
(Generate a pointcloud map and a segment map simultaneously so we can form a pcd file with the object segmented.)  
(Capture pointcloud from a mesh is a discrete sample progress.  
Actully,the rasterization of real time render is kind of discreate sample the triangle of the mesh.  
Luckly,Unreal engine adopt a technique named deferred render which we can get the mesh informations of a pixel on a raster from the DBuffer.  
And we should do a preprocessing for the pointcloud because the data should be map into [0,1] for saving into a picture.)  
