#pragma once
#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"
#include "BeelocalPlayer.generated.h"



UCLASS()
class BEE_API UBeeLocalPlayer: public ULocalPlayer {
	GENERATED_BODY()
public:
	UBeeLocalPlayer(FVTableHelper& Helper);
	virtual FSceneView* CalcSceneView(class FSceneViewFamily* ViewFamily,
		FVector& OutViewLocation,
		FRotator& OutViewRotation,
		FViewport* Viewport,
		class FViewElementDrawer* ViewDrawer = NULL,
		EStereoscopicPass StereoPass = eSSP_FULL);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*>ShowOnlyActors;
	void UpdateShowOnlyActors(TArray<AActor*>&actors);
};