// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LDTpsAudioDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "LDTps Audio Settings"))
class LDTPS_API ULDTpsAudioDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Audio", meta = (AllowedClasses = "/Script/Engine.SoundClass"))
	FSoftObjectPath MasterSoundClass;

	UPROPERTY(Config, EditAnywhere, Category = "Audio", meta = (AllowedClasses = "/Script/Engine.SoundClass"))
	FSoftObjectPath MusicSoundClass;

	UPROPERTY(Config, EditAnywhere, Category = "Audio", meta = (AllowedClasses = "/Script/Engine.SoundClass"))
	FSoftObjectPath SoundFXSoundClass;

	UPROPERTY(Config, EditAnywhere, Category = "Audio", meta = (AllowedClasses = "/Script/Engine.SoundMix"))
	FSoftObjectPath DefaultSoundMix;
};
