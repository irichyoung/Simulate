#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SceneView.h"
#include "Engine/Scene.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/BoxComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Box.h"
#include "Array.h"
#include "BeeTool.generated.h"

UCLASS()
class BEE_API UBeeToolLib :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		static FString RandomString(const int count);
	UFUNCTION(BlueprintCallable)
		static FVector RandomPointInBoundingBoxes(const TArray<UBoxComponent*>&boxes);
	UFUNCTION(BlueprintCallable)
		static FVector2D ProjectWorldToScreen(ASceneCapture2D*capture, const FVector&pos);
	UFUNCTION(BlueprintCallable)
		static FVector ProjectWorldToCam(ASceneCapture2D*capture, const FVector&pos);
	UFUNCTION(BlueprintCallable)
		static void WriteStringToFile(const FString&path, const FString&str);
	UFUNCTION(BlueprintCallable)
		static FColor GetColorById(int id);
	UFUNCTION(BlueprintCallable)
		static FString ColorToString(const FColor&color);
	UFUNCTION(BlueprintCallable)
		static void SaveRenderTarget(UTextureRenderTarget2D* TexRT, 
			const FString&path, const FString&filename);
};