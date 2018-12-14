#include "BeeTool.h"
#include "Kismet/KismetMathLibrary.h"
#include "FileHelper.h"
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

FVector2D UBeeToolLib::ProjectWorldToScreen(ASceneCapture2D *capture, const FVector&pos)
{
	check(capture);
	FVector2D result;
	if (capture->GetCaptureComponent2D()->TextureTarget) {
		FIntPoint rect(capture->GetCaptureComponent2D()->TextureTarget->GetSurfaceWidth(),
			capture->GetCaptureComponent2D()->TextureTarget->GetSurfaceHeight());
		FMatrix ProjectionMatrix;
		float FOV = capture->GetCaptureComponent2D()->FOVAngle / 360 * PI;
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
		FTransform transform = capture->GetCaptureComponent2D()->GetComponentTransform();
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

FVector UBeeToolLib::ProjectWorldToCam(ASceneCapture2D *capture, const FVector&pos)
{
	check(capture);
	FVector result;
	if (capture->GetCaptureComponent2D()->TextureTarget) {
		FIntPoint rect(capture->GetCaptureComponent2D()->TextureTarget->GetSurfaceWidth(),
			capture->GetCaptureComponent2D()->TextureTarget->GetSurfaceHeight());
		FTransform transform = capture->GetCaptureComponent2D()->GetComponentTransform();
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
