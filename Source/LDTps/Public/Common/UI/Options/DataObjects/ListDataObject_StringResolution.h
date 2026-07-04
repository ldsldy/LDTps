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
};
