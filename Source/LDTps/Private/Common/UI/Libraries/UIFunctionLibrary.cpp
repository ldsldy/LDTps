// LDY of Project Settings.


#include "Common/UI/Libraries/UIFunctionLibrary.h"
#include "Common/UI/Settings/LDTpsUIDeveloperSettings.h"

TSoftClassPtr<UWidget_ActivatableBase> UUIFunctionLibrary::GetSoftWidgetClassByTag(UPARAM(meta = (Categories = "UI.Widget")) FGameplayTag InWidgetTag)
{
	const ULDTpsUIDeveloperSettings* UISettings = GetDefault<ULDTpsUIDeveloperSettings>();

	checkf(UISettings->WidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());
	
	// FindRef() 함수는 TMap에서 키에 해당하는 값을 참조로 반환하는 함수입니다.
	return UISettings->WidgetMap.FindRef(InWidgetTag);
}

TSoftObjectPtr<UTexture2D> UUIFunctionLibrary::GetSoftImageByTag(FGameplayTag InImageTag)
{
	const ULDTpsUIDeveloperSettings* UISettings = GetDefault<ULDTpsUIDeveloperSettings>();

	checkf(UISettings->ImageMap.Contains(InImageTag), TEXT("Could not find an image associated with tag %s"), *InImageTag.ToString());

	return UISettings->ImageMap.FindRef(InImageTag);
}

TSoftObjectPtr<UTexture2D> UUIFunctionLibrary::GetOptionsSoftImageByTag(FGameplayTag InImageTag)
{
	return GetSoftImageByTag(InImageTag);
}
