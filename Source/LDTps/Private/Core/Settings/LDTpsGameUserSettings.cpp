// LDY of Project Settings.


#include "Core/Settings/LDTpsGameUserSettings.h"

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
	OverallVolume = InNewVolume;

	// 여기서 실제 오디오 시스템에 볼륨을 적용하는 코드를 추가할 수 있습니다.
}
