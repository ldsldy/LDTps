// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionsDataRegistry.generated.h"

class UListDataObject_Collection;
/**
 * 
 */
UCLASS()
class LDTPS_API UOptionsDataRegistry : public UObject
{
	GENERATED_BODY()
	
public:
	// 옵션 화면에서 UOptionsDataRegistry 유형의 객체가 생성된 직후에 호출됩니다.
	void InitOptionDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	const TArray<UListDataObject_Collection*>& GetRegisteredOptionsTabCollections() const { return RegisteredOptionsTabCollections; }
	
private:
	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();

private:
	UPROPERTY(Transient)
	TArray<UListDataObject_Collection*> RegisteredOptionsTabCollections;
};
