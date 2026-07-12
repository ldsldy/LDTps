// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Options/DataObjects/ListDataObject_Base.h"
#include "ListDataObject_Value.generated.h"

class FOptionsDataInteractionHelper;

/**
 * 
 */
UCLASS(Abstract)
class LDTPS_API UListDataObject_Value : public UListDataObject_Base
{
	GENERATED_BODY()
	
public:
	// 런타임에 동적으로 바뀔수 있는 UListDataObject의 값에 접근하기 위한 Getter
	void SetDataDynamicGetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicGetter);
	// 런타임에 동적으로 바뀔수 있는 UListDataObject의 값에 접근하기 위한 Setter
	void SetDataDynamicSetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicSetter);

	void SetDefaultValueFromString(const FString& InDefaultValue) { DefaultStringValue = InDefaultValue; }

	//~ Begin UListDataObject_Base Interface
	virtual bool HasDefaultValue() const override { return DefaultStringValue.IsSet(); }
	// ~ End UListDataObject_Base Interface

protected:
	FString GetDefaultValueAsString() const { return DefaultStringValue.GetValue(); }

	TSharedPtr<FOptionsDataInteractionHelper> DataDynamicGetter;
	TSharedPtr<FOptionsDataInteractionHelper> DataDynamicSetter;

private:
	TOptional<FString> DefaultStringValue;
};
