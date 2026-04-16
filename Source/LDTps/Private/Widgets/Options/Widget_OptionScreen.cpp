// LDY of Project Settings.


#include "Widgets/Options/Widget_OptionScreen.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Components/FrontendTabListWidgetBase.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Components/FrontendCommonListView.h"

#include "LDTpsDebugHelper.h"

void UWidget_OptionScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		// "리셋" 액션을 등록합니다.
		// FBindUIActionArgs 구조체를 사용하여 액션 바인딩을 설정합니다.
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,    // 데이터 테이블 행 핸들
				true,           // 액션 바에 표시 여부
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered) // 액션이 트리거될 때 호출될 델리게이트
			)
		);
	}

	// "뒤로 가기" 액션을 등록합니다. 
	// ICommonInputModule에서 기본 뒤로 가기 액션을 가져와서 바인딩합니다.
	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)
		)
	);

	TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);
}

void UWidget_OptionScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	// 옵션 화면이 활성화될 때마다 데이터 레지스트리를 가져오거나 생성하여 각 탭 컬렉션에 대한 처리를 수행합니다.
	for(UListDataObject_Collection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		// 각 탭 컬렉션에 대한 처리 로직을 여기에 추가합니다.
		if (!TabCollection)
		{
			continue;
		}

		const FName TabID = TabCollection->GetDataID();

		// ID를 찾는다면 이미 이전에 탭이 생성되어 있다는 뜻이므로 새로 등록하지 않습니다.
		if (TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabID) != nullptr)
		{
			continue;
		}

		// ID를 찾을 수 없다면 새로 탭을 등록합니다.
		TabListWidget_OptionsTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

UOptionsDataRegistry* UWidget_OptionScreen::GetOrCreateDataRegistry()
{
	// 옵션 화면에서 데이터 레지스트리가 이미 생성되어 있는지 확인합니다. 
	// 없다면 새로 생성하고 초기화합니다.
	if (!CreatedOwningDataRegistry)
	{
		CreatedOwningDataRegistry = NewObject<UOptionsDataRegistry>();
		CreatedOwningDataRegistry->InitOptionDataRegistry(GetOwningLocalPlayer());
	}

	checkf(CreatedOwningDataRegistry, TEXT("Data registry for options screen is not valid"));

	return CreatedOwningDataRegistry;
}

void UWidget_OptionScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered!"));
}

void UWidget_OptionScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void UWidget_OptionScreen::OnOptionsTabSelected(FName TabId)
{
	TArray<UListDataObject_Base*> FoundListSourceItems = GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabId);
	
	CommonListView_OptionsList->SetListItems(FoundListSourceItems);
	CommonListView_OptionsList->RequestRefresh();

	// CommonListView_OptionsList의 아이템 갯수가 0이 아니라면,
	// 인덱스 0으로 이동하여 해당 아이템을 선택 상태로 만듭니다.
	if (CommonListView_OptionsList->GetNumItems() != 0)
	{
		CommonListView_OptionsList->NavigateToIndex(0);
		CommonListView_OptionsList->SetSelectedIndex(0);
	}
}
