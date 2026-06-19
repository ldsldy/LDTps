// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableBase.generated.h"

class APlayerController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class LDTPS_API UWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	APlayerController* GetOwningLDTpsPlayerController();
private:
	TWeakObjectPtr<APlayerController> CachedOwningPlayerController;
};
