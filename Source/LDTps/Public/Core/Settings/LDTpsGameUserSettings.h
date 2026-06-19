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
	static ULDTpsGameUserSettings* Get();

	//***** Game Collection Tab *****//
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
	
	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InNewDifficulty) { CurrentGameDifficulty = InNewDifficulty; }
	//***** Game Collection Tab *****//

private:
	// Config는 이 값을 설정 파일에 저장할 수 있게 해준다.
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
};
