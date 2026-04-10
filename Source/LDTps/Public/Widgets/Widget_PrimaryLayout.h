// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Widget_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;

/**
 * 
 */
// Abstract (추상) 지정자는 클래스를 "추상 베이스 클래스" 로 선언하여, 
// 사용자가 이 클래스 액터를 월드에 추가하지 못하도록 합니다. 
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick)) 
class LDTPS_API UWidget_PrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InTag) const;

protected:
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(UPARAM(meta = (Categories = "UI.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack);

private:
	//Transient 키워드는 UPROPERTY로 속성을 지정했지만, 디스크로부터 데이터를 로딩하는 것을 방지할 때 사용합니다.
	//Transient 키워드를 붙이면 디스크 저장에서 제외되 불필요한 데이터 공간 낭비를 줄일 수 있습니다.
	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
