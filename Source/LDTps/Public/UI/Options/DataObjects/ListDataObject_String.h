// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Options/DataObjects/ListDataObject_Value.h"
#include "ListDataObject_String.generated.h"

/**
 * 
 */
UCLASS()
class LDTPS_API UListDataObject_String : public UListDataObject_Value
{
	GENERATED_BODY()
	
public:
	void AddDynamicOption(const FString& InStringValue, const FText& InDisplayText);
	void AdvanceToNextOption();
	void BackToPreviousOption();
	void OnRotatorInitializedValueChange(const FText& InNewSelectedText);

protected:
	// ~ Begin UListDataObject_Base Interface
	virtual void OnDataObjectInitialized() override;
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;
	// ~ End UListDataObject_Base Interface

	bool TrySetDisplayTextFromStringValue(const FString& InStringValue);

protected:
	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;

public:
	FORCEINLINE const TArray<FText>& GetAvailableOptionsTextArray() const { return AvailableOptionsTextArray; }
	FORCEINLINE const FText GetCurrentDisplayText() const { return CurrentDisplayText; }
};

UCLASS()
class LDTPS_API UListDataObject_StringBool : public UListDataObject_String
{
	GENERATED_BODY()

public:
	// True 디스플레이 텍스트를 오버라이드하여 새로운 텍스트로 설정합니다.
	void OverrideTrueDisplayText(const FText& InNewTrueDisplayText);

	// False 디스플레이 텍스트를 오버라이드하여 새로운 텍스트로 설정합니다.
	void OverrideFalseDisplayText(const FText& InNewFalseDisplayText);

	void SetTrueAsDefaultValue();
	void SetFalseAsDefaultValue();

protected:
	// ~Begin UListDataObject_String Interface
	virtual void OnDataObjectInitialized() override;
	// ~End UListDataObject_String Interface

private:
	// TryInitBoolValues 함수는 True와 False에 대한 기본 옵션을 초기화합니다. 만약 AvailableOptionsStringArray에 TrueString과 FalseString이 없다면, 이 함수는 해당 문자열과 디스플레이 텍스트를 추가합니다.
	void TryInitBoolValues();

	const FString TrueString = TEXT("True");
	const FString FalseString = TEXT("False");
};

UCLASS()
class LDTPS_API UListDataObject_StringEnum : public UListDataObject_String
{
	GENERATED_BODY()

public:
	template<typename EnumType>
	void AddEnumOption(EnumType InEnumOption, const FText& InDisplayText)
	{
		const UEnum* StaticEnumOption = StaticEnum<EnumType>();
		const FString ConvertedEnumString = StaticEnumOption->GetNameStringByValue(InEnumOption);
		
		// 키 값과 보여줄 텍스트를 배열에 추가합니다.
		AddDynamicOption(ConvertedEnumString, InDisplayText);
	}

	template<typename EnumType>
	EnumType GetCurrentValueAsEnum() const
	{
		const UEnum* StaticEnumOption = StaticEnum<EnumType>();

		// 현재 문자열 값을 Enum 값으로 변환하여 반환합니다.
		// String -> UEnum -> EnumType 캐스트
		return (EnumType)StaticEnumOption->GetValueByNameString(CurrentStringValue);
	}

	template<typename EnumType>
	void SetDefaultValueFromEnumOption(EnumType InEnumOption)
	{
		const UEnum* StaticEnumOption = StaticEnum<EnumType>();
		const FString ConvertedEnumString = StaticEnumOption->GetNameStringByValue(InEnumOption);

		// 기본값을 문자열을 받아서 설정합니다.
		SetDefaultValueFromString(ConvertedEnumString);
	}
};