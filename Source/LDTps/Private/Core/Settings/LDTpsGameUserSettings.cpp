// LDY of Project Settings.


#include "Core/Settings/LDTpsGameUserSettings.h"

ULDTpsGameUserSettings* ULDTpsGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<ULDTpsGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}