// LDY of Project Settings.


#include "UI/Widgets/Widget_ActivatableBase.h"
#include "GameFramework/PlayerController.h"

APlayerController* UWidget_ActivatableBase::GetOwningLDTpsPlayerController()
{
	if (!CachedOwningPlayerController.IsValid())
	{
		CachedOwningPlayerController = GetOwningPlayer();
	}

	return CachedOwningPlayerController.Get();
}
