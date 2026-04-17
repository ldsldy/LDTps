// LDY of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_String.h"

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

	NotifyListDataModified(this);

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

	NotifyListDataModified(this);
}

void UListDataObject_String::OnDataObjectInitialized()
{
	if (!AvailableOptionsStringArray.IsEmpty())
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}

	// TODO : 저장된 문자열 값을 읽어서 CurrentStringValue에 사용하도록 해야 합니다.

	// CurrentStringValue에 해당하는 CurrentDisplayText를 설정합니다. 
	// 만약 CurrentStringValue가 AvailableOptionsStringArray에 없다면, 
	// CurrentDisplayText는 "Invalid Option"으로 설정됩니다.
	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
	}
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
