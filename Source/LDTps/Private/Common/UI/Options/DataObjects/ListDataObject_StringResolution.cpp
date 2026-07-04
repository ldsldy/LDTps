// LDY of Project Settings.


#include "Common/UI/Options/DataObjects/ListDataObject_StringResolution.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Common/UI/Options/Data/OptionsDataInteractionHelper.h"
#include "Core/Settings/LDTpsGameUserSettings.h"

#include "Core/Debug/LDTpsDebugHelper.h"

void UListDataObject_StringResolution::InitResolutionValues()
{
	TArray<FIntPoint> AvailableResolutions; // FIntPoint는 2D 정수 좌표를 나타내는 구조체로 int32 X와 int32 Y를 멤버로 가진다.

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvailableResolutions);

	AvailableResolutions.Sort(
		[](const FIntPoint& A, const FIntPoint& B)->bool
		{
			return A.SizeSquared() < B.SizeSquared(); // SizeSquared() : return X * X + Y * Y;, 더 큰 해상도를 뒤로 보내기 위해 오름차순으로 정렬합니다.
		}
	);

	for (const FIntPoint& Resolution : AvailableResolutions)
	{
		// 지원하는 모든 해상도를 문자열과 FText로 변환하여 옵션으로 추가합니다.
		AddDynamicOption(ResToValueString(Resolution), ResToDisplayText(Resolution));
	}

	MaximumAllowedResolution = ResToValueString(AvailableResolutions.Last());

	SetDefaultValueFromString(MaximumAllowedResolution);
}

void UListDataObject_StringResolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		// 현재 해상도 값이 유효하지 않은 경우, 현재 게임 설정에서 해상도를 가져와서 표시 텍스트를 설정합니다.
		CurrentDisplayText = ResToDisplayText(ULDTpsGameUserSettings::Get()->GetScreenResolution());
	}
}

FString UListDataObject_StringResolution::ResToValueString(const FIntPoint& InResolution) const
{
	// Dynamic Getter로부터의 해상도 값 : (X = 1920,Y=1080)
	return FString::Printf(TEXT("(X=%i,Y=%i)"), InResolution.X, InResolution.Y);
}

FText UListDataObject_StringResolution::ResToDisplayText(const FIntPoint& InResolution) const
{
	const FString DisplayString = FString::Printf(TEXT("%i x %i"), InResolution.X, InResolution.Y);

	return FText::FromString(DisplayString);
}
