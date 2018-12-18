# Simulate
Sythesis the photorealistic images by using ue4 for training AI algorithm.

Features:
·A powerful scene capture actor that can extracts a lots of features from the simulation scene.
·Capture pointcloud from Unreal Engine.
·Segment Pointcloud.
·Instance Segmentation picture.
·Semantic Segmentation picture.
·Depth picture.
·RGB picture.
·Convert Coordinates System Between Unreal Engine and Pcl.



(Unreal Engine adopted a intrinsic ZYX euler rotation and it's a left-hand coordinate system.Pcl is intrinsic XYZ and right-hand.)
(We generate a pointcloud map and a segment map simultaneously so we can form a pcd file with the object segmented.)
(Capture pointcloud from a mesh is a discrete sample progress.
Actully,the rasterization of real time render is kind of discreate sample the triangle of the mesh.
Luckly,Unreal engine adopt a technique named deferred render which we can get the mesh informations of a pixel on a raster from the DBuffer.
And we should do a preprocessing for the pointcloud because the data should be map into [0,1] for saving into a picture.)
