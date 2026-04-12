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

private:
	// **** 바인딩 위젯 **** //
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
