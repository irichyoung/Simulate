#include "BeeLocalPlayer.h"
#include "SceneView.h"
#include "Engine/World.h"
#include "Camera/CameraTypes.h"
#include "SceneViewExtension.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"

static void SetupMonoParameters(FSceneViewFamily& ViewFamily, const FSceneView& MonoView)
{
	// Compute the NDC depths for the far field clip plane. This assumes symmetric projection.
	const FMatrix& LeftEyeProjection = ViewFamily.Views[0]->ViewMatrices.GetProjectionMatrix();

	// Start with a point on the far field clip plane in eye space. The mono view uses a point slightly biased towards the camera to ensure there's overlap.
	const FVector4 StereoDepthCullingPointEyeSpace(0.0f, 0.0f, ViewFamily.MonoParameters.CullingDistance, 1.0f);
	const FVector4 FarFieldDepthCullingPointEyeSpace(0.0f, 0.0f, ViewFamily.MonoParameters.CullingDistance - ViewFamily.MonoParameters.OverlapDistance, 1.0f);

	// Project into clip space
	const FVector4 ProjectedStereoDepthCullingPointClipSpace = LeftEyeProjection.TransformFVector4(StereoDepthCullingPointEyeSpace);
	const FVector4 ProjectedFarFieldDepthCullingPointClipSpace = LeftEyeProjection.TransformFVector4(FarFieldDepthCullingPointEyeSpace);

	// Perspective divide for NDC space
	ViewFamily.MonoParameters.StereoDepthClip = ProjectedStereoDepthCullingPointClipSpace.Z / ProjectedStereoDepthCullingPointClipSpace.W;
	ViewFamily.MonoParameters.MonoDepthClip = ProjectedFarFieldDepthCullingPointClipSpace.Z / ProjectedFarFieldDepthCullingPointClipSpace.W;

	// We need to determine the stereo disparity difference between the center mono view and an offset stereo view so we can account for it when compositing.
	// We take a point on a stereo view far field clip plane, unproject it, then reproject it using the mono view. The stereo disparity offset is then
	// the difference between the original test point and the reprojected point.
	const FVector4 ProjectedPointAtLimit(0.0f, 0.0f, ViewFamily.MonoParameters.MonoDepthClip, 1.0f);
	const FVector4 WorldProjectedPoint = ViewFamily.Views[0]->ViewMatrices.GetInvViewProjectionMatrix().TransformFVector4(ProjectedPointAtLimit);
	FVector4 MonoProjectedPoint = MonoView.ViewMatrices.GetViewProjectionMatrix().TransformFVector4(WorldProjectedPoint / WorldProjectedPoint.W);
	MonoProjectedPoint = MonoProjectedPoint / MonoProjectedPoint.W;
	ViewFamily.MonoParameters.LateralOffset = (MonoProjectedPoint.X - ProjectedPointAtLimit.X) / 2.0f;
}

FSceneView* UBeeLocalPlayer::CalcSceneView(class FSceneViewFamily* ViewFamily,
	FVector& OutViewLocation,
	FRotator& OutViewRotation,
	FViewport* Viewport,
	class FViewElementDrawer* ViewDrawer,
	EStereoscopicPass StereoPass)
{
	FSceneViewInitOptions ViewInitOptions;

	if (!CalcSceneViewInitOptions(ViewInitOptions, Viewport, ViewDrawer, StereoPass))
	{
		return nullptr;
	}

	// Get the viewpoint...technically doing this twice
	// but it makes GetProjectionData better
	FMinimalViewInfo ViewInfo;
	GetViewPoint(ViewInfo, StereoPass);
	OutViewLocation = ViewInfo.Location;
	OutViewRotation = ViewInfo.Rotation;
	ViewInitOptions.bUseFieldOfViewForLOD = ViewInfo.bUseFieldOfViewForLOD;
	ViewInitOptions.FOV = ViewInfo.FOV;
	ViewInitOptions.DesiredFOV = ViewInfo.DesiredFOV;

	// Fill out the rest of the view init options
	ViewInitOptions.ViewFamily = ViewFamily;

	if (!PlayerController->bRenderPrimitiveComponents)
	{
		// Emplaces an empty show only primitive list.
		//ViewInitOptions.ShowOnlyPrimitives.Emplace();
		for (auto&x : ShowOnlyActors) {

			if (x) {
				for (UActorComponent* Component : x->GetComponents())
				{
					if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
					{
						ViewInitOptions.ShowOnlyPrimitives->Add(PrimComp->ComponentId);
					}
				}
			}
		}
	}
	else
	{
		QUICK_SCOPE_CYCLE_COUNTER(STAT_BuildHiddenComponentList);
		PlayerController->BuildHiddenComponentList(OutViewLocation, /*out*/ ViewInitOptions.HiddenPrimitives);
	}

	//@TODO: SPLITSCREEN: This call will have an issue with splitscreen, as the show flags are shared across the view family
	EngineShowFlagOrthographicOverride(ViewInitOptions.IsPerspectiveProjection(), ViewFamily->EngineShowFlags);

	FSceneView* const View = new FSceneView(ViewInitOptions);

	View->ViewLocation = OutViewLocation;
	View->ViewRotation = OutViewRotation;

	ViewFamily->Views.Add(View);

	{
		View->StartFinalPostprocessSettings(OutViewLocation);

		// CameraAnim override
		if (PlayerController->PlayerCameraManager)
		{
			TArray<FPostProcessSettings> const* CameraAnimPPSettings;
			TArray<float> const* CameraAnimPPBlendWeights;
			PlayerController->PlayerCameraManager->GetCachedPostProcessBlends(CameraAnimPPSettings, CameraAnimPPBlendWeights);

			for (int32 PPIdx = 0; PPIdx < CameraAnimPPBlendWeights->Num(); ++PPIdx)
			{
				View->OverridePostProcessSettings((*CameraAnimPPSettings)[PPIdx], (*CameraAnimPPBlendWeights)[PPIdx]);
			}
		}

		//	CAMERA OVERRIDE
		//	NOTE: Matinee works through this channel
		View->OverridePostProcessSettings(ViewInfo.PostProcessSettings, ViewInfo.PostProcessBlendWeight);

		if (PlayerController->PlayerCameraManager)
		{
			PlayerController->PlayerCameraManager->UpdatePhotographyPostProcessing(View->FinalPostProcessSettings);
		}

		View->EndFinalPostprocessSettings(ViewInitOptions);
	}

	for (int ViewExt = 0; ViewExt < ViewFamily->ViewExtensions.Num(); ViewExt++)
	{
		ViewFamily->ViewExtensions[ViewExt]->SetupView(*ViewFamily, *View);
	}

	// Monoscopic far field setup
	if (ViewFamily->IsMonoscopicFarFieldEnabled() && StereoPass == eSSP_MONOSCOPIC_EYE)
	{
		SetupMonoParameters(*ViewFamily, *View);
	}

	return View;
}

