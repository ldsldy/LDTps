// LDY of Project Settings.


#include "AsyncAction/AsyncAction_PushConfirmScreen.h"
#include "Subsystems/LDTpsUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushConfirmScreen* Node = NewObject<UAsyncAction_PushConfirmScreen>();
			Node->CachedOwningWorld = World;
			Node->CachedScreenType = ScreenType;
			Node->CachedScreenTitle = InScreenTitle;
			Node->CachedScreenMessage = InScreenMessage;

			Node->RegisterWithGameInstance(World);

			// 생성한 노드 반환
			return Node;
		}
	}
	return nullptr;
}

void UAsyncAction_PushConfirmScreen::Activate()
{
	ULDTpsUISubsystem::Get(CachedOwningWorld.Get())->PushConfirmScreenToModalStackAynsc(
		CachedScreenType,
		CachedScreenTitle,
		CachedScreenMessage,
		[this](EConfirmScreenButtonType ClickedButtonType) // 버튼 클릭 시 실행될 람다 함수
		{
			OnButtonClicked.Broadcast(ClickedButtonType);

			SetReadyToDestroy();
		}
	);
}
