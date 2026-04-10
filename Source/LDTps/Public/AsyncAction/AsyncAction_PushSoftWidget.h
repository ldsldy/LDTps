// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "AsyncAction_PushSoftWidget.generated.h"

class UWidget_ActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UWidget_ActivatableBase*, PushedWidget);

/**
 * 
 */
UCLASS()
class LDTPS_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	// SoftClassPtr은 메모리 주소값이 아닌 경로값이기 때문에, 해당 경로에 있는 에셋이 로드될 때까지 기다려야 한다.
	// WorldContext = "WorldContextObject"는 이 함수가 블루프린트에서 메타 키워드를 통해서 WorldContextObject를 설정할 수 있게 해준다. (EX) Get Player Pawn 노드
	// 비동기 작업 객체를 생성, 초기화하여 블루프린트에 반환하는 팩토리 함수
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget To Widget Stack"))
	static UAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
		APlayerController* OwningPlayerController,
		TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
		UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag,
		bool bFocusOnNewlyPushedWidget = true);

	// ~Begin UBlueprintAsyncActionBase interface
	// 실제 비동기 로직이 시작되는 곳입니다. Activate 함수는 블루프린트에서 노드가 실행될 때 자동으로 호출됩니다.
	virtual void Activate() override;
	// ~End UBlueprintAsyncActionBase interface

public:
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;

private:
	TWeakObjectPtr<UWorld> CachedOwningWorld;
	TWeakObjectPtr<APlayerController> CachedOwningPC;
	TSoftClassPtr<UWidget_ActivatableBase> CachedSoftWidgetClass;
	FGameplayTag CachedWidgetStackTag;
	bool bCachedFocusOnNewlyPushedWidget = false;
};
