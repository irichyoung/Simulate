#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "ImageUtils.h"
#include "FileHelper.h"
#include "BeeCapture.generated.h"

UCLASS()
class BEE_API ABeeCapture : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABeeCapture();
	UPROPERTY(Category = SceneCapture, BlueprintReadWrite, EditAnywhere)
		ASceneCapture2D *capture;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void WritePointCloudToFile(const FString&path);
	UFUNCTION(BlueprintCallable)
		void WriteRGBToFile(const FString&path);
	UFUNCTION(BlueprintCallable)
		void WriteTransfromToFile(const FTransform&t, const FString&path);

};