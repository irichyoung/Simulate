#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "PrimitiveSceneProxy.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "BeePointCloudComponent.generated.h"

UCLASS()
class BEE_API UBeePointCloudComponent :public UMeshComponent {
	GENERATED_BODY()
public:
	//virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataSource")
		UTextureRenderTarget2D *rt;

};