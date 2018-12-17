// Fill out your copyright notice in the Description page of Project Settings.

#include "BeeCapture.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Serialization/BufferArchive.h"
#include "EngineGlobals.h"
#include "Internationalization.h"
#include "Logging/MessageLog.h"
#include "ImageUtils.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Modules/ModuleManager.h"
DEFINE_LOG_CATEGORY_STATIC(LogImageUtils, Log, All);

#define LOCTEXT_NAMESPACE "ImageUtils"

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

void ABeeCapture::PostActorCreated() {
	Super::PostActorCreated();

	// no need load the editor mesh when there is no editor
#if WITH_EDITOR
	if (GetMeshComp())
	{
		if (!IsRunningCommandlet())
		{
			if (!GetMeshComp()->GetStaticMesh())
			{
				UStaticMesh* CamMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EditorMeshes/MatineeCam_SM.MatineeCam_SM"), NULL, LOAD_None, NULL);
				GetMeshComp()->SetStaticMesh(CamMesh);
			}
		}
	}
#endif
}

void ABeeCapture::PointCloudToFile(const FString&path)
{
	if (PointCloudCap->TextureTarget) {
		UTextureRenderTarget2D *TexRT = PointCloudCap->TextureTarget;
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

void ABeeCapture::RGBToFile(UTextureRenderTarget2D* TextureRenderTarget,const FString&path,const FString&filename) {
	if (RGBCap->TextureTarget) {
		UKismetRenderingLibrary::ExportRenderTarget(GetWorld(), TextureRenderTarget, path, filename);
	}
}

void ABeeCapture::InstanceSegToFile(UTextureRenderTarget2D* TextureRenderTarget, const FString&path, const FString&filename) {
	if (InstanceSegCap->TextureTarget) {
		UKismetRenderingLibrary::ExportRenderTarget(GetWorld(), TextureRenderTarget, path, filename);
	}
}

void ABeeCapture::SemanticSegToFile(UTextureRenderTarget2D* TextureRenderTarget, const FString&path, const FString&filename) {
	if (SemanticSegCap->TextureTarget) {
		UKismetRenderingLibrary::ExportRenderTarget(GetWorld(), TextureRenderTarget, path, filename);
	}
}

void ABeeCapture::DepthToFile(UTextureRenderTarget2D* TextureRenderTarget, const FString&path, const FString&filename) {
	//FString TotalFileName = FPaths::Combine(*path, *filename);
	//FText PathError;
	//FPaths::ValidatePath(TotalFileName, &PathError);


	//if (!TextureRenderTarget)
	//{
	//	FMessageLog("Blueprint").Warning(LOCTEXT("ExportRenderTarget_InvalidTextureRenderTarget", "ExportRenderTarget: TextureRenderTarget must be non-null."));
	//}
	//else if (!TextureRenderTarget->Resource)
	//{
	//	FMessageLog("Blueprint").Warning(LOCTEXT("ExportRenderTarget_ReleasedTextureRenderTarget", "ExportRenderTarget: render target has been released."));
	//}
	//else if (!PathError.IsEmpty())
	//{
	//	FMessageLog("Blueprint").Warning(FText::Format(LOCTEXT("ExportRenderTarget_InvalidFilePath", "ExportRenderTarget: Invalid file path provided: '{0}'"), PathError));
	//}
	//else if (filename.IsEmpty())
	//{
	//	FMessageLog("Blueprint").Warning(LOCTEXT("ExportRenderTarget_InvalidFileName", "ExportRenderTarget: FileName must be non-empty."));
	//}
	//else
	//{
	//	FArchive* Ar = IFileManager::Get().CreateFileWriter(*TotalFileName);

	//	if (Ar)
	//	{
	//		FBufferArchive Buffer;

	//		bool bSuccess = false;
	//		if (TextureRenderTarget->GetFormat() == PF_B8G8R8A8)
	//		{
	//			check(TextureRenderTarget != nullptr);
	//			FRenderTarget* RenderTarget = TextureRenderTarget->GameThread_GetRenderTargetResource();
	//			FIntPoint Size = RenderTarget->GetSizeXY();

	//			TArray<uint8> RawData;
	//			bSuccess = GetRawData(TextureRenderTarget, RawData);

	//			IImageWrapperModule& ImageWrapperModule = FModuleManager::Get().LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));

	//			TSharedPtr<IImageWrapper> PNGImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	//			PNGImageWrapper->SetRaw(RawData.GetData(), RawData.GetAllocatedSize(), Size.X, Size.Y, ERGBFormat::BGRA, 8);

	//			const TArray<uint8>& PNGData = PNGImageWrapper->GetCompressed(100);

	//			Ar.Serialize((void*)PNGData.GetData(), PNGData.GetAllocatedSize());
	//		}

	//		if (bSuccess)
	//		{
	//			Ar->Serialize(const_cast<uint8*>(Buffer.GetData()), Buffer.Num());
	//		}

	//		delete Ar;
	//	}
	//	else
	//	{
	//		FMessageLog("Blueprint").Warning(LOCTEXT("ExportRenderTarget_FileWriterFailedToCreate", "ExportRenderTarget: FileWrite failed to create."));
	//	}
	//}
}

void ABeeCapture::TransfromToFile(const FTransform&transform, const FString&path) {
	FString t = "";
	FVector loc = transform.GetLocation();
	FVector rot = transform.GetRotation().Rotator().Euler();
	FVector scale = transform.GetScale3D();
	t.Append(FString::Printf(TEXT("%f %f %f %f %f %f %f %f %f\n"), loc.X, loc.Y, loc.Z, rot.X, rot.Y, rot.Z, scale.X, scale.Y, scale.Z));
	FFileHelper::SaveStringToFile(t, path.GetCharArray().GetData());
}