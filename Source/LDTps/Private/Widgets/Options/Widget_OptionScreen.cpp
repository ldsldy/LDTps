// LDY of Project Settings.


#include "Widgets/Options/Widget_OptionScreen.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Components/FrontendTabListWidgetBase.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Components/FrontendCommonListView.h"
#include "FrontendSettings/LDTpsGameUserSettings.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widgets/Options/Widget_OptionsDetailsView.h"
#include "Subsystems/LDTpsUISubsystem.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"

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

	CommonListView_OptionsList->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHovered);
	CommonListView_OptionsList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelected);
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

void UWidget_OptionScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	ULDTpsGameUserSettings::Get()->ApplySettings(true);
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
	if(ResettableDataArray.IsEmpty())
	{
		return;
	}

	UCommonButtonBase* SelectedTabButton = TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabListWidget_OptionsTabs->GetActiveTab()); // 현재 활성화된 탭의 버튼을 가져옵니다.

	const FString SelectedTabButtonName = CastChecked<UFrontendCommonButtonBase>(SelectedTabButton)->GetButtonDisplayText().ToString();

	// 사용자에게 리셋 확인을 요청하는 모달 스크린을 표시합니다. 사용자가 "예"를 선택하면 ResetableDataArray에 있는 데이터들을 기본값으로 리셋하는 로직을 구현할 수 있습니다.
	ULDTpsUISubsystem::Get(this)->PushConfirmScreenToModalStackAynsc(
		EConfirmScreenType::YesNo,
		FText::FromString(TEXT("Reset")),
		FText::FromString(TEXT("Are you sure you want to reset all the setting under the ") + SelectedTabButtonName + TEXT(" tab.")),
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			if (ClickedButtonType != EConfirmScreenButtonType::Confirmed)
			{
				return;
			}

			bIsResettingData = true;
			bool bHasDataFailedToReset = false;

			for (UListDataObject_Base* DataToReset : ResettableDataArray)
			{
				if (!DataToReset)
				{
					continue;
				}

				if (DataToReset->TryResetBackToDefaultValue())
				{
					Debug::Print(DataToReset->GetDataDisplayName().ToString() + TEXT(" was reset"));
				}
				else
				{
					bHasDataFailedToReset = true;
					Debug::Print(DataToReset->GetDataDisplayName().ToString() + TEXT(" failed to reset"));
				}
			}

			if (bHasDataFailedToReset)
			{
				ResettableDataArray.Empty();
				RemoveActionBinding(ResetActionHandle);
			}

			bIsResettingData = false;
		}
	);
}

void UWidget_OptionScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void UWidget_OptionScreen::OnOptionsTabSelected(FName TabId)
{
	DetailsView_ListEntryInfo->ClearDetailsViewInfo();

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

	// 탭이 변경될 때마다 ResetableDataArray를 초기화하여 이전 탭에서 리셋 가능한 데이터가 남아있지 않도록 합니다.
	// 그리고 새로 선택된 탭에 해당하는 아이템들 중에서 리셋이 가능한 데이터들을 찾아 ResetableDataArray에 추가합니다.
	// 이렇게 하면 탭이 변경될 때마다 리셋 가능한 데이터들이 올바르게 관리되고, 리셋 액션이 트리거될 때 해당 데이터들을 활용할 수 있게 됩니다.
	ResettableDataArray.Empty();

	for (UListDataObject_Base* FoundListSourceItem : FoundListSourceItems)
	{
		if (!FoundListSourceItem)
		{
			continue;
		}

		// 각 리스트 데이터가 수정될 때마다 해당 데이터의 OnListDataModified 리셋 가능 여부를 체크하여 ResetableDataArray에 추가하거나 제거하는 로직을 구현합니다.
		if (!FoundListSourceItem->OnListDataModified.IsBoundToObject(this))
		{
			FoundListSourceItem->OnListDataModified.AddUObject(this, &ThisClass::OnListViewListDataModified);
		}
		
		if (FoundListSourceItem->CanResetBackToDefaultValue()) // 리셋이 가능한 데이터라면
		{
			ResettableDataArray.AddUnique(FoundListSourceItem); // ResetableDataArray에 추가하여 추후 리셋 처리 시 활용할 수 있도록 합니다.
		}
	}

	// 리셋 가능한 데이터가 없는 경우, "리셋" 액션의 바인딩을 제거하여 비활성화합니다.
	if (ResettableDataArray.IsEmpty())
	{
		RemoveActionBinding(ResetActionHandle);
	}
	else
	{
		// 리셋 가능한 데이터가 존재하는 경우, "리셋" 액션이 바인딩되어 있지 않다면 바인딩을 추가하여 활성화합니다.
		if (!GetActionBindings().Contains(ResetActionHandle))
		{
			AddActionBinding(ResetActionHandle);
		}
	}
}

void UWidget_OptionScreen::OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered)
{
	if (!InHoveredItem)
	{
		return;
	}

	UWidget_ListEntry_Base* HoveredEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem<UWidget_ListEntry_Base>(InHoveredItem);

	check(HoveredEntryWidget);

	HoveredEntryWidget->NativeOnListEntryWidgetHovered(bWasHovered);

	if (bWasHovered)
	{
		DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
			CastChecked<UListDataObject_Base>(InHoveredItem),
			TryGetEntryWidgetClassName(InHoveredItem)
		);
	}
	else
	{
		if (UListDataObject_Base* SelectedItem = CommonListView_OptionsList->GetSelectedItem<UListDataObject_Base>())
		{
			DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
				SelectedItem,
				TryGetEntryWidgetClassName(SelectedItem)
			);
		}
	}
}

void UWidget_OptionScreen::OnListViewItemSelected(UObject* InSelectedItem)
{
	if (!InSelectedItem)
	{
		return;
	}

	DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
		CastChecked<UListDataObject_Base>(InSelectedItem),
		TryGetEntryWidgetClassName(InSelectedItem)
	);

}

FString UWidget_OptionScreen::TryGetEntryWidgetClassName(UObject* InOwningListItem) const
{
	if (UUserWidget* FoundEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(InOwningListItem))
	{
		return FoundEntryWidget->GetClass()->GetName();
	}

	return TEXT("Entry Widget Not Valid");
}

void UWidget_OptionScreen::OnListViewListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (!ModifiedData || bIsResettingData)
	{
		return;
	}

	if (ModifiedData->CanResetBackToDefaultValue())
	{
		// 리셋이 가능한 데이터가 수정된 경우, ResetableDataArray에 해당 데이터를 추가하여 리셋 대상으로 간주되도록 합니다.
		ResettableDataArray.AddUnique(ModifiedData);

		if(!GetActionBindings().Contains(ResetActionHandle))
		{	// "리셋" 액션이 바인딩되어 있지 않다면 바인딩을 추가하여 활성화합니다.

			AddActionBinding(ResetActionHandle);
		}
	}
	else
	{
		// 리셋이 불가능한 데이터가 수정된 경우, ResetableDataArray에서 해당 데이터를 제거하여 더 이상 리셋 대상으로 간주되지 않도록 합니다.
		if (ResettableDataArray.Contains(ModifiedData))
		{
			ResettableDataArray.Remove(ModifiedData);
		}
	}

	if(ResettableDataArray.IsEmpty())
	{	
		// 리셋 가능한 데이터가 없는 경우, "리셋" 액션의 바인딩을 제거하여 비활성화합니다.
		RemoveActionBinding(ResetActionHandle);
	}
}
