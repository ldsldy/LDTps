// LDY of Project Settings.


#include "Widgets/Components/LDTpsCommonRotator.h"
#include "CommonTextBlock.h"

void ULDTpsCommonRotator::SetSelectedOptionByText(const FText& InTextOption)
{
	// TextLabels는 사용가능한 모든 텍스트 표시들
	// 그 안에 InTextOption과 일치하는 텍스트가 있는지 확인, 만약 있다면 그 인덱스 반환
	const int32 FoundIndex = TextLabels.IndexOfByPredicate(
		[InTextOption](const FText& TextItem)->bool
		{
			return TextItem.EqualTo(InTextOption);
		}
	);

	// 만약 찾은 TextLabel이 있다면, 그 인덱스를 SetSelectedItem에 전달해서 선택된 아이템을 변경합니다.
	if(FoundIndex != INDEX_NONE)
	{
		SetSelectedItem(FoundIndex);
	}
	else
	{
		MyText->SetText(InTextOption);
	}
}
