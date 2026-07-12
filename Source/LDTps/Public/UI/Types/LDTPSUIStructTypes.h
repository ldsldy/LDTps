#pragma once

#include "LDTPSUIStructTypes.generated.h"

//
// *객체에 편집 조건을 설정하기 위한 구조체
//
USTRUCT()
struct FOptionsDataEditConditionDescriptor
{
	GENERATED_BODY()

public:
	// 편집 가능 조건을 결정하는 함수를 설정합니다.
	void SetEditConditionFunc(TFunction<bool()> InEditConditionFunc)
	{
		EditConditionFunc = InEditConditionFunc;
	}

	// 편집 조건이 설정되었는지 확인합니다.
	bool IsValid() const
	{
		return EditConditionFunc != nullptr;
	}

	// 편집 조건이 설정된 이후 편집 조건이 충족 되었는지 확인합니다.
	bool IsEidtConditionMet() const
	{
		if (IsValid())
		{
			return EditConditionFunc();
		}

		return true;
	}

	FString GetDisabledRichReason() const
	{
		return DisabledRichReason;
	}

	void SetDisabledRichReason(const FString& InDisabledRichReason)
	{
		DisabledRichReason = InDisabledRichReason;
	}

	bool HasForcedStringValue() const
	{
		return DisabledForcedStringValue.IsSet();
	}

	FString GetDisabledForcedStringValue() const
	{
		return DisabledForcedStringValue.GetValue();
	}

	void SetDisabledForcedStringValue(const FString& InForcedValue)
	{
		DisabledForcedStringValue = InForcedValue;
	}

private:
	// 편집 가능 여부를 결정하는 함수입니다. 이 함수가 true를 반환하면 해당 데이터는 편집 가능하며, false를 반환하면 편집 불가능합니다.
	TFunction<bool()> EditConditionFunc;

	// 편집 조건이 충족되지 않았을 때 보여지는 이유를 나타내는 문자열입니다.
	FString DisabledRichReason;

	// 편집 조건이 충족되지 않았을 때 강제로 보여지는 문자열 값입니다.
	TOptional<FString> DisabledForcedStringValue;
};