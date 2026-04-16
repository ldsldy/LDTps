// LDY of Project Settings.


#include "Widgets/Options/Widget_OptionScreen.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"

#include "LDTpsDebugHelper.h"

void UWidget_OptionScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		// "리셋" 액션을 등록합니다.
		// FBindUIActionArgs 구조체를 사용하여 액션 바인딩을 설정합니다.
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,    // 데이터 테이블 행 핸들
				true,           // 액션 바에 표시 여부
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered) // 액션이 트리거될 때 호출될 델리게이트
			)
		);
	}

	// "뒤로 가기" 액션을 등록합니다. 
	// ICommonInputModule에서 기본 뒤로 가기 액션을 가져와서 바인딩합니다.
	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)
		)
	);
}

void UWidget_OptionScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered!"));
}

void UWidget_OptionScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}
