#pragma once

#include "GameFramework/PlayerController.h"
#include "BeePlayerController.generated.h"

UCLASS()
class ABeePlayerController :public APlayerController {
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
		void SetHiddenActors(TArray<AActor*>&actors);
		
	virtual void UpdateHiddenActors(const FVector& ViewLocation)override;
private:
	TArray<AActor*>BeeHiddenActors;
};