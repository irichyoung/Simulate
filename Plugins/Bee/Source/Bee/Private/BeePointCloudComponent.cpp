#include "BeePointCloudComponent.h"
#include "PrimitiveSceneProxy.h"
#include "SceneManagement.h"
#include "Engine.h"
#include "Engine/Engine.h"

//
//class FBeePCSceneProxy final :public FPrimitiveSceneProxy {
//private:
//	FStaticMeshVertexBuffers VertexBuffers;
//	FLocalVertexFactory VertexFactory;
//	uint32 PrimitiveCount;
//public:
//	FBeePCSceneProxy(UBeePointCloudComponent *comp)
//		: FPrimitiveSceneProxy(comp),
//		VertexFactory(GetScene().GetFeatureLevel(),"FBeePCSceneProxy")
//	{
//		//VertexBuffers.InitWithDummyData(&VertexFactory,comp->)
//	}
//	SIZE_T GetTypeHash() const override{
//		static size_t UniquePointer;
//		return reinterpret_cast<size_t>(&UniquePointer);
//	}
//	virtual uint32 GetMemoryFootprint(void) const override {
//		return(sizeof(*this) + GetAllocatedSize()); 
//	}
//	uint32 GetAllocatedSize(void) const { 
//		return(FPrimitiveSceneProxy::GetAllocatedSize()); 
//	}
//	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
//	{
//		const bool bWireframe = AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe;
//
//		auto WireframeMaterialInstance = new FColoredMaterialRenderProxy(
//			GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy(IsSelected()) : NULL,
//			FLinearColor(0, 0.5f, 1.f)
//		);
//
//		Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);
//
//		FMaterialRenderProxy* MaterialProxy = NULL;
//		if (bWireframe)
//		{
//			MaterialProxy = WireframeMaterialInstance;
//		}
//		else
//		{
//			//MaterialProxy = Material->GetRenderProxy(IsSelected());
//		}
//
//		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
//		{
//			if (VisibilityMap & (1 << ViewIndex))
//			{
//				const FSceneView* View = Views[ViewIndex];
//				// Draw the mesh.
//				FMeshBatch& Mesh = Collector.AllocateMesh();
//				FMeshBatchElement& BatchElement = Mesh.Elements[0];
//				//BatchElement.IndexBuffer = &IndexBuffer;
//				Mesh.bWireframe = bWireframe;
//				Mesh.VertexFactory = &VertexFactory;
//				Mesh.MaterialRenderProxy = MaterialProxy;
//				BatchElement.PrimitiveUniformBuffer = CreatePrimitiveUniformBufferImmediate(GetLocalToWorld(), GetBounds(), GetLocalBounds(), true, UseEditorDepthTest());
//				BatchElement.FirstIndex = 0;
//				BatchElement.NumPrimitives = PrimitiveCount / 3;
//				//BatchElement.MinVertexIndex = 0;
//				//BatchElement.MaxVertexIndex = GetRequiredVertexCount();
//				Mesh.ReverseCulling = IsLocalToWorldDeterminantNegative();
//				Mesh.Type = PT_PointList;// PT_TriangleList;
//				Mesh.DepthPriorityGroup = SDPG_World;
//				Mesh.bCanApplyViewModeOverrides = false;
//				Collector.AddMesh(ViewIndex, Mesh);
//
//#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
//				// Render bounds
//				RenderBounds(Collector.GetPDI(ViewIndex), ViewFamily.EngineShowFlags, GetBounds(), IsSelected());
//#endif
//			}
//		}
//	}
//
//};
//
//FPrimitiveSceneProxy* UBeePointCloudComponent::CreateSceneProxy() {
//	return (FPrimitiveSceneProxy*)new FBeePCSceneProxy();
//}