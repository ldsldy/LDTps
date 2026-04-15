// LDY of Project Settings.


#include "Subsystems/LDTpsUISubsystem.h"
#include "Engine/AssetManager.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widgets/Widget_ConfirmScreen.h"
#include "UIFunctionLibrary.h"
#include "LDTpsGameplayTags.h"

#include "LDTpsDebugHelper.h"

ULDTpsUISubsystem* ULDTpsUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		// 월드 컨텍스트 객체에서 UWorld를 가져오기를 시도하고 실패하면 어설트 모드로 처리합니다.
		// 우아한 종료는 하고 있던 작업을 적절히 정리하고 종료하는 것입니다. 반대로 어설트는 즉시 종료하는 것입니다.
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	
		// 월드가 유효하다면, 게임 인스턴스에서 ULDTpsUISubsystem을 가져옵니다.
		return UGameInstance::GetSubsystem<ULDTpsUISubsystem>(World->GetGameInstance());
	}

	return nullptr;
}


// true를 반환하면 서브시스템이 생성되고 false를 반환하면 서브시스템이 생성되지 않습니다.
bool ULDTpsUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// Outer는 서브시스템이 생성될 때의 외부 객체입니다. 일반적으로 게임 인스턴스가 됩니다.
	// Dedicated Server가 아닌 경우에만 서브시스템을 생성하도록 합니다. 이렇게 하면 클라이언트에서만 UI 관련 서브시스템이 생성됩니다. 
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		// 자식 클래스가 있다면 서브시스템을 생성하지 않습니다.
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}
	
	return false;
}

void ULDTpsUISubsystem::RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);

	CreatedPrimaryLayout = InCreatedWidget;

	Debug::Print(TEXT("Primary Layout Widget Stored"));
}

void ULDTpsUISubsystem::PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableBase*)> AsyncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass, this, InWidgetStackTag, AsyncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				check(CreatedPrimaryLayout && LoadedWidgetClass);

				UCommonActivatableWidgetContainerBase* FoundWIdgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
				
				UWidget_ActivatableBase* CreatedWidget = FoundWIdgetStack->AddWidget<UWidget_ActivatableBase>(
					LoadedWidgetClass,
					[AsyncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance) // 초기화 람다, 인스턴스가 생성된 후에 호출됩니다. 여기서 위젯 활성화 전에 위젯 인스턴스를 초기화할 수 있습니다.
					{
						// 콜백 호출, 열거형 값을 채워서 호출자에게 현재 상태를 알림.
						AsyncPushStateCallback(EAsyncPushWidgetState::OnCreateBeforePush, &CreatedWidgetInstance);
					}
				);

				// 위젯이 스택에 추가된 후에 호출되는 람다입니다. 여기서 위젯이 스택에 추가된 후의 상태를 알릴 수 있습니다.
				AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
			}
		)
	);
}

void ULDTpsUISubsystem::PushConfirmScreenToModalStackAynsc(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreatedInfoObject = nullptr;

	switch (InScreenType)
	{
	case EConfirmScreenType::Ok:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::YesNo:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::OKCancel:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::Unkown:
		break;

	default:
		break;
	}

	check(CreatedInfoObject);

	PushSoftWidgetToStackAynsc(
		LDTpsGameplayTags::UI_WidgetStack_Modal,
		UUIFunctionLibrary::GetSoftWidgetClassByTag(LDTpsGameplayTags::UI_Widget_Frontend_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			// 소프트 클래스 위젯의 푸시 상태에 따른 처리
			if (InPushState == EAsyncPushWidgetState::OnCreateBeforePush)
			{
				UWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		}
	);
}
