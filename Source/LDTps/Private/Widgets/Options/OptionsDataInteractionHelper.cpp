// LDY of Project Settings.


#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "FrontendSettings/LDTpsGameUserSettings.h"

FOptionsDataInteractionHelper::FOptionsDataInteractionHelper(const FString& InSetterOrGetterFunctionPath)
	: CachedDynamicFunctionPath(InSetterOrGetterFunctionPath)
{
	CachedWeakGameUserSettings = ULDTpsGameUserSettings::Get();	
}

FString FOptionsDataInteractionHelper::GetValueAsString() const
{
	FString OutStringValue;
	PropertyPathHelpers::GetPropertyValueAsString(
		CachedWeakGameUserSettings.Get(),		// 얻을 값이 있는 객체
		CachedDynamicFunctionPath,				//
		OutStringValue);

	return OutStringValue;
}

void FOptionsDataInteractionHelper::SetValueFromString(const FString& InStringValue)
{
	PropertyPathHelpers::SetPropertyValueFromString(
		CachedWeakGameUserSettings.Get(),		// 값을 설정할 객체
		CachedDynamicFunctionPath,				
		InStringValue);
}