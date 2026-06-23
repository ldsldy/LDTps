// LDY of Project Settings.


#include "Common/UI/Options/ListEntries/Widget_ListEntry_Scalar.h"
#include "Common/UI/Options/DataObjects/ListDataObject_Scalar.h"
#include "AnalogSlider.h"

void UWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AnalogSlider_SettingSlider->OnValueChanged.AddUniqueDynamic(this, &ThisClass::OnSliderValueChanged);
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningScalarDataObject = CastChecked<UListDataObject_Scalar>(InOwningListDataObject);

	CommonNumeric_SettingValue->SetNumericType(CachedOwningScalarDataObject->GetDisplayNumericType());				  // 숫자 타입을 데이터 객체에서 가져와서 설정합니다.
	CommonNumeric_SettingValue->FormattingSpecification = CachedOwningScalarDataObject->GetNumberFormattingOptions(); // 숫자 형식 옵션을 데이터 객체에서 가져와서 설정합니다.
	CommonNumeric_SettingValue->SetCurrentValue(CachedOwningScalarDataObject->GetCurrentValue());					  // 현재 값을 데이터 객체에서 가져와서 설정합니다.

	AnalogSlider_SettingSlider->SetMinValue(CachedOwningScalarDataObject->GetDisplayValueRange().GetLowerBoundValue()); // 슬라이더의 최소값을 데이터 객체에서 가져와서 설정합니다.
	AnalogSlider_SettingSlider->SetMaxValue(CachedOwningScalarDataObject->GetDisplayValueRange().GetUpperBoundValue()); // 슬라이더의 최대값을 데이터 객체에서 가져와서 설정합니다.
	AnalogSlider_SettingSlider->SetStepSize(CachedOwningScalarDataObject->GetSliderStepSize());							// 슬라이더의 스텝 사이즈를 데이터 객체에서 가져와서 설정합니다.
	AnalogSlider_SettingSlider->SetValue(CachedOwningScalarDataObject->GetCurrentValue());								// 슬라이더의 현재 값을 데이터 객체에서 가져와서 설정합니다.
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	if (CachedOwningScalarDataObject)
	{
		CommonNumeric_SettingValue->SetCurrentValue(CachedOwningScalarDataObject->GetCurrentValue()); // 데이터 객체가 수정되면, 숫자 텍스트 블록의 값을 업데이트합니다.
		AnalogSlider_SettingSlider->SetValue(CachedOwningScalarDataObject->GetCurrentValue());		  // 데이터 객체가 수정되면, 슬라이더의 값을 업데이트합니다.
	}
}

void UWidget_ListEntry_Scalar::OnSliderValueChanged(float InValue)
{
	if (CachedOwningScalarDataObject)
	{
		CachedOwningScalarDataObject->SetCurrentValueFromSlider(InValue); // 슬라이더의 값이 변경되면, 데이터 객체의 값을 업데이트합니다.
	}
}