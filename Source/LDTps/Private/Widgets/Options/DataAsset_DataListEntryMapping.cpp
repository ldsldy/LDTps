// LDY of Project Settings.


#include "Widgets/Options/DataAsset_DataListEntryMapping.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

TSubclassOf<UWidget_ListEntry_Base> UDataAsset_DataListEntryMapping::FindEntryWidgetClassByDataObject(UListDataObject_Base* InDataObject) const
{
	check(InDataObject);

	// InDataObject의 클래스와 그 부모 클래스들을 순회하면서
	// DataObjectListEntryMap에 매핑된 엔트리가 있는지 확인합니다.
	// 이를 통하여 DataObjectClass의 직접적인 부모 클래스에 매핑된 엔트리가 있다면, 그 엔트리를 반환할 수 있도록 합니다.
	for (UClass* DataObjectClass = InDataObject->GetClass(); DataObjectClass; DataObjectClass->GetSuperClass())
	{
		if (TSubclassOf<UListDataObject_Base> ConvertedDataObjectClass = TSubclassOf<UListDataObject_Base>(DataObjectClass))
		{
			if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
			{
				return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
			}
		}
	}

	return TSubclassOf<UWidget_ListEntry_Base>();
}
