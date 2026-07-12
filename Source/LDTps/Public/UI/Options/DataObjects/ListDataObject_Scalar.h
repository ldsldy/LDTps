// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Options/DataObjects/ListDataObject_Value.h"
#include "CommonNumericTextBlock.h"
#include "ListDataObject_Scalar.generated.h"

/**
 * 스칼라 값을 가지는 리스트 데이터 객체를 나타내는 클래스입니다. 이 클래스는 UListDataObject_Base를 상속하며, 스칼라 값과 관련된 기능을 제공합니다.
 */
UCLASS()
class LDTPS_API UListDataObject_Scalar : public UListDataObject_Value
{
	GENERATED_BODY()
	
public:
	// GETTER와 SETTER를 정의하는 매크로로 부모 클래스에 정의되어 있습니다.
	LIST_DATA_ACCESSOR(TRange<float>, DisplayValueRange)
	LIST_DATA_ACCESSOR(TRange<float>, OutputValueRange)
	LIST_DATA_ACCESSOR(float, SliderStepSize)
	LIST_DATA_ACCESSOR(ECommonNumericType, DisplayNumericType)
	LIST_DATA_ACCESSOR(FCommonNumberFormattingOptions, NumberFormattingOptions)

	static FCommonNumberFormattingOptions NoDecimal();
	static FCommonNumberFormattingOptions WithDecimal(int32 NumFracDigit); // 소수점 이하 자릿수를 지정하여 숫자 형식 옵션을 생성하는 정적 함수입니다.

	float GetCurrentValue() const;
	void SetCurrentValueFromSlider(float InNewValue);

private:
	// ~ Begin UListDataObject_Base Interface
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;
	// ~ End UListDataObject_Base Interface

	// 문자열을 float로 변환하는 헬퍼 함수입니다.
	float StringToFloat(const FString& InString) const;

	TRange<float> DisplayValueRange = TRange<float>(0.f, 1.f);
	TRange<float> OutputValueRange = TRange<float>(0.f, 1.f); // 출력 값의 범위를 나타내는 범위
	float SliderStepSize = 0.1f; // 슬라이더를 움직일 때, 한 번에 움직이는 값의 크기
	ECommonNumericType DisplayNumericType = ECommonNumericType::Number; // ECommonNumericType은 CommonNumericTextBlock.h에 정의되어 있으며, 숫자, 퍼센트, 초, 거리 등의 타입을 나타냅니다.
	FCommonNumberFormattingOptions NumberFormattingOptions; // 숫자 형식 옵션 : CommonNumericTextBlock.h에 정의되어 있으며, 숫자 형식 옵션을 설정할 수 있습니다.
};
