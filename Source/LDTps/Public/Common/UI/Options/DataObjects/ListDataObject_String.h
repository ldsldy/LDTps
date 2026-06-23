// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/UI/Options/DataObjects/ListDataObject_Value.h"
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