// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Types/LDTPSUIEnum.h"
#include "ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType, PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName;} \
	void Set##PropertyName(DataType In##PropertyName) {PropertyName = In##PropertyName;}

/**
 * 옵션 메뉴에서 리스트 항목의 데이터를 담는 객체의 베이스 클래스입니다.
 */
UCLASS(Abstract)
class LDTPS_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate, UListDataObject_Base*, EOptionsListDataModifyReason);
	FOnListDataModifiedDelegate OnListDataModified;

	LIST_DATA_ACCESSOR(FName, DataID)
	LIST_DATA_ACCESSOR(FText, DataDisplayName)
	LIST_DATA_ACCESSOR(FText, DescriptionRichText)
	LIST_DATA_ACCESSOR(FText, DisabledRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData)

	void InitDataObject();

	// 자식 클래스인 ListDataObject_Collection에서 이 함수를 오버라이드하여 하위 탭에 있는 데이터들을 반환하도록 구현할 예정입니다.
	virtual TArray<UListDataObject_Base*> GetAllChildSettingData() const { return TArray<UListDataObject_Base*>(); }
	virtual bool HasAnyChildListData() const { return false; }

	void SetShouldApplySettingsImmediately(bool bshouldApplyRightAway) { bShouldApplyChangeImmediatly = bshouldApplyRightAway; }

	// 자식 클래스는 이 함수들을 오버라이드하여 데이터를 초기화하는 기능을 제공해야 합니다.
	virtual bool HasDefaultValue() const { return false; }
	virtual bool CanResetBackToDefaultValue() const { return false; }
	virtual bool TryResetBackToDefaultValue() { return false; }

protected:
	// 베이스에서는 아무 기능이 없습니다. 자식 클래스는 이 함수를 오버라이드하여 초기화가 필요한 경우에 맞게 처리해야 합니다.
	virtual void OnDataObjectInitialized();

	virtual void NotifyListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified);

private:
	FName DataID;
	FText DataDisplayName;		// 옵션 메뉴에서 보여지는 이름입니다.
	FText DescriptionRichText;	// 옵션 메뉴에서 보여지는 설명입니다.
	FText DisabledRichText;		// 옵션이 비활성화 되었을 때 보여지는 설명입니다.
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	UListDataObject_Base* ParentData; // 하위 탭에 있는 데이터

	bool bShouldApplyChangeImmediatly = false;
};
