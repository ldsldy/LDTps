// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "LDTpsGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class LDTPS_API ULDTpsGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	ULDTpsGameUserSettings();

	static ULDTpsGameUserSettings* Get();

	//***** 게임 플레이 탭 *****//
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
	
	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InNewDifficulty) { CurrentGameDifficulty = InNewDifficulty; }
	//***** 게임 플레이 탭 *****//

	//***** 오디오 탭 *****//
	UFUNCTION()
	float GetOverallVolume() const { return OverallVolume; }

	UFUNCTION()
	void SetOverallVolume(float InNewVolume);

	UFUNCTION()
	float GetMusicVolume() const { return MusicVolume; }

	UFUNCTION()
	void SetMusicVolume(float InNewVolume);

	UFUNCTION()
	float GetSoundFXVolume() const { return SoundFXVolume; }

	UFUNCTION()
	void SetSoundFXVolume(float InNewVolume);
	//***** 오디오 탭 *****//

private:
	// Config는 이 값을 설정 파일에 저장할 수 있게 해준다.

	//***** 게임 플레이 탭 *****//
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
	//***** 게임 플레이 탭 *****//

	//***** 오디오 탭 *****//
	UPROPERTY(Config)
	float OverallVolume;

	UPROPERTY(Config)
	float MusicVolume;

	UPROPERTY(Config)
	float SoundFXVolume;
	//***** 오디오 탭 *****//

};
