// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/UI/Options/DataObjects/ListDataObject_String.h"
#include "ListDataObject_StringResolution.generated.h"

/**
 * 
 */
UCLASS()
class LDTPS_API UListDataObject_StringResolution : public UListDataObject_String
{
	GENERATED_BODY()
	
public:
	void InitResolutionValues();

protected:
	// ~ Begin UListDataObject_String Interface
	virtual void OnDataObjectInitialized() override;
	// ~ End UListDataObject_String Interface

private:
	// FIntPoint 구조체를 문자열로 변환하는 헬퍼 함수입니다. 예: (X=1920,Y=1080) -> "1920x1080"
	FString ResToValueString(const FIntPoint& InResolution) const;

	// FIntPoint 구조체를 FText로 변환하는 헬퍼 함수입니다. 예: (X=1920,Y=1080) -> "1920 x 1080"
	FText ResToDisplayText(const FIntPoint& InResolution) const;

	// 사용자의 컴퓨터에서 지원되는 최대 해상도를 저장하는 멤버 변수입니다. 예: "3840x2160"
	FString MaximumAllowedResolution;
};
