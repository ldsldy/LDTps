// LDY of Project Settings.


#include "Widgets/Widget_ConfirmScreen.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "ICommonInputModule.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	// 스크린 정보 객체 생성 및 제목과 메시지 설정
    UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
    InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMsg;

	// OK 버튼 정보 설정
    FConfirmScreenButtonInfo OKButtonInfo;
    OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Ok"));

	// 버튼 정보를 팝업 정보 객체에 추가
	InfoObject->AvailableScreenButtons.Add(OKButtonInfo);

    return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	// 스크린 정보 객체 생성 및 제목과 메시지 설정
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMsg;

	// Yes 버튼 정보 설정
	FConfirmScreenButtonInfo YesButtonInfo;
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));
	
	// No 버튼 정보 설정
	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));

	// 버튼 정보를 팝업 정보 객체에 추가
	InfoObject->AvailableScreenButtons.Add(YesButtonInfo);
	InfoObject->AvailableScreenButtons.Add(NoButtonInfo);

	return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	// 스크린 정보 객체 생성 및 제목과 메시지 설정
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InScreenTitle;
	InfoObject->ScreenMessage = InScreenMsg;

	// Yes 버튼 정보 설정
	FConfirmScreenButtonInfo OkButtonInfo;
	OkButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confirmed;
	OkButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Ok"));

	// No 버튼 정보 설정
	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));

	// 버튼 정보를 팝업 정보 객체에 추가
	InfoObject->AvailableScreenButtons.Add(OkButtonInfo);
	InfoObject->AvailableScreenButtons.Add(CancelButtonInfo);

	return InfoObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);

	// 텍스트 블록에 팝업 정보 객체에서 전달된 제목과 메시지 설정
	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);

	// 활성화 가능 위젯이기 때문에 해당 기능을 사용할 때마다 이 스크린이 화면에 여러번 표시될 수 있기 때문에
	// 앞서 생성된 버튼들이 존재하는지 확인,
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		/*
		*	엔트리 박스에 기존 버튼이 존재하는 경우, 엔트리 박스에서 기존 버튼들을 제거합니다. 
		*	엔트리 박스의 위젯 유형은 자식 위젯 블루프린트에서 지정됩니다.
		*/
		DynamicEntryBox_Buttons->Reset<UFrontendCommonButtonBase>(
			[](UFrontendCommonButtonBase& ExistingButton) // 기존 버튼
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());

	// 팝업 정보 객체에서 전달된 버튼 정보 배열을 순회
	for (const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		FDataTableRowHandle InputActionRowHandle;

		switch (AvailableButtonInfo.ConfirmScreenButtonType)
		{
		case EConfirmScreenButtonType::Confirmed:
			// 확인 버튼의 경우 클릭 액션으로 설정된 입력 액션을 가져옵니다. 
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultClickAction(); // 에디터의 프로젝트 세팅에 설정된 기본 클릭 액션을 가온다
			break;

		case EConfirmScreenButtonType::Cancelled:
			// 취소 버튼의 경우 뒤로가기 액션으로 설정된 입력 액션을 가져옵니다.
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;

		case EConfirmScreenButtonType::Closed:
			// 닫기 버튼의 경우 뒤로가기 액션으로 설정된 입력 액션을 가져옵니다.
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;

		default:
			break;
		}

		UFrontendCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UFrontendCommonButtonBase>();
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeredInputAction(InputActionRowHandle); // 어떤 키를 사용하여 해당 버튼을 작동시킬지도 함께 설정 가능
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallback, AvailableButtonInfo, this]()
			{
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);

				// 작업이 끝난 후에는 팝업을 비활성화 해준다.
				DeactivateWidget();
			}
		);
	}

	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		/*
		* 마지막 버튼에 포커스를 설정합니다. 
		* 예를 들어, 버튼이 두 개 있고 하나는 예, 하나는 아니오인 경우, '아니오' 버튼에 포커스가 가게 됩니다.
		*/
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}
