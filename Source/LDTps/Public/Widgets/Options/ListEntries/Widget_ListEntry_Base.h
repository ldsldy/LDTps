// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;

/**
 *  옵션의 위젯 엔트리를 위한 베이스 클래스입니다. 옵션의 위젯 엔트리는 CommonListView에서 아이템을 표현하기 위해 사용되는 엔트리 위젯입니다.
 */
// 추상화 클래스를 통해 블루프린트로 상속받아야 사용할 수 있도록 설정.
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class LDTPS_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	// ~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	// ~ End IUserObjectListEntry Interface

private:
	// ****** Bound Widgets ****** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;
	// ****** Bound Widgets ****** //
};
