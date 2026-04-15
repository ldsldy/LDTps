// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Types/LDTpsUIEnum.h"
#include "LDTpsUISubsystem.generated.h"

class UWidget_PrimaryLayout;
class UWidget_ActivatableBase;
class UFrontendCommonButtonBase;
struct FGameplayTag;

enum class EAsyncPushWidgetState : uint8
{
	OnCreateBeforePush,
	AfterPush,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, UFrontendCommonButtonBase*, BroadcastingButton, FText, DescriptionText);
/**
 * 
 */
UCLASS()
class LDTPS_API ULDTpsUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	static ULDTpsUISubsystem* Get(const UObject* WorldContextObject);

	// ~ Begin USubsystem 인터페이스
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// ~ End USubsystem 인터페이스

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);
 
	// TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback는 
	// SoftWidget을 로드하여 생성하고 스택에 푸시하는 비동기 작업의 상태를 알리기 위한 함수
	void PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback);

	void PushConfirmScreenToModalStackAynsc(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback);

	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

private:
	// 항상 런타임에 채워지기 때문에 Transient로 지정하여 디스크 저장에서 제외합니다.
	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;
};
