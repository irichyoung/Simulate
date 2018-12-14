// Fill out your copyright notice in the Description page of Project Settings.

#include "BeeCapture.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ABeeCapture::ABeeCapture()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABeeCapture::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABeeCapture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABeeCapture::WritePointCloudToFile(const FString&path)
{
	if (capture->GetCaptureComponent2D()->TextureTarget) {
		UTextureRenderTarget2D *TexRT = capture->GetCaptureComponent2D()->TextureTarget;
		TArray<FFloat16Color> RawData;

		FRenderTarget* RenderTarget = TexRT->GameThread_GetRenderTargetResource();

		uint32 SizeX = TexRT->SizeX;
		uint32 SizeY = TexRT->SizeY;

		RawData.AddZeroed(SizeX * SizeY);
		if (!RenderTarget->ReadFloat16Pixels(RawData)) {
			UE_LOG(LogTemp, Warning, TEXT("Can not writePixel"));
		}

		FString pcd = "";
		pcd.Append("FIELDS x y z rgb\nSIZE 4 4 4 4\nTYPE F F F F\n");
		pcd.Append(FString::Printf(TEXT("WIDTH %d\n"), SizeX));
		pcd.Append(FString::Printf(TEXT("HEIGHT %d\n"), SizeY));
		pcd.Append(FString::Printf(TEXT("POINTS %d\n"), SizeX * SizeY));
		pcd.Append(FString::Printf(TEXT("DATA ascii\n")));

		for (uint32 i = 0; i < SizeX * SizeY; i++) {
			if (RawData[i].R != 0) {
				//UE_LOG(LogTemp, Warning, TEXT("!!!"));
			}
			float x = (float)RawData[i].B * 1600 - 800;
			float y = (float)RawData[i].G * 1600 - 800;
			float z = (float)RawData[i].R * 1600 - 800;
			uint8_t r = UKismetMathLibrary::RandomIntegerInRange(0,255), 
				g = UKismetMathLibrary::RandomIntegerInRange(0, 255), b = UKismetMathLibrary::RandomIntegerInRange(0, 255); 
			uint32_t rgb = ((uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b);
			//float w = *reinterpret_cast<float*>(&rgb);
			float w = 4.2108e+06;
			pcd.Append(FString::Printf(TEXT("%f %f %f %f\n"), x, y, z, w));
		}
		FFileHelper::SaveStringToFile(pcd, path.GetCharArray().GetData());
	}
}

void ABeeCapture::WriteRGBToFile(const FString&path) {
	if (capture->GetCaptureComponent2D()->TextureTarget) {
		UTextureRenderTarget2D *TexRT = capture->GetCaptureComponent2D()->TextureTarget;
		TArray<FFloat16Color> RawData;

		FRenderTarget* RenderTarget = TexRT->GameThread_GetRenderTargetResource();

		uint32 SizeX = TexRT->SizeX;
		uint32 SizeY = TexRT->SizeY;

		RawData.AddZeroed(SizeX * SizeY);
		if (!RenderTarget->ReadFloat16Pixels(RawData)) {
			UE_LOG(LogTemp, Warning, TEXT("Can not writePixel"));
		}

		FString pcd = "";
		pcd.Append("FIELDS x y z rgb\nSIZE 4 4 4 4\nTYPE F F F F\n");
		pcd.Append(FString::Printf(TEXT("WIDTH %d\n"), SizeX));
		pcd.Append(FString::Printf(TEXT("HEIGHT %d\n"), SizeY));
		pcd.Append(FString::Printf(TEXT("POINTS %d\n"), SizeX * SizeY));
		pcd.Append(FString::Printf(TEXT("DATA ascii\n")));

		for (uint32 i = 0; i < SizeX * SizeY; i++) {
			if (RawData[i].R != 0) {
				//UE_LOG(LogTemp, Warning, TEXT("!!!"));
			}
			float x = (float)RawData[i].B * 1600 - 800;
			float y = (float)RawData[i].G * 1600 - 800;
			float z = (float)RawData[i].R * 1600 - 800;
			uint8_t r = UKismetMathLibrary::RandomIntegerInRange(0, 255),
				g = UKismetMathLibrary::RandomIntegerInRange(0, 255), b = UKismetMathLibrary::RandomIntegerInRange(0, 255);
			uint32_t rgb = ((uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b);
			float w = *reinterpret_cast<float*>(&rgb);
			pcd.Append(FString::Printf(TEXT("%f %f %f %f\n"), x, y, z, w));
		}
		FFileHelper::SaveStringToFile(pcd, path.GetCharArray().GetData());
	}
}

void ABeeCapture::WriteTransfromToFile(const FTransform&transform, const FString&path) {
	FString t = "";
	FVector loc = transform.GetLocation();
	FVector rot = transform.GetRotation().Rotator().Euler();
	FVector scale = transform.GetScale3D();
	t.Append(FString::Printf(TEXT("%f %f %f %f %f %f %f %f %f\n"), loc.X, loc.Y, loc.Z, rot.X, rot.Y, rot.Z, scale.X, scale.Y, scale.Z));
	FFileHelper::SaveStringToFile(t, path.GetCharArray().GetData());
}