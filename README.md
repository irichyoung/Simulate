# Simulate
Sythesis the photorealistic images by using ue4 for training AI algorithm.
(As Simple As Possible For AI Training.)
Features:  
·Scene Capture Actor.  
·Pointcloud.  
·Segment Pointcloud.  (TODO)  
·Instance Segmentation.  
·Semantic Segmentation.  (TODO)  
·Depth.  
·RGB.  
·Poses.  
·Convert Coordinates System Between Unreal Engine and Pcl(Eigen).  
·Weather Controller.(TODO)  
·Simulate Soft Body.(TODO)  
·Procedural Mesh.(TODO)  
·Procedural Texture.(TODO)  
·Realistic Camera Model.(TODO)  
·Generate realistic Text Fit in Scene.(Can be used for training OCR)  
·Project A Whole Picture Into The Scene.(Can be used for color a pointcloud)  
·3D Shape Matching.(Used for measure the difference of mesh)(TODO)   

(Unreal Engine adopted a intrinsic ZYX euler rotation and it's a left-hand coordinate system.Pcl is intrinsic XYZ and right-hand.)  
(Generate a pointcloud map and a segment map simultaneously so we can form a pcd file with the object segmented.)  
(Capture pointcloud from a mesh is a discrete sample progress.  
Actully,the rasterization of real time render is kind of discreate sample the triangle of the mesh.  
Luckly,Unreal engine adopt a technique named deferred render which we can get the mesh informations of a pixel on a raster from the DBuffer.  
And we should do a preprocessing for the pointcloud because the data should be map into [0,1] for saving into a picture.)  
