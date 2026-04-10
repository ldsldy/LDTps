// LDY of Project Settings.


#include "UIFunctionLibrary.h"
#include "FrontendSettings/FrontendDeveloperSettings.h"

TSoftClassPtr<UWidget_ActivatableBase> UUIFunctionLibrary::GetSoftWidgetClassByTag(UPARAM(meta = (Categories = "UI.Widget")) FGameplayTag InWidgetTag)
{
	const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();

	checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());
	
	// FindRef() 함수는 TMap에서 키에 해당하는 값을 참조로 반환하는 함수입니다.
	return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);
}
