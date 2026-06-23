// LDY of Project Settings.


#include "Common/UI/Options/Data/OptionsDataInteractionHelper.h"
#include "Core/Settings/LDTpsGameUserSettings.h"

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
