// LDY of Project Settings.


#include "LDTpsGameplayTags.h"

namespace LDTpsGameplayTags
{
	// 실제로 게임 플레이 태그를 정의한다.
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_Modal,"UI.WidgetStack.Modal");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_GameMenu, "UI.WidgetStack.GameMenu");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_GameHUD, "UI.WidgetStack.GameHUD");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_Frontend, "UI.WidgetStack.Frontend");

	// UI Widgets 게임플레이 태그
	UE_DEFINE_GAMEPLAY_TAG(UI_Widget_Frontend_PressAnyKeyScreen,	"UI.Widget.Frontend.PressAnyKeyScreen");
	UE_DEFINE_GAMEPLAY_TAG(UI_Widget_Frontend_MainMenuScreen, "UI.Widget.Frontend.MainMenuScreen");
	UE_DEFINE_GAMEPLAY_TAG(UI_Widget_Frontend_ConfirmScreen, "UI.Widget.Frontend.ConfirmScreen");
}