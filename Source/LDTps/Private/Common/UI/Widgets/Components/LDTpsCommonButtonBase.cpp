// LDY of Project Settings.


#include "Common/UI/Widgets/Components/LDTpsCommonButtonBase.h"
#include "Common/UI/Subsystems/LDTpsUISubsystem.h"
#include "CommonTextBlock.h"

void ULDTpsCommonButtonBase::SetButtonText(FText InText)
{
	if (CommonTextBlock_ButtonText && !InText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? InText.ToUpper() : InText);
	}
}

FText ULDTpsCommonButtonBase::GetButtonDisplayText() const
{
	if (CommonTextBlock_ButtonText)
	{
		return CommonTextBlock_ButtonText->GetText();
	}

	return FText();
}

void ULDTpsCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void ULDTpsCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void ULDTpsCommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();
	
	if (!ButtonDescriptionText.IsEmpty())
	{
		ULDTpsUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
	}
}

void ULDTpsCommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	ULDTpsUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, FText::GetEmpty());

}
