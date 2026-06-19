// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "UIFunctionLibrary.generated.h"

class UWidget_ActivatableBase;

/**
 * 
 */
UCLASS()
class LDTPS_API UUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "UI Function Library")
	static TSoftClassPtr<UWidget_ActivatableBase> GetSoftWidgetClassByTag(UPARAM(meta = (Categories = "UI")) FGameplayTag InWidgetTag);

	UFUNCTION(BlueprintPure, Category = "UI Function Library")
	static TSoftObjectPtr<UTexture2D> GetSoftImageByTag(UPARAM(meta = (Categories = "UI")) FGameplayTag InImageTag);

	UFUNCTION(BlueprintPure, Category = "UI Function Library", meta = (DeprecatedFunction, DeprecationMessage = "Use GetSoftImageByTag instead."))
	static TSoftObjectPtr<UTexture2D> GetOptionsSoftImageByTag(UPARAM(meta = (Categories = "UI")) FGameplayTag InImageTag);

};
