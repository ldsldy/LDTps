// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Options/DataObjects/ListDataObject_Base.h"
#include "ListDataObject_Collection.generated.h"

/**
 * 리스트의 소제목을 나타내는 데이터 객체 클래스입니다. 이 클래스는 UListDataObject_Base를 상속하며, 하위 탭에 있는 데이터들을 관리하는 기능을 제공합니다.
 */
UCLASS()
class LDTPS_API UListDataObject_Collection : public UListDataObject_Base
{
	GENERATED_BODY()
	
public:
	void AddChildListData(UListDataObject_Base* InChildListData);

	//~ Begin UListDataObject_Base Interface
	virtual TArray<UListDataObject_Base*> GetAllChildSettingData() const override;
	virtual bool HasAnyChildListData() const override;
	// ~ End UListDataObject_Base Interface

private:
	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ChildListDataArray;
};
