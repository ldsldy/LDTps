// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Types/LDTpsUIEnum.h"
#include "Widget_ConfirmScreen.generated.h"

class UCommonTextBlock;
class UDynamicEntryBox;

// 팝업 스크린에서 사용할 버튼 정보를 담는 구조체입니다.
USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unkown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonTextToDisplay;
};

// 팝업 스크린을 위한 정보들을 담는 객체입니다.
UCLASS()
class LDTPS_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:
	static UConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg);

	// 런타임에 정의되는 팝업 정보입니다.
	UPROPERTY(Transient)
	FText ScreenTitle;		// 팝업에 표시될 제목 텍스트

	UPROPERTY(Transient)
	FText ScreenMessage;	// 팝업에 표시될 메시지 텍스트

	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons; // 팝업에 표시될 버튼 정보 배열
};

/**
 *  유저의 선택 확인용 팝업 위젯입니다.
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class LDTPS_API UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_Message;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> DynamicEntryBox_Buttons; // 동적으로 버튼 삽입을 위한 컨테이너
};
