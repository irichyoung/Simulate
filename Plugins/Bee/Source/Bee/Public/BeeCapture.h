#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/TextureRenderTarget2D.h"
#include "ImageUtils.h"
#include "FileHelper.h"
#include "BeeCapture.generated.h"

UCLASS()
class BEE_API ABeeCapture : public ASceneCapture2D
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABeeCapture();
	/*UPROPERTY(Category = SceneCapture, BlueprintReadWrite, EditAnywhere)
		ASceneCapture2D *capture;*/
	/** Scene capture component. */
	UPROPERTY(Category = DecalActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* DepthCap;
	/** Scene capture component. */
	UPROPERTY(Category = DecalActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* InstanceSegCap;
	/** Scene capture component. */
	UPROPERTY(Category = DecalActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* RGBCap;
	/** Scene capture component. */
	UPROPERTY(Category = DecalActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* PointCloudCap;
	/** Scene capture component. */
	UPROPERTY(Category = DecalActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* SemanticSegCap;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostActorCreated()override;
	UFUNCTION(BlueprintCallable)
		void PointCloudToFile(const FString&path);
	UFUNCTION(BlueprintCallable)
		void RGBToFile(UTextureRenderTarget2D* TextureRenderTarget,
			const FString&path, const FString&filename);
	UFUNCTION(BlueprintCallable)
		void InstanceSegToFile(UTextureRenderTarget2D* TextureRenderTarget, 
			const FString&path, const FString&filename);
	UFUNCTION(BlueprintCallable)
		void SemanticSegToFile(UTextureRenderTarget2D* TextureRenderTarget, 
			const FString&path, const FString&filename);
	UFUNCTION(BlueprintCallable)
		void DepthToFile(UTextureRenderTarget2D* TextureRenderTarget,
			const FString&path, const FString&filename);
	UFUNCTION(BlueprintCallable)
		void TransfromToFile(const FTransform&t, const FString&path);

};