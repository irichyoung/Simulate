#include "BeePlayerController.h"

void ABeePlayerController::SetHiddenActors(TArray<AActor*>&actors) {
	BeeHiddenActors = actors;
}

void ABeePlayerController::UpdateHiddenActors(const FVector& ViewLocation) {
	HiddenActors = BeeHiddenActors;
}