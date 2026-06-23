// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class ULDTpsGameUserSettings;

/**
 *  다양한 데이터 타입을 처리하기 위한 헬퍼 클래스입니다. 이 클래스는 언리얼의 UFUNCTION 리플렉션 시스템을 통해 동적으로 값을 가져오거나 설정할 수 있도록 도와줍니다.
 */
class LDTPS_API FOptionsDataInteractionHelper
{
public:
	FOptionsDataInteractionHelper(const FString& InSetterOrGetterFunctionPath);

	// 함수를 언리얼의 UFUNCTION 리플렉션 시스템을 통해 호출하여 값을 가져옵니다.
	FString GetValueAsString() const;
	// 언리얼의 UFUNCTION 리플렉션 시스템을 통해 함수를 호출하여 값을 설정합니다.
	void SetValueFromString(const FString& InStringValue);

private:
	FCachedPropertyPath CachedDynamicFunctionPath;
	TWeakObjectPtr<ULDTpsGameUserSettings> CachedWeakGameUserSettings;
};
