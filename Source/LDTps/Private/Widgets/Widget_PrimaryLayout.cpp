// LDY of Project Settings.


#include "Widgets/Widget_PrimaryLayout.h"

#include "LDTpsDebugHelper.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InTag), TEXT("Can not find Widget Stack with tag %s"), *InTag.ToString());
	
	// FindRef() 함수는 TMap에서 키에 해당하는 값을 참조로 반환하는 함수입니다.
	return RegisteredWidgetStackMap.FindRef(InTag);
}

void UWidget_PrimaryLayout::RegisterWidgetStack(UPARAM(meta = (Categories = "Frontend_WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	// IsDesignTime() 함수는 위젯이 디자인 타임인지 런타임인지 확인하는 함수입니다. 
	// 디자인 타임에서는 위젯이 에디터에서 편집되고 있는 상태를 나타냅니다. 
	// 런타임에서는 게임이 실행 중인 상태를 나타냅니다.
	if (!IsDesignTime())
	{
		// 런타임 이라면 RegisteredWidgetStackMap에 InStackTag가 이미 존재하는지 확인합니다.
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			RegisteredWidgetStackMap.Add(InStackTag, InStack);
		}
	}
}
