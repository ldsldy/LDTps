// LDY of Project Settings.


#include "Core/Settings/LDTpsGameUserSettings.h"
#include "Common/Audio/LDTpsAudioDeveloperSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

ULDTpsGameUserSettings::ULDTpsGameUserSettings()
	: OverallVolume(1.f) // 기본값을 1.0으로 설정
	, MusicVolume(1.f)
	, SoundFXVolume(1.f)
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

void ULDTpsGameUserSettings::SetMusicVolume(float InNewVolume)
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

	USoundClass* MusicSoundClass = nullptr;
	if(UObject* LoadedObject = AudioDeveloperSettings->MusicSoundClass.TryLoad())
	{
		MusicSoundClass = CastChecked<USoundClass>(LoadedObject);
	}

	USoundMix* DefaultSoundMix = nullptr;
	if (UObject* LoadedObject = AudioDeveloperSettings->DefaultSoundMix.TryLoad())
	{
		DefaultSoundMix = CastChecked<USoundMix>(LoadedObject);
	}

	MusicVolume = InNewVolume;

	UGameplayStatics::SetSoundMixClassOverride(
		InAudioWorld, DefaultSoundMix, MusicSoundClass, MusicVolume, 1.f, 0.2f);

	UGameplayStatics::PushSoundMixModifier(InAudioWorld, DefaultSoundMix);
}

void ULDTpsGameUserSettings::SetSoundFXVolume(float InNewVolume)
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

	USoundClass* SoundFXSoundClass = nullptr;
	if(UObject* LoadedObject = AudioDeveloperSettings->SoundFXSoundClass.TryLoad())
	{
		SoundFXSoundClass = CastChecked<USoundClass>(LoadedObject);
	}

	USoundMix* DefaultSoundMix = nullptr;
	if (UObject* LoadedObject = AudioDeveloperSettings->DefaultSoundMix.TryLoad())
	{
		DefaultSoundMix = CastChecked<USoundMix>(LoadedObject);
	}

	SoundFXVolume = InNewVolume;

	UGameplayStatics::SetSoundMixClassOverride(
		InAudioWorld, DefaultSoundMix, SoundFXSoundClass, SoundFXVolume, 1.f, 0.2f);
	UGameplayStatics::PushSoundMixModifier(InAudioWorld, DefaultSoundMix);
}
