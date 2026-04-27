// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Types/LDTPSUIEnum.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;
class UListDataObject_Base;

/**
 *  옵션의 위젯 엔트리를 위한 베이스 클래스입니다. 옵션의 위젯 엔트리는 CommonListView에서 아이템을 표현하기 위해 사용되는 엔트리 위젯입니다.
 */
// 추상화 클래스를 통해 블루프린트로 상속받아야 사용할 수 있도록 설정.
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class LDTPS_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);
	void NativeOnListEntryWidgetHovered(bool bWasHovered);

protected:
	// 게임패드 상호작용이 제대로 작동하려면 자식 위젯 블루프린트가 이 함수를 오버라이드해야 합니다.
	UFUNCTION(BlueprintImplementableEvent, meta  = (DisplayName = "Get Widget To Focus For Gamepad"))
	UWidget* BP_GetWidgetToFocusForGamepad() const;

	// ~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	// ~ End IUserObjectListEntry Interface

	// ~ Begin UUserWidget Interface
	//FocusEvent는 위젯이 포커스를 받을 때 발생하는 이벤트입니다. 이 함수를 오버라이드하여 포커스가 필요한 위젯에서 포커스 수신 시 필요한 처리를 할 수 있습니다.
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	// ~ End UUserWidget Interface

	// 하위 클래스는 이 함수를 오버라이드하여 필요한 초기화 처리를 해야 합니다. super 호출이 예상됩니다.
	// NativeOnListItemObjectSet, 즉, 아이템이 설정될 때마다 호출됩니다.
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject);

	// 하위 클래스는 이 함수를 오버라이드하여 데이터 오브젝트가 수정된 후 UI 값을 업데이트하는 처리를 해야 합니다. super 호출은 필요하지 않습니다.
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason);

	void SelectThisEntryWidget();

private:
	// ****** Bound Widgets ****** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;
	// ****** Bound Widgets ****** //
};
