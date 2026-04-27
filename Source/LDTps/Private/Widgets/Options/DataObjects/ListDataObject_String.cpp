// LDY of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"

#include "LDTpsDebugHelper.h"

void UListDataObject_String::OnDataObjectInitialized()
{
	if (!AvailableOptionsStringArray.IsEmpty())
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}

	// 만약 기본값이 있다면, CurrentStringValue을 기본값으로 초기화합니다.
	if (HasDefaultValue())
	{
		CurrentStringValue = GetDefaultValueAsString();
	}

	// 저장된 값이 있다면 CurrentStringValue에 저장된 값을 사용하도록 해야 합니다.
	if (DataDynamicGetter)
	{
		if (!DataDynamicGetter->GetValueAsString().IsEmpty())
		{
			CurrentStringValue = DataDynamicGetter->GetValueAsString();
		}
	}

	// CurrentStringValue에 해당하는 CurrentDisplayText를 설정합니다. 
	// 만약 CurrentStringValue가 AvailableOptionsStringArray에 없다면, 
	// CurrentDisplayText는 "Invalid Option"으로 설정됩니다.
	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
	}
}

void UListDataObject_String::AddDynamicOption(const FString& InStringValue, const FText& InDisplayText)
{
	AvailableOptionsStringArray.Add(InStringValue);
	AvailableOptionsTextArray.Add(InDisplayText);
}

void UListDataObject_String::AdvanceToNextOption()
{
	if(AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
	{
		return;
	}

	const int32 CurrentDisplayIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 NextIndexToDisplay = CurrentDisplayIndex + 1;

	const bool bIsNextIndexValid = AvailableOptionsStringArray.IsValidIndex(NextIndexToDisplay);

	if (bIsNextIndexValid)
	{
		// 다음 인덱스가 유효하다면, CurrentStringValue을 다음 인덱스에 해당하는 문자열로 업데이트합니다.
		CurrentStringValue = AvailableOptionsStringArray[NextIndexToDisplay];
	}
	else
	{
		// 다음 인덱스가 유효하지 않다면, CurrentStringValue을 첫 번째 인덱스에 해당하는 문자열로 업데이트합니다.
		CurrentStringValue = AvailableOptionsStringArray[0];
	}

	// CurrentStringValue에 해당하는 CurrentDisplayText를 설정합니다.
	TrySetDisplayTextFromStringValue(CurrentStringValue);

	// 문자열 값을 DynamicSetter를 통해 LDTpsGameUserSettings에 저장합니다.
	if (DataDynamicSetter)
	{
		DataDynamicSetter->SetValueFromString(CurrentStringValue);
		
		Debug::Print(TEXT("DataDynamicSetter is used. The latest value from Getter: ") + DataDynamicGetter->GetValueAsString());

		// 이 데이터 오브젝트가 수정되었다는 것을 알립니다. 
		// 이를 통해 이 데이터 오브젝트를 참조하는 다른 데이터 오브젝트나 UI 위젯이 변경 사항을 인지하고 업데이트할 수 있도록 합니다.
		NotifyListDataModified(this);
	}
}

void UListDataObject_String::BackToPreviousOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty())
	{
		return;
	}

	const int32 CurrentDisplayIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 PreviousIndexToDisplay = CurrentDisplayIndex - 1;

	const bool bIsPrevIndexValid = AvailableOptionsStringArray.IsValidIndex(PreviousIndexToDisplay);
	
	if (bIsPrevIndexValid)
	{
		// 이전 인덱스가 유효하다면, CurrentStringValue을 이전 인덱스에 해당하는 문자열로 업데이트합니다.
		CurrentStringValue = AvailableOptionsStringArray[PreviousIndexToDisplay];
	}
	else
	{
		// 이전 인덱스가 유효하지 않다면, CurrentStringValue을 마지막 인덱스에 해당하는 문자열로 업데이트합니다.
		CurrentStringValue = AvailableOptionsStringArray.Last();
	}

	// CurrentStringValue에 해당하는 CurrentDisplayText를 설정합니다.
	TrySetDisplayTextFromStringValue(CurrentStringValue);

	// 문자열 값을 DynamicSetter를 통해 LDTpsGameUserSettings에 저장합니다.
	if (DataDynamicSetter)
	{
		DataDynamicSetter->SetValueFromString(CurrentStringValue);

		Debug::Print(TEXT("DataDynamicSetter is used. The latest value from Getter: ") + DataDynamicGetter->GetValueAsString());

		NotifyListDataModified(this);
	}
}

void UListDataObject_String::OnRotatorInitializedValueChange(const FText& InNewSelectedText)
{
	const int32 FoundIndex = AvailableOptionsTextArray.IndexOfByPredicate(
		[InNewSelectedText](const FText& AvailableText)->bool
		{
			return AvailableText.EqualTo(InNewSelectedText);
		}
	);

	if (FoundIndex != INDEX_NONE && AvailableOptionsStringArray.IsValidIndex(FoundIndex))
	{
		CurrentDisplayText = InNewSelectedText;
		CurrentStringValue = AvailableOptionsStringArray[FoundIndex];

		if (DataDynamicSetter)
		{
			DataDynamicSetter->SetValueFromString(CurrentStringValue);

			NotifyListDataModified(this);
		}
	}
}

bool UListDataObject_String::CanResetBackToDefaultValue() const
{
	return HasDefaultValue() && CurrentStringValue != GetDefaultValueAsString();
}

bool UListDataObject_String::TryResetBackToDefaultValue()
{
	if (CanResetBackToDefaultValue())
	{
		CurrentStringValue = GetDefaultValueAsString();

		TrySetDisplayTextFromStringValue(CurrentStringValue);

		if (DataDynamicSetter)
		{
			DataDynamicSetter->SetValueFromString(CurrentStringValue);

			NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

			return true;
		}
	}
	return false;
}

bool UListDataObject_String::TrySetDisplayTextFromStringValue(const FString& InStringValue)
{
	const int32 CurrentFoundIndex = AvailableOptionsStringArray.IndexOfByKey(InStringValue);

	if (AvailableOptionsTextArray.IsValidIndex(CurrentFoundIndex))
	{
		CurrentDisplayText = AvailableOptionsTextArray[CurrentFoundIndex];
		
		return true;
	}

	return false;
}
