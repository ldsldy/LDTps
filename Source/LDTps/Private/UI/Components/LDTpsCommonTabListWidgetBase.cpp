// LDY of Project Settings.


#include "UI/Components/LDTpsCommonTabListWidgetBase.h"
#include "UI/Components/LDTpsCommonButtonBase.h"
#include "Editor/WidgetCompilerLog.h"

void ULDTpsCommonTabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
	// 1. 탭 등록
	// 탭ID, 탭 버튼 관련 위젯 클래스, 고유한 콘텐츠 위젯 링크, 탭 인덱스)
	RegisterTab(InTabID, TabButtonEntryWidgetClass, nullptr);
	
	// 2. 탭 등록이 성공한 것을 확인한 경우 탭 버튼의 텍스트를 설정
	if (ULDTpsCommonButtonBase* FoundButton = Cast<ULDTpsCommonButtonBase>(GetTabButtonBaseByID(InTabID)))
	{
		FoundButton->SetButtonText(InTabDisplayName);
	}
}

#if WITH_EDITOR
void ULDTpsCommonTabListWidgetBase::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(FText::FromString(
			TEXT("The variable TabButtonEntryWidgetClass has no valid entry specified. ") +
			GetClass()->GetName() +
			TEXT(" needs a valid entry widget class to function properly")
		));
	}
}
#endif
