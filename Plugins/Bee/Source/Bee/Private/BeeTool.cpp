#include "BeeTool.h"
#include "Kismet/KismetMathLibrary.h"
#include "FileHelper.h"
#include "Array.h"


static uint8 lookup[768] = {41,35,190,132,225,108,214,174,82,144,73,241,241,187,233,
						235,179,166,219,60,135,12,62,153,36,94,13,28,6,183,71,222,
						179,18,77,200,67,187,139,166,31,3,90,125,9,56,37,31,93,212,
						203,252,150,245,69,59,19,13,137,10,28,219,174,50,32,154,80,
						238,64,120,54,253,18,73,50,246,158,125,73,220,173,79,20,242,
						68,64,102,208,107,196,48,183,50,59,161,34,246,34,145,157,225,
						139,31,218,176,202,153,2,185,114,157,73,44,128,126,197,153,213,
						233,128,178,234,201,204,83,191,103,214,191,20,214,126,45,220,142,
						102,131,239,87,73,97,255,105,143,97,205,209,30,157,156,22,114,114,
						230,29,240,132,79,74,119,2,215,232,57,44,83,203,201,18,30,51,116,
						158,12,244,213,212,159,212,164,89,126,53,207,50,34,244,204,207,
						211,144,45,72,211,143,117,230,217,29,42,229,192,247,43,120,129,
						135,68,14,95,80,0,212,97,141,190,123,5,21,7,59,51,130,31,24,112,
						146,218,100,84,206,177,133,62,105,21,248,70,106,4,150,115,14,217,
						22,47,103,104,212,247,74,74,208,87,104,118,250,22,187,17,173,174,
						36,136,121,254,82,219,37,67,229,60,244,69,211,216,40,206,11,245,197,
						96,89,61,151,39,138,89,118,45,208,194,201,205,104,212,73,106,121,37,
						8,97,64,20,177,59,106,165,17,40,193,140,214,169,11,135,151,140,47,241,
						21,29,154,149,193,155,225,192,126,233,168,154,167,134,194,181,84,191,
						154,231,217,35,209,85,144,56,40,209,217,108,161,102,94,78,225,48,
						156,254,217,113,159,226,165,226,12,155,180,71,101,56,42,70,137,169,
						130,121,122,118,120,194,99,177,38,223,218,41,109,62,98,224,150,18,
						52,191,57,166,63,137,94,241,109,14,227,108,40,161,30,32,29,203,194,
						3,63,65,7,132,15,20,5,101,27,40,97,201,197,231,44,142,70,54,8,220,
						243,168,141,254,190,242,235,113,255,160,208,59,117,6,140,126,135,
						120,115,77,208,190,130,190,219,194,70,65,43,140,250,48,127,112,240,
						167,84,134,50,149,170,91,104,19,11,230,252,245,202,190,125,159,137,
						138,65,27,253,184,79,104,246,114,123,20,153,205,211,13,240,68,58,180,
						166,102,83,51,11,203,161,16,94,76,236,3,76,115,230,5,180,49,14,170,
						173,207,213,176,202,39,255,216,157,20,77,244,121,39,89,66,124,156,193,
						248,205,140,135,32,35,100,184,166,135,149,76,176,90,141,78,45,153,231,
						61,177,96,222,177,128,173,8,65,233,103,65,165,213,159,228,24,159,21,66,
						0,38,254,76,209,33,4,147,47,179,143,115,83,64,67,138,175,126,202,111,
						213,207,211,161,149,206,90,190,101,39,42,246,7,173,161,190,101,166,180,
						201,192,105,50,52,9,44,77,1,143,23,86,198,219,157,200,166,216,11,136,
						129,56,97,107,104,18,98,249,84,208,231,113,23,72,120,13,146,41,29,134,
						41,153,114,219,116,28,250,79,55,184,181,176,149,87,245,223,128,108,109,
						141,116,217,139,67,101,17,8,165,246,121,189,247,235,21,184,224,225,96,
						143,110,60,123,244,91,98,138,138,143,39,92,247,229,135,74,59,50,155,97,
						64,132,198,195,177,167,48,74,16,238,117,111,3,47,158,106,239,16,80,155,
						200,129,67,41,40,138,246,233,158,71,161,129,72,49,108,205,164,158,222,
						129,163,140,152,16,255,154,67,205,207 };

FString UBeeToolLib::RandomString(const int count)
{
	char tmp[50];
	tmp[0] = UKismetMathLibrary::RandomIntegerInRange('A', 'Z');
	for (int i = 1; i < count; i++) {
		tmp[i] = UKismetMathLibrary::RandomIntegerInRange('0', '9');
	}
	tmp[count] = '\0';
	return tmp;
}

FVector2D UBeeToolLib::ProjectWorldToScreen(USceneCaptureComponent2D *capture, const FVector&pos)
{
	check(capture);
	FVector2D result;
	if (capture->TextureTarget) {
		FIntPoint rect(capture->TextureTarget->GetSurfaceWidth(),
			capture->TextureTarget->GetSurfaceHeight());
		FMatrix ProjectionMatrix;
		float FOV = capture->FOVAngle / 360 * PI;
		float XAxisMultiplier = 1.f;
		float YAxisMultiplier = rect.X / rect.Y;
		if ((int32)ERHIZBuffer::IsInverted)
		{
			ProjectionMatrix = FReversedZPerspectiveMatrix(
				FOV,
				FOV,
				XAxisMultiplier,
				YAxisMultiplier,
				GNearClippingPlane,
				GNearClippingPlane
			);
		}
		FTransform transform = capture->GetComponentTransform();
		FMatrix RotationMatrix = transform.ToInverseMatrixWithScale() * FMatrix(
			FPlane(0, 0, 1, 0),
			FPlane(1, 0, 0, 0),
			FPlane(0, 1, 0, 0),
			FPlane(0, 0, 0, 1));
		FMatrix intrisicMat = RotationMatrix * ProjectionMatrix;
		FSceneView::ProjectWorldToScreen(pos, FIntRect(FIntPoint(0, 0), rect),
			intrisicMat, result);
	}
	return result;
}

FVector UBeeToolLib::ProjectWorldToCam(USceneCaptureComponent2D *capture, const FVector&pos)
{
	check(capture);
	FVector result;
	if (capture->TextureTarget) {
		FIntPoint rect(capture->TextureTarget->GetSurfaceWidth(),
			capture->TextureTarget->GetSurfaceHeight());
		FTransform transform = capture->GetComponentTransform();
		FMatrix RotationMatrix = transform.ToInverseMatrixWithScale() * FMatrix(
			FPlane(0, 0, 1, 0),
			FPlane(1, 0, 0, 0),
			FPlane(0, 1, 0, 0),
			FPlane(0, 0, 0, 1));
		result = RotationMatrix.TransformPosition(pos);
	}
	return result;
}

FVector UBeeToolLib::RandomPointInBoundingBoxes(const TArray<UBoxComponent*>&boxes)
{
	int id = UKismetMathLibrary::RandomIntegerInRange(0, boxes.Num() - 1);
	FBoxSphereBounds box = boxes[id]->CalcBounds(boxes[id]->GetComponentTransform());
	return UKismetMathLibrary::RandomPointInBoundingBox(box.Origin, box.BoxExtent);
}

void UBeeToolLib::WriteStringToFile(const FString&path, const FString&str)
{
	FFileHelper::SaveStringToFile(str, path.GetCharArray().GetData());
}

FColor UBeeToolLib::GetColorById(int id) {
	return FColor{ lookup[id * 3 ], lookup[id * 3 + 1], lookup[id * 3 + 2] };
}

FString UBeeToolLib::ColorToString(const FColor&color) {
	return "R:" + FString::FromInt(color.R) + " " +
		"G:" + FString::FromInt(color.G) + " " +
		"B:" + FString::FromInt(color.B);
}

void UBeeToolLib::SaveRenderTarget(UTextureRenderTarget2D* TexRT,
	const FString&path, const FString&filename) {
	//FRenderTarget* RenderTarget = TexRT->GameThread_GetRenderTargetResource();
	//EPixelFormat Format = TexRT->GetFormat();
	//TArray<uint8>RawData;

	//int32 ImageBytes = CalculateImageBytes(TexRT->SizeX, TexRT->SizeY, 0, Format);
	//RawData.AddUninitialized(ImageBytes);
	//bool bReadSuccess = false;
	//switch (Format)
	//{
	//	case PF_FloatRGBA:
	//	{
	//		TArray<FFloat16Color> FloatColors;
	//		bReadSuccess = RenderTarget->ReadFloat16Pixels(FloatColors);
	//		FMemory::Memcpy(RawData.GetData(), FloatColors.GetData(), ImageBytes);
	//	}
	//	break;
	//	case PF_B8G8R8A8:
	//		bReadSuccess = RenderTarget->ReadPixelsPtr((FColor*)RawData.GetData());
	//		break;
	//	case PF_A8:
	//		bReadSuccess = RenderTarget->ReadFloat16Pixels
	//}
	//if (bReadSuccess == false)
	//{
	//	RawData.Empty();
	//}
	//return bReadSuccess;
}

bool operator>(const FVector&l, const FVector&r) {
	if (l.X > r.X && l.Y > r.Y && l.Z > r.Z)return true;
	else return false;
}

bool operator<(const FVector&l, const FVector&r) {
	if (l.X < r.X && l.Y < r.Y && l.Z < r.Z)return true;
	else return false;
}

void UBeeToolLib::InitInstancedStaticMesh(UInstancedStaticMeshComponent*inst, int num) {
	for (int i = 0; i < num; i++) {
		inst->AddInstance(FTransform());
	}
}