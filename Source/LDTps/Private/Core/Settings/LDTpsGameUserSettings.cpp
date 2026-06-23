// LDY of Project Settings.


#include "Core/Settings/LDTpsGameUserSettings.h"
#include "Common/Audio/LDTpsAudioDeveloperSettings.h"
#include "Kismet/GameplayStatics.h"

ULDTpsGameUserSettings::ULDTpsGameUserSettings()
	: OverallVolume(1.f) // 기본값을 1.0으로 설정
{

}

ULDTpsGameUserSettings* ULDTpsGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<ULDTpsGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}

void ULDTpsGameUserSettings::SetOverallVolume(float InNewVolume)
{
	UWorld* InAudioWorld = nullptr;
	const ULDTpsAudioDeveloperSettings* AudioDeveloperSettings = GetDefault<ULDTpsAudioDeveloperSettings>();

	if (GEngine)
	{
		InAudioWorld = GEngine->GetCurrentPlayWorld();
	}

	if(!InAudioWorld || !AudioDeveloperSettings)
	{
		return;
	}

	USoundClass* MasterSoundClass = nullptr;
	if(UObject* LoadedObject = AudioDeveloperSettings->MasterSoundClass.TryLoad())
	{
		MasterSoundClass = CastChecked<USoundClass>(LoadedObject);
	}

	USoundMix* DefaultSoundMix = nullptr;
	if(UObject* LoadedObject = AudioDeveloperSettings->DefaultSoundMix.TryLoad())
	{
		DefaultSoundMix = CastChecked<USoundMix>(LoadedObject);
	}

	OverallVolume = InNewVolume;

	UGameplayStatics::SetSoundMixClassOverride(
		InAudioWorld, DefaultSoundMix, MasterSoundClass, OverallVolume, 1.f, 0.2f);

	// 변경 사항을 적용하기 위해 SoundMixModifier를 푸시합니다.
	UGameplayStatics::PushSoundMixModifier(InAudioWorld, DefaultSoundMix);
}
