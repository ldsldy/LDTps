// LDY of Project Settings.


#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	// 인터페이스는 직접적인 상속이 아닌 간접적인 상속이므로, 
	// IUserObjectListEntry의 NativeOnListItemObjectSet을 명시적으로 호출해야 합니다.
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
}
