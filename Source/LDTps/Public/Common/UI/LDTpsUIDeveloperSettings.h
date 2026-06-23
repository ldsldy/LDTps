// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "LDTpsUIDeveloperSettings.generated.h"

class UWidget_ActivatableBase;

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "LDTps UI Settings"))
class LDTPS_API ULDTpsUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "UI Assets", meta = (ForceInlineRow))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_ActivatableBase>> WidgetMap;

	UPROPERTY(Config, EditAnywhere, Category = "UI Assets", meta = (ForceInlineRow))
	TMap<FGameplayTag, TSoftObjectPtr<UTexture2D>> ImageMap;
};
