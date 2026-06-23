// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/UI/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_Scalar.generated.h"

class UCommonNumericTextBlock;
class UAnalogSlider;
class UListDataObject_Scalar;

/**
 * 슬라이더로 값을 조정하는 리스트 항목 위젯입니다. (예시: 볼륨, 밝기 등)
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class LDTPS_API UWidget_ListEntry_Scalar : public UWidget_ListEntry_Base
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
	UFUNCTION()
	void OnSliderValueChanged(float InValue);

	// ****** Bound Widgets ****** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonNumericTextBlock* CommonNumeric_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UAnalogSlider* AnalogSlider_SettingSlider;
	// ****** Bound Widgets ****** //

	UPROPERTY(Transient) // 소유한 데이터 객체의 캐시된 포인터입니다. 데이터 객체가 변경될 때마다 업데이트됩니다. 런타임에만 사용하는 데이터에 이 프로퍼티를 붙여서 에디터에서 보이지 않도록 합니다.
	UListDataObject_Scalar* CachedOwningScalarDataObject;
};
