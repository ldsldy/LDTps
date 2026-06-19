// LDY of Project Settings.


#include "Common/UI/Settings/Widgets/Widget_OptionsDetailsView.h"
#include "CommonTextBlock.h"
#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "Common/UI/Settings/DataObjects/ListDataObject_Base.h"

void UWidget_OptionsDetailsView::UpdateDetailsViewInfo(UListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName)
{
	if (!InDataObject)
	{
		return;
	}

	CommonTextBlock_Title->SetText(InDataObject->GetDataDisplayName());
	
	// 설명 아이콘이 존재하는 경우에만 설정하고, 그렇지 않으면 아이콘을 숨깁니다.
	if (!InDataObject->GetSoftDescriptionImage().IsNull())
	{
		CommonLazyImage_DescriptionIcon->SetBrushFromLazyTexture(InDataObject->GetSoftDescriptionImage());
		CommonLazyImage_DescriptionIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		CommonLazyImage_DescriptionIcon->SetVisibility(ESlateVisibility::Collapsed);
	}

	CommonRichText_Description->SetText(InDataObject->GetDescriptionRichText());

	const FString DynamicDetails = FString::Printf(
		TEXT("Data Object Class : <Bold>%s</>\n\nEntry Widget Class:<Bold>%s</>"),
		*InDataObject->GetClass()->GetName(),
		*InEntryWidgetClassName
	);

	CommonRichText_DynamicDetails->SetText(FText::FromString(DynamicDetails));

	CommonRichText_DisabledReason->SetText(InDataObject->GetDisabledRichText());
}

void UWidget_OptionsDetailsView::ClearDetailsViewInfo()
{
	CommonTextBlock_Title->SetText(FText::GetEmpty());
	CommonLazyImage_DescriptionIcon->SetVisibility(ESlateVisibility::Collapsed);
	CommonRichText_Description->SetText(FText::GetEmpty());
	CommonRichText_DynamicDetails->SetText(FText::GetEmpty());
	CommonRichText_DisabledReason->SetText(FText::GetEmpty());
}

void UWidget_OptionsDetailsView::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClearDetailsViewInfo();
}
