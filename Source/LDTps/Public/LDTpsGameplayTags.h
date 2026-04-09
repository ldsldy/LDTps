// LDY of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace LDTpsGameplayTags
{
	// 다른 모듈에서 게임 플레이 태그를 참조할 수 있도록한다.
	// LDTPS_API

	// UI Widget Stack 게임플레이 태그
	LDTPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Modal);
	LDTPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameMenu);
	LDTPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameHUD);
	LDTPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Frontend);
}