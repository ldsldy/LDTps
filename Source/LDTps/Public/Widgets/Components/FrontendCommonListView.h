// LDY of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "FrontendCommonListView.generated.h"

class UDataAsset_DataListEntryMapping;

/**
 * 
 */
UCLASS()
class LDTPS_API UFrontendCommonListView : public UCommonListView
{
	GENERATED_BODY()
	
protected:
	/// ~Begin UCommonListView Interface
	// OnGenerateEntryWidgetInternal은 ListView가 각 아이템에 대한 엔트리 위젯을 생성할 때 호출됩니다
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	// ~End UCommonListView Interface
private:
	// ~Begin UWidget Interface
#if WITH_EDITOR
	// 컴파일 타임에 DataListEntryMapping이 유효한지 검증합니다.
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif
	// ~End UWidget Interface

	UPROPERTY(EditAnywhere, Category = "Frontend List View Settings")
	UDataAsset_DataListEntryMapping* DataListEntryMapping;
};
