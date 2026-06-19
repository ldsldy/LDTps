// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontendPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LDTPS_API AFrontendPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	//~ Begin APlayerController interface
	virtual void OnPossess(APawn* aPawn) override;
	//~ End APlayerController interface
};
