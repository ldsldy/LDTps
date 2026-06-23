// LDY of Project Settings.


#include "Common/UI/Options/DataObjects/ListDataObject_Scalar.h"
#include "Common/UI/Options/Data/OptionsDataInteractionHelper.h"

FCommonNumberFormattingOptions UListDataObject_Scalar::NoDecimal()
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = 0; // 소수점 이하 자릿수를 0으로 설정하여 소수점이 표시되지 않도록 합니다.
	
	return Options;
}

FCommonNumberFormattingOptions UListDataObject_Scalar::WithDecimal(int32 NumFracDigit)
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = NumFracDigit; // 소수점 이하 자릿수를 지정하여 숫자 형식 옵션을 생성합니다.

	return Options;
}


float UListDataObject_Scalar::GetCurrentValue() const
{
	if (DataDynamicGetter)
	{
		// 문자열로 실제 설정값 획득 => float로 변환 => OutputValueRange에서 현재 위치 계산 => DisplayValueRange의 대응 값으로 변환(범위를 벗어나면 최솟값/최댓값으로 제한)
		// 예를 들어, 0.5가 OutputValueRange(0~1)에서 0.5에 해당하면, DisplayValueRange(0~100)에서는 50에 해당합니다.
		return FMath::GetMappedRangeValueClamped(
			OutputValueRange,
			DisplayValueRange,
			StringToFloat(DataDynamicGetter->GetValueAsString())
		);
	}

	return 0.f; // 동적 게터가 설정되지 않은 경우, 기본값으로 0을 반환합니다.
}

float UListDataObject_Scalar::StringToFloat(const FString& InString) const
{
	float OutConvertedValue = 0.f;

	LexFromString(OutConvertedValue, *InString);
	
	return OutConvertedValue;
}
