// LDY of Project Settings.


#include "Core/GameplayTags/LDTpsGameplayTags.h"

namespace LDTpsGameplayTags
{
	// 실제로 게임 플레이 태그를 정의한다.
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_Modal,"UI.WidgetStack.Modal");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_GameMenu, "UI.WidgetStack.GameMenu");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_GameHUD, "UI.WidgetStack.GameHUD");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_Frontend, "UI.WidgetStack.Frontend");

	// UI Widgets 게임플레이 태그
	UE_DEFINE_GAMEPLAY_TAG(UI_Frontend_Widget_PressAnyKeyScreen, "UI.Frontend.Widget.PressAnyKeyScreen");
	UE_DEFINE_GAMEPLAY_TAG(UI_Frontend_Widget_MainMenuScreen, "UI.Frontend.Widget.MainMenuScreen");
	UE_DEFINE_GAMEPLAY_TAG(UI_Frontend_Widget_OptionsScreen, "UI.Frontend.Widget.OptionsScreen");

	UE_DEFINE_GAMEPLAY_TAG(UI_Frontend_Widget_ConfirmScreen, "UI.Frontend.Widget.ConfirmScreen");

	// UI Widget 이미지
	UE_DEFINE_GAMEPLAY_TAG(UI_Frontend_Image_TestImage, "UI.Frontend.Image.TestImage");
}		
