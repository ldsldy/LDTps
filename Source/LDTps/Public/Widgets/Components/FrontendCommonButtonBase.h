// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "FrontendCommonButtonBase.generated.h"

class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class LDTPS_API UFrontendCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

private:
	// UWidget interface
	virtual void NativePreConstruct() override;
	// End of UWidget interface

	// ~ Begin UCommonButtonBase interface
	virtual void NativeOnCurrentTextStyleChanged() override;
	// ~ End of UCommonButtonBase interface

private:
	// **** 바인딩 위젯 **** //
	// meta = (BindWidgetOptional)로 설정하여, 위젯 트리에 해당 이름의 위젯이 존재할 경우 자동으로 바인딩되도록 함. 
	// 존재하지 않을 경우에도 에러가 발생하지 않음.
	UPROPERTY(meta = (BindWidgetOptional)) 
	UCommonTextBlock* CommonTextBlock_ButtonText;
	// **** 바인딩 위젯 **** //

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta= (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	bool bUseUpperCaseForButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;
};
