#pragma once
#include "Interface.h"
#include <d3d9.h>
#include "Global.h"

ImFont* fDefault;
ImFont* fskeet;
ImFont* fbadcache;
ImFont* guns;


void RenderDefault(IDirect3DDevice9* pDevice)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.f / 60.f;
	D3DDEVICE_CREATION_PARAMETERS d3dcp{ 0 };
	pDevice->GetCreationParameters(&d3dcp);

	auto& style = ImGui::GetStyle();

	fDefault = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16.0f);
	fskeet = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\skrrtmenufont.ttf", 55.0f);
	fbadcache = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\badcache.ttf", 55.0f);
	guns = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\astriumwep.ttf", 36.0f);


	static int hue = 140;

	ImVec4 col_text = ImColor::HSV(hue / 255.f, 20.f / 255.f, 235.f / 255.f);
	ImVec4 col_theme = ImColor(17, 17, 17);
	ImVec4 col_main = ImColor(9, 82, 128);
	ImVec4 col_back = ImColor(35, 35, 35);
	ImVec4 col_area = ImColor(4, 32, 41);

	style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.99f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.27f, 0.27f, .27f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.f); //testing
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.13, 0.13, 0.13, 1.f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.11, 0.11, 0.11, 1.f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.15, 0.15, 0.15, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.53f, 0.69f, 0.1f, 1.f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.53f, 0.69f, 0.1f, 1.f);
	style.Colors[ImGuiCol_Button] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.53f, 0.69f, 0.1f, 1.f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.53f, 0.69f, 0.1f, 1.f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(col_theme.x, col_theme.y, col_theme.z, .97f);
	style.Colors[ImGuiCol_Column] = ImVec4(col_text.x, col_text.y, col_text.z, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(col_text.x, col_text.y, col_text.z, 0.f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(col_text.x, col_text.y, col_text.z, 0);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.92f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

	//style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.5f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 2);
	style.FrameRounding = 0.0f;
	
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 0.1f;
	style.GrabRounding = 0.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;
}

