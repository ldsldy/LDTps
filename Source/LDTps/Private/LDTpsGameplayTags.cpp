// LDY of Project Settings.


#include "LDTpsGameplayTags.h"

namespace LDTpsGameplayTags
{
	// 실제로 게임 플레이 태그를 정의한다.
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_Modal_Frontend,"UI.WidgetStack.Modal.Frontend");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_GameMenu_Frontend, "UI.WidgetStack.GameMenu.Frontend");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_GameHUD_Frontend, "UI.WidgetStack.GameHUD.Frontend");
	UE_DEFINE_GAMEPLAY_TAG(UI_WidgetStack_Frontend_Frontend, "UI.WidgetStack.Frontend.Frontend");

	// UI Widgets 게임플레이 태그
	UE_DEFINE_GAMEPLAY_TAG(UI_Widget_Frontend_PressAnyKeyScreen,	"UI.Widget.Frontend.PressAnyKeyScreen");
	UE_DEFINE_GAMEPLAY_TAG(UI_Widget_Frontend_MainMenuScreen, "UI.Widget.Frontend.MainMenuScreen");
}