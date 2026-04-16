// LDY of Project Settings.


#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

void UListDataObject_Collection::AddChildListData(UListDataObject_Base* InChildListData)
{
	// 자녀 목록 데이가 스스로 초기화될 수 있도록 알림
	InChildListData->InitDataObject();

	//자식의 리스트 데이터의 부모로 이 데이터 객체를 설정합니다.
	InChildListData->SetParentData(this);

	ChildListDataArray.Add(InChildListData);
}

TArray<UListDataObject_Base*> UListDataObject_Collection::GetChildSettingData() const
{
	return ChildListDataArray;
}

bool UListDataObject_Collection::HasAnyChildListData() const
{
	return !ChildListDataArray.IsEmpty();
}
