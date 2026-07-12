// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionsDataRegistry.generated.h"

class UListDataObject_Collection;
class UListDataObject_Base;

/**
 * 옵션의 상위 탭들을 관리하는 레지스트리.
 */
UCLASS()
class LDTPS_API UOptionsDataRegistry : public UObject
{
	GENERATED_BODY()
	
public:
	// 옵션 화면에서 UOptionsDataRegistry 유형의 객체가 생성된 직후에 호출됩니다.
	void InitOptionDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	const TArray<UListDataObject_Collection*>& GetRegisteredOptionsTabCollections() const { return RegisteredOptionsTabCollections; }
	
	// 선택된 탭 ID에 해당하는 탭 컬렉션에서 하위 탭에 있는 데이터들을 모두 반환합니다.
	TArray<UListDataObject_Base*> GetListSourceItemsBySelectedTabID(const FName& InSelectedTabID) const;

private:
	// InParentData부터 시작하여 모든 자식 리스트 데이터를 재귀적으로 찾아서 OutFoundChildListData에 추가합니다.
	void FindChildListDataRecursively(UListDataObject_Base* InParentData, TArray<UListDataObject_Base*>& OutFoundChildListData) const;
		
	// 게임 플레이 탭의 리스트 데이터를 초기화합니다.
	void InitGameplayCollectionTab();
	// 오디오 탭의 리스트 데이터를 초기화합니다.
	void InitAudioCollectionTab();
	// 비디오 탭의 리스트 데이터를 초기화합니다.
	void InitVideoCollectionTab();
	// 컨트롤 탭의 리스트 데이터를 초기화합니다.
	void InitControlCollectionTab();

private:
	UPROPERTY(Transient)
	TArray<UListDataObject_Collection*> RegisteredOptionsTabCollections;
};
