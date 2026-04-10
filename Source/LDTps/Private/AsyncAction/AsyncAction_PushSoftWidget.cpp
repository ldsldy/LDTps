// LDY of Project Settings.


#include "AsyncAction/AsyncAction_PushSoftWidget.h"
#include "Subsystems/LDTpsUISubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, UPARAM(meta = (Categories = "UI.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"));
	
	if (UWorld * World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		//UAsyncAction_PushSoftWidget를 하나 생성한다. NewObject는 UObject 시스템에서 객체를 생성하는 함수입니다. 이 함수는 가비지 컬렉션과 같은 시스템과 통합되어 객체의 수명 관리를 돕습니다.
		UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
		Node->CachedOwningWorld = World;
		Node->CachedOwningPC = OwningPlayerController;
		Node->CachedSoftWidgetClass = InSoftWidgetClass;
		Node->CachedWidgetStackTag = InWidgetStackTag;
		Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

		// UAsyncAction_PushSoftWidget를 생성한 후, RegisterWithGameInstance 함수를 호출하여 게임 인스턴스에 등록합니다.
		// 생명주기관리 : 게임 인스턴스에 등록하면, 게임 인스턴스에 등록하여 비동기 작업이 진행되는 동안 안정적으로 생명주기를 보장받는다
		Node->RegisterWithGameInstance(World);

		return Node;
	}

	return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
	ULDTpsUISubsystem* UISubsystem = ULDTpsUISubsystem::Get(CachedOwningWorld.Get());

	UISubsystem->PushSoftWidgetToStackAynsc(CachedWidgetStackTag, CachedSoftWidgetClass,
		[this](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			switch (InPushState)
			{
				// 만약 위젯이 아직 스택에 푸시되기 전이라면 (즉, 위젯이 생성되었지만 아직 스택에 푸시되지 않은 상태라면), 
				// Widget에 OwningPlayer를 설정하고,
				// OnWidgetCreatedBeforePush 델리게이트를 브로드캐스트하여 위젯이 생성되었음을 알립니다.
			case EAsyncPushWidgetState::OnCreateBeforePush:
				PushedWidget->SetOwningPlayer(CachedOwningPC.Get());

				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);

				break;

				// 만약 위젯이 스택에 푸시된 후라면,
				// AfterPush 델리게이트를 브로드캐스트하여 위젯이 푸시되었음을 알립니다.
				// bCachedFocusOnNewlyPushedWidget가 true로 설정되어 있다면, 
				// 새로 푸시된 위젯의 원하는 포커스 대상이 있다면 해당 위젯에 포커스를 설정합니다.
			case EAsyncPushWidgetState::AfterPush:
				AfterPush.Broadcast(PushedWidget);

				if (bCachedFocusOnNewlyPushedWidget)
				{
					if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
					}
				}
				
				SetReadyToDestroy(); // 비동기 제거

				break;

			default:
				break;
			}
		}
	);
}
