// LDY of Project Settings.


#include "Common/UI/Options/Data/OptionsDataRegistry.h"
#include "Common/UI/Options/DataObjects/ListDataObject_Collection.h"
#include "Common/UI/Options/DataObjects/ListDataObject_String.h"
#include "Common/UI/Options/DataObjects/ListDataObject_Scalar.h"
#include "Common/UI/Options/Data/OptionsDataInteractionHelper.h"
#include "Core/Settings/LDTpsGameUserSettings.h"
#include "Common/UI/Libraries/UIFunctionLibrary.h"
#include "Core/GameplayTags/LDTpsGameplayTags.h"

//FOptionsDataInteractionHelper 객체를 생성하는 매크로
#define MAKE_OPTION_DATA_CONTROL(SetterOrGetterFuncName) \
     MakeShared<FOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(ULDTpsGameUserSettings, SetterOrGetterFuncName))

void UOptionsDataRegistry::InitOptionDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
}

TArray<UListDataObject_Base*> UOptionsDataRegistry::GetListSourceItemsBySelectedTabID(const FName& InSelectedTabID) const
{
	// 선택된 탭 ID에 해당하는 탭 컬렉션을 RegisteredOptionsTabCollections에서 찾습니다.
	UListDataObject_Collection* const* FoundTabCollectionPtr = RegisteredOptionsTabCollections.FindByPredicate(
		[InSelectedTabID](UListDataObject_Collection* AvailableTabCollection)->bool
		{
			return AvailableTabCollection->GetDataID() == InSelectedTabID;
		}
	);

	checkf(FoundTabCollectionPtr, TEXT("No valid tab found under the ID %s"), *InSelectedTabID.ToString());

	UListDataObject_Collection* FoundTabCollection = *FoundTabCollectionPtr;

	TArray<UListDataObject_Base*> AllChildListItems;

	for (UListDataObject_Base* ChildListData : FoundTabCollection->GetAllChildSettingData())
	{
		if (!ChildListData)
		{
			continue;
		}

		AllChildListItems.Add(ChildListData);

		if (ChildListData->HasAnyChildListData())
		{
			FindChildListDataRecursively(ChildListData, AllChildListItems);
		}
	}

	return AllChildListItems;
}

void UOptionsDataRegistry::FindChildListDataRecursively(UListDataObject_Base* InParentData, TArray<UListDataObject_Base*>& OutFoundChildListData) const
{
	if (!InParentData || InParentData->HasAnyChildListData())
	{
		return;
	}

	for (UListDataObject_Base* SubChildListData : InParentData->GetAllChildSettingData())
	{
		if(!SubChildListData)
		{
			continue;
		}

		OutFoundChildListData.Add(SubChildListData);

		if (SubChildListData->HasAnyChildListData())
		{
			FindChildListDataRecursively(SubChildListData, OutFoundChildListData);
		}
	}
}

void UOptionsDataRegistry::InitGameplayCollectionTab()
{
	UListDataObject_Collection* GameplayTabCollection = NewObject<UListDataObject_Collection>();
	GameplayTabCollection->SetDataID(FName("GameplayTabCollection"));
	GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("게임 플레이")));

	// 이 코드는 FOptionsDataInteractionHelper 객체를 생성하는 전체 코드입니다.
	/*TSharedPtr<FOptionsDataInteractionHelper> ConstructedHelper =
		MakeShared<FOptionsDataInteractionHelper>(
			GET_FUNCTION_NAME_STRING_CHECKED(ULDTpsGameUserSettings, GetCurrentGameDifficulty)
		);*/

	//난이도 카테고리
	{
		UListDataObject_String* GameDifficulty = NewObject<UListDataObject_String>();
		GameDifficulty->SetDataID(FName("GameDifficulty"));
		GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("난이도")));
		GameDifficulty->SetDescriptionRichText(FText::FromString(TEXT("게임 경험의 난이도를 조절합니다.\n\n<Bold>쉬움:</> 스토리 경험에 중점을 둡니다. 가장 편안한 전투를 제공합니다.\n\n<Bold>보통:</> 약간 더 어려운 전투 경험을 제공합니다.\n\n<Bold>어려움:</> 숙련된 플레이어를 위한 도전적인 경험을 제공합니다.\n\n<Bold>매우 어려움:</> 가장 도전적인 전투 경험을 제공합니다. 첫 플레이에는 권장되지 않습니다.")));
		GameDifficulty->AddDynamicOption(TEXT("Easy"), FText::FromString(TEXT("쉬움")));
		GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("보통")));
		GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("어려움")));
		GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("매우 어려움")));
		GameDifficulty->SetDefaultValueFromString(TEXT("Normal")); // 기본값을 "Normal"로 설정합니다.
		GameDifficulty->SetDataDynamicGetter(MAKE_OPTION_DATA_CONTROL(GetCurrentGameDifficulty));
		GameDifficulty->SetDataDynamicSetter(MAKE_OPTION_DATA_CONTROL(SetCurrentGameDifficulty));
		GameDifficulty->SetShouldApplySettingsImmediately(true);

		GameplayTabCollection->AddChildListData(GameDifficulty);
	}

	//Test Item
	{
		UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
		TestItem->SetDataID(FName("TestItem"));
		TestItem->SetDataDisplayName(FText::FromString(TEXT("테스트 이미지")));
		TestItem->SetSoftDescriptionImage(UUIFunctionLibrary::GetSoftImageByTag(LDTpsGameplayTags::UI_Frontend_Image_TestImage));
		TestItem->SetDescriptionRichText(FText::FromString(TEXT("표시할 이미지는 프로젝트 설정에서 지정할 수 있습니다.")));

		GameplayTabCollection->AddChildListData(TestItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionsDataRegistry::InitAudioCollectionTab()
{
	UListDataObject_Collection* AudioTabCollection = NewObject<UListDataObject_Collection>();
	AudioTabCollection->SetDataID(FName("AudioTabCollection"));
	AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("오디오")));

	//볼륨 카테고리
	{
		UListDataObject_Collection* VolumeCategoryCollection = NewObject<UListDataObject_Collection>();
		VolumeCategoryCollection->SetDataID(FName("VolumeCategoryCollection"));
		VolumeCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("볼륨")));

		AudioTabCollection->AddChildListData(VolumeCategoryCollection);

		// 전체 볼륨
		{
			UListDataObject_Scalar* OverallVolume = NewObject<UListDataObject_Scalar>();
			OverallVolume->SetDataID(FName("OverallVolume"));
			OverallVolume->SetDataDisplayName(FText::FromString(TEXT("전체 볼륨")));
			OverallVolume->SetDescriptionRichText(FText::FromString(TEXT("게임 내 모든 오디오의 볼륨을 조절합니다.")));
			OverallVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			OverallVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			OverallVolume->SetSliderStepSize(0.01f);
			OverallVolume->SetDefaultValueFromString(LexToString(1.f));
			OverallVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			OverallVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());  //No Decimal: 50%  //One Decimal: 50.5%
			OverallVolume->SetDataDynamicGetter(MAKE_OPTION_DATA_CONTROL(GetOverallVolume));
			OverallVolume->SetDataDynamicSetter(MAKE_OPTION_DATA_CONTROL(SetOverallVolume));
			OverallVolume->SetShouldApplySettingsImmediately(true);

			AudioTabCollection->AddChildListData(OverallVolume);
		}

		// 배경음악 볼륨
		{
			UListDataObject_Scalar* MusicVolume = NewObject<UListDataObject_Scalar>();
			MusicVolume->SetDataID(FName("MusicVolume"));
			MusicVolume->SetDataDisplayName(FText::FromString(TEXT("배경음악 볼륨")));
			MusicVolume->SetDescriptionRichText(FText::FromString(TEXT("게임 내 배경음악의 볼륨을 조절합니다.")));
			MusicVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			MusicVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			MusicVolume->SetSliderStepSize(0.01f);
			MusicVolume->SetDefaultValueFromString(LexToString(1.f));
			MusicVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			MusicVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());  //No Decimal: 50%  //One Decimal: 50.5%
			MusicVolume->SetDataDynamicGetter(MAKE_OPTION_DATA_CONTROL(GetMusicVolume));
			MusicVolume->SetDataDynamicSetter(MAKE_OPTION_DATA_CONTROL(SetMusicVolume));
			MusicVolume->SetShouldApplySettingsImmediately(true);

			AudioTabCollection->AddChildListData(MusicVolume);
		}

		// FX 볼륨
		{
			UListDataObject_Scalar* SoundFXVolume = NewObject<UListDataObject_Scalar>();
			SoundFXVolume->SetDataID(FName("SoundFXVolume"));
			SoundFXVolume->SetDataDisplayName(FText::FromString(TEXT("효과음 볼륨")));
			SoundFXVolume->SetDescriptionRichText(FText::FromString(TEXT("게임 내 효과음의 볼륨을 조절합니다.")));
			SoundFXVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			SoundFXVolume->SetOutputValueRange(TRange<float>(0.f, 2.f));
			SoundFXVolume->SetSliderStepSize(0.01f);
			SoundFXVolume->SetDefaultValueFromString(LexToString(1.f));
			SoundFXVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			SoundFXVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());  //No Decimal: 50%  //One Decimal: 50.5%
			SoundFXVolume->SetDataDynamicGetter(MAKE_OPTION_DATA_CONTROL(GetSoundFXVolume));
			SoundFXVolume->SetDataDynamicSetter(MAKE_OPTION_DATA_CONTROL(SetSoundFXVolume));
			SoundFXVolume->SetShouldApplySettingsImmediately(true);

			AudioTabCollection->AddChildListData(SoundFXVolume);
		}
	}

	// 사운드 카테고리
	{
		UListDataObject_Collection* SoundCategoryCollection = NewObject<UListDataObject_Collection>();
		SoundCategoryCollection->SetDataID(FName("SoundCategoryCollection"));
		SoundCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("사운드")));

		AudioTabCollection->AddChildListData(SoundCategoryCollection);

		// 백그라운드 사운드 옵션
		{
			UListDataObject_StringBool* AllowBackgroundAudio = NewObject<UListDataObject_StringBool>();
			AllowBackgroundAudio->SetDataID(FName("AllowBackgroundAudio"));
			AllowBackgroundAudio->SetDataDisplayName(FText::FromString(TEXT("백그라운드 사운드 허용")));
			AllowBackgroundAudio->OverrideTrueDisplayText(FText::FromString(TEXT("허용")));
			AllowBackgroundAudio->OverrideFalseDisplayText(FText::FromString(TEXT("허용 안함")));
			AllowBackgroundAudio->SetFalseAsDefaultValue(); // 기본값을 False로 설정합니다.
			AllowBackgroundAudio->SetDataDynamicGetter(MAKE_OPTION_DATA_CONTROL(GetAllowBackgroundAudio));
			AllowBackgroundAudio->SetDataDynamicSetter(MAKE_OPTION_DATA_CONTROL(SetAllowBackgroundAudio));
			AllowBackgroundAudio->SetShouldApplySettingsImmediately(true);

			AudioTabCollection->AddChildListData(AllowBackgroundAudio);
		}

		// HDR Audio 옵션
		{
			UListDataObject_StringBool* UseHDRAudioMode = NewObject<UListDataObject_StringBool>();
			UseHDRAudioMode->SetDataID(FName("UseHDRAudioMode"));
			UseHDRAudioMode->SetDataDisplayName(FText::FromString(TEXT("HDR 오디오 활성화")));
			UseHDRAudioMode->OverrideTrueDisplayText(FText::FromString(TEXT("허용")));
			UseHDRAudioMode->OverrideFalseDisplayText(FText::FromString(TEXT("허용 안함")));
			UseHDRAudioMode->SetFalseAsDefaultValue(); // 기본값을 False로 설정합니다.
			UseHDRAudioMode->SetDataDynamicGetter(MAKE_OPTION_DATA_CONTROL(GetUseHDRAudioMode));
			UseHDRAudioMode->SetDataDynamicSetter(MAKE_OPTION_DATA_CONTROL(SetUseHDRAudioMode));
			UseHDRAudioMode->SetShouldApplySettingsImmediately(true);

			AudioTabCollection->AddChildListData(UseHDRAudioMode);
		}
	}

	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionsDataRegistry::InitVideoCollectionTab()
{
	UListDataObject_Collection* VideoTabCollection = NewObject<UListDataObject_Collection>();
	VideoTabCollection->SetDataID(FName("VideoTabCollection"));
	VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("그래픽")));

	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UOptionsDataRegistry::InitControlCollectionTab()
{
	UListDataObject_Collection* ControlTabCollection = NewObject<UListDataObject_Collection>();
	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("컨트롤")));

	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}
