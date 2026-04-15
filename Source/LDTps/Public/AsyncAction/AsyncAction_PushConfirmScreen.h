// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Types/LDTpsUIEnum.h"
#include "AsyncAction_PushConfirmScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate, EConfirmScreenButtonType, ClickedButtonType);

/**
 * 
 */
UCLASS()
class LDTPS_API UAsyncAction_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	// 비동기 작업 개체를 생성 및 초기화하여 블루프린트에 반환하는 팩토리 함수입니다.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Show Confirmation Screen"))
	static UAsyncAction_PushConfirmScreen* PushConfirmScreen(
		const UObject* WorldContextObject,
		EConfirmScreenType ScreenType,
		FText InScreenTitle,
		FText InScreenMessage
	);

	// ~Begin UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	// ~End UBlueprintAsyncActionBase interface

public:
	UPROPERTY(BlueprintAssignable)
	FOnConfirmScreenButtonClickedDelegate OnButtonClicked;

private:
	TWeakObjectPtr<UWorld> CachedOwningWorld;
	EConfirmScreenType CachedScreenType;
	FText CachedScreenTitle;
	FText CachedScreenMessage;
};
