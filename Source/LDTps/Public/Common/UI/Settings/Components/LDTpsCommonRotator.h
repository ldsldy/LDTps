// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "LDTpsCommonRotator.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class LDTPS_API ULDTpsCommonRotator : public UCommonRotator
{
	GENERATED_BODY()

public:
	void SetSelectedOptionByText(const FText& InTextOption);
};
