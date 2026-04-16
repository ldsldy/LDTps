// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_OptionScreen.generated.h"

class UOptionsDataRegistry;
class UFrontendTabListWidgetBase;
/**
 * 
 */
UCLASS()
class LDTPS_API UWidget_OptionScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()
	
protected:
	// ~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	// ~ End UUserWidget Interface

	// ~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	// ~ End UCommonActivatableWidget Interface

private:
	UOptionsDataRegistry* GetOrCreateDataRegistry();

	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();

	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);

private:
	// ****** Bound Widgets ****** //
	UPROPERTY(meta = (BindWidget))
	UFrontendTabListWidgetBase* TabListWidget_OptionsTabs;
	// ****** Bound Widgets ****** //

	// 옵션 화면에서 데이터의 생성을 처리하는 핸들러, 이 변수에 대한 직접 액세스는 금지됩니다.
	UPROPERTY(Transient)
	UOptionsDataRegistry* CreatedOwningDataRegistry;

	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;
};
