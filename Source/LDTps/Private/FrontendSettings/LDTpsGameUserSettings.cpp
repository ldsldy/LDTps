// LDY of Project Settings.


#include "FrontendSettings/LDTpsGameUserSettings.h"

ULDTpsGameUserSettings* ULDTpsGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<ULDTpsGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}