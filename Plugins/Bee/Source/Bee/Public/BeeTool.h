#pragma once

#include "CoreMinimal.h"
#include "JsonGlobals.h"
#include "Serialization/JsonTypes.h"
#include "Dom/JsonValue.h"
#include "JsonObject.h"
#include "JsonWriter.h"
#include "JsonSerializer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SceneView.h"
#include "Engine/Scene.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Box.h"
#include "Array.h"
#include "SharedPointer.h"
#include "BeeTool.generated.h"

USTRUCT(BlueprintType)
struct FObj {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FString Pos;

	UPROPERTY(BlueprintReadWrite)
		FString color;
};

USTRUCT(BlueprintType)
struct FGroundTruth {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FString Cam;

	UPROPERTY(BlueprintReadWrite)
		FString RGB;

	UPROPERTY(BlueprintReadWrite)
		FString Depth;

	UPROPERTY(BlueprintReadWrite)
		FString Segmetation;

	UPROPERTY(BlueprintReadWrite)
		TArray<FObj> objs;
};

UCLASS()
class BEE_API UBeeToolLib :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		static FString RandomString(const int count);
	UFUNCTION(BlueprintCallable)
		static FVector RandomPointInBoundingBoxes(const TArray<UBoxComponent*>&boxes);
	UFUNCTION(BlueprintCallable)
		static FVector2D ProjectWorldToScreen(USceneCaptureComponent2D*capture, const FVector&pos);
	UFUNCTION(BlueprintCallable)
		static FVector ProjectWorldToCam(USceneCaptureComponent2D*capture, const FVector&pos);
	UFUNCTION(BlueprintCallable)
		static void WriteStringToFile(const FString&path, const FString&str);
	UFUNCTION(BlueprintCallable)
		static void WriteGroundTruthToFile(const FString&path, const FGroundTruth&groundTruth);
	UFUNCTION(BlueprintCallable)
		static FColor GetColorById(int id);
	UFUNCTION(BlueprintCallable)
		static FString ColorToString(const FColor&color);
	UFUNCTION(BlueprintCallable)
		static void SaveRenderTarget(UTextureRenderTarget2D* TexRT, 
			const FString&path, const FString&filename);
	UFUNCTION(BlueprintCallable)
		static void InitInstancedStaticMesh(UInstancedStaticMeshComponent*comp,int num);

};