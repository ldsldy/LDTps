// LDY of Project Settings.


#include "Common/UI/Options/DataObjects/ListDataObject_Base.h"
#include "Core/Settings/LDTpsGameUserSettings.h"

void UListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}

void UListDataObject_Base::AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition)
{
	EditConditionDescArray.Add(InEditCondition);
}

bool UListDataObject_Base::IsDataCurrentlyEditable()
{
	bool bIsEditable = true;

	if (EditConditionDescArray.IsEmpty())
	{
		// 편집 조건이 없는 경우, 편집 가능으로 간주합니다.
		return bIsEditable;
	}
	
	FString CachedDisabledRichReason;

	for (const FOptionsDataEditConditionDescriptor& Condition : EditConditionDescArray)
	{
		if (!Condition.IsValid() || Condition.IsEidtConditionMet())
		{
			continue;
		}

		// 편집 조건이 충족되지 않은 경우, 편집 불가능으로 간주합니다.
		bIsEditable = false;

		CachedDisabledRichReason.Append(Condition.GetDisabledRichReason());

		SetDisabledRichText(FText::FromString(CachedDisabledRichReason));

		if (Condition.HasForcedStringValue())
		{
			const FString ForcedStringValue = Condition.GetDisabledForcedStringValue();
			
			// 현재 데이터 객체가 강제된 값으로 설정될 수 있는 경우
			if (CanSetToForcedStringValue(ForcedStringValue))
			{
				// 강제된 값으로 설정합니다.
				OnSetToForcedStringValue(ForcedStringValue);
			}
		}
	}

	return bIsEditable;
}

void UListDataObject_Base::OnDataObjectInitialized()
{
}

void UListDataObject_Base::NotifyListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedData, ModifyReason);

	if (bShouldApplyChangeImmediatly)
	{
		ULDTpsGameUserSettings::Get()->ApplySettings(true);
	}
}
