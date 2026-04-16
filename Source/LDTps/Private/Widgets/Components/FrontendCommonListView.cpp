// LDY of Project Settings.


#include "Widgets/Components/FrontendCommonListView.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Options/DataAsset_DataListEntryMapping.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

UUserWidget& UFrontendCommonListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (IsDesignTime())
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}

	TSubclassOf<UWidget_ListEntry_Base> FoundWidgetClass = DataListEntryMapping->FindEntryWidgetClassByDataObject(CastChecked<UListDataObject_Base>(Item));
	
	// 템플릿 함수
	// 리스트뷰 엔트리용 UUserWidget을 풀에서 재사용하거나 생성하고, 
	// 그 위젯을 감싸는 Slate Row를 만들고, 
	// Hover/Drag 같은 이벤트를 연결한 뒤 
	// 최종 초기화까지 마쳐서 반환하는 함수.
	return GenerateTypedEntry<UWidget_ListEntry_Base>(FoundWidgetClass, OwnerTable);
}

#if WITH_EDITOR
void UFrontendCommonListView::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!DataListEntryMapping)
	{
		CompileLog.Error(FText::FromString(TEXT("The Variable DataListEntryMapping has no valid data asset assigned") +
			GetClass()->GetName() +
			TEXT(" needs a valid data asset to function properly")
		));
	}
}
#endif
