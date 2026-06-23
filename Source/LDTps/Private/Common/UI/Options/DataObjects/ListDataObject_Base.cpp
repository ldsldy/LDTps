// LDY of Project Settings.


#include "Common/UI/Options/DataObjects/ListDataObject_Base.h"
#include "Core/Settings/LDTpsGameUserSettings.h"

void UListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
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
