// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_String.generated.h"

class UFrontendCommonButtonBase;
class ULDTpsCommonRotator;
class UListDataObject_String;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class LDTPS_API UWidget_ListEntry_String : public UWidget_ListEntry_Base
{
	GENERATED_BODY()
	
protected:
	// ~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	// ~ End UUserWidget Interface

	// ~ Begin UWidget_ListEntry_Base Interface
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason) override;
	// ~ End UWidget_ListEntry_Base Interface

private:
	void OnPreviousOptionButtonClicked();
	void OnNextOptionButtonClicked();

	void OnRotatorValueChanged(int32 Value, bool bIsUserInitiated);

private:
	//****** Bound Widgets ****** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UFrontendCommonButtonBase* CommonButton_PreviousOption;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	ULDTpsCommonRotator* CommonRotator_AvailableOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UFrontendCommonButtonBase* CommonButton_NextOption;
	//****** Bound Widgets ****** //

	UPROPERTY(Transient)
	UListDataObject_String* CachedOwningStringDataObject;
};
