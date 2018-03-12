// dear imgui, v1.51 WIP
// (main code and documentation)

// See ImGui::ShowTestWindow() in imgui_demo.cpp for demo code.
// Newcomers, read 'Programmer guide' below for notes on how to setup ImGui in your codebase.
// Get latest version at https://github.com/ocornut/imgui
// Releases change-log at https://github.com/ocornut/imgui/releases
// Gallery (please post your screenshots/video there!): https://github.com/ocornut/imgui/issues/772
// Developed by Omar Cornut and every direct or indirect contributors to the GitHub.
// This library is free but I need your support to sustain development and maintenance.
// If you work for a company, please consider financial support, e.g: https://www.patreon.com/imgui

/*

Index
- MISSION STATEMENT
- END-USER GUIDE
- PROGRAMMER GUIDE (read me!)
- API BREAKING CHANGES (read me when you update!)
- FREQUENTLY ASKED QUESTIONS (FAQ), TIPS
- How can I help?
- How do I update to a newer version of ImGui?
- What is ImTextureID and how do I display an image?
- I integrated ImGui in my engine and the text or lines are blurry..
- I integrated ImGui in my engine and some elements are clipping or disappearing when I move windows around..
- How can I have multiple widgets with the same label? Can I have widget without a label? (Yes). A primer on the purpose of labels/IDs.
- How can I tell when ImGui wants my mouse/keyboard inputs and when I can pass them to my application?
- How can I load a different font than the default?
- How can I easily use icons in my application?
- How can I load multiple fonts?
- How can I display and input non-latin characters such as Chinese, Japanese, Korean, Cyrillic?
- How can I use the drawing facilities without an ImGui window? (using ImDrawList API)
- ISSUES & TODO-LIST
- CODE


MISSION STATEMENT
=================

- easy to use to create code-driven and data-driven tools
- easy to use to create ad hoc short-lived tools and long-lived, more elaborate tools
- easy to hack and improve
- minimize screen real-estate usage
- minimize setup and maintenance
- minimize state storage on user side
- portable, minimize dependencies, run on target (consoles, phones, etc.)
- efficient runtime (NB- we do allocate when "growing" content - creating a window / opening a tree node for the first time, etc. - but a typical frame won't allocate anything)
- read about immediate-mode gui principles @ http://mollyrocket.com/861, http://mollyrocket.com/forums/index.html

Designed for developers and content-creators, not the typical end-user! Some of the weaknesses includes:
- doesn't look fancy, doesn't animate
- limited layout features, intricate layouts are typically crafted in code
- occasionally uses statically sized buffers for string manipulations - won't crash, but some very long pieces of text may be clipped. functions like ImGui::TextUnformatted() don't have such restriction.


END-USER GUIDE
==============

- double-click title bar to collapse window
- click upper right corner to close a window, available when 'bool* p_open' is passed to ImGui::Begin()
- click and drag on lower right corner to resize window
- click and drag on any empty space to move window
- double-click/double-tap on lower right corner grip to auto-fit to content
- TAB/SHIFT+TAB to cycle through keyboard editable fields
- use mouse wheel to scroll
- use CTRL+mouse wheel to zoom window contents (if IO.FontAllowScaling is true)
- CTRL+Click on a slider or drag box to input value as text
- text editor:
- Hold SHIFT or use mouse to select text.
- CTRL+Left/Right to word jump
- CTRL+Shift+Left/Right to select words
- CTRL+A our Double-Click to select all
- CTRL+X,CTRL+C,CTRL+V to use OS clipboard
- CTRL+Z,CTRL+Y to undo/redo
- ESCAPE to revert text to its original value
- You can apply arithmetic operators +,*,/ on numerical values. Use +- to subtract (because - would set a negative value!)


PROGRAMMER GUIDE
================

- read the FAQ below this section!
- your code creates the UI, if your code doesn't run the UI is gone! == very dynamic UI, no construction/destructions steps, less data retention on your side, no state duplication, less sync, less bugs.
- call and read ImGui::ShowTestWindow() for demo code demonstrating most features.
- see examples/ folder for standalone sample applications. Prefer reading examples/opengl2_example/ first as it is the simplest.
you may be able to grab and copy a ready made imgui_impl_*** file from the examples/.
- customization: PushStyleColor()/PushStyleVar() or the style editor to tweak the look of the interface (e.g. if you want a more compact UI or a different color scheme).

- getting started:
- init: call ImGui::GetIO() to retrieve the ImGuiIO structure and fill the fields marked 'Settings'.
- init: call io.Fonts->GetTexDataAsRGBA32(...) and load the font texture pixels into graphics memory.
- every frame:
1/ in your mainloop or right after you got your keyboard/mouse info, call ImGui::GetIO() and fill the fields marked 'Input'
2/ call ImGui::NewFrame() as early as you can!
3/ use any ImGui function you want between NewFrame() and Render()
4/ call ImGui::Render() as late as you can to end the frame and finalize render data. it will call your RenderDrawListFn handler that you set in the IO structure.
(if you don't need to render, you still need to call Render() and ignore the callback, or call EndFrame() instead. if you call neither some aspects of windows focusing/moving will appear broken.)
- all rendering information are stored into command-lists until ImGui::Render() is called.
- ImGui never touches or know about your GPU state. the only function that knows about GPU is the RenderDrawListFn handler that you provide.
- effectively it means you can create widgets at any time in your code, regardless of considerations of being in "update" vs "render" phases of your own application.
- refer to the examples applications in the examples/ folder for instruction on how to setup your code.
- a typical application skeleton may be:

// Application init
ImGuiIO& io = ImGui::GetIO();
io.DisplaySize.x = 1920.0f;
io.DisplaySize.y = 1280.0f;
io.IniFilename = "imgui.ini";
io.RenderDrawListsFn = my_render_function;  // Setup a render function, or set to NULL and call GetDrawData() after Render() to access the render data.
// TODO: Fill others settings of the io structure

// Load texture atlas
// There is a default font so you don't need to care about choosing a font yet
unsigned char* pixels;
int width, height;
io.Fonts->GetTexDataAsRGBA32(pixels, &width, &height);
// TODO: At this points you've got a texture pointed to by 'pixels' and you need to upload that your your graphic system
// TODO: Store your texture pointer/identifier (whatever your engine uses) in 'io.Fonts->TexID'

// Application main loop
while (true)
{
// 1) get low-level inputs (e.g. on Win32, GetKeyboardState(), or poll your events, etc.)
// TODO: fill all fields of IO structure and call NewFrame
ImGuiIO& io = ImGui::GetIO();
io.DeltaTime = 1.0f/60.0f;
io.MousePos = mouse_pos;
io.MouseDown[0] = mouse_button_0;
io.MouseDown[1] = mouse_button_1;
io.KeysDown[i] = ...

// 2) call NewFrame(), after this point you can use ImGui::* functions anytime
ImGui::NewFrame();

// 3) most of your application code here
MyGameUpdate(); // may use any ImGui functions, e.g. ImGui::Begin("My window"); ImGui::Text("Hello, world!"); ImGui::End();
MyGameRender(); // may use any ImGui functions

// 4) render & swap video buffers
ImGui::Render();
SwapBuffers();
}

- You can read back 'io.WantCaptureMouse', 'io.WantCaptureKeybord' etc. flags from the IO structure to tell how ImGui intends to use your
inputs and to know if you should share them or hide them from the rest of your application. Read the FAQ below for more information.


API BREAKING CHANGES
====================

Occasionally introducing changes that are breaking the API. The breakage are generally minor and easy to fix.
Here is a change-log of API breaking changes, if you are using one of the functions listed, expect to have to fix some code.
Also read releases logs https://github.com/ocornut/imgui/releases for more details.

- 2017/07/20 (1.51) - Removed IsPosHoveringAnyWindow(ImVec2), which was partly broken and misleading. ASSERT + redirect user to io.WantCaptureMouse
- 2017/05/26 (1.50) - Removed ImFontConfig::MergeGlyphCenterV in favor of a more multipurpose ImFontConfig::GlyphOffset.
- 2017/05/01 (1.50) - Renamed ImDrawList::PathFill() (rarely used directly) to ImDrawList::PathFillConvex() for clarity.
- 2016/11/06 (1.50) - BeginChild(const char*) now applies the stack id to the provided label, consistently with other functions as it should always have been. It shouldn't affect you unless (extremely unlikely) you were appending multiple times to a same child from different locations of the stack id. If that's the case, generate an id with GetId() and use it instead of passing string to BeginChild().
- 2016/10/15 (1.50) - avoid 'void* user_data' parameter to io.SetClipboardTextFn/io.GetClipboardTextFn pointers. We pass io.ClipboardUserData to it.
- 2016/09/25 (1.50) - style.WindowTitleAlign is now a ImVec2 (ImGuiAlign enum was removed). set to (0.5f,0.5f) for horizontal+vertical centering, (0.0f,0.0f) for upper-left, etc.
- 2016/07/30 (1.50) - SameLine(x) with x>0.0f is now relative to left of column/group if any, and not always to left of window. This was sort of always the intent and hopefully breakage should be minimal.
- 2016/05/12 (1.49) - title bar (using ImGuiCol_TitleBg/ImGuiCol_TitleBgActive colors) isn't rendered over a window background (ImGuiCol_WindowBg color) anymore.
If your TitleBg/TitleBgActive alpha was 1.0f or you are using the default theme it will not affect you.
However if your TitleBg/TitleBgActive alpha was <1.0f you need to tweak your custom theme to readjust for the fact that we don't draw a WindowBg background behind the title bar.
This helper function will convert an old TitleBg/TitleBgActive color into a new one with the same visual output, given the OLD color and the OLD WindowBg color.
ImVec4 ConvertTitleBgCol(const ImVec4& win_bg_col, const ImVec4& title_bg_col)
{
float new_a = 1.0f - ((1.0f - win_bg_col.w) * (1.0f - title_bg_col.w)), k = title_bg_col.w / new_a;
return ImVec4((win_bg_col.x * win_bg_col.w + title_bg_col.x) * k, (win_bg_col.y * win_bg_col.w + title_bg_col.y) * k, (win_bg_col.z * win_bg_col.w + title_bg_col.z) * k, new_a);
}
If this is confusing, pick the RGB value from title bar from an old screenshot and apply this as TitleBg/TitleBgActive. Or you may just create TitleBgActive from a tweaked TitleBg color.
- 2016/05/07 (1.49) - removed confusing set of GetInternalState(), GetInternalStateSize(), SetInternalState() functions. Now using CreateContext(), DestroyContext(), GetCurrentContext(), SetCurrentContext().
- 2016/05/02 (1.49) - renamed SetNextTreeNodeOpened() to SetNextTreeNodeOpen(), no redirection.
- 2016/05/01 (1.49) - obsoleted old signature of CollapsingHeader(const char* label, const char* str_id = NULL, bool display_frame = true, bool default_open = false) as extra parameters were badly designed and rarely used. You can replace the "default_open = true" flag in new API with CollapsingHeader(label, ImGuiTreeNodeFlags_DefaultOpen).
- 2016/04/26 (1.49) - changed ImDrawList::PushClipRect(ImVec4 rect) to ImDraw::PushClipRect(Imvec2 min,ImVec2 max,bool intersect_with_current_clip_rect=false). Note that higher-level ImGui::PushClipRect() is preferable because it will clip at logic/widget level, whereas ImDrawList::PushClipRect() only affect your renderer.
- 2016/04/03 (1.48) - removed style.WindowFillAlphaDefault setting which was redundant. Bake default BG alpha inside style.Colors[ImGuiCol_WindowBg] and all other Bg color values. (ref github issue #337).
- 2016/04/03 (1.48) - renamed ImGuiCol_TooltipBg to ImGuiCol_PopupBg, used by popups/menus and tooltips. popups/menus were previously using ImGuiCol_WindowBg. (ref github issue #337)
- 2016/03/21 (1.48) - renamed GetWindowFont() to GetFont(), GetWindowFontSize() to GetFontSize(). Kept inline redirection function (will obsolete).
- 2016/03/02 (1.48) - InputText() completion/history/always callbacks: if you modify the text buffer manually (without using DeleteChars()/InsertChars() helper) you need to maintain the BufTextLen field. added an assert.
- 2016/01/23 (1.48) - fixed not honoring exact width passed to PushItemWidth(), previously it would add extra FramePadding.x*2 over that width. if you had manual pixel-perfect alignment in place it might affect you.
- 2015/12/27 (1.48) - fixed ImDrawList::AddRect() which used to render a rectangle 1 px too large on each axis.
- 2015/12/04 (1.47) - renamed Color() helpers to ValueColor() - dangerously named, rarely used and probably to be made obsolete.
- 2015/08/29 (1.45) - with the addition of horizontal scrollbar we made various fixes to inconsistencies with dealing with cursor position.
GetCursorPos()/SetCursorPos() functions now include the scrolled amount. It shouldn't affect the majority of users, but take note that SetCursorPosX(100.0f) puts you at +100 from the starting x position which may include scrolling, not at +100 from the window left side.
GetContentRegionMax()/GetWindowContentRegionMin()/GetWindowContentRegionMax() functions allow include the scrolled amount. Typically those were used in cases where no scrolling would happen so it may not be a problem, but watch out!
- 2015/08/29 (1.45) - renamed style.ScrollbarWidth to style.ScrollbarSize
- 2015/08/05 (1.44) - split imgui.cpp into extra files: imgui_demo.cpp imgui_draw.cpp imgui_internal.h that you need to add to your project.
- 2015/07/18 (1.44) - fixed angles in ImDrawList::PathArcTo(), PathArcToFast() (introduced in 1.43) being off by an extra PI for no justifiable reason
- 2015/07/14 (1.43) - add new ImFontAtlas::AddFont() API. For the old AddFont***, moved the 'font_no' parameter of ImFontAtlas::AddFont** functions to the ImFontConfig structure.
you need to render your textured triangles with bilinear filtering to benefit from sub-pixel positioning of text.
- 2015/07/08 (1.43) - switched rendering data to use indexed rendering. this is saving a fair amount of CPU/GPU and enables us to get anti-aliasing for a marginal cost.
this necessary change will break your rendering function! the fix should be very easy. sorry for that :(
- if you are using a vanilla copy of one of the imgui_impl_XXXX.cpp provided in the example, you just need to update your copy and you can ignore the rest.
- the signature of the io.RenderDrawListsFn handler has changed!
ImGui_XXXX_RenderDrawLists(ImDrawList** const cmd_lists, int cmd_lists_count)
became:
ImGui_XXXX_RenderDrawLists(ImDrawData* draw_data).
argument   'cmd_lists'        -> 'draw_data->CmdLists'
argument   'cmd_lists_count'  -> 'draw_data->CmdListsCount'
ImDrawList 'commands'         -> 'CmdBuffer'
ImDrawList 'vtx_buffer'       -> 'VtxBuffer'
ImDrawList  n/a               -> 'IdxBuffer' (new)
ImDrawCmd  'vtx_count'        -> 'ElemCount'
ImDrawCmd  'clip_rect'        -> 'ClipRect'
ImDrawCmd  'user_callback'    -> 'UserCallback'
ImDrawCmd  'texture_id'       -> 'TextureId'
- each ImDrawList now contains both a vertex buffer and an index buffer. For each command, render ElemCount/3 triangles using indices from the index buffer.
- if you REALLY cannot render indexed primitives, you can call the draw_data->DeIndexAllBuffers() method to de-index the buffers. This is slow and a waste of CPU/GPU. Prefer using indexed rendering!
- refer to code in the examples/ folder or ask on the GitHub if you are unsure of how to upgrade. please upgrade!
- 2015/07/10 (1.43) - changed SameLine() parameters from int to float.
- 2015/07/02 (1.42) - renamed SetScrollPosHere() to SetScrollFromCursorPos(). Kept inline redirection function (will obsolete).
- 2015/07/02 (1.42) - renamed GetScrollPosY() to GetScrollY(). Necessary to reduce confusion along with other scrolling functions, because positions (e.g. cursor position) are not equivalent to scrolling amount.
- 2015/06/14 (1.41) - changed ImageButton() default bg_col parameter from (0,0,0,1) (black) to (0,0,0,0) (transparent) - makes a difference when texture have transparence
- 2015/06/14 (1.41) - changed Selectable() API from (label, selected, size) to (label, selected, flags, size). Size override should have been rarely be used. Sorry!
- 2015/05/31 (1.40) - renamed GetWindowCollapsed() to IsWindowCollapsed() for consistency. Kept inline redirection function (will obsolete).
- 2015/05/31 (1.40) - renamed IsRectClipped() to IsRectVisible() for consistency. Note that return value is opposite! Kept inline redirection function (will obsolete).
- 2015/05/27 (1.40) - removed the third 'repeat_if_held' parameter from Button() - sorry! it was rarely used and inconsistent. Use PushButtonRepeat(true) / PopButtonRepeat() to enable repeat on desired buttons.
- 2015/05/11 (1.40) - changed BeginPopup() API, takes a string identifier instead of a bool. ImGui needs to manage the open/closed state of popups. Call OpenPopup() to actually set the "open" state of a popup. BeginPopup() returns true if the popup is opened.
- 2015/05/03 (1.40) - removed style.AutoFitPadding, using style.WindowPadding makes more sense (the default values were already the same).
- 2015/04/13 (1.38) - renamed IsClipped() to IsRectClipped(). Kept inline redirection function until 1.50.
- 2015/04/09 (1.38) - renamed ImDrawList::AddArc() to ImDrawList::AddArcFast() for compatibility with future API
- 2015/04/03 (1.38) - removed ImGuiCol_CheckHovered, ImGuiCol_CheckActive, replaced with the more general ImGuiCol_FrameBgHovered, ImGuiCol_FrameBgActive.
- 2014/04/03 (1.38) - removed support for passing -FLT_MAX..+FLT_MAX as the range for a SliderFloat(). Use DragFloat() or Inputfloat() instead.
- 2015/03/17 (1.36) - renamed GetItemBoxMin()/GetItemBoxMax()/IsMouseHoveringBox() to GetItemRectMin()/GetItemRectMax()/IsMouseHoveringRect(). Kept inline redirection function until 1.50.
- 2015/03/15 (1.36) - renamed style.TreeNodeSpacing to style.IndentSpacing, ImGuiStyleVar_TreeNodeSpacing to ImGuiStyleVar_IndentSpacing
- 2015/03/13 (1.36) - renamed GetWindowIsFocused() to IsWindowFocused(). Kept inline redirection function until 1.50.
- 2015/03/08 (1.35) - renamed style.ScrollBarWidth to style.ScrollbarWidth (casing)
- 2015/02/27 (1.34) - renamed OpenNextNode(bool) to SetNextTreeNodeOpened(bool, ImGuiSetCond). Kept inline redirection function until 1.50.
- 2015/02/27 (1.34) - renamed ImGuiSetCondition_*** to ImGuiSetCond_***, and _FirstUseThisSession becomes _Once.
- 2015/02/11 (1.32) - changed text input callback ImGuiTextEditCallback return type from void-->int. reserved for future use, return 0 for now.
- 2015/02/10 (1.32) - renamed GetItemWidth() to CalcItemWidth() to clarify its evolving behavior
- 2015/02/08 (1.31) - renamed GetTextLineSpacing() to GetTextLineHeightWithSpacing()
- 2015/02/01 (1.31) - removed IO.MemReallocFn (unused)
- 2015/01/19 (1.30) - renamed ImGuiStorage::GetIntPtr()/GetFloatPtr() to GetIntRef()/GetIntRef() because Ptr was conflicting with actual pointer storage functions.
- 2015/01/11 (1.30) - big font/image API change! now loads TTF file. allow for multiple fonts. no need for a PNG loader.
(1.30) - removed GetDefaultFontData(). uses io.Fonts->GetTextureData*() API to retrieve uncompressed pixels.
this sequence:
const void* png_data;
unsigned int png_size;
ImGui::GetDefaultFontData(NULL, NULL, &png_data, &png_size);
// <Copy to GPU>
became:
unsigned char* pixels;
int width, height;
io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
// <Copy to GPU>
io.Fonts->TexID = (your_texture_identifier);
you now have much more flexibility to load multiple TTF fonts and manage the texture buffer for internal needs.
it is now recommended that you sample the font texture with bilinear interpolation.
(1.30) - added texture identifier in ImDrawCmd passed to your render function (we can now render images). make sure to set io.Fonts->TexID.
(1.30) - removed IO.PixelCenterOffset (unnecessary, can be handled in user projection matrix)
(1.30) - removed ImGui::IsItemFocused() in favor of ImGui::IsItemActive() which handles all widgets
- 2014/12/10 (1.18) - removed SetNewWindowDefaultPos() in favor of new generic API SetNextWindowPos(pos, ImGuiSetCondition_FirstUseEver)
- 2014/11/28 (1.17) - moved IO.Font*** options to inside the IO.Font-> structure (FontYOffset, FontTexUvForWhite, FontBaseScale, FontFallbackGlyph)
- 2014/11/26 (1.17) - reworked syntax of IMGUI_ONCE_UPON_A_FRAME helper macro to increase compiler compatibility
- 2014/11/07 (1.15) - renamed IsHovered() to IsItemHovered()
- 2014/10/02 (1.14) - renamed IMGUI_INCLUDE_IMGUI_USER_CPP to IMGUI_INCLUDE_IMGUI_USER_INL and imgui_user.cpp to imgui_user.inl (more IDE friendly)
- 2014/09/25 (1.13) - removed 'text_end' parameter from IO.SetClipboardTextFn (the string is now always zero-terminated for simplicity)
- 2014/09/24 (1.12) - renamed SetFontScale() to SetWindowFontScale()
- 2014/09/24 (1.12) - moved IM_MALLOC/IM_REALLOC/IM_FREE preprocessor defines to IO.MemAllocFn/IO.MemReallocFn/IO.MemFreeFn
- 2014/08/30 (1.09) - removed IO.FontHeight (now computed automatically)
- 2014/08/30 (1.09) - moved IMGUI_FONT_TEX_UV_FOR_WHITE preprocessor define to IO.FontTexUvForWhite
- 2014/08/28 (1.09) - changed the behavior of IO.PixelCenterOffset following various rendering fixes


FREQUENTLY ASKED QUESTIONS (FAQ), TIPS
======================================

Q: How can I help?
A: - If you are experienced enough with ImGui and with C/C++, look at the todo list and see how you want/can help!
- Become a Patron/donate. Convince your company to become a Patron or provide serious funding for development time.

Q: How do I update to a newer version of ImGui?
A: Overwrite the following files:
imgui.cpp
imgui.h
imgui_demo.cpp
imgui_draw.cpp
imgui_internal.h
stb_rect_pack.h
stb_textedit.h
stb_truetype.h
Don't overwrite imconfig.h if you have made modification to your copy.
If you have a problem with a missing function/symbols, search for its name in the code, there will likely be a comment about it.
Check the "API BREAKING CHANGES" sections for a list of occasional API breaking changes.
Please report any issue to the GitHub page!

Q: What is ImTextureID and how do I display an image?
A: ImTextureID is a void* used to pass renderer-agnostic texture references around until it hits your render function.
ImGui knows nothing about what those bits represent, it just passes them around. It is up to you to decide what you want the void* to carry!
It could be an identifier to your OpenGL texture (cast GLuint to void*), a pointer to your custom engine material (cast MyMaterial* to void*), etc.
At the end of the chain, your renderer takes this void* to cast it back into whatever it needs to select a current texture to render.
Refer to examples applications, where each renderer (in a imgui_impl_xxxx.cpp file) is treating ImTextureID as a different thing.
(c++ tip: OpenGL uses integers to identify textures. You can safely store an integer into a void*, just cast it to void*, don't take it's address!)
To display a custom image/texture within an ImGui window, you may use ImGui::Image(), ImGui::ImageButton(), ImDrawList::AddImage() functions.
ImGui will generate the geometry and draw calls using the ImTextureID that you passed and which your renderer can use.
It is your responsibility to get textures uploaded to your GPU.

Q: I integrated ImGui in my engine and the text or lines are blurry..
A: In your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f).
Also make sure your orthographic projection matrix and io.DisplaySize matches your actual framebuffer dimension.

Q: I integrated ImGui in my engine and some elements are clipping or disappearing when I move windows around..
A: Most likely you are mishandling the clipping rectangles in your render function. Rectangles provided by ImGui are defined as (x1=left,y1=top,x2=right,y2=bottom) and NOT as (x1,y1,width,height).

Q: Can I have multiple widgets with the same label? Can I have widget without a label? (Yes)
A: Yes. A primer on the use of labels/IDs in ImGui..

- Elements that are not clickable, such as Text() items don't need an ID.

- Interactive widgets require state to be carried over multiple frames (most typically ImGui often needs to remember what is the "active" widget).
to do so they need a unique ID. unique ID are typically derived from a string label, an integer index or a pointer.

Button("OK");        // Label = "OK",     ID = hash of "OK"
Button("Cancel");    // Label = "Cancel", ID = hash of "Cancel"

- ID are uniquely scoped within windows, tree nodes, etc. so no conflict can happen if you have two buttons called "OK" in two different windows
or in two different locations of a tree.

- If you have a same ID twice in the same location, you'll have a conflict:

Button("OK");
Button("OK");           // ID collision! Both buttons will be treated as the same.

Fear not! this is easy to solve and there are many ways to solve it!

- When passing a label you can optionally specify extra unique ID information within string itself. This helps solving the simpler collision cases.
use "##" to pass a complement to the ID that won't be visible to the end-user:

Button("Play");         // Label = "Play",   ID = hash of "Play"
Button("Play##foo1");   // Label = "Play",   ID = hash of "Play##foo1" (different from above)
Button("Play##foo2");   // Label = "Play",   ID = hash of "Play##foo2" (different from above)

- If you want to completely hide the label, but still need an ID:

Checkbox("##On", &b);   // Label = "",       ID = hash of "##On" (no label!)

- Occasionally/rarely you might want change a label while preserving a constant ID. This allows you to animate labels.
For example you may want to include varying information in a window title bar (and windows are uniquely identified by their ID.. obviously)
Use "###" to pass a label that isn't part of ID:

Button("Hello###ID";   // Label = "Hello",  ID = hash of "ID"
Button("World###ID";   // Label = "World",  ID = hash of "ID" (same as above)

sprintf(buf, "My game (%f FPS)###MyGame");
Begin(buf);            // Variable label,   ID = hash of "MyGame"

- Use PushID() / PopID() to create scopes and avoid ID conflicts within the same Window.
This is the most convenient way of distinguishing ID if you are iterating and creating many UI elements.
You can push a pointer, a string or an integer value. Remember that ID are formed from the concatenation of everything in the ID stack!

for (int i = 0; i < 100; i++)
{
PushID(i);
Button("Click");   // Label = "Click",  ID = hash of integer + "label" (unique)
PopID();
}

for (int i = 0; i < 100; i++)
{
MyObject* obj = Objects[i];
PushID(obj);
Button("Click");   // Label = "Click",  ID = hash of pointer + "label" (unique)
PopID();
}

for (int i = 0; i < 100; i++)
{
MyObject* obj = Objects[i];
PushID(obj->Name);
Button("Click");   // Label = "Click",  ID = hash of string + "label" (unique)
PopID();
}

- More example showing that you can stack multiple prefixes into the ID stack:

Button("Click");     // Label = "Click",  ID = hash of "Click"
PushID("node");
Button("Click");     // Label = "Click",  ID = hash of "node" + "Click"
PushID(my_ptr);
Button("Click"); // Label = "Click",  ID = hash of "node" + ptr + "Click"
PopID();
PopID();

- Tree nodes implicitly creates a scope for you by calling PushID().

Button("Click");     // Label = "Click",  ID = hash of "Click"
if (TreeNode("node"))
{
Button("Click");   // Label = "Click",  ID = hash of "node" + "Click"
TreePop();
}

- When working with trees, ID are used to preserve the open/close state of each tree node.
Depending on your use cases you may want to use strings, indices or pointers as ID.
e.g. when displaying a single object that may change over time (1-1 relationship), using a static string as ID will preserve your node open/closed state when the targeted object change.
e.g. when displaying a list of objects, using indices or pointers as ID will preserve the node open/closed state differently. experiment and see what makes more sense!

Q: How can I tell when ImGui wants my mouse/keyboard inputs and when I can pass them to my application?
A: You can read the 'io.WantCaptureXXX' flags in the ImGuiIO structure. Preferably read them after calling ImGui::NewFrame() to avoid those flags lagging by one frame, but either should be fine.
When 'io.WantCaptureMouse' or 'io.WantCaptureKeyboard' flags are set you may want to discard/hide the inputs from the rest of your application.
When 'io.WantInputsCharacters' is set to may want to notify your OS to popup an on-screen keyboard, if available.
ImGui is tracking dragging and widget activity that may occur outside the boundary of a window, so 'io.WantCaptureMouse' is a more accurate and complete than testing for ImGui::IsMouseHoveringAnyWindow().
(Advanced note: text input releases focus on Return 'KeyDown', so the following Return 'KeyUp' event that your application receive will typically have 'io.WantcaptureKeyboard=false'.
Depending on your application logic it may or not be inconvenient. You might want to track which key-downs were for ImGui (e.g. with an array of bool) and filter out the corresponding key-ups.)

Q: How can I load a different font than the default? (default is an embedded version of ProggyClean.ttf, rendered at size 13)
A: Use the font atlas to load the TTF file you want:

ImGuiIO& io = ImGui::GetIO();
io.Fonts->AddFontFromFileTTF("myfontfile.ttf", size_in_pixels);
io.Fonts->GetTexDataAsRGBA32() or GetTexDataAsAlpha8()

Q: How can I easily use icons in my application?
A: The most convenient and practical way is to merge an icon font such as FontAwesome inside you main font. Then you can refer to icons within your strings.
Read 'How can I load multiple fonts?' and the file 'extra_fonts/README.txt' for instructions.

Q: How can I load multiple fonts?
A: Use the font atlas to pack them into a single texture:
(Read extra_fonts/README.txt and the code in ImFontAtlas for more details.)

ImGuiIO& io = ImGui::GetIO();
ImFont* font0 = io.Fonts->AddFontDefault();
ImFont* font1 = io.Fonts->AddFontFromFileTTF("myfontfile.ttf", size_in_pixels);
ImFont* font2 = io.Fonts->AddFontFromFileTTF("myfontfile2.ttf", size_in_pixels);
io.Fonts->GetTexDataAsRGBA32() or GetTexDataAsAlpha8()
// the first loaded font gets used by default
// use ImGui::PushFont()/ImGui::PopFont() to change the font at runtime

// Options
ImFontConfig config;
config.OversampleH = 3;
config.OversampleV = 1;
config.GlyphOffset.y -= 2.0f;      // Move everything by 2 pixels up
config.GlyphExtraSpacing.x = 1.0f; // Increase spacing between characters
io.Fonts->LoadFromFileTTF("myfontfile.ttf", size_pixels, &config);

// Combine multiple fonts into one (e.g. for icon fonts)
ImWchar ranges[] = { 0xf000, 0xf3ff, 0 };
ImFontConfig config;
config.MergeMode = true;
io.Fonts->AddFontDefault();
io.Fonts->LoadFromFileTTF("fontawesome-webfont.ttf", 16.0f, &config, ranges); // Merge icon font
io.Fonts->LoadFromFileTTF("myfontfile.ttf", size_pixels, NULL, &config, io.Fonts->GetGlyphRangesJapanese()); // Merge japanese glyphs

Q: How can I display and input non-Latin characters such as Chinese, Japanese, Korean, Cyrillic?
A: When loading a font, pass custom Unicode ranges to specify the glyphs to load.
All your strings needs to use UTF-8 encoding. Specifying literal in your source code using a local code page (such as CP-923 for Japanese or CP-1251 for Cyrillic) will not work.
In C++11 you can encode a string literal in UTF-8 by using the u8"hello" syntax. Otherwise you can convert yourself to UTF-8 or load text data from file already saved as UTF-8.
You can also try to remap your local codepage characters to their Unicode codepoint using font->AddRemapChar(), but international users may have problems reading/editing your source code.

io.Fonts->AddFontFromFileTTF("myfontfile.ttf", size_in_pixels, NULL, io.Fonts->GetGlyphRangesJapanese());  // Load Japanese characters
io.Fonts->GetTexDataAsRGBA32() or GetTexDataAsAlpha8()
io.ImeWindowHandle = MY_HWND;      // To input using Microsoft IME, give ImGui the hwnd of your application

As for text input, depends on you passing the right character code to io.AddInputCharacter(). The example applications do that.

Q: How can I use the drawing facilities without an ImGui window? (using ImDrawList API)
A: The easiest way is to create a dummy window. Call Begin() with NoTitleBar|NoResize|NoMove|NoScrollbar|NoSavedSettings|NoInputs flag, zero background alpha,
then retrieve the ImDrawList* via GetWindowDrawList() and draw to it in any way you like.

- tip: the construct 'IMGUI_ONCE_UPON_A_FRAME { ... }' will run the block of code only once a frame. You can use it to quickly add custom UI in the middle of a deep nested inner loop in your code.
- tip: you can create widgets without a Begin()/End() block, they will go in an implicit window called "Debug"
- tip: you can call Begin() multiple times with the same name during the same frame, it will keep appending to the same window. this is also useful to set yourself in the context of another window (to get/set other settings)
- tip: you can call Render() multiple times (e.g for VR renders).
- tip: call and read the ShowTestWindow() code in imgui_demo.cpp for more example of how to use ImGui!


ISSUES & TODO-LIST
==================
Issue numbers (#) refer to github issues listed at https://github.com/ocornut/imgui/issues
The list below consist mostly of ideas noted down before they are requested/discussed by users (at which point it usually moves to the github)

- doc: add a proper documentation+regression testing system (#435)
- window: add a way for very transient windows (non-saved, temporary overlay over hundreds of objects) to "clean" up from the global window list. perhaps a lightweight explicit cleanup pass.
- window: calling SetNextWindowSize() every frame with <= 0 doesn't do anything, may be useful to allow (particularly when used for a single axis) (#690)
- window: auto-fit feedback loop when user relies on any dynamic layout (window width multiplier, column) appears weird to end-user. clarify.
- window: allow resizing of child windows (possibly given min/max for each axis?)
- window: background options for child windows, border option (disable rounding)
- window: add a way to clear an existing window instead of appending (e.g. for tooltip override using a consistent api rather than the deferred tooltip)
- window: resizing from any sides? + mouse cursor directives for app.
!- window: begin with *p_open == false should return false.
- window: get size/pos helpers given names (see discussion in #249)
- window: a collapsed window can be stuck behind the main menu bar?
- window: when window is small, prioritize resize button over close button.
- window: detect extra End() call that pop the "Debug" window out and assert at call site instead of later.
- window/tooltip: allow to set the width of a tooltip to allow TextWrapped() etc. while keeping the height automatic.
- window: increase minimum size of a window with menus or fix the menu rendering so that it doesn't look odd.
- draw-list: maintaining bounding box per command would allow to merge draw command when clipping isn't relied on (typical non-scrolling window or non-overflowing column would merge with previous command).
!- scrolling: allow immediately effective change of scroll if we haven't appended items yet
- splitter/separator: formalize the splitter idiom into an official api (we want to handle n-way split) (#319)
- widgets: display mode: widget-label, label-widget (aligned on column or using fixed size), label-newline-tab-widget etc.
- widgets: clean up widgets internal toward exposing everything.
- widgets: add disabled and read-only modes (#211)
- main: considering adding an Init() function? some constructs are awkward in the implementation because of the lack of them.
!- main: make it so that a frame with no window registered won't refocus every window on subsequent frames (~bump LastFrameActive of all windows).
- main: IsItemHovered() make it more consistent for various type of widgets, widgets with multiple components, etc. also effectively IsHovered() region sometimes differs from hot region, e.g tree nodes
- main: IsItemHovered() info stored in a stack? so that 'if TreeNode() { Text; TreePop; } if IsHovered' return the hover state of the TreeNode?
- input text: clean up the mess caused by converting UTF-8 <> wchar. the code is rather inefficient right now and super fragile.
- input text: reorganize event handling, allow CharFilter to modify buffers, allow multiple events? (#541)
- input text: expose CursorPos in char filter event (#816)
- input text: flag to disable live update of the user buffer (also applies to float/int text input)
- input text: resize behavior - field could stretch when being edited? hover tooltip shows more text?
- input text: add ImGuiInputTextFlags_EnterToApply? (off #218)
- input text: add discard flag (e.g. ImGuiInputTextFlags_DiscardActiveBuffer) or make it easier to clear active focus for text replacement during edition (#725)
- input text multi-line: don't directly call AddText() which does an unnecessary vertex reserve for character count prior to clipping. and/or more line-based clipping to AddText(). and/or reorganize TextUnformatted/RenderText for more efficiency for large text (e.g TextUnformatted could clip and log separately, etc).
- input text multi-line: way to dynamically grow the buffer without forcing the user to initially allocate for worse case (follow up on #200)
- input text multi-line: line numbers? status bar? (follow up on #200)
- input text multi-line: behave better when user changes input buffer while editing is active (even though it is illegal behavior). namely, the change of buffer can create a scrollbar glitch (#725)
- input text multi-line: better horizontal scrolling support (#383, #1224)
- input text: allow centering/positioning text so that ctrl+clicking Drag or Slider keeps the textual value at the same pixel position.
- input number: optional range min/max for Input*() functions
- input number: holding [-]/[+] buttons could increase the step speed non-linearly (or user-controlled)
- input number: use mouse wheel to step up/down
- input number: applying arithmetics ops (+,-,*,/) messes up with text edit undo stack.
- button: provide a button that looks framed.
- text: proper alignment options
- image/image button: misalignment on padded/bordered button?
- image/image button: parameters are confusing, image() has tint_col,border_col whereas imagebutton() has bg_col/tint_col. Even thou they are different parameters ordering could be more consistent. can we fix that?
- layout: horizontal layout helper (#97)
- layout: horizontal flow until no space left (#404)
- layout: more generic alignment state (left/right/centered) for single items?
- layout: clean up the InputFloatN/SliderFloatN/ColorEdit4 layout code. item width should include frame padding.
- layout: BeginGroup() needs a border option.
- columns: declare column set (each column: fixed size, %, fill, distribute default size among fills) (#513, #125)
- columns: add a conditional parameter to SetColumnOffset() (#513, #125)
- columns: separator function or parameter that works within the column (currently Separator() bypass all columns) (#125)
- columns: columns header to act as button (~sort op) and allow resize/reorder (#513, #125)
- columns: user specify columns size (#513, #125)
- columns: flag to add horizontal separator above/below?
- columns/layout: setup minimum line height (equivalent of automatically calling AlignFirstTextHeightToWidgets)
- combo: sparse combo boxes (via function call?) / iterators
- combo: contents should extends to fit label if combo widget is small
- combo/listbox: keyboard control. need InputText-like non-active focus + key handling. considering keyboard for custom listbox (pr #203)
- listbox: multiple selection
- listbox: user may want to initial scroll to focus on the one selected value?
- listbox: keyboard navigation.
- listbox: scrolling should track modified selection.
!- popups/menus: clarify usage of popups id, how MenuItem/Selectable closing parent popups affects the ID, etc. this is quite fishy needs improvement! (#331, #402)
- popups: add variant using global identifier similar to Begin/End (#402)
- popups: border options. richer api like BeginChild() perhaps? (#197)
- tooltip: tooltip that doesn't fit in entire screen seems to lose their "last preferred button" and may teleport when moving mouse
- menus: local shortcuts, global shortcuts (#456, #126)
- menus: icons
- menus: menubars: some sort of priority / effect of main menu-bar on desktop size?
- menus: calling BeginMenu() twice with a same name doesn't seem to append nicely
- statusbar: add a per-window status bar helper similar to what menubar does.
- tabs (#261, #351)
- separator: separator on the initial position of a window is not visible (cursorpos.y <= clippos.y)
!- color: the color helpers/typing is a mess and needs sorting out.
- color: add a better color picker (#346)
- node/graph editor (#306)
- pie menus patterns (#434)
- drag'n drop, dragging helpers (carry dragging info, visualize drag source before clicking, drop target, etc.) (#143, #479)
- plot: PlotLines() should use the polygon-stroke facilities (currently issues with averaging normals)
- plot: make it easier for user to draw extra stuff into the graph (e.g: draw basis, highlight certain points, 2d plots, multiple plots)
- plot: "smooth" automatic scale over time, user give an input 0.0(full user scale) 1.0(full derived from value)
- plot: add a helper e.g. Plot(char* label, float value, float time_span=2.0f) that stores values and Plot them for you - probably another function name. and/or automatically allow to plot ANY displayed value (more reliance on stable ID)
- slider: allow using the [-]/[+] buttons used by InputFloat()/InputInt()
- slider: initial absolute click is imprecise. change to relative movement slider (same as scrollbar).
- slider: add dragging-based widgets to edit values with mouse (on 2 axises), saving screen real-estate.
- slider: tint background based on value (e.g. v_min -> v_max, or use 0.0f either side of the sign)
- slider & drag: int data passing through a float
- drag float: up/down axis
- drag float: added leeway on edge (e.g. a few invisible steps past the clamp limits)
- tree node / optimization: avoid formatting when clipped.
- tree node: tree-node/header right-most side doesn't take account of horizontal scrolling.
- tree node: add treenode/treepush int variants? not there because (void*) cast from int warns on some platforms/settings?
- tree node: try to apply scrolling at time of TreePop() if node was just opened and end of node is past scrolling limits?
- tree node / selectable render mismatch which is visible if you use them both next to each other (e.g. cf. property viewer)
- tree node: tweak color scheme to distinguish headers from selected tree node (#581)
- textwrapped: figure out better way to use TextWrapped() in an always auto-resize context (tooltip, etc.) (#249)
- settings: write more decent code to allow saving/loading new fields
- settings: api for per-tool simple persistent data (bool,int,float,columns sizes,etc.) in .ini file
- style: add window shadows.
- style/optimization: store rounded corners in texture to use 1 quad per corner (filled and wireframe) to lower the cost of rounding.
- style: color-box not always square?
- style: a concept of "compact style" that the end-user can easily rely on (e.g. PushStyleCompact()?) that maps to other settings? avoid implementing duplicate helpers such as SmallCheckbox(), etc.
- style: try to make PushStyleVar() more robust to incorrect parameters (to be more friendly to edit & continues situation).
- style: global scale setting.
- style: WindowPadding needs to be EVEN needs the 0.5 multiplier probably have a subtle effect on clip rectangle
- text: simple markup language for color change?
- font: dynamic font atlas to avoid baking huge ranges into bitmap and make scaling easier.
- font: small opt: for monospace font (like the defalt one) we can trim IndexXAdvance as long as trailing value is == FallbackXAdvance
- font: add support for kerning, probably optional. perhaps default to (32..128)^2 matrix ~ 36KB then hash fallback.
- font: add a simpler CalcTextSizeA() api? current one ok but not welcome if user needs to call it directly (without going through ImGui::CalcTextSize)
- font: fix AddRemapChar() to work before font has been built.
- log: LogButtons() options for specifying depth and/or hiding depth slider
- log: have more control over the log scope (e.g. stop logging when leaving current tree node scope)
- log: be able to log anything (e.g. right-click on a window/tree-node, shows context menu? log into tty/file/clipboard)
- log: let user copy any window content to clipboard easily (CTRL+C on windows? while moving it? context menu?). code is commented because it fails with multiple Begin/End pairs.
- filters: set a current filter that tree node can automatically query to hide themselves
- filters: handle wildcards (with implicit leading/trailing *), regexps
- shortcuts: add a shortcut api, e.g. parse "&Save" and/or "Save (CTRL+S)", pass in to widgets or provide simple ways to use (button=activate, input=focus)
!- keyboard: tooltip & combo boxes are messing up / not honoring keyboard tabbing
- keyboard: full keyboard navigation and focus. (#323)
- focus: preserve ActiveId/focus stack state, e.g. when opening a menu and close it, previously selected InputText() focus gets restored (#622)
- focus: SetKeyboardFocusHere() on with >= 0 offset could be done on same frame (else latch and modulate on beginning of next frame)
- input: rework IO system to be able to pass actual ordered/timestamped events. (~#335, #71)
- input: allow to decide and pass explicit double-clicks (e.g. for windows by the CS_DBLCLKS style).
- input: support track pad style scrolling & slider edit.
- misc: provide a way to compile out the entire implementation while providing a dummy API (e.g. #define IMGUI_DUMMY_IMPL)
- misc: double-clicking on title bar to minimize isn't consistent, perhaps move to single-click on left-most collapse icon?
- misc: provide HoveredTime and ActivatedTime to ease the creation of animations.
- style editor: have a more global HSV setter (e.g. alter hue on all elements). consider replacing active/hovered by offset in HSV space? (#438)
- style editor: color child window height expressed in multiple of line height.
- remote: make a system like RemoteImGui first-class citizen/project (#75)
- drawlist: move Font, FontSize, FontTexUvWhitePixel inside ImDrawList and make it self-contained (apart from drawing settings?)
- drawlist: end-user probably can't call Clear() directly because we expect a texture to be pushed in the stack.
- examples: directx9: save/restore device state more thoroughly.
- examples: window minimize, maximize (#583)
- optimization: add a flag to disable most of rendering, for the case where the user expect to skip it (#335)
- optimization: use another hash function than crc32, e.g. FNV1a
- optimization/render: merge command-lists with same clip-rect into one even if they aren't sequential? (as long as in-between clip rectangle don't overlap)?
- optimization: turn some the various stack vectors into statically-sized arrays
- optimization: better clipping for multi-component widgets
*/

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_PLACEMENT_NEW
#include "imgui_internal.h"

#include <ctype.h>      // toupper, isprint
#include <stdlib.h>     // NULL, malloc, free, qsort, atoi
#include <stdio.h>      // vsnprintf, sscanf, printf
#include <limits.h>     // INT_MIN, INT_MAX
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>     // intptr_t
#else
#include <stdint.h>     // intptr_t
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4127) // condition expression is constant
#pragma warning (disable: 4505) // unreferenced local function has been removed (stb stuff)
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#endif

// Clang warnings with -Weverything
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunknown-pragmas"        // warning : unknown warning group '-Wformat-pedantic *'        // not all warnings are known by all clang versions.. so ignoring warnings triggers new warnings on some configuration. great!
#pragma clang diagnostic ignored "-Wold-style-cast"         // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wfloat-equal"            // warning : comparing floating point with == or != is unsafe   // storing and comparing against same constants (typically 0.0f) is ok.
#pragma clang diagnostic ignored "-Wformat-nonliteral"      // warning : format string is not a string literal              // passing non-literal to vsnformat(). yes, user passing incorrect format strings can crash the code.
#pragma clang diagnostic ignored "-Wexit-time-destructors"  // warning : declaration requires an exit-time destructor       // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#pragma clang diagnostic ignored "-Wglobal-constructors"    // warning : declaration requires a global destructor           // similar to above, not sure what the exact difference it.
#pragma clang diagnostic ignored "-Wsign-conversion"        // warning : implicit conversion changes signedness             //
#pragma clang diagnostic ignored "-Wformat-pedantic"        // warning : format specifies type 'void *' but the argument has type 'xxxx *' // unreasonable, would lead to casting every %p arg to void*. probably enabled by -pedantic. 
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast" // warning : cast to 'void *' from smaller integer type 'int' //
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"          // warning: 'xxxx' defined but not used
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"      // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat"                   // warning: format '%p' expects argument of type 'void*', but argument 6 has type 'ImGuiWindow*'
#pragma GCC diagnostic ignored "-Wdouble-promotion"         // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"               // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#pragma GCC diagnostic ignored "-Wcast-qual"                // warning: cast from type 'xxxx' to type 'xxxx' casts away qualifiers
#endif

//-------------------------------------------------------------------------
// Forward Declarations
//-------------------------------------------------------------------------

static void             LogRenderedText(const ImVec2& ref_pos, const char* text, const char* text_end = NULL);

static void             PushMultiItemsWidths(int components, float w_full = 0.0f);
static float            GetDraggedColumnOffset(int column_index);

static bool             IsKeyPressedMap(ImGuiKey key, bool repeat = true);

static ImFont*          GetDefaultFont();
static void             SetCurrentFont(ImFont* font);
static void             SetCurrentWindow(ImGuiWindow* window);
static void             SetWindowScrollY(ImGuiWindow* window, float new_scroll_y);
static void             SetWindowPos(ImGuiWindow* window, const ImVec2& pos, ImGuiSetCond cond);
static void             SetWindowSize(ImGuiWindow* window, const ImVec2& size, ImGuiSetCond cond);
static void             SetWindowCollapsed(ImGuiWindow* window, bool collapsed, ImGuiSetCond cond);
static ImGuiWindow*     FindHoveredWindow(ImVec2 pos, bool excluding_childs);
static ImGuiWindow*     CreateNewWindow(const char* name, ImVec2 size, ImGuiWindowFlags flags);
static inline bool      IsWindowContentHoverable(ImGuiWindow* window);
static void             ClearSetNextWindowData();
static void             CheckStacksSize(ImGuiWindow* window, bool write);
static void             Scrollbar(ImGuiWindow* window, bool horizontal);

static void             AddDrawListToRenderList(ImVector<ImDrawList*>& out_render_list, ImDrawList* draw_list);
static void             AddWindowToRenderList(ImVector<ImDrawList*>& out_render_list, ImGuiWindow* window);
static void             AddWindowToSortedBuffer(ImVector<ImGuiWindow*>& out_sorted_windows, ImGuiWindow* window);

static ImGuiIniData*    FindWindowSettings(const char* name);
static ImGuiIniData*    AddWindowSettings(const char* name);
static void             LoadIniSettingsFromDisk(const char* ini_filename);
static void             SaveIniSettingsToDisk(const char* ini_filename);
static void             MarkIniSettingsDirty();

static void             PushColumnClipRect(int column_index = -1);
static ImRect           GetVisibleRect();

static bool             BeginPopupEx(const char* str_id, ImGuiWindowFlags extra_flags);
static void             CloseInactivePopups();
static void             ClosePopupToLevel(int remaining);
static void             ClosePopup(ImGuiID id);
static bool             IsPopupOpen(ImGuiID id);
static ImGuiWindow*     GetFrontMostModalRootWindow();
static ImVec2           FindBestPopupWindowPos(const ImVec2& base_pos, const ImVec2& size, int* last_dir, const ImRect& rect_to_avoid);

static bool             InputTextFilterCharacter(unsigned int* p_char, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data);
static int              InputTextCalcTextLenAndLineCount(const char* text_begin, const char** out_text_end);
static ImVec2           InputTextCalcTextSizeW(const ImWchar* text_begin, const ImWchar* text_end, const ImWchar** remaining = NULL, ImVec2* out_offset = NULL, bool stop_on_new_line = false);

static inline void      DataTypeFormatString(ImGuiDataType data_type, void* data_ptr, const char* display_format, char* buf, int buf_size);
static inline void      DataTypeFormatString(ImGuiDataType data_type, void* data_ptr, int decimal_precision, char* buf, int buf_size);
static void             DataTypeApplyOp(ImGuiDataType data_type, int op, void* value1, const void* value2);
static bool             DataTypeApplyOpFromText(const char* buf, const char* initial_value_buf, ImGuiDataType data_type, void* data_ptr, const char* scalar_format);

//-----------------------------------------------------------------------------
// Platform dependent default implementations
//-----------------------------------------------------------------------------

static const char*      GetClipboardTextFn_DefaultImpl(void* user_data);
static void             SetClipboardTextFn_DefaultImpl(void* user_data, const char* text);
static void             ImeSetInputScreenPosFn_DefaultImpl(int x, int y);

//-----------------------------------------------------------------------------
// Context
//-----------------------------------------------------------------------------

// Default font atlas storage .
// New contexts always point by default to this font atlas. It can be changed by reassigning the GetIO().Fonts variable.
static ImFontAtlas      GImDefaultFontAtlas;

// Default context storage + current context pointer.
// Implicitely used by all ImGui functions. Always assumed to be != NULL. Change to a different context by calling ImGui::SetCurrentContext()
// ImGui is currently not thread-safe because of this variable. If you want thread-safety to allow N threads to access N different contexts, you might work around it by:
// - Having multiple instances of the ImGui code compiled inside different namespace (easiest/safest, if you have a finite number of contexts)
// - or: Changing this variable to be TLS. You may #define GImGui in imconfig.h for further custom hackery. Future development aim to make this context pointer explicit to all calls. Also read https://github.com/ocornut/imgui/issues/586
#ifndef GImGui
static ImGuiContext     GImDefaultContext;
ImGuiContext*           GImGui = &GImDefaultContext;
#endif

//-----------------------------------------------------------------------------
// User facing structures
//-----------------------------------------------------------------------------

ImGuiStyle::ImGuiStyle()
{
	Alpha = 1.0f;             // Global alpha applies to everything in ImGui
	WindowPadding = ImVec2(8, 8);      // Padding within a window
	WindowMinSize = ImVec2(32, 32);    // Minimum window size
	WindowRounding = 9.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	WindowTitleAlign = ImVec2(0.0f, 0.5f);// Alignment for title bar text
	ChildWindowRounding = 0.0f;             // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
	FramePadding = ImVec2(4, 3);      // Padding within a framed rectangle (used by most widgets)
	FrameRounding = 0.0f;             // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	ItemSpacing = ImVec2(8, 4);      // Horizontal and vertical spacing between widgets/lines
	ItemInnerSpacing = ImVec2(4, 4);      // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	TouchExtraPadding = ImVec2(0, 0);      // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	IndentSpacing = 21.0f;            // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	ColumnsMinSpacing = 6.0f;             // Minimum horizontal spacing between two columns
	ScrollbarSize = 16.0f;            // Width of the vertical scrollbar, Height of the horizontal scrollbar
	ScrollbarRounding = 9.0f;             // Radius of grab corners rounding for scrollbar
	GrabMinSize = 10.0f;            // Minimum width/height of a grab box for slider/scrollbar
	GrabRounding = 0.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	ButtonTextAlign = ImVec2(0.5f, 0.5f);// Alignment of button text when button is larger than text.
	DisplayWindowPadding = ImVec2(22, 22);    // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
	DisplaySafeAreaPadding = ImVec2(4, 4);      // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	AntiAliasedLines = true;             // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	AntiAliasedShapes = true;             // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
	CurveTessellationTol = 1.25f;            // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.

	Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
	Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.30f);   // Background of checkbox, radio button, plot, slider, text input
	Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
	Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
	Colors[ImGuiCol_TitleBg] = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
	Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
	Colors[ImGuiCol_TitleBgActive] = ImVec4(0.32f, 0.32f, 0.63f, 0.87f);
	Colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
	Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
	Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
	Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 0.40f);
	Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
	Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
	Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	Colors[ImGuiCol_Button] = ImVec4(0.67f, 0.40f, 0.40f, 0.60f);
	Colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.40f, 0.40f, 1.00f);
	Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	Colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
	Colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
	Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
	Colors[ImGuiCol_ColumnActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
	Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	Colors[ImGuiCol_CloseButton] = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
	Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
	Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

ImGuiIO::ImGuiIO()
{
	// Most fields are initialized with zero
	memset(this, 0, sizeof(*this));

	DisplaySize = ImVec2(-1.0f, -1.0f);
	DeltaTime = 1.0f / 60.0f;
	IniSavingRate = 5.0f;
	IniFilename = "imgui.ini";
	LogFilename = "imgui_log.txt";
	Fonts = &GImDefaultFontAtlas;
	FontGlobalScale = 1.0f;
	FontDefault = NULL;
	DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	MousePos = ImVec2(-1, -1);
	MousePosPrev = ImVec2(-1, -1);
	MouseDoubleClickTime = 0.30f;
	MouseDoubleClickMaxDist = 6.0f;
	MouseDragThreshold = 6.0f;
	for (int i = 0; i < IM_ARRAYSIZE(MouseDownDuration); i++)
		MouseDownDuration[i] = MouseDownDurationPrev[i] = -1.0f;
	for (int i = 0; i < IM_ARRAYSIZE(KeysDownDuration); i++)
		KeysDownDuration[i] = KeysDownDurationPrev[i] = -1.0f;
	for (int i = 0; i < ImGuiKey_COUNT; i++)
		KeyMap[i] = -1;
	KeyRepeatDelay = 0.250f;
	KeyRepeatRate = 0.050f;
	UserData = NULL;

	// User functions
	RenderDrawListsFn = NULL;
	MemAllocFn = malloc;
	MemFreeFn = free;
	GetClipboardTextFn = GetClipboardTextFn_DefaultImpl;   // Platform dependent default implementations
	SetClipboardTextFn = SetClipboardTextFn_DefaultImpl;
	ClipboardUserData = NULL;
	ImeSetInputScreenPosFn = ImeSetInputScreenPosFn_DefaultImpl;

	// Set OS X style defaults based on __APPLE__ compile time flag
#ifdef __APPLE__
	OSXBehaviors = true;
#endif
}

// Pass in translated ASCII characters for text input.
// - with glfw you can get those from the callback set in glfwSetCharCallback()
// - on Windows you can get those using ToAscii+keyboard state, or via the WM_CHAR message
void ImGuiIO::AddInputCharacter(ImWchar c)
{
	const int n = ImStrlenW(InputCharacters);
	if (n + 1 < IM_ARRAYSIZE(InputCharacters))
	{
		InputCharacters[n] = c;
		InputCharacters[n + 1] = '\0';
	}
}

void ImGuiIO::AddInputCharactersUTF8(const char* utf8_chars)
{
	// We can't pass more wchars than ImGuiIO::InputCharacters[] can hold so don't convert more
	const int wchars_buf_len = sizeof(ImGuiIO::InputCharacters) / sizeof(ImWchar);
	ImWchar wchars[wchars_buf_len];
	ImTextStrFromUtf8(wchars, wchars_buf_len, utf8_chars, NULL);
	for (int i = 0; i < wchars_buf_len && wchars[i] != 0; i++)
		AddInputCharacter(wchars[i]);
}

//-----------------------------------------------------------------------------
// HELPERS
//-----------------------------------------------------------------------------

#define IM_F32_TO_INT8_UNBOUND(_VAL)    ((int)((_VAL) * 255.0f + ((_VAL)>=0 ? 0.5f : -0.5f)))   // Unsaturated, for display purpose 
#define IM_F32_TO_INT8_SAT(_VAL)        ((int)(ImSaturate(_VAL) * 255.0f + 0.5f))               // Saturated, always output 0..255

// Play it nice with Windows users. Notepad in 2015 still doesn't display text data with Unix-style \n.
#ifdef _WIN32
#define IM_NEWLINE "\r\n"
#else
#define IM_NEWLINE "\n"
#endif

bool ImIsPointInTriangle(const ImVec2& p, const ImVec2& a, const ImVec2& b, const ImVec2& c)
{
	bool b1 = ((p.x - b.x) * (a.y - b.y) - (p.y - b.y) * (a.x - b.x)) < 0.0f;
	bool b2 = ((p.x - c.x) * (b.y - c.y) - (p.y - c.y) * (b.x - c.x)) < 0.0f;
	bool b3 = ((p.x - a.x) * (c.y - a.y) - (p.y - a.y) * (c.x - a.x)) < 0.0f;
	return ((b1 == b2) && (b2 == b3));
}

int ImStricmp(const char* str1, const char* str2)
{
	int d;
	while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; }
	return d;
}

int ImStrnicmp(const char* str1, const char* str2, int count)
{
	int d = 0;
	while (count > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; count--; }
	return d;
}

void ImStrncpy(char* dst, const char* src, int count)
{
	if (count < 1) return;
	strncpy(dst, src, (size_t)count);
	dst[count - 1] = 0;
}

char* ImStrdup(const char *str)
{
	size_t len = strlen(str) + 1;
	void* buff = ImGui::MemAlloc(len);
	return (char*)memcpy(buff, (const void*)str, len);
}

int ImStrlenW(const ImWchar* str)
{
	int n = 0;
	while (*str++) n++;
	return n;
}

const ImWchar* ImStrbolW(const ImWchar* buf_mid_line, const ImWchar* buf_begin) // find beginning-of-line
{
	while (buf_mid_line > buf_begin && buf_mid_line[-1] != '\n')
		buf_mid_line--;
	return buf_mid_line;
}

const char* ImStristr(const char* haystack, const char* haystack_end, const char* needle, const char* needle_end)
{
	if (!needle_end)
		needle_end = needle + strlen(needle);

	const char un0 = (char)toupper(*needle);
	while ((!haystack_end && *haystack) || (haystack_end && haystack < haystack_end))
	{
		if (toupper(*haystack) == un0)
		{
			const char* b = needle + 1;
			for (const char* a = haystack + 1; b < needle_end; a++, b++)
				if (toupper(*a) != toupper(*b))
					break;
			if (b == needle_end)
				return haystack;
		}
		haystack++;
	}
	return NULL;
}


// MSVC version appears to return -1 on overflow, whereas glibc appears to return total count (which may be >= buf_size). 
// Ideally we would test for only one of those limits at runtime depending on the behavior the vsnprintf(), but trying to deduct it at compile time sounds like a pandora can of worm.
int ImFormatString(char* buf, int buf_size, const char* fmt, ...)
{
	IM_ASSERT(buf_size > 0);
	va_list args;
	va_start(args, fmt);
	int w = vsnprintf(buf, buf_size, fmt, args);
	va_end(args);
	if (w == -1 || w >= buf_size)
		w = buf_size - 1;
	buf[w] = 0;
	return w;
}

int ImFormatStringV(char* buf, int buf_size, const char* fmt, va_list args)
{
	IM_ASSERT(buf_size > 0);
	int w = vsnprintf(buf, buf_size, fmt, args);
	if (w == -1 || w >= buf_size)
		w = buf_size - 1;
	buf[w] = 0;
	return w;
}

// Pass data_size==0 for zero-terminated strings
// FIXME-OPT: Replace with e.g. FNV1a hash? CRC32 pretty much randomly access 1KB. Need to do proper measurements.
ImU32 ImHash(const void* data, int data_size, ImU32 seed)
{
	static ImU32 crc32_lut[256] = { 0 };
	if (!crc32_lut[1])
	{
		const ImU32 polynomial = 0xEDB88320;
		for (ImU32 i = 0; i < 256; i++)
		{
			ImU32 crc = i;
			for (ImU32 j = 0; j < 8; j++)
				crc = (crc >> 1) ^ (ImU32(-int(crc & 1)) & polynomial);
			crc32_lut[i] = crc;
		}
	}

	seed = ~seed;
	ImU32 crc = seed;
	const unsigned char* current = (const unsigned char*)data;

	if (data_size > 0)
	{
		// Known size
		while (data_size--)
			crc = (crc >> 8) ^ crc32_lut[(crc & 0xFF) ^ *current++];
	}
	else
	{
		// Zero-terminated string
		while (unsigned char c = *current++)
		{
			// We support a syntax of "label###id" where only "###id" is included in the hash, and only "label" gets displayed.
			// Because this syntax is rarely used we are optimizing for the common case.
			// - If we reach ### in the string we discard the hash so far and reset to the seed.
			// - We don't do 'current += 2; continue;' after handling ### to keep the code smaller.
			if (c == '#' && current[0] == '#' && current[1] == '#')
				crc = seed;
			crc = (crc >> 8) ^ crc32_lut[(crc & 0xFF) ^ c];
		}
	}
	return ~crc;
}

//-----------------------------------------------------------------------------
// ImText* helpers
//-----------------------------------------------------------------------------

// Convert UTF-8 to 32-bits character, process single character input.
// Based on stb_from_utf8() from github.com/nothings/stb/
// We handle UTF-8 decoding error by skipping forward.
int ImTextCharFromUtf8(unsigned int* out_char, const char* in_text, const char* in_text_end)
{
	unsigned int c = (unsigned int)-1;
	const unsigned char* str = (const unsigned char*)in_text;
	if (!(*str & 0x80))
	{
		c = (unsigned int)(*str++);
		*out_char = c;
		return 1;
	}
	if ((*str & 0xe0) == 0xc0)
	{
		*out_char = 0xFFFD; // will be invalid but not end of string
		if (in_text_end && in_text_end - (const char*)str < 2) return 1;
		if (*str < 0xc2) return 2;
		c = (unsigned int)((*str++ & 0x1f) << 6);
		if ((*str & 0xc0) != 0x80) return 2;
		c += (*str++ & 0x3f);
		*out_char = c;
		return 2;
	}
	if ((*str & 0xf0) == 0xe0)
	{
		*out_char = 0xFFFD; // will be invalid but not end of string
		if (in_text_end && in_text_end - (const char*)str < 3) return 1;
		if (*str == 0xe0 && (str[1] < 0xa0 || str[1] > 0xbf)) return 3;
		if (*str == 0xed && str[1] > 0x9f) return 3; // str[1] < 0x80 is checked below
		c = (unsigned int)((*str++ & 0x0f) << 12);
		if ((*str & 0xc0) != 0x80) return 3;
		c += (unsigned int)((*str++ & 0x3f) << 6);
		if ((*str & 0xc0) != 0x80) return 3;
		c += (*str++ & 0x3f);
		*out_char = c;
		return 3;
	}
	if ((*str & 0xf8) == 0xf0)
	{
		*out_char = 0xFFFD; // will be invalid but not end of string
		if (in_text_end && in_text_end - (const char*)str < 4) return 1;
		if (*str > 0xf4) return 4;
		if (*str == 0xf0 && (str[1] < 0x90 || str[1] > 0xbf)) return 4;
		if (*str == 0xf4 && str[1] > 0x8f) return 4; // str[1] < 0x80 is checked below
		c = (unsigned int)((*str++ & 0x07) << 18);
		if ((*str & 0xc0) != 0x80) return 4;
		c += (unsigned int)((*str++ & 0x3f) << 12);
		if ((*str & 0xc0) != 0x80) return 4;
		c += (unsigned int)((*str++ & 0x3f) << 6);
		if ((*str & 0xc0) != 0x80) return 4;
		c += (*str++ & 0x3f);
		// utf-8 encodings of values used in surrogate pairs are invalid
		if ((c & 0xFFFFF800) == 0xD800) return 4;
		*out_char = c;
		return 4;
	}
	*out_char = 0;
	return 0;
}

int ImTextStrFromUtf8(ImWchar* buf, int buf_size, const char* in_text, const char* in_text_end, const char** in_text_remaining)
{
	ImWchar* buf_out = buf;
	ImWchar* buf_end = buf + buf_size;
	while (buf_out < buf_end - 1 && (!in_text_end || in_text < in_text_end) && *in_text)
	{
		unsigned int c;
		in_text += ImTextCharFromUtf8(&c, in_text, in_text_end);
		if (c == 0)
			break;
		if (c < 0x10000)    // FIXME: Losing characters that don't fit in 2 bytes
			*buf_out++ = (ImWchar)c;
	}
	*buf_out = 0;
	if (in_text_remaining)
		*in_text_remaining = in_text;
	return (int)(buf_out - buf);
}

int ImTextCountCharsFromUtf8(const char* in_text, const char* in_text_end)
{
	int char_count = 0;
	while ((!in_text_end || in_text < in_text_end) && *in_text)
	{
		unsigned int c;
		in_text += ImTextCharFromUtf8(&c, in_text, in_text_end);
		if (c == 0)
			break;
		if (c < 0x10000)
			char_count++;
	}
	return char_count;
}

// Based on stb_to_utf8() from github.com/nothings/stb/
static inline int ImTextCharToUtf8(char* buf, int buf_size, unsigned int c)
{
	if (c < 0x80)
	{
		buf[0] = (char)c;
		return 1;
	}
	if (c < 0x800)
	{
		if (buf_size < 2) return 0;
		buf[0] = (char)(0xc0 + (c >> 6));
		buf[1] = (char)(0x80 + (c & 0x3f));
		return 2;
	}
	if (c >= 0xdc00 && c < 0xe000)
	{
		return 0;
	}
	if (c >= 0xd800 && c < 0xdc00)
	{
		if (buf_size < 4) return 0;
		buf[0] = (char)(0xf0 + (c >> 18));
		buf[1] = (char)(0x80 + ((c >> 12) & 0x3f));
		buf[2] = (char)(0x80 + ((c >> 6) & 0x3f));
		buf[3] = (char)(0x80 + ((c) & 0x3f));
		return 4;
	}
	//else if (c < 0x10000)
	{
		if (buf_size < 3) return 0;
		buf[0] = (char)(0xe0 + (c >> 12));
		buf[1] = (char)(0x80 + ((c >> 6) & 0x3f));
		buf[2] = (char)(0x80 + ((c) & 0x3f));
		return 3;
	}
}

static inline int ImTextCountUtf8BytesFromChar(unsigned int c)
{
	if (c < 0x80) return 1;
	if (c < 0x800) return 2;
	if (c >= 0xdc00 && c < 0xe000) return 0;
	if (c >= 0xd800 && c < 0xdc00) return 4;
	return 3;
}

int ImTextStrToUtf8(char* buf, int buf_size, const ImWchar* in_text, const ImWchar* in_text_end)
{
	char* buf_out = buf;
	const char* buf_end = buf + buf_size;
	while (buf_out < buf_end - 1 && (!in_text_end || in_text < in_text_end) && *in_text)
	{
		unsigned int c = (unsigned int)(*in_text++);
		if (c < 0x80)
			*buf_out++ = (char)c;
		else
			buf_out += ImTextCharToUtf8(buf_out, (int)(buf_end - buf_out - 1), c);
	}
	*buf_out = 0;
	return (int)(buf_out - buf);
}

int ImTextCountUtf8BytesFromStr(const ImWchar* in_text, const ImWchar* in_text_end)
{
	int bytes_count = 0;
	while ((!in_text_end || in_text < in_text_end) && *in_text)
	{
		unsigned int c = (unsigned int)(*in_text++);
		if (c < 0x80)
			bytes_count++;
		else
			bytes_count += ImTextCountUtf8BytesFromChar(c);
	}
	return bytes_count;
}

ImVec4 ImGui::ColorConvertU32ToFloat4(ImU32 in)
{
	float s = 1.0f / 255.0f;
	return ImVec4(
		((in >> IM_COL32_R_SHIFT) & 0xFF) * s,
		((in >> IM_COL32_G_SHIFT) & 0xFF) * s,
		((in >> IM_COL32_B_SHIFT) & 0xFF) * s,
		((in >> IM_COL32_A_SHIFT) & 0xFF) * s);
}

ImU32 ImGui::ColorConvertFloat4ToU32(const ImVec4& in)
{
	ImU32 out;
	out = ((ImU32)IM_F32_TO_INT8_SAT(in.x)) << IM_COL32_R_SHIFT;
	out |= ((ImU32)IM_F32_TO_INT8_SAT(in.y)) << IM_COL32_G_SHIFT;
	out |= ((ImU32)IM_F32_TO_INT8_SAT(in.z)) << IM_COL32_B_SHIFT;
	out |= ((ImU32)IM_F32_TO_INT8_SAT(in.w)) << IM_COL32_A_SHIFT;
	return out;
}

ImU32 ImGui::GetColorU32(ImGuiCol idx, float alpha_mul)
{
	ImVec4 c = GImGui->Style.Colors[idx];
	c.w *= GImGui->Style.Alpha * alpha_mul;
	return ColorConvertFloat4ToU32(c);
}

ImU32 ImGui::GetColorU32(const ImVec4& col)
{
	ImVec4 c = col;
	c.w *= GImGui->Style.Alpha;
	return ColorConvertFloat4ToU32(c);
}

// Convert rgb floats ([0-1],[0-1],[0-1]) to hsv floats ([0-1],[0-1],[0-1]), from Foley & van Dam p592
// Optimized http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
void ImGui::ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v)
{
	float K = 0.f;
	if (g < b)
	{
		const float tmp = g; g = b; b = tmp;
		K = -1.f;
	}
	if (r < g)
	{
		const float tmp = r; r = g; g = tmp;
		K = -2.f / 6.f - K;
	}

	const float chroma = r - (g < b ? g : b);
	out_h = fabsf(K + (g - b) / (6.f * chroma + 1e-20f));
	out_s = chroma / (r + 1e-20f);
	out_v = r;
}

// Convert hsv floats ([0-1],[0-1],[0-1]) to rgb floats ([0-1],[0-1],[0-1]), from Foley & van Dam p593
// also http://en.wikipedia.org/wiki/HSL_and_HSV
void ImGui::ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b)
{
	if (s == 0.0f)
	{
		// gray
		out_r = out_g = out_b = v;
		return;
	}

	h = fmodf(h, 1.0f) / (60.0f / 360.0f);
	int   i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i)
	{
	case 0: out_r = v; out_g = t; out_b = p; break;
	case 1: out_r = q; out_g = v; out_b = p; break;
	case 2: out_r = p; out_g = v; out_b = t; break;
	case 3: out_r = p; out_g = q; out_b = v; break;
	case 4: out_r = t; out_g = p; out_b = v; break;
	case 5: default: out_r = v; out_g = p; out_b = q; break;
	}
}

bool ImGui::ColorPicker(const char* label, float* col)
{
	const int    EDGE_SIZE = 200; // = int( ImGui::GetWindowWidth() * 0.75f );
	const ImVec2 SV_PICKER_SIZE = ImVec2(EDGE_SIZE, EDGE_SIZE);
	const float  SPACING = ImGui::GetStyle().ItemInnerSpacing.x;
	const float  HUE_PICKER_WIDTH = 20.f;
	const float  CROSSHAIR_SIZE = 7.0f;

	ImColor color(col[0], col[1], col[2]);
	bool value_changed = false;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	// setup

	ImVec2 picker_pos = ImGui::GetCursorScreenPos();

	float hue, saturation, value;
	ImGui::ColorConvertRGBtoHSV(
		color.Value.x, color.Value.y, color.Value.z, hue, saturation, value);

	// draw hue bar

	ImColor colors[] = { ImColor(255, 0, 0),
		ImColor(255, 255, 0),
		ImColor(0, 255, 0),
		ImColor(0, 255, 255),
		ImColor(0, 0, 255),
		ImColor(255, 0, 255),
		ImColor(255, 0, 0) };

	for (int i = 0; i < 6; ++i)
	{
		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING, picker_pos.y + i * (SV_PICKER_SIZE.y / 6)),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + HUE_PICKER_WIDTH,
				picker_pos.y + (i + 1) * (SV_PICKER_SIZE.y / 6)),
			colors[i],
			colors[i],
			colors[i + 1],
			colors[i + 1]);
	}

	draw_list->AddLine(
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING - 2, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImVec2(picker_pos.x + SV_PICKER_SIZE.x + SPACING + 2 + HUE_PICKER_WIDTH, picker_pos.y + hue * SV_PICKER_SIZE.y),
		ImColor(255, 255, 255));

	// draw color matrix

	{
		const ImU32 c_oColorBlack = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
		const ImU32 c_oColorBlackTransparent = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.f));
		const ImU32 c_oColorWhite = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

		ImVec4 cHueValue(1, 1, 1, 1);
		ImGui::ColorConvertHSVtoRGB(hue, 1, 1, cHueValue.x, cHueValue.y, cHueValue.z);
		ImU32 oHueColor = ImGui::ColorConvertFloat4ToU32(cHueValue);

		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x, picker_pos.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
			c_oColorWhite,
			oHueColor,
			oHueColor,
			c_oColorWhite
		);

		draw_list->AddRectFilledMultiColor(
			ImVec2(picker_pos.x, picker_pos.y),
			ImVec2(picker_pos.x + SV_PICKER_SIZE.x, picker_pos.y + SV_PICKER_SIZE.y),
			c_oColorBlackTransparent,
			c_oColorBlackTransparent,
			c_oColorBlack,
			c_oColorBlack
		);
	}

	// draw cross-hair

	float x = saturation * SV_PICKER_SIZE.x;
	float y = (1 - value) * SV_PICKER_SIZE.y;
	ImVec2 p(picker_pos.x + x, picker_pos.y + y);
	draw_list->AddLine(ImVec2(p.x - CROSSHAIR_SIZE, p.y), ImVec2(p.x - 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x + CROSSHAIR_SIZE, p.y), ImVec2(p.x + 2, p.y), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y + CROSSHAIR_SIZE), ImVec2(p.x, p.y + 2), ImColor(255, 255, 255));
	draw_list->AddLine(ImVec2(p.x, p.y - CROSSHAIR_SIZE), ImVec2(p.x, p.y - 2), ImColor(255, 255, 255));

	// color matrix logic

	ImGui::InvisibleButton("saturation_value_selector", SV_PICKER_SIZE);

	if (ImGui::IsItemActive() && ImGui::GetIO().MouseDown[0])
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(
			ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		/**/ if (mouse_pos_in_canvas.x <                     0) mouse_pos_in_canvas.x = 0;
		else if (mouse_pos_in_canvas.x >= SV_PICKER_SIZE.x - 1) mouse_pos_in_canvas.x = SV_PICKER_SIZE.x - 1;

		/**/ if (mouse_pos_in_canvas.y <                     0) mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1) mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		value = 1 - (mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1));
		saturation = mouse_pos_in_canvas.x / (SV_PICKER_SIZE.x - 1);
		value_changed = true;
	}

	// hue bar logic

	ImGui::SetCursorScreenPos(ImVec2(picker_pos.x + SPACING + SV_PICKER_SIZE.x, picker_pos.y));
	ImGui::InvisibleButton("hue_selector", ImVec2(HUE_PICKER_WIDTH, SV_PICKER_SIZE.y));

	if (ImGui::GetIO().MouseDown[0] && (ImGui::IsItemHovered() || ImGui::IsItemActive()))
	{
		ImVec2 mouse_pos_in_canvas = ImVec2(
			ImGui::GetIO().MousePos.x - picker_pos.x, ImGui::GetIO().MousePos.y - picker_pos.y);

		/**/ if (mouse_pos_in_canvas.y <                     0) mouse_pos_in_canvas.y = 0;
		else if (mouse_pos_in_canvas.y >= SV_PICKER_SIZE.y - 1) mouse_pos_in_canvas.y = SV_PICKER_SIZE.y - 1;

		hue = mouse_pos_in_canvas.y / (SV_PICKER_SIZE.y - 1);
		value_changed = true;
	}

	// R,G,B or H,S,V color editor

	//color = ImColor::HSV(hue >= 1 ? hue - 10 * 1e-6 : hue, saturation > 0 ? saturation : 10 * 1e-6, value > 0 ? value : 1e-6);
	color = ImColor::HSV(hue, saturation, value);
	col[0] = color.Value.x;
	col[1] = color.Value.y;
	col[2] = color.Value.z;

	return value_changed;
}

FILE* ImFileOpen(const char* filename, const char* mode)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	// We need a fopen() wrapper because MSVC/Windows fopen doesn't handle UTF-8 filenames. Converting both strings from UTF-8 to wchar format (using a single allocation, because we can)
	const int filename_wsize = ImTextCountCharsFromUtf8(filename, NULL) + 1;
	const int mode_wsize = ImTextCountCharsFromUtf8(mode, NULL) + 1;
	ImVector<ImWchar> buf;
	buf.resize(filename_wsize + mode_wsize);
	ImTextStrFromUtf8(&buf[0], filename_wsize, filename, NULL);
	ImTextStrFromUtf8(&buf[filename_wsize], mode_wsize, mode, NULL);
	return _wfopen((wchar_t*)&buf[0], (wchar_t*)&buf[filename_wsize]);
#else
	return fopen(filename, mode);
#endif
}

// Load file content into memory
// Memory allocated with ImGui::MemAlloc(), must be freed by user using ImGui::MemFree()
void* ImFileLoadToMemory(const char* filename, const char* file_open_mode, int* out_file_size, int padding_bytes)
{
	IM_ASSERT(filename && file_open_mode);
	if (out_file_size)
		*out_file_size = 0;

	FILE* f;
	if ((f = ImFileOpen(filename, file_open_mode)) == NULL)
		return NULL;

	long file_size_signed;
	if (fseek(f, 0, SEEK_END) || (file_size_signed = ftell(f)) == -1 || fseek(f, 0, SEEK_SET))
	{
		fclose(f);
		return NULL;
	}

	int file_size = (int)file_size_signed;
	void* file_data = ImGui::MemAlloc(file_size + padding_bytes);
	if (file_data == NULL)
	{
		fclose(f);
		return NULL;
	}
	if (fread(file_data, 1, (size_t)file_size, f) != (size_t)file_size)
	{
		fclose(f);
		ImGui::MemFree(file_data);
		return NULL;
	}
	if (padding_bytes > 0)
		memset((void *)(((char*)file_data) + file_size), 0, padding_bytes);

	fclose(f);
	if (out_file_size)
		*out_file_size = file_size;

	return file_data;
}

//-----------------------------------------------------------------------------
// ImGuiStorage
//-----------------------------------------------------------------------------

// Helper: Key->value storage
void ImGuiStorage::Clear()
{
	Data.clear();
}

// std::lower_bound but without the bullshit
static ImVector<ImGuiStorage::Pair>::iterator LowerBound(ImVector<ImGuiStorage::Pair>& data, ImGuiID key)
{
	ImVector<ImGuiStorage::Pair>::iterator first = data.begin();
	ImVector<ImGuiStorage::Pair>::iterator last = data.end();
	int count = (int)(last - first);
	while (count > 0)
	{
		int count2 = count / 2;
		ImVector<ImGuiStorage::Pair>::iterator mid = first + count2;
		if (mid->key < key)
		{
			first = ++mid;
			count -= count2 + 1;
		}
		else
		{
			count = count2;
		}
	}
	return first;
}

int ImGuiStorage::GetInt(ImGuiID key, int default_val) const
{
	ImVector<Pair>::iterator it = LowerBound(const_cast<ImVector<ImGuiStorage::Pair>&>(Data), key);
	if (it == Data.end() || it->key != key)
		return default_val;
	return it->val_i;
}

bool ImGuiStorage::GetBool(ImGuiID key, bool default_val) const
{
	return GetInt(key, default_val ? 1 : 0) != 0;
}

float ImGuiStorage::GetFloat(ImGuiID key, float default_val) const
{
	ImVector<Pair>::iterator it = LowerBound(const_cast<ImVector<ImGuiStorage::Pair>&>(Data), key);
	if (it == Data.end() || it->key != key)
		return default_val;
	return it->val_f;
}

void* ImGuiStorage::GetVoidPtr(ImGuiID key) const
{
	ImVector<Pair>::iterator it = LowerBound(const_cast<ImVector<ImGuiStorage::Pair>&>(Data), key);
	if (it == Data.end() || it->key != key)
		return NULL;
	return it->val_p;
}

// References are only valid until a new value is added to the storage. Calling a Set***() function or a Get***Ref() function invalidates the pointer.
int* ImGuiStorage::GetIntRef(ImGuiID key, int default_val)
{
	ImVector<Pair>::iterator it = LowerBound(Data, key);
	if (it == Data.end() || it->key != key)
		it = Data.insert(it, Pair(key, default_val));
	return &it->val_i;
}

bool* ImGuiStorage::GetBoolRef(ImGuiID key, bool default_val)
{
	return (bool*)GetIntRef(key, default_val ? 1 : 0);
}

float* ImGuiStorage::GetFloatRef(ImGuiID key, float default_val)
{
	ImVector<Pair>::iterator it = LowerBound(Data, key);
	if (it == Data.end() || it->key != key)
		it = Data.insert(it, Pair(key, default_val));
	return &it->val_f;
}

void** ImGuiStorage::GetVoidPtrRef(ImGuiID key, void* default_val)
{
	ImVector<Pair>::iterator it = LowerBound(Data, key);
	if (it == Data.end() || it->key != key)
		it = Data.insert(it, Pair(key, default_val));
	return &it->val_p;
}

// FIXME-OPT: Need a way to reuse the result of lower_bound when doing GetInt()/SetInt() - not too bad because it only happens on explicit interaction (maximum one a frame)
void ImGuiStorage::SetInt(ImGuiID key, int val)
{
	ImVector<Pair>::iterator it = LowerBound(Data, key);
	if (it == Data.end() || it->key != key)
	{
		Data.insert(it, Pair(key, val));
		return;
	}
	it->val_i = val;
}

void ImGuiStorage::SetBool(ImGuiID key, bool val)
{
	SetInt(key, val ? 1 : 0);
}

void ImGuiStorage::SetFloat(ImGuiID key, float val)
{
	ImVector<Pair>::iterator it = LowerBound(Data, key);
	if (it == Data.end() || it->key != key)
	{
		Data.insert(it, Pair(key, val));
		return;
	}
	it->val_f = val;
}

void ImGuiStorage::SetVoidPtr(ImGuiID key, void* val)
{
	ImVector<Pair>::iterator it = LowerBound(Data, key);
	if (it == Data.end() || it->key != key)
	{
		Data.insert(it, Pair(key, val));
		return;
	}
	it->val_p = val;
}

void ImGuiStorage::SetAllInt(int v)
{
	for (int i = 0; i < Data.Size; i++)
		Data[i].val_i = v;
}

//-----------------------------------------------------------------------------
// ImGuiTextFilter
//-----------------------------------------------------------------------------

// Helper: Parse and apply text filters. In format "aaaaa[,bbbb][,ccccc]"
ImGuiTextFilter::ImGuiTextFilter(const char* default_filter)
{
	if (default_filter)
	{
		ImStrncpy(InputBuf, default_filter, IM_ARRAYSIZE(InputBuf));
		Build();
	}
	else
	{
		InputBuf[0] = 0;
		CountGrep = 0;
	}
}

bool ImGuiTextFilter::Draw(const char* label, float width)
{
	if (width != 0.0f)
		ImGui::PushItemWidth(width);
	bool value_changed = ImGui::InputText(label, InputBuf, IM_ARRAYSIZE(InputBuf));
	if (width != 0.0f)
		ImGui::PopItemWidth();
	if (value_changed)
		Build();
	return value_changed;
}

void ImGuiTextFilter::TextRange::split(char separator, ImVector<TextRange>& out)
{
	out.resize(0);
	const char* wb = b;
	const char* we = wb;
	while (we < e)
	{
		if (*we == separator)
		{
			out.push_back(TextRange(wb, we));
			wb = we + 1;
		}
		we++;
	}
	if (wb != we)
		out.push_back(TextRange(wb, we));
}

void ImGuiTextFilter::Build()
{
	Filters.resize(0);
	TextRange input_range(InputBuf, InputBuf + strlen(InputBuf));
	input_range.split(',', Filters);

	CountGrep = 0;
	for (int i = 0; i != Filters.Size; i++)
	{
		Filters[i].trim_blanks();
		if (Filters[i].empty())
			continue;
		if (Filters[i].front() != '-')
			CountGrep += 1;
	}
}

bool ImGuiTextFilter::PassFilter(const char* text, const char* text_end) const
{
	if (Filters.empty())
		return true;

	if (text == NULL)
		text = "";

	for (int i = 0; i != Filters.Size; i++)
	{
		const TextRange& f = Filters[i];
		if (f.empty())
			continue;
		if (f.front() == '-')
		{
			// Subtract
			if (ImStristr(text, text_end, f.begin() + 1, f.end()) != NULL)
				return false;
		}
		else
		{
			// Grep
			if (ImStristr(text, text_end, f.begin(), f.end()) != NULL)
				return true;
		}
	}

	// Implicit * grep
	if (CountGrep == 0)
		return true;

	return false;
}

//-----------------------------------------------------------------------------
// ImGuiTextBuffer
//-----------------------------------------------------------------------------

// On some platform vsnprintf() takes va_list by reference and modifies it.
// va_copy is the 'correct' way to copy a va_list but Visual Studio prior to 2013 doesn't have it.
#ifndef va_copy
#define va_copy(dest, src) (dest = src)
#endif

// Helper: Text buffer for logging/accumulating text
void ImGuiTextBuffer::appendv(const char* fmt, va_list args)
{
	va_list args_copy;
	va_copy(args_copy, args);

	int len = vsnprintf(NULL, 0, fmt, args);         // FIXME-OPT: could do a first pass write attempt, likely successful on first pass.
	if (len <= 0)
		return;

	const int write_off = Buf.Size;
	const int needed_sz = write_off + len;
	if (write_off + len >= Buf.Capacity)
	{
		int double_capacity = Buf.Capacity * 2;
		Buf.reserve(needed_sz > double_capacity ? needed_sz : double_capacity);
	}

	Buf.resize(needed_sz);
	ImFormatStringV(&Buf[write_off] - 1, len + 1, fmt, args_copy);
}

void ImGuiTextBuffer::append(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	appendv(fmt, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// ImGuiSimpleColumns
//-----------------------------------------------------------------------------

ImGuiSimpleColumns::ImGuiSimpleColumns()
{
	Count = 0;
	Spacing = Width = NextWidth = 0.0f;
	memset(Pos, 0, sizeof(Pos));
	memset(NextWidths, 0, sizeof(NextWidths));
}

void ImGuiSimpleColumns::Update(int count, float spacing, bool clear)
{
	IM_ASSERT(Count <= IM_ARRAYSIZE(Pos));
	Count = count;
	Width = NextWidth = 0.0f;
	Spacing = spacing;
	if (clear) memset(NextWidths, 0, sizeof(NextWidths));
	for (int i = 0; i < Count; i++)
	{
		if (i > 0 && NextWidths[i] > 0.0f)
			Width += Spacing;
		Pos[i] = (float)(int)Width;
		Width += NextWidths[i];
		NextWidths[i] = 0.0f;
	}
}

float ImGuiSimpleColumns::DeclColumns(float w0, float w1, float w2) // not using va_arg because they promote float to double
{
	NextWidth = 0.0f;
	NextWidths[0] = ImMax(NextWidths[0], w0);
	NextWidths[1] = ImMax(NextWidths[1], w1);
	NextWidths[2] = ImMax(NextWidths[2], w2);
	for (int i = 0; i < 3; i++)
		NextWidth += NextWidths[i] + ((i > 0 && NextWidths[i] > 0.0f) ? Spacing : 0.0f);
	return ImMax(Width, NextWidth);
}

float ImGuiSimpleColumns::CalcExtraSpace(float avail_w)
{
	return ImMax(0.0f, avail_w - Width);
}

//-----------------------------------------------------------------------------
// ImGuiListClipper
//-----------------------------------------------------------------------------

static void SetCursorPosYAndSetupDummyPrevLine(float pos_y, float line_height)
{
	// Set cursor position and a few other things so that SetScrollHere() and Columns() can work when seeking cursor. 
	// FIXME: It is problematic that we have to do that here, because custom/equivalent end-user code would stumble on the same issue. Consider moving within SetCursorXXX functions?
	ImGui::SetCursorPosY(pos_y);
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DC.CursorPosPrevLine.y = window->DC.CursorPos.y - line_height;      // Setting those fields so that SetScrollHere() can properly function after the end of our clipper usage.
	window->DC.PrevLineHeight = (line_height - GImGui->Style.ItemSpacing.y);    // If we end up needing more accurate data (to e.g. use SameLine) we may as well make the clipper have a fourth step to let user process and display the last item in their list.
	if (window->DC.ColumnsCount > 1)
		window->DC.ColumnsCellMinY = window->DC.CursorPos.y;                    // Setting this so that cell Y position are set properly
}

// Use case A: Begin() called from constructor with items_height<0, then called again from Sync() in StepNo 1
// Use case B: Begin() called from constructor with items_height>0
// FIXME-LEGACY: Ideally we should remove the Begin/End functions but they are part of the legacy API we still support. This is why some of the code in Step() calling Begin() and reassign some fields, spaghetti style.
void ImGuiListClipper::Begin(int count, float items_height)
{
	StartPosY = ImGui::GetCursorPosY();
	ItemsHeight = items_height;
	ItemsCount = count;
	StepNo = 0;
	DisplayEnd = DisplayStart = -1;
	if (ItemsHeight > 0.0f)
	{
		ImGui::CalcListClipping(ItemsCount, ItemsHeight, &DisplayStart, &DisplayEnd); // calculate how many to clip/display
		if (DisplayStart > 0)
			SetCursorPosYAndSetupDummyPrevLine(StartPosY + DisplayStart * ItemsHeight, ItemsHeight); // advance cursor
		StepNo = 2;
	}
}

void ImGuiListClipper::End()
{
	if (ItemsCount < 0)
		return;
	// In theory here we should assert that ImGui::GetCursorPosY() == StartPosY + DisplayEnd * ItemsHeight, but it feels saner to just seek at the end and not assert/crash the user.
	if (ItemsCount < INT_MAX)
		SetCursorPosYAndSetupDummyPrevLine(StartPosY + ItemsCount * ItemsHeight, ItemsHeight); // advance cursor
	ItemsCount = -1;
	StepNo = 3;
}

bool ImGuiListClipper::Step()
{
	if (ItemsCount == 0 || ImGui::GetCurrentWindowRead()->SkipItems)
	{
		ItemsCount = -1;
		return false;
	}
	if (StepNo == 0) // Step 0: the clipper let you process the first element, regardless of it being visible or not, so we can measure the element height.
	{
		DisplayStart = 0;
		DisplayEnd = 1;
		StartPosY = ImGui::GetCursorPosY();
		StepNo = 1;
		return true;
	}
	if (StepNo == 1) // Step 1: the clipper infer height from first element, calculate the actual range of elements to display, and position the cursor before the first element.
	{
		if (ItemsCount == 1) { ItemsCount = -1; return false; }
		float items_height = ImGui::GetCursorPosY() - StartPosY;
		IM_ASSERT(items_height > 0.0f);   // If this triggers, it means Item 0 hasn't moved the cursor vertically
		Begin(ItemsCount - 1, items_height);
		DisplayStart++;
		DisplayEnd++;
		StepNo = 3;
		return true;
	}
	if (StepNo == 2) // Step 2: dummy step only required if an explicit items_height was passed to constructor or Begin() and user still call Step(). Does nothing and switch to Step 3.
	{
		IM_ASSERT(DisplayStart >= 0 && DisplayEnd >= 0);
		StepNo = 3;
		return true;
	}
	if (StepNo == 3) // Step 3: the clipper validate that we have reached the expected Y position (corresponding to element DisplayEnd), advance the cursor to the end of the list and then returns 'false' to end the loop.
		End();
	return false;
}

//-----------------------------------------------------------------------------
// ImGuiWindow
//-----------------------------------------------------------------------------

ImGuiWindow::ImGuiWindow(const char* name)
{
	Name = ImStrdup(name);
	ID = ImHash(name, 0);
	IDStack.push_back(ID);
	MoveId = GetID("#MOVE");

	Flags = 0;
	OrderWithinParent = 0;
	PosFloat = Pos = ImVec2(0.0f, 0.0f);
	Size = SizeFull = ImVec2(0.0f, 0.0f);
	SizeContents = SizeContentsExplicit = ImVec2(0.0f, 0.0f);
	WindowPadding = ImVec2(0.0f, 0.0f);
	Scroll = ImVec2(0.0f, 0.0f);
	ScrollTarget = ImVec2(FLT_MAX, FLT_MAX);
	ScrollTargetCenterRatio = ImVec2(0.5f, 0.5f);
	ScrollbarX = ScrollbarY = false;
	ScrollbarSizes = ImVec2(0.0f, 0.0f);
	BorderSize = 0.0f;
	Active = WasActive = false;
	Accessed = false;
	Collapsed = false;
	SkipItems = false;
	BeginCount = 0;
	PopupId = 0;
	AutoFitFramesX = AutoFitFramesY = -1;
	AutoFitOnlyGrows = false;
	AutoPosLastDirection = -1;
	HiddenFrames = 0;
	SetWindowPosAllowFlags = SetWindowSizeAllowFlags = SetWindowCollapsedAllowFlags = ImGuiSetCond_Always | ImGuiSetCond_Once | ImGuiSetCond_FirstUseEver | ImGuiSetCond_Appearing;
	SetWindowPosCenterWanted = false;

	LastFrameActive = -1;
	ItemWidthDefault = 0.0f;
	FontWindowScale = 1.0f;

	DrawList = (ImDrawList*)ImGui::MemAlloc(sizeof(ImDrawList));
	IM_PLACEMENT_NEW(DrawList) ImDrawList();
	DrawList->_OwnerName = Name;
	RootWindow = NULL;
	RootNonPopupWindow = NULL;
	ParentWindow = NULL;

	FocusIdxAllCounter = FocusIdxTabCounter = -1;
	FocusIdxAllRequestCurrent = FocusIdxTabRequestCurrent = INT_MAX;
	FocusIdxAllRequestNext = FocusIdxTabRequestNext = INT_MAX;
}

ImGuiWindow::~ImGuiWindow()
{
	DrawList->~ImDrawList();
	ImGui::MemFree(DrawList);
	DrawList = NULL;
	ImGui::MemFree(Name);
	Name = NULL;
}

ImGuiID ImGuiWindow::GetID(const char* str, const char* str_end)
{
	ImGuiID seed = IDStack.back();
	ImGuiID id = ImHash(str, str_end ? (int)(str_end - str) : 0, seed);
	ImGui::KeepAliveID(id);
	return id;
}

ImGuiID ImGuiWindow::GetID(const void* ptr)
{
	ImGuiID seed = IDStack.back();
	ImGuiID id = ImHash(&ptr, sizeof(void*), seed);
	ImGui::KeepAliveID(id);
	return id;
}

ImGuiID ImGuiWindow::GetIDNoKeepAlive(const char* str, const char* str_end)
{
	ImGuiID seed = IDStack.back();
	return ImHash(str, str_end ? (int)(str_end - str) : 0, seed);
}

//-----------------------------------------------------------------------------
// Internal API exposed in imgui_internal.h
//-----------------------------------------------------------------------------

static void SetCurrentWindow(ImGuiWindow* window)
{
	ImGuiContext& g = *GImGui;
	g.CurrentWindow = window;
	if (window)
		g.FontSize = window->CalcFontSize();
}

ImGuiWindow* ImGui::GetParentWindow()
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(g.CurrentWindowStack.Size >= 2);
	return g.CurrentWindowStack[(unsigned int)g.CurrentWindowStack.Size - 2];
}

void ImGui::SetActiveID(ImGuiID id, ImGuiWindow* window)
{
	ImGuiContext& g = *GImGui;
	g.ActiveId = id;
	g.ActiveIdAllowOverlap = false;
	g.ActiveIdIsJustActivated = true;
	if (id)
		g.ActiveIdIsAlive = true;
	g.ActiveIdWindow = window;
}

void ImGui::ClearActiveID()
{
	SetActiveID(0, NULL);
}

void ImGui::SetHoveredID(ImGuiID id)
{
	ImGuiContext& g = *GImGui;
	g.HoveredId = id;
	g.HoveredIdAllowOverlap = false;
}

void ImGui::KeepAliveID(ImGuiID id)
{
	ImGuiContext& g = *GImGui;
	if (g.ActiveId == id)
		g.ActiveIdIsAlive = true;
}

// Advance cursor given item size for layout.
void ImGui::ItemSize(const ImVec2& size, float text_offset_y)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	// Always align ourselves on pixel boundaries
	ImGuiContext& g = *GImGui;
	const float line_height = ImMax(window->DC.CurrentLineHeight, size.y);
	const float text_base_offset = ImMax(window->DC.CurrentLineTextBaseOffset, text_offset_y);
	window->DC.CursorPosPrevLine = ImVec2(window->DC.CursorPos.x + size.x, window->DC.CursorPos.y);
	window->DC.CursorPos = ImVec2((float)(int)(window->Pos.x + window->DC.IndentX + window->DC.ColumnsOffsetX), (float)(int)(window->DC.CursorPos.y + line_height + g.Style.ItemSpacing.y));
	window->DC.CursorMaxPos.x = ImMax(window->DC.CursorMaxPos.x, window->DC.CursorPosPrevLine.x);
	window->DC.CursorMaxPos.y = ImMax(window->DC.CursorMaxPos.y, window->DC.CursorPos.y);

	//window->DrawList->AddCircle(window->DC.CursorMaxPos, 3.0f, IM_COL32(255,0,0,255), 4); // Debug

	window->DC.PrevLineHeight = line_height;
	window->DC.PrevLineTextBaseOffset = text_base_offset;
	window->DC.CurrentLineHeight = window->DC.CurrentLineTextBaseOffset = 0.0f;
}

void ImGui::ItemSize(const ImRect& bb, float text_offset_y)
{
	ItemSize(bb.GetSize(), text_offset_y);
}

// Declare item bounding box for clipping and interaction.
// Note that the size can be different than the one provided to ItemSize(). Typically, widgets that spread over available surface
// declares their minimum size requirement to ItemSize() and then use a larger region for drawing/interaction, which is passed to ItemAdd().
bool ImGui::ItemAdd(const ImRect& bb, const ImGuiID* id)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.LastItemId = id ? *id : 0;
	window->DC.LastItemRect = bb;
	window->DC.LastItemHoveredAndUsable = window->DC.LastItemHoveredRect = false;
	if (IsClippedEx(bb, id, false))
		return false;

	// This is a sensible default, but widgets are free to override it after calling ItemAdd()
	ImGuiContext& g = *GImGui;
	if (IsMouseHoveringRect(bb.Min, bb.Max))
	{
		// Matching the behavior of IsHovered() but allow if ActiveId==window->MoveID (we clicked on the window background)
		// So that clicking on items with no active id such as Text() still returns true with IsItemHovered()
		window->DC.LastItemHoveredRect = true;
		if (g.HoveredRootWindow == window->RootWindow)
			if (g.ActiveId == 0 || (id && g.ActiveId == *id) || g.ActiveIdAllowOverlap || (g.ActiveId == window->MoveId))
				if (IsWindowContentHoverable(window))
					window->DC.LastItemHoveredAndUsable = true;
	}

	return true;
}

bool ImGui::IsClippedEx(const ImRect& bb, const ImGuiID* id, bool clip_even_when_logged)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindowRead();

	if (!bb.Overlaps(window->ClipRect))
		if (!id || *id != GImGui->ActiveId)
			if (clip_even_when_logged || !g.LogEnabled)
				return true;
	return false;
}

// NB: This is an internal helper. The user-facing IsItemHovered() is using data emitted from ItemAdd(), with a slightly different logic.
bool ImGui::IsHovered(const ImRect& bb, ImGuiID id, bool flatten_childs)
{
	ImGuiContext& g = *GImGui;
	if (g.HoveredId == 0 || g.HoveredId == id || g.HoveredIdAllowOverlap)
	{
		ImGuiWindow* window = GetCurrentWindowRead();
		if (g.HoveredWindow == window || (flatten_childs && g.HoveredRootWindow == window->RootWindow))
			if ((g.ActiveId == 0 || g.ActiveId == id || g.ActiveIdAllowOverlap) && IsMouseHoveringRect(bb.Min, bb.Max))
				if (IsWindowContentHoverable(g.HoveredRootWindow))
					return true;
	}
	return false;
}

bool ImGui::FocusableItemRegister(ImGuiWindow* window, bool is_active, bool tab_stop)
{
	ImGuiContext& g = *GImGui;

	const bool allow_keyboard_focus = window->DC.AllowKeyboardFocus;
	window->FocusIdxAllCounter++;
	if (allow_keyboard_focus)
		window->FocusIdxTabCounter++;

	// Process keyboard input at this point: TAB, Shift-TAB switch focus
	// We can always TAB out of a widget that doesn't allow tabbing in.
	if (tab_stop && window->FocusIdxAllRequestNext == INT_MAX && window->FocusIdxTabRequestNext == INT_MAX && is_active && IsKeyPressedMap(ImGuiKey_Tab))
	{
		// Modulo on index will be applied at the end of frame once we've got the total counter of items.
		window->FocusIdxTabRequestNext = window->FocusIdxTabCounter + (g.IO.KeyShift ? (allow_keyboard_focus ? -1 : 0) : +1);
	}

	if (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent)
		return true;

	if (allow_keyboard_focus)
		if (window->FocusIdxTabCounter == window->FocusIdxTabRequestCurrent)
			return true;

	return false;
}

void ImGui::FocusableItemUnregister(ImGuiWindow* window)
{
	window->FocusIdxAllCounter--;
	window->FocusIdxTabCounter--;
}

ImVec2 ImGui::CalcItemSize(ImVec2 size, float default_x, float default_y)
{
	ImGuiContext& g = *GImGui;
	ImVec2 content_max;
	if (size.x < 0.0f || size.y < 0.0f)
		content_max = g.CurrentWindow->Pos + GetContentRegionMax();
	if (size.x <= 0.0f)
		size.x = (size.x == 0.0f) ? default_x : ImMax(content_max.x - g.CurrentWindow->DC.CursorPos.x, 4.0f) + size.x;
	if (size.y <= 0.0f)
		size.y = (size.y == 0.0f) ? default_y : ImMax(content_max.y - g.CurrentWindow->DC.CursorPos.y, 4.0f) + size.y;
	return size;
}

float ImGui::CalcWrapWidthForPos(const ImVec2& pos, float wrap_pos_x)
{
	if (wrap_pos_x < 0.0f)
		return 0.0f;

	ImGuiWindow* window = GetCurrentWindowRead();
	if (wrap_pos_x == 0.0f)
		wrap_pos_x = GetContentRegionMax().x + window->Pos.x;
	else if (wrap_pos_x > 0.0f)
		wrap_pos_x += window->Pos.x - window->Scroll.x; // wrap_pos_x is provided is window local space

	return ImMax(wrap_pos_x - pos.x, 1.0f);
}

//-----------------------------------------------------------------------------

void* ImGui::MemAlloc(size_t sz)
{
	GImGui->IO.MetricsAllocs++;
	return GImGui->IO.MemAllocFn(sz);
}

void ImGui::MemFree(void* ptr)
{
	if (ptr) GImGui->IO.MetricsAllocs--;
	return GImGui->IO.MemFreeFn(ptr);
}

const char* ImGui::GetClipboardText()
{
	return GImGui->IO.GetClipboardTextFn ? GImGui->IO.GetClipboardTextFn(GImGui->IO.ClipboardUserData) : "";
}

void ImGui::SetClipboardText(const char* text)
{
	if (GImGui->IO.SetClipboardTextFn)
		GImGui->IO.SetClipboardTextFn(GImGui->IO.ClipboardUserData, text);
}

const char* ImGui::GetVersion()
{
	return IMGUI_VERSION;
}

// Internal state access - if you want to share ImGui state between modules (e.g. DLL) or allocate it yourself
// Note that we still point to some static data and members (such as GFontAtlas), so the state instance you end up using will point to the static data within its module
ImGuiContext* ImGui::GetCurrentContext()
{
	return GImGui;
}

void ImGui::SetCurrentContext(ImGuiContext* ctx)
{
#ifdef IMGUI_SET_CURRENT_CONTEXT_FUNC
	IMGUI_SET_CURRENT_CONTEXT_FUNC(ctx); // For custom thread-based hackery you may want to have control over this.
#else
	GImGui = ctx;
#endif
}

ImGuiContext* ImGui::CreateContext(void* (*malloc_fn)(size_t), void(*free_fn)(void*))
{
	if (!malloc_fn) malloc_fn = malloc;
	ImGuiContext* ctx = (ImGuiContext*)malloc_fn(sizeof(ImGuiContext));
	IM_PLACEMENT_NEW(ctx) ImGuiContext();
	ctx->IO.MemAllocFn = malloc_fn;
	ctx->IO.MemFreeFn = free_fn ? free_fn : free;
	return ctx;
}

void ImGui::DestroyContext(ImGuiContext* ctx)
{
	void(*free_fn)(void*) = ctx->IO.MemFreeFn;
	ctx->~ImGuiContext();
	free_fn(ctx);
	if (GImGui == ctx)
		SetCurrentContext(NULL);
}

ImGuiIO& ImGui::GetIO()
{
	return GImGui->IO;
}

ImGuiStyle& ImGui::GetStyle()
{
	return GImGui->Style;
}

// Same value as passed to your RenderDrawListsFn() function. valid after Render() and until the next call to NewFrame()
ImDrawData* ImGui::GetDrawData()
{
	return GImGui->RenderDrawData.Valid ? &GImGui->RenderDrawData : NULL;
}

float ImGui::GetTime()
{
	return GImGui->Time;
}

int ImGui::GetFrameCount()
{
	return GImGui->FrameCount;
}

void ImGui::NewFrame()
{
	ImGuiContext& g = *GImGui;

	// Check user data
	IM_ASSERT(g.IO.DeltaTime >= 0.0f);               // Need a positive DeltaTime (zero is tolerated but will cause some timing issues)
	IM_ASSERT(g.IO.DisplaySize.x >= 0.0f && g.IO.DisplaySize.y >= 0.0f);
	IM_ASSERT(g.IO.Fonts->Fonts.Size > 0);           // Font Atlas not created. Did you call io.Fonts->GetTexDataAsRGBA32 / GetTexDataAsAlpha8 ?
	IM_ASSERT(g.IO.Fonts->Fonts[0]->IsLoaded());     // Font Atlas not created. Did you call io.Fonts->GetTexDataAsRGBA32 / GetTexDataAsAlpha8 ?
	IM_ASSERT(g.Style.CurveTessellationTol > 0.0f);  // Invalid style setting

	if (!g.Initialized)
	{
		// Initialize on first frame
		g.LogClipboard = (ImGuiTextBuffer*)ImGui::MemAlloc(sizeof(ImGuiTextBuffer));
		IM_PLACEMENT_NEW(g.LogClipboard) ImGuiTextBuffer();

		IM_ASSERT(g.Settings.empty());
		LoadIniSettingsFromDisk(g.IO.IniFilename);
		g.Initialized = true;
	}

	SetCurrentFont(GetDefaultFont());
	IM_ASSERT(g.Font->IsLoaded());

	g.Time += g.IO.DeltaTime;
	g.FrameCount += 1;
	g.TooltipOverrideCount = 0;
	g.OverlayDrawList.Clear();
	g.OverlayDrawList.PushTextureID(g.IO.Fonts->TexID);
	g.OverlayDrawList.PushClipRectFullScreen();

	// Mark rendering data as invalid to prevent user who may have a handle on it to use it
	g.RenderDrawData.Valid = false;
	g.RenderDrawData.CmdLists = NULL;
	g.RenderDrawData.CmdListsCount = g.RenderDrawData.TotalVtxCount = g.RenderDrawData.TotalIdxCount = 0;

	// Update inputs state
	if (g.IO.MousePos.x < 0 && g.IO.MousePos.y < 0)
		g.IO.MousePos = ImVec2(-9999.0f, -9999.0f);
	if ((g.IO.MousePos.x < 0 && g.IO.MousePos.y < 0) || (g.IO.MousePosPrev.x < 0 && g.IO.MousePosPrev.y < 0))   // if mouse just appeared or disappeared (negative coordinate) we cancel out movement in MouseDelta
		g.IO.MouseDelta = ImVec2(0.0f, 0.0f);
	else
		g.IO.MouseDelta = g.IO.MousePos - g.IO.MousePosPrev;
	g.IO.MousePosPrev = g.IO.MousePos;
	for (int i = 0; i < IM_ARRAYSIZE(g.IO.MouseDown); i++)
	{
		g.IO.MouseClicked[i] = g.IO.MouseDown[i] && g.IO.MouseDownDuration[i] < 0.0f;
		g.IO.MouseReleased[i] = !g.IO.MouseDown[i] && g.IO.MouseDownDuration[i] >= 0.0f;
		g.IO.MouseDownDurationPrev[i] = g.IO.MouseDownDuration[i];
		g.IO.MouseDownDuration[i] = g.IO.MouseDown[i] ? (g.IO.MouseDownDuration[i] < 0.0f ? 0.0f : g.IO.MouseDownDuration[i] + g.IO.DeltaTime) : -1.0f;
		g.IO.MouseDoubleClicked[i] = false;
		if (g.IO.MouseClicked[i])
		{
			if (g.Time - g.IO.MouseClickedTime[i] < g.IO.MouseDoubleClickTime)
			{
				if (ImLengthSqr(g.IO.MousePos - g.IO.MouseClickedPos[i]) < g.IO.MouseDoubleClickMaxDist * g.IO.MouseDoubleClickMaxDist)
					g.IO.MouseDoubleClicked[i] = true;
				g.IO.MouseClickedTime[i] = -FLT_MAX;    // so the third click isn't turned into a double-click
			}
			else
			{
				g.IO.MouseClickedTime[i] = g.Time;
			}
			g.IO.MouseClickedPos[i] = g.IO.MousePos;
			g.IO.MouseDragMaxDistanceSqr[i] = 0.0f;
		}
		else if (g.IO.MouseDown[i])
		{
			g.IO.MouseDragMaxDistanceSqr[i] = ImMax(g.IO.MouseDragMaxDistanceSqr[i], ImLengthSqr(g.IO.MousePos - g.IO.MouseClickedPos[i]));
		}
	}
	memcpy(g.IO.KeysDownDurationPrev, g.IO.KeysDownDuration, sizeof(g.IO.KeysDownDuration));
	for (int i = 0; i < IM_ARRAYSIZE(g.IO.KeysDown); i++)
		g.IO.KeysDownDuration[i] = g.IO.KeysDown[i] ? (g.IO.KeysDownDuration[i] < 0.0f ? 0.0f : g.IO.KeysDownDuration[i] + g.IO.DeltaTime) : -1.0f;

	// Calculate frame-rate for the user, as a purely luxurious feature
	g.FramerateSecPerFrameAccum += g.IO.DeltaTime - g.FramerateSecPerFrame[g.FramerateSecPerFrameIdx];
	g.FramerateSecPerFrame[g.FramerateSecPerFrameIdx] = g.IO.DeltaTime;
	g.FramerateSecPerFrameIdx = (g.FramerateSecPerFrameIdx + 1) % IM_ARRAYSIZE(g.FramerateSecPerFrame);
	g.IO.Framerate = 1.0f / (g.FramerateSecPerFrameAccum / (float)IM_ARRAYSIZE(g.FramerateSecPerFrame));

	// Clear reference to active widget if the widget isn't alive anymore
	g.HoveredIdPreviousFrame = g.HoveredId;
	g.HoveredId = 0;
	g.HoveredIdAllowOverlap = false;
	if (!g.ActiveIdIsAlive && g.ActiveIdPreviousFrame == g.ActiveId && g.ActiveId != 0)
		ClearActiveID();
	g.ActiveIdPreviousFrame = g.ActiveId;
	g.ActiveIdIsAlive = false;
	g.ActiveIdIsJustActivated = false;

	// Handle user moving window (at the beginning of the frame to avoid input lag or sheering). Only valid for root windows.
	if (g.MovedWindowMoveId && g.MovedWindowMoveId == g.ActiveId)
	{
		KeepAliveID(g.MovedWindowMoveId);
		IM_ASSERT(g.MovedWindow && g.MovedWindow->RootWindow);
		IM_ASSERT(g.MovedWindow->RootWindow->MoveId == g.MovedWindowMoveId);
		if (g.IO.MouseDown[0])
		{
			if (!(g.MovedWindow->Flags & ImGuiWindowFlags_NoMove))
			{
				g.MovedWindow->PosFloat += g.IO.MouseDelta;
				if (!(g.MovedWindow->Flags & ImGuiWindowFlags_NoSavedSettings) && (g.IO.MouseDelta.x != 0.0f || g.IO.MouseDelta.y != 0.0f))
					MarkIniSettingsDirty();
			}
			FocusWindow(g.MovedWindow);
		}
		else
		{
			ClearActiveID();
			g.MovedWindow = NULL;
			g.MovedWindowMoveId = 0;
		}
	}
	else
	{
		g.MovedWindow = NULL;
		g.MovedWindowMoveId = 0;
	}

	// Delay saving settings so we don't spam disk too much
	if (g.SettingsDirtyTimer > 0.0f)
	{
		g.SettingsDirtyTimer -= g.IO.DeltaTime;
		if (g.SettingsDirtyTimer <= 0.0f)
			SaveIniSettingsToDisk(g.IO.IniFilename);
	}

	// Find the window we are hovering. Child windows can extend beyond the limit of their parent so we need to derive HoveredRootWindow from HoveredWindow
	g.HoveredWindow = g.MovedWindow ? g.MovedWindow : FindHoveredWindow(g.IO.MousePos, false);
	if (g.HoveredWindow && (g.HoveredWindow->Flags & ImGuiWindowFlags_ChildWindow))
		g.HoveredRootWindow = g.HoveredWindow->RootWindow;
	else
		g.HoveredRootWindow = g.MovedWindow ? g.MovedWindow->RootWindow : FindHoveredWindow(g.IO.MousePos, true);

	if (ImGuiWindow* modal_window = GetFrontMostModalRootWindow())
	{
		g.ModalWindowDarkeningRatio = ImMin(g.ModalWindowDarkeningRatio + g.IO.DeltaTime * 6.0f, 1.0f);
		ImGuiWindow* window = g.HoveredRootWindow;
		while (window && window != modal_window)
			window = window->ParentWindow;
		if (!window)
			g.HoveredRootWindow = g.HoveredWindow = NULL;
	}
	else
	{
		g.ModalWindowDarkeningRatio = 0.0f;
	}

	// Are we using inputs? Tell user so they can capture/discard the inputs away from the rest of their application.
	// When clicking outside of a window we assume the click is owned by the application and won't request capture. We need to track click ownership.
	int mouse_earliest_button_down = -1;
	bool mouse_any_down = false;
	for (int i = 0; i < IM_ARRAYSIZE(g.IO.MouseDown); i++)
	{
		if (g.IO.MouseClicked[i])
			g.IO.MouseDownOwned[i] = (g.HoveredWindow != NULL) || (!g.OpenPopupStack.empty());
		mouse_any_down |= g.IO.MouseDown[i];
		if (g.IO.MouseDown[i])
			if (mouse_earliest_button_down == -1 || g.IO.MouseClickedTime[mouse_earliest_button_down] > g.IO.MouseClickedTime[i])
				mouse_earliest_button_down = i;
	}
	bool mouse_avail_to_imgui = (mouse_earliest_button_down == -1) || g.IO.MouseDownOwned[mouse_earliest_button_down];
	if (g.CaptureMouseNextFrame != -1)
		g.IO.WantCaptureMouse = (g.CaptureMouseNextFrame != 0);
	else
		g.IO.WantCaptureMouse = (mouse_avail_to_imgui && (g.HoveredWindow != NULL || mouse_any_down)) || (g.ActiveId != 0) || (!g.OpenPopupStack.empty());
	g.IO.WantCaptureKeyboard = (g.CaptureKeyboardNextFrame != -1) ? (g.CaptureKeyboardNextFrame != 0) : (g.ActiveId != 0);
	g.IO.WantTextInput = (g.ActiveId != 0 && g.InputTextState.Id == g.ActiveId);
	g.MouseCursor = ImGuiMouseCursor_Arrow;
	g.CaptureMouseNextFrame = g.CaptureKeyboardNextFrame = -1;
	g.OsImePosRequest = ImVec2(1.0f, 1.0f); // OS Input Method Editor showing on top-left of our window by default

											// If mouse was first clicked outside of ImGui bounds we also cancel out hovering.
	if (!mouse_avail_to_imgui)
		g.HoveredWindow = g.HoveredRootWindow = NULL;

	// Scale & Scrolling
	if (g.HoveredWindow && g.IO.MouseWheel != 0.0f && !g.HoveredWindow->Collapsed)
	{
		ImGuiWindow* window = g.HoveredWindow;
		if (g.IO.KeyCtrl)
		{
			if (g.IO.FontAllowUserScaling)
			{
				// Zoom / Scale window
				float new_font_scale = ImClamp(window->FontWindowScale + g.IO.MouseWheel * 0.10f, 0.50f, 2.50f);
				float scale = new_font_scale / window->FontWindowScale;
				window->FontWindowScale = new_font_scale;

				const ImVec2 offset = window->Size * (1.0f - scale) * (g.IO.MousePos - window->Pos) / window->Size;
				window->Pos += offset;
				window->PosFloat += offset;
				window->Size *= scale;
				window->SizeFull *= scale;
			}
		}
		else if (!(window->Flags & ImGuiWindowFlags_NoScrollWithMouse))
		{
			// Scroll
			const int scroll_lines = (window->Flags & ImGuiWindowFlags_ComboBox) ? 3 : 5;
			SetWindowScrollY(window, window->Scroll.y - g.IO.MouseWheel * window->CalcFontSize() * scroll_lines);
		}
	}

	// Pressing TAB activate widget focus
	// NB: Don't discard FocusedWindow if it isn't active, so that a window that go on/off programatically won't lose its keyboard focus.
	if (g.ActiveId == 0 && g.FocusedWindow != NULL && g.FocusedWindow->Active && IsKeyPressedMap(ImGuiKey_Tab, false))
		g.FocusedWindow->FocusIdxTabRequestNext = 0;

	// Mark all windows as not visible
	for (int i = 0; i != g.Windows.Size; i++)
	{
		ImGuiWindow* window = g.Windows[i];
		window->WasActive = window->Active;
		window->Active = false;
		window->Accessed = false;
	}

	// Closing the focused window restore focus to the first active root window in descending z-order
	if (g.FocusedWindow && !g.FocusedWindow->WasActive)
		for (int i = g.Windows.Size - 1; i >= 0; i--)
			if (g.Windows[i]->WasActive && !(g.Windows[i]->Flags & ImGuiWindowFlags_ChildWindow))
			{
				FocusWindow(g.Windows[i]);
				break;
			}

	// No window should be open at the beginning of the frame.
	// But in order to allow the user to call NewFrame() multiple times without calling Render(), we are doing an explicit clear.
	g.CurrentWindowStack.resize(0);
	g.CurrentPopupStack.resize(0);
	CloseInactivePopups();

	// Create implicit window - we will only render it if the user has added something to it.
	ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Debug");
}

// NB: behavior of ImGui after Shutdown() is not tested/guaranteed at the moment. This function is merely here to free heap allocations.
void ImGui::Shutdown()
{
	ImGuiContext& g = *GImGui;

	// The fonts atlas can be used prior to calling NewFrame(), so we clear it even if g.Initialized is FALSE (which would happen if we never called NewFrame)
	if (g.IO.Fonts) // Testing for NULL to allow user to NULLify in case of running Shutdown() on multiple contexts. Bit hacky.
		g.IO.Fonts->Clear();

	// Cleanup of other data are conditional on actually having used ImGui.
	if (!g.Initialized)
		return;

	SaveIniSettingsToDisk(g.IO.IniFilename);

	for (int i = 0; i < g.Windows.Size; i++)
	{
		g.Windows[i]->~ImGuiWindow();
		ImGui::MemFree(g.Windows[i]);
	}
	g.Windows.clear();
	g.WindowsSortBuffer.clear();
	g.CurrentWindow = NULL;
	g.CurrentWindowStack.clear();
	g.FocusedWindow = NULL;
	g.HoveredWindow = NULL;
	g.HoveredRootWindow = NULL;
	g.ActiveIdWindow = NULL;
	g.MovedWindow = NULL;
	for (int i = 0; i < g.Settings.Size; i++)
		ImGui::MemFree(g.Settings[i].Name);
	g.Settings.clear();
	g.ColorModifiers.clear();
	g.StyleModifiers.clear();
	g.FontStack.clear();
	g.OpenPopupStack.clear();
	g.CurrentPopupStack.clear();
	g.SetNextWindowSizeConstraintCallback = NULL;
	g.SetNextWindowSizeConstraintCallbackUserData = NULL;
	for (int i = 0; i < IM_ARRAYSIZE(g.RenderDrawLists); i++)
		g.RenderDrawLists[i].clear();
	g.OverlayDrawList.ClearFreeMemory();
	g.ColorEditModeStorage.Clear();
	if (g.PrivateClipboard)
	{
		ImGui::MemFree(g.PrivateClipboard);
		g.PrivateClipboard = NULL;
	}
	g.InputTextState.Text.clear();
	g.InputTextState.InitialText.clear();
	g.InputTextState.TempTextBuffer.clear();

	if (g.LogFile && g.LogFile != stdout)
	{
		fclose(g.LogFile);
		g.LogFile = NULL;
	}
	if (g.LogClipboard)
	{
		g.LogClipboard->~ImGuiTextBuffer();
		ImGui::MemFree(g.LogClipboard);
	}

	g.Initialized = false;
}

static ImGuiIniData* FindWindowSettings(const char* name)
{
	ImGuiContext& g = *GImGui;
	ImGuiID id = ImHash(name, 0);
	for (int i = 0; i != g.Settings.Size; i++)
	{
		ImGuiIniData* ini = &g.Settings[i];
		if (ini->Id == id)
			return ini;
	}
	return NULL;
}

static ImGuiIniData* AddWindowSettings(const char* name)
{
	GImGui->Settings.resize(GImGui->Settings.Size + 1);
	ImGuiIniData* ini = &GImGui->Settings.back();
	ini->Name = ImStrdup(name);
	ini->Id = ImHash(name, 0);
	ini->Collapsed = false;
	ini->Pos = ImVec2(FLT_MAX, FLT_MAX);
	ini->Size = ImVec2(0, 0);
	return ini;
}

// Zero-tolerance, poor-man .ini parsing
// FIXME: Write something less rubbish
static void LoadIniSettingsFromDisk(const char* ini_filename)
{
	ImGuiContext& g = *GImGui;
	if (!ini_filename)
		return;

	int file_size;
	char* file_data = (char*)ImFileLoadToMemory(ini_filename, "rb", &file_size, 1);
	if (!file_data)
		return;

	ImGuiIniData* settings = NULL;
	const char* buf_end = file_data + file_size;
	for (const char* line_start = file_data; line_start < buf_end; )
	{
		const char* line_end = line_start;
		while (line_end < buf_end && *line_end != '\n' && *line_end != '\r')
			line_end++;

		if (line_start[0] == '[' && line_end > line_start && line_end[-1] == ']')
		{
			char name[64];
			ImFormatString(name, IM_ARRAYSIZE(name), "%.*s", (int)(line_end - line_start - 2), line_start + 1);
			settings = FindWindowSettings(name);
			if (!settings)
				settings = AddWindowSettings(name);
		}
		else if (settings)
		{
			float x, y;
			int i;
			if (sscanf(line_start, "Pos=%f,%f", &x, &y) == 2)
				settings->Pos = ImVec2(x, y);
			else if (sscanf(line_start, "Size=%f,%f", &x, &y) == 2)
				settings->Size = ImMax(ImVec2(x, y), g.Style.WindowMinSize);
			else if (sscanf(line_start, "Collapsed=%d", &i) == 1)
				settings->Collapsed = (i != 0);
		}

		line_start = line_end + 1;
	}

	ImGui::MemFree(file_data);
}

static void SaveIniSettingsToDisk(const char* ini_filename)
{
	ImGuiContext& g = *GImGui;
	g.SettingsDirtyTimer = 0.0f;
	if (!ini_filename)
		return;

	// Gather data from windows that were active during this session
	for (int i = 0; i != g.Windows.Size; i++)
	{
		ImGuiWindow* window = g.Windows[i];
		if (window->Flags & ImGuiWindowFlags_NoSavedSettings)
			continue;
		ImGuiIniData* settings = FindWindowSettings(window->Name);
		settings->Pos = window->Pos;
		settings->Size = window->SizeFull;
		settings->Collapsed = window->Collapsed;
	}

	// Write .ini file
	// If a window wasn't opened in this session we preserve its settings
	FILE* f = ImFileOpen(ini_filename, "wt");
	if (!f)
		return;
	for (int i = 0; i != g.Settings.Size; i++)
	{
		const ImGuiIniData* settings = &g.Settings[i];
		if (settings->Pos.x == FLT_MAX)
			continue;
		const char* name = settings->Name;
		if (const char* p = strstr(name, "###"))  // Skip to the "###" marker if any. We don't skip past to match the behavior of GetID()
			name = p;
		fprintf(f, "[%s]\n", name);
		fprintf(f, "Pos=%d,%d\n", (int)settings->Pos.x, (int)settings->Pos.y);
		fprintf(f, "Size=%d,%d\n", (int)settings->Size.x, (int)settings->Size.y);
		fprintf(f, "Collapsed=%d\n", settings->Collapsed);
		fprintf(f, "\n");
	}

	fclose(f);
}

static void MarkIniSettingsDirty()
{
	ImGuiContext& g = *GImGui;
	if (g.SettingsDirtyTimer <= 0.0f)
		g.SettingsDirtyTimer = g.IO.IniSavingRate;
}

// FIXME: Add a more explicit sort order in the window structure.
static int ChildWindowComparer(const void* lhs, const void* rhs)
{
	const ImGuiWindow* a = *(const ImGuiWindow**)lhs;
	const ImGuiWindow* b = *(const ImGuiWindow**)rhs;
	if (int d = (a->Flags & ImGuiWindowFlags_Popup) - (b->Flags & ImGuiWindowFlags_Popup))
		return d;
	if (int d = (a->Flags & ImGuiWindowFlags_Tooltip) - (b->Flags & ImGuiWindowFlags_Tooltip))
		return d;
	if (int d = (a->Flags & ImGuiWindowFlags_ComboBox) - (b->Flags & ImGuiWindowFlags_ComboBox))
		return d;
	return (a->OrderWithinParent - b->OrderWithinParent);
}

static void AddWindowToSortedBuffer(ImVector<ImGuiWindow*>& out_sorted_windows, ImGuiWindow* window)
{
	out_sorted_windows.push_back(window);
	if (window->Active)
	{
		int count = window->DC.ChildWindows.Size;
		if (count > 1)
			qsort(window->DC.ChildWindows.begin(), (size_t)count, sizeof(ImGuiWindow*), ChildWindowComparer);
		for (int i = 0; i < count; i++)
		{
			ImGuiWindow* child = window->DC.ChildWindows[i];
			if (child->Active)
				AddWindowToSortedBuffer(out_sorted_windows, child);
		}
	}
}

static void AddDrawListToRenderList(ImVector<ImDrawList*>& out_render_list, ImDrawList* draw_list)
{
	if (draw_list->CmdBuffer.empty())
		return;

	// Remove trailing command if unused
	ImDrawCmd& last_cmd = draw_list->CmdBuffer.back();
	if (last_cmd.ElemCount == 0 && last_cmd.UserCallback == NULL)
	{
		draw_list->CmdBuffer.pop_back();
		if (draw_list->CmdBuffer.empty())
			return;
	}

	// Draw list sanity check. Detect mismatch between PrimReserve() calls and incrementing _VtxCurrentIdx, _VtxWritePtr etc. May trigger for you if you are using PrimXXX functions incorrectly.
	IM_ASSERT(draw_list->VtxBuffer.Size == 0 || draw_list->_VtxWritePtr == draw_list->VtxBuffer.Data + draw_list->VtxBuffer.Size);
	IM_ASSERT(draw_list->IdxBuffer.Size == 0 || draw_list->_IdxWritePtr == draw_list->IdxBuffer.Data + draw_list->IdxBuffer.Size);
	IM_ASSERT((int)draw_list->_VtxCurrentIdx == draw_list->VtxBuffer.Size);

	// Check that draw_list doesn't use more vertices than indexable in a single draw call (default ImDrawIdx = unsigned short = 2 bytes = 64K vertices per window)
	// If this assert triggers because you are drawing lots of stuff manually, you can:
	// A) Add '#define ImDrawIdx unsigned int' in imconfig.h to set the index size to 4 bytes. You'll need to handle the 4-bytes indices to your renderer.
	//    For example, the OpenGL example code detect index size at compile-time by doing:
	//    'glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);'
	//    Your own engine or render API may use different parameters or function calls to specify index sizes. 2 and 4 bytes indices are generally supported by most API.
	// B) If for some reason you cannot use 4 bytes indices or don't want to, a workaround is to call BeginChild()/EndChild() before reaching the 64K limit to split your draw commands in multiple draw lists.
	IM_ASSERT(((ImU64)draw_list->_VtxCurrentIdx >> (sizeof(ImDrawIdx) * 8)) == 0);  // Too many vertices in same ImDrawList. See comment above.

	out_render_list.push_back(draw_list);
	GImGui->IO.MetricsRenderVertices += draw_list->VtxBuffer.Size;
	GImGui->IO.MetricsRenderIndices += draw_list->IdxBuffer.Size;
}

static void AddWindowToRenderList(ImVector<ImDrawList*>& out_render_list, ImGuiWindow* window)
{
	AddDrawListToRenderList(out_render_list, window->DrawList);
	for (int i = 0; i < window->DC.ChildWindows.Size; i++)
	{
		ImGuiWindow* child = window->DC.ChildWindows[i];
		if (!child->Active) // clipped children may have been marked not active
			continue;
		if ((child->Flags & ImGuiWindowFlags_Popup) && child->HiddenFrames > 0)
			continue;
		AddWindowToRenderList(out_render_list, child);
	}
}

// When using this function it is sane to ensure that float are perfectly rounded to integer values, to that e.g. (int)(max.x-min.x) in user's render produce correct result.
void ImGui::PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DrawList->PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);
	window->ClipRect = window->DrawList->_ClipRectStack.back();
}

void ImGui::PopClipRect()
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DrawList->PopClipRect();
	window->ClipRect = window->DrawList->_ClipRectStack.back();
}

// This is normally called by Render(). You may want to call it directly if you want to avoid calling Render() but the gain will be very minimal.
void ImGui::EndFrame()
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(g.Initialized);                       // Forgot to call ImGui::NewFrame()
	IM_ASSERT(g.FrameCountEnded != g.FrameCount);   // ImGui::EndFrame() called multiple times, or forgot to call ImGui::NewFrame() again

													// Notify OS when our Input Method Editor cursor has moved (e.g. CJK inputs using Microsoft IME)
	if (g.IO.ImeSetInputScreenPosFn && ImLengthSqr(g.OsImePosRequest - g.OsImePosSet) > 0.0001f)
	{
		g.IO.ImeSetInputScreenPosFn((int)g.OsImePosRequest.x, (int)g.OsImePosRequest.y);
		g.OsImePosSet = g.OsImePosRequest;
	}

	// Hide implicit "Debug" window if it hasn't been used
	IM_ASSERT(g.CurrentWindowStack.Size == 1);    // Mismatched Begin()/End() calls
	if (g.CurrentWindow && !g.CurrentWindow->Accessed)
		g.CurrentWindow->Active = false;
	ImGui::End();

	// Click to focus window and start moving (after we're done with all our widgets)
	if (g.ActiveId == 0 && g.HoveredId == 0 && g.IO.MouseClicked[0])
	{
		if (!(g.FocusedWindow && !g.FocusedWindow->WasActive && g.FocusedWindow->Active)) // Unless we just made a popup appear
		{
			if (g.HoveredRootWindow != NULL)
			{
				FocusWindow(g.HoveredWindow);
				if (!(g.HoveredWindow->Flags & ImGuiWindowFlags_NoMove))
				{
					g.MovedWindow = g.HoveredWindow;
					g.MovedWindowMoveId = g.HoveredRootWindow->MoveId;
					SetActiveID(g.MovedWindowMoveId, g.HoveredRootWindow);
				}
			}
			else if (g.FocusedWindow != NULL && GetFrontMostModalRootWindow() == NULL)
			{
				// Clicking on void disable focus
				FocusWindow(NULL);
			}
		}
	}

	// Sort the window list so that all child windows are after their parent
	// We cannot do that on FocusWindow() because childs may not exist yet
	g.WindowsSortBuffer.resize(0);
	g.WindowsSortBuffer.reserve(g.Windows.Size);
	for (int i = 0; i != g.Windows.Size; i++)
	{
		ImGuiWindow* window = g.Windows[i];
		if (window->Active && (window->Flags & ImGuiWindowFlags_ChildWindow))       // if a child is active its parent will add it
			continue;
		AddWindowToSortedBuffer(g.WindowsSortBuffer, window);
	}
	IM_ASSERT(g.Windows.Size == g.WindowsSortBuffer.Size);  // we done something wrong
	g.Windows.swap(g.WindowsSortBuffer);

	// Clear Input data for next frame
	g.IO.MouseWheel = 0.0f;
	memset(g.IO.InputCharacters, 0, sizeof(g.IO.InputCharacters));

	g.FrameCountEnded = g.FrameCount;
}

void ImGui::Render()
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(g.Initialized);   // Forgot to call ImGui::NewFrame()

	if (g.FrameCountEnded != g.FrameCount)
		ImGui::EndFrame();
	g.FrameCountRendered = g.FrameCount;

	// Skip render altogether if alpha is 0.0
	// Note that vertex buffers have been created and are wasted, so it is best practice that you don't create windows in the first place, or consistently respond to Begin() returning false.
	if (g.Style.Alpha > 0.0f)
	{
		// Gather windows to render
		g.IO.MetricsRenderVertices = g.IO.MetricsRenderIndices = g.IO.MetricsActiveWindows = 0;
		for (int i = 0; i < IM_ARRAYSIZE(g.RenderDrawLists); i++)
			g.RenderDrawLists[i].resize(0);
		for (int i = 0; i != g.Windows.Size; i++)
		{
			ImGuiWindow* window = g.Windows[i];
			if (window->Active && window->HiddenFrames <= 0 && (window->Flags & (ImGuiWindowFlags_ChildWindow)) == 0)
			{
				// FIXME: Generalize this with a proper layering system so e.g. user can draw in specific layers, below text, ..
				g.IO.MetricsActiveWindows++;
				if (window->Flags & ImGuiWindowFlags_Popup)
					AddWindowToRenderList(g.RenderDrawLists[1], window);
				else if (window->Flags & ImGuiWindowFlags_Tooltip)
					AddWindowToRenderList(g.RenderDrawLists[2], window);
				else
					AddWindowToRenderList(g.RenderDrawLists[0], window);
			}
		}

		// Flatten layers
		int n = g.RenderDrawLists[0].Size;
		int flattened_size = n;
		for (int i = 1; i < IM_ARRAYSIZE(g.RenderDrawLists); i++)
			flattened_size += g.RenderDrawLists[i].Size;
		g.RenderDrawLists[0].resize(flattened_size);
		for (int i = 1; i < IM_ARRAYSIZE(g.RenderDrawLists); i++)
		{
			ImVector<ImDrawList*>& layer = g.RenderDrawLists[i];
			if (layer.empty())
				continue;
			memcpy(&g.RenderDrawLists[0][n], &layer[0], layer.Size * sizeof(ImDrawList*));
			n += layer.Size;
		}

		// Draw software mouse cursor if requested
		if (g.IO.MouseDrawCursor)
		{
			const ImGuiMouseCursorData& cursor_data = g.MouseCursorData[g.MouseCursor];
			const ImVec2 pos = g.IO.MousePos - cursor_data.HotOffset;
			const ImVec2 size = cursor_data.Size;
			const ImTextureID tex_id = g.IO.Fonts->TexID;
			g.OverlayDrawList.PushTextureID(tex_id);
			g.OverlayDrawList.AddImage(tex_id, pos + ImVec2(1, 0), pos + ImVec2(1, 0) + size, cursor_data.TexUvMin[1], cursor_data.TexUvMax[1], IM_COL32(0, 0, 0, 48));        // Shadow
			g.OverlayDrawList.AddImage(tex_id, pos + ImVec2(2, 0), pos + ImVec2(2, 0) + size, cursor_data.TexUvMin[1], cursor_data.TexUvMax[1], IM_COL32(0, 0, 0, 48));        // Shadow
			g.OverlayDrawList.AddImage(tex_id, pos, pos + size, cursor_data.TexUvMin[1], cursor_data.TexUvMax[1], IM_COL32(0, 0, 0, 255));       // Black border
			g.OverlayDrawList.AddImage(tex_id, pos, pos + size, cursor_data.TexUvMin[0], cursor_data.TexUvMax[0], IM_COL32(255, 255, 255, 255)); // White fill
			g.OverlayDrawList.PopTextureID();
		}
		if (!g.OverlayDrawList.VtxBuffer.empty())
			AddDrawListToRenderList(g.RenderDrawLists[0], &g.OverlayDrawList);

		// Setup draw data
		g.RenderDrawData.Valid = true;
		g.RenderDrawData.CmdLists = (g.RenderDrawLists[0].Size > 0) ? &g.RenderDrawLists[0][0] : NULL;
		g.RenderDrawData.CmdListsCount = g.RenderDrawLists[0].Size;
		g.RenderDrawData.TotalVtxCount = g.IO.MetricsRenderVertices;
		g.RenderDrawData.TotalIdxCount = g.IO.MetricsRenderIndices;

		// Render. If user hasn't set a callback then they may retrieve the draw data via GetDrawData()
		if (g.RenderDrawData.CmdListsCount > 0 && g.IO.RenderDrawListsFn != NULL)
			g.IO.RenderDrawListsFn(&g.RenderDrawData);
	}
}

const char* ImGui::FindRenderedTextEnd(const char* text, const char* text_end)
{
	const char* text_display_end = text;
	if (!text_end)
		text_end = (const char*)-1;

	while (text_display_end < text_end && *text_display_end != '\0' && (text_display_end[0] != '#' || text_display_end[1] != '#'))
		text_display_end++;
	return text_display_end;
}

// Pass text data straight to log (without being displayed)
void ImGui::LogText(const char* fmt, ...)
{
	ImGuiContext& g = *GImGui;
	if (!g.LogEnabled)
		return;

	va_list args;
	va_start(args, fmt);
	if (g.LogFile)
	{
		vfprintf(g.LogFile, fmt, args);
	}
	else
	{
		g.LogClipboard->appendv(fmt, args);
	}
	va_end(args);
}

// Internal version that takes a position to decide on newline placement and pad items according to their depth.
// We split text into individual lines to add current tree level padding
static void LogRenderedText(const ImVec2& ref_pos, const char* text, const char* text_end)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = ImGui::GetCurrentWindowRead();

	if (!text_end)
		text_end = ImGui::FindRenderedTextEnd(text, text_end);

	const bool log_new_line = ref_pos.y > window->DC.LogLinePosY + 1;
	window->DC.LogLinePosY = ref_pos.y;

	const char* text_remaining = text;
	if (g.LogStartDepth > window->DC.TreeDepth)  // Re-adjust padding if we have popped out of our starting depth
		g.LogStartDepth = window->DC.TreeDepth;
	const int tree_depth = (window->DC.TreeDepth - g.LogStartDepth);
	for (;;)
	{
		// Split the string. Each new line (after a '\n') is followed by spacing corresponding to the current depth of our log entry.
		const char* line_end = text_remaining;
		while (line_end < text_end)
			if (*line_end == '\n')
				break;
			else
				line_end++;
		if (line_end >= text_end)
			line_end = NULL;

		const bool is_first_line = (text == text_remaining);
		bool is_last_line = false;
		if (line_end == NULL)
		{
			is_last_line = true;
			line_end = text_end;
		}
		if (line_end != NULL && !(is_last_line && (line_end - text_remaining) == 0))
		{
			const int char_count = (int)(line_end - text_remaining);
			if (log_new_line || !is_first_line)
				ImGui::LogText(IM_NEWLINE "%*s%.*s", tree_depth * 4, "", char_count, text_remaining);
			else
				ImGui::LogText(" %.*s", char_count, text_remaining);
		}

		if (is_last_line)
			break;
		text_remaining = line_end + 1;
	}
}

// Internal ImGui functions to render text
// RenderText***() functions calls ImDrawList::AddText() calls ImBitmapFont::RenderText()
void ImGui::RenderText(ImVec2 pos, const char* text, const char* text_end, bool hide_text_after_hash, ImU32 col)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();

	// Hide anything after a '##' string
	const char* text_display_end;
	if (hide_text_after_hash)
	{
		text_display_end = FindRenderedTextEnd(text, text_end);
	}
	else
	{
		if (!text_end)
			text_end = text + strlen(text); // FIXME-OPT
		text_display_end = text_end;
	}

	const int text_len = (int)(text_display_end - text);
	if (text_len > 0)
	{
		window->DrawList->AddText(g.Font, g.FontSize, pos, GetColorU32(col), text, text_display_end);
		if (g.LogEnabled)
			LogRenderedText(pos, text, text_display_end);
	}
}

void ImGui::RenderTextWrapped(ImVec2 pos, const char* text, const char* text_end, float wrap_width)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();

	if (!text_end)
		text_end = text + strlen(text); // FIXME-OPT

	const int text_len = (int)(text_end - text);
	if (text_len > 0)
	{
		window->DrawList->AddText(g.Font, g.FontSize, pos, GetColorU32(ImGuiCol_Text), text, text_end, wrap_width);
		if (g.LogEnabled)
			LogRenderedText(pos, text, text_end);
	}
}

// Default clip_rect uses (pos_min,pos_max)
// Handle clipping on CPU immediately (vs typically let the GPU clip the triangles that are overlapping the clipping rectangle edges)
void ImGui::RenderTextClipped(const ImVec2& pos_min, const ImVec2& pos_max, const char* text, const char* text_end, const ImVec2* text_size_if_known, const ImVec2& align, const ImRect* clip_rect)
{
	// Hide anything after a '##' string
	const char* text_display_end = FindRenderedTextEnd(text, text_end);
	const int text_len = (int)(text_display_end - text);
	if (text_len == 0)
		return;

	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();

	// Perform CPU side clipping for single clipped element to avoid using scissor state
	ImVec2 pos = pos_min;
	const ImVec2 text_size = text_size_if_known ? *text_size_if_known : CalcTextSize(text, text_display_end, false, 0.0f);

	const ImVec2* clip_min = clip_rect ? &clip_rect->Min : &pos_min;
	const ImVec2* clip_max = clip_rect ? &clip_rect->Max : &pos_max;
	bool need_clipping = (pos.x + text_size.x >= clip_max->x) || (pos.y + text_size.y >= clip_max->y);
	if (clip_rect) // If we had no explicit clipping rectangle then pos==clip_min
		need_clipping |= (pos.x < clip_min->x) || (pos.y < clip_min->y);

	// Align whole block. We should defer that to the better rendering function when we'll have support for individual line alignment.
	if (align.x > 0.0f) pos.x = ImMax(pos.x, pos.x + (pos_max.x - pos.x - text_size.x) * align.x);
	if (align.y > 0.0f) pos.y = ImMax(pos.y, pos.y + (pos_max.y - pos.y - text_size.y) * align.y);

	// Render
	if (need_clipping)
	{
		ImVec4 fine_clip_rect(clip_min->x, clip_min->y, clip_max->x, clip_max->y);
		window->DrawList->AddText(g.Font, g.FontSize, pos, GetColorU32(ImGuiCol_Text), text, text_display_end, 0.0f, &fine_clip_rect);
	}
	else
	{
		window->DrawList->AddText(g.Font, g.FontSize, pos, GetColorU32(ImGuiCol_Text), text, text_display_end, 0.0f, NULL);
	}
	if (g.LogEnabled)
		LogRenderedText(pos, text, text_display_end);
}

// Render a rectangle shaped with optional rounding and borders
void ImGui::RenderFrame(ImVec2 p_min, ImVec2 p_max, ImU32 fill_col, bool border, float rounding)
{
	ImGuiWindow* window = GetCurrentWindow();

	window->DrawList->AddRectFilled(p_min, p_max, fill_col, rounding);
	if (border && (window->Flags & ImGuiWindowFlags_ShowBorders))
	{
		window->DrawList->AddRect(p_min + ImVec2(1, 1), p_max + ImVec2(1, 1), GetColorU32(ImGuiCol_BorderShadow), rounding);
		window->DrawList->AddRect(p_min, p_max, GetColorU32(ImGuiCol_Border), rounding);
	}
}

// Render a triangle to denote expanded/collapsed state
void ImGui::RenderCollapseTriangle(ImVec2 p_min, bool is_open, float scale)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();

	const float h = g.FontSize * 1.00f;
	const float r = h * 0.40f * scale;
	ImVec2 center = p_min + ImVec2(h*0.50f, h*0.50f*scale);

	ImVec2 a, b, c;
	if (is_open)
	{
		center.y -= r * 0.25f;
		a = center + ImVec2(0, 1)*r;
		b = center + ImVec2(-0.866f, -0.5f)*r;
		c = center + ImVec2(0.866f, -0.5f)*r;
	}
	else
	{
		a = center + ImVec2(1, 0)*r;
		b = center + ImVec2(-0.500f, 0.866f)*r;
		c = center + ImVec2(-0.500f, -0.866f)*r;
	}

	window->DrawList->AddTriangleFilled(a, b, c, GetColorU32(ImGuiCol_Text));
}

void ImGui::RenderBullet(ImVec2 pos)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DrawList->AddCircleFilled(pos, GImGui->FontSize*0.20f, GetColorU32(ImGuiCol_Text), 8);
}

void ImGui::RenderCheckMark(ImVec2 pos, ImU32 col)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();

	ImVec2 a, b, c;
	float start_x = (float)(int)(g.FontSize * 0.307f + 0.5f);
	float rem_third = (float)(int)((g.FontSize - start_x) / 3.0f);
	a.x = pos.x + 0.5f + start_x;
	b.x = a.x + rem_third;
	c.x = a.x + rem_third * 3.0f;
	b.y = pos.y - 1.0f + (float)(int)(g.Font->Ascent * (g.FontSize / g.Font->FontSize) + 0.5f) + (float)(int)(g.Font->DisplayOffset.y);
	a.y = b.y - rem_third;
	c.y = b.y - rem_third * 2.0f;

	window->DrawList->PathLineTo(a);
	window->DrawList->PathLineTo(b);
	window->DrawList->PathLineTo(c);
	window->DrawList->PathStroke(col, false);
}

// Calculate text size. Text can be multi-line. Optionally ignore text after a ## marker.
// CalcTextSize("") should return ImVec2(0.0f, GImGui->FontSize)
ImVec2 ImGui::CalcTextSize(const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width)
{
	ImGuiContext& g = *GImGui;

	const char* text_display_end;
	if (hide_text_after_double_hash)
		text_display_end = FindRenderedTextEnd(text, text_end);      // Hide anything after a '##' string
	else
		text_display_end = text_end;

	ImFont* font = g.Font;
	const float font_size = g.FontSize;
	if (text == text_display_end)
		return ImVec2(0.0f, font_size);
	ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, wrap_width, text, text_display_end, NULL);

	// Cancel out character spacing for the last character of a line (it is baked into glyph->XAdvance field)
	const float font_scale = font_size / font->FontSize;
	const float character_spacing_x = 1.0f * font_scale;
	if (text_size.x > 0.0f)
		text_size.x -= character_spacing_x;
	text_size.x = (float)(int)(text_size.x + 0.95f);

	return text_size;
}

// Helper to calculate coarse clipping of large list of evenly sized items.
// NB: Prefer using the ImGuiListClipper higher-level helper if you can! Read comments and instructions there on how those use this sort of pattern.
// NB: 'items_count' is only used to clamp the result, if you don't know your count you can use INT_MAX
void ImGui::CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindowRead();
	if (g.LogEnabled)
	{
		// If logging is active, do not perform any clipping
		*out_items_display_start = 0;
		*out_items_display_end = items_count;
		return;
	}
	if (window->SkipItems)
	{
		*out_items_display_start = *out_items_display_end = 0;
		return;
	}

	const ImVec2 pos = window->DC.CursorPos;
	int start = (int)((window->ClipRect.Min.y - pos.y) / items_height);
	int end = (int)((window->ClipRect.Max.y - pos.y) / items_height);
	start = ImClamp(start, 0, items_count);
	end = ImClamp(end + 1, start, items_count);
	*out_items_display_start = start;
	*out_items_display_end = end;
}

// Find window given position, search front-to-back
// FIXME: Note that we have a lag here because WindowRectClipped is updated in Begin() so windows moved by user via SetWindowPos() and not SetNextWindowPos() will have that rectangle lagging by a frame at the time FindHoveredWindow() is called, aka before the next Begin(). Moving window thankfully isn't affected.
static ImGuiWindow* FindHoveredWindow(ImVec2 pos, bool excluding_childs)
{
	ImGuiContext& g = *GImGui;
	for (int i = g.Windows.Size - 1; i >= 0; i--)
	{
		ImGuiWindow* window = g.Windows[i];
		if (!window->Active)
			continue;
		if (window->Flags & ImGuiWindowFlags_NoInputs)
			continue;
		if (excluding_childs && (window->Flags & ImGuiWindowFlags_ChildWindow) != 0)
			continue;

		// Using the clipped AABB so a child window will typically be clipped by its parent.
		ImRect bb(window->WindowRectClipped.Min - g.Style.TouchExtraPadding, window->WindowRectClipped.Max + g.Style.TouchExtraPadding);
		if (bb.Contains(pos))
			return window;
	}
	return NULL;
}

// Test if mouse cursor is hovering given rectangle
// NB- Rectangle is clipped by our current clip setting
// NB- Expand the rectangle to be generous on imprecise inputs systems (g.Style.TouchExtraPadding)
bool ImGui::IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindowRead();

	// Clip
	ImRect rect_clipped(r_min, r_max);
	if (clip)
		rect_clipped.Clip(window->ClipRect);

	// Expand for touch input
	const ImRect rect_for_touch(rect_clipped.Min - g.Style.TouchExtraPadding, rect_clipped.Max + g.Style.TouchExtraPadding);
	return rect_for_touch.Contains(g.IO.MousePos);
}

bool ImGui::IsMouseHoveringWindow()
{
	ImGuiContext& g = *GImGui;
	return g.HoveredWindow == g.CurrentWindow;
}

bool ImGui::IsMouseHoveringAnyWindow()
{
	ImGuiContext& g = *GImGui;
	return g.HoveredWindow != NULL;
}

static bool IsKeyPressedMap(ImGuiKey key, bool repeat)
{
	const int key_index = GImGui->IO.KeyMap[key];
	return ImGui::IsKeyPressed(key_index, repeat);
}

int ImGui::GetKeyIndex(ImGuiKey imgui_key)
{
	IM_ASSERT(imgui_key >= 0 && imgui_key < ImGuiKey_COUNT);
	return GImGui->IO.KeyMap[imgui_key];
}

// Note that imgui doesn't know the semantic of each entry of io.KeyDown[]. Use your own indices/enums according to how your backend/engine stored them into KeyDown[]!
bool ImGui::IsKeyDown(int user_key_index)
{
	if (user_key_index < 0) return false;
	IM_ASSERT(user_key_index >= 0 && user_key_index < IM_ARRAYSIZE(GImGui->IO.KeysDown));
	return GImGui->IO.KeysDown[user_key_index];
}

bool ImGui::IsKeyPressed(int user_key_index, bool repeat)
{
	ImGuiContext& g = *GImGui;
	if (user_key_index < 0) return false;
	IM_ASSERT(user_key_index >= 0 && user_key_index < IM_ARRAYSIZE(g.IO.KeysDown));
	const float t = g.IO.KeysDownDuration[user_key_index];
	if (t == 0.0f)
		return true;

	if (repeat && t > g.IO.KeyRepeatDelay)
	{
		float delay = g.IO.KeyRepeatDelay, rate = g.IO.KeyRepeatRate;
		if ((fmodf(t - delay, rate) > rate*0.5f) != (fmodf(t - delay - g.IO.DeltaTime, rate) > rate*0.5f))
			return true;
	}
	return false;
}

bool ImGui::IsKeyReleased(int user_key_index)
{
	ImGuiContext& g = *GImGui;
	if (user_key_index < 0) return false;
	IM_ASSERT(user_key_index >= 0 && user_key_index < IM_ARRAYSIZE(g.IO.KeysDown));
	if (g.IO.KeysDownDurationPrev[user_key_index] >= 0.0f && !g.IO.KeysDown[user_key_index])
		return true;
	return false;
}

bool ImGui::IsMouseDown(int button)
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(button >= 0 && button < IM_ARRAYSIZE(g.IO.MouseDown));
	return g.IO.MouseDown[button];
}

bool ImGui::IsMouseClicked(int button, bool repeat)
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(button >= 0 && button < IM_ARRAYSIZE(g.IO.MouseDown));
	const float t = g.IO.MouseDownDuration[button];
	if (t == 0.0f)
		return true;

	if (repeat && t > g.IO.KeyRepeatDelay)
	{
		float delay = g.IO.KeyRepeatDelay, rate = g.IO.KeyRepeatRate;
		if ((fmodf(t - delay, rate) > rate*0.5f) != (fmodf(t - delay - g.IO.DeltaTime, rate) > rate*0.5f))
			return true;
	}

	return false;
}

bool ImGui::IsMouseReleased(int button)
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(button >= 0 && button < IM_ARRAYSIZE(g.IO.MouseDown));
	return g.IO.MouseReleased[button];
}

bool ImGui::IsMouseDoubleClicked(int button)
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(button >= 0 && button < IM_ARRAYSIZE(g.IO.MouseDown));
	return g.IO.MouseDoubleClicked[button];
}

bool ImGui::IsMouseDragging(int button, float lock_threshold)
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(button >= 0 && button < IM_ARRAYSIZE(g.IO.MouseDown));
	if (!g.IO.MouseDown[button])
		return false;
	if (lock_threshold < 0.0f)
		lock_threshold = g.IO.MouseDragThreshold;
	return g.IO.MouseDragMaxDistanceSqr[button] >= lock_threshold * lock_threshold;
}

ImVec2 ImGui::GetMousePos()
{
	return GImGui->IO.MousePos;
}

// NB: prefer to call right after BeginPopup(). At the time Selectable/MenuItem is activated, the popup is already closed!
ImVec2 ImGui::GetMousePosOnOpeningCurrentPopup()
{
	ImGuiContext& g = *GImGui;
	if (g.CurrentPopupStack.Size > 0)
		return g.OpenPopupStack[g.CurrentPopupStack.Size - 1].MousePosOnOpen;
	return g.IO.MousePos;
}

ImVec2 ImGui::GetMouseDragDelta(int button, float lock_threshold)
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(button >= 0 && button < IM_ARRAYSIZE(g.IO.MouseDown));
	if (lock_threshold < 0.0f)
		lock_threshold = g.IO.MouseDragThreshold;
	if (g.IO.MouseDown[button])
		if (g.IO.MouseDragMaxDistanceSqr[button] >= lock_threshold * lock_threshold)
			return g.IO.MousePos - g.IO.MouseClickedPos[button];     // Assume we can only get active with left-mouse button (at the moment).
	return ImVec2(0.0f, 0.0f);
}

void ImGui::ResetMouseDragDelta(int button)
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(button >= 0 && button < IM_ARRAYSIZE(g.IO.MouseDown));
	// NB: We don't need to reset g.IO.MouseDragMaxDistanceSqr
	g.IO.MouseClickedPos[button] = g.IO.MousePos;
}

ImGuiMouseCursor ImGui::GetMouseCursor()
{
	return GImGui->MouseCursor;
}

void ImGui::SetMouseCursor(ImGuiMouseCursor cursor_type)
{
	GImGui->MouseCursor = cursor_type;
}

void ImGui::CaptureKeyboardFromApp(bool capture)
{
	GImGui->CaptureKeyboardNextFrame = capture ? 1 : 0;
}

void ImGui::CaptureMouseFromApp(bool capture)
{
	GImGui->CaptureMouseNextFrame = capture ? 1 : 0;
}

bool ImGui::IsItemHovered()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.LastItemHoveredAndUsable;
}

bool ImGui::IsItemHoveredRect()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.LastItemHoveredRect;
}

bool ImGui::IsItemActive()
{
	ImGuiContext& g = *GImGui;
	if (g.ActiveId)
	{
		ImGuiWindow* window = GetCurrentWindowRead();
		return g.ActiveId == window->DC.LastItemId;
	}
	return false;
}

bool ImGui::IsItemClicked(int mouse_button)
{
	return IsMouseClicked(mouse_button) && IsItemHovered();
}

bool ImGui::IsAnyItemHovered()
{
	return GImGui->HoveredId != 0 || GImGui->HoveredIdPreviousFrame != 0;
}

bool ImGui::IsAnyItemActive()
{
	return GImGui->ActiveId != 0;
}

bool ImGui::IsItemVisible()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	ImRect r(window->ClipRect);
	return r.Overlaps(window->DC.LastItemRect);
}

// Allow last item to be overlapped by a subsequent item. Both may be activated during the same frame before the later one takes priority.
void ImGui::SetItemAllowOverlap()
{
	ImGuiContext& g = *GImGui;
	if (g.HoveredId == g.CurrentWindow->DC.LastItemId)
		g.HoveredIdAllowOverlap = true;
	if (g.ActiveId == g.CurrentWindow->DC.LastItemId)
		g.ActiveIdAllowOverlap = true;
}

ImVec2 ImGui::GetItemRectMin()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.LastItemRect.Min;
}

ImVec2 ImGui::GetItemRectMax()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.LastItemRect.Max;
}

ImVec2 ImGui::GetItemRectSize()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.LastItemRect.GetSize();
}

ImVec2 ImGui::CalcItemRectClosestPoint(const ImVec2& pos, bool on_edge, float outward)
{
	ImGuiWindow* window = GetCurrentWindowRead();
	ImRect rect = window->DC.LastItemRect;
	rect.Expand(outward);
	return rect.GetClosestPoint(pos, on_edge);
}

static ImRect GetVisibleRect()
{
	ImGuiContext& g = *GImGui;
	if (g.IO.DisplayVisibleMin.x != g.IO.DisplayVisibleMax.x && g.IO.DisplayVisibleMin.y != g.IO.DisplayVisibleMax.y)
		return ImRect(g.IO.DisplayVisibleMin, g.IO.DisplayVisibleMax);
	return ImRect(0.0f, 0.0f, g.IO.DisplaySize.x, g.IO.DisplaySize.y);
}

// Not exposed publicly as BeginTooltip() because bool parameters are evil. Let's see if other needs arise first.
static void BeginTooltipEx(bool override_previous_tooltip)
{
	ImGuiContext& g = *GImGui;
	char window_name[16];
	ImFormatString(window_name, IM_ARRAYSIZE(window_name), "##Tooltip%02d", g.TooltipOverrideCount);
	if (override_previous_tooltip)
		if (ImGuiWindow* window = ImGui::FindWindowByName(window_name))
			if (window->Active)
			{
				// Hide previous tooltips. We can't easily "reset" the content of a window so we create a new one.
				window->HiddenFrames = 1;
				ImFormatString(window_name, IM_ARRAYSIZE(window_name), "##Tooltip%02d", ++g.TooltipOverrideCount);
			}
	ImGui::Begin(window_name, NULL, ImGuiWindowFlags_Tooltip | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize);
}

void ImGui::SetTooltipV(const char* fmt, va_list args)
{
	BeginTooltipEx(true);
	TextV(fmt, args);
	EndTooltip();
}

void ImGui::SetTooltip(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	SetTooltipV(fmt, args);
	va_end(args);
}

void ImGui::BeginTooltip()
{
	BeginTooltipEx(false);
}

void ImGui::EndTooltip()
{
	IM_ASSERT(GetCurrentWindowRead()->Flags & ImGuiWindowFlags_Tooltip);   // Mismatched BeginTooltip()/EndTooltip() calls
	ImGui::End();
}

static bool IsPopupOpen(ImGuiID id)
{
	ImGuiContext& g = *GImGui;
	return g.OpenPopupStack.Size > g.CurrentPopupStack.Size && g.OpenPopupStack[g.CurrentPopupStack.Size].PopupId == id;
}

// Mark popup as open (toggle toward open state).
// Popups are closed when user click outside, or activate a pressable item, or CloseCurrentPopup() is called within a BeginPopup()/EndPopup() block.
// Popup identifiers are relative to the current ID-stack (so OpenPopup and BeginPopup needs to be at the same level).
// One open popup per level of the popup hierarchy (NB: when assigning we reset the Window member of ImGuiPopupRef to NULL)
void ImGui::OpenPopupEx(const char* str_id, bool reopen_existing)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	ImGuiID id = window->GetID(str_id);
	int current_stack_size = g.CurrentPopupStack.Size;
	ImGuiPopupRef popup_ref = ImGuiPopupRef(id, window, window->GetID("##menus"), g.IO.MousePos); // Tagged as new ref because constructor sets Window to NULL (we are passing the ParentWindow info here)
	if (g.OpenPopupStack.Size < current_stack_size + 1)
		g.OpenPopupStack.push_back(popup_ref);
	else if (reopen_existing || g.OpenPopupStack[current_stack_size].PopupId != id)
	{
		g.OpenPopupStack.resize(current_stack_size + 1);
		g.OpenPopupStack[current_stack_size] = popup_ref;
	}
}

void ImGui::OpenPopup(const char* str_id)
{
	ImGui::OpenPopupEx(str_id, false);
}

static void CloseInactivePopups()
{
	ImGuiContext& g = *GImGui;
	if (g.OpenPopupStack.empty())
		return;

	// When popups are stacked, clicking on a lower level popups puts focus back to it and close popups above it.
	// Don't close our own child popup windows
	int n = 0;
	if (g.FocusedWindow)
	{
		for (n = 0; n < g.OpenPopupStack.Size; n++)
		{
			ImGuiPopupRef& popup = g.OpenPopupStack[n];
			if (!popup.Window)
				continue;
			IM_ASSERT((popup.Window->Flags & ImGuiWindowFlags_Popup) != 0);
			if (popup.Window->Flags & ImGuiWindowFlags_ChildWindow)
				continue;

			bool has_focus = false;
			for (int m = n; m < g.OpenPopupStack.Size && !has_focus; m++)
				has_focus = (g.OpenPopupStack[m].Window && g.OpenPopupStack[m].Window->RootWindow == g.FocusedWindow->RootWindow);
			if (!has_focus)
				break;
		}
	}
	if (n < g.OpenPopupStack.Size)   // This test is not required but it allows to set a useful breakpoint on the line below
		g.OpenPopupStack.resize(n);
}

static ImGuiWindow* GetFrontMostModalRootWindow()
{
	ImGuiContext& g = *GImGui;
	for (int n = g.OpenPopupStack.Size - 1; n >= 0; n--)
		if (ImGuiWindow* front_most_popup = g.OpenPopupStack.Data[n].Window)
			if (front_most_popup->Flags & ImGuiWindowFlags_Modal)
				return front_most_popup;
	return NULL;
}

static void ClosePopupToLevel(int remaining)
{
	ImGuiContext& g = *GImGui;
	if (remaining > 0)
		ImGui::FocusWindow(g.OpenPopupStack[remaining - 1].Window);
	else
		ImGui::FocusWindow(g.OpenPopupStack[0].ParentWindow);
	g.OpenPopupStack.resize(remaining);
}

static void ClosePopup(ImGuiID id)
{
	if (!IsPopupOpen(id))
		return;
	ImGuiContext& g = *GImGui;
	ClosePopupToLevel(g.OpenPopupStack.Size - 1);
}

// Close the popup we have begin-ed into.
void ImGui::CloseCurrentPopup()
{
	ImGuiContext& g = *GImGui;
	int popup_idx = g.CurrentPopupStack.Size - 1;
	if (popup_idx < 0 || popup_idx > g.OpenPopupStack.Size || g.CurrentPopupStack[popup_idx].PopupId != g.OpenPopupStack[popup_idx].PopupId)
		return;
	while (popup_idx > 0 && g.OpenPopupStack[popup_idx].Window && (g.OpenPopupStack[popup_idx].Window->Flags & ImGuiWindowFlags_ChildMenu))
		popup_idx--;
	ClosePopupToLevel(popup_idx);
}

static inline void ClearSetNextWindowData()
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowPosCond = g.SetNextWindowSizeCond = g.SetNextWindowContentSizeCond = g.SetNextWindowCollapsedCond = 0;
	g.SetNextWindowSizeConstraint = g.SetNextWindowFocus = false;
}

static bool BeginPopupEx(const char* str_id, ImGuiWindowFlags extra_flags)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	const ImGuiID id = window->GetID(str_id);
	if (!IsPopupOpen(id))
	{
		ClearSetNextWindowData(); // We behave like Begin() and need to consume those values
		return false;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGuiWindowFlags flags = extra_flags | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

	char name[20];
	if (flags & ImGuiWindowFlags_ChildMenu)
		ImFormatString(name, IM_ARRAYSIZE(name), "##menu_%d", g.CurrentPopupStack.Size);    // Recycle windows based on depth
	else
		ImFormatString(name, IM_ARRAYSIZE(name), "##popup_%08x", id); // Not recycling, so we can close/open during the same frame

	bool is_open = ImGui::Begin(name, NULL, flags);
	if (!(window->Flags & ImGuiWindowFlags_ShowBorders))
		g.CurrentWindow->Flags &= ~ImGuiWindowFlags_ShowBorders;
	if (!is_open) // NB: is_open can be 'false' when the popup is completely clipped (e.g. zero size display)
		ImGui::EndPopup();

	return is_open;
}

bool ImGui::BeginPopup(const char* str_id)
{
	if (GImGui->OpenPopupStack.Size <= GImGui->CurrentPopupStack.Size)	// Early out for performance
	{
		ClearSetNextWindowData(); // We behave like Begin() and need to consume those values
		return false;
	}
	return BeginPopupEx(str_id, ImGuiWindowFlags_ShowBorders);
}

bool ImGui::BeginPopupModal(const char* name, bool* p_open, ImGuiWindowFlags extra_flags)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	const ImGuiID id = window->GetID(name);
	if (!IsPopupOpen(id))
	{
		ClearSetNextWindowData(); // We behave like Begin() and need to consume those values
		return false;
	}

	ImGuiWindowFlags flags = extra_flags | ImGuiWindowFlags_Popup | ImGuiWindowFlags_Modal | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
	bool is_open = ImGui::Begin(name, p_open, flags);
	if (!is_open || (p_open && !*p_open)) // NB: is_open can be 'false' when the popup is completely clipped (e.g. zero size display)
	{
		ImGui::EndPopup();
		if (is_open)
			ClosePopup(id);
		return false;
	}

	return is_open;
}

void ImGui::EndPopup()
{
	ImGuiWindow* window = GetCurrentWindow();
	IM_ASSERT(window->Flags & ImGuiWindowFlags_Popup);  // Mismatched BeginPopup()/EndPopup() calls
	IM_ASSERT(GImGui->CurrentPopupStack.Size > 0);
	ImGui::End();
	if (!(window->Flags & ImGuiWindowFlags_Modal))
		ImGui::PopStyleVar();
}

// This is a helper to handle the most simple case of associating one named popup to one given widget.
// 1. If you have many possible popups (for different "instances" of a same widget, or for wholly different widgets), you may be better off handling
//    this yourself so you can store data relative to the widget that opened the popup instead of choosing different popup identifiers.
// 2. If you want right-clicking on the same item to reopen the popup at new location, use the same code replacing IsItemHovered() with IsItemHoveredRect()
//    and passing true to the OpenPopupEx().
//    Because: hovering an item in a window below the popup won't normally trigger is hovering behavior/coloring. The pattern of ignoring the fact that
//    the item isn't interactable (because it is blocked by the active popup) may useful in some situation when e.g. large canvas as one item, content of menu
//    driven by click position.
bool ImGui::BeginPopupContextItem(const char* str_id, int mouse_button)
{
	if (IsItemHovered() && IsMouseClicked(mouse_button))
		OpenPopupEx(str_id, false);
	return BeginPopup(str_id);
}

bool ImGui::BeginPopupContextWindow(bool also_over_items, const char* str_id, int mouse_button)
{
	if (!str_id) str_id = "window_context_menu";
	if (IsMouseHoveringWindow() && IsMouseClicked(mouse_button))
		if (also_over_items || !IsAnyItemHovered())
			OpenPopupEx(str_id, true);
	return BeginPopup(str_id);
}

bool ImGui::BeginPopupContextVoid(const char* str_id, int mouse_button)
{
	if (!str_id) str_id = "void_context_menu";
	if (!IsMouseHoveringAnyWindow() && IsMouseClicked(mouse_button))
		OpenPopupEx(str_id, true);
	return BeginPopup(str_id);
}

static bool BeginChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;

	const ImVec2 content_avail = ImGui::GetContentRegionAvail();
	ImVec2 size = ImFloor(size_arg);
	if (size.x <= 0.0f)
	{
		if (size.x == 0.0f)
			flags |= ImGuiWindowFlags_ChildWindowAutoFitX;
		size.x = ImMax(content_avail.x, 4.0f) - fabsf(size.x); // Arbitrary minimum zero-ish child size of 4.0f (0.0f causing too much issues)
	}
	if (size.y <= 0.0f)
	{
		if (size.y == 0.0f)
			flags |= ImGuiWindowFlags_ChildWindowAutoFitY;
		size.y = ImMax(content_avail.y, 4.0f) - fabsf(size.y);
	}
	if (border)
		flags |= ImGuiWindowFlags_ShowBorders;
	flags |= extra_flags;

	char title[256];
	if (name)
		ImFormatString(title, IM_ARRAYSIZE(title), "%s.%s.%08X", window->Name, name, id);
	else
		ImFormatString(title, IM_ARRAYSIZE(title), "%s.%08X", window->Name, id);

	bool ret = ImGui::Begin(title, NULL, size, -1.0f, flags);

	if (!(window->Flags & ImGuiWindowFlags_ShowBorders))
		ImGui::GetCurrentWindow()->Flags &= ~ImGuiWindowFlags_ShowBorders;

	return ret;
}

bool ImGui::BeginChild(const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	return BeginChildEx(str_id, window->GetID(str_id), size_arg, border, extra_flags);
}

bool ImGui::BeginChild(ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
{
	return BeginChildEx(NULL, id, size_arg, border, extra_flags);
}

void ImGui::EndChild()
{
	ImGuiWindow* window = GetCurrentWindow();

	IM_ASSERT(window->Flags & ImGuiWindowFlags_ChildWindow);   // Mismatched BeginChild()/EndChild() callss
	if ((window->Flags & ImGuiWindowFlags_ComboBox) || window->BeginCount > 1)
	{
		ImGui::End();
	}
	else
	{
		// When using auto-filling child window, we don't provide full width/height to ItemSize so that it doesn't feed back into automatic size-fitting.
		ImVec2 sz = GetWindowSize();
		if (window->Flags & ImGuiWindowFlags_ChildWindowAutoFitX) // Arbitrary minimum zero-ish child size of 4.0f causes less trouble than a 0.0f
			sz.x = ImMax(4.0f, sz.x);
		if (window->Flags & ImGuiWindowFlags_ChildWindowAutoFitY)
			sz.y = ImMax(4.0f, sz.y);

		ImGui::End();

		window = GetCurrentWindow();
		ImRect bb(window->DC.CursorPos, window->DC.CursorPos + sz);
		ItemSize(sz);
		ItemAdd(bb, NULL);
	}
}

// Helper to create a child window / scrolling region that looks like a normal widget frame.
bool ImGui::BeginChildFrame(ImGuiID id, const ImVec2& size, ImGuiWindowFlags extra_flags)
{
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, style.Colors[ImGuiCol_FrameBg]);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildWindowRounding, style.FrameRounding);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, style.FramePadding);
	return ImGui::BeginChild(id, size, (g.CurrentWindow->Flags & ImGuiWindowFlags_ShowBorders) ? true : false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysUseWindowPadding | extra_flags);
}

void ImGui::EndChildFrame()
{
	ImGui::EndChild();
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor();
}

// Save and compare stack sizes on Begin()/End() to detect usage errors
static void CheckStacksSize(ImGuiWindow* window, bool write)
{
	// NOT checking: DC.ItemWidth, DC.AllowKeyboardFocus, DC.ButtonRepeat, DC.TextWrapPos (per window) to allow user to conveniently push once and not pop (they are cleared on Begin)
	ImGuiContext& g = *GImGui;
	int* p_backup = &window->DC.StackSizesBackup[0];
	{ int current = window->IDStack.Size;       if (write) *p_backup = current; else IM_ASSERT(*p_backup == current && "PushID/PopID or TreeNode/TreePop Mismatch!");   p_backup++; }    // Too few or too many PopID()/TreePop()
	{ int current = window->DC.GroupStack.Size; if (write) *p_backup = current; else IM_ASSERT(*p_backup == current && "BeginGroup/EndGroup Mismatch!");                p_backup++; }    // Too few or too many EndGroup()
	{ int current = g.CurrentPopupStack.Size;   if (write) *p_backup = current; else IM_ASSERT(*p_backup == current && "BeginMenu/EndMenu or BeginPopup/EndPopup Mismatch"); p_backup++; }// Too few or too many EndMenu()/EndPopup()
	{ int current = g.ColorModifiers.Size;      if (write) *p_backup = current; else IM_ASSERT(*p_backup == current && "PushStyleColor/PopStyleColor Mismatch!");       p_backup++; }    // Too few or too many PopStyleColor()
	{ int current = g.StyleModifiers.Size;      if (write) *p_backup = current; else IM_ASSERT(*p_backup == current && "PushStyleVar/PopStyleVar Mismatch!");           p_backup++; }    // Too few or too many PopStyleVar()
	{ int current = g.FontStack.Size;           if (write) *p_backup = current; else IM_ASSERT(*p_backup == current && "PushFont/PopFont Mismatch!");                   p_backup++; }    // Too few or too many PopFont()
	IM_ASSERT(p_backup == window->DC.StackSizesBackup + IM_ARRAYSIZE(window->DC.StackSizesBackup));
}

static ImVec2 FindBestPopupWindowPos(const ImVec2& base_pos, const ImVec2& size, int* last_dir, const ImRect& r_inner)
{
	const ImGuiStyle& style = GImGui->Style;

	// Clamp into visible area while not overlapping the cursor. Safety padding is optional if our popup size won't fit without it.
	ImVec2 safe_padding = style.DisplaySafeAreaPadding;
	ImRect r_outer(GetVisibleRect());
	r_outer.Reduce(ImVec2((size.x - r_outer.GetWidth() > safe_padding.x * 2) ? safe_padding.x : 0.0f, (size.y - r_outer.GetHeight() > safe_padding.y * 2) ? safe_padding.y : 0.0f));
	ImVec2 base_pos_clamped = ImClamp(base_pos, r_outer.Min, r_outer.Max - size);

	for (int n = (*last_dir != -1) ? -1 : 0; n < 4; n++)   // Last, Right, down, up, left. (Favor last used direction).
	{
		const int dir = (n == -1) ? *last_dir : n;
		ImRect rect(dir == 0 ? r_inner.Max.x : r_outer.Min.x, dir == 1 ? r_inner.Max.y : r_outer.Min.y, dir == 3 ? r_inner.Min.x : r_outer.Max.x, dir == 2 ? r_inner.Min.y : r_outer.Max.y);
		if (rect.GetWidth() < size.x || rect.GetHeight() < size.y)
			continue;
		*last_dir = dir;
		return ImVec2(dir == 0 ? r_inner.Max.x : dir == 3 ? r_inner.Min.x - size.x : base_pos_clamped.x, dir == 1 ? r_inner.Max.y : dir == 2 ? r_inner.Min.y - size.y : base_pos_clamped.y);
	}

	// Fallback, try to keep within display
	*last_dir = -1;
	ImVec2 pos = base_pos;
	pos.x = ImMax(ImMin(pos.x + size.x, r_outer.Max.x) - size.x, r_outer.Min.x);
	pos.y = ImMax(ImMin(pos.y + size.y, r_outer.Max.y) - size.y, r_outer.Min.y);
	return pos;
}

ImGuiWindow* ImGui::FindWindowByName(const char* name)
{
	// FIXME-OPT: Store sorted hashes -> pointers so we can do a bissection in a contiguous block
	ImGuiContext& g = *GImGui;
	ImGuiID id = ImHash(name, 0);
	for (int i = 0; i < g.Windows.Size; i++)
		if (g.Windows[i]->ID == id)
			return g.Windows[i];
	return NULL;
}

static ImGuiWindow* CreateNewWindow(const char* name, ImVec2 size, ImGuiWindowFlags flags)
{
	ImGuiContext& g = *GImGui;

	// Create window the first time
	ImGuiWindow* window = (ImGuiWindow*)ImGui::MemAlloc(sizeof(ImGuiWindow));
	IM_PLACEMENT_NEW(window) ImGuiWindow(name);
	window->Flags = flags;

	if (flags & ImGuiWindowFlags_NoSavedSettings)
	{
		// User can disable loading and saving of settings. Tooltip and child windows also don't store settings.
		window->Size = window->SizeFull = size;
	}
	else
	{
		// Retrieve settings from .ini file
		// Use SetWindowPos() or SetNextWindowPos() with the appropriate condition flag to change the initial position of a window.
		window->PosFloat = ImVec2(60, 60);
		window->Pos = ImVec2((float)(int)window->PosFloat.x, (float)(int)window->PosFloat.y);

		ImGuiIniData* settings = FindWindowSettings(name);
		if (!settings)
		{
			settings = AddWindowSettings(name);
		}
		else
		{
			window->SetWindowPosAllowFlags &= ~ImGuiSetCond_FirstUseEver;
			window->SetWindowSizeAllowFlags &= ~ImGuiSetCond_FirstUseEver;
			window->SetWindowCollapsedAllowFlags &= ~ImGuiSetCond_FirstUseEver;
		}

		if (settings->Pos.x != FLT_MAX)
		{
			window->PosFloat = settings->Pos;
			window->Pos = ImVec2((float)(int)window->PosFloat.x, (float)(int)window->PosFloat.y);
			window->Collapsed = settings->Collapsed;
		}

		if (ImLengthSqr(settings->Size) > 0.00001f && !(flags & ImGuiWindowFlags_NoResize))
			size = settings->Size;
		window->Size = window->SizeFull = size;
	}

	if ((flags & ImGuiWindowFlags_AlwaysAutoResize) != 0)
	{
		window->AutoFitFramesX = window->AutoFitFramesY = 2;
		window->AutoFitOnlyGrows = false;
	}
	else
	{
		if (window->Size.x <= 0.0f)
			window->AutoFitFramesX = 2;
		if (window->Size.y <= 0.0f)
			window->AutoFitFramesY = 2;
		window->AutoFitOnlyGrows = (window->AutoFitFramesX > 0) || (window->AutoFitFramesY > 0);
	}

	if (flags & ImGuiWindowFlags_NoBringToFrontOnFocus)
		g.Windows.insert(g.Windows.begin(), window); // Quite slow but rare and only once
	else
		g.Windows.push_back(window);
	return window;
}

static void ApplySizeFullWithConstraint(ImGuiWindow* window, ImVec2 new_size)
{
	ImGuiContext& g = *GImGui;
	if (g.SetNextWindowSizeConstraint)
	{
		// Using -1,-1 on either X/Y axis to preserve the current size.
		ImRect cr = g.SetNextWindowSizeConstraintRect;
		new_size.x = (cr.Min.x >= 0 && cr.Max.x >= 0) ? ImClamp(new_size.x, cr.Min.x, cr.Max.x) : window->SizeFull.x;
		new_size.y = (cr.Min.y >= 0 && cr.Max.y >= 0) ? ImClamp(new_size.y, cr.Min.y, cr.Max.y) : window->SizeFull.y;
		if (g.SetNextWindowSizeConstraintCallback)
		{
			ImGuiSizeConstraintCallbackData data;
			data.UserData = g.SetNextWindowSizeConstraintCallbackUserData;
			data.Pos = window->Pos;
			data.CurrentSize = window->SizeFull;
			data.DesiredSize = new_size;
			g.SetNextWindowSizeConstraintCallback(&data);
			new_size = data.DesiredSize;
		}
	}
	if (!(window->Flags & (ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_AlwaysAutoResize)))
		new_size = ImMax(new_size, g.Style.WindowMinSize);
	window->SizeFull = new_size;
}

// Push a new ImGui window to add widgets to.
// - A default window called "Debug" is automatically stacked at the beginning of every frame so you can use widgets without explicitly calling a Begin/End pair.
// - Begin/End can be called multiple times during the frame with the same window name to append content.
// - 'size_on_first_use' for a regular window denote the initial size for first-time creation (no saved data) and isn't that useful. Use SetNextWindowSize() prior to calling Begin() for more flexible window manipulation.
// - The window name is used as a unique identifier to preserve window information across frames (and save rudimentary information to the .ini file).
//   You can use the "##" or "###" markers to use the same label with different id, or same id with different label. See documentation at the top of this file.
// - Return false when window is collapsed, so you can early out in your code. You always need to call ImGui::End() even if false is returned.
// - Passing 'bool* p_open' displays a Close button on the upper-right corner of the window, the pointed value will be set to false when the button is pressed.
// - Passing non-zero 'size' is roughly equivalent to calling SetNextWindowSize(size, ImGuiSetCond_FirstUseEver) prior to calling Begin().
bool ImGui::Begin(const char* name, bool* p_open, ImGuiWindowFlags flags)
{
	return ImGui::Begin(name, p_open, ImVec2(0.f, 0.f), -1.0f, flags);
}

bool ImGui::Begin(const char* name, bool* p_open, const ImVec2& size_on_first_use, float bg_alpha, ImGuiWindowFlags flags)
{
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	IM_ASSERT(name != NULL);                        // Window name required
	IM_ASSERT(g.Initialized);                       // Forgot to call ImGui::NewFrame()
	IM_ASSERT(g.FrameCountEnded != g.FrameCount);   // Called ImGui::Render() or ImGui::EndFrame() and haven't called ImGui::NewFrame() again yet

	if (flags & ImGuiWindowFlags_NoInputs)
		flags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	// Find or create
	bool window_is_new = false;
	ImGuiWindow* window = FindWindowByName(name);
	if (!window)
	{
		window = CreateNewWindow(name, size_on_first_use, flags);
		window_is_new = true;
	}

	const int current_frame = ImGui::GetFrameCount();
	const bool first_begin_of_the_frame = (window->LastFrameActive != current_frame);
	if (first_begin_of_the_frame)
		window->Flags = (ImGuiWindowFlags)flags;
	else
		flags = window->Flags;

	// Add to stack
	ImGuiWindow* parent_window = !g.CurrentWindowStack.empty() ? g.CurrentWindowStack.back() : NULL;
	g.CurrentWindowStack.push_back(window);
	SetCurrentWindow(window);
	CheckStacksSize(window, true);
	IM_ASSERT(parent_window != NULL || !(flags & ImGuiWindowFlags_ChildWindow));

	bool window_was_active = (window->LastFrameActive == current_frame - 1);   // Not using !WasActive because the implicit "Debug" window would always toggle off->on
	if (flags & ImGuiWindowFlags_Popup)
	{
		ImGuiPopupRef& popup_ref = g.OpenPopupStack[g.CurrentPopupStack.Size];
		window_was_active &= (window->PopupId == popup_ref.PopupId);
		window_was_active &= (window == popup_ref.Window);
		popup_ref.Window = window;
		g.CurrentPopupStack.push_back(popup_ref);
		window->PopupId = popup_ref.PopupId;
	}

	const bool window_appearing_after_being_hidden = (window->HiddenFrames == 1);

	// Process SetNextWindow***() calls
	bool window_pos_set_by_api = false, window_size_set_by_api = false;
	if (g.SetNextWindowPosCond)
	{
		const ImVec2 backup_cursor_pos = window->DC.CursorPos;                  // FIXME: not sure of the exact reason of this saving/restore anymore :( need to look into that.
		if (!window_was_active || window_appearing_after_being_hidden) window->SetWindowPosAllowFlags |= ImGuiSetCond_Appearing;
		window_pos_set_by_api = (window->SetWindowPosAllowFlags & g.SetNextWindowPosCond) != 0;
		if (window_pos_set_by_api && ImLengthSqr(g.SetNextWindowPosVal - ImVec2(-FLT_MAX, -FLT_MAX)) < 0.001f)
		{
			window->SetWindowPosCenterWanted = true;                            // May be processed on the next frame if this is our first frame and we are measuring size
			window->SetWindowPosAllowFlags &= ~(ImGuiSetCond_Once | ImGuiSetCond_FirstUseEver | ImGuiSetCond_Appearing);
		}
		else
		{
			SetWindowPos(window, g.SetNextWindowPosVal, g.SetNextWindowPosCond);
		}
		window->DC.CursorPos = backup_cursor_pos;
		g.SetNextWindowPosCond = 0;
	}
	if (g.SetNextWindowSizeCond)
	{
		if (!window_was_active || window_appearing_after_being_hidden) window->SetWindowSizeAllowFlags |= ImGuiSetCond_Appearing;
		window_size_set_by_api = (window->SetWindowSizeAllowFlags & g.SetNextWindowSizeCond) != 0;
		SetWindowSize(window, g.SetNextWindowSizeVal, g.SetNextWindowSizeCond);
		g.SetNextWindowSizeCond = 0;
	}
	if (g.SetNextWindowContentSizeCond)
	{
		window->SizeContentsExplicit = g.SetNextWindowContentSizeVal;
		g.SetNextWindowContentSizeCond = 0;
	}
	else if (first_begin_of_the_frame)
	{
		window->SizeContentsExplicit = ImVec2(0.0f, 0.0f);
	}
	if (g.SetNextWindowCollapsedCond)
	{
		if (!window_was_active || window_appearing_after_being_hidden) window->SetWindowCollapsedAllowFlags |= ImGuiSetCond_Appearing;
		SetWindowCollapsed(window, g.SetNextWindowCollapsedVal, g.SetNextWindowCollapsedCond);
		g.SetNextWindowCollapsedCond = 0;
	}
	if (g.SetNextWindowFocus)
	{
		ImGui::SetWindowFocus();
		g.SetNextWindowFocus = false;
	}

	// Update known root window (if we are a child window, otherwise window == window->RootWindow)
	int root_idx, root_non_popup_idx;
	for (root_idx = g.CurrentWindowStack.Size - 1; root_idx > 0; root_idx--)
		if (!(g.CurrentWindowStack[root_idx]->Flags & ImGuiWindowFlags_ChildWindow))
			break;
	for (root_non_popup_idx = root_idx; root_non_popup_idx > 0; root_non_popup_idx--)
		if (!(g.CurrentWindowStack[root_non_popup_idx]->Flags & (ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_Popup)))
			break;
	window->ParentWindow = parent_window;
	window->RootWindow = g.CurrentWindowStack[root_idx];
	window->RootNonPopupWindow = g.CurrentWindowStack[root_non_popup_idx];      // This is merely for displaying the TitleBgActive color.

																				// When reusing window again multiple times a frame, just append content (don't need to setup again)
	if (first_begin_of_the_frame)
	{
		window->Active = true;
		window->OrderWithinParent = 0;
		window->BeginCount = 0;
		window->ClipRect = ImVec4(-FLT_MAX, -FLT_MAX, +FLT_MAX, +FLT_MAX);
		window->LastFrameActive = current_frame;
		window->IDStack.resize(1);

		// Clear draw list, setup texture, outer clipping rectangle
		window->DrawList->Clear();
		window->DrawList->PushTextureID(g.Font->ContainerAtlas->TexID);
		ImRect fullscreen_rect(GetVisibleRect());
		if ((flags & ImGuiWindowFlags_ChildWindow) && !(flags & (ImGuiWindowFlags_ComboBox | ImGuiWindowFlags_Popup)))
			PushClipRect(parent_window->ClipRect.Min, parent_window->ClipRect.Max, true);
		else
			PushClipRect(fullscreen_rect.Min, fullscreen_rect.Max, true);

		if (!window_was_active)
		{
			// Popup first latch mouse position, will position itself when it appears next frame
			window->AutoPosLastDirection = -1;
			if ((flags & ImGuiWindowFlags_Popup) != 0 && !window_pos_set_by_api)
				window->PosFloat = g.IO.MousePos;
		}

		// Collapse window by double-clicking on title bar
		// At this point we don't have a clipping rectangle setup yet, so we can use the title bar area for hit detection and drawing
		if (!(flags & ImGuiWindowFlags_NoTitleBar) && !(flags & ImGuiWindowFlags_NoCollapse))
		{
			ImRect title_bar_rect = window->TitleBarRect();
			if (g.HoveredWindow == window && IsMouseHoveringRect(title_bar_rect.Min, title_bar_rect.Max) && g.IO.MouseDoubleClicked[0])
			{
				window->Collapsed = !window->Collapsed;
				if (!(flags & ImGuiWindowFlags_NoSavedSettings))
					MarkIniSettingsDirty();
				FocusWindow(window);
			}
		}
		else
		{
			window->Collapsed = false;
		}

		// SIZE

		// Save contents size from last frame for auto-fitting (unless explicitly specified)
		window->SizeContents.x = (float)(int)((window->SizeContentsExplicit.x != 0.0f) ? window->SizeContentsExplicit.x : ((window_is_new ? 0.0f : window->DC.CursorMaxPos.x - window->Pos.x) + window->Scroll.x));
		window->SizeContents.y = (float)(int)((window->SizeContentsExplicit.y != 0.0f) ? window->SizeContentsExplicit.y : ((window_is_new ? 0.0f : window->DC.CursorMaxPos.y - window->Pos.y) + window->Scroll.y));

		// Hide popup/tooltip window when first appearing while we measure size (because we recycle them)
		if (window->HiddenFrames > 0)
			window->HiddenFrames--;
		if ((flags & (ImGuiWindowFlags_Popup | ImGuiWindowFlags_Tooltip)) != 0 && !window_was_active)
		{
			window->HiddenFrames = 1;
			if (flags & ImGuiWindowFlags_AlwaysAutoResize)
			{
				if (!window_size_set_by_api)
					window->Size = window->SizeFull = ImVec2(0.f, 0.f);
				window->SizeContents = ImVec2(0.f, 0.f);
			}
		}

		// Lock window padding so that altering the ShowBorders flag for children doesn't have side-effects.
		window->WindowPadding = ((flags & ImGuiWindowFlags_ChildWindow) && !(flags & (ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_ComboBox | ImGuiWindowFlags_Popup))) ? ImVec2(0, 0) : style.WindowPadding;

		// Calculate auto-fit size
		ImVec2 size_auto_fit;
		if ((flags & ImGuiWindowFlags_Tooltip) != 0)
		{
			// Tooltip always resize. We keep the spacing symmetric on both axises for aesthetic purpose.
			size_auto_fit = window->SizeContents + window->WindowPadding - ImVec2(0.0f, style.ItemSpacing.y);
		}
		else
		{
			size_auto_fit = ImClamp(window->SizeContents + window->WindowPadding, style.WindowMinSize, ImMax(style.WindowMinSize, g.IO.DisplaySize - g.Style.DisplaySafeAreaPadding));

			// Handling case of auto fit window not fitting in screen on one axis, we are growing auto fit size on the other axis to compensate for expected scrollbar. FIXME: Might turn bigger than DisplaySize-WindowPadding.
			if (size_auto_fit.x < window->SizeContents.x && !(flags & ImGuiWindowFlags_NoScrollbar) && (flags & ImGuiWindowFlags_HorizontalScrollbar))
				size_auto_fit.y += style.ScrollbarSize;
			if (size_auto_fit.y < window->SizeContents.y && !(flags & ImGuiWindowFlags_NoScrollbar))
				size_auto_fit.x += style.ScrollbarSize;
			size_auto_fit.y = ImMax(size_auto_fit.y - style.ItemSpacing.y, 0.0f);
		}

		// Handle automatic resize
		if (window->Collapsed)
		{
			// We still process initial auto-fit on collapsed windows to get a window width,
			// But otherwise we don't honor ImGuiWindowFlags_AlwaysAutoResize when collapsed.
			if (window->AutoFitFramesX > 0)
				window->SizeFull.x = window->AutoFitOnlyGrows ? ImMax(window->SizeFull.x, size_auto_fit.x) : size_auto_fit.x;
			if (window->AutoFitFramesY > 0)
				window->SizeFull.y = window->AutoFitOnlyGrows ? ImMax(window->SizeFull.y, size_auto_fit.y) : size_auto_fit.y;
		}
		else
		{
			if ((flags & ImGuiWindowFlags_AlwaysAutoResize) && !window_size_set_by_api)
			{
				window->SizeFull = size_auto_fit;
			}
			else if ((window->AutoFitFramesX > 0 || window->AutoFitFramesY > 0) && !window_size_set_by_api)
			{
				// Auto-fit only grows during the first few frames
				if (window->AutoFitFramesX > 0)
					window->SizeFull.x = window->AutoFitOnlyGrows ? ImMax(window->SizeFull.x, size_auto_fit.x) : size_auto_fit.x;
				if (window->AutoFitFramesY > 0)
					window->SizeFull.y = window->AutoFitOnlyGrows ? ImMax(window->SizeFull.y, size_auto_fit.y) : size_auto_fit.y;
				if (!(flags & ImGuiWindowFlags_NoSavedSettings))
					MarkIniSettingsDirty();
			}
		}

		// Apply minimum/maximum window size constraints and final size
		ApplySizeFullWithConstraint(window, window->SizeFull);
		window->Size = window->Collapsed ? window->TitleBarRect().GetSize() : window->SizeFull;

		// POSITION

		// Position child window
		if (flags & ImGuiWindowFlags_ChildWindow)
		{
			window->OrderWithinParent = parent_window->DC.ChildWindows.Size;
			parent_window->DC.ChildWindows.push_back(window);
		}
		if ((flags & ImGuiWindowFlags_ChildWindow) && !(flags & ImGuiWindowFlags_Popup))
		{
			window->Pos = window->PosFloat = parent_window->DC.CursorPos;
			window->Size = window->SizeFull = size_on_first_use; // NB: argument name 'size_on_first_use' misleading here, it's really just 'size' as provided by user passed via BeginChild()->Begin().
		}

		bool window_pos_center = false;
		window_pos_center |= (window->SetWindowPosCenterWanted && window->HiddenFrames == 0);
		window_pos_center |= ((flags & ImGuiWindowFlags_Modal) && !window_pos_set_by_api && window_appearing_after_being_hidden);
		if (window_pos_center)
		{
			// Center (any sort of window)
			SetWindowPos(window, ImMax(style.DisplaySafeAreaPadding, fullscreen_rect.GetCenter() - window->SizeFull * 0.5f), 0);
		}
		else if (flags & ImGuiWindowFlags_ChildMenu)
		{
			// Child menus typically request _any_ position within the parent menu item, and then our FindBestPopupWindowPos() function will move the new menu outside the parent bounds.
			// This is how we end up with child menus appearing (most-commonly) on the right of the parent menu.
			IM_ASSERT(window_pos_set_by_api);
			float horizontal_overlap = style.ItemSpacing.x; // We want some overlap to convey the relative depth of each popup (currently the amount of overlap it is hard-coded to style.ItemSpacing.x, may need to introduce another style value).
			ImRect rect_to_avoid;
			if (parent_window->DC.MenuBarAppending)
				rect_to_avoid = ImRect(-FLT_MAX, parent_window->Pos.y + parent_window->TitleBarHeight(), FLT_MAX, parent_window->Pos.y + parent_window->TitleBarHeight() + parent_window->MenuBarHeight());
			else
				rect_to_avoid = ImRect(parent_window->Pos.x + horizontal_overlap, -FLT_MAX, parent_window->Pos.x + parent_window->Size.x - horizontal_overlap - parent_window->ScrollbarSizes.x, FLT_MAX);
			window->PosFloat = FindBestPopupWindowPos(window->PosFloat, window->Size, &window->AutoPosLastDirection, rect_to_avoid);
		}
		else if ((flags & ImGuiWindowFlags_Popup) != 0 && !window_pos_set_by_api && window_appearing_after_being_hidden)
		{
			ImRect rect_to_avoid(window->PosFloat.x - 1, window->PosFloat.y - 1, window->PosFloat.x + 1, window->PosFloat.y + 1);
			window->PosFloat = FindBestPopupWindowPos(window->PosFloat, window->Size, &window->AutoPosLastDirection, rect_to_avoid);
		}

		// Position tooltip (always follows mouse)
		if ((flags & ImGuiWindowFlags_Tooltip) != 0 && !window_pos_set_by_api)
		{
			ImRect rect_to_avoid(g.IO.MousePos.x - 16, g.IO.MousePos.y - 8, g.IO.MousePos.x + 24, g.IO.MousePos.y + 24); // FIXME: Completely hard-coded. Perhaps center on cursor hit-point instead?
			window->PosFloat = FindBestPopupWindowPos(g.IO.MousePos, window->Size, &window->AutoPosLastDirection, rect_to_avoid);
			if (window->AutoPosLastDirection == -1)
				window->PosFloat = g.IO.MousePos + ImVec2(2, 2); // If there's not enough room, for tooltip we prefer avoiding the cursor at all cost even if it means that part of the tooltip won't be visible.
		}

		// Clamp position so it stays visible
		if (!(flags & ImGuiWindowFlags_ChildWindow) && !(flags & ImGuiWindowFlags_Tooltip))
		{
			if (!window_pos_set_by_api && window->AutoFitFramesX <= 0 && window->AutoFitFramesY <= 0 && g.IO.DisplaySize.x > 0.0f && g.IO.DisplaySize.y > 0.0f) // Ignore zero-sized display explicitly to avoid losing positions if a window manager reports zero-sized window when initializing or minimizing.
			{
				ImVec2 padding = ImMax(style.DisplayWindowPadding, style.DisplaySafeAreaPadding);
				window->PosFloat = ImMax(window->PosFloat + window->Size, padding) - window->Size;
				window->PosFloat = ImMin(window->PosFloat, g.IO.DisplaySize - padding);
			}
		}
		window->Pos = ImVec2((float)(int)window->PosFloat.x, (float)(int)window->PosFloat.y);

		// Default item width. Make it proportional to window size if window manually resizes
		if (window->Size.x > 0.0f && !(flags & ImGuiWindowFlags_Tooltip) && !(flags & ImGuiWindowFlags_AlwaysAutoResize))
			window->ItemWidthDefault = (float)(int)(window->Size.x * 0.65f);
		else
			window->ItemWidthDefault = (float)(int)(g.FontSize * 16.0f);

		// Prepare for focus requests
		window->FocusIdxAllRequestCurrent = (window->FocusIdxAllRequestNext == INT_MAX || window->FocusIdxAllCounter == -1) ? INT_MAX : (window->FocusIdxAllRequestNext + (window->FocusIdxAllCounter + 1)) % (window->FocusIdxAllCounter + 1);
		window->FocusIdxTabRequestCurrent = (window->FocusIdxTabRequestNext == INT_MAX || window->FocusIdxTabCounter == -1) ? INT_MAX : (window->FocusIdxTabRequestNext + (window->FocusIdxTabCounter + 1)) % (window->FocusIdxTabCounter + 1);
		window->FocusIdxAllCounter = window->FocusIdxTabCounter = -1;
		window->FocusIdxAllRequestNext = window->FocusIdxTabRequestNext = INT_MAX;

		// Apply scrolling
		if (window->ScrollTarget.x < FLT_MAX)
		{
			window->Scroll.x = window->ScrollTarget.x;
			window->ScrollTarget.x = FLT_MAX;
		}
		if (window->ScrollTarget.y < FLT_MAX)
		{
			float center_ratio = window->ScrollTargetCenterRatio.y;
			window->Scroll.y = window->ScrollTarget.y - ((1.0f - center_ratio) * (window->TitleBarHeight() + window->MenuBarHeight())) - (center_ratio * window->SizeFull.y);
			window->ScrollTarget.y = FLT_MAX;
		}
		window->Scroll = ImMax(window->Scroll, ImVec2(0.0f, 0.0f));
		if (!window->Collapsed && !window->SkipItems)
			window->Scroll = ImMin(window->Scroll, ImMax(ImVec2(0.0f, 0.0f), window->SizeContents - window->SizeFull + window->ScrollbarSizes));

		// Modal window darkens what is behind them
		if ((flags & ImGuiWindowFlags_Modal) != 0 && window == GetFrontMostModalRootWindow())
			window->DrawList->AddRectFilled(fullscreen_rect.Min, fullscreen_rect.Max, GetColorU32(ImGuiCol_ModalWindowDarkening, g.ModalWindowDarkeningRatio));

		// Draw window + handle manual resize
		ImRect title_bar_rect = window->TitleBarRect();
		const float window_rounding = (flags & ImGuiWindowFlags_ChildWindow) ? style.ChildWindowRounding : style.WindowRounding;
		if (window->Collapsed)
		{
			// Draw title bar only
			RenderFrame(title_bar_rect.GetTL(), title_bar_rect.GetBR(), GetColorU32(ImGuiCol_TitleBgCollapsed), true, window_rounding);
		}
		else
		{
			ImU32 resize_col = 0;
			const float resize_corner_size = ImMax(g.FontSize * 1.35f, window_rounding + 1.0f + g.FontSize * 0.2f);
			if (!(flags & ImGuiWindowFlags_AlwaysAutoResize) && window->AutoFitFramesX <= 0 && window->AutoFitFramesY <= 0 && !(flags & ImGuiWindowFlags_NoResize))
			{
				// Manual resize
				const ImVec2 br = window->Rect().GetBR();
				const ImRect resize_rect(br - ImVec2(resize_corner_size * 0.75f, resize_corner_size * 0.75f), br);
				const ImGuiID resize_id = window->GetID("#RESIZE");
				bool hovered, held;
				ButtonBehavior(resize_rect, resize_id, &hovered, &held, ImGuiButtonFlags_FlattenChilds);
				resize_col = GetColorU32(held ? ImGuiCol_ResizeGripActive : hovered ? ImGuiCol_ResizeGripHovered : ImGuiCol_ResizeGrip);

				if (hovered || held)
					g.MouseCursor = ImGuiMouseCursor_ResizeNWSE;

				if (g.HoveredWindow == window && held && g.IO.MouseDoubleClicked[0])
				{
					// Manual auto-fit when double-clicking
					ApplySizeFullWithConstraint(window, size_auto_fit);
					if (!(flags & ImGuiWindowFlags_NoSavedSettings))
						MarkIniSettingsDirty();
					ClearActiveID();
				}
				else if (held)
				{
					// We don't use an incremental MouseDelta but rather compute an absolute target size based on mouse position
					ApplySizeFullWithConstraint(window, (g.IO.MousePos - g.ActiveIdClickOffset + resize_rect.GetSize()) - window->Pos);
					if (!(flags & ImGuiWindowFlags_NoSavedSettings))
						MarkIniSettingsDirty();
				}

				window->Size = window->SizeFull;
				title_bar_rect = window->TitleBarRect();
			}

			// Scrollbars
			window->ScrollbarY = (flags & ImGuiWindowFlags_AlwaysVerticalScrollbar) || ((window->SizeContents.y > window->Size.y + style.ItemSpacing.y) && !(flags & ImGuiWindowFlags_NoScrollbar));
			window->ScrollbarX = (flags & ImGuiWindowFlags_AlwaysHorizontalScrollbar) || ((window->SizeContents.x > window->Size.x - (window->ScrollbarY ? style.ScrollbarSize : 0.0f) - window->WindowPadding.x) && !(flags & ImGuiWindowFlags_NoScrollbar) && (flags & ImGuiWindowFlags_HorizontalScrollbar));
			window->ScrollbarSizes = ImVec2(window->ScrollbarY ? style.ScrollbarSize : 0.0f, window->ScrollbarX ? style.ScrollbarSize : 0.0f);
			window->BorderSize = (flags & ImGuiWindowFlags_ShowBorders) ? 1.0f : 0.0f;

			// Window background, Default Alpha
			ImGuiCol bg_color_idx = ImGuiCol_WindowBg;
			if ((flags & ImGuiWindowFlags_ComboBox) != 0)
				bg_color_idx = ImGuiCol_ComboBg;
			else if ((flags & ImGuiWindowFlags_Tooltip) != 0 || (flags & ImGuiWindowFlags_Popup) != 0)
				bg_color_idx = ImGuiCol_PopupBg;
			else if ((flags & ImGuiWindowFlags_ChildWindow) != 0)
				bg_color_idx = ImGuiCol_ChildWindowBg;
			ImVec4 bg_color = style.Colors[bg_color_idx];
			if (bg_alpha >= 0.0f)
				bg_color.w = bg_alpha;
			bg_color.w *= style.Alpha;
			if (bg_color.w > 0.0f)
				window->DrawList->AddRectFilled(window->Pos + ImVec2(0, window->TitleBarHeight()), window->Pos + window->Size, ColorConvertFloat4ToU32(bg_color), window_rounding, (flags & ImGuiWindowFlags_NoTitleBar) ? ImGuiCorner_All : ImGuiCorner_BottomLeft | ImGuiCorner_BottomRight);

			// Title bar
			if (!(flags & ImGuiWindowFlags_NoTitleBar))
				window->DrawList->AddRectFilled(title_bar_rect.GetTL(), title_bar_rect.GetBR(), GetColorU32((g.FocusedWindow && window->RootNonPopupWindow == g.FocusedWindow->RootNonPopupWindow) ? ImGuiCol_TitleBgActive : ImGuiCol_TitleBg), window_rounding, ImGuiCorner_TopLeft | ImGuiCorner_TopRight);

			// Menu bar
			if (flags & ImGuiWindowFlags_MenuBar)
			{
				ImRect menu_bar_rect = window->MenuBarRect();
				if (flags & ImGuiWindowFlags_ShowBorders)
					window->DrawList->AddLine(menu_bar_rect.GetBL(), menu_bar_rect.GetBR(), GetColorU32(ImGuiCol_Border));
				window->DrawList->AddRectFilled(menu_bar_rect.GetTL(), menu_bar_rect.GetBR(), GetColorU32(ImGuiCol_MenuBarBg), (flags & ImGuiWindowFlags_NoTitleBar) ? window_rounding : 0.0f, ImGuiCorner_TopLeft | ImGuiCorner_TopRight);
			}

			// Scrollbars
			if (window->ScrollbarX)
				Scrollbar(window, true);
			if (window->ScrollbarY)
				Scrollbar(window, false);

			// Render resize grip
			// (after the input handling so we don't have a frame of latency)
			if (!(flags & ImGuiWindowFlags_NoResize))
			{
				const ImVec2 br = window->Rect().GetBR();
				window->DrawList->PathLineTo(br + ImVec2(-resize_corner_size, -window->BorderSize));
				window->DrawList->PathLineTo(br + ImVec2(-window->BorderSize, -resize_corner_size));
				window->DrawList->PathArcToFast(ImVec2(br.x - window_rounding - window->BorderSize, br.y - window_rounding - window->BorderSize), window_rounding, 0, 3);
				window->DrawList->PathFillConvex(resize_col);
			}

			// Borders
			if (flags & ImGuiWindowFlags_ShowBorders)
			{
				window->DrawList->AddRect(window->Pos + ImVec2(1, 1), window->Pos + window->Size + ImVec2(1, 1), GetColorU32(ImGuiCol_BorderShadow), window_rounding);
				window->DrawList->AddRect(window->Pos, window->Pos + window->Size, GetColorU32(ImGuiCol_Border), window_rounding);
				if (!(flags & ImGuiWindowFlags_NoTitleBar))
					window->DrawList->AddLine(title_bar_rect.GetBL() + ImVec2(1, 0), title_bar_rect.GetBR() - ImVec2(1, 0), GetColorU32(ImGuiCol_Border));
			}
		}

		// Update ContentsRegionMax. All the variable it depends on are set above in this function.
		window->ContentsRegionRect.Min.x = -window->Scroll.x + window->WindowPadding.x;
		window->ContentsRegionRect.Min.y = -window->Scroll.y + window->WindowPadding.y + window->TitleBarHeight() + window->MenuBarHeight();
		window->ContentsRegionRect.Max.x = -window->Scroll.x - window->WindowPadding.x + (window->SizeContentsExplicit.x != 0.0f ? window->SizeContentsExplicit.x : (window->Size.x - window->ScrollbarSizes.x));
		window->ContentsRegionRect.Max.y = -window->Scroll.y - window->WindowPadding.y + (window->SizeContentsExplicit.y != 0.0f ? window->SizeContentsExplicit.y : (window->Size.y - window->ScrollbarSizes.y));

		// Setup drawing context
		window->DC.IndentX = 0.0f + window->WindowPadding.x - window->Scroll.x;
		window->DC.GroupOffsetX = 0.0f;
		window->DC.ColumnsOffsetX = 0.0f;
		window->DC.CursorStartPos = window->Pos + ImVec2(window->DC.IndentX + window->DC.ColumnsOffsetX, window->TitleBarHeight() + window->MenuBarHeight() + window->WindowPadding.y - window->Scroll.y);
		window->DC.CursorPos = window->DC.CursorStartPos;
		window->DC.CursorPosPrevLine = window->DC.CursorPos;
		window->DC.CursorMaxPos = window->DC.CursorStartPos;
		window->DC.CurrentLineHeight = window->DC.PrevLineHeight = 0.0f;
		window->DC.CurrentLineTextBaseOffset = window->DC.PrevLineTextBaseOffset = 0.0f;
		window->DC.MenuBarAppending = false;
		window->DC.MenuBarOffsetX = ImMax(window->WindowPadding.x, style.ItemSpacing.x);
		window->DC.LogLinePosY = window->DC.CursorPos.y - 9999.0f;
		window->DC.ChildWindows.resize(0);
		window->DC.LayoutType = ImGuiLayoutType_Vertical;
		window->DC.ItemWidth = window->ItemWidthDefault;
		window->DC.TextWrapPos = -1.0f; // disabled
		window->DC.AllowKeyboardFocus = true;
		window->DC.ButtonRepeat = false;
		window->DC.ItemWidthStack.resize(0);
		window->DC.AllowKeyboardFocusStack.resize(0);
		window->DC.ButtonRepeatStack.resize(0);
		window->DC.TextWrapPosStack.resize(0);
		window->DC.ColumnsCurrent = 0;
		window->DC.ColumnsCount = 1;
		window->DC.ColumnsStartPosY = window->DC.CursorPos.y;
		window->DC.ColumnsCellMinY = window->DC.ColumnsCellMaxY = window->DC.ColumnsStartPosY;
		window->DC.TreeDepth = 0;
		window->DC.StateStorage = &window->StateStorage;
		window->DC.GroupStack.resize(0);
		window->DC.ColorEditMode = ImGuiColorEditMode_UserSelect;
		window->MenuColumns.Update(3, style.ItemSpacing.x, !window_was_active);

		if (window->AutoFitFramesX > 0)
			window->AutoFitFramesX--;
		if (window->AutoFitFramesY > 0)
			window->AutoFitFramesY--;

		// New windows appears in front (we need to do that AFTER setting DC.CursorStartPos so our initial navigation reference rectangle can start around there)
		if (!window_was_active && !(flags & ImGuiWindowFlags_NoFocusOnAppearing))
			if (!(flags & (ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_Tooltip)) || (flags & ImGuiWindowFlags_Popup))
				FocusWindow(window);

		// Title bar
		if (!(flags & ImGuiWindowFlags_NoTitleBar))
		{
			if (p_open != NULL)
			{
				const float pad = 2.0f;
				const float rad = (window->TitleBarHeight() - pad * 2.0f) * 0.5f;
				if (CloseButton(window->GetID("#CLOSE"), window->Rect().GetTR() + ImVec2(-pad - rad, pad + rad), rad))
					*p_open = false;
			}

			const ImVec2 text_size = CalcTextSize(name, NULL, true);
			if (!(flags & ImGuiWindowFlags_NoCollapse))
				RenderCollapseTriangle(window->Pos + style.FramePadding, !window->Collapsed, 1.0f);

			ImVec2 text_min = window->Pos;
			ImVec2 text_max = window->Pos + ImVec2(window->Size.x, style.FramePadding.y * 2 + text_size.y);
			ImRect clip_rect;
			clip_rect.Max = ImVec2(window->Pos.x + window->Size.x - (p_open ? title_bar_rect.GetHeight() - 3 : style.FramePadding.x), text_max.y); // Match the size of CloseWindowButton()
			float pad_left = (flags & ImGuiWindowFlags_NoCollapse) == 0 ? (style.FramePadding.x + g.FontSize + style.ItemInnerSpacing.x) : style.FramePadding.x;
			float pad_right = (p_open != NULL) ? (style.FramePadding.x + g.FontSize + style.ItemInnerSpacing.x) : style.FramePadding.x;
			if (style.WindowTitleAlign.x > 0.0f) pad_right = ImLerp(pad_right, pad_left, style.WindowTitleAlign.x);
			text_min.x += pad_left;
			text_max.x -= pad_right;
			clip_rect.Min = ImVec2(text_min.x, window->Pos.y);
			RenderTextClipped(text_min, text_max, name, NULL, &text_size, style.WindowTitleAlign, &clip_rect);
		}

		// Save clipped aabb so we can access it in constant-time in FindHoveredWindow()
		window->WindowRectClipped = window->Rect();
		window->WindowRectClipped.Clip(window->ClipRect);

		// Pressing CTRL+C while holding on a window copy its content to the clipboard
		// This works but 1. doesn't handle multiple Begin/End pairs, 2. recursing into another Begin/End pair - so we need to work that out and add better logging scope.
		// Maybe we can support CTRL+C on every element?
		/*
		if (g.ActiveId == move_id)
		if (g.IO.KeyCtrl && IsKeyPressedMap(ImGuiKey_C))
		ImGui::LogToClipboard();
		*/
	}

	// Inner clipping rectangle
	// We set this up after processing the resize grip so that our clip rectangle doesn't lag by a frame
	// Note that if our window is collapsed we will end up with a null clipping rectangle which is the correct behavior.
	const ImRect title_bar_rect = window->TitleBarRect();
	const float border_size = window->BorderSize;
	ImRect clip_rect; // Force round to ensure that e.g. (int)(max.x-min.x) in user's render code produce correct result.
	clip_rect.Min.x = ImFloor(0.5f + title_bar_rect.Min.x + ImMax(border_size, ImFloor(window->WindowPadding.x*0.5f)));
	clip_rect.Min.y = ImFloor(0.5f + title_bar_rect.Max.y + window->MenuBarHeight() + border_size);
	clip_rect.Max.x = ImFloor(0.5f + window->Pos.x + window->Size.x - window->ScrollbarSizes.x - ImMax(border_size, ImFloor(window->WindowPadding.x*0.5f)));
	clip_rect.Max.y = ImFloor(0.5f + window->Pos.y + window->Size.y - window->ScrollbarSizes.y - border_size);
	PushClipRect(clip_rect.Min, clip_rect.Max, true);

	// Clear 'accessed' flag last thing
	if (first_begin_of_the_frame)
		window->Accessed = false;
	window->BeginCount++;
	g.SetNextWindowSizeConstraint = false;

	// Child window can be out of sight and have "negative" clip windows.
	// Mark them as collapsed so commands are skipped earlier (we can't manually collapse because they have no title bar).
	if (flags & ImGuiWindowFlags_ChildWindow)
	{
		IM_ASSERT((flags & ImGuiWindowFlags_NoTitleBar) != 0);
		window->Collapsed = parent_window && parent_window->Collapsed;

		if (!(flags & ImGuiWindowFlags_AlwaysAutoResize) && window->AutoFitFramesX <= 0 && window->AutoFitFramesY <= 0)
			window->Collapsed |= (window->WindowRectClipped.Min.x >= window->WindowRectClipped.Max.x || window->WindowRectClipped.Min.y >= window->WindowRectClipped.Max.y);

		// We also hide the window from rendering because we've already added its border to the command list.
		// (we could perform the check earlier in the function but it is simpler at this point)
		if (window->Collapsed)
			window->Active = false;
	}
	if (style.Alpha <= 0.0f)
		window->Active = false;

	// Return false if we don't intend to display anything to allow user to perform an early out optimization
	window->SkipItems = (window->Collapsed || !window->Active) && window->AutoFitFramesX <= 0 && window->AutoFitFramesY <= 0;
	return !window->SkipItems;
}

void ImGui::End()
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;

	if (window->DC.ColumnsCount != 1) // close columns set if any is open
		Columns(1, "#CLOSECOLUMNS");
	PopClipRect();   // inner window clip rectangle

					 // Stop logging
	if (!(window->Flags & ImGuiWindowFlags_ChildWindow))    // FIXME: add more options for scope of logging
		LogFinish();

	// Pop
	// NB: we don't clear 'window->RootWindow'. The pointer is allowed to live until the next call to Begin().
	g.CurrentWindowStack.pop_back();
	if (window->Flags & ImGuiWindowFlags_Popup)
		g.CurrentPopupStack.pop_back();
	CheckStacksSize(window, false);
	SetCurrentWindow(g.CurrentWindowStack.empty() ? NULL : g.CurrentWindowStack.back());
}

// Vertical scrollbar
// The entire piece of code below is rather confusing because:
// - We handle absolute seeking (when first clicking outside the grab) and relative manipulation (afterward or when clicking inside the grab)
// - We store values as normalized ratio and in a form that allows the window content to change while we are holding on a scrollbar
// - We handle both horizontal and vertical scrollbars, which makes the terminology not ideal.
static void Scrollbar(ImGuiWindow* window, bool horizontal)
{
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(horizontal ? "#SCROLLX" : "#SCROLLY");

	// Render background
	bool other_scrollbar = (horizontal ? window->ScrollbarY : window->ScrollbarX);
	float other_scrollbar_size_w = other_scrollbar ? style.ScrollbarSize : 0.0f;
	const ImRect window_rect = window->Rect();
	const float border_size = window->BorderSize;
	ImRect bb = horizontal
		? ImRect(window->Pos.x + border_size, window_rect.Max.y - style.ScrollbarSize, window_rect.Max.x - other_scrollbar_size_w - border_size, window_rect.Max.y - border_size)
		: ImRect(window_rect.Max.x - style.ScrollbarSize, window->Pos.y + border_size, window_rect.Max.x - border_size, window_rect.Max.y - other_scrollbar_size_w - border_size);
	if (!horizontal)
		bb.Min.y += window->TitleBarHeight() + ((window->Flags & ImGuiWindowFlags_MenuBar) ? window->MenuBarHeight() : 0.0f);
	if (bb.GetWidth() <= 0.0f || bb.GetHeight() <= 0.0f)
		return;

	float window_rounding = (window->Flags & ImGuiWindowFlags_ChildWindow) ? style.ChildWindowRounding : style.WindowRounding;
	int window_rounding_corners;
	if (horizontal)
		window_rounding_corners = ImGuiCorner_BottomLeft | (other_scrollbar ? 0 : ImGuiCorner_BottomRight);
	else
		window_rounding_corners = (((window->Flags & ImGuiWindowFlags_NoTitleBar) && !(window->Flags & ImGuiWindowFlags_MenuBar)) ? ImGuiCorner_TopRight : 0) | (other_scrollbar ? 0 : ImGuiCorner_BottomRight);
	window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ScrollbarBg), window_rounding, window_rounding_corners);
	bb.Reduce(ImVec2(ImClamp((float)(int)((bb.Max.x - bb.Min.x - 2.0f) * 0.5f), 0.0f, 3.0f), ImClamp((float)(int)((bb.Max.y - bb.Min.y - 2.0f) * 0.5f), 0.0f, 3.0f)));

	// V denote the main axis of the scrollbar
	float scrollbar_size_v = horizontal ? bb.GetWidth() : bb.GetHeight();
	float scroll_v = horizontal ? window->Scroll.x : window->Scroll.y;
	float win_size_avail_v = (horizontal ? window->Size.x : window->Size.y) - other_scrollbar_size_w;
	float win_size_contents_v = horizontal ? window->SizeContents.x : window->SizeContents.y;

	// The grabable box size generally represent the amount visible (vs the total scrollable amount)
	// But we maintain a minimum size in pixel to allow for the user to still aim inside.
	const float grab_h_pixels = ImMin(ImMax(scrollbar_size_v * ImSaturate(win_size_avail_v / ImMax(win_size_contents_v, win_size_avail_v)), style.GrabMinSize), scrollbar_size_v);
	const float grab_h_norm = grab_h_pixels / scrollbar_size_v;

	// Handle input right away. None of the code of Begin() is relying on scrolling position before calling Scrollbar().
	bool held = false;
	bool hovered = false;
	const bool previously_held = (g.ActiveId == id);
	ImGui::ButtonBehavior(bb, id, &hovered, &held);

	float scroll_max = ImMax(1.0f, win_size_contents_v - win_size_avail_v);
	float scroll_ratio = ImSaturate(scroll_v / scroll_max);
	float grab_v_norm = scroll_ratio * (scrollbar_size_v - grab_h_pixels) / scrollbar_size_v;
	if (held && grab_h_norm < 1.0f)
	{
		float scrollbar_pos_v = horizontal ? bb.Min.x : bb.Min.y;
		float mouse_pos_v = horizontal ? g.IO.MousePos.x : g.IO.MousePos.y;
		float* click_delta_to_grab_center_v = horizontal ? &g.ScrollbarClickDeltaToGrabCenter.x : &g.ScrollbarClickDeltaToGrabCenter.y;

		// Click position in scrollbar normalized space (0.0f->1.0f)
		const float clicked_v_norm = ImSaturate((mouse_pos_v - scrollbar_pos_v) / scrollbar_size_v);
		ImGui::SetHoveredID(id);

		bool seek_absolute = false;
		if (!previously_held)
		{
			// On initial click calculate the distance between mouse and the center of the grab
			if (clicked_v_norm >= grab_v_norm && clicked_v_norm <= grab_v_norm + grab_h_norm)
			{
				*click_delta_to_grab_center_v = clicked_v_norm - grab_v_norm - grab_h_norm * 0.5f;
			}
			else
			{
				seek_absolute = true;
				*click_delta_to_grab_center_v = 0.0f;
			}
		}

		// Apply scroll
		// It is ok to modify Scroll here because we are being called in Begin() after the calculation of SizeContents and before setting up our starting position
		const float scroll_v_norm = ImSaturate((clicked_v_norm - *click_delta_to_grab_center_v - grab_h_norm * 0.5f) / (1.0f - grab_h_norm));
		scroll_v = (float)(int)(0.5f + scroll_v_norm * scroll_max);//(win_size_contents_v - win_size_v));
		if (horizontal)
			window->Scroll.x = scroll_v;
		else
			window->Scroll.y = scroll_v;

		// Update values for rendering
		scroll_ratio = ImSaturate(scroll_v / scroll_max);
		grab_v_norm = scroll_ratio * (scrollbar_size_v - grab_h_pixels) / scrollbar_size_v;

		// Update distance to grab now that we have seeked and saturated
		if (seek_absolute)
			*click_delta_to_grab_center_v = clicked_v_norm - grab_v_norm - grab_h_norm * 0.5f;
	}

	// Render
	const ImU32 grab_col = ImGui::GetColorU32(held ? ImGuiCol_ScrollbarGrabActive : hovered ? ImGuiCol_ScrollbarGrabHovered : ImGuiCol_ScrollbarGrab);
	if (horizontal)
		window->DrawList->AddRectFilled(ImVec2(ImLerp(bb.Min.x, bb.Max.x, grab_v_norm), bb.Min.y), ImVec2(ImLerp(bb.Min.x, bb.Max.x, grab_v_norm) + grab_h_pixels, bb.Max.y), grab_col, style.ScrollbarRounding);
	else
		window->DrawList->AddRectFilled(ImVec2(bb.Min.x, ImLerp(bb.Min.y, bb.Max.y, grab_v_norm)), ImVec2(bb.Max.x, ImLerp(bb.Min.y, bb.Max.y, grab_v_norm) + grab_h_pixels), grab_col, style.ScrollbarRounding);
}

// Moving window to front of display (which happens to be back of our sorted list)
void ImGui::FocusWindow(ImGuiWindow* window)
{
	ImGuiContext& g = *GImGui;

	// Always mark the window we passed as focused. This is used for keyboard interactions such as tabbing.
	g.FocusedWindow = window;

	// Passing NULL allow to disable keyboard focus
	if (!window)
		return;

	// And move its root window to the top of the pile
	if (window->RootWindow)
		window = window->RootWindow;

	// Steal focus on active widgets
	if (window->Flags & ImGuiWindowFlags_Popup) // FIXME: This statement should be unnecessary. Need further testing before removing it..
		if (g.ActiveId != 0 && g.ActiveIdWindow && g.ActiveIdWindow->RootWindow != window)
			ClearActiveID();

	// Bring to front
	if ((window->Flags & ImGuiWindowFlags_NoBringToFrontOnFocus) || g.Windows.back() == window)
		return;
	for (int i = 0; i < g.Windows.Size; i++)
		if (g.Windows[i] == window)
		{
			g.Windows.erase(g.Windows.begin() + i);
			break;
		}
	g.Windows.push_back(window);
}

void ImGui::PushItemWidth(float item_width)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.ItemWidth = (item_width == 0.0f ? window->ItemWidthDefault : item_width);
	window->DC.ItemWidthStack.push_back(window->DC.ItemWidth);
}

static void PushMultiItemsWidths(int components, float w_full)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	const ImGuiStyle& style = GImGui->Style;
	if (w_full <= 0.0f)
		w_full = ImGui::CalcItemWidth();
	const float w_item_one = ImMax(1.0f, (float)(int)((w_full - (style.ItemInnerSpacing.x) * (components - 1)) / (float)components));
	const float w_item_last = ImMax(1.0f, (float)(int)(w_full - (w_item_one + style.ItemInnerSpacing.x) * (components - 1)));
	window->DC.ItemWidthStack.push_back(w_item_last);
	for (int i = 0; i < components - 1; i++)
		window->DC.ItemWidthStack.push_back(w_item_one);
	window->DC.ItemWidth = window->DC.ItemWidthStack.back();
}

void ImGui::PopItemWidth()
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.ItemWidthStack.pop_back();
	window->DC.ItemWidth = window->DC.ItemWidthStack.empty() ? window->ItemWidthDefault : window->DC.ItemWidthStack.back();
}

float ImGui::CalcItemWidth()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	float w = window->DC.ItemWidth;
	if (w < 0.0f)
	{
		// Align to a right-side limit. We include 1 frame padding in the calculation because this is how the width is always used (we add 2 frame padding to it), but we could move that responsibility to the widget as well.
		float width_to_right_edge = GetContentRegionAvail().x;
		w = ImMax(1.0f, width_to_right_edge + w);
	}
	w = (float)(int)w;
	return w;
}

static ImFont* GetDefaultFont()
{
	ImGuiContext& g = *GImGui;
	return g.IO.FontDefault ? g.IO.FontDefault : g.IO.Fonts->Fonts[0];
}

static void SetCurrentFont(ImFont* font)
{
	ImGuiContext& g = *GImGui;
	IM_ASSERT(font && font->IsLoaded());    // Font Atlas not created. Did you call io.Fonts->GetTexDataAsRGBA32 / GetTexDataAsAlpha8 ?
	IM_ASSERT(font->Scale > 0.0f);
	g.Font = font;
	g.FontBaseSize = g.IO.FontGlobalScale * g.Font->FontSize * g.Font->Scale;
	g.FontSize = g.CurrentWindow ? g.CurrentWindow->CalcFontSize() : 0.0f;
	g.FontTexUvWhitePixel = g.Font->ContainerAtlas->TexUvWhitePixel;
}

void ImGui::PushFont(ImFont* font)
{
	ImGuiContext& g = *GImGui;
	if (!font)
		font = GetDefaultFont();
	SetCurrentFont(font);
	g.FontStack.push_back(font);
	g.CurrentWindow->DrawList->PushTextureID(font->ContainerAtlas->TexID);
}

void  ImGui::PopFont()
{
	ImGuiContext& g = *GImGui;
	g.CurrentWindow->DrawList->PopTextureID();
	g.FontStack.pop_back();
	SetCurrentFont(g.FontStack.empty() ? GetDefaultFont() : g.FontStack.back());
}

void ImGui::PushAllowKeyboardFocus(bool allow_keyboard_focus)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.AllowKeyboardFocus = allow_keyboard_focus;
	window->DC.AllowKeyboardFocusStack.push_back(allow_keyboard_focus);
}

void ImGui::PopAllowKeyboardFocus()
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.AllowKeyboardFocusStack.pop_back();
	window->DC.AllowKeyboardFocus = window->DC.AllowKeyboardFocusStack.empty() ? true : window->DC.AllowKeyboardFocusStack.back();
}

void ImGui::PushButtonRepeat(bool repeat)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.ButtonRepeat = repeat;
	window->DC.ButtonRepeatStack.push_back(repeat);
}

void ImGui::PopButtonRepeat()
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.ButtonRepeatStack.pop_back();
	window->DC.ButtonRepeat = window->DC.ButtonRepeatStack.empty() ? false : window->DC.ButtonRepeatStack.back();
}

void ImGui::PushTextWrapPos(float wrap_pos_x)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.TextWrapPos = wrap_pos_x;
	window->DC.TextWrapPosStack.push_back(wrap_pos_x);
}

void ImGui::PopTextWrapPos()
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.TextWrapPosStack.pop_back();
	window->DC.TextWrapPos = window->DC.TextWrapPosStack.empty() ? -1.0f : window->DC.TextWrapPosStack.back();
}

void ImGui::PushStyleColor(ImGuiCol idx, const ImVec4& col)
{
	ImGuiContext& g = *GImGui;
	ImGuiColMod backup;
	backup.Col = idx;
	backup.BackupValue = g.Style.Colors[idx];
	g.ColorModifiers.push_back(backup);
	g.Style.Colors[idx] = col;
}

void ImGui::PopStyleColor(int count)
{
	ImGuiContext& g = *GImGui;
	while (count > 0)
	{
		ImGuiColMod& backup = g.ColorModifiers.back();
		g.Style.Colors[backup.Col] = backup.BackupValue;
		g.ColorModifiers.pop_back();
		count--;
	}
}

struct ImGuiStyleVarInfo
{
	ImGuiDataType   Type;
	ImU32           Offset;
	void*           GetVarPtr() const { return (void*)((unsigned char*)&GImGui->Style + Offset); }
};

static const ImGuiStyleVarInfo GStyleVarInfo[ImGuiStyleVar_Count_] =
{
	{ ImGuiDataType_Float,  (ImU32)IM_OFFSETOF(ImGuiStyle, Alpha) },                // ImGuiStyleVar_Alpha
{ ImGuiDataType_Float2, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowPadding) },        // ImGuiStyleVar_WindowPadding
{ ImGuiDataType_Float,  (ImU32)IM_OFFSETOF(ImGuiStyle, WindowRounding) },       // ImGuiStyleVar_WindowRounding
{ ImGuiDataType_Float2, (ImU32)IM_OFFSETOF(ImGuiStyle, WindowMinSize) },        // ImGuiStyleVar_WindowMinSize
{ ImGuiDataType_Float,  (ImU32)IM_OFFSETOF(ImGuiStyle, ChildWindowRounding) },  // ImGuiStyleVar_ChildWindowRounding
{ ImGuiDataType_Float2, (ImU32)IM_OFFSETOF(ImGuiStyle, FramePadding) },         // ImGuiStyleVar_FramePadding
{ ImGuiDataType_Float,  (ImU32)IM_OFFSETOF(ImGuiStyle, FrameRounding) },        // ImGuiStyleVar_FrameRounding
{ ImGuiDataType_Float2, (ImU32)IM_OFFSETOF(ImGuiStyle, ItemSpacing) },          // ImGuiStyleVar_ItemSpacing
{ ImGuiDataType_Float2, (ImU32)IM_OFFSETOF(ImGuiStyle, ItemInnerSpacing) },     // ImGuiStyleVar_ItemInnerSpacing
{ ImGuiDataType_Float,  (ImU32)IM_OFFSETOF(ImGuiStyle, IndentSpacing) },        // ImGuiStyleVar_IndentSpacing
{ ImGuiDataType_Float,  (ImU32)IM_OFFSETOF(ImGuiStyle, GrabMinSize) },          // ImGuiStyleVar_GrabMinSize
{ ImGuiDataType_Float2, (ImU32)IM_OFFSETOF(ImGuiStyle, ButtonTextAlign) },      // ImGuiStyleVar_ButtonTextAlign
};

static const ImGuiStyleVarInfo* GetStyleVarInfo(ImGuiStyleVar idx)
{
	IM_ASSERT(idx >= 0 && idx < ImGuiStyleVar_Count_);
	return &GStyleVarInfo[idx];
}

void ImGui::PushStyleVar(ImGuiStyleVar idx, float val)
{
	const ImGuiStyleVarInfo* var_info = GetStyleVarInfo(idx);
	if (var_info->Type == ImGuiDataType_Float)
	{
		float* pvar = (float*)var_info->GetVarPtr();
		GImGui->StyleModifiers.push_back(ImGuiStyleMod(idx, *pvar));
		*pvar = val;
		return;
	}
	IM_ASSERT(0); // Called function with wrong-type? Variable is not a float.
}

void ImGui::PushStyleVar(ImGuiStyleVar idx, const ImVec2& val)
{
	const ImGuiStyleVarInfo* var_info = GetStyleVarInfo(idx);
	if (var_info->Type == ImGuiDataType_Float2)
	{
		ImVec2* pvar = (ImVec2*)var_info->GetVarPtr();
		GImGui->StyleModifiers.push_back(ImGuiStyleMod(idx, *pvar));
		*pvar = val;
		return;
	}
	IM_ASSERT(0); // Called function with wrong-type? Variable is not a ImVec2.
}

void ImGui::PopStyleVar(int count)
{
	ImGuiContext& g = *GImGui;
	while (count > 0)
	{
		ImGuiStyleMod& backup = g.StyleModifiers.back();
		const ImGuiStyleVarInfo* info = GetStyleVarInfo(backup.VarIdx);
		if (info->Type == ImGuiDataType_Float)          (*(float*)info->GetVarPtr()) = backup.BackupFloat[0];
		else if (info->Type == ImGuiDataType_Float2)    (*(ImVec2*)info->GetVarPtr()) = ImVec2(backup.BackupFloat[0], backup.BackupFloat[1]);
		else if (info->Type == ImGuiDataType_Int)       (*(int*)info->GetVarPtr()) = backup.BackupInt[0];
		g.StyleModifiers.pop_back();
		count--;
	}
}

const char* ImGui::GetStyleColName(ImGuiCol idx)
{
	// Create switch-case from enum with regexp: ImGuiCol_{.*}, --> case ImGuiCol_\1: return "\1";
	switch (idx)
	{
	case ImGuiCol_Text: return "Text";
	case ImGuiCol_TextDisabled: return "TextDisabled";
	case ImGuiCol_WindowBg: return "WindowBg";
	case ImGuiCol_ChildWindowBg: return "ChildWindowBg";
	case ImGuiCol_PopupBg: return "PopupBg";
	case ImGuiCol_Border: return "Border";
	case ImGuiCol_BorderShadow: return "BorderShadow";
	case ImGuiCol_FrameBg: return "FrameBg";
	case ImGuiCol_FrameBgHovered: return "FrameBgHovered";
	case ImGuiCol_FrameBgActive: return "FrameBgActive";
	case ImGuiCol_TitleBg: return "TitleBg";
	case ImGuiCol_TitleBgCollapsed: return "TitleBgCollapsed";
	case ImGuiCol_TitleBgActive: return "TitleBgActive";
	case ImGuiCol_MenuBarBg: return "MenuBarBg";
	case ImGuiCol_ScrollbarBg: return "ScrollbarBg";
	case ImGuiCol_ScrollbarGrab: return "ScrollbarGrab";
	case ImGuiCol_ScrollbarGrabHovered: return "ScrollbarGrabHovered";
	case ImGuiCol_ScrollbarGrabActive: return "ScrollbarGrabActive";
	case ImGuiCol_ComboBg: return "ComboBg";
	case ImGuiCol_CheckMark: return "CheckMark";
	case ImGuiCol_SliderGrab: return "SliderGrab";
	case ImGuiCol_SliderGrabActive: return "SliderGrabActive";
	case ImGuiCol_Button: return "Button";
	case ImGuiCol_ButtonHovered: return "ButtonHovered";
	case ImGuiCol_ButtonActive: return "ButtonActive";
	case ImGuiCol_Header: return "Header";
	case ImGuiCol_HeaderHovered: return "HeaderHovered";
	case ImGuiCol_HeaderActive: return "HeaderActive";
	case ImGuiCol_Column: return "Column";
	case ImGuiCol_ColumnHovered: return "ColumnHovered";
	case ImGuiCol_ColumnActive: return "ColumnActive";
	case ImGuiCol_ResizeGrip: return "ResizeGrip";
	case ImGuiCol_ResizeGripHovered: return "ResizeGripHovered";
	case ImGuiCol_ResizeGripActive: return "ResizeGripActive";
	case ImGuiCol_CloseButton: return "CloseButton";
	case ImGuiCol_CloseButtonHovered: return "CloseButtonHovered";
	case ImGuiCol_CloseButtonActive: return "CloseButtonActive";
	case ImGuiCol_PlotLines: return "PlotLines";
	case ImGuiCol_PlotLinesHovered: return "PlotLinesHovered";
	case ImGuiCol_PlotHistogram: return "PlotHistogram";
	case ImGuiCol_PlotHistogramHovered: return "PlotHistogramHovered";
	case ImGuiCol_TextSelectedBg: return "TextSelectedBg";
	case ImGuiCol_ModalWindowDarkening: return "ModalWindowDarkening";
	}
	IM_ASSERT(0);
	return "Unknown";
}

bool ImGui::IsWindowHovered()
{
	ImGuiContext& g = *GImGui;
	return g.HoveredWindow == g.CurrentWindow && IsWindowContentHoverable(g.HoveredRootWindow);
}

bool ImGui::IsWindowFocused()
{
	ImGuiContext& g = *GImGui;
	return g.FocusedWindow == g.CurrentWindow;
}

bool ImGui::IsRootWindowFocused()
{
	ImGuiContext& g = *GImGui;
	return g.FocusedWindow == g.CurrentWindow->RootWindow;
}

bool ImGui::IsRootWindowOrAnyChildFocused()
{
	ImGuiContext& g = *GImGui;
	return g.FocusedWindow && g.FocusedWindow->RootWindow == g.CurrentWindow->RootWindow;
}

bool ImGui::IsRootWindowOrAnyChildHovered()
{
	ImGuiContext& g = *GImGui;
	return g.HoveredRootWindow && (g.HoveredRootWindow == g.CurrentWindow->RootWindow) && IsWindowContentHoverable(g.HoveredRootWindow);
}

float ImGui::GetWindowWidth()
{
	ImGuiWindow* window = GImGui->CurrentWindow;
	return window->Size.x;
}

float ImGui::GetWindowHeight()
{
	ImGuiWindow* window = GImGui->CurrentWindow;
	return window->Size.y;
}

ImVec2 ImGui::GetWindowPos()
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	return window->Pos;
}

static void SetWindowScrollY(ImGuiWindow* window, float new_scroll_y)
{
	window->DC.CursorMaxPos.y += window->Scroll.y;
	window->Scroll.y = new_scroll_y;
	window->DC.CursorMaxPos.y -= window->Scroll.y;
}

static void SetWindowPos(ImGuiWindow* window, const ImVec2& pos, ImGuiSetCond cond)
{
	// Test condition (NB: bit 0 is always true) and clear flags for next time
	if (cond && (window->SetWindowPosAllowFlags & cond) == 0)
		return;
	window->SetWindowPosAllowFlags &= ~(ImGuiSetCond_Once | ImGuiSetCond_FirstUseEver | ImGuiSetCond_Appearing);
	window->SetWindowPosCenterWanted = false;

	// Set
	const ImVec2 old_pos = window->Pos;
	window->PosFloat = pos;
	window->Pos = ImVec2((float)(int)window->PosFloat.x, (float)(int)window->PosFloat.y);
	window->DC.CursorPos += (window->Pos - old_pos);    // As we happen to move the window while it is being appended to (which is a bad idea - will smear) let's at least offset the cursor
	window->DC.CursorMaxPos += (window->Pos - old_pos); // And more importantly we need to adjust this so size calculation doesn't get affected.
}

void ImGui::SetWindowPos(const ImVec2& pos, ImGuiSetCond cond)
{
	ImGuiWindow* window = GetCurrentWindowRead();
	SetWindowPos(window, pos, cond);
}

void ImGui::SetWindowPos(const char* name, const ImVec2& pos, ImGuiSetCond cond)
{
	if (ImGuiWindow* window = FindWindowByName(name))
		SetWindowPos(window, pos, cond);
}

ImVec2 ImGui::GetWindowSize()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->Size;
}

static void SetWindowSize(ImGuiWindow* window, const ImVec2& size, ImGuiSetCond cond)
{
	// Test condition (NB: bit 0 is always true) and clear flags for next time
	if (cond && (window->SetWindowSizeAllowFlags & cond) == 0)
		return;
	window->SetWindowSizeAllowFlags &= ~(ImGuiSetCond_Once | ImGuiSetCond_FirstUseEver | ImGuiSetCond_Appearing);

	// Set
	if (size.x > 0.0f)
	{
		window->AutoFitFramesX = 0;
		window->SizeFull.x = size.x;
	}
	else
	{
		window->AutoFitFramesX = 2;
		window->AutoFitOnlyGrows = false;
	}
	if (size.y > 0.0f)
	{
		window->AutoFitFramesY = 0;
		window->SizeFull.y = size.y;
	}
	else
	{
		window->AutoFitFramesY = 2;
		window->AutoFitOnlyGrows = false;
	}
}

void ImGui::SetWindowSize(const ImVec2& size, ImGuiSetCond cond)
{
	SetWindowSize(GImGui->CurrentWindow, size, cond);
}

void ImGui::SetWindowSize(const char* name, const ImVec2& size, ImGuiSetCond cond)
{
	ImGuiWindow* window = FindWindowByName(name);
	if (window)
		SetWindowSize(window, size, cond);
}

static void SetWindowCollapsed(ImGuiWindow* window, bool collapsed, ImGuiSetCond cond)
{
	// Test condition (NB: bit 0 is always true) and clear flags for next time
	if (cond && (window->SetWindowCollapsedAllowFlags & cond) == 0)
		return;
	window->SetWindowCollapsedAllowFlags &= ~(ImGuiSetCond_Once | ImGuiSetCond_FirstUseEver | ImGuiSetCond_Appearing);

	// Set
	window->Collapsed = collapsed;
}

void ImGui::SetWindowCollapsed(bool collapsed, ImGuiSetCond cond)
{
	SetWindowCollapsed(GImGui->CurrentWindow, collapsed, cond);
}

bool ImGui::IsWindowCollapsed()
{
	return GImGui->CurrentWindow->Collapsed;
}

void ImGui::SetWindowCollapsed(const char* name, bool collapsed, ImGuiSetCond cond)
{
	ImGuiWindow* window = FindWindowByName(name);
	if (window)
		SetWindowCollapsed(window, collapsed, cond);
}

void ImGui::SetWindowFocus()
{
	FocusWindow(GImGui->CurrentWindow);
}

void ImGui::SetWindowFocus(const char* name)
{
	if (name)
	{
		if (ImGuiWindow* window = FindWindowByName(name))
			FocusWindow(window);
	}
	else
	{
		FocusWindow(NULL);
	}
}

void ImGui::SetNextWindowPos(const ImVec2& pos, ImGuiSetCond cond)
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowPosVal = pos;
	g.SetNextWindowPosCond = cond ? cond : ImGuiSetCond_Always;
}

void ImGui::SetNextWindowPosCenter(ImGuiSetCond cond)
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowPosVal = ImVec2(-FLT_MAX, -FLT_MAX);
	g.SetNextWindowPosCond = cond ? cond : ImGuiSetCond_Always;
}

void ImGui::SetNextWindowSize(const ImVec2& size, ImGuiSetCond cond)
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowSizeVal = size;
	g.SetNextWindowSizeCond = cond ? cond : ImGuiSetCond_Always;
}

void ImGui::SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeConstraintCallback custom_callback, void* custom_callback_user_data)
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowSizeConstraint = true;
	g.SetNextWindowSizeConstraintRect = ImRect(size_min, size_max);
	g.SetNextWindowSizeConstraintCallback = custom_callback;
	g.SetNextWindowSizeConstraintCallbackUserData = custom_callback_user_data;
}

void ImGui::SetNextWindowContentSize(const ImVec2& size)
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowContentSizeVal = size;
	g.SetNextWindowContentSizeCond = ImGuiSetCond_Always;
}

void ImGui::SetNextWindowContentWidth(float width)
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowContentSizeVal = ImVec2(width, g.SetNextWindowContentSizeCond ? g.SetNextWindowContentSizeVal.y : 0.0f);
	g.SetNextWindowContentSizeCond = ImGuiSetCond_Always;
}

void ImGui::SetNextWindowCollapsed(bool collapsed, ImGuiSetCond cond)
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowCollapsedVal = collapsed;
	g.SetNextWindowCollapsedCond = cond ? cond : ImGuiSetCond_Always;
}

void ImGui::SetNextWindowFocus()
{
	ImGuiContext& g = *GImGui;
	g.SetNextWindowFocus = true;
}

// In window space (not screen space!)
ImVec2 ImGui::GetContentRegionMax()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	ImVec2 mx = window->ContentsRegionRect.Max;
	if (window->DC.ColumnsCount != 1)
		mx.x = GetColumnOffset(window->DC.ColumnsCurrent + 1) - window->WindowPadding.x;
	return mx;
}

ImVec2 ImGui::GetContentRegionAvail()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return GetContentRegionMax() - (window->DC.CursorPos - window->Pos);
}

float ImGui::GetContentRegionAvailWidth()
{
	return GetContentRegionAvail().x;
}

// In window space (not screen space!)
ImVec2 ImGui::GetWindowContentRegionMin()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->ContentsRegionRect.Min;
}

ImVec2 ImGui::GetWindowContentRegionMax()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->ContentsRegionRect.Max;
}

float ImGui::GetWindowContentRegionWidth()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->ContentsRegionRect.Max.x - window->ContentsRegionRect.Min.x;
}

float ImGui::GetTextLineHeight()
{
	ImGuiContext& g = *GImGui;
	return g.FontSize;
}

float ImGui::GetTextLineHeightWithSpacing()
{
	ImGuiContext& g = *GImGui;
	return g.FontSize + g.Style.ItemSpacing.y;
}

float ImGui::GetItemsLineHeightWithSpacing()
{
	ImGuiContext& g = *GImGui;
	return g.FontSize + g.Style.FramePadding.y * 2.0f + g.Style.ItemSpacing.y;
}

ImDrawList* ImGui::GetWindowDrawList()
{
	ImGuiWindow* window = GetCurrentWindow();
	return window->DrawList;
}

ImFont* ImGui::GetFont()
{
	return GImGui->Font;
}

float ImGui::GetFontSize()
{
	return GImGui->FontSize;
}

ImVec2 ImGui::GetFontTexUvWhitePixel()
{
	return GImGui->FontTexUvWhitePixel;
}

void ImGui::SetWindowFontScale(float scale)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();
	window->FontWindowScale = scale;
	g.FontSize = window->CalcFontSize();
}

// User generally sees positions in window coordinates. Internally we store CursorPos in absolute screen coordinates because it is more convenient.
// Conversion happens as we pass the value to user, but it makes our naming convention confusing because GetCursorPos() == (DC.CursorPos - window.Pos). May want to rename 'DC.CursorPos'.
ImVec2 ImGui::GetCursorPos()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.CursorPos - window->Pos + window->Scroll;
}

float ImGui::GetCursorPosX()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.CursorPos.x - window->Pos.x + window->Scroll.x;
}

float ImGui::GetCursorPosY()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.CursorPos.y - window->Pos.y + window->Scroll.y;
}

void ImGui::SetCursorPos(const ImVec2& local_pos)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.CursorPos = window->Pos - window->Scroll + local_pos;
	window->DC.CursorMaxPos = ImMax(window->DC.CursorMaxPos, window->DC.CursorPos);
}

void ImGui::SetCursorPosX(float x)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.CursorPos.x = window->Pos.x - window->Scroll.x + x;
	window->DC.CursorMaxPos.x = ImMax(window->DC.CursorMaxPos.x, window->DC.CursorPos.x);
}

void ImGui::SetCursorPosY(float y)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.CursorPos.y = window->Pos.y - window->Scroll.y + y;
	window->DC.CursorMaxPos.y = ImMax(window->DC.CursorMaxPos.y, window->DC.CursorPos.y);
}

ImVec2 ImGui::GetCursorStartPos()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.CursorStartPos - window->Pos;
}

ImVec2 ImGui::GetCursorScreenPos()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.CursorPos;
}

void ImGui::SetCursorScreenPos(const ImVec2& screen_pos)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.CursorPos = screen_pos;
	window->DC.CursorMaxPos = ImMax(window->DC.CursorMaxPos, window->DC.CursorPos);
}

float ImGui::GetScrollX()
{
	return GImGui->CurrentWindow->Scroll.x;
}

float ImGui::GetScrollY()
{
	return GImGui->CurrentWindow->Scroll.y;
}

float ImGui::GetScrollMaxX()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->SizeContents.x - window->SizeFull.x - window->ScrollbarSizes.x;
}

float ImGui::GetScrollMaxY()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->SizeContents.y - window->SizeFull.y - window->ScrollbarSizes.y;
}

void ImGui::SetScrollX(float scroll_x)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->ScrollTarget.x = scroll_x;
	window->ScrollTargetCenterRatio.x = 0.0f;
}

void ImGui::SetScrollY(float scroll_y)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->ScrollTarget.y = scroll_y + window->TitleBarHeight() + window->MenuBarHeight(); // title bar height canceled out when using ScrollTargetRelY
	window->ScrollTargetCenterRatio.y = 0.0f;
}

void ImGui::SetScrollFromPosY(float pos_y, float center_y_ratio)
{
	// We store a target position so centering can occur on the next frame when we are guaranteed to have a known window size
	ImGuiWindow* window = GetCurrentWindow();
	IM_ASSERT(center_y_ratio >= 0.0f && center_y_ratio <= 1.0f);
	window->ScrollTarget.y = (float)(int)(pos_y + window->Scroll.y);
	if (center_y_ratio <= 0.0f && window->ScrollTarget.y <= window->WindowPadding.y)    // Minor hack to make "scroll to top" take account of WindowPadding, else it would scroll to (WindowPadding.y - ItemSpacing.y)
		window->ScrollTarget.y = 0.0f;
	window->ScrollTargetCenterRatio.y = center_y_ratio;
}

// center_y_ratio: 0.0f top of last item, 0.5f vertical center of last item, 1.0f bottom of last item.
void ImGui::SetScrollHere(float center_y_ratio)
{
	ImGuiWindow* window = GetCurrentWindow();
	float target_y = window->DC.CursorPosPrevLine.y + (window->DC.PrevLineHeight * center_y_ratio) + (GImGui->Style.ItemSpacing.y * (center_y_ratio - 0.5f) * 2.0f); // Precisely aim above, in the middle or below the last line.
	SetScrollFromPosY(target_y - window->Pos.y, center_y_ratio);
}

void ImGui::SetKeyboardFocusHere(int offset)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->FocusIdxAllRequestNext = window->FocusIdxAllCounter + 1 + offset;
	window->FocusIdxTabRequestNext = INT_MAX;
}

void ImGui::SetStateStorage(ImGuiStorage* tree)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.StateStorage = tree ? tree : &window->StateStorage;
}

ImGuiStorage* ImGui::GetStateStorage()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.StateStorage;
}

void ImGui::TextV(const char* fmt, va_list args)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const char* text_end = g.TempBuffer + ImFormatStringV(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), fmt, args);
	TextUnformatted(g.TempBuffer, text_end);
}

void ImGui::Text(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	TextV(fmt, args);
	va_end(args);
}

void ImGui::TextColoredV(const ImVec4& col, const char* fmt, va_list args)
{
	PushStyleColor(ImGuiCol_Text, col);
	TextV(fmt, args);
	PopStyleColor();
}

void ImGui::TextColored(const ImVec4& col, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	TextColoredV(col, fmt, args);
	va_end(args);
}

void ImGui::TextDisabledV(const char* fmt, va_list args)
{
	PushStyleColor(ImGuiCol_Text, GImGui->Style.Colors[ImGuiCol_TextDisabled]);
	TextV(fmt, args);
	PopStyleColor();
}

void ImGui::TextDisabled(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	TextDisabledV(fmt, args);
	va_end(args);
}

void ImGui::TextWrappedV(const char* fmt, va_list args)
{
	bool need_wrap = (GImGui->CurrentWindow->DC.TextWrapPos < 0.0f);    // Keep existing wrap position is one ia already set
	if (need_wrap) PushTextWrapPos(0.0f);
	TextV(fmt, args);
	if (need_wrap) PopTextWrapPos();
}

void ImGui::TextWrapped(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	TextWrappedV(fmt, args);
	va_end(args);
}

void ImGui::TextUnformatted(const char* text, const char* text_end)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	IM_ASSERT(text != NULL);
	const char* text_begin = text;
	if (text_end == NULL)
		text_end = text + strlen(text); // FIXME-OPT

	const float wrap_pos_x = window->DC.TextWrapPos;
	const bool wrap_enabled = wrap_pos_x >= 0.0f;
	if (text_end - text > 2000 && !wrap_enabled)
	{
		// Long text!
		// Perform manual coarse clipping to optimize for long multi-line text
		// From this point we will only compute the width of lines that are visible. Optimization only available when word-wrapping is disabled.
		// We also don't vertically center the text within the line full height, which is unlikely to matter because we are likely the biggest and only item on the line.
		const char* line = text;
		const float line_height = GetTextLineHeight();
		const ImVec2 text_pos = window->DC.CursorPos + ImVec2(0.0f, window->DC.CurrentLineTextBaseOffset);
		const ImRect clip_rect = window->ClipRect;
		ImVec2 text_size(0, 0);

		if (text_pos.y <= clip_rect.Max.y)
		{
			ImVec2 pos = text_pos;

			// Lines to skip (can't skip when logging text)
			if (!g.LogEnabled)
			{
				int lines_skippable = (int)((clip_rect.Min.y - text_pos.y) / line_height);
				if (lines_skippable > 0)
				{
					int lines_skipped = 0;
					while (line < text_end && lines_skipped < lines_skippable)
					{
						const char* line_end = strchr(line, '\n');
						if (!line_end)
							line_end = text_end;
						line = line_end + 1;
						lines_skipped++;
					}
					pos.y += lines_skipped * line_height;
				}
			}

			// Lines to render
			if (line < text_end)
			{
				ImRect line_rect(pos, pos + ImVec2(FLT_MAX, line_height));
				while (line < text_end)
				{
					const char* line_end = strchr(line, '\n');
					if (IsClippedEx(line_rect, NULL, false))
						break;

					const ImVec2 line_size = CalcTextSize(line, line_end, false);
					text_size.x = ImMax(text_size.x, line_size.x);
					RenderText(pos, line, line_end, false);
					if (!line_end)
						line_end = text_end;
					line = line_end + 1;
					line_rect.Min.y += line_height;
					line_rect.Max.y += line_height;
					pos.y += line_height;
				}

				// Count remaining lines
				int lines_skipped = 0;
				while (line < text_end)
				{
					const char* line_end = strchr(line, '\n');
					if (!line_end)
						line_end = text_end;
					line = line_end + 1;
					lines_skipped++;
				}
				pos.y += lines_skipped * line_height;
			}

			text_size.y += (pos - text_pos).y;
		}

		ImRect bb(text_pos, text_pos + text_size);
		ItemSize(bb);
		ItemAdd(bb, NULL);
	}
	else
	{
		const float wrap_width = wrap_enabled ? CalcWrapWidthForPos(window->DC.CursorPos, wrap_pos_x) : 0.0f;
		const ImVec2 text_size = CalcTextSize(text_begin, text_end, false, wrap_width);

		// Account of baseline offset
		ImVec2 text_pos(window->DC.CursorPos.x, window->DC.CursorPos.y + window->DC.CurrentLineTextBaseOffset);
		ImRect bb(text_pos, text_pos + text_size);
		ItemSize(text_size);
		if (!ItemAdd(bb, NULL))
			return;

		// Render (we don't hide text after ## in this end-user function)
		RenderTextWrapped(bb.Min, text_begin, text_end, wrap_width);
	}
}

void ImGui::AlignFirstTextHeightToWidgets()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	// Declare a dummy item size to that upcoming items that are smaller will center-align on the newly expanded line height.
	ImGuiContext& g = *GImGui;
	ItemSize(ImVec2(0, g.FontSize + g.Style.FramePadding.y * 2), g.Style.FramePadding.y);
	SameLine(0, 0);
}

// Add a label+text combo aligned to other label+value widgets
void ImGui::LabelTextV(const char* label, const char* fmt, va_list args)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const float w = CalcItemWidth();

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect value_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2));
	const ImRect total_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w + (label_size.x > 0.0f ? style.ItemInnerSpacing.x : 0.0f), style.FramePadding.y * 2) + label_size);
	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, NULL))
		return;

	// Render
	const char* value_text_begin = &g.TempBuffer[0];
	const char* value_text_end = value_text_begin + ImFormatStringV(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), fmt, args);
	RenderTextClipped(value_bb.Min, value_bb.Max, value_text_begin, value_text_end, NULL, ImVec2(0.0f, 0.5f));
	if (label_size.x > 0.0f)
		RenderText(ImVec2(value_bb.Max.x + style.ItemInnerSpacing.x, value_bb.Min.y + style.FramePadding.y), label);
}

void ImGui::LabelText(const char* label, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	LabelTextV(label, fmt, args);
	va_end(args);
}

static inline bool IsWindowContentHoverable(ImGuiWindow* window)
{
	// An active popup disable hovering on other windows (apart from its own children)
	ImGuiContext& g = *GImGui;
	if (ImGuiWindow* focused_window = g.FocusedWindow)
		if (ImGuiWindow* focused_root_window = focused_window->RootWindow)
			if ((focused_root_window->Flags & ImGuiWindowFlags_Popup) != 0 && focused_root_window->WasActive && focused_root_window != window->RootWindow)
				return false;

	return true;
}

bool ImGui::ButtonBehavior(const ImRect& bb, ImGuiID id, bool* out_hovered, bool* out_held, ImGuiButtonFlags flags)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();

	if (flags & ImGuiButtonFlags_Disabled)
	{
		if (out_hovered) *out_hovered = false;
		if (out_held) *out_held = false;
		if (g.ActiveId == id) ClearActiveID();
		return false;
	}

	if ((flags & (ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnClick | ImGuiButtonFlags_PressedOnRelease | ImGuiButtonFlags_PressedOnDoubleClick)) == 0)
		flags |= ImGuiButtonFlags_PressedOnClickRelease;

	bool pressed = false;
	bool hovered = IsHovered(bb, id, (flags & ImGuiButtonFlags_FlattenChilds) != 0);
	if (hovered)
	{
		SetHoveredID(id);
		if (!(flags & ImGuiButtonFlags_NoKeyModifiers) || (!g.IO.KeyCtrl && !g.IO.KeyShift && !g.IO.KeyAlt))
		{
			//                        | CLICKING        | HOLDING with ImGuiButtonFlags_Repeat
			// PressedOnClickRelease  |  <on release>*  |  <on repeat> <on repeat> .. (NOT on release)  <-- MOST COMMON! (*) only if both click/release were over bounds
			// PressedOnClick         |  <on click>     |  <on click> <on repeat> <on repeat> ..
			// PressedOnRelease       |  <on release>   |  <on repeat> <on repeat> .. (NOT on release)
			// PressedOnDoubleClick   |  <on dclick>    |  <on dclick> <on repeat> <on repeat> ..
			if ((flags & ImGuiButtonFlags_PressedOnClickRelease) && g.IO.MouseClicked[0])
			{
				SetActiveID(id, window); // Hold on ID
				FocusWindow(window);
				g.ActiveIdClickOffset = g.IO.MousePos - bb.Min;
			}
			if (((flags & ImGuiButtonFlags_PressedOnClick) && g.IO.MouseClicked[0]) || ((flags & ImGuiButtonFlags_PressedOnDoubleClick) && g.IO.MouseDoubleClicked[0]))
			{
				pressed = true;
				ClearActiveID();
				FocusWindow(window);
			}
			if ((flags & ImGuiButtonFlags_PressedOnRelease) && g.IO.MouseReleased[0])
			{
				if (!((flags & ImGuiButtonFlags_Repeat) && g.IO.MouseDownDurationPrev[0] >= g.IO.KeyRepeatDelay))  // Repeat mode trumps <on release>
					pressed = true;
				ClearActiveID();
			}

			// 'Repeat' mode acts when held regardless of _PressedOn flags (see table above). 
			// Relies on repeat logic of IsMouseClicked() but we may as well do it ourselves if we end up exposing finer RepeatDelay/RepeatRate settings.
			if ((flags & ImGuiButtonFlags_Repeat) && g.ActiveId == id && g.IO.MouseDownDuration[0] > 0.0f && IsMouseClicked(0, true))
				pressed = true;
		}
	}

	bool held = false;
	if (g.ActiveId == id)
	{
		if (g.IO.MouseDown[0])
		{
			held = true;
		}
		else
		{
			if (hovered && (flags & ImGuiButtonFlags_PressedOnClickRelease))
				if (!((flags & ImGuiButtonFlags_Repeat) && g.IO.MouseDownDurationPrev[0] >= g.IO.KeyRepeatDelay))  // Repeat mode trumps <on release>
					pressed = true;
			ClearActiveID();
		}
	}

	// AllowOverlap mode (rarely used) requires previous frame HoveredId to be null or to match. This allows using patterns where a later submitted widget overlaps a previous one.
	if (hovered && (flags & ImGuiButtonFlags_AllowOverlapMode) && (g.HoveredIdPreviousFrame != id && g.HoveredIdPreviousFrame != 0))
		hovered = pressed = held = false;

	if (out_hovered) *out_hovered = hovered;
	if (out_held) *out_held = held;

	return pressed;
}

bool ImGui::ButtonEx(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrentLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrentLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(bb, &id))
		return false;

	if (window->DC.ButtonRepeat) flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

	// Render
	const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
	RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

	// Automatically close popups
	//if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
	//    CloseCurrentPopup();

	return pressed;
}

bool ImGui::Button(const char* label, const ImVec2& size_arg)
{
	return ButtonEx(label, size_arg, 0);
}

// Small buttons fits within text without additional vertical spacing.
bool ImGui::SmallButton(const char* label)
{
	ImGuiContext& g = *GImGui;
	float backup_padding_y = g.Style.FramePadding.y;
	g.Style.FramePadding.y = 0.0f;
	bool pressed = ButtonEx(label, ImVec2(0, 0), ImGuiButtonFlags_AlignTextBaseLine);
	g.Style.FramePadding.y = backup_padding_y;
	return pressed;
}

// Tip: use ImGui::PushID()/PopID() to push indices or pointers in the ID stack.
// Then you can keep 'str_id' empty or the same for all your buttons (instead of creating a string based on a non-string id)
bool ImGui::InvisibleButton(const char* str_id, const ImVec2& size_arg)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	const ImGuiID id = window->GetID(str_id);
	ImVec2 size = CalcItemSize(size_arg, 0.0f, 0.0f);
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
	ItemSize(bb);
	if (!ItemAdd(bb, &id))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);

	return pressed;
}

// Upper-right button to close a window.
bool ImGui::CloseButton(ImGuiID id, const ImVec2& pos, float radius)
{
	ImGuiWindow* window = GetCurrentWindow();

	const ImRect bb(pos - ImVec2(radius, radius), pos + ImVec2(radius, radius));

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);

	// Render
	const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_CloseButtonActive : hovered ? ImGuiCol_CloseButtonHovered : ImGuiCol_CloseButton);
	const ImVec2 center = bb.GetCenter();
	window->DrawList->AddCircleFilled(center, ImMax(2.0f, radius), col, 12);

	const float cross_extent = (radius * 0.7071f) - 1.0f;
	if (hovered)
	{
		window->DrawList->AddLine(center + ImVec2(+cross_extent, +cross_extent), center + ImVec2(-cross_extent, -cross_extent), GetColorU32(ImGuiCol_Text));
		window->DrawList->AddLine(center + ImVec2(+cross_extent, -cross_extent), center + ImVec2(-cross_extent, +cross_extent), GetColorU32(ImGuiCol_Text));
	}

	return pressed;
}

void ImGui::Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
	if (border_col.w > 0.0f)
		bb.Max += ImVec2(2, 2);
	ItemSize(bb);
	if (!ItemAdd(bb, NULL))
		return;

	if (border_col.w > 0.0f)
	{
		window->DrawList->AddRect(bb.Min, bb.Max, GetColorU32(border_col), 0.0f);
		window->DrawList->AddImage(user_texture_id, bb.Min + ImVec2(1, 1), bb.Max - ImVec2(1, 1), uv0, uv1, GetColorU32(tint_col));
	}
	else
	{
		window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, uv0, uv1, GetColorU32(tint_col));
	}
}

// frame_padding < 0: uses FramePadding from style (default)
// frame_padding = 0: no framing
// frame_padding > 0: set framing size
// The color used are the button colors.
bool ImGui::ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	// Default to using texture ID as ID. User can still push string/integer prefixes.
	// We could hash the size/uv to create a unique ID but that would prevent the user from animating UV.
	PushID((void *)user_texture_id);
	const ImGuiID id = window->GetID("#image");
	PopID();

	const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size + padding * 2);
	const ImRect image_bb(window->DC.CursorPos + padding, window->DC.CursorPos + padding + size);
	ItemSize(bb);
	if (!ItemAdd(bb, &id))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);

	// Render
	const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
	if (bg_col.w > 0.0f)
		window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));
	window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));

	return pressed;
}

// Start logging ImGui output to TTY
void ImGui::LogToTTY(int max_depth)
{
	ImGuiContext& g = *GImGui;
	if (g.LogEnabled)
		return;
	ImGuiWindow* window = GetCurrentWindowRead();

	g.LogEnabled = true;
	g.LogFile = stdout;
	g.LogStartDepth = window->DC.TreeDepth;
	if (max_depth >= 0)
		g.LogAutoExpandMaxDepth = max_depth;
}

// Start logging ImGui output to given file
void ImGui::LogToFile(int max_depth, const char* filename)
{
	ImGuiContext& g = *GImGui;
	if (g.LogEnabled)
		return;
	ImGuiWindow* window = GetCurrentWindowRead();

	if (!filename)
	{
		filename = g.IO.LogFilename;
		if (!filename)
			return;
	}

	g.LogFile = ImFileOpen(filename, "ab");
	if (!g.LogFile)
	{
		IM_ASSERT(g.LogFile != NULL); // Consider this an error
		return;
	}
	g.LogEnabled = true;
	g.LogStartDepth = window->DC.TreeDepth;
	if (max_depth >= 0)
		g.LogAutoExpandMaxDepth = max_depth;
}

// Start logging ImGui output to clipboard
void ImGui::LogToClipboard(int max_depth)
{
	ImGuiContext& g = *GImGui;
	if (g.LogEnabled)
		return;
	ImGuiWindow* window = GetCurrentWindowRead();

	g.LogEnabled = true;
	g.LogFile = NULL;
	g.LogStartDepth = window->DC.TreeDepth;
	if (max_depth >= 0)
		g.LogAutoExpandMaxDepth = max_depth;
}

void ImGui::LogFinish()
{
	ImGuiContext& g = *GImGui;
	if (!g.LogEnabled)
		return;

	LogText(IM_NEWLINE);
	g.LogEnabled = false;
	if (g.LogFile != NULL)
	{
		if (g.LogFile == stdout)
			fflush(g.LogFile);
		else
			fclose(g.LogFile);
		g.LogFile = NULL;
	}
	if (g.LogClipboard->size() > 1)
	{
		SetClipboardText(g.LogClipboard->begin());
		g.LogClipboard->clear();
	}
}

// Helper to display logging buttons
void ImGui::LogButtons()
{
	ImGuiContext& g = *GImGui;

	PushID("LogButtons");
	const bool log_to_tty = Button("Log To TTY"); SameLine();
	const bool log_to_file = Button("Log To File"); SameLine();
	const bool log_to_clipboard = Button("Log To Clipboard"); SameLine();
	PushItemWidth(80.0f);
	PushAllowKeyboardFocus(false);
	SliderInt("Depth", &g.LogAutoExpandMaxDepth, 0, 9, NULL);
	PopAllowKeyboardFocus();
	PopItemWidth();
	PopID();

	// Start logging at the end of the function so that the buttons don't appear in the log
	if (log_to_tty)
		LogToTTY(g.LogAutoExpandMaxDepth);
	if (log_to_file)
		LogToFile(g.LogAutoExpandMaxDepth, g.IO.LogFilename);
	if (log_to_clipboard)
		LogToClipboard(g.LogAutoExpandMaxDepth);
}

bool ImGui::TreeNodeBehaviorIsOpen(ImGuiID id, ImGuiTreeNodeFlags flags)
{
	if (flags & ImGuiTreeNodeFlags_Leaf)
		return true;

	// We only write to the tree storage if the user clicks (or explicitely use SetNextTreeNode*** functions)
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	ImGuiStorage* storage = window->DC.StateStorage;

	bool is_open;
	if (g.SetNextTreeNodeOpenCond != 0)
	{
		if (g.SetNextTreeNodeOpenCond & ImGuiSetCond_Always)
		{
			is_open = g.SetNextTreeNodeOpenVal;
			storage->SetInt(id, is_open);
		}
		else
		{
			// We treat ImGuiSetCondition_Once and ImGuiSetCondition_FirstUseEver the same because tree node state are not saved persistently.
			const int stored_value = storage->GetInt(id, -1);
			if (stored_value == -1)
			{
				is_open = g.SetNextTreeNodeOpenVal;
				storage->SetInt(id, is_open);
			}
			else
			{
				is_open = stored_value != 0;
			}
		}
		g.SetNextTreeNodeOpenCond = 0;
	}
	else
	{
		is_open = storage->GetInt(id, (flags & ImGuiTreeNodeFlags_DefaultOpen) ? 1 : 0) != 0;
	}

	// When logging is enabled, we automatically expand tree nodes (but *NOT* collapsing headers.. seems like sensible behavior).
	// NB- If we are above max depth we still allow manually opened nodes to be logged.
	if (g.LogEnabled && !(flags & ImGuiTreeNodeFlags_NoAutoOpenOnLog) && window->DC.TreeDepth < g.LogAutoExpandMaxDepth)
		is_open = true;

	return is_open;
}

bool ImGui::TreeNodeBehavior(ImGuiID id, ImGuiTreeNodeFlags flags, const char* label, const char* label_end)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const bool display_frame = (flags & ImGuiTreeNodeFlags_Framed) != 0;
	const ImVec2 padding = display_frame ? style.FramePadding : ImVec2(style.FramePadding.x, 0.0f);

	if (!label_end)
		label_end = FindRenderedTextEnd(label);
	const ImVec2 label_size = CalcTextSize(label, label_end, false);

	// We vertically grow up to current line height up the typical widget height.
	const float text_base_offset_y = ImMax(0.0f, window->DC.CurrentLineTextBaseOffset - padding.y); // Latch before ItemSize changes it
	const float frame_height = ImMax(ImMin(window->DC.CurrentLineHeight, g.FontSize + style.FramePadding.y * 2), label_size.y + padding.y * 2);
	ImRect bb = ImRect(window->DC.CursorPos, ImVec2(window->Pos.x + GetContentRegionMax().x, window->DC.CursorPos.y + frame_height));
	if (display_frame)
	{
		// Framed header expand a little outside the default padding
		bb.Min.x -= (float)(int)(window->WindowPadding.x*0.5f) - 1;
		bb.Max.x += (float)(int)(window->WindowPadding.x*0.5f) - 1;
	}

	const float text_offset_x = (g.FontSize + (display_frame ? padding.x * 3 : padding.x * 2));   // Collapser arrow width + Spacing
	const float text_width = g.FontSize + (label_size.x > 0.0f ? label_size.x + padding.x * 2 : 0.0f);   // Include collapser
	ItemSize(ImVec2(text_width, frame_height), text_base_offset_y);

	// For regular tree nodes, we arbitrary allow to click past 2 worth of ItemSpacing
	// (Ideally we'd want to add a flag for the user to specify we want want the hit test to be done up to the right side of the content or not)
	const ImRect interact_bb = display_frame ? bb : ImRect(bb.Min.x, bb.Min.y, bb.Min.x + text_width + style.ItemSpacing.x * 2, bb.Max.y);
	bool is_open = TreeNodeBehaviorIsOpen(id, flags);
	if (!ItemAdd(interact_bb, &id))
	{
		if (is_open && !(flags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
			TreePushRawID(id);
		return is_open;
	}

	// Flags that affects opening behavior:
	// - 0(default) ..................... single-click anywhere to open
	// - OpenOnDoubleClick .............. double-click anywhere to open
	// - OpenOnArrow .................... single-click on arrow to open
	// - OpenOnDoubleClick|OpenOnArrow .. single-click on arrow or double-click anywhere to open
	ImGuiButtonFlags button_flags = ImGuiButtonFlags_NoKeyModifiers | ((flags & ImGuiTreeNodeFlags_AllowOverlapMode) ? ImGuiButtonFlags_AllowOverlapMode : 0);
	if (flags & ImGuiTreeNodeFlags_OpenOnDoubleClick)
		button_flags |= ImGuiButtonFlags_PressedOnDoubleClick | ((flags & ImGuiTreeNodeFlags_OpenOnArrow) ? ImGuiButtonFlags_PressedOnClickRelease : 0);
	bool hovered, held, pressed = ButtonBehavior(interact_bb, id, &hovered, &held, button_flags);
	if (pressed && !(flags & ImGuiTreeNodeFlags_Leaf))
	{
		bool toggled = !(flags & (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));
		if (flags & ImGuiTreeNodeFlags_OpenOnArrow)
			toggled |= IsMouseHoveringRect(interact_bb.Min, ImVec2(interact_bb.Min.x + text_offset_x, interact_bb.Max.y));
		if (flags & ImGuiTreeNodeFlags_OpenOnDoubleClick)
			toggled |= g.IO.MouseDoubleClicked[0];
		if (toggled)
		{
			is_open = !is_open;
			window->DC.StateStorage->SetInt(id, is_open);
		}
	}
	if (flags & ImGuiTreeNodeFlags_AllowOverlapMode)
		SetItemAllowOverlap();

	// Render
	const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
	const ImVec2 text_pos = bb.Min + ImVec2(text_offset_x, padding.y + text_base_offset_y);
	if (display_frame)
	{
		// Framed type
		RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
		RenderCollapseTriangle(bb.Min + padding + ImVec2(0.0f, text_base_offset_y), is_open, 1.0f);
		if (g.LogEnabled)
		{
			// NB: '##' is normally used to hide text (as a library-wide feature), so we need to specify the text range to make sure the ## aren't stripped out here.
			const char log_prefix[] = "\n##";
			const char log_suffix[] = "##";
			LogRenderedText(text_pos, log_prefix, log_prefix + 3);
			RenderTextClipped(text_pos, bb.Max, label, label_end, &label_size);
			LogRenderedText(text_pos, log_suffix + 1, log_suffix + 3);
		}
		else
		{
			RenderTextClipped(text_pos, bb.Max, label, label_end, &label_size);
		}
	}
	else
	{
		// Unframed typed for tree nodes
		if (hovered || (flags & ImGuiTreeNodeFlags_Selected))
			RenderFrame(bb.Min, bb.Max, col, false);

		if (flags & ImGuiTreeNodeFlags_Bullet)
			RenderBullet(bb.Min + ImVec2(text_offset_x * 0.5f, g.FontSize*0.50f + text_base_offset_y));
		else if (!(flags & ImGuiTreeNodeFlags_Leaf))
			RenderCollapseTriangle(bb.Min + ImVec2(padding.x, g.FontSize*0.15f + text_base_offset_y), is_open, 0.70f);
		if (g.LogEnabled)
			LogRenderedText(text_pos, ">");
		RenderText(text_pos, label, label_end, false);
	}

	if (is_open && !(flags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
		TreePushRawID(id);
	return is_open;
}

// CollapsingHeader returns true when opened but do not indent nor push into the ID stack (because of the ImGuiTreeNodeFlags_NoTreePushOnOpen flag).
// This is basically the same as calling TreeNodeEx(label, ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_NoTreePushOnOpen). You can remove the _NoTreePushOnOpen flag if you want behavior closer to normal TreeNode().
bool ImGui::CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	return TreeNodeBehavior(window->GetID(label), flags | ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_NoTreePushOnOpen, label);
}

bool ImGui::CollapsingHeader(const char* label, bool* p_open, ImGuiTreeNodeFlags flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	if (p_open && !*p_open)
		return false;

	ImGuiID id = window->GetID(label);
	bool is_open = TreeNodeBehavior(id, flags | ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_NoTreePushOnOpen | (p_open ? ImGuiTreeNodeFlags_AllowOverlapMode : 0), label);
	if (p_open)
	{
		// Create a small overlapping close button // FIXME: We can evolve this into user accessible helpers to add extra buttons on title bars, headers, etc.
		ImGuiContext& g = *GImGui;
		float button_sz = g.FontSize * 0.5f;
		if (CloseButton(window->GetID((void*)(intptr_t)(id + 1)), ImVec2(ImMin(window->DC.LastItemRect.Max.x, window->ClipRect.Max.x) - g.Style.FramePadding.x - button_sz, window->DC.LastItemRect.Min.y + g.Style.FramePadding.y + button_sz), button_sz))
			*p_open = false;
	}

	return is_open;
}

bool ImGui::TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	return TreeNodeBehavior(window->GetID(label), flags, label, NULL);
}

bool ImGui::TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const char* label_end = g.TempBuffer + ImFormatStringV(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), fmt, args);
	return TreeNodeBehavior(window->GetID(str_id), flags, g.TempBuffer, label_end);
}

bool ImGui::TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const char* label_end = g.TempBuffer + ImFormatStringV(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), fmt, args);
	return TreeNodeBehavior(window->GetID(ptr_id), flags, g.TempBuffer, label_end);
}

bool ImGui::TreeNodeV(const char* str_id, const char* fmt, va_list args)
{
	return TreeNodeExV(str_id, 0, fmt, args);
}

bool ImGui::TreeNodeV(const void* ptr_id, const char* fmt, va_list args)
{
	return TreeNodeExV(ptr_id, 0, fmt, args);
}

bool ImGui::TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool is_open = TreeNodeExV(str_id, flags, fmt, args);
	va_end(args);
	return is_open;
}

bool ImGui::TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool is_open = TreeNodeExV(ptr_id, flags, fmt, args);
	va_end(args);
	return is_open;
}

bool ImGui::TreeNode(const char* str_id, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool is_open = TreeNodeExV(str_id, 0, fmt, args);
	va_end(args);
	return is_open;
}

bool ImGui::TreeNode(const void* ptr_id, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool is_open = TreeNodeExV(ptr_id, 0, fmt, args);
	va_end(args);
	return is_open;
}

bool ImGui::TreeNode(const char* label)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;
	return TreeNodeBehavior(window->GetID(label), 0, label, NULL);
}

void ImGui::TreeAdvanceToLabelPos()
{
	ImGuiContext& g = *GImGui;
	g.CurrentWindow->DC.CursorPos.x += GetTreeNodeToLabelSpacing();
}

// Horizontal distance preceding label when using TreeNode() or Bullet()
float ImGui::GetTreeNodeToLabelSpacing()
{
	ImGuiContext& g = *GImGui;
	return g.FontSize + (g.Style.FramePadding.x * 2.0f);
}

void ImGui::SetNextTreeNodeOpen(bool is_open, ImGuiSetCond cond)
{
	ImGuiContext& g = *GImGui;
	g.SetNextTreeNodeOpenVal = is_open;
	g.SetNextTreeNodeOpenCond = cond ? cond : ImGuiSetCond_Always;
}

void ImGui::PushID(const char* str_id)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->IDStack.push_back(window->GetID(str_id));
}

void ImGui::PushID(const char* str_id_begin, const char* str_id_end)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->IDStack.push_back(window->GetID(str_id_begin, str_id_end));
}

void ImGui::PushID(const void* ptr_id)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->IDStack.push_back(window->GetID(ptr_id));
}

void ImGui::PushID(int int_id)
{
	const void* ptr_id = (void*)(intptr_t)int_id;
	ImGuiWindow* window = GetCurrentWindow();
	window->IDStack.push_back(window->GetID(ptr_id));
}

void ImGui::PopID()
{
	ImGuiWindow* window = GetCurrentWindow();
	window->IDStack.pop_back();
}

ImGuiID ImGui::GetID(const char* str_id)
{
	return GImGui->CurrentWindow->GetID(str_id);
}

ImGuiID ImGui::GetID(const char* str_id_begin, const char* str_id_end)
{
	return GImGui->CurrentWindow->GetID(str_id_begin, str_id_end);
}

ImGuiID ImGui::GetID(const void* ptr_id)
{
	return GImGui->CurrentWindow->GetID(ptr_id);
}

void ImGui::Bullet()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const float line_height = ImMax(ImMin(window->DC.CurrentLineHeight, g.FontSize + g.Style.FramePadding.y * 2), g.FontSize);
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(g.FontSize, line_height));
	ItemSize(bb);
	if (!ItemAdd(bb, NULL))
	{
		SameLine(0, style.FramePadding.x * 2);
		return;
	}

	// Render and stay on same line
	RenderBullet(bb.Min + ImVec2(style.FramePadding.x + g.FontSize*0.5f, line_height*0.5f));
	SameLine(0, style.FramePadding.x * 2);
}

// Text with a little bullet aligned to the typical tree node.
void ImGui::BulletTextV(const char* fmt, va_list args)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	const char* text_begin = g.TempBuffer;
	const char* text_end = text_begin + ImFormatStringV(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), fmt, args);
	const ImVec2 label_size = CalcTextSize(text_begin, text_end, false);
	const float text_base_offset_y = ImMax(0.0f, window->DC.CurrentLineTextBaseOffset); // Latch before ItemSize changes it
	const float line_height = ImMax(ImMin(window->DC.CurrentLineHeight, g.FontSize + g.Style.FramePadding.y * 2), g.FontSize);
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(g.FontSize + (label_size.x > 0.0f ? (label_size.x + style.FramePadding.x * 2) : 0.0f), ImMax(line_height, label_size.y)));  // Empty text doesn't add padding
	ItemSize(bb);
	if (!ItemAdd(bb, NULL))
		return;

	// Render
	RenderBullet(bb.Min + ImVec2(style.FramePadding.x + g.FontSize*0.5f, line_height*0.5f));
	RenderText(bb.Min + ImVec2(g.FontSize + style.FramePadding.x * 2, text_base_offset_y), text_begin, text_end, false);
}

void ImGui::BulletText(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	BulletTextV(fmt, args);
	va_end(args);
}

static inline void DataTypeFormatString(ImGuiDataType data_type, void* data_ptr, const char* display_format, char* buf, int buf_size)
{
	if (data_type == ImGuiDataType_Int)
		ImFormatString(buf, buf_size, display_format, *(int*)data_ptr);
	else if (data_type == ImGuiDataType_Float)
		ImFormatString(buf, buf_size, display_format, *(float*)data_ptr);
}

static inline void DataTypeFormatString(ImGuiDataType data_type, void* data_ptr, int decimal_precision, char* buf, int buf_size)
{
	if (data_type == ImGuiDataType_Int)
	{
		if (decimal_precision < 0)
			ImFormatString(buf, buf_size, "%d", *(int*)data_ptr);
		else
			ImFormatString(buf, buf_size, "%.*d", decimal_precision, *(int*)data_ptr);
	}
	else if (data_type == ImGuiDataType_Float)
	{
		if (decimal_precision < 0)
			ImFormatString(buf, buf_size, "%f", *(float*)data_ptr);     // Ideally we'd have a minimum decimal precision of 1 to visually denote that it is a float, while hiding non-significant digits?
		else
			ImFormatString(buf, buf_size, "%.*f", decimal_precision, *(float*)data_ptr);
	}
}

static void DataTypeApplyOp(ImGuiDataType data_type, int op, void* value1, const void* value2)// Store into value1
{
	if (data_type == ImGuiDataType_Int)
	{
		if (op == '+')
			*(int*)value1 = *(int*)value1 + *(const int*)value2;
		else if (op == '-')
			*(int*)value1 = *(int*)value1 - *(const int*)value2;
	}
	else if (data_type == ImGuiDataType_Float)
	{
		if (op == '+')
			*(float*)value1 = *(float*)value1 + *(const float*)value2;
		else if (op == '-')
			*(float*)value1 = *(float*)value1 - *(const float*)value2;
	}
}

// User can input math operators (e.g. +100) to edit a numerical values.
static bool DataTypeApplyOpFromText(const char* buf, const char* initial_value_buf, ImGuiDataType data_type, void* data_ptr, const char* scalar_format)
{
	while (ImCharIsSpace(*buf))
		buf++;

	// We don't support '-' op because it would conflict with inputing negative value.
	// Instead you can use +-100 to subtract from an existing value
	char op = buf[0];
	if (op == '+' || op == '*' || op == '/')
	{
		buf++;
		while (ImCharIsSpace(*buf))
			buf++;
	}
	else
	{
		op = 0;
	}
	if (!buf[0])
		return false;

	if (data_type == ImGuiDataType_Int)
	{
		if (!scalar_format)
			scalar_format = "%d";
		int* v = (int*)data_ptr;
		const int old_v = *v;
		int arg0 = *v;
		if (op && sscanf(initial_value_buf, scalar_format, &arg0) < 1)
			return false;

		// Store operand in a float so we can use fractional value for multipliers (*1.1), but constant always parsed as integer so we can fit big integers (e.g. 2000000003) past float precision
		float arg1 = 0.0f;
		if (op == '+') { if (sscanf(buf, "%f", &arg1) == 1) *v = (int)(arg0 + arg1); }                // Add (use "+-" to subtract)
		else if (op == '*') { if (sscanf(buf, "%f", &arg1) == 1) *v = (int)(arg0 * arg1); }                // Multiply
		else if (op == '/') { if (sscanf(buf, "%f", &arg1) == 1 && arg1 != 0.0f) *v = (int)(arg0 / arg1); }// Divide
		else { if (sscanf(buf, scalar_format, &arg0) == 1) *v = arg0; }                     // Assign constant
		return (old_v != *v);
	}
	else if (data_type == ImGuiDataType_Float)
	{
		// For floats we have to ignore format with precision (e.g. "%.2f") because sscanf doesn't take them in
		scalar_format = "%f";
		float* v = (float*)data_ptr;
		const float old_v = *v;
		float arg0 = *v;
		if (op && sscanf(initial_value_buf, scalar_format, &arg0) < 1)
			return false;

		float arg1 = 0.0f;
		if (sscanf(buf, scalar_format, &arg1) < 1)
			return false;
		if (op == '+') { *v = arg0 + arg1; }                    // Add (use "+-" to subtract)
		else if (op == '*') { *v = arg0 * arg1; }                    // Multiply
		else if (op == '/') { if (arg1 != 0.0f) *v = arg0 / arg1; }  // Divide
		else { *v = arg1; }                           // Assign constant
		return (old_v != *v);
	}

	return false;
}

// Create text input in place of a slider (when CTRL+Clicking on slider)
bool ImGui::InputScalarAsWidgetReplacement(const ImRect& aabb, const char* label, ImGuiDataType data_type, void* data_ptr, ImGuiID id, int decimal_precision)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();

	// Our replacement widget will override the focus ID (registered previously to allow for a TAB focus to happen)
	SetActiveID(g.ScalarAsInputTextId, window);
	SetHoveredID(0);
	FocusableItemUnregister(window);

	char buf[32];
	DataTypeFormatString(data_type, data_ptr, decimal_precision, buf, IM_ARRAYSIZE(buf));
	bool text_value_changed = InputTextEx(label, buf, IM_ARRAYSIZE(buf), aabb.GetSize(), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_AutoSelectAll);
	if (g.ScalarAsInputTextId == 0)
	{
		// First frame
		IM_ASSERT(g.ActiveId == id);    // InputText ID expected to match the Slider ID (else we'd need to store them both, which is also possible)
		g.ScalarAsInputTextId = g.ActiveId;
		SetHoveredID(id);
	}
	else if (g.ActiveId != g.ScalarAsInputTextId)
	{
		// Release
		g.ScalarAsInputTextId = 0;
	}
	if (text_value_changed)
		return DataTypeApplyOpFromText(buf, GImGui->InputTextState.InitialText.begin(), data_type, data_ptr, NULL);
	return false;
}

// Parse display precision back from the display format string
int ImGui::ParseFormatPrecision(const char* fmt, int default_precision)
{
	int precision = default_precision;
	while ((fmt = strchr(fmt, '%')) != NULL)
	{
		fmt++;
		if (fmt[0] == '%') { fmt++; continue; } // Ignore "%%"
		while (*fmt >= '0' && *fmt <= '9')
			fmt++;
		if (*fmt == '.')
		{
			precision = atoi(fmt + 1);
			if (precision < 0 || precision > 10)
				precision = default_precision;
		}
		break;
	}
	return precision;
}

float ImGui::RoundScalar(float value, int decimal_precision)
{
	// Round past decimal precision
	// So when our value is 1.99999 with a precision of 0.001 we'll end up rounding to 2.0
	// FIXME: Investigate better rounding methods
	static const float min_steps[10] = { 1.0f, 0.1f, 0.01f, 0.001f, 0.0001f, 0.00001f, 0.000001f, 0.0000001f, 0.00000001f, 0.000000001f };
	float min_step = (decimal_precision >= 0 && decimal_precision < 10) ? min_steps[decimal_precision] : powf(10.0f, (float)-decimal_precision);
	bool negative = value < 0.0f;
	value = fabsf(value);
	float remainder = fmodf(value, min_step);
	if (remainder <= min_step * 0.5f)
		value -= remainder;
	else
		value += (min_step - remainder);
	return negative ? -value : value;
}

static inline float SliderBehaviorCalcRatioFromValue(float v, float v_min, float v_max, float power, float linear_zero_pos)
{
	if (v_min == v_max)
		return 0.0f;

	const bool is_non_linear = (power < 1.0f - 0.00001f) || (power > 1.0f + 0.00001f);
	const float v_clamped = (v_min < v_max) ? ImClamp(v, v_min, v_max) : ImClamp(v, v_max, v_min);
	if (is_non_linear)
	{
		if (v_clamped < 0.0f)
		{
			const float f = 1.0f - (v_clamped - v_min) / (ImMin(0.0f, v_max) - v_min);
			return (1.0f - powf(f, 1.0f / power)) * linear_zero_pos;
		}
		else
		{
			const float f = (v_clamped - ImMax(0.0f, v_min)) / (v_max - ImMax(0.0f, v_min));
			return linear_zero_pos + powf(f, 1.0f / power) * (1.0f - linear_zero_pos);
		}
	}

	// Linear slider
	return (v_clamped - v_min) / (v_max - v_min);
}

bool ImGui::SliderBehavior(const ImRect& frame_bb, ImGuiID id, float* v, float v_min, float v_max, float power, int decimal_precision, ImGuiSliderFlags flags, ImVec4 color)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();
	const ImGuiStyle& style = g.Style;

	// Draw frame
	RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

	const bool is_non_linear = (power < 1.0f - 0.00001f) || (power > 1.0f + 0.00001f);
	const bool is_horizontal = (flags & ImGuiSliderFlags_Vertical) == 0;

	const float grab_padding = 2.0f;
	const float slider_sz = is_horizontal ? (frame_bb.GetWidth() - grab_padding * 2.0f) : (frame_bb.GetHeight() - grab_padding * 2.0f);
	float grab_sz;
	if (decimal_precision > 0)
		grab_sz = ImMin(style.GrabMinSize, slider_sz);
	else
		grab_sz = ImMin(ImMax(1.0f * (slider_sz / ((v_min < v_max ? v_max - v_min : v_min - v_max) + 1.0f)), style.GrabMinSize), slider_sz);  // Integer sliders, if possible have the grab size represent 1 unit
	const float slider_usable_sz = slider_sz - grab_sz;
	const float slider_usable_pos_min = (is_horizontal ? frame_bb.Min.x : frame_bb.Min.y) + grab_padding + grab_sz * 0.5f;
	const float slider_usable_pos_max = (is_horizontal ? frame_bb.Max.x : frame_bb.Max.y) - grab_padding - grab_sz * 0.5f;

	// For logarithmic sliders that cross over sign boundary we want the exponential increase to be symmetric around 0.0f
	float linear_zero_pos = 0.0f;   // 0.0->1.0f
	if (v_min * v_max < 0.0f)
	{
		// Different sign
		const float linear_dist_min_to_0 = powf(fabsf(0.0f - v_min), 1.0f / power);
		const float linear_dist_max_to_0 = powf(fabsf(v_max - 0.0f), 1.0f / power);
		linear_zero_pos = linear_dist_min_to_0 / (linear_dist_min_to_0 + linear_dist_max_to_0);
	}
	else
	{
		// Same sign
		linear_zero_pos = v_min < 0.0f ? 1.0f : 0.0f;
	}

	// Process clicking on the slider
	bool value_changed = false;
	if (g.ActiveId == id)
	{
		if (g.IO.MouseDown[0])
		{
			const float mouse_abs_pos = is_horizontal ? g.IO.MousePos.x : g.IO.MousePos.y;
			float clicked_t = (slider_usable_sz > 0.0f) ? ImClamp((mouse_abs_pos - slider_usable_pos_min) / slider_usable_sz, 0.0f, 1.0f) : 0.0f;
			if (!is_horizontal)
				clicked_t = 1.0f - clicked_t;

			float new_value;
			if (is_non_linear)
			{
				// Account for logarithmic scale on both sides of the zero
				if (clicked_t < linear_zero_pos)
				{
					// Negative: rescale to the negative range before powering
					float a = 1.0f - (clicked_t / linear_zero_pos);
					a = powf(a, power);
					new_value = ImLerp(ImMin(v_max, 0.0f), v_min, a);
				}
				else
				{
					// Positive: rescale to the positive range before powering
					float a;
					if (fabsf(linear_zero_pos - 1.0f) > 1.e-6f)
						a = (clicked_t - linear_zero_pos) / (1.0f - linear_zero_pos);
					else
						a = clicked_t;
					a = powf(a, power);
					new_value = ImLerp(ImMax(v_min, 0.0f), v_max, a);
				}
			}
			else
			{
				// Linear slider
				new_value = ImLerp(v_min, v_max, clicked_t);
			}

			// Round past decimal precision
			new_value = RoundScalar(new_value, decimal_precision);
			if (*v != new_value)
			{
				*v = new_value;
				value_changed = true;
			}
		}
		else
		{
			ClearActiveID();
		}
	}

	// Calculate slider grab positioning
	float grab_t = SliderBehaviorCalcRatioFromValue(*v, v_min, v_max, power, linear_zero_pos);

	// Draw
	if (!is_horizontal)
		grab_t = 1.0f - grab_t;
	const float grab_pos = ImLerp(slider_usable_pos_min, slider_usable_pos_max, grab_t);
	ImRect grab_bb;
	if (is_horizontal)
		grab_bb = ImRect(ImVec2(grab_pos - grab_sz * 0.5f, frame_bb.Min.y), ImVec2(grab_pos + grab_sz * 0.5f, frame_bb.Max.y));
	else
		grab_bb = ImRect(ImVec2(frame_bb.Min.x + grab_padding, grab_pos - grab_sz * 0.5f), ImVec2(frame_bb.Max.x - grab_padding, grab_pos + grab_sz * 0.5f));
	window->DrawList->AddRectFilled(frame_bb.Min + ImVec2(2, 2), grab_bb.Max - ImVec2(0, 2), color.Empty() ? GetColorU32(ImGuiCol_SliderGrabActive) : GetColorU32(color), style.GrabRounding);

	return value_changed;
}

// Use power!=1.0 for logarithmic sliders.
// Adjust display_format to decorate the value with a prefix or a suffix.
//   "%.3f"         1.234
//   "%5.2f secs"   01.23 secs
//   "Gold: %.0f"   Gold: 1
bool ImGui::SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format, float power, ImVec2 size, ImVec4 color)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = CalcItemWidth();

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y*0.5f));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	// NB- we don't call ItemSize() yet because we may turn into a text edit box below
	if (!ItemAdd(total_bb, &id))
	{
		ItemSize(total_bb, style.FramePadding.y);
		return false;
	}

	const bool hovered = IsHovered(frame_bb, id);
	if (hovered)
		SetHoveredID(id);

	if (!display_format)
		display_format = "%.3f";
	int decimal_precision = ParseFormatPrecision(display_format, 3);

	// Tabbing or CTRL-clicking on Slider turns it into an input box
	bool start_text_input = false;
	const bool tab_focus_requested = FocusableItemRegister(window, g.ActiveId == id);
	if (tab_focus_requested || (hovered && g.IO.MouseClicked[0]))
	{
		SetActiveID(id, window);
		FocusWindow(window);

		if (tab_focus_requested || g.IO.KeyCtrl)
		{
			start_text_input = true;
			g.ScalarAsInputTextId = 0;
		}
	}
	if (start_text_input || (g.ActiveId == id && g.ScalarAsInputTextId == id))
		return InputScalarAsWidgetReplacement(frame_bb, label, ImGuiDataType_Float, v, id, decimal_precision);

	ItemSize(total_bb, style.FramePadding.y);

	// Actual slider behavior + render grab
	const bool value_changed = SliderBehavior(frame_bb, id, v, v_min, v_max, power, decimal_precision, 0, color);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + ImFormatString(value_buf, IM_ARRAYSIZE(value_buf), display_format, *v);
	RenderTextClipped(frame_bb.Min - ImVec2(0, 5), frame_bb.Max - ImVec2(8, 1), value_buf, value_buf_end, NULL, ImVec2(1.f, 1.f));


	if (label_size.x > 0.0f)
		RenderText(ImVec2(frame_bb.Min.x + style.ItemInnerSpacing.x, frame_bb.Min.y), label);

	return value_changed;
}

bool ImGui::VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* display_format, float power)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
	const ImRect bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(frame_bb, &id))
		return false;

	const bool hovered = IsHovered(frame_bb, id);
	if (hovered)
		SetHoveredID(id);

	if (!display_format)
		display_format = "%.3f";
	int decimal_precision = ParseFormatPrecision(display_format, 3);

	if (hovered && g.IO.MouseClicked[0])
	{
		SetActiveID(id, window);
		FocusWindow(window);
	}

	// Actual slider behavior + render grab
	bool value_changed = SliderBehavior(frame_bb, id, v, v_min, v_max, power, decimal_precision, ImGuiSliderFlags_Vertical);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	// For the vertical slider we allow centered text to overlap the frame padding
	char value_buf[64];
	char* value_buf_end = value_buf + ImFormatString(value_buf, IM_ARRAYSIZE(value_buf), display_format, *v);
	RenderTextClipped(ImVec2(frame_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.0f));
	if (label_size.x > 0.0f)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}

bool ImGui::SliderAngle(const char* label, float* v_rad, float v_degrees_min, float v_degrees_max)
{
	float v_deg = (*v_rad) * 360.0f / (2 * IM_PI);
	bool value_changed = SliderFloat(label, &v_deg, v_degrees_min, v_degrees_max, "%.0f deg", 1.0f);
	*v_rad = v_deg * (2 * IM_PI) / 360.0f;
	return value_changed;
}

bool ImGui::SliderInt(const char* label, int* v, int v_min, int v_max, const char* display_format, ImVec4 color)
{
	if (!display_format)
		display_format = "%.0f";
	float v_f = (float)*v;
	bool value_changed = SliderFloat(label, &v_f, (float)v_min, (float)v_max, display_format, 1.0f, ImVec2(0, 0), color);
	*v = (int)v_f;
	return value_changed;
}

bool ImGui::VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* display_format)
{
	if (!display_format)
		display_format = "%.0f";
	float v_f = (float)*v;
	bool value_changed = VSliderFloat(label, size, &v_f, (float)v_min, (float)v_max, display_format, 1.0f);
	*v = (int)v_f;
	return value_changed;
}

// Add multiple sliders on 1 line for compact edition of multiple components
bool ImGui::SliderFloatN(const char* label, float* v, int components, float v_min, float v_max, const char* display_format, float power)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	bool value_changed = false;
	BeginGroup();
	PushID(label);
	PushMultiItemsWidths(components);
	for (int i = 0; i < components; i++)
	{
		PushID(i);
		value_changed |= SliderFloat("##v", &v[i], v_min, v_max, display_format, power);
		SameLine(0, g.Style.ItemInnerSpacing.x);
		PopID();
		PopItemWidth();
	}
	PopID();

	TextUnformatted(label, FindRenderedTextEnd(label));
	EndGroup();

	return value_changed;
}

bool ImGui::SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* display_format, float power)
{
	return SliderFloatN(label, v, 2, v_min, v_max, display_format, power);
}

bool ImGui::SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* display_format, float power)
{
	return SliderFloatN(label, v, 3, v_min, v_max, display_format, power);
}

bool ImGui::SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* display_format, float power)
{
	return SliderFloatN(label, v, 4, v_min, v_max, display_format, power);
}

bool ImGui::SliderIntN(const char* label, int* v, int components, int v_min, int v_max, const char* display_format)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	bool value_changed = false;
	BeginGroup();
	PushID(label);
	PushMultiItemsWidths(components);
	for (int i = 0; i < components; i++)
	{
		PushID(i);
		value_changed |= SliderInt("##v", &v[i], v_min, v_max, display_format);
		SameLine(0, g.Style.ItemInnerSpacing.x);
		PopID();
		PopItemWidth();
	}
	PopID();

	TextUnformatted(label, FindRenderedTextEnd(label));
	EndGroup();

	return value_changed;
}

bool ImGui::SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* display_format)
{
	return SliderIntN(label, v, 2, v_min, v_max, display_format);
}

bool ImGui::SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* display_format)
{
	return SliderIntN(label, v, 3, v_min, v_max, display_format);
}

bool ImGui::SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format)
{
	return SliderIntN(label, v, 4, v_min, v_max, display_format);
}

bool ImGui::DragBehavior(const ImRect& frame_bb, ImGuiID id, float* v, float v_speed, float v_min, float v_max, int decimal_precision, float power)
{
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	// Draw frame
	const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, style.FrameRounding);

	bool value_changed = false;

	// Process clicking on the drag
	if (g.ActiveId == id)
	{
		if (g.IO.MouseDown[0])
		{
			if (g.ActiveIdIsJustActivated)
			{
				// Lock current value on click
				g.DragCurrentValue = *v;
				g.DragLastMouseDelta = ImVec2(0.f, 0.f);
			}

			float v_cur = g.DragCurrentValue;
			const ImVec2 mouse_drag_delta = GetMouseDragDelta(0, 1.0f);
			if (fabsf(mouse_drag_delta.x - g.DragLastMouseDelta.x) > 0.0f)
			{
				float speed = v_speed;
				if (speed == 0.0f && (v_max - v_min) != 0.0f && (v_max - v_min) < FLT_MAX)
					speed = (v_max - v_min) * g.DragSpeedDefaultRatio;
				if (g.IO.KeyShift && g.DragSpeedScaleFast >= 0.0f)
					speed = speed * g.DragSpeedScaleFast;
				if (g.IO.KeyAlt && g.DragSpeedScaleSlow >= 0.0f)
					speed = speed * g.DragSpeedScaleSlow;

				float delta = (mouse_drag_delta.x - g.DragLastMouseDelta.x) * speed;
				if (fabsf(power - 1.0f) > 0.001f)
				{
					// Logarithmic curve on both side of 0.0
					float v0_abs = v_cur >= 0.0f ? v_cur : -v_cur;
					float v0_sign = v_cur >= 0.0f ? 1.0f : -1.0f;
					float v1 = powf(v0_abs, 1.0f / power) + (delta * v0_sign);
					float v1_abs = v1 >= 0.0f ? v1 : -v1;
					float v1_sign = v1 >= 0.0f ? 1.0f : -1.0f;          // Crossed sign line
					v_cur = powf(v1_abs, power) * v0_sign * v1_sign;    // Reapply sign
				}
				else
				{
					v_cur += delta;
				}
				g.DragLastMouseDelta.x = mouse_drag_delta.x;

				// Clamp
				if (v_min < v_max)
					v_cur = ImClamp(v_cur, v_min, v_max);
				g.DragCurrentValue = v_cur;
			}

			// Round to user desired precision, then apply
			v_cur = RoundScalar(v_cur, decimal_precision);
			if (*v != v_cur)
			{
				*v = v_cur;
				value_changed = true;
			}
		}
		else
		{
			ClearActiveID();
		}
	}

	return value_changed;
}

bool ImGui::DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* display_format, float power)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = CalcItemWidth();

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y*2.0f));
	const ImRect inner_bb(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding);
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	// NB- we don't call ItemSize() yet because we may turn into a text edit box below
	if (!ItemAdd(total_bb, &id))
	{
		ItemSize(total_bb, style.FramePadding.y);
		return false;
	}

	const bool hovered = IsHovered(frame_bb, id);
	if (hovered)
		SetHoveredID(id);

	if (!display_format)
		display_format = "%.3f";
	int decimal_precision = ParseFormatPrecision(display_format, 3);

	// Tabbing or CTRL-clicking on Drag turns it into an input box
	bool start_text_input = false;
	const bool tab_focus_requested = FocusableItemRegister(window, g.ActiveId == id);
	if (tab_focus_requested || (hovered && (g.IO.MouseClicked[0] | g.IO.MouseDoubleClicked[0])))
	{
		SetActiveID(id, window);
		FocusWindow(window);

		if (tab_focus_requested || g.IO.KeyCtrl || g.IO.MouseDoubleClicked[0])
		{
			start_text_input = true;
			g.ScalarAsInputTextId = 0;
		}
	}
	if (start_text_input || (g.ActiveId == id && g.ScalarAsInputTextId == id))
		return InputScalarAsWidgetReplacement(frame_bb, label, ImGuiDataType_Float, v, id, decimal_precision);

	// Actual drag behavior
	ItemSize(total_bb, style.FramePadding.y);
	const bool value_changed = DragBehavior(frame_bb, id, v, v_speed, v_min, v_max, decimal_precision, power);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + ImFormatString(value_buf, IM_ARRAYSIZE(value_buf), display_format, *v);
	RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

	if (label_size.x > 0.0f)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, inner_bb.Min.y), label);

	return value_changed;
}

bool ImGui::DragFloatN(const char* label, float* v, int components, float v_speed, float v_min, float v_max, const char* display_format, float power)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	bool value_changed = false;
	BeginGroup();
	PushID(label);
	PushMultiItemsWidths(components);
	for (int i = 0; i < components; i++)
	{
		PushID(i);
		value_changed |= DragFloat("##v", &v[i], v_speed, v_min, v_max, display_format, power);
		SameLine(0, g.Style.ItemInnerSpacing.x);
		PopID();
		PopItemWidth();
	}
	PopID();

	TextUnformatted(label, FindRenderedTextEnd(label));
	EndGroup();

	return value_changed;
}

bool ImGui::DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* display_format, float power)
{
	return DragFloatN(label, v, 2, v_speed, v_min, v_max, display_format, power);
}

bool ImGui::DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* display_format, float power)
{
	return DragFloatN(label, v, 3, v_speed, v_min, v_max, display_format, power);
}

bool ImGui::DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* display_format, float power)
{
	return DragFloatN(label, v, 4, v_speed, v_min, v_max, display_format, power);
}

bool ImGui::DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed, float v_min, float v_max, const char* display_format, const char* display_format_max, float power)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	PushID(label);
	BeginGroup();
	PushMultiItemsWidths(2);

	bool value_changed = DragFloat("##min", v_current_min, v_speed, (v_min >= v_max) ? -FLT_MAX : v_min, (v_min >= v_max) ? *v_current_max : ImMin(v_max, *v_current_max), display_format, power);
	PopItemWidth();
	SameLine(0, g.Style.ItemInnerSpacing.x);
	value_changed |= DragFloat("##max", v_current_max, v_speed, (v_min >= v_max) ? *v_current_min : ImMax(v_min, *v_current_min), (v_min >= v_max) ? FLT_MAX : v_max, display_format_max ? display_format_max : display_format, power);
	PopItemWidth();
	SameLine(0, g.Style.ItemInnerSpacing.x);

	TextUnformatted(label, FindRenderedTextEnd(label));
	EndGroup();
	PopID();

	return value_changed;
}

// NB: v_speed is float to allow adjusting the drag speed with more precision
bool ImGui::DragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* display_format)
{
	if (!display_format)
		display_format = "%.0f";
	float v_f = (float)*v;
	bool value_changed = DragFloat(label, &v_f, v_speed, (float)v_min, (float)v_max, display_format);
	*v = (int)v_f;
	return value_changed;
}

bool ImGui::DragIntN(const char* label, int* v, int components, float v_speed, int v_min, int v_max, const char* display_format)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	bool value_changed = false;
	BeginGroup();
	PushID(label);
	PushMultiItemsWidths(components);
	for (int i = 0; i < components; i++)
	{
		PushID(i);
		value_changed |= DragInt("##v", &v[i], v_speed, v_min, v_max, display_format);
		SameLine(0, g.Style.ItemInnerSpacing.x);
		PopID();
		PopItemWidth();
	}
	PopID();

	TextUnformatted(label, FindRenderedTextEnd(label));
	EndGroup();

	return value_changed;
}

bool ImGui::DragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* display_format)
{
	return DragIntN(label, v, 2, v_speed, v_min, v_max, display_format);
}

bool ImGui::DragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* display_format)
{
	return DragIntN(label, v, 3, v_speed, v_min, v_max, display_format);
}

bool ImGui::DragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* display_format)
{
	return DragIntN(label, v, 4, v_speed, v_min, v_max, display_format);
}

bool ImGui::DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed, int v_min, int v_max, const char* display_format, const char* display_format_max)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	PushID(label);
	BeginGroup();
	PushMultiItemsWidths(2);

	bool value_changed = DragInt("##min", v_current_min, v_speed, (v_min >= v_max) ? INT_MIN : v_min, (v_min >= v_max) ? *v_current_max : ImMin(v_max, *v_current_max), display_format);
	PopItemWidth();
	SameLine(0, g.Style.ItemInnerSpacing.x);
	value_changed |= DragInt("##max", v_current_max, v_speed, (v_min >= v_max) ? *v_current_min : ImMax(v_min, *v_current_min), (v_min >= v_max) ? INT_MAX : v_max, display_format_max ? display_format_max : display_format);
	PopItemWidth();
	SameLine(0, g.Style.ItemInnerSpacing.x);

	TextUnformatted(label, FindRenderedTextEnd(label));
	EndGroup();
	PopID();

	return value_changed;
}

void ImGui::PlotEx(ImGuiPlotType plot_type, const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	if (graph_size.x == 0.0f)
		graph_size.x = CalcItemWidth();
	if (graph_size.y == 0.0f)
		graph_size.y = label_size.y + (style.FramePadding.y * 2);

	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(graph_size.x, graph_size.y));
	const ImRect inner_bb(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding);
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0));
	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, NULL))
		return;

	// Determine scale from values if not specified
	if (scale_min == FLT_MAX || scale_max == FLT_MAX)
	{
		float v_min = FLT_MAX;
		float v_max = -FLT_MAX;
		for (int i = 0; i < values_count; i++)
		{
			const float v = values_getter(data, i);
			v_min = ImMin(v_min, v);
			v_max = ImMax(v_max, v);
		}
		if (scale_min == FLT_MAX)
			scale_min = v_min;
		if (scale_max == FLT_MAX)
			scale_max = v_max;
	}

	RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

	if (values_count > 0)
	{
		int res_w = ImMin((int)graph_size.x, values_count) + ((plot_type == ImGuiPlotType_Lines) ? -1 : 0);
		int item_count = values_count + ((plot_type == ImGuiPlotType_Lines) ? -1 : 0);

		// Tooltip on hover
		int v_hovered = -1;
		if (IsHovered(inner_bb, 0))
		{
			const float t = ImClamp((g.IO.MousePos.x - inner_bb.Min.x) / (inner_bb.Max.x - inner_bb.Min.x), 0.0f, 0.9999f);
			const int v_idx = (int)(t * item_count);
			IM_ASSERT(v_idx >= 0 && v_idx < values_count);

			const float v0 = values_getter(data, (v_idx + values_offset) % values_count);
			const float v1 = values_getter(data, (v_idx + 1 + values_offset) % values_count);
			if (plot_type == ImGuiPlotType_Lines)
				SetTooltip("%d: %8.4g\n%d: %8.4g", v_idx, v0, v_idx + 1, v1);
			else if (plot_type == ImGuiPlotType_Histogram)
				SetTooltip("%d: %8.4g", v_idx, v0);
			v_hovered = v_idx;
		}

		const float t_step = 1.0f / (float)res_w;

		float v0 = values_getter(data, (0 + values_offset) % values_count);
		float t0 = 0.0f;
		ImVec2 tp0 = ImVec2(t0, 1.0f - ImSaturate((v0 - scale_min) / (scale_max - scale_min)));    // Point in the normalized space of our target rectangle

		const ImU32 col_base = GetColorU32((plot_type == ImGuiPlotType_Lines) ? ImGuiCol_PlotLines : ImGuiCol_PlotHistogram);
		const ImU32 col_hovered = GetColorU32((plot_type == ImGuiPlotType_Lines) ? ImGuiCol_PlotLinesHovered : ImGuiCol_PlotHistogramHovered);

		for (int n = 0; n < res_w; n++)
		{
			const float t1 = t0 + t_step;
			const int v1_idx = (int)(t0 * item_count + 0.5f);
			IM_ASSERT(v1_idx >= 0 && v1_idx < values_count);
			const float v1 = values_getter(data, (v1_idx + values_offset + 1) % values_count);
			const ImVec2 tp1 = ImVec2(t1, 1.0f - ImSaturate((v1 - scale_min) / (scale_max - scale_min)));

			// NB: Draw calls are merged together by the DrawList system. Still, we should render our batch are lower level to save a bit of CPU.
			ImVec2 pos0 = ImLerp(inner_bb.Min, inner_bb.Max, tp0);
			ImVec2 pos1 = ImLerp(inner_bb.Min, inner_bb.Max, (plot_type == ImGuiPlotType_Lines) ? tp1 : ImVec2(tp1.x, 1.0f));
			if (plot_type == ImGuiPlotType_Lines)
			{
				window->DrawList->AddLine(pos0, pos1, v_hovered == v1_idx ? col_hovered : col_base);
			}
			else if (plot_type == ImGuiPlotType_Histogram)
			{
				if (pos1.x >= pos0.x + 2.0f)
					pos1.x -= 1.0f;
				window->DrawList->AddRectFilled(pos0, pos1, v_hovered == v1_idx ? col_hovered : col_base);
			}

			t0 = t1;
			tp0 = tp1;
		}
	}

	// Text overlay
	if (overlay_text)
		RenderTextClipped(ImVec2(frame_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), frame_bb.Max, overlay_text, NULL, NULL, ImVec2(0.5f, 0.0f));

	if (label_size.x > 0.0f)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, inner_bb.Min.y), label);
}

struct ImGuiPlotArrayGetterData
{
	const float* Values;
	int Stride;

	ImGuiPlotArrayGetterData(const float* values, int stride) { Values = values; Stride = stride; }
};

static float Plot_ArrayGetter(void* data, int idx)
{
	ImGuiPlotArrayGetterData* plot_data = (ImGuiPlotArrayGetterData*)data;
	const float v = *(float*)(void*)((unsigned char*)plot_data->Values + (size_t)idx * plot_data->Stride);
	return v;
}

void ImGui::PlotLines(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size, int stride)
{
	ImGuiPlotArrayGetterData data(values, stride);
	PlotEx(ImGuiPlotType_Lines, label, &Plot_ArrayGetter, (void*)&data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
}

void ImGui::PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
{
	PlotEx(ImGuiPlotType_Lines, label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
}

void ImGui::PlotHistogram(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size, int stride)
{
	ImGuiPlotArrayGetterData data(values, stride);
	PlotEx(ImGuiPlotType_Histogram, label, &Plot_ArrayGetter, (void*)&data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
}

void ImGui::PlotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
{
	PlotEx(ImGuiPlotType_Histogram, label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
}

// size_arg (for each axis) < 0.0f: align to end, 0.0f: auto, > 0.0f: specified size
void ImGui::ProgressBar(float fraction, const ImVec2& size_arg, const char* overlay)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	ImVec2 pos = window->DC.CursorPos;
	ImRect bb(pos, pos + CalcItemSize(size_arg, CalcItemWidth(), g.FontSize + style.FramePadding.y*2.0f));
	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(bb, NULL))
		return;

	// Render
	fraction = ImSaturate(fraction);
	RenderFrame(bb.Min, bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
	bb.Reduce(ImVec2(window->BorderSize, window->BorderSize));
	const ImVec2 fill_br = ImVec2(ImLerp(bb.Min.x, bb.Max.x, fraction), bb.Max.y);
	RenderFrame(bb.Min, fill_br, GetColorU32(ImGuiCol_PlotHistogram), false, style.FrameRounding);

	// Default displaying the fraction as percentage string, but user can override it
	char overlay_buf[32];
	if (!overlay)
	{
		ImFormatString(overlay_buf, IM_ARRAYSIZE(overlay_buf), "%.0f%%", fraction * 100 + 0.01f);
		overlay = overlay_buf;
	}

	ImVec2 overlay_size = CalcTextSize(overlay, NULL);
	if (overlay_size.x > 0.0f)
		RenderTextClipped(ImVec2(ImClamp(fill_br.x + style.ItemSpacing.x, bb.Min.x, bb.Max.x - overlay_size.x - style.ItemInnerSpacing.x), bb.Min.y), bb.Max, overlay, NULL, &overlay_size, ImVec2(0.0f, 0.5f), &bb);
}

bool ImGui::Checkbox(const char* label, bool* v)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = ImGuiStyle::ImGuiStyle();
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImVec2 pading = ImVec2(2, 2);
	const ImRect check_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(label_size.y + style.FramePadding.x * 6, label_size.y + style.FramePadding.y / 2));
	ItemSize(check_bb, style.FramePadding.y);
	ImRect total_bb = check_bb;
	if (label_size.x > 0)
		SameLine(0, style.ItemInnerSpacing.x);
	const ImRect text_bb(window->DC.CursorPos + ImVec2(0, style.FramePadding.y), window->DC.CursorPos + ImVec2(0, style.FramePadding.y) + label_size);
	if (label_size.x > 0)
	{
		ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
		total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
	}
	if (!ItemAdd(total_bb, &id))
		return false;
	bool hovered, held;
	bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
		*v = !(*v);
	const float check_sz = ImMin(check_bb.GetWidth(), check_bb.GetHeight());
	const float check_sz2 = check_sz / 2;
	const float pad = ImMax(1.0f, (float)(int)(check_sz / 4.f));
	//window->DrawList->AddRectFilled(check_bb.Min+ImVec2(pad,pad), check_bb.Max-ImVec2(pad,pad), GetColorU32(ImGuiCol_CheckMark), style.FrameRounding);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 5, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 4, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 3, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 2, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 1, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 1, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 2, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 3, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 4, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 5, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), 12);
	if (*v)//от исовка галочки
	{
		//window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2, check_bb.Min.y), check_bb.Max, GetColorU32(ImVec4(0.34f, 1.0f, 0.54f, 1.0f)), 0);
		//window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2, check_bb.Min.y), check_bb.Max, GetColorU32(ImVec4(0.34f, 1.0f, 0.54f, 1.0f)), 0);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 5, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 4, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 3, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 2, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 1, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 1, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 2, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 3, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 4, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 5, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(0.50f, 0.69f, 1.0f, 1.0f)), 12);
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 + 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), 12);
	}
	else
	{
		window->DrawList->AddCircleFilled(ImVec2(check_bb.Min.x + (check_bb.Max.x - check_bb.Min.x) / 2 - 6, check_bb.Min.y + 9), 7, GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), 12);
	}
	if (label_size.x > 0.0f)
		RenderText(text_bb.GetTL(), label);
	return pressed;
}

bool ImGui::CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value)
{
	bool v = ((*flags & flags_value) == flags_value);
	bool pressed = Checkbox(label, &v);
	if (pressed)
	{
		if (v)
			*flags |= flags_value;
		else
			*flags &= ~flags_value;
	}

	return pressed;
}

bool ImGui::RadioButton(const char* label, bool active)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);

	const ImRect check_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(label_size.y + style.FramePadding.y * 2 - 1, label_size.y + style.FramePadding.y * 2 - 1));
	ItemSize(check_bb, style.FramePadding.y);

	ImRect total_bb = check_bb;
	if (label_size.x > 0)
		SameLine(0, style.ItemInnerSpacing.x);
	const ImRect text_bb(window->DC.CursorPos + ImVec2(0, style.FramePadding.y), window->DC.CursorPos + ImVec2(0, style.FramePadding.y) + label_size);
	if (label_size.x > 0)
	{
		ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
		total_bb.Add(text_bb);
	}

	if (!ItemAdd(total_bb, &id))
		return false;

	ImVec2 center = check_bb.GetCenter();
	center.x = (float)(int)center.x + 0.5f;
	center.y = (float)(int)center.y + 0.5f;
	const float radius = check_bb.GetHeight() * 0.5f;

	bool hovered, held;
	bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);

	window->DrawList->AddCircleFilled(center, radius, GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
	if (active)
	{
		const float check_sz = ImMin(check_bb.GetWidth(), check_bb.GetHeight());
		const float pad = ImMax(1.0f, (float)(int)(check_sz / 6.0f));
		window->DrawList->AddCircleFilled(center, radius - pad, GetColorU32(ImGuiCol_CheckMark), 16);
	}

	if (window->Flags & ImGuiWindowFlags_ShowBorders)
	{
		window->DrawList->AddCircle(center + ImVec2(1, 1), radius, GetColorU32(ImGuiCol_BorderShadow), 16);
		window->DrawList->AddCircle(center, radius, GetColorU32(ImGuiCol_Border), 16);
	}

	if (g.LogEnabled)
		LogRenderedText(text_bb.GetTL(), active ? "(x)" : "( )");
	if (label_size.x > 0.0f)
		RenderText(text_bb.GetTL(), label);

	return pressed;
}

bool ImGui::RadioButton(const char* label, int* v, int v_button)
{
	const bool pressed = RadioButton(label, *v == v_button);
	if (pressed)
	{
		*v = v_button;
	}
	return pressed;
}

static int InputTextCalcTextLenAndLineCount(const char* text_begin, const char** out_text_end)
{
	int line_count = 0;
	const char* s = text_begin;
	while (char c = *s++) // We are only matching for \n so we can ignore UTF-8 decoding
		if (c == '\n')
			line_count++;
	s--;
	if (s[0] != '\n' && s[0] != '\r')
		line_count++;
	*out_text_end = s;
	return line_count;
}

static ImVec2 InputTextCalcTextSizeW(const ImWchar* text_begin, const ImWchar* text_end, const ImWchar** remaining, ImVec2* out_offset, bool stop_on_new_line)
{
	ImFont* font = GImGui->Font;
	const float line_height = GImGui->FontSize;
	const float scale = line_height / font->FontSize;

	ImVec2 text_size = ImVec2(0, 0);
	float line_width = 0.0f;

	const ImWchar* s = text_begin;
	while (s < text_end)
	{
		unsigned int c = (unsigned int)(*s++);
		if (c == '\n')
		{
			text_size.x = ImMax(text_size.x, line_width);
			text_size.y += line_height;
			line_width = 0.0f;
			if (stop_on_new_line)
				break;
			continue;
		}
		if (c == '\r')
			continue;

		const float char_width = font->GetCharAdvance((unsigned short)c) * scale;
		line_width += char_width;
	}

	if (text_size.x < line_width)
		text_size.x = line_width;

	if (out_offset)
		*out_offset = ImVec2(line_width, text_size.y + line_height);  // offset allow for the possibility of sitting after a trailing \n

	if (line_width > 0 || text_size.y == 0.0f)                        // whereas size.y will ignore the trailing \n
		text_size.y += line_height;

	if (remaining)
		*remaining = s;

	return text_size;
}

// Wrapper for stb_textedit.h to edit text (our wrapper is for: statically sized buffer, single-line, wchar characters. InputText converts between UTF-8 and wchar)
namespace ImGuiStb
{

	static int     STB_TEXTEDIT_STRINGLEN(const STB_TEXTEDIT_STRING* obj) { return obj->CurLenW; }
	static ImWchar STB_TEXTEDIT_GETCHAR(const STB_TEXTEDIT_STRING* obj, int idx) { return obj->Text[idx]; }
	static float   STB_TEXTEDIT_GETWIDTH(STB_TEXTEDIT_STRING* obj, int line_start_idx, int char_idx) { ImWchar c = obj->Text[line_start_idx + char_idx]; if (c == '\n') return STB_TEXTEDIT_GETWIDTH_NEWLINE; return GImGui->Font->GetCharAdvance(c) * (GImGui->FontSize / GImGui->Font->FontSize); }
	static int     STB_TEXTEDIT_KEYTOTEXT(int key) { return key >= 0x10000 ? 0 : key; }
	static ImWchar STB_TEXTEDIT_NEWLINE = '\n';
	static void    STB_TEXTEDIT_LAYOUTROW(StbTexteditRow* r, STB_TEXTEDIT_STRING* obj, int line_start_idx)
	{
		const ImWchar* text = obj->Text.Data;
		const ImWchar* text_remaining = NULL;
		const ImVec2 size = InputTextCalcTextSizeW(text + line_start_idx, text + obj->CurLenW, &text_remaining, NULL, true);
		r->x0 = 0.0f;
		r->x1 = size.x;
		r->baseline_y_delta = size.y;
		r->ymin = 0.0f;
		r->ymax = size.y;
		r->num_chars = (int)(text_remaining - (text + line_start_idx));
	}

	static bool is_separator(unsigned int c) { return ImCharIsSpace(c) || c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == '|'; }
	static int  is_word_boundary_from_right(STB_TEXTEDIT_STRING* obj, int idx) { return idx > 0 ? (is_separator(obj->Text[idx - 1]) && !is_separator(obj->Text[idx])) : 1; }
	static int  STB_TEXTEDIT_MOVEWORDLEFT_IMPL(STB_TEXTEDIT_STRING* obj, int idx) { idx--; while (idx >= 0 && !is_word_boundary_from_right(obj, idx)) idx--; return idx < 0 ? 0 : idx; }
#ifdef __APPLE__    // FIXME: Move setting to IO structure
	static int  is_word_boundary_from_left(STB_TEXTEDIT_STRING* obj, int idx) { return idx > 0 ? (!is_separator(obj->Text[idx - 1]) && is_separator(obj->Text[idx])) : 1; }
	static int  STB_TEXTEDIT_MOVEWORDRIGHT_IMPL(STB_TEXTEDIT_STRING* obj, int idx) { idx++; int len = obj->CurLenW; while (idx < len && !is_word_boundary_from_left(obj, idx)) idx++; return idx > len ? len : idx; }
#else
	static int  STB_TEXTEDIT_MOVEWORDRIGHT_IMPL(STB_TEXTEDIT_STRING* obj, int idx) { idx++; int len = obj->CurLenW; while (idx < len && !is_word_boundary_from_right(obj, idx)) idx++; return idx > len ? len : idx; }
#endif
#define STB_TEXTEDIT_MOVEWORDLEFT   STB_TEXTEDIT_MOVEWORDLEFT_IMPL    // They need to be #define for stb_textedit.h
#define STB_TEXTEDIT_MOVEWORDRIGHT  STB_TEXTEDIT_MOVEWORDRIGHT_IMPL

	static void STB_TEXTEDIT_DELETECHARS(STB_TEXTEDIT_STRING* obj, int pos, int n)
	{
		ImWchar* dst = obj->Text.Data + pos;

		// We maintain our buffer length in both UTF-8 and wchar formats
		obj->CurLenA -= ImTextCountUtf8BytesFromStr(dst, dst + n);
		obj->CurLenW -= n;

		// Offset remaining text
		const ImWchar* src = obj->Text.Data + pos + n;
		while (ImWchar c = *src++)
			*dst++ = c;
		*dst = '\0';
	}

	static bool STB_TEXTEDIT_INSERTCHARS(STB_TEXTEDIT_STRING* obj, int pos, const ImWchar* new_text, int new_text_len)
	{
		const int text_len = obj->CurLenW;
		IM_ASSERT(pos <= text_len);
		if (new_text_len + text_len + 1 > obj->Text.Size)
			return false;

		const int new_text_len_utf8 = ImTextCountUtf8BytesFromStr(new_text, new_text + new_text_len);
		if (new_text_len_utf8 + obj->CurLenA + 1 > obj->BufSizeA)
			return false;

		ImWchar* text = obj->Text.Data;
		if (pos != text_len)
			memmove(text + pos + new_text_len, text + pos, (size_t)(text_len - pos) * sizeof(ImWchar));
		memcpy(text + pos, new_text, (size_t)new_text_len * sizeof(ImWchar));

		obj->CurLenW += new_text_len;
		obj->CurLenA += new_text_len_utf8;
		obj->Text[obj->CurLenW] = '\0';

		return true;
	}

	// We don't use an enum so we can build even with conflicting symbols (if another user of stb_textedit.h leak their STB_TEXTEDIT_K_* symbols)
#define STB_TEXTEDIT_K_LEFT         0x10000 // keyboard input to move cursor left
#define STB_TEXTEDIT_K_RIGHT        0x10001 // keyboard input to move cursor right
#define STB_TEXTEDIT_K_UP           0x10002 // keyboard input to move cursor up
#define STB_TEXTEDIT_K_DOWN         0x10003 // keyboard input to move cursor down
#define STB_TEXTEDIT_K_LINESTART    0x10004 // keyboard input to move cursor to start of line
#define STB_TEXTEDIT_K_LINEEND      0x10005 // keyboard input to move cursor to end of line
#define STB_TEXTEDIT_K_TEXTSTART    0x10006 // keyboard input to move cursor to start of text
#define STB_TEXTEDIT_K_TEXTEND      0x10007 // keyboard input to move cursor to end of text
#define STB_TEXTEDIT_K_DELETE       0x10008 // keyboard input to delete selection or character under cursor
#define STB_TEXTEDIT_K_BACKSPACE    0x10009 // keyboard input to delete selection or character left of cursor
#define STB_TEXTEDIT_K_UNDO         0x1000A // keyboard input to perform undo
#define STB_TEXTEDIT_K_REDO         0x1000B // keyboard input to perform redo
#define STB_TEXTEDIT_K_WORDLEFT     0x1000C // keyboard input to move cursor left one word
#define STB_TEXTEDIT_K_WORDRIGHT    0x1000D // keyboard input to move cursor right one word
#define STB_TEXTEDIT_K_SHIFT        0x20000

#define STB_TEXTEDIT_IMPLEMENTATION
#include "stb_textedit.h"

}

void ImGuiTextEditState::OnKeyPressed(int key)
{
	stb_textedit_key(this, &StbState, key);
	CursorFollow = true;
	CursorAnimReset();
}

// Public API to manipulate UTF-8 text
// We expose UTF-8 to the user (unlike the STB_TEXTEDIT_* functions which are manipulating wchar)
// FIXME: The existence of this rarely exercised code path is a bit of a nuisance.
void ImGuiTextEditCallbackData::DeleteChars(int pos, int bytes_count)
{
	IM_ASSERT(pos + bytes_count <= BufTextLen);
	char* dst = Buf + pos;
	const char* src = Buf + pos + bytes_count;
	while (char c = *src++)
		*dst++ = c;
	*dst = '\0';

	if (CursorPos + bytes_count >= pos)
		CursorPos -= bytes_count;
	else if (CursorPos >= pos)
		CursorPos = pos;
	SelectionStart = SelectionEnd = CursorPos;
	BufDirty = true;
	BufTextLen -= bytes_count;
}

void ImGuiTextEditCallbackData::InsertChars(int pos, const char* new_text, const char* new_text_end)
{
	const int new_text_len = new_text_end ? (int)(new_text_end - new_text) : (int)strlen(new_text);
	if (new_text_len + BufTextLen + 1 >= BufSize)
		return;

	if (BufTextLen != pos)
		memmove(Buf + pos + new_text_len, Buf + pos, (size_t)(BufTextLen - pos));
	memcpy(Buf + pos, new_text, (size_t)new_text_len * sizeof(char));
	Buf[BufTextLen + new_text_len] = '\0';

	if (CursorPos >= pos)
		CursorPos += new_text_len;
	SelectionStart = SelectionEnd = CursorPos;
	BufDirty = true;
	BufTextLen += new_text_len;
}

// Return false to discard a character.
static bool InputTextFilterCharacter(unsigned int* p_char, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data)
{
	unsigned int c = *p_char;

	if (c < 128 && c != ' ' && !isprint((int)(c & 0xFF)))
	{
		bool pass = false;
		pass |= (c == '\n' && (flags & ImGuiInputTextFlags_Multiline));
		pass |= (c == '\t' && (flags & ImGuiInputTextFlags_AllowTabInput));
		if (!pass)
			return false;
	}

	if (c >= 0xE000 && c <= 0xF8FF) // Filter private Unicode range. I don't imagine anybody would want to input them. GLFW on OSX seems to send private characters for special keys like arrow keys.
		return false;

	if (flags & (ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank))
	{
		if (flags & ImGuiInputTextFlags_CharsDecimal)
			if (!(c >= '0' && c <= '9') && (c != '.') && (c != '-') && (c != '+') && (c != '*') && (c != '/'))
				return false;

		if (flags & ImGuiInputTextFlags_CharsHexadecimal)
			if (!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F'))
				return false;

		if (flags & ImGuiInputTextFlags_CharsUppercase)
			if (c >= 'a' && c <= 'z')
				*p_char = (c += (unsigned int)('A' - 'a'));

		if (flags & ImGuiInputTextFlags_CharsNoBlank)
			if (ImCharIsSpace(c))
				return false;
	}

	if (flags & ImGuiInputTextFlags_CallbackCharFilter)
	{
		ImGuiTextEditCallbackData callback_data;
		memset(&callback_data, 0, sizeof(ImGuiTextEditCallbackData));
		callback_data.EventFlag = ImGuiInputTextFlags_CallbackCharFilter;
		callback_data.EventChar = (ImWchar)c;
		callback_data.Flags = flags;
		callback_data.UserData = user_data;
		if (callback(&callback_data) != 0)
			return false;
		*p_char = callback_data.EventChar;
		if (!callback_data.EventChar)
			return false;
	}

	return true;
}

// Edit a string of text
// NB: when active, hold on a privately held copy of the text (and apply back to 'buf'). So changing 'buf' while active has no effect.
// FIXME: Rather messy function partly because we are doing UTF8 > u16 > UTF8 conversions on the go to more easily handle stb_textedit calls. Ideally we should stay in UTF-8 all the time. See https://github.com/nothings/stb/issues/188
bool ImGui::InputTextEx(const char* label, char* buf, int buf_size, const ImVec2& size_arg, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	IM_ASSERT(!((flags & ImGuiInputTextFlags_CallbackHistory) && (flags & ImGuiInputTextFlags_Multiline))); // Can't use both together (they both use up/down keys)
	IM_ASSERT(!((flags & ImGuiInputTextFlags_CallbackCompletion) && (flags & ImGuiInputTextFlags_AllowTabInput))); // Can't use both together (they both use tab key)

	ImGuiContext& g = *GImGui;
	const ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const bool is_multiline = (flags & ImGuiInputTextFlags_Multiline) != 0;
	const bool is_editable = (flags & ImGuiInputTextFlags_ReadOnly) == 0;
	const bool is_password = (flags & ImGuiInputTextFlags_Password) != 0;

	if (is_multiline) // Open group before calling GetID() because groups tracks id created during their spawn
		BeginGroup();
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	ImVec2 size = CalcItemSize(size_arg, CalcItemWidth(), (is_multiline ? GetTextLineHeight() * 8.0f : label_size.y) + style.FramePadding.y*2.0f); // Arbitrary default of 8 lines high for multi-line
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? (style.ItemInnerSpacing.x + label_size.x) : 0.0f, 0.0f));

	ImGuiWindow* draw_window = window;
	if (is_multiline)
	{
		if (!BeginChildFrame(id, frame_bb.GetSize()))
		{
			EndChildFrame();
			EndGroup();
			return false;
		}
		draw_window = GetCurrentWindow();
		size.x -= draw_window->ScrollbarSizes.x;
	}
	else
	{
		ItemSize(total_bb, style.FramePadding.y);
		if (!ItemAdd(total_bb, &id))
			return false;
	}

	// Password pushes a temporary font with only a fallback glyph
	if (is_password)
	{
		const ImFont::Glyph* glyph = g.Font->FindGlyph('*');
		ImFont* password_font = &g.InputTextPasswordFont;
		password_font->FontSize = g.Font->FontSize;
		password_font->Scale = g.Font->Scale;
		password_font->DisplayOffset = g.Font->DisplayOffset;
		password_font->Ascent = g.Font->Ascent;
		password_font->Descent = g.Font->Descent;
		password_font->ContainerAtlas = g.Font->ContainerAtlas;
		password_font->FallbackGlyph = glyph;
		password_font->FallbackXAdvance = glyph->XAdvance;
		IM_ASSERT(password_font->Glyphs.empty() && password_font->IndexXAdvance.empty() && password_font->IndexLookup.empty());
		PushFont(password_font);
	}

	// NB: we are only allowed to access 'edit_state' if we are the active widget.
	ImGuiTextEditState& edit_state = g.InputTextState;

	const bool focus_requested = FocusableItemRegister(window, g.ActiveId == id, (flags & (ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_AllowTabInput)) == 0);    // Using completion callback disable keyboard tabbing
	const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = IsHovered(frame_bb, id);
	if (hovered)
	{
		SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}
	const bool user_clicked = hovered && io.MouseClicked[0];
	const bool user_scrolled = is_multiline && g.ActiveId == 0 && edit_state.Id == id && g.ActiveIdPreviousFrame == draw_window->GetIDNoKeepAlive("#SCROLLY");

	bool select_all = (g.ActiveId != id) && (flags & ImGuiInputTextFlags_AutoSelectAll) != 0;
	if (focus_requested || user_clicked || user_scrolled)
	{
		if (g.ActiveId != id)
		{
			// Start edition
			// Take a copy of the initial buffer value (both in original UTF-8 format and converted to wchar)
			// From the moment we focused we are ignoring the content of 'buf' (unless we are in read-only mode)
			const int prev_len_w = edit_state.CurLenW;
			edit_state.Text.resize(buf_size + 1);        // wchar count <= UTF-8 count. we use +1 to make sure that .Data isn't NULL so it doesn't crash.
			edit_state.InitialText.resize(buf_size + 1); // UTF-8. we use +1 to make sure that .Data isn't NULL so it doesn't crash.
			ImStrncpy(edit_state.InitialText.Data, buf, edit_state.InitialText.Size);
			const char* buf_end = NULL;
			edit_state.CurLenW = ImTextStrFromUtf8(edit_state.Text.Data, edit_state.Text.Size, buf, NULL, &buf_end);
			edit_state.CurLenA = (int)(buf_end - buf); // We can't get the result from ImFormatString() above because it is not UTF-8 aware. Here we'll cut off malformed UTF-8.
			edit_state.CursorAnimReset();

			// Preserve cursor position and undo/redo stack if we come back to same widget
			// FIXME: We should probably compare the whole buffer to be on the safety side. Comparing buf (utf8) and edit_state.Text (wchar).
			const bool recycle_state = (edit_state.Id == id) && (prev_len_w == edit_state.CurLenW);
			if (recycle_state)
			{
				// Recycle existing cursor/selection/undo stack but clamp position
				// Note a single mouse click will override the cursor/position immediately by calling stb_textedit_click handler.
				edit_state.CursorClamp();
			}
			else
			{
				edit_state.Id = id;
				edit_state.ScrollX = 0.0f;
				stb_textedit_initialize_state(&edit_state.StbState, !is_multiline);
				if (!is_multiline && focus_requested_by_code)
					select_all = true;
			}
			if (flags & ImGuiInputTextFlags_AlwaysInsertMode)
				edit_state.StbState.insert_mode = true;
			if (!is_multiline && (focus_requested_by_tab || (user_clicked && io.KeyCtrl)))
				select_all = true;
		}
		SetActiveID(id, window);
		FocusWindow(window);
	}
	else if (io.MouseClicked[0])
	{
		// Release focus when we click outside
		if (g.ActiveId == id)
			ClearActiveID();
	}

	bool value_changed = false;
	bool enter_pressed = false;

	if (g.ActiveId == id)
	{
		if (!is_editable && !g.ActiveIdIsJustActivated)
		{
			// When read-only we always use the live data passed to the function
			edit_state.Text.resize(buf_size + 1);
			const char* buf_end = NULL;
			edit_state.CurLenW = ImTextStrFromUtf8(edit_state.Text.Data, edit_state.Text.Size, buf, NULL, &buf_end);
			edit_state.CurLenA = (int)(buf_end - buf);
			edit_state.CursorClamp();
		}

		edit_state.BufSizeA = buf_size;

		// Although we are active we don't prevent mouse from hovering other elements unless we are interacting right now with the widget.
		// Down the line we should have a cleaner library-wide concept of Selected vs Active.
		g.ActiveIdAllowOverlap = !io.MouseDown[0];

		// Edit in progress
		const float mouse_x = (io.MousePos.x - frame_bb.Min.x - style.FramePadding.x) + edit_state.ScrollX;
		const float mouse_y = (is_multiline ? (io.MousePos.y - draw_window->DC.CursorPos.y - style.FramePadding.y) : (g.FontSize*0.5f));

		const bool osx_double_click_selects_words = io.OSXBehaviors;      // OS X style: Double click selects by word instead of selecting whole text
		if (select_all || (hovered && !osx_double_click_selects_words && io.MouseDoubleClicked[0]))
		{
			edit_state.SelectAll();
			edit_state.SelectedAllMouseLock = true;
		}
		else if (hovered && osx_double_click_selects_words && io.MouseDoubleClicked[0])
		{
			// Select a word only, OS X style (by simulating keystrokes)
			edit_state.OnKeyPressed(STB_TEXTEDIT_K_WORDLEFT);
			edit_state.OnKeyPressed(STB_TEXTEDIT_K_WORDRIGHT | STB_TEXTEDIT_K_SHIFT);
		}
		else if (io.MouseClicked[0] && !edit_state.SelectedAllMouseLock)
		{
			stb_textedit_click(&edit_state, &edit_state.StbState, mouse_x, mouse_y);
			edit_state.CursorAnimReset();
		}
		else if (io.MouseDown[0] && !edit_state.SelectedAllMouseLock && (io.MouseDelta.x != 0.0f || io.MouseDelta.y != 0.0f))
		{
			stb_textedit_drag(&edit_state, &edit_state.StbState, mouse_x, mouse_y);
			edit_state.CursorAnimReset();
			edit_state.CursorFollow = true;
		}
		if (edit_state.SelectedAllMouseLock && !io.MouseDown[0])
			edit_state.SelectedAllMouseLock = false;

		if (io.InputCharacters[0])
		{
			// Process text input (before we check for Return because using some IME will effectively send a Return?)
			// We ignore CTRL inputs, but need to allow CTRL+ALT as some keyboards (e.g. German) use AltGR - which is Alt+Ctrl - to input certain characters.
			if (!(io.KeyCtrl && !io.KeyAlt) && is_editable)
			{
				for (int n = 0; n < IM_ARRAYSIZE(io.InputCharacters) && io.InputCharacters[n]; n++)
					if (unsigned int c = (unsigned int)io.InputCharacters[n])
					{
						// Insert character if they pass filtering
						if (!InputTextFilterCharacter(&c, flags, callback, user_data))
							continue;
						edit_state.OnKeyPressed((int)c);
					}
			}

			// Consume characters
			memset(g.IO.InputCharacters, 0, sizeof(g.IO.InputCharacters));
		}

		// Handle various key-presses
		bool cancel_edit = false;
		const int k_mask = (io.KeyShift ? STB_TEXTEDIT_K_SHIFT : 0);
		const bool is_shortcut_key_only = (io.OSXBehaviors ? (io.KeySuper && !io.KeyCtrl) : (io.KeyCtrl && !io.KeySuper)) && !io.KeyAlt && !io.KeyShift; // OS X style: Shortcuts using Cmd/Super instead of Ctrl
		const bool is_wordmove_key_down = io.OSXBehaviors ? io.KeyAlt : io.KeyCtrl;                     // OS X style: Text editing cursor movement using Alt instead of Ctrl
		const bool is_startend_key_down = io.OSXBehaviors && io.KeySuper && !io.KeyCtrl && !io.KeyAlt;  // OS X style: Line/Text Start and End using Cmd+Arrows instead of Home/End

		if (IsKeyPressedMap(ImGuiKey_LeftArrow)) { edit_state.OnKeyPressed((is_startend_key_down ? STB_TEXTEDIT_K_LINESTART : is_wordmove_key_down ? STB_TEXTEDIT_K_WORDLEFT : STB_TEXTEDIT_K_LEFT) | k_mask); }
		else if (IsKeyPressedMap(ImGuiKey_RightArrow)) { edit_state.OnKeyPressed((is_startend_key_down ? STB_TEXTEDIT_K_LINEEND : is_wordmove_key_down ? STB_TEXTEDIT_K_WORDRIGHT : STB_TEXTEDIT_K_RIGHT) | k_mask); }
		else if (IsKeyPressedMap(ImGuiKey_UpArrow) && is_multiline) { if (io.KeyCtrl) SetWindowScrollY(draw_window, ImMax(draw_window->Scroll.y - g.FontSize, 0.0f)); else edit_state.OnKeyPressed((is_startend_key_down ? STB_TEXTEDIT_K_TEXTSTART : STB_TEXTEDIT_K_UP) | k_mask); }
		else if (IsKeyPressedMap(ImGuiKey_DownArrow) && is_multiline) { if (io.KeyCtrl) SetWindowScrollY(draw_window, ImMin(draw_window->Scroll.y + g.FontSize, GetScrollMaxY())); else edit_state.OnKeyPressed((is_startend_key_down ? STB_TEXTEDIT_K_TEXTEND : STB_TEXTEDIT_K_DOWN) | k_mask); }
		else if (IsKeyPressedMap(ImGuiKey_Home)) { edit_state.OnKeyPressed(io.KeyCtrl ? STB_TEXTEDIT_K_TEXTSTART | k_mask : STB_TEXTEDIT_K_LINESTART | k_mask); }
		else if (IsKeyPressedMap(ImGuiKey_End)) { edit_state.OnKeyPressed(io.KeyCtrl ? STB_TEXTEDIT_K_TEXTEND | k_mask : STB_TEXTEDIT_K_LINEEND | k_mask); }
		else if (IsKeyPressedMap(ImGuiKey_Delete) && is_editable) { edit_state.OnKeyPressed(STB_TEXTEDIT_K_DELETE | k_mask); }
		else if (IsKeyPressedMap(ImGuiKey_Backspace) && is_editable)
		{
			if (!edit_state.HasSelection())
			{
				if (is_wordmove_key_down) edit_state.OnKeyPressed(STB_TEXTEDIT_K_WORDLEFT | STB_TEXTEDIT_K_SHIFT);
				else if (io.OSXBehaviors && io.KeySuper && !io.KeyAlt && !io.KeyCtrl) edit_state.OnKeyPressed(STB_TEXTEDIT_K_LINESTART | STB_TEXTEDIT_K_SHIFT);
			}
			edit_state.OnKeyPressed(STB_TEXTEDIT_K_BACKSPACE | k_mask);
		}
		else if (IsKeyPressedMap(ImGuiKey_Enter))
		{
			bool ctrl_enter_for_new_line = (flags & ImGuiInputTextFlags_CtrlEnterForNewLine) != 0;
			if (!is_multiline || (ctrl_enter_for_new_line && !io.KeyCtrl) || (!ctrl_enter_for_new_line && io.KeyCtrl))
			{
				ClearActiveID();
				enter_pressed = true;
			}
			else if (is_editable)
			{
				unsigned int c = '\n'; // Insert new line
				if (InputTextFilterCharacter(&c, flags, callback, user_data))
					edit_state.OnKeyPressed((int)c);
			}
		}
		else if ((flags & ImGuiInputTextFlags_AllowTabInput) && IsKeyPressedMap(ImGuiKey_Tab) && !io.KeyCtrl && !io.KeyShift && !io.KeyAlt && is_editable)
		{
			unsigned int c = '\t'; // Insert TAB
			if (InputTextFilterCharacter(&c, flags, callback, user_data))
				edit_state.OnKeyPressed((int)c);
		}
		else if (IsKeyPressedMap(ImGuiKey_Escape)) { ClearActiveID(); cancel_edit = true; }
		else if (is_shortcut_key_only && IsKeyPressedMap(ImGuiKey_Z) && is_editable) { edit_state.OnKeyPressed(STB_TEXTEDIT_K_UNDO); edit_state.ClearSelection(); }
		else if (is_shortcut_key_only && IsKeyPressedMap(ImGuiKey_Y) && is_editable) { edit_state.OnKeyPressed(STB_TEXTEDIT_K_REDO); edit_state.ClearSelection(); }
		else if (is_shortcut_key_only && IsKeyPressedMap(ImGuiKey_A)) { edit_state.SelectAll(); edit_state.CursorFollow = true; }
		else if (is_shortcut_key_only && !is_password && ((IsKeyPressedMap(ImGuiKey_X) && is_editable) || IsKeyPressedMap(ImGuiKey_C)) && (!is_multiline || edit_state.HasSelection()))
		{
			// Cut, Copy
			const bool cut = IsKeyPressedMap(ImGuiKey_X);
			if (cut && !edit_state.HasSelection())
				edit_state.SelectAll();

			if (io.SetClipboardTextFn)
			{
				const int ib = edit_state.HasSelection() ? ImMin(edit_state.StbState.select_start, edit_state.StbState.select_end) : 0;
				const int ie = edit_state.HasSelection() ? ImMax(edit_state.StbState.select_start, edit_state.StbState.select_end) : edit_state.CurLenW;
				edit_state.TempTextBuffer.resize((ie - ib) * 4 + 1);
				ImTextStrToUtf8(edit_state.TempTextBuffer.Data, edit_state.TempTextBuffer.Size, edit_state.Text.Data + ib, edit_state.Text.Data + ie);
				SetClipboardText(edit_state.TempTextBuffer.Data);
			}

			if (cut)
			{
				edit_state.CursorFollow = true;
				stb_textedit_cut(&edit_state, &edit_state.StbState);
			}
		}
		else if (is_shortcut_key_only && IsKeyPressedMap(ImGuiKey_V) && is_editable)
		{
			// Paste
			if (const char* clipboard = GetClipboardText())
			{
				// Filter pasted buffer
				const int clipboard_len = (int)strlen(clipboard);
				ImWchar* clipboard_filtered = (ImWchar*)ImGui::MemAlloc((clipboard_len + 1) * sizeof(ImWchar));
				int clipboard_filtered_len = 0;
				for (const char* s = clipboard; *s; )
				{
					unsigned int c;
					s += ImTextCharFromUtf8(&c, s, NULL);
					if (c == 0)
						break;
					if (c >= 0x10000 || !InputTextFilterCharacter(&c, flags, callback, user_data))
						continue;
					clipboard_filtered[clipboard_filtered_len++] = (ImWchar)c;
				}
				clipboard_filtered[clipboard_filtered_len] = 0;
				if (clipboard_filtered_len > 0) // If everything was filtered, ignore the pasting operation
				{
					stb_textedit_paste(&edit_state, &edit_state.StbState, clipboard_filtered, clipboard_filtered_len);
					edit_state.CursorFollow = true;
				}
				ImGui::MemFree(clipboard_filtered);
			}
		}

		if (cancel_edit)
		{
			// Restore initial value
			if (is_editable)
			{
				ImStrncpy(buf, edit_state.InitialText.Data, buf_size);
				value_changed = true;
			}
		}
		else
		{
			// Apply new value immediately - copy modified buffer back
			// Note that as soon as the input box is active, the in-widget value gets priority over any underlying modification of the input buffer
			// FIXME: We actually always render 'buf' when calling DrawList->AddText, making the comment above incorrect.
			// FIXME-OPT: CPU waste to do this every time the widget is active, should mark dirty state from the stb_textedit callbacks.
			if (is_editable)
			{
				edit_state.TempTextBuffer.resize(edit_state.Text.Size * 4);
				ImTextStrToUtf8(edit_state.TempTextBuffer.Data, edit_state.TempTextBuffer.Size, edit_state.Text.Data, NULL);
			}

			// User callback
			if ((flags & (ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackAlways)) != 0)
			{
				IM_ASSERT(callback != NULL);

				// The reason we specify the usage semantic (Completion/History) is that Completion needs to disable keyboard TABBING at the moment.
				ImGuiInputTextFlags event_flag = 0;
				ImGuiKey event_key = ImGuiKey_COUNT;
				if ((flags & ImGuiInputTextFlags_CallbackCompletion) != 0 && IsKeyPressedMap(ImGuiKey_Tab))
				{
					event_flag = ImGuiInputTextFlags_CallbackCompletion;
					event_key = ImGuiKey_Tab;
				}
				else if ((flags & ImGuiInputTextFlags_CallbackHistory) != 0 && IsKeyPressedMap(ImGuiKey_UpArrow))
				{
					event_flag = ImGuiInputTextFlags_CallbackHistory;
					event_key = ImGuiKey_UpArrow;
				}
				else if ((flags & ImGuiInputTextFlags_CallbackHistory) != 0 && IsKeyPressedMap(ImGuiKey_DownArrow))
				{
					event_flag = ImGuiInputTextFlags_CallbackHistory;
					event_key = ImGuiKey_DownArrow;
				}
				else if (flags & ImGuiInputTextFlags_CallbackAlways)
					event_flag = ImGuiInputTextFlags_CallbackAlways;

				if (event_flag)
				{
					ImGuiTextEditCallbackData callback_data;
					memset(&callback_data, 0, sizeof(ImGuiTextEditCallbackData));
					callback_data.EventFlag = event_flag;
					callback_data.Flags = flags;
					callback_data.UserData = user_data;
					callback_data.ReadOnly = !is_editable;

					callback_data.EventKey = event_key;
					callback_data.Buf = edit_state.TempTextBuffer.Data;
					callback_data.BufTextLen = edit_state.CurLenA;
					callback_data.BufSize = edit_state.BufSizeA;
					callback_data.BufDirty = false;

					// We have to convert from wchar-positions to UTF-8-positions, which can be pretty slow (an incentive to ditch the ImWchar buffer, see https://github.com/nothings/stb/issues/188)
					ImWchar* text = edit_state.Text.Data;
					const int utf8_cursor_pos = callback_data.CursorPos = ImTextCountUtf8BytesFromStr(text, text + edit_state.StbState.cursor);
					const int utf8_selection_start = callback_data.SelectionStart = ImTextCountUtf8BytesFromStr(text, text + edit_state.StbState.select_start);
					const int utf8_selection_end = callback_data.SelectionEnd = ImTextCountUtf8BytesFromStr(text, text + edit_state.StbState.select_end);

					// Call user code
					callback(&callback_data);

					// Read back what user may have modified
					IM_ASSERT(callback_data.Buf == edit_state.TempTextBuffer.Data);  // Invalid to modify those fields
					IM_ASSERT(callback_data.BufSize == edit_state.BufSizeA);
					IM_ASSERT(callback_data.Flags == flags);
					if (callback_data.CursorPos != utf8_cursor_pos)            edit_state.StbState.cursor = ImTextCountCharsFromUtf8(callback_data.Buf, callback_data.Buf + callback_data.CursorPos);
					if (callback_data.SelectionStart != utf8_selection_start)  edit_state.StbState.select_start = ImTextCountCharsFromUtf8(callback_data.Buf, callback_data.Buf + callback_data.SelectionStart);
					if (callback_data.SelectionEnd != utf8_selection_end)      edit_state.StbState.select_end = ImTextCountCharsFromUtf8(callback_data.Buf, callback_data.Buf + callback_data.SelectionEnd);
					if (callback_data.BufDirty)
					{
						IM_ASSERT(callback_data.BufTextLen == (int)strlen(callback_data.Buf)); // You need to maintain BufTextLen if you change the text!
						edit_state.CurLenW = ImTextStrFromUtf8(edit_state.Text.Data, edit_state.Text.Size, callback_data.Buf, NULL);
						edit_state.CurLenA = callback_data.BufTextLen;  // Assume correct length and valid UTF-8 from user, saves us an extra strlen()
						edit_state.CursorAnimReset();
					}
				}
			}

			// Copy back to user buffer
			if (is_editable && strcmp(edit_state.TempTextBuffer.Data, buf) != 0)
			{
				ImStrncpy(buf, edit_state.TempTextBuffer.Data, buf_size);
				value_changed = true;
			}
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is set 'buf' might still be the old value. We set buf to NULL to prevent accidental usage from now on.
	const char* buf_display = (g.ActiveId == id && is_editable) ? edit_state.TempTextBuffer.Data : buf; buf = NULL;

	if (!is_multiline)
		RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

	const ImVec4 clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = is_multiline ? draw_window->DC.CursorPos : frame_bb.Min + style.FramePadding;
	ImVec2 text_size(0.f, 0.f);
	const bool is_currently_scrolling = (edit_state.Id == id && is_multiline && g.ActiveId == draw_window->GetIDNoKeepAlive("#SCROLLY"));
	if (g.ActiveId == id || is_currently_scrolling)
	{
		edit_state.CursorAnim += io.DeltaTime;

		// This is going to be messy. We need to:
		// - Display the text (this alone can be more easily clipped)
		// - Handle scrolling, highlight selection, display cursor (those all requires some form of 1d->2d cursor position calculation)
		// - Measure text height (for scrollbar)
		// We are attempting to do most of that in **one main pass** to minimize the computation cost (non-negligible for large amount of text) + 2nd pass for selection rendering (we could merge them by an extra refactoring effort)
		// FIXME: This should occur on buf_display but we'd need to maintain cursor/select_start/select_end for UTF-8.
		const ImWchar* text_begin = edit_state.Text.Data;
		ImVec2 cursor_offset, select_start_offset;

		{
			// Count lines + find lines numbers straddling 'cursor' and 'select_start' position.
			const ImWchar* searches_input_ptr[2];
			searches_input_ptr[0] = text_begin + edit_state.StbState.cursor;
			searches_input_ptr[1] = NULL;
			int searches_remaining = 1;
			int searches_result_line_number[2] = { -1, -999 };
			if (edit_state.StbState.select_start != edit_state.StbState.select_end)
			{
				searches_input_ptr[1] = text_begin + ImMin(edit_state.StbState.select_start, edit_state.StbState.select_end);
				searches_result_line_number[1] = -1;
				searches_remaining++;
			}

			// Iterate all lines to find our line numbers
			// In multi-line mode, we never exit the loop until all lines are counted, so add one extra to the searches_remaining counter.
			searches_remaining += is_multiline ? 1 : 0;
			int line_count = 0;
			for (const ImWchar* s = text_begin; *s != 0; s++)
				if (*s == '\n')
				{
					line_count++;
					if (searches_result_line_number[0] == -1 && s >= searches_input_ptr[0]) { searches_result_line_number[0] = line_count; if (--searches_remaining <= 0) break; }
					if (searches_result_line_number[1] == -1 && s >= searches_input_ptr[1]) { searches_result_line_number[1] = line_count; if (--searches_remaining <= 0) break; }
				}
			line_count++;
			if (searches_result_line_number[0] == -1) searches_result_line_number[0] = line_count;
			if (searches_result_line_number[1] == -1) searches_result_line_number[1] = line_count;

			// Calculate 2d position by finding the beginning of the line and measuring distance
			cursor_offset.x = InputTextCalcTextSizeW(ImStrbolW(searches_input_ptr[0], text_begin), searches_input_ptr[0]).x;
			cursor_offset.y = searches_result_line_number[0] * g.FontSize;
			if (searches_result_line_number[1] >= 0)
			{
				select_start_offset.x = InputTextCalcTextSizeW(ImStrbolW(searches_input_ptr[1], text_begin), searches_input_ptr[1]).x;
				select_start_offset.y = searches_result_line_number[1] * g.FontSize;
			}

			// Store text height (note that we haven't calculated text width at all, see GitHub issues #383, #1224)
			if (is_multiline)
				text_size = ImVec2(size.x, line_count * g.FontSize);
		}

		// Scroll
		if (edit_state.CursorFollow)
		{
			// Horizontal scroll in chunks of quarter width
			if (!(flags & ImGuiInputTextFlags_NoHorizontalScroll))
			{
				const float scroll_increment_x = size.x * 0.25f;
				if (cursor_offset.x < edit_state.ScrollX)
					edit_state.ScrollX = (float)(int)ImMax(0.0f, cursor_offset.x - scroll_increment_x);
				else if (cursor_offset.x - size.x >= edit_state.ScrollX)
					edit_state.ScrollX = (float)(int)(cursor_offset.x - size.x + scroll_increment_x);
			}
			else
			{
				edit_state.ScrollX = 0.0f;
			}

			// Vertical scroll
			if (is_multiline)
			{
				float scroll_y = draw_window->Scroll.y;
				if (cursor_offset.y - g.FontSize < scroll_y)
					scroll_y = ImMax(0.0f, cursor_offset.y - g.FontSize);
				else if (cursor_offset.y - size.y >= scroll_y)
					scroll_y = cursor_offset.y - size.y;
				draw_window->DC.CursorPos.y += (draw_window->Scroll.y - scroll_y);   // To avoid a frame of lag
				draw_window->Scroll.y = scroll_y;
				render_pos.y = draw_window->DC.CursorPos.y;
			}
		}
		edit_state.CursorFollow = false;
		const ImVec2 render_scroll = ImVec2(edit_state.ScrollX, 0.0f);

		// Draw selection
		if (edit_state.StbState.select_start != edit_state.StbState.select_end)
		{
			const ImWchar* text_selected_begin = text_begin + ImMin(edit_state.StbState.select_start, edit_state.StbState.select_end);
			const ImWchar* text_selected_end = text_begin + ImMax(edit_state.StbState.select_start, edit_state.StbState.select_end);

			float bg_offy_up = is_multiline ? 0.0f : -1.0f;    // FIXME: those offsets should be part of the style? they don't play so well with multi-line selection.
			float bg_offy_dn = is_multiline ? 0.0f : 2.0f;
			ImU32 bg_color = GetColorU32(ImGuiCol_TextSelectedBg);
			ImVec2 rect_pos = render_pos + select_start_offset - render_scroll;
			for (const ImWchar* p = text_selected_begin; p < text_selected_end; )
			{
				if (rect_pos.y > clip_rect.w + g.FontSize)
					break;
				if (rect_pos.y < clip_rect.y)
				{
					while (p < text_selected_end)
						if (*p++ == '\n')
							break;
				}
				else
				{
					ImVec2 rect_size = InputTextCalcTextSizeW(p, text_selected_end, &p, NULL, true);
					if (rect_size.x <= 0.0f) rect_size.x = (float)(int)(g.Font->GetCharAdvance((unsigned short)' ') * 0.50f); // So we can see selected empty lines
					ImRect rect(rect_pos + ImVec2(0.0f, bg_offy_up - g.FontSize), rect_pos + ImVec2(rect_size.x, bg_offy_dn));
					rect.Clip(clip_rect);
					if (rect.Overlaps(clip_rect))
						draw_window->DrawList->AddRectFilled(rect.Min, rect.Max, bg_color);
				}
				rect_pos.x = render_pos.x - render_scroll.x;
				rect_pos.y += g.FontSize;
			}
		}

		draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos - render_scroll, GetColorU32(ImGuiCol_Text), buf_display, buf_display + edit_state.CurLenA, 0.0f, is_multiline ? NULL : &clip_rect);

		// Draw blinking cursor
		bool cursor_is_visible = (g.InputTextState.CursorAnim <= 0.0f) || fmodf(g.InputTextState.CursorAnim, 1.20f) <= 0.80f;
		ImVec2 cursor_screen_pos = render_pos + cursor_offset - render_scroll;
		ImRect cursor_screen_rect(cursor_screen_pos.x, cursor_screen_pos.y - g.FontSize + 0.5f, cursor_screen_pos.x + 1.0f, cursor_screen_pos.y - 1.5f);
		if (cursor_is_visible && cursor_screen_rect.Overlaps(clip_rect))
			draw_window->DrawList->AddLine(cursor_screen_rect.Min, cursor_screen_rect.GetBL(), GetColorU32(ImGuiCol_Text));

		// Notify OS of text input position for advanced IME (-1 x offset so that Windows IME can cover our cursor. Bit of an extra nicety.)
		if (is_editable)
			g.OsImePosRequest = ImVec2(cursor_screen_pos.x - 1, cursor_screen_pos.y - g.FontSize);
	}
	else
	{
		// Render text only
		const char* buf_end = NULL;
		if (is_multiline)
			text_size = ImVec2(size.x, InputTextCalcTextLenAndLineCount(buf_display, &buf_end) * g.FontSize); // We don't need width
		draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, buf_end, 0.0f, is_multiline ? NULL : &clip_rect);
	}

	if (is_multiline)
	{
		Dummy(text_size + ImVec2(0.0f, g.FontSize)); // Always add room to scroll an extra line
		EndChildFrame();
		EndGroup();
	}

	if (is_password)
		PopFont();

	// Log as text
	if (g.LogEnabled && !is_password)
		LogRenderedText(render_pos, buf_display, NULL);

	if (label_size.x > 0)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	if ((flags & ImGuiInputTextFlags_EnterReturnsTrue) != 0)
		return enter_pressed;
	else
		return value_changed;
}

bool ImGui::InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data)
{
	IM_ASSERT(!(flags & ImGuiInputTextFlags_Multiline)); // call InputTextMultiline()
	return InputTextEx(label, buf, (int)buf_size, ImVec2(0, 0), flags, callback, user_data);
}

bool ImGui::InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data)
{
	return InputTextEx(label, buf, (int)buf_size, size, flags | ImGuiInputTextFlags_Multiline, callback, user_data);
}

// NB: scalar_format here must be a simple "%xx" format string with no prefix/suffix (unlike the Drag/Slider functions "display_format" argument)
bool ImGui::InputScalarEx(const char* label, ImGuiDataType data_type, void* data_ptr, void* step_ptr, void* step_fast_ptr, const char* scalar_format, ImGuiInputTextFlags extra_flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImVec2 label_size = CalcTextSize(label, NULL, true);

	BeginGroup();
	PushID(label);
	const ImVec2 button_sz = ImVec2(g.FontSize, g.FontSize) + style.FramePadding*2.0f;
	if (step_ptr)
		PushItemWidth(ImMax(1.0f, CalcItemWidth() - (button_sz.x + style.ItemInnerSpacing.x) * 2));

	char buf[64];
	DataTypeFormatString(data_type, data_ptr, scalar_format, buf, IM_ARRAYSIZE(buf));

	bool value_changed = false;
	if (!(extra_flags & ImGuiInputTextFlags_CharsHexadecimal))
		extra_flags |= ImGuiInputTextFlags_CharsDecimal;
	extra_flags |= ImGuiInputTextFlags_AutoSelectAll;
	if (InputText("", buf, IM_ARRAYSIZE(buf), extra_flags)) // PushId(label) + "" gives us the expected ID from outside point of view
		value_changed = DataTypeApplyOpFromText(buf, GImGui->InputTextState.InitialText.begin(), data_type, data_ptr, scalar_format);

	// Step buttons
	if (step_ptr)
	{
		PopItemWidth();
		SameLine(0, style.ItemInnerSpacing.x);
		if (ButtonEx("-", button_sz, ImGuiButtonFlags_Repeat | ImGuiButtonFlags_DontClosePopups))
		{
			DataTypeApplyOp(data_type, '-', data_ptr, g.IO.KeyCtrl && step_fast_ptr ? step_fast_ptr : step_ptr);
			value_changed = true;
		}
		SameLine(0, style.ItemInnerSpacing.x);
		if (ButtonEx("+", button_sz, ImGuiButtonFlags_Repeat | ImGuiButtonFlags_DontClosePopups))
		{
			DataTypeApplyOp(data_type, '+', data_ptr, g.IO.KeyCtrl && step_fast_ptr ? step_fast_ptr : step_ptr);
			value_changed = true;
		}
	}
	PopID();

	if (label_size.x > 0)
	{
		SameLine(0, style.ItemInnerSpacing.x);
		RenderText(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + style.FramePadding.y), label);
		ItemSize(label_size, style.FramePadding.y);
	}
	EndGroup();

	return value_changed;
}

bool ImGui::InputFloat(const char* label, float* v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags extra_flags)
{
	char display_format[16];
	if (decimal_precision < 0)
		strcpy(display_format, "%f");      // Ideally we'd have a minimum decimal precision of 1 to visually denote that this is a float, while hiding non-significant digits? %f doesn't have a minimum of 1
	else
		ImFormatString(display_format, IM_ARRAYSIZE(display_format), "%%.%df", decimal_precision);
	return InputScalarEx(label, ImGuiDataType_Float, (void*)v, (void*)(step>0.0f ? &step : NULL), (void*)(step_fast>0.0f ? &step_fast : NULL), display_format, extra_flags);
}

bool ImGui::InputInt(const char* label, int* v, int step, int step_fast, ImGuiInputTextFlags extra_flags)
{
	// Hexadecimal input provided as a convenience but the flag name is awkward. Typically you'd use InputText() to parse your own data, if you want to handle prefixes.
	const char* scalar_format = (extra_flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
	return InputScalarEx(label, ImGuiDataType_Int, (void*)v, (void*)(step>0.0f ? &step : NULL), (void*)(step_fast>0.0f ? &step_fast : NULL), scalar_format, extra_flags);
}

bool ImGui::InputFloatN(const char* label, float* v, int components, int decimal_precision, ImGuiInputTextFlags extra_flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	bool value_changed = false;
	BeginGroup();
	PushID(label);
	PushMultiItemsWidths(components);
	for (int i = 0; i < components; i++)
	{
		PushID(i);
		value_changed |= InputFloat("##v", &v[i], 0, 0, decimal_precision, extra_flags);
		SameLine(0, g.Style.ItemInnerSpacing.x);
		PopID();
		PopItemWidth();
	}
	PopID();

	window->DC.CurrentLineTextBaseOffset = ImMax(window->DC.CurrentLineTextBaseOffset, g.Style.FramePadding.y);
	TextUnformatted(label, FindRenderedTextEnd(label));
	EndGroup();

	return value_changed;
}

bool ImGui::InputFloat2(const char* label, float v[2], int decimal_precision, ImGuiInputTextFlags extra_flags)
{
	return InputFloatN(label, v, 2, decimal_precision, extra_flags);
}

bool ImGui::InputFloat3(const char* label, float v[3], int decimal_precision, ImGuiInputTextFlags extra_flags)
{
	return InputFloatN(label, v, 3, decimal_precision, extra_flags);
}

bool ImGui::InputFloat4(const char* label, float v[4], int decimal_precision, ImGuiInputTextFlags extra_flags)
{
	return InputFloatN(label, v, 4, decimal_precision, extra_flags);
}

bool ImGui::InputIntN(const char* label, int* v, int components, ImGuiInputTextFlags extra_flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	bool value_changed = false;
	BeginGroup();
	PushID(label);
	PushMultiItemsWidths(components);
	for (int i = 0; i < components; i++)
	{
		PushID(i);
		value_changed |= InputInt("##v", &v[i], 0, 0, extra_flags);
		SameLine(0, g.Style.ItemInnerSpacing.x);
		PopID();
		PopItemWidth();
	}
	PopID();

	window->DC.CurrentLineTextBaseOffset = ImMax(window->DC.CurrentLineTextBaseOffset, g.Style.FramePadding.y);
	TextUnformatted(label, FindRenderedTextEnd(label));
	EndGroup();

	return value_changed;
}

bool ImGui::InputInt2(const char* label, int v[2], ImGuiInputTextFlags extra_flags)
{
	return InputIntN(label, v, 2, extra_flags);
}

bool ImGui::InputInt3(const char* label, int v[3], ImGuiInputTextFlags extra_flags)
{
	return InputIntN(label, v, 3, extra_flags);
}

bool ImGui::InputInt4(const char* label, int v[4], ImGuiInputTextFlags extra_flags)
{
	return InputIntN(label, v, 4, extra_flags);
}

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

static bool Items_SingleStringGetter(void* data, int idx, const char** out_text)
{
	// FIXME-OPT: we could pre-compute the indices to fasten this. But only 1 active combo means the waste is limited.
	const char* items_separated_by_zeros = (const char*)data;
	int items_count = 0;
	const char* p = items_separated_by_zeros;
	while (*p)
	{
		if (idx == items_count)
			break;
		p += strlen(p) + 1;
		items_count++;
	}
	if (!*p)
		return false;
	if (out_text)
		*out_text = p;
	return true;
}

// Combo box helper allowing to pass an array of strings.
bool ImGui::Combo(const char* label, int* current_item, const char* const* items, int items_count, int height_in_items)
{
	const bool value_changed = Combo(label, current_item, Items_ArrayGetter, (void*)items, items_count, height_in_items);
	return value_changed;
}

// Combo box helper allowing to pass all items in a single string.
bool ImGui::Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items)
{
	int items_count = 0;
	const char* p = items_separated_by_zeros;       // FIXME-OPT: Avoid computing this, or at least only when combo is open
	while (*p)
	{
		p += strlen(p) + 1;
		items_count++;
	}
	bool value_changed = Combo(label, current_item, Items_SingleStringGetter, (void*)items_separated_by_zeros, items_count, height_in_items);
	return value_changed;
}

// Combo box function.
bool ImGui::Combo(const char* label, int* current_item, bool(*items_getter)(void*, int, const char**), void* data, int items_count, int height_in_items)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = CalcItemWidth();

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y*0.5f));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, &id))
		return false;

	const float arrow_size = (g.FontSize + style.FramePadding.x * 2.0f);
	const bool hovered = IsHovered(frame_bb, id);
	bool popup_open = IsPopupOpen(id);
	bool popup_opened_now = false;

	const ImRect value_bb(frame_bb.Min, frame_bb.Max - ImVec2(arrow_size, 0.0f));
	RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
	RenderFrame(ImVec2(frame_bb.Max.x - arrow_size, frame_bb.Min.y), frame_bb.Max, GetColorU32(popup_open || hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button), true, style.FrameRounding); // FIXME-ROUNDING
																																															  //RenderCollapseTriangle(ImVec2(frame_bb.Max.x-arrow_size, frame_bb.Min.y) + style.FramePadding, true);

	if (*current_item >= 0 && *current_item < items_count)
	{
		const char* item_text;
		if (items_getter(data, *current_item, &item_text))
			RenderTextClipped(frame_bb.Min + ImVec2(2, 0), value_bb.Max, item_text, NULL, NULL, ImVec2(0.0f, 0.0f));
	}

	if (label_size.x > 0)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y - 2), label);

	if (hovered)
	{
		SetHoveredID(id);
		if (g.IO.MouseClicked[0])
		{
			ClearActiveID();
			if (IsPopupOpen(id))
			{
				ClosePopup(id);
			}
			else
			{
				FocusWindow(window);
				OpenPopup(label);
				popup_open = popup_opened_now = true;
			}
		}
	}

	bool value_changed = false;
	if (IsPopupOpen(id))
	{
		// Size default to hold ~7 items
		if (height_in_items < 0)
			height_in_items = 7;

		float popup_height = (label_size.y + style.ItemSpacing.y) * ImMin(items_count, height_in_items) + (style.FramePadding.y * 3);
		float popup_y1 = frame_bb.Max.y;
		float popup_y2 = ImClamp(popup_y1 + popup_height, popup_y1, g.IO.DisplaySize.y - style.DisplaySafeAreaPadding.y);
		if ((popup_y2 - popup_y1) < ImMin(popup_height, frame_bb.Min.y - style.DisplaySafeAreaPadding.y))
		{
			// Position our combo ABOVE because there's more space to fit! (FIXME: Handle in Begin() or use a shared helper. We have similar code in Begin() for popup placement)
			popup_y1 = ImClamp(frame_bb.Min.y - popup_height, style.DisplaySafeAreaPadding.y, frame_bb.Min.y);
			popup_y2 = frame_bb.Min.y;
		}
		ImRect popup_rect(ImVec2(frame_bb.Min.x, popup_y1), ImVec2(frame_bb.Max.x, popup_y2));
		SetNextWindowPos(popup_rect.Min);
		SetNextWindowSize(popup_rect.GetSize());
		PushStyleVar(ImGuiStyleVar_WindowPadding, style.FramePadding);

		const ImGuiWindowFlags flags = ImGuiWindowFlags_ComboBox | ((window->Flags & ImGuiWindowFlags_ShowBorders) ? ImGuiWindowFlags_ShowBorders : 0);
		if (BeginPopupEx(label, flags))
		{
			// Display items
			Spacing();
			for (int i = 0; i < items_count; i++)
			{
				PushID((void*)(intptr_t)i);
				const bool item_selected = (i == *current_item);
				const char* item_text;
				if (!items_getter(data, i, &item_text))
					item_text = "*Unknown item*";
				if (Selectable(item_text, item_selected))
				{
					ClearActiveID();
					value_changed = true;
					*current_item = i;
				}
				if (item_selected && popup_opened_now)
					SetScrollHere();
				PopID();
			}
			EndPopup();
		}
		PopStyleVar();
	}
	return value_changed;
}

bool ImGui::Selectable1(const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size_arg)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.ColumnsCount > 1)
		PopClipRect();

	ImGuiID id = window->GetID(label);
	ImVec2 label_size = CalcTextSize(label, NULL, true);
	ImVec2 size(size_arg.x != 0.0f ? size_arg.x : label_size.x, size_arg.y != 0.0f ? size_arg.y : label_size.y);
	ImVec2 pos = window->DC.CursorPos;
	pos.y += window->DC.CurrentLineTextBaseOffset;
	ImRect bb(pos, pos + size);
	ItemSize(bb);

	// Fill horizontal space.
	ImVec2 window_padding = window->WindowPadding;
	float max_x = (flags & ImGuiSelectableFlags_SpanAllColumns) ? GetWindowContentRegionMax().x : GetContentRegionMax().x;
	float w_draw = ImMax(label_size.x, window->Pos.x + max_x - window_padding.x - window->DC.CursorPos.x);
	ImVec2 size_draw((size_arg.x != 0 && !(flags & ImGuiSelectableFlags_DrawFillAvailWidth)) ? size_arg.x : w_draw, size_arg.y != 0.0f ? size_arg.y : size.y);
	ImRect bb_with_spacing(pos, pos + size_draw);
	if (size_arg.x == 0.0f || (flags & ImGuiSelectableFlags_DrawFillAvailWidth))
		bb_with_spacing.Max.x += window_padding.x;

	// Selectables are tightly packed together, we extend the box to cover spacing between selectable.
	float spacing_L = (float)(int)(style.ItemSpacing.x * 0.5f);
	float spacing_U = (float)(int)(style.ItemSpacing.y * 0.5f);
	float spacing_R = style.ItemSpacing.x - spacing_L;
	float spacing_D = style.ItemSpacing.y - spacing_U;
	bb_with_spacing.Min.x -= spacing_L;
	bb_with_spacing.Min.y -= spacing_U;
	bb_with_spacing.Max.x += spacing_R;
	bb_with_spacing.Max.y += spacing_D;
	if (!ItemAdd(bb_with_spacing, &id))
	{
		if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.ColumnsCount > 1)
			PushColumnClipRect();
		return false;
	}

	ImGuiButtonFlags button_flags = 0;
	if (flags & ImGuiSelectableFlags_Menu) button_flags |= ImGuiButtonFlags_PressedOnClick;
	if (flags & ImGuiSelectableFlags_MenuItem) button_flags |= ImGuiButtonFlags_PressedOnClick | ImGuiButtonFlags_PressedOnRelease;
	if (flags & ImGuiSelectableFlags_Disabled) button_flags |= ImGuiButtonFlags_Disabled;
	if (flags & ImGuiSelectableFlags_AllowDoubleClick) button_flags |= ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnDoubleClick;
	bool hovered, held;
	bool pressed = ButtonBehavior(bb_with_spacing, id, &hovered, &held, button_flags);
	if (flags & ImGuiSelectableFlags_Disabled)
		selected = false;

	// Render
	if (hovered || selected)
	{
		const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
		//RenderFrame(bb_with_spacing.Min, bb_with_spacing.Max + ImVec2(1,0), col, false, 0.0f);
	}

	if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.ColumnsCount > 1)
	{
		PushColumnClipRect();
		bb_with_spacing.Max.x -= (GetContentRegionMax().x - max_x);
	}

	//if (flags & ImGuiSelectableFlags_Disabled) PushStyleColor(ImGuiCol_Text, g.Style.Colors[ImGuiCol_TextDisabled]);
	if (selected)
		PushStyleColor(ImGuiCol_Text, ImVec4(0.98f, 0.98f, 0.98f, 1.f));
	else if (hovered && !selected)
		PushStyleColor(ImGuiCol_Text, ImVec4(0.6f, 0.6f, 0.6f, 1.f));
	else
		PushStyleColor(ImGuiCol_Text, ImVec4(0.40f, 0.40f, 0.40f, 1.f));
	RenderTextClipped(bb.Min, bb_with_spacing.Max, label, NULL, &label_size, ImVec2(0.0f, 0.0f));
	PushStyleColor(ImGuiCol_Text, g.Style.Colors[ImGuiCol_TextDisabled]);
	if (flags & ImGuiSelectableFlags_Disabled) PopStyleColor();

	// Automatically close popups
	if (pressed && !(flags & ImGuiSelectableFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
		CloseCurrentPopup();
	return pressed;
}

// Tip: pass an empty label (e.g. "##dummy") then you can use the space to draw other text or image.
// But you need to make sure the ID is unique, e.g. enclose calls in PushID/PopID.
bool ImGui::Selectable(const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size_arg)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.ColumnsCount > 1)
		PopClipRect();

	ImGuiID id = window->GetID(label);
	ImVec2 label_size = CalcTextSize(label, NULL, true);
	ImVec2 size(size_arg.x != 0.0f ? size_arg.x : label_size.x, size_arg.y != 0.0f ? size_arg.y : label_size.y);
	ImVec2 pos = window->DC.CursorPos;
	pos.y += window->DC.CurrentLineTextBaseOffset;
	ImRect bb(pos, pos + size);
	ItemSize(bb);

	// Fill horizontal space.
	ImVec2 window_padding = window->WindowPadding;
	float max_x = (flags & ImGuiSelectableFlags_SpanAllColumns) ? GetWindowContentRegionMax().x : GetContentRegionMax().x;
	float w_draw = ImMax(label_size.x, window->Pos.x + max_x - window_padding.x - window->DC.CursorPos.x);
	ImVec2 size_draw((size_arg.x != 0 && !(flags & ImGuiSelectableFlags_DrawFillAvailWidth)) ? size_arg.x : w_draw, size_arg.y != 0.0f ? size_arg.y : size.y);
	ImRect bb_with_spacing(pos, pos + size_draw);
	if (size_arg.x == 0.0f || (flags & ImGuiSelectableFlags_DrawFillAvailWidth))
		bb_with_spacing.Max.x += window_padding.x;

	// Selectables are tightly packed together, we extend the box to cover spacing between selectable.
	float spacing_L = (float)(int)(style.ItemSpacing.x * 0.5f);
	float spacing_U = (float)(int)(style.ItemSpacing.y * 0.5f);
	float spacing_R = style.ItemSpacing.x - spacing_L;
	float spacing_D = style.ItemSpacing.y - spacing_U;
	bb_with_spacing.Min.x -= spacing_L;
	bb_with_spacing.Min.y -= spacing_U;
	bb_with_spacing.Max.x += spacing_R;
	bb_with_spacing.Max.y += spacing_D;
	if (!ItemAdd(bb_with_spacing, &id))
	{
		if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.ColumnsCount > 1)
			PushColumnClipRect();
		return false;
	}

	ImGuiButtonFlags button_flags = 0;
	if (flags & ImGuiSelectableFlags_Menu) button_flags |= ImGuiButtonFlags_PressedOnClick;
	if (flags & ImGuiSelectableFlags_MenuItem) button_flags |= ImGuiButtonFlags_PressedOnClick | ImGuiButtonFlags_PressedOnRelease;
	if (flags & ImGuiSelectableFlags_Disabled) button_flags |= ImGuiButtonFlags_Disabled;
	if (flags & ImGuiSelectableFlags_AllowDoubleClick) button_flags |= ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnDoubleClick;
	bool hovered, held;
	bool pressed = ButtonBehavior(bb_with_spacing, id, &hovered, &held, button_flags);
	if (flags & ImGuiSelectableFlags_Disabled)
		selected = false;

	// Render
	if (hovered || selected)
	{
		const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
		RenderFrame(bb_with_spacing.Min, bb_with_spacing.Max + ImVec2(1, 0), col, false, 0.0f);
	}

	if ((flags & ImGuiSelectableFlags_SpanAllColumns) && window->DC.ColumnsCount > 1)
	{
		PushColumnClipRect();
		bb_with_spacing.Max.x -= (GetContentRegionMax().x - max_x);
	}

	if (flags & ImGuiSelectableFlags_Disabled) PushStyleColor(ImGuiCol_Text, g.Style.Colors[ImGuiCol_TextDisabled]);
	//if (selected)
	//	PushStyleColor(ImGuiCol_Text, ImVec4(0.98f, 0.98f, 0.98f, 1.f));
	//else 
	//	PushStyleColor(ImGuiCol_Text, ImVec4(0.40f, 0.40f, 0.40f, 1.f));
	RenderTextClipped(bb.Min, bb_with_spacing.Max, label, NULL, &label_size, ImVec2(0.0f, 0.0f));
	if (flags & ImGuiSelectableFlags_Disabled) PopStyleColor();

	// Automatically close popups
	if (pressed && !(flags & ImGuiSelectableFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
		CloseCurrentPopup();
	return pressed;
}

bool ImGui::Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags, const ImVec2& size_arg)
{
	if (Selectable(label, *p_selected, flags, size_arg))
	{
		*p_selected = !*p_selected;
		return true;
	}
	return false;
}

// Helper to calculate the size of a listbox and display a label on the right.
// Tip: To have a list filling the entire window width, PushItemWidth(-1) and pass an empty label "##empty"
bool ImGui::ListBoxHeader(const char* label, const ImVec2& size_arg)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	const ImGuiStyle& style = GetStyle();
	const ImGuiID id = GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);

	// Size default to hold ~7 items. Fractional number of items helps seeing that we can scroll down/up without looking at scrollbar.
	ImVec2 size = CalcItemSize(size_arg, CalcItemWidth(), GetTextLineHeightWithSpacing() * 7.4f + style.ItemSpacing.y);
	ImVec2 frame_size = ImVec2(size.x, ImMax(size.y, label_size.y));
	ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + frame_size);
	ImRect bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
	window->DC.LastItemRect = bb;

	BeginGroup();
	if (label_size.x > 0)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	BeginChildFrame(id, frame_bb.GetSize());
	return true;
}

bool ImGui::ListBoxHeader(const char* label, int items_count, int height_in_items)
{
	// Size default to hold ~7 items. Fractional number of items helps seeing that we can scroll down/up without looking at scrollbar.
	// However we don't add +0.40f if items_count <= height_in_items. It is slightly dodgy, because it means a dynamic list of items will make the widget resize occasionally when it crosses that size.
	// I am expecting that someone will come and complain about this behavior in a remote future, then we can advise on a better solution.
	if (height_in_items < 0)
		height_in_items = ImMin(items_count, 7);
	float height_in_items_f = height_in_items < items_count ? (height_in_items + 0.40f) : (height_in_items + 0.00f);

	// We include ItemSpacing.y so that a list sized for the exact number of items doesn't make a scrollbar appears. We could also enforce that by passing a flag to BeginChild().
	ImVec2 size;
	size.x = 0.0f;
	size.y = GetTextLineHeightWithSpacing() * height_in_items_f + GetStyle().ItemSpacing.y;
	return ListBoxHeader(label, size);
}

void ImGui::ListBoxFooter()
{
	ImGuiWindow* parent_window = GetParentWindow();
	const ImRect bb = parent_window->DC.LastItemRect;
	const ImGuiStyle& style = GetStyle();

	EndChildFrame();

	// Redeclare item size so that it includes the label (we have stored the full size in LastItemRect)
	// We call SameLine() to restore DC.CurrentLine* data
	SameLine();
	parent_window->DC.CursorPos = bb.Min;
	ItemSize(bb, style.FramePadding.y);
	EndGroup();
}

bool ImGui::ListBox(const char* label, int* current_item, const char* const* items, int items_count, int height_items)
{
	const bool value_changed = ListBox(label, current_item, Items_ArrayGetter, (void*)items, items_count, height_items);
	return value_changed;
}

bool ImGui::ListBox(const char* label, int* current_item, bool(*items_getter)(void*, int, const char**), void* data, int items_count, int height_in_items)
{
	if (!ListBoxHeader(label, items_count, height_in_items))
		return false;

	// Assume all items have even height (= 1 line of text). If you need items of different or variable sizes you can create a custom version of ListBox() in your code without using the clipper.
	bool value_changed = false;
	ImGuiListClipper clipper(items_count, GetTextLineHeightWithSpacing());
	while (clipper.Step())
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		{
			const bool item_selected = (i == *current_item);
			const char* item_text;
			if (!items_getter(data, i, &item_text))
				item_text = "*Unknown item*";

			PushID(i);
			if (Selectable(item_text, item_selected))
			{
				*current_item = i;
				value_changed = true;
			}
			PopID();
		}
	ListBoxFooter();
	return value_changed;
}

bool ImGui::MenuItem(const char* label, const char* shortcut, bool selected, bool enabled)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImVec2 pos = window->DC.CursorPos;
	ImVec2 label_size = CalcTextSize(label, NULL, true);
	ImVec2 shortcut_size = shortcut ? CalcTextSize(shortcut, NULL) : ImVec2(0.0f, 0.0f);
	float w = window->MenuColumns.DeclColumns(label_size.x, shortcut_size.x, (float)(int)(g.FontSize * 1.20f)); // Feedback for next frame
	float extra_w = ImMax(0.0f, GetContentRegionAvail().x - w);

	bool pressed = Selectable(label, false, ImGuiSelectableFlags_MenuItem | ImGuiSelectableFlags_DrawFillAvailWidth | (enabled ? 0 : ImGuiSelectableFlags_Disabled), ImVec2(w, 0.0f));
	if (shortcut_size.x > 0.0f)
	{
		PushStyleColor(ImGuiCol_Text, g.Style.Colors[ImGuiCol_TextDisabled]);
		RenderText(pos + ImVec2(window->MenuColumns.Pos[1] + extra_w, 0.0f), shortcut, NULL, false);
		PopStyleColor();
	}

	if (selected)
		RenderCheckMark(pos + ImVec2(window->MenuColumns.Pos[2] + extra_w + g.FontSize * 0.20f, 0.0f), GetColorU32(enabled ? ImGuiCol_Text : ImGuiCol_TextDisabled));

	return pressed;
}

bool ImGui::MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled)
{
	if (MenuItem(label, shortcut, p_selected ? *p_selected : false, enabled))
	{
		if (p_selected)
			*p_selected = !*p_selected;
		return true;
	}
	return false;
}

bool ImGui::BeginMainMenuBar()
{
	ImGuiContext& g = *GImGui;
	SetNextWindowPos(ImVec2(0.0f, 0.0f));
	SetNextWindowSize(ImVec2(g.IO.DisplaySize.x, g.FontBaseSize + g.Style.FramePadding.y * 2.0f));
	PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));
	if (!Begin("##MainMenuBar", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar)
		|| !BeginMenuBar())
	{
		End();
		PopStyleVar(2);
		return false;
	}
	g.CurrentWindow->DC.MenuBarOffsetX += g.Style.DisplaySafeAreaPadding.x;
	return true;
}

void ImGui::EndMainMenuBar()
{
	EndMenuBar();
	End();
	PopStyleVar(2);
}

bool ImGui::BeginMenuBar()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;
	if (!(window->Flags & ImGuiWindowFlags_MenuBar))
		return false;

	IM_ASSERT(!window->DC.MenuBarAppending);
	BeginGroup(); // Save position
	PushID("##menubar");
	ImRect rect = window->MenuBarRect();
	PushClipRect(ImVec2(ImFloor(rect.Min.x + 0.5f), ImFloor(rect.Min.y + window->BorderSize + 0.5f)), ImVec2(ImFloor(rect.Max.x + 0.5f), ImFloor(rect.Max.y + 0.5f)), false);
	window->DC.CursorPos = ImVec2(rect.Min.x + window->DC.MenuBarOffsetX, rect.Min.y);// + g.Style.FramePadding.y);
	window->DC.LayoutType = ImGuiLayoutType_Horizontal;
	window->DC.MenuBarAppending = true;
	AlignFirstTextHeightToWidgets();
	return true;
}

void ImGui::EndMenuBar()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	IM_ASSERT(window->Flags & ImGuiWindowFlags_MenuBar);
	IM_ASSERT(window->DC.MenuBarAppending);
	PopClipRect();
	PopID();
	window->DC.MenuBarOffsetX = window->DC.CursorPos.x - window->MenuBarRect().Min.x;
	window->DC.GroupStack.back().AdvanceCursor = false;
	EndGroup();
	window->DC.LayoutType = ImGuiLayoutType_Vertical;
	window->DC.MenuBarAppending = false;
}

bool ImGui::BeginMenu(const char* label, bool enabled)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	ImVec2 label_size = CalcTextSize(label, NULL, true);
	ImGuiWindow* backed_focused_window = g.FocusedWindow;

	bool pressed;
	bool menu_is_open = IsPopupOpen(id);
	bool menuset_is_open = !(window->Flags & ImGuiWindowFlags_Popup) && (g.OpenPopupStack.Size > g.CurrentPopupStack.Size && g.OpenPopupStack[g.CurrentPopupStack.Size].ParentMenuSet == window->GetID("##menus"));
	if (menuset_is_open)
		g.FocusedWindow = window;

	// The reference position stored in popup_pos will be used by Begin() to find a suitable position for the child menu (using FindBestPopupWindowPos).
	ImVec2 popup_pos, pos = window->DC.CursorPos;
	if (window->DC.LayoutType == ImGuiLayoutType_Horizontal)
	{
		popup_pos = ImVec2(pos.x - window->WindowPadding.x, pos.y - style.FramePadding.y + window->MenuBarHeight());
		window->DC.CursorPos.x += (float)(int)(style.ItemSpacing.x * 0.5f);
		PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemSpacing * 2.0f);
		float w = label_size.x;
		pressed = Selectable(label, menu_is_open, ImGuiSelectableFlags_Menu | ImGuiSelectableFlags_DontClosePopups | (!enabled ? ImGuiSelectableFlags_Disabled : 0), ImVec2(w, 0.0f));
		PopStyleVar();
		SameLine();
		window->DC.CursorPos.x += (float)(int)(style.ItemSpacing.x * 0.5f);
	}
	else
	{
		popup_pos = ImVec2(pos.x, pos.y - style.WindowPadding.y);
		float w = window->MenuColumns.DeclColumns(label_size.x, 0.0f, (float)(int)(g.FontSize * 1.20f)); // Feedback to next frame
		float extra_w = ImMax(0.0f, GetContentRegionAvail().x - w);
		pressed = Selectable(label, menu_is_open, ImGuiSelectableFlags_Menu | ImGuiSelectableFlags_DontClosePopups | ImGuiSelectableFlags_DrawFillAvailWidth | (!enabled ? ImGuiSelectableFlags_Disabled : 0), ImVec2(w, 0.0f));
		if (!enabled) PushStyleColor(ImGuiCol_Text, g.Style.Colors[ImGuiCol_TextDisabled]);
		RenderCollapseTriangle(pos + ImVec2(window->MenuColumns.Pos[2] + extra_w + g.FontSize * 0.20f, 0.0f), false);
		if (!enabled) PopStyleColor();
	}

	bool hovered = enabled && IsHovered(window->DC.LastItemRect, id);
	if (menuset_is_open)
		g.FocusedWindow = backed_focused_window;

	bool want_open = false, want_close = false;
	if (window->Flags & (ImGuiWindowFlags_Popup | ImGuiWindowFlags_ChildMenu))
	{
		// Implement http://bjk5.com/post/44698559168/breaking-down-amazons-mega-dropdown to avoid using timers, so menus feels more reactive.
		bool moving_within_opened_triangle = false;
		if (g.HoveredWindow == window && g.OpenPopupStack.Size > g.CurrentPopupStack.Size && g.OpenPopupStack[g.CurrentPopupStack.Size].ParentWindow == window)
		{
			if (ImGuiWindow* next_window = g.OpenPopupStack[g.CurrentPopupStack.Size].Window)
			{
				ImRect next_window_rect = next_window->Rect();
				ImVec2 ta = g.IO.MousePos - g.IO.MouseDelta;
				ImVec2 tb = (window->Pos.x < next_window->Pos.x) ? next_window_rect.GetTL() : next_window_rect.GetTR();
				ImVec2 tc = (window->Pos.x < next_window->Pos.x) ? next_window_rect.GetBL() : next_window_rect.GetBR();
				float extra = ImClamp(fabsf(ta.x - tb.x) * 0.30f, 5.0f, 30.0f); // add a bit of extra slack.
				ta.x += (window->Pos.x < next_window->Pos.x) ? -0.5f : +0.5f;   // to avoid numerical issues
				tb.y = ta.y + ImMax((tb.y - extra) - ta.y, -100.0f);            // triangle is maximum 200 high to limit the slope and the bias toward large sub-menus // FIXME: Multiply by fb_scale?
				tc.y = ta.y + ImMin((tc.y + extra) - ta.y, +100.0f);
				moving_within_opened_triangle = ImIsPointInTriangle(g.IO.MousePos, ta, tb, tc);
				//window->DrawList->PushClipRectFullScreen(); window->DrawList->AddTriangleFilled(ta, tb, tc, moving_within_opened_triangle ? IM_COL32(0,128,0,128) : IM_COL32(128,0,0,128)); window->DrawList->PopClipRect(); // Debug
			}
		}

		want_close = (menu_is_open && !hovered && g.HoveredWindow == window && g.HoveredIdPreviousFrame != 0 && g.HoveredIdPreviousFrame != id && !moving_within_opened_triangle);
		want_open = (!menu_is_open && hovered && !moving_within_opened_triangle) || (!menu_is_open && hovered && pressed);
	}
	else if (menu_is_open && pressed && menuset_is_open) // menu-bar: click open menu to close
	{
		want_close = true;
		want_open = menu_is_open = false;
	}
	else if (pressed || (hovered && menuset_is_open && !menu_is_open)) // menu-bar: first click to open, then hover to open others
		want_open = true;
	if (!enabled) // explicitly close if an open menu becomes disabled, facilitate users code a lot in pattern such as 'if (BeginMenu("options", has_object)) { ..use object.. }'
		want_close = true;
	if (want_close && IsPopupOpen(id))
		ClosePopupToLevel(GImGui->CurrentPopupStack.Size);

	if (!menu_is_open && want_open && g.OpenPopupStack.Size > g.CurrentPopupStack.Size)
	{
		// Don't recycle same menu level in the same frame, first close the other menu and yield for a frame.
		OpenPopup(label);
		return false;
	}

	menu_is_open |= want_open;
	if (want_open)
		OpenPopup(label);

	if (menu_is_open)
	{
		SetNextWindowPos(popup_pos, ImGuiSetCond_Always);
		ImGuiWindowFlags flags = ImGuiWindowFlags_ShowBorders | ((window->Flags & (ImGuiWindowFlags_Popup | ImGuiWindowFlags_ChildMenu)) ? ImGuiWindowFlags_ChildMenu | ImGuiWindowFlags_ChildWindow : ImGuiWindowFlags_ChildMenu);
		menu_is_open = BeginPopupEx(label, flags); // menu_is_open can be 'false' when the popup is completely clipped (e.g. zero size display)
	}

	return menu_is_open;
}

void ImGui::EndMenu()
{
	EndPopup();
}

// A little colored square. Return true when clicked.
// FIXME: May want to display/ignore the alpha component in the color display? Yet show it in the tooltip.
bool ImGui::ColorButton(const ImVec4& col, bool small_height, bool outline_border)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID("#colorbutton");
	const float square_size = g.FontSize;
	const ImRect bb(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + 6), window->DC.CursorPos + ImVec2(square_size + style.FramePadding.y * 2, square_size + (small_height ? 0 : style.FramePadding.y * 2) - 4));
	ItemSize(bb, small_height ? 0.0f : style.FramePadding.y);
	if (!ItemAdd(bb, &id))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);
	RenderFrame(bb.Min, bb.Max, GetColorU32(col), outline_border, style.FrameRounding);

	//if (hovered)
	//	SetTooltip("Color:\n(%.2f,%.2f,%.2f,%.2f)\n#%02X%02X%02X%02X", col.x, col.y, col.z, col.w, IM_F32_TO_INT8_SAT(col.x), IM_F32_TO_INT8_SAT(col.y), IM_F32_TO_INT8_SAT(col.z), IM_F32_TO_INT8_SAT(col.w));

	return pressed;
}

bool ImGui::ColorEdit3(const char* label, float col[3])
{
	float col4[4];
	col4[0] = col[0];
	col4[1] = col[1];
	col4[2] = col[2];
	col4[3] = 1.0f;
	const bool value_changed = ColorEdit4(label, col4, false);
	col[0] = col4[0];
	col[1] = col4[1];
	col[2] = col4[2];
	return value_changed;
}

// Edit colors components (each component in 0.0f..1.0f range
// Use CTRL-Click to input value and TAB to go to next item.
bool ImGui::ColorEdit4(const char* label, float col[4], bool alpha)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w_full = CalcItemWidth();
	const float square_sz = (g.FontSize + style.FramePadding.y * 2.0f);

	ImGuiColorEditMode edit_mode = window->DC.ColorEditMode;
	if (edit_mode == ImGuiColorEditMode_UserSelect || edit_mode == ImGuiColorEditMode_UserSelectShowButton)
		edit_mode = g.ColorEditModeStorage.GetInt(id, 0) % 3;

	float f[4] = { col[0], col[1], col[2], col[3] };
	if (edit_mode == ImGuiColorEditMode_HSV)
		ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);

	int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };

	int components = alpha ? 4 : 3;
	bool value_changed = false;

	BeginGroup();
	PushID(label);

	const bool hsv = (edit_mode == 1);
	switch (edit_mode)
	{
	case ImGuiColorEditMode_RGB:
	case ImGuiColorEditMode_HSV:
	{
		// RGB/HSV 0..255 Sliders
		const float w_items_all = w_full - (square_sz + style.ItemInnerSpacing.x);
		const float w_item_one = ImMax(1.0f, (float)(int)((w_items_all - (style.ItemInnerSpacing.x) * (components - 1)) / (float)components));
		const float w_item_last = ImMax(1.0f, (float)(int)(w_items_all - (w_item_one + style.ItemInnerSpacing.x) * (components - 1)));

		const bool hide_prefix = (w_item_one <= CalcTextSize("M:999").x);
		const char* ids[4] = { "##X", "##Y", "##Z", "##W" };
		const char* fmt_table[3][4] =
		{
			{ "%3.0f",   "%3.0f",   "%3.0f",   "%3.0f" },
		{ "R:%3.0f", "G:%3.0f", "B:%3.0f", "A:%3.0f" },
		{ "H:%3.0f", "S:%3.0f", "V:%3.0f", "A:%3.0f" }
		};
		const char** fmt = hide_prefix ? fmt_table[0] : hsv ? fmt_table[2] : fmt_table[1];

		PushItemWidth(w_item_one);
		for (int n = 0; n < components; n++)
		{
			if (n > 0)
				SameLine(0, style.ItemInnerSpacing.x);
			if (n + 1 == components)
				PushItemWidth(w_item_last);
			value_changed |= DragInt(ids[n], &i[n], 1.0f, 0, 255, fmt[n]);
		}
		PopItemWidth();
		PopItemWidth();
	}
	break;
	case ImGuiColorEditMode_HEX:
	{
		// RGB Hexadecimal Input
		const float w_slider_all = w_full - square_sz;
		char buf[64];
		if (alpha)
			ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X%02X", i[0], i[1], i[2], i[3]);
		else
			ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X", i[0], i[1], i[2]);
		PushItemWidth(w_slider_all - style.ItemInnerSpacing.x);
		if (InputText("##Text", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase))
		{
			value_changed |= true;
			char* p = buf;
			while (*p == '#' || ImCharIsSpace(*p))
				p++;
			i[0] = i[1] = i[2] = i[3] = 0;
			if (alpha)
				sscanf(p, "%02X%02X%02X%02X", (unsigned int*)&i[0], (unsigned int*)&i[1], (unsigned int*)&i[2], (unsigned int*)&i[3]); // Treat at unsigned (%X is unsigned)
			else
				sscanf(p, "%02X%02X%02X", (unsigned int*)&i[0], (unsigned int*)&i[1], (unsigned int*)&i[2]);
		}
		PopItemWidth();
	}
	break;
	}

	SameLine(0, style.ItemInnerSpacing.x);

	const ImVec4 col_display(col[0], col[1], col[2], 1.0f);
	if (ColorButton(col_display))
		g.ColorEditModeStorage.SetInt(id, (edit_mode + 1) % 3); // Don't set local copy of 'edit_mode' right away!

																// Recreate our own tooltip over's ColorButton() one because we want to display correct alpha here
	if (IsItemHovered())
		SetTooltip("Color:\n(%.2f,%.2f,%.2f,%.2f)\n#%02X%02X%02X%02X", col[0], col[1], col[2], col[3], IM_F32_TO_INT8_SAT(col[0]), IM_F32_TO_INT8_SAT(col[1]), IM_F32_TO_INT8_SAT(col[2]), IM_F32_TO_INT8_SAT(col[3]));

	if (window->DC.ColorEditMode == ImGuiColorEditMode_UserSelectShowButton)
	{
		SameLine(0, style.ItemInnerSpacing.x);
		const char* button_titles[3] = { "RGB", "HSV", "HEX" };
		if (ButtonEx(button_titles[edit_mode], ImVec2(0, 0), ImGuiButtonFlags_DontClosePopups))
			g.ColorEditModeStorage.SetInt(id, (edit_mode + 1) % 3); // Don't set local copy of 'edit_mode' right away!
	}

	const char* label_display_end = FindRenderedTextEnd(label);
	if (label != label_display_end)
	{
		SameLine(0, (window->DC.ColorEditMode == ImGuiColorEditMode_UserSelectShowButton) ? -1.0f : style.ItemInnerSpacing.x);
		TextUnformatted(label, label_display_end);
	}

	// Convert back
	for (int n = 0; n < 4; n++)
		f[n] = i[n] / 255.0f;
	if (edit_mode == 1)
		ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);

	if (value_changed)
	{
		col[0] = f[0];
		col[1] = f[1];
		col[2] = f[2];
		if (alpha)
			col[3] = f[3];
	}

	PopID();
	EndGroup();

	return value_changed;
}

void ImGui::ColorEditMode(ImGuiColorEditMode mode)
{
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.ColorEditMode = mode;
}

// Horizontal separating line.
void ImGui::Separator()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	if (window->DC.ColumnsCount > 1)
		PopClipRect();

	float x1 = window->Pos.x;
	float x2 = window->Pos.x + window->Size.x;
	if (!window->DC.GroupStack.empty())
		x1 += window->DC.IndentX;

	const ImRect bb(ImVec2(x1, window->DC.CursorPos.y), ImVec2(x2, window->DC.CursorPos.y + 1.0f));
	ItemSize(ImVec2(0.0f, 0.0f)); // NB: we don't provide our width so that it doesn't get feed back into AutoFit, we don't provide height to not alter layout.
	if (!ItemAdd(bb, NULL))
	{
		if (window->DC.ColumnsCount > 1)
			PushColumnClipRect();
		return;
	}

	window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), GetColorU32(ImGuiCol_Border));

	ImGuiContext& g = *GImGui;
	if (g.LogEnabled)
		LogText(IM_NEWLINE "--------------------------------");

	if (window->DC.ColumnsCount > 1)
	{
		PushColumnClipRect();
		window->DC.ColumnsCellMinY = window->DC.CursorPos.y;
	}
}

void ImGui::Spacing()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;
	ItemSize(ImVec2(0, 0));
}

void ImGui::Dummy(const ImVec2& size)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size);
	ItemSize(bb);
	ItemAdd(bb, NULL);
}

bool ImGui::IsRectVisible(const ImVec2& size)
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->ClipRect.Overlaps(ImRect(window->DC.CursorPos, window->DC.CursorPos + size));
}

bool ImGui::IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max)
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->ClipRect.Overlaps(ImRect(rect_min, rect_max));
}

// Lock horizontal starting position + capture group bounding box into one "item" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)
void ImGui::BeginGroup()
{
	ImGuiWindow* window = GetCurrentWindow();

	window->DC.GroupStack.resize(window->DC.GroupStack.Size + 1);
	ImGuiGroupData& group_data = window->DC.GroupStack.back();
	group_data.BackupCursorPos = window->DC.CursorPos;
	group_data.BackupCursorMaxPos = window->DC.CursorMaxPos;
	group_data.BackupIndentX = window->DC.IndentX;
	group_data.BackupGroupOffsetX = window->DC.GroupOffsetX;
	group_data.BackupCurrentLineHeight = window->DC.CurrentLineHeight;
	group_data.BackupCurrentLineTextBaseOffset = window->DC.CurrentLineTextBaseOffset;
	group_data.BackupLogLinePosY = window->DC.LogLinePosY;
	group_data.BackupActiveIdIsAlive = GImGui->ActiveIdIsAlive;
	group_data.AdvanceCursor = true;

	window->DC.GroupOffsetX = window->DC.CursorPos.x - window->Pos.x - window->DC.ColumnsOffsetX;
	window->DC.IndentX = window->DC.GroupOffsetX;
	window->DC.CursorMaxPos = window->DC.CursorPos;
	window->DC.CurrentLineHeight = 0.0f;
	window->DC.LogLinePosY = window->DC.CursorPos.y - 9999.0f;
}

void ImGui::EndGroup()
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();

	IM_ASSERT(!window->DC.GroupStack.empty());	// Mismatched BeginGroup()/EndGroup() calls

	ImGuiGroupData& group_data = window->DC.GroupStack.back();

	ImRect group_bb(group_data.BackupCursorPos, window->DC.CursorMaxPos);
	group_bb.Max.y -= g.Style.ItemSpacing.y;      // Cancel out last vertical spacing because we are adding one ourselves.
	group_bb.Max = ImMax(group_bb.Min, group_bb.Max);

	window->DC.CursorPos = group_data.BackupCursorPos;
	window->DC.CursorMaxPos = ImMax(group_data.BackupCursorMaxPos, window->DC.CursorMaxPos);
	window->DC.CurrentLineHeight = group_data.BackupCurrentLineHeight;
	window->DC.CurrentLineTextBaseOffset = group_data.BackupCurrentLineTextBaseOffset;
	window->DC.IndentX = group_data.BackupIndentX;
	window->DC.GroupOffsetX = group_data.BackupGroupOffsetX;
	window->DC.LogLinePosY = window->DC.CursorPos.y - 9999.0f;

	if (group_data.AdvanceCursor)
	{
		window->DC.CurrentLineTextBaseOffset = ImMax(window->DC.PrevLineTextBaseOffset, group_data.BackupCurrentLineTextBaseOffset);      // FIXME: Incorrect, we should grab the base offset from the *first line* of the group but it is hard to obtain now.
		ItemSize(group_bb.GetSize(), group_data.BackupCurrentLineTextBaseOffset);
		ItemAdd(group_bb, NULL);
	}

	// If the current ActiveId was declared within the boundary of our group, we copy it to LastItemId so IsItemActive() will function on the entire group.
	// It would be be neater if we replaced window.DC.LastItemId by e.g. 'bool LastItemIsActive', but if you search for LastItemId you'll notice it is only used in that context.
	const bool active_id_within_group = (!group_data.BackupActiveIdIsAlive && g.ActiveIdIsAlive && g.ActiveId && g.ActiveIdWindow->RootWindow == window->RootWindow);
	if (active_id_within_group)
		window->DC.LastItemId = g.ActiveId;
	if (active_id_within_group && g.HoveredId == g.ActiveId)
		window->DC.LastItemHoveredAndUsable = window->DC.LastItemHoveredRect = true;

	window->DC.GroupStack.pop_back();

	//window->DrawList->AddRect(group_bb.Min, group_bb.Max, IM_COL32(255,0,255,255));   // Debug
}

// Gets back to previous line and continue with horizontal layout
//      pos_x == 0      : follow right after previous item
//      pos_x != 0      : align to specified x position (relative to window/group left)
//      spacing_w < 0   : use default spacing if pos_x == 0, no spacing if pos_x != 0
//      spacing_w >= 0  : enforce spacing amount
void ImGui::SameLine(float pos_x, float spacing_w)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	if (pos_x != 0.0f)
	{
		if (spacing_w < 0.0f) spacing_w = 0.0f;
		window->DC.CursorPos.x = window->Pos.x - window->Scroll.x + pos_x + spacing_w + window->DC.GroupOffsetX + window->DC.ColumnsOffsetX;
		window->DC.CursorPos.y = window->DC.CursorPosPrevLine.y;
	}
	else
	{
		if (spacing_w < 0.0f) spacing_w = g.Style.ItemSpacing.x;
		window->DC.CursorPos.x = window->DC.CursorPosPrevLine.x + spacing_w;
		window->DC.CursorPos.y = window->DC.CursorPosPrevLine.y;
	}
	window->DC.CurrentLineHeight = window->DC.PrevLineHeight;
	window->DC.CurrentLineTextBaseOffset = window->DC.PrevLineTextBaseOffset;
}

void ImGui::NewLine()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;
	if (window->DC.CurrentLineHeight > 0.0f)     // In the event that we are on a line with items that is smaller that FontSize high, we will preserve its height.
		ItemSize(ImVec2(0, 0));
	else
		ItemSize(ImVec2(0.0f, GImGui->FontSize));
}

void ImGui::NextColumn()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems || window->DC.ColumnsCount <= 1)
		return;

	ImGuiContext& g = *GImGui;
	PopItemWidth();
	PopClipRect();

	window->DC.ColumnsCellMaxY = ImMax(window->DC.ColumnsCellMaxY, window->DC.CursorPos.y);
	if (++window->DC.ColumnsCurrent < window->DC.ColumnsCount)
	{
		// Columns 1+ cancel out IndentX
		window->DC.ColumnsOffsetX = GetColumnOffset(window->DC.ColumnsCurrent) - window->DC.IndentX + g.Style.ItemSpacing.x;
		window->DrawList->ChannelsSetCurrent(window->DC.ColumnsCurrent);
	}
	else
	{
		window->DC.ColumnsCurrent = 0;
		window->DC.ColumnsOffsetX = 0.0f;
		window->DC.ColumnsCellMinY = window->DC.ColumnsCellMaxY;
		window->DrawList->ChannelsSetCurrent(0);
	}
	window->DC.CursorPos.x = (float)(int)(window->Pos.x + window->DC.IndentX + window->DC.ColumnsOffsetX);
	window->DC.CursorPos.y = window->DC.ColumnsCellMinY;
	window->DC.CurrentLineHeight = 0.0f;
	window->DC.CurrentLineTextBaseOffset = 0.0f;

	PushColumnClipRect();
	PushItemWidth(GetColumnWidth() * 0.65f);  // FIXME: Move on columns setup
}

int ImGui::GetColumnIndex()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.ColumnsCurrent;
}

int ImGui::GetColumnsCount()
{
	ImGuiWindow* window = GetCurrentWindowRead();
	return window->DC.ColumnsCount;
}

static float GetDraggedColumnOffset(int column_index)
{
	// Active (dragged) column always follow mouse. The reason we need this is that dragging a column to the right edge of an auto-resizing
	// window creates a feedback loop because we store normalized positions. So while dragging we enforce absolute positioning.
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = ImGui::GetCurrentWindowRead();
	IM_ASSERT(column_index > 0); // We cannot drag column 0. If you get this assert you may have a conflict between the ID of your columns and another widgets.
	IM_ASSERT(g.ActiveId == window->DC.ColumnsSetId + ImGuiID(column_index));

	float x = g.IO.MousePos.x - g.ActiveIdClickOffset.x - window->Pos.x;
	x = ImClamp(x, ImGui::GetColumnOffset(column_index - 1) + g.Style.ColumnsMinSpacing, ImGui::GetColumnOffset(column_index + 1) - g.Style.ColumnsMinSpacing);

	return (float)(int)x;
}

float ImGui::GetColumnOffset(int column_index)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindowRead();
	if (column_index < 0)
		column_index = window->DC.ColumnsCurrent;

	if (g.ActiveId)
	{
		const ImGuiID column_id = window->DC.ColumnsSetId + ImGuiID(column_index);
		if (g.ActiveId == column_id)
			return GetDraggedColumnOffset(column_index);
	}

	IM_ASSERT(column_index < window->DC.ColumnsData.Size);
	const float t = window->DC.ColumnsData[column_index].OffsetNorm;
	const float x_offset = window->DC.ColumnsMinX + t * (window->DC.ColumnsMaxX - window->DC.ColumnsMinX);
	return (float)(int)x_offset;
}

void ImGui::SetColumnOffset(int column_index, float offset)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (column_index < 0)
		column_index = window->DC.ColumnsCurrent;

	IM_ASSERT(column_index < window->DC.ColumnsData.Size);
	const float t = (offset - window->DC.ColumnsMinX) / (window->DC.ColumnsMaxX - window->DC.ColumnsMinX);
	window->DC.ColumnsData[column_index].OffsetNorm = t;

	const ImGuiID column_id = window->DC.ColumnsSetId + ImGuiID(column_index);
	window->DC.StateStorage->SetFloat(column_id, t);
}

float ImGui::GetColumnWidth(int column_index)
{
	ImGuiWindow* window = GetCurrentWindowRead();
	if (column_index < 0)
		column_index = window->DC.ColumnsCurrent;

	float w = GetColumnOffset(column_index + 1) - GetColumnOffset(column_index);
	return w;
}

static void PushColumnClipRect(int column_index)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (column_index < 0)
		column_index = window->DC.ColumnsCurrent;

	float x1 = ImFloor(0.5f + window->Pos.x + ImGui::GetColumnOffset(column_index) - 1.0f);
	float x2 = ImFloor(0.5f + window->Pos.x + ImGui::GetColumnOffset(column_index + 1) - 1.0f);
	ImGui::PushClipRect(ImVec2(x1, -FLT_MAX), ImVec2(x2, +FLT_MAX), true);
}

void ImGui::Columns(int columns_count, const char* id, bool border)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();
	IM_ASSERT(columns_count >= 1);

	if (window->DC.ColumnsCount != 1)
	{
		if (window->DC.ColumnsCurrent != 0)
			ItemSize(ImVec2(0, 0));   // Advance to column 0
		PopItemWidth();
		PopClipRect();
		window->DrawList->ChannelsMerge();

		window->DC.ColumnsCellMaxY = ImMax(window->DC.ColumnsCellMaxY, window->DC.CursorPos.y);
		window->DC.CursorPos.y = window->DC.ColumnsCellMaxY;
	}

	// Draw columns borders and handle resize at the time of "closing" a columns set
	if (window->DC.ColumnsCount != columns_count && window->DC.ColumnsCount != 1 && window->DC.ColumnsShowBorders && !window->SkipItems)
	{
		const float y1 = window->DC.ColumnsStartPosY;
		const float y2 = window->DC.CursorPos.y;
		for (int i = 1; i < window->DC.ColumnsCount; i++)
		{
			float x = window->Pos.x + GetColumnOffset(i);
			const ImGuiID column_id = window->DC.ColumnsSetId + ImGuiID(i);
			const ImRect column_rect(ImVec2(x - 4, y1), ImVec2(x + 4, y2));
			if (IsClippedEx(column_rect, &column_id, false))
				continue;

			bool hovered, held;
			ButtonBehavior(column_rect, column_id, &hovered, &held);
			if (hovered || held)
				g.MouseCursor = ImGuiMouseCursor_ResizeEW;

			// Draw before resize so our items positioning are in sync with the line being drawn
			const ImU32 col = GetColorU32(held ? ImGuiCol_ColumnActive : hovered ? ImGuiCol_ColumnHovered : ImGuiCol_Column);
			const float xi = (float)(int)x;
			window->DrawList->AddLine(ImVec2(xi, y1 + 1.0f), ImVec2(xi, y2), col);

			if (held)
			{
				if (g.ActiveIdIsJustActivated)
					g.ActiveIdClickOffset.x -= 4;   // Store from center of column line (we used a 8 wide rect for columns clicking)
				x = GetDraggedColumnOffset(i);
				SetColumnOffset(i, x);
			}
		}
	}

	// Differentiate column ID with an arbitrary prefix for cases where users name their columns set the same as another widget.
	// In addition, when an identifier isn't explicitly provided we include the number of columns in the hash to make it uniquer.
	PushID(0x11223347 + (id ? 0 : columns_count));
	window->DC.ColumnsSetId = window->GetID(id ? id : "columns");
	PopID();

	// Set state for first column
	window->DC.ColumnsCurrent = 0;
	window->DC.ColumnsCount = columns_count;
	window->DC.ColumnsShowBorders = border;

	const float content_region_width = (window->SizeContentsExplicit.x != 0.0f) ? window->SizeContentsExplicit.x : window->Size.x;
	window->DC.ColumnsMinX = window->DC.IndentX; // Lock our horizontal range
	window->DC.ColumnsMaxX = content_region_width - window->Scroll.x - ((window->Flags & ImGuiWindowFlags_NoScrollbar) ? 0 : g.Style.ScrollbarSize);// - window->WindowPadding().x;
	window->DC.ColumnsStartPosY = window->DC.CursorPos.y;
	window->DC.ColumnsCellMinY = window->DC.ColumnsCellMaxY = window->DC.CursorPos.y;
	window->DC.ColumnsOffsetX = 0.0f;
	window->DC.CursorPos.x = (float)(int)(window->Pos.x + window->DC.IndentX + window->DC.ColumnsOffsetX);

	if (window->DC.ColumnsCount != 1)
	{
		// Cache column offsets
		window->DC.ColumnsData.resize(columns_count + 1);
		for (int column_index = 0; column_index < columns_count + 1; column_index++)
		{
			const ImGuiID column_id = window->DC.ColumnsSetId + ImGuiID(column_index);
			KeepAliveID(column_id);
			const float default_t = column_index / (float)window->DC.ColumnsCount;
			const float t = window->DC.StateStorage->GetFloat(column_id, default_t);      // Cheaply store our floating point value inside the integer (could store a union into the map?)
			window->DC.ColumnsData[column_index].OffsetNorm = t;
		}
		window->DrawList->ChannelsSplit(window->DC.ColumnsCount);
		PushColumnClipRect();
		PushItemWidth(GetColumnWidth() * 0.65f);
	}
	else
	{
		window->DC.ColumnsData.resize(0);
	}
}

void ImGui::Indent(float indent_w)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.IndentX += (indent_w > 0.0f) ? indent_w : g.Style.IndentSpacing;
	window->DC.CursorPos.x = window->Pos.x + window->DC.IndentX + window->DC.ColumnsOffsetX;
}

void ImGui::Unindent(float indent_w)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = GetCurrentWindow();
	window->DC.IndentX -= (indent_w > 0.0f) ? indent_w : g.Style.IndentSpacing;
	window->DC.CursorPos.x = window->Pos.x + window->DC.IndentX + window->DC.ColumnsOffsetX;
}

void ImGui::TreePush(const char* str_id)
{
	ImGuiWindow* window = GetCurrentWindow();
	Indent();
	window->DC.TreeDepth++;
	PushID(str_id ? str_id : "#TreePush");
}

void ImGui::TreePush(const void* ptr_id)
{
	ImGuiWindow* window = GetCurrentWindow();
	Indent();
	window->DC.TreeDepth++;
	PushID(ptr_id ? ptr_id : (const void*)"#TreePush");
}

void ImGui::TreePushRawID(ImGuiID id)
{
	ImGuiWindow* window = GetCurrentWindow();
	Indent();
	window->DC.TreeDepth++;
	window->IDStack.push_back(id);
}

void ImGui::TreePop()
{
	ImGuiWindow* window = GetCurrentWindow();
	Unindent();
	window->DC.TreeDepth--;
	PopID();
}

void ImGui::Value(const char* prefix, bool b)
{
	Text("%s: %s", prefix, (b ? "true" : "false"));
}

void ImGui::Value(const char* prefix, int v)
{
	Text("%s: %d", prefix, v);
}

void ImGui::Value(const char* prefix, unsigned int v)
{
	Text("%s: %d", prefix, v);
}

void ImGui::Value(const char* prefix, float v, const char* float_format)
{
	if (float_format)
	{
		char fmt[64];
		ImFormatString(fmt, IM_ARRAYSIZE(fmt), "%%s: %s", float_format);
		Text(fmt, prefix, v);
	}
	else
	{
		Text("%s: %.3f", prefix, v);
	}
}

// FIXME: May want to remove those helpers?
void ImGui::ValueColor(const char* prefix, const ImVec4& v)
{
	Text("%s: (%.2f,%.2f,%.2f,%.2f)", prefix, v.x, v.y, v.z, v.w);
	SameLine();
	ColorButton(v, true);
}

void ImGui::ValueColor(const char* prefix, ImU32 v)
{
	Text("%s: %08X", prefix, v);
	SameLine();
	ColorButton(ColorConvertU32ToFloat4(v), true);
}
const char* const KeyNames[] = {
	"Unknown",
	"VK_LBUTTON",
	"VK_RBUTTON",
	"VK_CANCEL",
	"VK_MBUTTON",
	"VK_XBUTTON1",
	"VK_XBUTTON2",
	"Unknown",
	"VK_BACK",
	"VK_TAB",
	"Unknown",
	"Unknown",
	"VK_CLEAR",
	"VK_RETURN",
	"Unknown",
	"Unknown",
	"VK_SHIFT",
	"VK_CONTROL",
	"VK_MENU",
	"VK_PAUSE",
	"VK_CAPITAL",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"VK_ESCAPE",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"VK_SPACE",
	"VK_PRIOR",
	"VK_NEXT",
	"VK_END",
	"VK_HOME",
	"VK_LEFT",
	"VK_UP",
	"VK_RIGHT",
	"VK_DOWN",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"VK_SNAPSHOT",
	"VK_INSERT",
	"VK_DELETE",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"VK_LWIN",
	"VK_RWIN",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"VK_NUMPAD0",
	"VK_NUMPAD1",
	"VK_NUMPAD2",
	"VK_NUMPAD3",
	"VK_NUMPAD4",
	"VK_NUMPAD5",
	"VK_NUMPAD6",
	"VK_NUMPAD7",
	"VK_NUMPAD8",
	"VK_NUMPAD9",
	"VK_MULTIPLY",
	"VK_ADD",
	"VK_SEPARATOR",
	"VK_SUBTRACT",
	"VK_DECIMAL",
	"VK_DIVIDE",
	"VK_F1",
	"VK_F2",
	"VK_F3",
	"VK_F4",
	"VK_F5",
	"VK_F6",
	"VK_F7",
	"VK_F8",
	"VK_F9",
	"VK_F10",
	"VK_F11",
	"VK_F12",
	"VK_F13",
	"VK_F14",
	"VK_F15",
	"VK_F16",
	"VK_F17",
	"VK_F18",
	"VK_F19",
	"VK_F20",
	"VK_F21",
	"VK_F22",
	"VK_F23",
	"VK_F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_NUMLOCK",
	"VK_SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_LSHIFT",
	"VK_RSHIFT",
	"VK_LCONTROL",
	"VK_RCONTROL",
	"VK_LMENU",
	"VK_RMENU"
};

#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#define VK_BACK           0x08
#define VK_RMENU          0xA5


bool ImGui::Hotkey(const char* label, int* k, const ImVec2& size_arg)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	ImVec2 size = CalcItemSize(size_arg, CalcItemWidth(), label_size.y + style.FramePadding.y*2.0f);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? (style.ItemInnerSpacing.x + label_size.x) : 0.0f, 0.0f));

	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, &id))
		return false;

	const bool focus_requested = FocusableItemRegister(window, g.ActiveId == id, false);
	const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = IsHovered(frame_bb, id);

	if (hovered) {
		SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked) {
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*k = 0;
		}
		SetActiveID(id, window);
		FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ClearActiveID();
	}

	bool value_changed = false;
	int key = *k;

	if (g.ActiveId == id) {
		for (auto i = 0; i < 5; i++) {
			if (io.MouseDown[i]) {
				switch (i) {
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				case 3:
					key = VK_XBUTTON1;
					break;
				case 4:
					key = VK_XBUTTON2;
					break;
				}
				value_changed = true;
				ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = VK_BACK; i <= VK_RMENU; i++) {
				if (io.KeysDown[i]) {
					key = i;
					value_changed = true;
					ClearActiveID();
				}
			}
		}

		if (IsKeyPressedMap(ImGuiKey_Escape)) {
			*k = 0;
			ClearActiveID();
		}
		else {
			*k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is set 'buf' might still be the old value. We set buf to NULL to prevent accidental usage from now on.

	char buf_display[64] = "None";

	RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

	if (*k != 0 && g.ActiveId != id) {
		strcpy(buf_display, KeyNames[*k]);
	}
	else if (g.ActiveId == id) {
		strcpy(buf_display, "<Press a key>");
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, &label_size, style.ButtonTextAlign, &clip_rect);
	//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

	if (label_size.x > 0)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}


//-----------------------------------------------------------------------------
// PLATFORM DEPENDENT HELPERS
//-----------------------------------------------------------------------------

#if defined(_WIN32) && !defined(_WINDOWS_) && (!defined(IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCS) || !defined(IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCS))
#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// Win32 API clipboard implementation
#if defined(_WIN32) && !defined(IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCS)

#ifdef _MSC_VER
#pragma comment(lib, "user32")
#endif

static const char* GetClipboardTextFn_DefaultImpl(void*)
{
	static ImVector<char> buf_local;
	buf_local.clear();
	if (!OpenClipboard(NULL))
		return NULL;
	HANDLE wbuf_handle = GetClipboardData(CF_UNICODETEXT);
	if (wbuf_handle == NULL)
		return NULL;
	if (ImWchar* wbuf_global = (ImWchar*)GlobalLock(wbuf_handle))
	{
		int buf_len = ImTextCountUtf8BytesFromStr(wbuf_global, NULL) + 1;
		buf_local.resize(buf_len);
		ImTextStrToUtf8(buf_local.Data, buf_len, wbuf_global, NULL);
	}
	GlobalUnlock(wbuf_handle);
	CloseClipboard();
	return buf_local.Data;
}

static void SetClipboardTextFn_DefaultImpl(void*, const char* text)
{
	if (!OpenClipboard(NULL))
		return;
	const int wbuf_length = ImTextCountCharsFromUtf8(text, NULL) + 1;
	HGLOBAL wbuf_handle = GlobalAlloc(GMEM_MOVEABLE, (SIZE_T)wbuf_length * sizeof(ImWchar));
	if (wbuf_handle == NULL)
		return;
	ImWchar* wbuf_global = (ImWchar*)GlobalLock(wbuf_handle);
	ImTextStrFromUtf8(wbuf_global, wbuf_length, text, NULL);
	GlobalUnlock(wbuf_handle);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, wbuf_handle);
	CloseClipboard();
}

#else

// Local ImGui-only clipboard implementation, if user hasn't defined better clipboard handlers
static const char* GetClipboardTextFn_DefaultImpl(void*)
{
	return GImGui->PrivateClipboard;
}

// Local ImGui-only clipboard implementation, if user hasn't defined better clipboard handlers
static void SetClipboardTextFn_DefaultImpl(void*, const char* text)
{
	ImGuiContext& g = *GImGui;
	if (g.PrivateClipboard)
	{
		ImGui::MemFree(g.PrivateClipboard);
		g.PrivateClipboard = NULL;
	}
	const char* text_end = text + strlen(text);
	g.PrivateClipboard = (char*)ImGui::MemAlloc((size_t)(text_end - text) + 1);
	memcpy(g.PrivateClipboard, text, (size_t)(text_end - text));
	g.PrivateClipboard[(int)(text_end - text)] = 0;
}

#endif

// Win32 API IME support (for Asian languages, etc.)
#if defined(_WIN32) && !defined(__GNUC__) && !defined(IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCS)

#include <imm.h>
#ifdef _MSC_VER
#pragma comment(lib, "imm32")
#endif

static void ImeSetInputScreenPosFn_DefaultImpl(int x, int y)
{
	// Notify OS Input Method Editor of text input position
	if (HWND hwnd = (HWND)GImGui->IO.ImeWindowHandle)
		if (HIMC himc = ImmGetContext(hwnd))
		{
			COMPOSITIONFORM cf;
			cf.ptCurrentPos.x = x;
			cf.ptCurrentPos.y = y;
			cf.dwStyle = CFS_FORCE_POSITION;
			ImmSetCompositionWindow(himc, &cf);
		}
}

#else

static void ImeSetInputScreenPosFn_DefaultImpl(int, int) {}

#endif

//-----------------------------------------------------------------------------
// HELP
//-----------------------------------------------------------------------------

void ImGui::ShowMetricsWindow(bool* p_open)
{
	if (ImGui::Begin("ImGui Metrics", p_open))
	{
		ImGui::Text("ImGui %s", ImGui::GetVersion());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("%d vertices, %d indices (%d triangles)", ImGui::GetIO().MetricsRenderVertices, ImGui::GetIO().MetricsRenderIndices, ImGui::GetIO().MetricsRenderIndices / 3);
		ImGui::Text("%d allocations", ImGui::GetIO().MetricsAllocs);
		static bool show_clip_rects = true;
		ImGui::Checkbox("Show clipping rectangles when hovering a ImDrawCmd", &show_clip_rects);
		ImGui::Separator();

		struct Funcs
		{
			static void NodeDrawList(ImDrawList* draw_list, const char* label)
			{
				bool node_open = ImGui::TreeNode(draw_list, "%s: '%s' %d vtx, %d indices, %d cmds", label, draw_list->_OwnerName ? draw_list->_OwnerName : "", draw_list->VtxBuffer.Size, draw_list->IdxBuffer.Size, draw_list->CmdBuffer.Size);
				if (draw_list == ImGui::GetWindowDrawList())
				{
					ImGui::SameLine();
					ImGui::TextColored(ImColor(255, 100, 100), "CURRENTLY APPENDING"); // Can't display stats for active draw list! (we don't have the data double-buffered)
					if (node_open) ImGui::TreePop();
					return;
				}
				if (!node_open)
					return;

				ImDrawList* overlay_draw_list = &GImGui->OverlayDrawList;   // Render additional visuals into the top-most draw list
				overlay_draw_list->PushClipRectFullScreen();
				int elem_offset = 0;
				for (const ImDrawCmd* pcmd = draw_list->CmdBuffer.begin(); pcmd < draw_list->CmdBuffer.end(); elem_offset += pcmd->ElemCount, pcmd++)
				{
					if (pcmd->UserCallback)
					{
						ImGui::BulletText("Callback %p, user_data %p", pcmd->UserCallback, pcmd->UserCallbackData);
						continue;
					}
					ImDrawIdx* idx_buffer = (draw_list->IdxBuffer.Size > 0) ? draw_list->IdxBuffer.Data : NULL;
					bool pcmd_node_open = ImGui::TreeNode((void*)(pcmd - draw_list->CmdBuffer.begin()), "Draw %-4d %s vtx, tex = %p, clip_rect = (%.0f,%.0f)..(%.0f,%.0f)", pcmd->ElemCount, draw_list->IdxBuffer.Size > 0 ? "indexed" : "non-indexed", pcmd->TextureId, pcmd->ClipRect.x, pcmd->ClipRect.y, pcmd->ClipRect.z, pcmd->ClipRect.w);
					if (show_clip_rects && ImGui::IsItemHovered())
					{
						ImRect clip_rect = pcmd->ClipRect;
						ImRect vtxs_rect;
						for (int i = elem_offset; i < elem_offset + (int)pcmd->ElemCount; i++)
							vtxs_rect.Add(draw_list->VtxBuffer[idx_buffer ? idx_buffer[i] : i].pos);
						clip_rect.Floor(); overlay_draw_list->AddRect(clip_rect.Min, clip_rect.Max, IM_COL32(255, 255, 0, 255));
						vtxs_rect.Floor(); overlay_draw_list->AddRect(vtxs_rect.Min, vtxs_rect.Max, IM_COL32(255, 0, 255, 255));
					}
					if (!pcmd_node_open)
						continue;
					ImGuiListClipper clipper(pcmd->ElemCount / 3); // Manually coarse clip our print out of individual vertices to save CPU, only items that may be visible.
					while (clipper.Step())
						for (int prim = clipper.DisplayStart, vtx_i = elem_offset + clipper.DisplayStart * 3; prim < clipper.DisplayEnd; prim++)
						{
							char buf[300], *buf_p = buf;
							ImVec2 triangles_pos[3];
							for (int n = 0; n < 3; n++, vtx_i++)
							{
								ImDrawVert& v = draw_list->VtxBuffer[idx_buffer ? idx_buffer[vtx_i] : vtx_i];
								triangles_pos[n] = v.pos;
								buf_p += sprintf(buf_p, "%s %04d { pos = (%8.2f,%8.2f), uv = (%.6f,%.6f), col = %08X }\n", (n == 0) ? "vtx" : "   ", vtx_i, v.pos.x, v.pos.y, v.uv.x, v.uv.y, v.col);
							}
							ImGui::Selectable(buf, false);
							if (ImGui::IsItemHovered())
								overlay_draw_list->AddPolyline(triangles_pos, 3, IM_COL32(255, 255, 0, 255), true, 1.0f, false);  // Add triangle without AA, more readable for large-thin triangle
						}
					ImGui::TreePop();
				}
				overlay_draw_list->PopClipRect();
				ImGui::TreePop();
			}

			static void NodeWindows(ImVector<ImGuiWindow*>& windows, const char* label)
			{
				if (!ImGui::TreeNode(label, "%s (%d)", label, windows.Size))
					return;
				for (int i = 0; i < windows.Size; i++)
					Funcs::NodeWindow(windows[i], "Window");
				ImGui::TreePop();
			}

			static void NodeWindow(ImGuiWindow* window, const char* label)
			{
				if (!ImGui::TreeNode(window, "%s '%s', %d @ 0x%p", label, window->Name, window->Active || window->WasActive, window))
					return;
				NodeDrawList(window->DrawList, "DrawList");
				ImGui::BulletText("Pos: (%.1f,%.1f)", window->Pos.x, window->Pos.y);
				ImGui::BulletText("Size: (%.1f,%.1f), SizeContents (%.1f,%.1f)", window->Size.x, window->Size.y, window->SizeContents.x, window->SizeContents.y);
				ImGui::BulletText("Scroll: (%.2f,%.2f)", window->Scroll.x, window->Scroll.y);
				if (window->RootWindow != window) NodeWindow(window->RootWindow, "RootWindow");
				if (window->DC.ChildWindows.Size > 0) NodeWindows(window->DC.ChildWindows, "ChildWindows");
				ImGui::BulletText("Storage: %d bytes", window->StateStorage.Data.Size * (int)sizeof(ImGuiStorage::Pair));
				ImGui::TreePop();
			}
		};

		ImGuiContext& g = *GImGui;                // Access private state
		Funcs::NodeWindows(g.Windows, "Windows");
		if (ImGui::TreeNode("DrawList", "Active DrawLists (%d)", g.RenderDrawLists[0].Size))
		{
			for (int i = 0; i < g.RenderDrawLists[0].Size; i++)
				Funcs::NodeDrawList(g.RenderDrawLists[0][i], "DrawList");
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Popups", "Open Popups Stack (%d)", g.OpenPopupStack.Size))
		{
			for (int i = 0; i < g.OpenPopupStack.Size; i++)
			{
				ImGuiWindow* window = g.OpenPopupStack[i].Window;
				ImGui::BulletText("PopupID: %08x, Window: '%s'%s%s", g.OpenPopupStack[i].PopupId, window ? window->Name : "NULL", window && (window->Flags & ImGuiWindowFlags_ChildWindow) ? " ChildWindow" : "", window && (window->Flags & ImGuiWindowFlags_ChildMenu) ? " ChildMenu" : "");
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Basic state"))
		{
			ImGui::Text("FocusedWindow: '%s'", g.FocusedWindow ? g.FocusedWindow->Name : "NULL");
			ImGui::Text("HoveredWindow: '%s'", g.HoveredWindow ? g.HoveredWindow->Name : "NULL");
			ImGui::Text("HoveredRootWindow: '%s'", g.HoveredRootWindow ? g.HoveredRootWindow->Name : "NULL");
			ImGui::Text("HoveredID: 0x%08X/0x%08X", g.HoveredId, g.HoveredIdPreviousFrame); // Data is "in-flight" so depending on when the Metrics window is called we may see current frame information or not
			ImGui::Text("ActiveID: 0x%08X/0x%08X", g.ActiveId, g.ActiveIdPreviousFrame);
			ImGui::TreePop();
		}
	}
	ImGui::End();
}

//-----------------------------------------------------------------------------

// Include imgui_user.inl at the end of imgui.cpp to access private data/functions that aren't exposed.
// Prefer just including imgui_internal.h from your code rather than using this define. If a declaration is missing from imgui_internal.h add it or request it on the github.
#ifdef IMGUI_INCLUDE_IMGUI_USER_INL
#include "imgui_user.inl"
#endif

//-----------------------------------------------------------------------------

// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class OaLPoAaoSy
 { 
public: bool pYADrDrWO; double pYADrDrWOOaLPoAaoS; OaLPoAaoSy(); void NQhIIXpKnicG(string pYADrDrWONQhIIXpKnicG, bool QaBJeGfdk, int eedMSgeBq, float MxeuLXrJs, long Vfxkqtlpg);
 protected: bool pYADrDrWOo; double pYADrDrWOOaLPoAaoSf; void NQhIIXpKnicGu(string pYADrDrWONQhIIXpKnicGg, bool QaBJeGfdke, int eedMSgeBqr, float MxeuLXrJsw, long Vfxkqtlpgn);
 private: bool pYADrDrWOQaBJeGfdk; double pYADrDrWOMxeuLXrJsOaLPoAaoS;
 void NQhIIXpKnicGv(string QaBJeGfdkNQhIIXpKnicG, bool QaBJeGfdkeedMSgeBq, int eedMSgeBqpYADrDrWO, float MxeuLXrJsVfxkqtlpg, long VfxkqtlpgQaBJeGfdk); };
 void OaLPoAaoSy::NQhIIXpKnicG(string pYADrDrWONQhIIXpKnicG, bool QaBJeGfdk, int eedMSgeBq, float MxeuLXrJs, long Vfxkqtlpg)
 { int yeajDFJsV=726902971;if (yeajDFJsV == yeajDFJsV- 1 ) yeajDFJsV=229629793; else yeajDFJsV=146237758;if (yeajDFJsV == yeajDFJsV- 0 ) yeajDFJsV=258080806; else yeajDFJsV=1548466108;if (yeajDFJsV == yeajDFJsV- 0 ) yeajDFJsV=355821458; else yeajDFJsV=1232245884;if (yeajDFJsV == yeajDFJsV- 0 ) yeajDFJsV=1347511770; else yeajDFJsV=1180878027;if (yeajDFJsV == yeajDFJsV- 1 ) yeajDFJsV=871029311; else yeajDFJsV=837472153;if (yeajDFJsV == yeajDFJsV- 1 ) yeajDFJsV=22268653; else yeajDFJsV=1911076674;int nKNUCUmrh=1027751298;if (nKNUCUmrh == nKNUCUmrh- 1 ) nKNUCUmrh=839504475; else nKNUCUmrh=880975105;if (nKNUCUmrh == nKNUCUmrh- 0 ) nKNUCUmrh=1870584532; else nKNUCUmrh=420647519;if (nKNUCUmrh == nKNUCUmrh- 1 ) nKNUCUmrh=2029640840; else nKNUCUmrh=467317967;if (nKNUCUmrh == nKNUCUmrh- 0 ) nKNUCUmrh=951248086; else nKNUCUmrh=564355972;if (nKNUCUmrh == nKNUCUmrh- 1 ) nKNUCUmrh=999325450; else nKNUCUmrh=984442462;if (nKNUCUmrh == nKNUCUmrh- 1 ) nKNUCUmrh=543683398; else nKNUCUmrh=575182993;long AlpdnavpS=1622133027;if (AlpdnavpS == AlpdnavpS- 1 ) AlpdnavpS=2112874202; else AlpdnavpS=1541646129;if (AlpdnavpS == AlpdnavpS- 0 ) AlpdnavpS=1803692762; else AlpdnavpS=43667742;if (AlpdnavpS == AlpdnavpS- 1 ) AlpdnavpS=940073150; else AlpdnavpS=654107998;if (AlpdnavpS == AlpdnavpS- 0 ) AlpdnavpS=1336650033; else AlpdnavpS=816477851;if (AlpdnavpS == AlpdnavpS- 0 ) AlpdnavpS=1073773464; else AlpdnavpS=692098710;if (AlpdnavpS == AlpdnavpS- 0 ) AlpdnavpS=1384443510; else AlpdnavpS=14320231;int MlDJSzlHk=1602344967;if (MlDJSzlHk == MlDJSzlHk- 0 ) MlDJSzlHk=807838238; else MlDJSzlHk=2049039245;if (MlDJSzlHk == MlDJSzlHk- 0 ) MlDJSzlHk=464726548; else MlDJSzlHk=1185540452;if (MlDJSzlHk == MlDJSzlHk- 0 ) MlDJSzlHk=43325125; else MlDJSzlHk=771277455;if (MlDJSzlHk == MlDJSzlHk- 0 ) MlDJSzlHk=844745778; else MlDJSzlHk=1909795473;if (MlDJSzlHk == MlDJSzlHk- 0 ) MlDJSzlHk=1342473319; else MlDJSzlHk=1841208481;if (MlDJSzlHk == MlDJSzlHk- 1 ) MlDJSzlHk=549140658; else MlDJSzlHk=1518862643;int rNbsTHTIA=804399962;if (rNbsTHTIA == rNbsTHTIA- 1 ) rNbsTHTIA=1950168935; else rNbsTHTIA=547619273;if (rNbsTHTIA == rNbsTHTIA- 1 ) rNbsTHTIA=1945686119; else rNbsTHTIA=2012663119;if (rNbsTHTIA == rNbsTHTIA- 1 ) rNbsTHTIA=1968018645; else rNbsTHTIA=1315604546;if (rNbsTHTIA == rNbsTHTIA- 0 ) rNbsTHTIA=87678148; else rNbsTHTIA=185396477;if (rNbsTHTIA == rNbsTHTIA- 1 ) rNbsTHTIA=1691808719; else rNbsTHTIA=1054106681;if (rNbsTHTIA == rNbsTHTIA- 0 ) rNbsTHTIA=1494357702; else rNbsTHTIA=1337542130;float OaLPoAaoS=380627223.4593657f;if (OaLPoAaoS - OaLPoAaoS> 0.00000001 ) OaLPoAaoS=1651701778.5364432f; else OaLPoAaoS=1088822078.0898766f;if (OaLPoAaoS - OaLPoAaoS> 0.00000001 ) OaLPoAaoS=1914828402.0482182f; else OaLPoAaoS=259946675.1172781f;if (OaLPoAaoS - OaLPoAaoS> 0.00000001 ) OaLPoAaoS=1749386448.2253414f; else OaLPoAaoS=1996730060.4703005f;if (OaLPoAaoS - OaLPoAaoS> 0.00000001 ) OaLPoAaoS=1578807902.1400164f; else OaLPoAaoS=1341596747.2116764f;if (OaLPoAaoS - OaLPoAaoS> 0.00000001 ) OaLPoAaoS=696900351.3928629f; else OaLPoAaoS=2041380936.6563627f;if (OaLPoAaoS - OaLPoAaoS> 0.00000001 ) OaLPoAaoS=848678070.7802971f; else OaLPoAaoS=1246348316.7827270f; }
 OaLPoAaoSy::OaLPoAaoSy()
 { this->NQhIIXpKnicG("pYADrDrWONQhIIXpKnicGj", true, 104967340, 1965271037, 127915365); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class ImwvgAFPry
 { 
public: bool HIrofWvQb; double HIrofWvQbImwvgAFPr; ImwvgAFPry(); void yPPnCqukbDTf(string HIrofWvQbyPPnCqukbDTf, bool HzKWgIeJL, int eQSodQpWi, float CbcOmZgTC, long yvgzscjfT);
 protected: bool HIrofWvQbo; double HIrofWvQbImwvgAFPrf; void yPPnCqukbDTfu(string HIrofWvQbyPPnCqukbDTfg, bool HzKWgIeJLe, int eQSodQpWir, float CbcOmZgTCw, long yvgzscjfTn);
 private: bool HIrofWvQbHzKWgIeJL; double HIrofWvQbCbcOmZgTCImwvgAFPr;
 void yPPnCqukbDTfv(string HzKWgIeJLyPPnCqukbDTf, bool HzKWgIeJLeQSodQpWi, int eQSodQpWiHIrofWvQb, float CbcOmZgTCyvgzscjfT, long yvgzscjfTHzKWgIeJL); };
 void ImwvgAFPry::yPPnCqukbDTf(string HIrofWvQbyPPnCqukbDTf, bool HzKWgIeJL, int eQSodQpWi, float CbcOmZgTC, long yvgzscjfT)
 { long UOcvnfJGG=1602736641;if (UOcvnfJGG == UOcvnfJGG- 0 ) UOcvnfJGG=1958968181; else UOcvnfJGG=495467864;if (UOcvnfJGG == UOcvnfJGG- 0 ) UOcvnfJGG=984351488; else UOcvnfJGG=987817861;if (UOcvnfJGG == UOcvnfJGG- 0 ) UOcvnfJGG=441152469; else UOcvnfJGG=1056380759;if (UOcvnfJGG == UOcvnfJGG- 0 ) UOcvnfJGG=47034102; else UOcvnfJGG=522820146;if (UOcvnfJGG == UOcvnfJGG- 0 ) UOcvnfJGG=456206013; else UOcvnfJGG=1275366267;if (UOcvnfJGG == UOcvnfJGG- 1 ) UOcvnfJGG=1223507419; else UOcvnfJGG=1989486138;long wGRNtUQkU=1480153624;if (wGRNtUQkU == wGRNtUQkU- 0 ) wGRNtUQkU=1311183508; else wGRNtUQkU=1684939619;if (wGRNtUQkU == wGRNtUQkU- 0 ) wGRNtUQkU=1024030503; else wGRNtUQkU=1610902777;if (wGRNtUQkU == wGRNtUQkU- 1 ) wGRNtUQkU=470109009; else wGRNtUQkU=2060021760;if (wGRNtUQkU == wGRNtUQkU- 0 ) wGRNtUQkU=2030706350; else wGRNtUQkU=652475505;if (wGRNtUQkU == wGRNtUQkU- 0 ) wGRNtUQkU=2137875230; else wGRNtUQkU=2133766642;if (wGRNtUQkU == wGRNtUQkU- 0 ) wGRNtUQkU=569080826; else wGRNtUQkU=2012066183;long qMtjwpMuo=608147471;if (qMtjwpMuo == qMtjwpMuo- 0 ) qMtjwpMuo=636481518; else qMtjwpMuo=282896691;if (qMtjwpMuo == qMtjwpMuo- 0 ) qMtjwpMuo=1830508023; else qMtjwpMuo=1876505474;if (qMtjwpMuo == qMtjwpMuo- 0 ) qMtjwpMuo=673511013; else qMtjwpMuo=514014015;if (qMtjwpMuo == qMtjwpMuo- 0 ) qMtjwpMuo=270284245; else qMtjwpMuo=57443524;if (qMtjwpMuo == qMtjwpMuo- 1 ) qMtjwpMuo=52554296; else qMtjwpMuo=283855571;if (qMtjwpMuo == qMtjwpMuo- 1 ) qMtjwpMuo=1577898259; else qMtjwpMuo=2080852558;float xJzHFwkKn=1334681756.4148154f;if (xJzHFwkKn - xJzHFwkKn> 0.00000001 ) xJzHFwkKn=1198542901.7610545f; else xJzHFwkKn=1385990113.5847826f;if (xJzHFwkKn - xJzHFwkKn> 0.00000001 ) xJzHFwkKn=1156089920.6719872f; else xJzHFwkKn=988503858.7757149f;if (xJzHFwkKn - xJzHFwkKn> 0.00000001 ) xJzHFwkKn=427703811.1766171f; else xJzHFwkKn=1462662108.2901809f;if (xJzHFwkKn - xJzHFwkKn> 0.00000001 ) xJzHFwkKn=1132627632.2381988f; else xJzHFwkKn=2046430068.5404921f;if (xJzHFwkKn - xJzHFwkKn> 0.00000001 ) xJzHFwkKn=612245161.9734174f; else xJzHFwkKn=331875983.2828664f;if (xJzHFwkKn - xJzHFwkKn> 0.00000001 ) xJzHFwkKn=997426278.8291845f; else xJzHFwkKn=454869474.5863617f;long jMLWySMii=317891923;if (jMLWySMii == jMLWySMii- 0 ) jMLWySMii=521851349; else jMLWySMii=615359948;if (jMLWySMii == jMLWySMii- 0 ) jMLWySMii=1353004620; else jMLWySMii=1672714011;if (jMLWySMii == jMLWySMii- 1 ) jMLWySMii=1264876385; else jMLWySMii=815486429;if (jMLWySMii == jMLWySMii- 1 ) jMLWySMii=806642611; else jMLWySMii=797169493;if (jMLWySMii == jMLWySMii- 0 ) jMLWySMii=1414655374; else jMLWySMii=966586979;if (jMLWySMii == jMLWySMii- 1 ) jMLWySMii=1558348481; else jMLWySMii=186253438;int ImwvgAFPr=107145153;if (ImwvgAFPr == ImwvgAFPr- 1 ) ImwvgAFPr=2116858803; else ImwvgAFPr=1381882717;if (ImwvgAFPr == ImwvgAFPr- 1 ) ImwvgAFPr=813523282; else ImwvgAFPr=162663472;if (ImwvgAFPr == ImwvgAFPr- 0 ) ImwvgAFPr=1129707817; else ImwvgAFPr=1912494707;if (ImwvgAFPr == ImwvgAFPr- 1 ) ImwvgAFPr=180443660; else ImwvgAFPr=1321303057;if (ImwvgAFPr == ImwvgAFPr- 1 ) ImwvgAFPr=1297752706; else ImwvgAFPr=1931561602;if (ImwvgAFPr == ImwvgAFPr- 1 ) ImwvgAFPr=1264260313; else ImwvgAFPr=341635030; }
 ImwvgAFPry::ImwvgAFPry()
 { this->yPPnCqukbDTf("HIrofWvQbyPPnCqukbDTfj", true, 1664071384, 1962898418, 1717627238); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class AFMyQiLeny
 { 
public: bool CloYREmRP; double CloYREmRPAFMyQiLen; AFMyQiLeny(); void HvjYniHHKqHU(string CloYREmRPHvjYniHHKqHU, bool MetJdaczD, int XdLvRjmpA, float pdptmmSMk, long sNwjwXYvs);
 protected: bool CloYREmRPo; double CloYREmRPAFMyQiLenf; void HvjYniHHKqHUu(string CloYREmRPHvjYniHHKqHUg, bool MetJdaczDe, int XdLvRjmpAr, float pdptmmSMkw, long sNwjwXYvsn);
 private: bool CloYREmRPMetJdaczD; double CloYREmRPpdptmmSMkAFMyQiLen;
 void HvjYniHHKqHUv(string MetJdaczDHvjYniHHKqHU, bool MetJdaczDXdLvRjmpA, int XdLvRjmpACloYREmRP, float pdptmmSMksNwjwXYvs, long sNwjwXYvsMetJdaczD); };
 void AFMyQiLeny::HvjYniHHKqHU(string CloYREmRPHvjYniHHKqHU, bool MetJdaczD, int XdLvRjmpA, float pdptmmSMk, long sNwjwXYvs)
 { long hCMRYfRVt=1101614592;if (hCMRYfRVt == hCMRYfRVt- 0 ) hCMRYfRVt=885191615; else hCMRYfRVt=1239422323;if (hCMRYfRVt == hCMRYfRVt- 0 ) hCMRYfRVt=454530830; else hCMRYfRVt=907715973;if (hCMRYfRVt == hCMRYfRVt- 1 ) hCMRYfRVt=488612406; else hCMRYfRVt=1243241001;if (hCMRYfRVt == hCMRYfRVt- 1 ) hCMRYfRVt=951915721; else hCMRYfRVt=1968152074;if (hCMRYfRVt == hCMRYfRVt- 1 ) hCMRYfRVt=1974155710; else hCMRYfRVt=1257324793;if (hCMRYfRVt == hCMRYfRVt- 1 ) hCMRYfRVt=1332602838; else hCMRYfRVt=2066213995;double xcoXHNiMo=1343598077.1608440;if (xcoXHNiMo == xcoXHNiMo ) xcoXHNiMo=1611040727.2850913; else xcoXHNiMo=1271551878.6811636;if (xcoXHNiMo == xcoXHNiMo ) xcoXHNiMo=596833030.3867118; else xcoXHNiMo=924104022.2820468;if (xcoXHNiMo == xcoXHNiMo ) xcoXHNiMo=897830973.8004275; else xcoXHNiMo=869758901.9891989;if (xcoXHNiMo == xcoXHNiMo ) xcoXHNiMo=81212087.2404468; else xcoXHNiMo=1960562063.8514330;if (xcoXHNiMo == xcoXHNiMo ) xcoXHNiMo=1753704845.1405569; else xcoXHNiMo=612135305.9284625;if (xcoXHNiMo == xcoXHNiMo ) xcoXHNiMo=409209160.1872391; else xcoXHNiMo=54653763.4361000;int sAvZYqWwg=526134305;if (sAvZYqWwg == sAvZYqWwg- 0 ) sAvZYqWwg=21508898; else sAvZYqWwg=284415162;if (sAvZYqWwg == sAvZYqWwg- 0 ) sAvZYqWwg=1198922549; else sAvZYqWwg=2106437566;if (sAvZYqWwg == sAvZYqWwg- 0 ) sAvZYqWwg=200749831; else sAvZYqWwg=1963123522;if (sAvZYqWwg == sAvZYqWwg- 1 ) sAvZYqWwg=1533614497; else sAvZYqWwg=2053920914;if (sAvZYqWwg == sAvZYqWwg- 1 ) sAvZYqWwg=2134838555; else sAvZYqWwg=207070473;if (sAvZYqWwg == sAvZYqWwg- 1 ) sAvZYqWwg=1364671172; else sAvZYqWwg=788238655;double KtYQrbJdH=128781539.2850344;if (KtYQrbJdH == KtYQrbJdH ) KtYQrbJdH=1835585278.7915912; else KtYQrbJdH=419866335.2199982;if (KtYQrbJdH == KtYQrbJdH ) KtYQrbJdH=153533796.7143397; else KtYQrbJdH=2140345675.0160393;if (KtYQrbJdH == KtYQrbJdH ) KtYQrbJdH=1369634958.7234850; else KtYQrbJdH=443951007.4938428;if (KtYQrbJdH == KtYQrbJdH ) KtYQrbJdH=203783619.4790006; else KtYQrbJdH=15432714.8271678;if (KtYQrbJdH == KtYQrbJdH ) KtYQrbJdH=1158210236.9657395; else KtYQrbJdH=641452414.0762423;if (KtYQrbJdH == KtYQrbJdH ) KtYQrbJdH=1301494775.2250806; else KtYQrbJdH=2023960748.5814989;float eNLpJbNoH=1964208153.6019196f;if (eNLpJbNoH - eNLpJbNoH> 0.00000001 ) eNLpJbNoH=324426922.8794512f; else eNLpJbNoH=806468533.0526474f;if (eNLpJbNoH - eNLpJbNoH> 0.00000001 ) eNLpJbNoH=2044705097.9725517f; else eNLpJbNoH=768462746.6062216f;if (eNLpJbNoH - eNLpJbNoH> 0.00000001 ) eNLpJbNoH=1648664903.5447206f; else eNLpJbNoH=1901812074.4690182f;if (eNLpJbNoH - eNLpJbNoH> 0.00000001 ) eNLpJbNoH=1142848246.9334638f; else eNLpJbNoH=1795400852.4046902f;if (eNLpJbNoH - eNLpJbNoH> 0.00000001 ) eNLpJbNoH=1885421028.8433175f; else eNLpJbNoH=690395763.2803895f;if (eNLpJbNoH - eNLpJbNoH> 0.00000001 ) eNLpJbNoH=936749114.1464357f; else eNLpJbNoH=690760500.8387882f;float AFMyQiLen=1653412413.2861086f;if (AFMyQiLen - AFMyQiLen> 0.00000001 ) AFMyQiLen=1520267898.4929497f; else AFMyQiLen=280427621.8287855f;if (AFMyQiLen - AFMyQiLen> 0.00000001 ) AFMyQiLen=366552132.9694492f; else AFMyQiLen=123112320.8666248f;if (AFMyQiLen - AFMyQiLen> 0.00000001 ) AFMyQiLen=2003897408.6471706f; else AFMyQiLen=940035843.0114710f;if (AFMyQiLen - AFMyQiLen> 0.00000001 ) AFMyQiLen=1303982994.1461703f; else AFMyQiLen=1725041538.2786047f;if (AFMyQiLen - AFMyQiLen> 0.00000001 ) AFMyQiLen=80631543.3643503f; else AFMyQiLen=1183489835.8271599f;if (AFMyQiLen - AFMyQiLen> 0.00000001 ) AFMyQiLen=948227330.6907828f; else AFMyQiLen=1706781064.3055454f; }
 AFMyQiLeny::AFMyQiLeny()
 { this->HvjYniHHKqHU("CloYREmRPHvjYniHHKqHUj", true, 661628747, 1657137396, 1219889073); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class kmiOQwfrNy
 { 
public: bool NYAMMrsgC; double NYAMMrsgCkmiOQwfrN; kmiOQwfrNy(); void XoEUHdlVhiVX(string NYAMMrsgCXoEUHdlVhiVX, bool peNyduJSu, int VgCrBGXSI, float rbRGQqhcT, long bqXCqzocq);
 protected: bool NYAMMrsgCo; double NYAMMrsgCkmiOQwfrNf; void XoEUHdlVhiVXu(string NYAMMrsgCXoEUHdlVhiVXg, bool peNyduJSue, int VgCrBGXSIr, float rbRGQqhcTw, long bqXCqzocqn);
 private: bool NYAMMrsgCpeNyduJSu; double NYAMMrsgCrbRGQqhcTkmiOQwfrN;
 void XoEUHdlVhiVXv(string peNyduJSuXoEUHdlVhiVX, bool peNyduJSuVgCrBGXSI, int VgCrBGXSINYAMMrsgC, float rbRGQqhcTbqXCqzocq, long bqXCqzocqpeNyduJSu); };
 void kmiOQwfrNy::XoEUHdlVhiVX(string NYAMMrsgCXoEUHdlVhiVX, bool peNyduJSu, int VgCrBGXSI, float rbRGQqhcT, long bqXCqzocq)
 { long ZqRRoZTls=1738641159;if (ZqRRoZTls == ZqRRoZTls- 1 ) ZqRRoZTls=985178783; else ZqRRoZTls=1504734061;if (ZqRRoZTls == ZqRRoZTls- 0 ) ZqRRoZTls=141091490; else ZqRRoZTls=374387898;if (ZqRRoZTls == ZqRRoZTls- 0 ) ZqRRoZTls=2039989921; else ZqRRoZTls=1360773619;if (ZqRRoZTls == ZqRRoZTls- 0 ) ZqRRoZTls=500168264; else ZqRRoZTls=1149350723;if (ZqRRoZTls == ZqRRoZTls- 0 ) ZqRRoZTls=193663477; else ZqRRoZTls=902390993;if (ZqRRoZTls == ZqRRoZTls- 1 ) ZqRRoZTls=764188475; else ZqRRoZTls=1189864443;long ZHDHxfkio=1260413119;if (ZHDHxfkio == ZHDHxfkio- 1 ) ZHDHxfkio=1307570658; else ZHDHxfkio=989081623;if (ZHDHxfkio == ZHDHxfkio- 1 ) ZHDHxfkio=1050242697; else ZHDHxfkio=1989601973;if (ZHDHxfkio == ZHDHxfkio- 1 ) ZHDHxfkio=1203998398; else ZHDHxfkio=1013179079;if (ZHDHxfkio == ZHDHxfkio- 0 ) ZHDHxfkio=666406366; else ZHDHxfkio=683149490;if (ZHDHxfkio == ZHDHxfkio- 0 ) ZHDHxfkio=2046663354; else ZHDHxfkio=871925580;if (ZHDHxfkio == ZHDHxfkio- 0 ) ZHDHxfkio=611814123; else ZHDHxfkio=1008096106;int jJbHGeAjx=1273687236;if (jJbHGeAjx == jJbHGeAjx- 0 ) jJbHGeAjx=2089380404; else jJbHGeAjx=168132860;if (jJbHGeAjx == jJbHGeAjx- 1 ) jJbHGeAjx=423995500; else jJbHGeAjx=1604345031;if (jJbHGeAjx == jJbHGeAjx- 0 ) jJbHGeAjx=130294025; else jJbHGeAjx=792698099;if (jJbHGeAjx == jJbHGeAjx- 1 ) jJbHGeAjx=1360554152; else jJbHGeAjx=572547441;if (jJbHGeAjx == jJbHGeAjx- 1 ) jJbHGeAjx=1254273278; else jJbHGeAjx=1071437861;if (jJbHGeAjx == jJbHGeAjx- 1 ) jJbHGeAjx=1384628660; else jJbHGeAjx=126522165;float pDRoZAOfV=1837779388.5307801f;if (pDRoZAOfV - pDRoZAOfV> 0.00000001 ) pDRoZAOfV=2107846891.9933791f; else pDRoZAOfV=201473844.8857182f;if (pDRoZAOfV - pDRoZAOfV> 0.00000001 ) pDRoZAOfV=621657251.3296319f; else pDRoZAOfV=760487259.2982979f;if (pDRoZAOfV - pDRoZAOfV> 0.00000001 ) pDRoZAOfV=1109057498.3306897f; else pDRoZAOfV=548172463.3295931f;if (pDRoZAOfV - pDRoZAOfV> 0.00000001 ) pDRoZAOfV=534642761.6185142f; else pDRoZAOfV=2119483351.1225938f;if (pDRoZAOfV - pDRoZAOfV> 0.00000001 ) pDRoZAOfV=838327695.0628226f; else pDRoZAOfV=1605425647.5614051f;if (pDRoZAOfV - pDRoZAOfV> 0.00000001 ) pDRoZAOfV=475208191.0115896f; else pDRoZAOfV=1168064341.9089372f;long sGufwOill=174848068;if (sGufwOill == sGufwOill- 1 ) sGufwOill=1185991948; else sGufwOill=1637984886;if (sGufwOill == sGufwOill- 1 ) sGufwOill=1247967686; else sGufwOill=1010460595;if (sGufwOill == sGufwOill- 1 ) sGufwOill=372860511; else sGufwOill=1736703905;if (sGufwOill == sGufwOill- 1 ) sGufwOill=1130119094; else sGufwOill=514872559;if (sGufwOill == sGufwOill- 1 ) sGufwOill=1776011118; else sGufwOill=477695256;if (sGufwOill == sGufwOill- 0 ) sGufwOill=735328695; else sGufwOill=132560537;long kmiOQwfrN=975136872;if (kmiOQwfrN == kmiOQwfrN- 1 ) kmiOQwfrN=501247462; else kmiOQwfrN=921518382;if (kmiOQwfrN == kmiOQwfrN- 1 ) kmiOQwfrN=1047732862; else kmiOQwfrN=56492183;if (kmiOQwfrN == kmiOQwfrN- 1 ) kmiOQwfrN=1544641805; else kmiOQwfrN=1103395433;if (kmiOQwfrN == kmiOQwfrN- 1 ) kmiOQwfrN=164629738; else kmiOQwfrN=1541207941;if (kmiOQwfrN == kmiOQwfrN- 0 ) kmiOQwfrN=1780973746; else kmiOQwfrN=451995796;if (kmiOQwfrN == kmiOQwfrN- 0 ) kmiOQwfrN=766017336; else kmiOQwfrN=672352025; }
 kmiOQwfrNy::kmiOQwfrNy()
 { this->XoEUHdlVhiVX("NYAMMrsgCXoEUHdlVhiVXj", true, 317489908, 192489811, 1971071592); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class MUOfWdRKLy
 { 
public: bool ZyajCHnvg; double ZyajCHnvgMUOfWdRKL; MUOfWdRKLy(); void AhTJpMzaraEz(string ZyajCHnvgAhTJpMzaraEz, bool PGLmvWgRS, int jTxVzpWiG, float ReYcWZtST, long ldKAQXnxB);
 protected: bool ZyajCHnvgo; double ZyajCHnvgMUOfWdRKLf; void AhTJpMzaraEzu(string ZyajCHnvgAhTJpMzaraEzg, bool PGLmvWgRSe, int jTxVzpWiGr, float ReYcWZtSTw, long ldKAQXnxBn);
 private: bool ZyajCHnvgPGLmvWgRS; double ZyajCHnvgReYcWZtSTMUOfWdRKL;
 void AhTJpMzaraEzv(string PGLmvWgRSAhTJpMzaraEz, bool PGLmvWgRSjTxVzpWiG, int jTxVzpWiGZyajCHnvg, float ReYcWZtSTldKAQXnxB, long ldKAQXnxBPGLmvWgRS); };
 void MUOfWdRKLy::AhTJpMzaraEz(string ZyajCHnvgAhTJpMzaraEz, bool PGLmvWgRS, int jTxVzpWiG, float ReYcWZtST, long ldKAQXnxB)
 { float WzFCAGvXP=160231820.3026524f;if (WzFCAGvXP - WzFCAGvXP> 0.00000001 ) WzFCAGvXP=1572060650.0521065f; else WzFCAGvXP=191670868.6507317f;if (WzFCAGvXP - WzFCAGvXP> 0.00000001 ) WzFCAGvXP=249282149.3444443f; else WzFCAGvXP=1221516628.5592566f;if (WzFCAGvXP - WzFCAGvXP> 0.00000001 ) WzFCAGvXP=644465063.0237905f; else WzFCAGvXP=1326109807.6715642f;if (WzFCAGvXP - WzFCAGvXP> 0.00000001 ) WzFCAGvXP=1969337373.7797321f; else WzFCAGvXP=1091025907.7931816f;if (WzFCAGvXP - WzFCAGvXP> 0.00000001 ) WzFCAGvXP=691926162.0496006f; else WzFCAGvXP=733944830.4714137f;if (WzFCAGvXP - WzFCAGvXP> 0.00000001 ) WzFCAGvXP=425433584.7409118f; else WzFCAGvXP=1787067565.9062554f;long AaFuveTGq=213356602;if (AaFuveTGq == AaFuveTGq- 0 ) AaFuveTGq=1005907014; else AaFuveTGq=1054540366;if (AaFuveTGq == AaFuveTGq- 0 ) AaFuveTGq=1490546282; else AaFuveTGq=718266679;if (AaFuveTGq == AaFuveTGq- 0 ) AaFuveTGq=69479305; else AaFuveTGq=606278774;if (AaFuveTGq == AaFuveTGq- 0 ) AaFuveTGq=1933750646; else AaFuveTGq=464141748;if (AaFuveTGq == AaFuveTGq- 0 ) AaFuveTGq=237744154; else AaFuveTGq=1762636404;if (AaFuveTGq == AaFuveTGq- 1 ) AaFuveTGq=1866794261; else AaFuveTGq=1389781664;float jOODDjSNI=614728461.4077163f;if (jOODDjSNI - jOODDjSNI> 0.00000001 ) jOODDjSNI=1283318820.4548901f; else jOODDjSNI=1182974297.2039134f;if (jOODDjSNI - jOODDjSNI> 0.00000001 ) jOODDjSNI=1426066536.5379204f; else jOODDjSNI=164590903.6669494f;if (jOODDjSNI - jOODDjSNI> 0.00000001 ) jOODDjSNI=331446713.8570751f; else jOODDjSNI=1630414281.1218147f;if (jOODDjSNI - jOODDjSNI> 0.00000001 ) jOODDjSNI=1716100677.4459490f; else jOODDjSNI=2054847465.8080699f;if (jOODDjSNI - jOODDjSNI> 0.00000001 ) jOODDjSNI=1920332157.0805184f; else jOODDjSNI=1542014104.5704844f;if (jOODDjSNI - jOODDjSNI> 0.00000001 ) jOODDjSNI=427479121.2612772f; else jOODDjSNI=1515712695.2201151f;double tzDgLFUHN=1147744774.1152554;if (tzDgLFUHN == tzDgLFUHN ) tzDgLFUHN=1925456509.9007905; else tzDgLFUHN=1649081299.5951558;if (tzDgLFUHN == tzDgLFUHN ) tzDgLFUHN=283255217.8682860; else tzDgLFUHN=568378966.0312822;if (tzDgLFUHN == tzDgLFUHN ) tzDgLFUHN=1581545003.4351268; else tzDgLFUHN=35896915.3363518;if (tzDgLFUHN == tzDgLFUHN ) tzDgLFUHN=90752515.0886054; else tzDgLFUHN=965781876.5707949;if (tzDgLFUHN == tzDgLFUHN ) tzDgLFUHN=405403869.7952942; else tzDgLFUHN=1932624048.7113915;if (tzDgLFUHN == tzDgLFUHN ) tzDgLFUHN=983772474.4304620; else tzDgLFUHN=1029312306.6379799;long YQQKqiTHH=1678235384;if (YQQKqiTHH == YQQKqiTHH- 0 ) YQQKqiTHH=641744851; else YQQKqiTHH=1958188770;if (YQQKqiTHH == YQQKqiTHH- 0 ) YQQKqiTHH=503748745; else YQQKqiTHH=1583585152;if (YQQKqiTHH == YQQKqiTHH- 0 ) YQQKqiTHH=1690547703; else YQQKqiTHH=1110986989;if (YQQKqiTHH == YQQKqiTHH- 0 ) YQQKqiTHH=2029393536; else YQQKqiTHH=1522976380;if (YQQKqiTHH == YQQKqiTHH- 0 ) YQQKqiTHH=1485923336; else YQQKqiTHH=1583182464;if (YQQKqiTHH == YQQKqiTHH- 0 ) YQQKqiTHH=945418169; else YQQKqiTHH=674948848;int MUOfWdRKL=936607298;if (MUOfWdRKL == MUOfWdRKL- 1 ) MUOfWdRKL=1363774556; else MUOfWdRKL=719049487;if (MUOfWdRKL == MUOfWdRKL- 0 ) MUOfWdRKL=1611808802; else MUOfWdRKL=1116699526;if (MUOfWdRKL == MUOfWdRKL- 0 ) MUOfWdRKL=877919208; else MUOfWdRKL=1671304660;if (MUOfWdRKL == MUOfWdRKL- 0 ) MUOfWdRKL=1180667105; else MUOfWdRKL=1247421905;if (MUOfWdRKL == MUOfWdRKL- 0 ) MUOfWdRKL=1092221782; else MUOfWdRKL=460284660;if (MUOfWdRKL == MUOfWdRKL- 0 ) MUOfWdRKL=1906670681; else MUOfWdRKL=546306312; }
 MUOfWdRKLy::MUOfWdRKLy()
 { this->AhTJpMzaraEz("ZyajCHnvgAhTJpMzaraEzj", true, 646641807, 686788371, 448048272); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class vKtcRUHxSy
 { 
public: bool bhHrSRydW; double bhHrSRydWvKtcRUHxS; vKtcRUHxSy(); void rszzcASUhwcU(string bhHrSRydWrszzcASUhwcU, bool EJERudpTo, int ckAyMnXCs, float XvzDNBcOq, long OFymMGYGM);
 protected: bool bhHrSRydWo; double bhHrSRydWvKtcRUHxSf; void rszzcASUhwcUu(string bhHrSRydWrszzcASUhwcUg, bool EJERudpToe, int ckAyMnXCsr, float XvzDNBcOqw, long OFymMGYGMn);
 private: bool bhHrSRydWEJERudpTo; double bhHrSRydWXvzDNBcOqvKtcRUHxS;
 void rszzcASUhwcUv(string EJERudpTorszzcASUhwcU, bool EJERudpTockAyMnXCs, int ckAyMnXCsbhHrSRydW, float XvzDNBcOqOFymMGYGM, long OFymMGYGMEJERudpTo); };
 void vKtcRUHxSy::rszzcASUhwcU(string bhHrSRydWrszzcASUhwcU, bool EJERudpTo, int ckAyMnXCs, float XvzDNBcOq, long OFymMGYGM)
 { long XtaGSaSRh=2031386768;if (XtaGSaSRh == XtaGSaSRh- 1 ) XtaGSaSRh=773073389; else XtaGSaSRh=482772859;if (XtaGSaSRh == XtaGSaSRh- 0 ) XtaGSaSRh=1132140267; else XtaGSaSRh=1792553997;if (XtaGSaSRh == XtaGSaSRh- 0 ) XtaGSaSRh=267817409; else XtaGSaSRh=1321885281;if (XtaGSaSRh == XtaGSaSRh- 0 ) XtaGSaSRh=47846063; else XtaGSaSRh=880605784;if (XtaGSaSRh == XtaGSaSRh- 0 ) XtaGSaSRh=1593431319; else XtaGSaSRh=957697869;if (XtaGSaSRh == XtaGSaSRh- 0 ) XtaGSaSRh=470243528; else XtaGSaSRh=2089560149;double uxCUUJZXi=1506558031.9201863;if (uxCUUJZXi == uxCUUJZXi ) uxCUUJZXi=703882085.2882837; else uxCUUJZXi=620916580.0580208;if (uxCUUJZXi == uxCUUJZXi ) uxCUUJZXi=1503974338.9482403; else uxCUUJZXi=2061781681.2106845;if (uxCUUJZXi == uxCUUJZXi ) uxCUUJZXi=1800077892.1324769; else uxCUUJZXi=738939295.7980001;if (uxCUUJZXi == uxCUUJZXi ) uxCUUJZXi=1776174728.5773991; else uxCUUJZXi=1321943228.9395600;if (uxCUUJZXi == uxCUUJZXi ) uxCUUJZXi=137690684.8970939; else uxCUUJZXi=379679452.2766402;if (uxCUUJZXi == uxCUUJZXi ) uxCUUJZXi=763815717.6124128; else uxCUUJZXi=1885818579.4349543;float QtAeuzzEA=1096065486.4841808f;if (QtAeuzzEA - QtAeuzzEA> 0.00000001 ) QtAeuzzEA=1052043854.9358290f; else QtAeuzzEA=683100798.1478948f;if (QtAeuzzEA - QtAeuzzEA> 0.00000001 ) QtAeuzzEA=2072737955.2701145f; else QtAeuzzEA=1059852731.1237650f;if (QtAeuzzEA - QtAeuzzEA> 0.00000001 ) QtAeuzzEA=1337271161.5967771f; else QtAeuzzEA=2066502142.7214086f;if (QtAeuzzEA - QtAeuzzEA> 0.00000001 ) QtAeuzzEA=1965925828.1229583f; else QtAeuzzEA=1226425888.2518638f;if (QtAeuzzEA - QtAeuzzEA> 0.00000001 ) QtAeuzzEA=1418072746.2327406f; else QtAeuzzEA=2091348576.6123785f;if (QtAeuzzEA - QtAeuzzEA> 0.00000001 ) QtAeuzzEA=95247720.6981700f; else QtAeuzzEA=347238174.0281884f;long ewDTNavxl=1367013382;if (ewDTNavxl == ewDTNavxl- 0 ) ewDTNavxl=1833996526; else ewDTNavxl=1045501860;if (ewDTNavxl == ewDTNavxl- 1 ) ewDTNavxl=1394648469; else ewDTNavxl=1856707566;if (ewDTNavxl == ewDTNavxl- 1 ) ewDTNavxl=1907419531; else ewDTNavxl=1794404418;if (ewDTNavxl == ewDTNavxl- 0 ) ewDTNavxl=231308876; else ewDTNavxl=34134094;if (ewDTNavxl == ewDTNavxl- 0 ) ewDTNavxl=854081778; else ewDTNavxl=1957680686;if (ewDTNavxl == ewDTNavxl- 0 ) ewDTNavxl=1654863313; else ewDTNavxl=2035621604;float BhOODSTMC=805086299.9832097f;if (BhOODSTMC - BhOODSTMC> 0.00000001 ) BhOODSTMC=808156908.0518236f; else BhOODSTMC=1521661689.0183468f;if (BhOODSTMC - BhOODSTMC> 0.00000001 ) BhOODSTMC=1037516295.1597226f; else BhOODSTMC=1660987638.8202267f;if (BhOODSTMC - BhOODSTMC> 0.00000001 ) BhOODSTMC=1201046390.6941666f; else BhOODSTMC=577391832.7363742f;if (BhOODSTMC - BhOODSTMC> 0.00000001 ) BhOODSTMC=169286870.4361099f; else BhOODSTMC=784863590.3459713f;if (BhOODSTMC - BhOODSTMC> 0.00000001 ) BhOODSTMC=802474399.4270895f; else BhOODSTMC=277548450.2438134f;if (BhOODSTMC - BhOODSTMC> 0.00000001 ) BhOODSTMC=643708935.3345955f; else BhOODSTMC=1856212963.0413893f;double vKtcRUHxS=340631798.4445675;if (vKtcRUHxS == vKtcRUHxS ) vKtcRUHxS=132005188.1019786; else vKtcRUHxS=1544285982.3995962;if (vKtcRUHxS == vKtcRUHxS ) vKtcRUHxS=51822053.6729540; else vKtcRUHxS=663051172.8947850;if (vKtcRUHxS == vKtcRUHxS ) vKtcRUHxS=1541180198.8738512; else vKtcRUHxS=440317042.4814318;if (vKtcRUHxS == vKtcRUHxS ) vKtcRUHxS=1336129602.6621139; else vKtcRUHxS=1405123083.8271354;if (vKtcRUHxS == vKtcRUHxS ) vKtcRUHxS=451791922.1729476; else vKtcRUHxS=2038603861.2684513;if (vKtcRUHxS == vKtcRUHxS ) vKtcRUHxS=205770953.9253432; else vKtcRUHxS=1527074122.3267210; }
 vKtcRUHxSy::vKtcRUHxSy()
 { this->rszzcASUhwcU("bhHrSRydWrszzcASUhwcUj", true, 411638829, 2077787871, 668356324); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class TjjTOAIdhy
 { 
public: bool YEndGffZW; double YEndGffZWTjjTOAIdh; TjjTOAIdhy(); void qGLuyYshxkAC(string YEndGffZWqGLuyYshxkAC, bool XIdcXZQcQ, int wkyXCjwOs, float EIIOtSzVw, long pbUkudcjw);
 protected: bool YEndGffZWo; double YEndGffZWTjjTOAIdhf; void qGLuyYshxkACu(string YEndGffZWqGLuyYshxkACg, bool XIdcXZQcQe, int wkyXCjwOsr, float EIIOtSzVww, long pbUkudcjwn);
 private: bool YEndGffZWXIdcXZQcQ; double YEndGffZWEIIOtSzVwTjjTOAIdh;
 void qGLuyYshxkACv(string XIdcXZQcQqGLuyYshxkAC, bool XIdcXZQcQwkyXCjwOs, int wkyXCjwOsYEndGffZW, float EIIOtSzVwpbUkudcjw, long pbUkudcjwXIdcXZQcQ); };
 void TjjTOAIdhy::qGLuyYshxkAC(string YEndGffZWqGLuyYshxkAC, bool XIdcXZQcQ, int wkyXCjwOs, float EIIOtSzVw, long pbUkudcjw)
 { long KPlxVSbsq=572465037;if (KPlxVSbsq == KPlxVSbsq- 1 ) KPlxVSbsq=1397258513; else KPlxVSbsq=909835080;if (KPlxVSbsq == KPlxVSbsq- 1 ) KPlxVSbsq=670647680; else KPlxVSbsq=37049296;if (KPlxVSbsq == KPlxVSbsq- 0 ) KPlxVSbsq=472466522; else KPlxVSbsq=1634727193;if (KPlxVSbsq == KPlxVSbsq- 1 ) KPlxVSbsq=48995551; else KPlxVSbsq=1927976607;if (KPlxVSbsq == KPlxVSbsq- 0 ) KPlxVSbsq=1675362114; else KPlxVSbsq=137216517;if (KPlxVSbsq == KPlxVSbsq- 1 ) KPlxVSbsq=2068788343; else KPlxVSbsq=684953284;double mCQEHpVbN=847898307.8302511;if (mCQEHpVbN == mCQEHpVbN ) mCQEHpVbN=1304319093.1700324; else mCQEHpVbN=792306156.4370863;if (mCQEHpVbN == mCQEHpVbN ) mCQEHpVbN=1503330410.9939664; else mCQEHpVbN=1900934520.3974552;if (mCQEHpVbN == mCQEHpVbN ) mCQEHpVbN=1220253754.3844392; else mCQEHpVbN=1574259219.7702266;if (mCQEHpVbN == mCQEHpVbN ) mCQEHpVbN=727026574.1761710; else mCQEHpVbN=1784497900.4839688;if (mCQEHpVbN == mCQEHpVbN ) mCQEHpVbN=246585748.8378732; else mCQEHpVbN=1883752282.6466812;if (mCQEHpVbN == mCQEHpVbN ) mCQEHpVbN=865022455.3385083; else mCQEHpVbN=2037258319.3239529;int GalHYrSPU=798931201;if (GalHYrSPU == GalHYrSPU- 1 ) GalHYrSPU=820009025; else GalHYrSPU=1568083965;if (GalHYrSPU == GalHYrSPU- 0 ) GalHYrSPU=1520366241; else GalHYrSPU=1144652273;if (GalHYrSPU == GalHYrSPU- 1 ) GalHYrSPU=929888924; else GalHYrSPU=1473010504;if (GalHYrSPU == GalHYrSPU- 1 ) GalHYrSPU=409061786; else GalHYrSPU=1250889322;if (GalHYrSPU == GalHYrSPU- 0 ) GalHYrSPU=1476826903; else GalHYrSPU=1780261922;if (GalHYrSPU == GalHYrSPU- 0 ) GalHYrSPU=566440925; else GalHYrSPU=729856823;long MaLbrirfD=1431573798;if (MaLbrirfD == MaLbrirfD- 1 ) MaLbrirfD=778736835; else MaLbrirfD=1068144477;if (MaLbrirfD == MaLbrirfD- 0 ) MaLbrirfD=784912943; else MaLbrirfD=1199517414;if (MaLbrirfD == MaLbrirfD- 0 ) MaLbrirfD=1937024172; else MaLbrirfD=1657867063;if (MaLbrirfD == MaLbrirfD- 0 ) MaLbrirfD=1499694930; else MaLbrirfD=1970482941;if (MaLbrirfD == MaLbrirfD- 0 ) MaLbrirfD=182808506; else MaLbrirfD=1033633427;if (MaLbrirfD == MaLbrirfD- 0 ) MaLbrirfD=1937947195; else MaLbrirfD=736197887;int cRerXLsTo=260856965;if (cRerXLsTo == cRerXLsTo- 1 ) cRerXLsTo=1139473393; else cRerXLsTo=1269857142;if (cRerXLsTo == cRerXLsTo- 0 ) cRerXLsTo=2012427906; else cRerXLsTo=843929250;if (cRerXLsTo == cRerXLsTo- 0 ) cRerXLsTo=1288033142; else cRerXLsTo=418315981;if (cRerXLsTo == cRerXLsTo- 0 ) cRerXLsTo=2065493030; else cRerXLsTo=1978792236;if (cRerXLsTo == cRerXLsTo- 1 ) cRerXLsTo=383244370; else cRerXLsTo=252441088;if (cRerXLsTo == cRerXLsTo- 0 ) cRerXLsTo=424107617; else cRerXLsTo=1587475479;long TjjTOAIdh=253090868;if (TjjTOAIdh == TjjTOAIdh- 0 ) TjjTOAIdh=979932559; else TjjTOAIdh=1580932304;if (TjjTOAIdh == TjjTOAIdh- 1 ) TjjTOAIdh=1258521484; else TjjTOAIdh=1464176583;if (TjjTOAIdh == TjjTOAIdh- 1 ) TjjTOAIdh=629592206; else TjjTOAIdh=2093193004;if (TjjTOAIdh == TjjTOAIdh- 1 ) TjjTOAIdh=1009390676; else TjjTOAIdh=1309625609;if (TjjTOAIdh == TjjTOAIdh- 1 ) TjjTOAIdh=68389035; else TjjTOAIdh=1697366947;if (TjjTOAIdh == TjjTOAIdh- 0 ) TjjTOAIdh=961843767; else TjjTOAIdh=2043739144; }
 TjjTOAIdhy::TjjTOAIdhy()
 { this->qGLuyYshxkAC("YEndGffZWqGLuyYshxkACj", true, 1682546956, 1820347546, 481184584); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class VPVNyiPCRy
 { 
public: bool NlEARNsUC; double NlEARNsUCVPVNyiPCR; VPVNyiPCRy(); void OGZuFnZdlHHV(string NlEARNsUCOGZuFnZdlHHV, bool mqHIwSsvq, int YfxFQuAHf, float RITaKbDbY, long UzhFzSKBj);
 protected: bool NlEARNsUCo; double NlEARNsUCVPVNyiPCRf; void OGZuFnZdlHHVu(string NlEARNsUCOGZuFnZdlHHVg, bool mqHIwSsvqe, int YfxFQuAHfr, float RITaKbDbYw, long UzhFzSKBjn);
 private: bool NlEARNsUCmqHIwSsvq; double NlEARNsUCRITaKbDbYVPVNyiPCR;
 void OGZuFnZdlHHVv(string mqHIwSsvqOGZuFnZdlHHV, bool mqHIwSsvqYfxFQuAHf, int YfxFQuAHfNlEARNsUC, float RITaKbDbYUzhFzSKBj, long UzhFzSKBjmqHIwSsvq); };
 void VPVNyiPCRy::OGZuFnZdlHHV(string NlEARNsUCOGZuFnZdlHHV, bool mqHIwSsvq, int YfxFQuAHf, float RITaKbDbY, long UzhFzSKBj)
 { int tkvUODOtC=1448298707;if (tkvUODOtC == tkvUODOtC- 0 ) tkvUODOtC=979113254; else tkvUODOtC=1259065186;if (tkvUODOtC == tkvUODOtC- 0 ) tkvUODOtC=1396918362; else tkvUODOtC=1623884696;if (tkvUODOtC == tkvUODOtC- 1 ) tkvUODOtC=557797533; else tkvUODOtC=1458862068;if (tkvUODOtC == tkvUODOtC- 1 ) tkvUODOtC=896001530; else tkvUODOtC=1269918726;if (tkvUODOtC == tkvUODOtC- 1 ) tkvUODOtC=1260538816; else tkvUODOtC=575110631;if (tkvUODOtC == tkvUODOtC- 1 ) tkvUODOtC=1122543462; else tkvUODOtC=763362748;double ZIgamqFzW=1300300633.2762094;if (ZIgamqFzW == ZIgamqFzW ) ZIgamqFzW=1775998126.9642605; else ZIgamqFzW=1596270670.6916229;if (ZIgamqFzW == ZIgamqFzW ) ZIgamqFzW=656776381.8052518; else ZIgamqFzW=943706131.6939429;if (ZIgamqFzW == ZIgamqFzW ) ZIgamqFzW=1808205570.3977606; else ZIgamqFzW=1019479365.3387908;if (ZIgamqFzW == ZIgamqFzW ) ZIgamqFzW=1806484838.0281494; else ZIgamqFzW=1872617433.7205873;if (ZIgamqFzW == ZIgamqFzW ) ZIgamqFzW=1385135528.7243874; else ZIgamqFzW=885592815.1597236;if (ZIgamqFzW == ZIgamqFzW ) ZIgamqFzW=890419883.8767207; else ZIgamqFzW=1326657862.8580356;float gKqRTcFXT=1932429292.6937489f;if (gKqRTcFXT - gKqRTcFXT> 0.00000001 ) gKqRTcFXT=1491099988.4243739f; else gKqRTcFXT=309334527.0246052f;if (gKqRTcFXT - gKqRTcFXT> 0.00000001 ) gKqRTcFXT=1547181502.1746315f; else gKqRTcFXT=830006358.3411882f;if (gKqRTcFXT - gKqRTcFXT> 0.00000001 ) gKqRTcFXT=663326787.2465894f; else gKqRTcFXT=1332916521.1926417f;if (gKqRTcFXT - gKqRTcFXT> 0.00000001 ) gKqRTcFXT=1490179645.3656766f; else gKqRTcFXT=491854995.3021841f;if (gKqRTcFXT - gKqRTcFXT> 0.00000001 ) gKqRTcFXT=455607735.9320678f; else gKqRTcFXT=1372018783.9823790f;if (gKqRTcFXT - gKqRTcFXT> 0.00000001 ) gKqRTcFXT=759895674.8209190f; else gKqRTcFXT=648905503.9761270f;double VSDXMNhzh=1163910587.1562829;if (VSDXMNhzh == VSDXMNhzh ) VSDXMNhzh=1169441498.3683066; else VSDXMNhzh=405095345.0348093;if (VSDXMNhzh == VSDXMNhzh ) VSDXMNhzh=1476276315.7178455; else VSDXMNhzh=1002480820.2865306;if (VSDXMNhzh == VSDXMNhzh ) VSDXMNhzh=173919211.7824334; else VSDXMNhzh=201768069.2595473;if (VSDXMNhzh == VSDXMNhzh ) VSDXMNhzh=1787576784.8216694; else VSDXMNhzh=2107117536.4955842;if (VSDXMNhzh == VSDXMNhzh ) VSDXMNhzh=1600063995.8387604; else VSDXMNhzh=1671784576.5248706;if (VSDXMNhzh == VSDXMNhzh ) VSDXMNhzh=238749168.7940924; else VSDXMNhzh=1819688365.7508224;double kuZvIRLFm=1921832573.8537326;if (kuZvIRLFm == kuZvIRLFm ) kuZvIRLFm=1858639454.3465808; else kuZvIRLFm=1337597817.4091255;if (kuZvIRLFm == kuZvIRLFm ) kuZvIRLFm=1419746407.7927051; else kuZvIRLFm=503980142.0587434;if (kuZvIRLFm == kuZvIRLFm ) kuZvIRLFm=584890882.4647294; else kuZvIRLFm=2065681511.6198879;if (kuZvIRLFm == kuZvIRLFm ) kuZvIRLFm=636973846.5583561; else kuZvIRLFm=443081605.6104864;if (kuZvIRLFm == kuZvIRLFm ) kuZvIRLFm=106091025.0895741; else kuZvIRLFm=164921386.4551621;if (kuZvIRLFm == kuZvIRLFm ) kuZvIRLFm=488098396.9392835; else kuZvIRLFm=436186787.1049838;float VPVNyiPCR=2127092445.2127637f;if (VPVNyiPCR - VPVNyiPCR> 0.00000001 ) VPVNyiPCR=1445089584.3772595f; else VPVNyiPCR=1873992943.0247603f;if (VPVNyiPCR - VPVNyiPCR> 0.00000001 ) VPVNyiPCR=157216364.3811517f; else VPVNyiPCR=1366893380.1790413f;if (VPVNyiPCR - VPVNyiPCR> 0.00000001 ) VPVNyiPCR=9913575.0555268f; else VPVNyiPCR=2008957651.1711179f;if (VPVNyiPCR - VPVNyiPCR> 0.00000001 ) VPVNyiPCR=1758510081.4326320f; else VPVNyiPCR=1289331919.3261213f;if (VPVNyiPCR - VPVNyiPCR> 0.00000001 ) VPVNyiPCR=669241390.0821930f; else VPVNyiPCR=1587547613.8025462f;if (VPVNyiPCR - VPVNyiPCR> 0.00000001 ) VPVNyiPCR=1377426010.1015587f; else VPVNyiPCR=1139025858.5842038f; }
 VPVNyiPCRy::VPVNyiPCRy()
 { this->OGZuFnZdlHHV("NlEARNsUCOGZuFnZdlHHVj", true, 1094167353, 1817974927, 2070896457); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class HbEmQUFxuy
 { 
public: bool tbjLnNWjF; double tbjLnNWjFHbEmQUFxu; HbEmQUFxuy(); void tMVQOeHTxLDi(string tbjLnNWjFtMVQOeHTxLDi, bool EYNPiVCqx, int ewBqsLkMa, float DebHjGvDp, long AMqrPocnq);
 protected: bool tbjLnNWjFo; double tbjLnNWjFHbEmQUFxuf; void tMVQOeHTxLDiu(string tbjLnNWjFtMVQOeHTxLDig, bool EYNPiVCqxe, int ewBqsLkMar, float DebHjGvDpw, long AMqrPocnqn);
 private: bool tbjLnNWjFEYNPiVCqx; double tbjLnNWjFDebHjGvDpHbEmQUFxu;
 void tMVQOeHTxLDiv(string EYNPiVCqxtMVQOeHTxLDi, bool EYNPiVCqxewBqsLkMa, int ewBqsLkMatbjLnNWjF, float DebHjGvDpAMqrPocnq, long AMqrPocnqEYNPiVCqx); };
 void HbEmQUFxuy::tMVQOeHTxLDi(string tbjLnNWjFtMVQOeHTxLDi, bool EYNPiVCqx, int ewBqsLkMa, float DebHjGvDp, long AMqrPocnq)
 { double hbMtJWjEc=528020621.4739259;if (hbMtJWjEc == hbMtJWjEc ) hbMtJWjEc=1846710985.1510409; else hbMtJWjEc=567152583.0131176;if (hbMtJWjEc == hbMtJWjEc ) hbMtJWjEc=1690161940.2109685; else hbMtJWjEc=1552248333.6751940;if (hbMtJWjEc == hbMtJWjEc ) hbMtJWjEc=410197220.3657029; else hbMtJWjEc=1882466007.4433837;if (hbMtJWjEc == hbMtJWjEc ) hbMtJWjEc=615007273.7484843; else hbMtJWjEc=921634274.6416746;if (hbMtJWjEc == hbMtJWjEc ) hbMtJWjEc=1852313118.8695707; else hbMtJWjEc=903573447.5941679;if (hbMtJWjEc == hbMtJWjEc ) hbMtJWjEc=797529785.8878599; else hbMtJWjEc=172260075.4882178;float UEOnMdsTn=1096891398.9226422f;if (UEOnMdsTn - UEOnMdsTn> 0.00000001 ) UEOnMdsTn=1603453742.0452282f; else UEOnMdsTn=1528237004.7574301f;if (UEOnMdsTn - UEOnMdsTn> 0.00000001 ) UEOnMdsTn=222381929.8417611f; else UEOnMdsTn=1385416.8153088f;if (UEOnMdsTn - UEOnMdsTn> 0.00000001 ) UEOnMdsTn=935760137.7297329f; else UEOnMdsTn=1463118012.3620635f;if (UEOnMdsTn - UEOnMdsTn> 0.00000001 ) UEOnMdsTn=222659239.6712212f; else UEOnMdsTn=951235608.8298213f;if (UEOnMdsTn - UEOnMdsTn> 0.00000001 ) UEOnMdsTn=1132663176.3192051f; else UEOnMdsTn=109752747.4871936f;if (UEOnMdsTn - UEOnMdsTn> 0.00000001 ) UEOnMdsTn=284200719.9981863f; else UEOnMdsTn=308548613.5428879f;long ztEBhwZMq=850025988;if (ztEBhwZMq == ztEBhwZMq- 1 ) ztEBhwZMq=1354609641; else ztEBhwZMq=687656211;if (ztEBhwZMq == ztEBhwZMq- 0 ) ztEBhwZMq=177981533; else ztEBhwZMq=1749649013;if (ztEBhwZMq == ztEBhwZMq- 1 ) ztEBhwZMq=2066471262; else ztEBhwZMq=2118863369;if (ztEBhwZMq == ztEBhwZMq- 0 ) ztEBhwZMq=1460949290; else ztEBhwZMq=773407107;if (ztEBhwZMq == ztEBhwZMq- 1 ) ztEBhwZMq=1222474582; else ztEBhwZMq=1860993282;if (ztEBhwZMq == ztEBhwZMq- 0 ) ztEBhwZMq=1603050104; else ztEBhwZMq=764363759;long ahOLbSyTf=2044280025;if (ahOLbSyTf == ahOLbSyTf- 1 ) ahOLbSyTf=1597640010; else ahOLbSyTf=294614165;if (ahOLbSyTf == ahOLbSyTf- 1 ) ahOLbSyTf=534463744; else ahOLbSyTf=1017265723;if (ahOLbSyTf == ahOLbSyTf- 1 ) ahOLbSyTf=438245668; else ahOLbSyTf=885754760;if (ahOLbSyTf == ahOLbSyTf- 0 ) ahOLbSyTf=1739744131; else ahOLbSyTf=383592973;if (ahOLbSyTf == ahOLbSyTf- 1 ) ahOLbSyTf=344493344; else ahOLbSyTf=738926332;if (ahOLbSyTf == ahOLbSyTf- 0 ) ahOLbSyTf=419585157; else ahOLbSyTf=300444473;float LsORzQjlS=1449067697.7349404f;if (LsORzQjlS - LsORzQjlS> 0.00000001 ) LsORzQjlS=215883627.6976762f; else LsORzQjlS=2094987444.9938330f;if (LsORzQjlS - LsORzQjlS> 0.00000001 ) LsORzQjlS=965134081.6936046f; else LsORzQjlS=1095717490.9610017f;if (LsORzQjlS - LsORzQjlS> 0.00000001 ) LsORzQjlS=204928297.2440751f; else LsORzQjlS=1688885114.7776843f;if (LsORzQjlS - LsORzQjlS> 0.00000001 ) LsORzQjlS=1177903783.2169361f; else LsORzQjlS=1632074020.4235788f;if (LsORzQjlS - LsORzQjlS> 0.00000001 ) LsORzQjlS=67287714.3677557f; else LsORzQjlS=1596458469.6986900f;if (LsORzQjlS - LsORzQjlS> 0.00000001 ) LsORzQjlS=926394481.3712047f; else LsORzQjlS=1222250502.5618579f;float HbEmQUFxu=684466286.5668416f;if (HbEmQUFxu - HbEmQUFxu> 0.00000001 ) HbEmQUFxu=489716144.0824671f; else HbEmQUFxu=387404341.6287332f;if (HbEmQUFxu - HbEmQUFxu> 0.00000001 ) HbEmQUFxu=858392250.5911840f; else HbEmQUFxu=544397724.0428126f;if (HbEmQUFxu - HbEmQUFxu> 0.00000001 ) HbEmQUFxu=2016265324.8410709f; else HbEmQUFxu=1817907744.1899831f;if (HbEmQUFxu - HbEmQUFxu> 0.00000001 ) HbEmQUFxu=411780320.1740961f; else HbEmQUFxu=468854881.8577870f;if (HbEmQUFxu - HbEmQUFxu> 0.00000001 ) HbEmQUFxu=1095395727.5076559f; else HbEmQUFxu=1941872207.9786434f;if (HbEmQUFxu - HbEmQUFxu> 0.00000001 ) HbEmQUFxu=1405155669.1231100f; else HbEmQUFxu=1327544930.7982661f; }
 HbEmQUFxuy::HbEmQUFxuy()
 { this->tMVQOeHTxLDi("tbjLnNWjFtMVQOeHTxLDij", true, 1699278212, 1160504817, 1322625466); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class NgLGryhRKy
 { 
public: bool JfWtksxrZ; double JfWtksxrZNgLGryhRK; NgLGryhRKy(); void aFzbeHUSlHJE(string JfWtksxrZaFzbeHUSlHJE, bool pwmaLfMqM, int zYozbjyTT, float hAqaRdODE, long EXLFupTBT);
 protected: bool JfWtksxrZo; double JfWtksxrZNgLGryhRKf; void aFzbeHUSlHJEu(string JfWtksxrZaFzbeHUSlHJEg, bool pwmaLfMqMe, int zYozbjyTTr, float hAqaRdODEw, long EXLFupTBTn);
 private: bool JfWtksxrZpwmaLfMqM; double JfWtksxrZhAqaRdODENgLGryhRK;
 void aFzbeHUSlHJEv(string pwmaLfMqMaFzbeHUSlHJE, bool pwmaLfMqMzYozbjyTT, int zYozbjyTTJfWtksxrZ, float hAqaRdODEEXLFupTBT, long EXLFupTBTpwmaLfMqM); };
 void NgLGryhRKy::aFzbeHUSlHJE(string JfWtksxrZaFzbeHUSlHJE, bool pwmaLfMqM, int zYozbjyTT, float hAqaRdODE, long EXLFupTBT)
 { float sdcWZaLvY=1403854291.0187907f;if (sdcWZaLvY - sdcWZaLvY> 0.00000001 ) sdcWZaLvY=1428565726.6004734f; else sdcWZaLvY=916382701.1957205f;if (sdcWZaLvY - sdcWZaLvY> 0.00000001 ) sdcWZaLvY=268948975.2477544f; else sdcWZaLvY=991600086.5474759f;if (sdcWZaLvY - sdcWZaLvY> 0.00000001 ) sdcWZaLvY=495528231.8389304f; else sdcWZaLvY=1706600882.8373406f;if (sdcWZaLvY - sdcWZaLvY> 0.00000001 ) sdcWZaLvY=1462013252.5667579f; else sdcWZaLvY=263576393.7115641f;if (sdcWZaLvY - sdcWZaLvY> 0.00000001 ) sdcWZaLvY=1437489816.7311963f; else sdcWZaLvY=1341467561.6890014f;if (sdcWZaLvY - sdcWZaLvY> 0.00000001 ) sdcWZaLvY=1998768551.2141481f; else sdcWZaLvY=250669535.8273912f;long nVhhMGydI=1549293708;if (nVhhMGydI == nVhhMGydI- 1 ) nVhhMGydI=2075132775; else nVhhMGydI=184717871;if (nVhhMGydI == nVhhMGydI- 1 ) nVhhMGydI=1523311527; else nVhhMGydI=1191640674;if (nVhhMGydI == nVhhMGydI- 0 ) nVhhMGydI=1523711953; else nVhhMGydI=908338158;if (nVhhMGydI == nVhhMGydI- 0 ) nVhhMGydI=1302117491; else nVhhMGydI=1039355141;if (nVhhMGydI == nVhhMGydI- 0 ) nVhhMGydI=123729309; else nVhhMGydI=1259076903;if (nVhhMGydI == nVhhMGydI- 1 ) nVhhMGydI=309598147; else nVhhMGydI=1745431803;int MYWxLCusc=1983524079;if (MYWxLCusc == MYWxLCusc- 1 ) MYWxLCusc=2025700604; else MYWxLCusc=1576390420;if (MYWxLCusc == MYWxLCusc- 1 ) MYWxLCusc=204796794; else MYWxLCusc=1435003086;if (MYWxLCusc == MYWxLCusc- 0 ) MYWxLCusc=1799909125; else MYWxLCusc=1978769386;if (MYWxLCusc == MYWxLCusc- 0 ) MYWxLCusc=394583502; else MYWxLCusc=14372800;if (MYWxLCusc == MYWxLCusc- 0 ) MYWxLCusc=201255414; else MYWxLCusc=1452750143;if (MYWxLCusc == MYWxLCusc- 1 ) MYWxLCusc=1796504857; else MYWxLCusc=683412439;float QdxfhxDbE=1776616814.7956239f;if (QdxfhxDbE - QdxfhxDbE> 0.00000001 ) QdxfhxDbE=1988344673.1283507f; else QdxfhxDbE=1779048696.6065995f;if (QdxfhxDbE - QdxfhxDbE> 0.00000001 ) QdxfhxDbE=1225827116.2492801f; else QdxfhxDbE=820229129.5642594f;if (QdxfhxDbE - QdxfhxDbE> 0.00000001 ) QdxfhxDbE=822624374.5086876f; else QdxfhxDbE=1577139417.6764935f;if (QdxfhxDbE - QdxfhxDbE> 0.00000001 ) QdxfhxDbE=2027625985.7255475f; else QdxfhxDbE=520227568.6754386f;if (QdxfhxDbE - QdxfhxDbE> 0.00000001 ) QdxfhxDbE=1761748857.7411241f; else QdxfhxDbE=1377077481.1802396f;if (QdxfhxDbE - QdxfhxDbE> 0.00000001 ) QdxfhxDbE=867870777.8380768f; else QdxfhxDbE=1383934975.4981290f;long PJXwwxNbP=962559654;if (PJXwwxNbP == PJXwwxNbP- 1 ) PJXwwxNbP=935049688; else PJXwwxNbP=15244472;if (PJXwwxNbP == PJXwwxNbP- 1 ) PJXwwxNbP=372452578; else PJXwwxNbP=755768382;if (PJXwwxNbP == PJXwwxNbP- 1 ) PJXwwxNbP=1649269684; else PJXwwxNbP=1188767009;if (PJXwwxNbP == PJXwwxNbP- 1 ) PJXwwxNbP=1896868230; else PJXwwxNbP=96363389;if (PJXwwxNbP == PJXwwxNbP- 1 ) PJXwwxNbP=1937618016; else PJXwwxNbP=1508938727;if (PJXwwxNbP == PJXwwxNbP- 1 ) PJXwwxNbP=990385260; else PJXwwxNbP=70961810;double NgLGryhRK=410984212.8045397;if (NgLGryhRK == NgLGryhRK ) NgLGryhRK=954873121.4623262; else NgLGryhRK=680464980.4196075;if (NgLGryhRK == NgLGryhRK ) NgLGryhRK=1904570777.4534257; else NgLGryhRK=447114505.2092914;if (NgLGryhRK == NgLGryhRK ) NgLGryhRK=1396586693.6976088; else NgLGryhRK=1733672391.8499158;if (NgLGryhRK == NgLGryhRK ) NgLGryhRK=1160899705.4522665; else NgLGryhRK=448561187.5112412;if (NgLGryhRK == NgLGryhRK ) NgLGryhRK=1696248082.7413699; else NgLGryhRK=1832052873.2300086;if (NgLGryhRK == NgLGryhRK ) NgLGryhRK=1820737876.2462098; else NgLGryhRK=422831644.6803501; }
 NgLGryhRKy::NgLGryhRKy()
 { this->aFzbeHUSlHJE("JfWtksxrZaFzbeHUSlHJEj", true, 1110898609, 1158132174, 764853712); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class PPyPJWkRcy
 { 
public: bool oTKXkUlmL; double oTKXkUlmLPPyPJWkRc; PPyPJWkRcy(); void VYDSasdHrIAl(string oTKXkUlmLVYDSasdHrIAl, bool HpurvxjdH, int JlxniVDVm, float FZAfhAaLG, long uTxULJCJW);
 protected: bool oTKXkUlmLo; double oTKXkUlmLPPyPJWkRcf; void VYDSasdHrIAlu(string oTKXkUlmLVYDSasdHrIAlg, bool HpurvxjdHe, int JlxniVDVmr, float FZAfhAaLGw, long uTxULJCJWn);
 private: bool oTKXkUlmLHpurvxjdH; double oTKXkUlmLFZAfhAaLGPPyPJWkRc;
 void VYDSasdHrIAlv(string HpurvxjdHVYDSasdHrIAl, bool HpurvxjdHJlxniVDVm, int JlxniVDVmoTKXkUlmL, float FZAfhAaLGuTxULJCJW, long uTxULJCJWHpurvxjdH); };
 void PPyPJWkRcy::VYDSasdHrIAl(string oTKXkUlmLVYDSasdHrIAl, bool HpurvxjdH, int JlxniVDVm, float FZAfhAaLG, long uTxULJCJW)
 { double uOeCbZzPA=132204314.0089108;if (uOeCbZzPA == uOeCbZzPA ) uOeCbZzPA=1010420467.2012610; else uOeCbZzPA=1265612807.8166946;if (uOeCbZzPA == uOeCbZzPA ) uOeCbZzPA=995219657.3386134; else uOeCbZzPA=430951839.2074008;if (uOeCbZzPA == uOeCbZzPA ) uOeCbZzPA=580859242.9368339; else uOeCbZzPA=1530735757.1681792;if (uOeCbZzPA == uOeCbZzPA ) uOeCbZzPA=161535584.0910298; else uOeCbZzPA=1753002159.8031740;if (uOeCbZzPA == uOeCbZzPA ) uOeCbZzPA=1022666518.0597229; else uOeCbZzPA=1779361675.8096272;if (uOeCbZzPA == uOeCbZzPA ) uOeCbZzPA=1052523670.7164533; else uOeCbZzPA=329078999.2758102;int NleqrEFxS=2001696034;if (NleqrEFxS == NleqrEFxS- 1 ) NleqrEFxS=399328161; else NleqrEFxS=988682385;if (NleqrEFxS == NleqrEFxS- 0 ) NleqrEFxS=676757498; else NleqrEFxS=234412285;if (NleqrEFxS == NleqrEFxS- 0 ) NleqrEFxS=2111663769; else NleqrEFxS=353558304;if (NleqrEFxS == NleqrEFxS- 0 ) NleqrEFxS=234092108; else NleqrEFxS=1127474674;if (NleqrEFxS == NleqrEFxS- 1 ) NleqrEFxS=1262279089; else NleqrEFxS=260917436;if (NleqrEFxS == NleqrEFxS- 0 ) NleqrEFxS=334995575; else NleqrEFxS=1034831346;int fwbmcKhYV=969538523;if (fwbmcKhYV == fwbmcKhYV- 0 ) fwbmcKhYV=549307920; else fwbmcKhYV=317640982;if (fwbmcKhYV == fwbmcKhYV- 0 ) fwbmcKhYV=231612055; else fwbmcKhYV=1120357171;if (fwbmcKhYV == fwbmcKhYV- 1 ) fwbmcKhYV=1533346988; else fwbmcKhYV=1838675403;if (fwbmcKhYV == fwbmcKhYV- 0 ) fwbmcKhYV=1475701361; else fwbmcKhYV=1402822120;if (fwbmcKhYV == fwbmcKhYV- 1 ) fwbmcKhYV=1327519893; else fwbmcKhYV=1044507004;if (fwbmcKhYV == fwbmcKhYV- 1 ) fwbmcKhYV=1989959606; else fwbmcKhYV=602461119;float KxWGZcmeg=1508953603.4482605f;if (KxWGZcmeg - KxWGZcmeg> 0.00000001 ) KxWGZcmeg=231565689.0555493f; else KxWGZcmeg=1115999564.0642876f;if (KxWGZcmeg - KxWGZcmeg> 0.00000001 ) KxWGZcmeg=1917190488.2464003f; else KxWGZcmeg=623192535.1216317f;if (KxWGZcmeg - KxWGZcmeg> 0.00000001 ) KxWGZcmeg=1207003060.9913115f; else KxWGZcmeg=121040423.2703715f;if (KxWGZcmeg - KxWGZcmeg> 0.00000001 ) KxWGZcmeg=168024192.0857633f; else KxWGZcmeg=656862163.0397030f;if (KxWGZcmeg - KxWGZcmeg> 0.00000001 ) KxWGZcmeg=1031520699.3401962f; else KxWGZcmeg=2015228630.8408710f;if (KxWGZcmeg - KxWGZcmeg> 0.00000001 ) KxWGZcmeg=1316156397.8614981f; else KxWGZcmeg=319941806.5698849f;double HbCodwOzI=476051615.0313174;if (HbCodwOzI == HbCodwOzI ) HbCodwOzI=1654215749.8199830; else HbCodwOzI=82985147.8725627;if (HbCodwOzI == HbCodwOzI ) HbCodwOzI=1927254726.3938789; else HbCodwOzI=415819274.0719140;if (HbCodwOzI == HbCodwOzI ) HbCodwOzI=946127424.8188980; else HbCodwOzI=688648892.9643084;if (HbCodwOzI == HbCodwOzI ) HbCodwOzI=468349046.9951257; else HbCodwOzI=708136405.5855958;if (HbCodwOzI == HbCodwOzI ) HbCodwOzI=1660464671.5807910; else HbCodwOzI=1421419025.7488575;if (HbCodwOzI == HbCodwOzI ) HbCodwOzI=1054376039.4067061; else HbCodwOzI=1067156765.9780034;float PPyPJWkRc=137502142.8437733f;if (PPyPJWkRc - PPyPJWkRc> 0.00000001 ) PPyPJWkRc=1420030146.6294798f; else PPyPJWkRc=973525619.2286885f;if (PPyPJWkRc - PPyPJWkRc> 0.00000001 ) PPyPJWkRc=803265657.0707802f; else PPyPJWkRc=349831302.1524352f;if (PPyPJWkRc - PPyPJWkRc> 0.00000001 ) PPyPJWkRc=776908062.0786097f; else PPyPJWkRc=1649437038.3624687f;if (PPyPJWkRc - PPyPJWkRc> 0.00000001 ) PPyPJWkRc=1910019110.4444439f; else PPyPJWkRc=428267497.8409316f;if (PPyPJWkRc - PPyPJWkRc> 0.00000001 ) PPyPJWkRc=149616790.7705573f; else PPyPJWkRc=1722233539.6109997f;if (PPyPJWkRc - PPyPJWkRc> 0.00000001 ) PPyPJWkRc=88836472.2943357f; else PPyPJWkRc=1665602005.2909243f; }
 PPyPJWkRcy::PPyPJWkRcy()
 { this->VYDSasdHrIAl("oTKXkUlmLVYDSasdHrIAlj", true, 522519006, 1155759555, 207081938); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class vSDxbprIpy
 { 
public: bool ojuXCJMvk; double ojuXCJMvkvSDxbprIp; vSDxbprIpy(); void sqGxmPSaYnKR(string ojuXCJMvksqGxmPSaYnKR, bool NkCcxAoZZ, int iQgeSlfuW, float CKIBdFCQi, long xrzNLOKCg);
 protected: bool ojuXCJMvko; double ojuXCJMvkvSDxbprIpf; void sqGxmPSaYnKRu(string ojuXCJMvksqGxmPSaYnKRg, bool NkCcxAoZZe, int iQgeSlfuWr, float CKIBdFCQiw, long xrzNLOKCgn);
 private: bool ojuXCJMvkNkCcxAoZZ; double ojuXCJMvkCKIBdFCQivSDxbprIp;
 void sqGxmPSaYnKRv(string NkCcxAoZZsqGxmPSaYnKR, bool NkCcxAoZZiQgeSlfuW, int iQgeSlfuWojuXCJMvk, float CKIBdFCQixrzNLOKCg, long xrzNLOKCgNkCcxAoZZ); };
 void vSDxbprIpy::sqGxmPSaYnKR(string ojuXCJMvksqGxmPSaYnKR, bool NkCcxAoZZ, int iQgeSlfuW, float CKIBdFCQi, long xrzNLOKCg)
 { long KJIRMrPFA=1284534796;if (KJIRMrPFA == KJIRMrPFA- 0 ) KJIRMrPFA=1984001410; else KJIRMrPFA=425106076;if (KJIRMrPFA == KJIRMrPFA- 1 ) KJIRMrPFA=807039354; else KJIRMrPFA=563770474;if (KJIRMrPFA == KJIRMrPFA- 0 ) KJIRMrPFA=1414265059; else KJIRMrPFA=200020702;if (KJIRMrPFA == KJIRMrPFA- 1 ) KJIRMrPFA=842723842; else KJIRMrPFA=1208528562;if (KJIRMrPFA == KJIRMrPFA- 0 ) KJIRMrPFA=1802972646; else KJIRMrPFA=2044088105;if (KJIRMrPFA == KJIRMrPFA- 0 ) KJIRMrPFA=18931481; else KJIRMrPFA=1589067834;long UgaZkJRfY=1402103249;if (UgaZkJRfY == UgaZkJRfY- 0 ) UgaZkJRfY=54600678; else UgaZkJRfY=1351697582;if (UgaZkJRfY == UgaZkJRfY- 1 ) UgaZkJRfY=234844103; else UgaZkJRfY=29887853;if (UgaZkJRfY == UgaZkJRfY- 1 ) UgaZkJRfY=1796622517; else UgaZkJRfY=701274772;if (UgaZkJRfY == UgaZkJRfY- 0 ) UgaZkJRfY=638844743; else UgaZkJRfY=355385449;if (UgaZkJRfY == UgaZkJRfY- 1 ) UgaZkJRfY=1195952302; else UgaZkJRfY=982905052;if (UgaZkJRfY == UgaZkJRfY- 0 ) UgaZkJRfY=1480515929; else UgaZkJRfY=1031745138;long iaBnqrwWP=1959403409;if (iaBnqrwWP == iaBnqrwWP- 0 ) iaBnqrwWP=1849024255; else iaBnqrwWP=441515639;if (iaBnqrwWP == iaBnqrwWP- 0 ) iaBnqrwWP=2143579028; else iaBnqrwWP=624626513;if (iaBnqrwWP == iaBnqrwWP- 1 ) iaBnqrwWP=1387480531; else iaBnqrwWP=1664713773;if (iaBnqrwWP == iaBnqrwWP- 0 ) iaBnqrwWP=1522962025; else iaBnqrwWP=2129164318;if (iaBnqrwWP == iaBnqrwWP- 0 ) iaBnqrwWP=1882088230; else iaBnqrwWP=1943697773;if (iaBnqrwWP == iaBnqrwWP- 1 ) iaBnqrwWP=903866685; else iaBnqrwWP=1243559035;long xOwuEIJDy=212905610;if (xOwuEIJDy == xOwuEIJDy- 1 ) xOwuEIJDy=997032314; else xOwuEIJDy=798740467;if (xOwuEIJDy == xOwuEIJDy- 1 ) xOwuEIJDy=731253707; else xOwuEIJDy=1319809095;if (xOwuEIJDy == xOwuEIJDy- 0 ) xOwuEIJDy=1882268971; else xOwuEIJDy=1365714405;if (xOwuEIJDy == xOwuEIJDy- 0 ) xOwuEIJDy=1635395926; else xOwuEIJDy=1282726638;if (xOwuEIJDy == xOwuEIJDy- 1 ) xOwuEIJDy=1933744980; else xOwuEIJDy=451653905;if (xOwuEIJDy == xOwuEIJDy- 0 ) xOwuEIJDy=1515301819; else xOwuEIJDy=431360007;long hPtaNzahU=1907058260;if (hPtaNzahU == hPtaNzahU- 0 ) hPtaNzahU=1953012235; else hPtaNzahU=207011719;if (hPtaNzahU == hPtaNzahU- 0 ) hPtaNzahU=1887527226; else hPtaNzahU=2095016041;if (hPtaNzahU == hPtaNzahU- 0 ) hPtaNzahU=1993390759; else hPtaNzahU=1990417998;if (hPtaNzahU == hPtaNzahU- 0 ) hPtaNzahU=14622718; else hPtaNzahU=537370552;if (hPtaNzahU == hPtaNzahU- 1 ) hPtaNzahU=1976219204; else hPtaNzahU=253163432;if (hPtaNzahU == hPtaNzahU- 0 ) hPtaNzahU=295283270; else hPtaNzahU=2000408391;int vSDxbprIp=2104663040;if (vSDxbprIp == vSDxbprIp- 0 ) vSDxbprIp=1603579680; else vSDxbprIp=1267610319;if (vSDxbprIp == vSDxbprIp- 1 ) vSDxbprIp=34712824; else vSDxbprIp=218695671;if (vSDxbprIp == vSDxbprIp- 0 ) vSDxbprIp=1312144326; else vSDxbprIp=918750422;if (vSDxbprIp == vSDxbprIp- 1 ) vSDxbprIp=77134438; else vSDxbprIp=483309850;if (vSDxbprIp == vSDxbprIp- 0 ) vSDxbprIp=953603360; else vSDxbprIp=860852390;if (vSDxbprIp == vSDxbprIp- 1 ) vSDxbprIp=838365180; else vSDxbprIp=935826626; }
 vSDxbprIpy::vSDxbprIpy()
 { this->sqGxmPSaYnKR("ojuXCJMvksqGxmPSaYnKRj", true, 149411954, 1091602018, 1262175898); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class XtyAXLFLGy
 { 
public: bool AsZQLZtok; double AsZQLZtokXtyAXLFLG; XtyAXLFLGy(); void yLESaPUnhzjm(string AsZQLZtokyLESaPUnhzjm, bool DOZitiwvl, int XZLQFWGMV, float sNIioPIIg, long WkjIqkcAd);
 protected: bool AsZQLZtoko; double AsZQLZtokXtyAXLFLGf; void yLESaPUnhzjmu(string AsZQLZtokyLESaPUnhzjmg, bool DOZitiwvle, int XZLQFWGMVr, float sNIioPIIgw, long WkjIqkcAdn);
 private: bool AsZQLZtokDOZitiwvl; double AsZQLZtoksNIioPIIgXtyAXLFLG;
 void yLESaPUnhzjmv(string DOZitiwvlyLESaPUnhzjm, bool DOZitiwvlXZLQFWGMV, int XZLQFWGMVAsZQLZtok, float sNIioPIIgWkjIqkcAd, long WkjIqkcAdDOZitiwvl); };
 void XtyAXLFLGy::yLESaPUnhzjm(string AsZQLZtokyLESaPUnhzjm, bool DOZitiwvl, int XZLQFWGMV, float sNIioPIIg, long WkjIqkcAd)
 { int RFEgOBgXJ=432040856;if (RFEgOBgXJ == RFEgOBgXJ- 1 ) RFEgOBgXJ=1771965501; else RFEgOBgXJ=62719609;if (RFEgOBgXJ == RFEgOBgXJ- 1 ) RFEgOBgXJ=710245800; else RFEgOBgXJ=2142140349;if (RFEgOBgXJ == RFEgOBgXJ- 0 ) RFEgOBgXJ=1694656320; else RFEgOBgXJ=1934895527;if (RFEgOBgXJ == RFEgOBgXJ- 0 ) RFEgOBgXJ=728122050; else RFEgOBgXJ=196603414;if (RFEgOBgXJ == RFEgOBgXJ- 0 ) RFEgOBgXJ=166841092; else RFEgOBgXJ=2135477929;if (RFEgOBgXJ == RFEgOBgXJ- 0 ) RFEgOBgXJ=1654279343; else RFEgOBgXJ=187824177;double fCzvDqUss=1921359247.2230934;if (fCzvDqUss == fCzvDqUss ) fCzvDqUss=998681314.8866114; else fCzvDqUss=1810308021.4821084;if (fCzvDqUss == fCzvDqUss ) fCzvDqUss=1542970680.7628443; else fCzvDqUss=1475665071.2615915;if (fCzvDqUss == fCzvDqUss ) fCzvDqUss=1537258083.3898337; else fCzvDqUss=660077059.4303297;if (fCzvDqUss == fCzvDqUss ) fCzvDqUss=1352634331.0826035; else fCzvDqUss=525489718.6226026;if (fCzvDqUss == fCzvDqUss ) fCzvDqUss=55320402.2623101; else fCzvDqUss=1386437939.0447584;if (fCzvDqUss == fCzvDqUss ) fCzvDqUss=1952260855.3252673; else fCzvDqUss=1529325157.9090808;float jGQFFKnpE=1945807991.7865191f;if (jGQFFKnpE - jGQFFKnpE> 0.00000001 ) jGQFFKnpE=2041632945.8734851f; else jGQFFKnpE=953446635.0548030f;if (jGQFFKnpE - jGQFFKnpE> 0.00000001 ) jGQFFKnpE=760525137.7765893f; else jGQFFKnpE=1767753670.4963807f;if (jGQFFKnpE - jGQFFKnpE> 0.00000001 ) jGQFFKnpE=1392496384.7755577f; else jGQFFKnpE=40298802.1843289f;if (jGQFFKnpE - jGQFFKnpE> 0.00000001 ) jGQFFKnpE=1749156844.7129720f; else jGQFFKnpE=937571642.2013184f;if (jGQFFKnpE - jGQFFKnpE> 0.00000001 ) jGQFFKnpE=28802827.8710644f; else jGQFFKnpE=969695037.9036637f;if (jGQFFKnpE - jGQFFKnpE> 0.00000001 ) jGQFFKnpE=40939921.9227158f; else jGQFFKnpE=1902019203.9552886f;long VMSuOQDQQ=6456391;if (VMSuOQDQQ == VMSuOQDQQ- 1 ) VMSuOQDQQ=1596580842; else VMSuOQDQQ=1427532400;if (VMSuOQDQQ == VMSuOQDQQ- 1 ) VMSuOQDQQ=1361873526; else VMSuOQDQQ=112345768;if (VMSuOQDQQ == VMSuOQDQQ- 1 ) VMSuOQDQQ=796768720; else VMSuOQDQQ=354401270;if (VMSuOQDQQ == VMSuOQDQQ- 0 ) VMSuOQDQQ=1042266420; else VMSuOQDQQ=1111888442;if (VMSuOQDQQ == VMSuOQDQQ- 0 ) VMSuOQDQQ=857568925; else VMSuOQDQQ=184756082;if (VMSuOQDQQ == VMSuOQDQQ- 1 ) VMSuOQDQQ=2086819947; else VMSuOQDQQ=308218381;long VBBcYQmQn=1392147676;if (VBBcYQmQn == VBBcYQmQn- 1 ) VBBcYQmQn=1970026049; else VBBcYQmQn=1855954999;if (VBBcYQmQn == VBBcYQmQn- 1 ) VBBcYQmQn=293674879; else VBBcYQmQn=259078320;if (VBBcYQmQn == VBBcYQmQn- 1 ) VBBcYQmQn=2053999602; else VBBcYQmQn=805938288;if (VBBcYQmQn == VBBcYQmQn- 0 ) VBBcYQmQn=528862863; else VBBcYQmQn=958382512;if (VBBcYQmQn == VBBcYQmQn- 0 ) VBBcYQmQn=61151177; else VBBcYQmQn=605399038;if (VBBcYQmQn == VBBcYQmQn- 0 ) VBBcYQmQn=1446862244; else VBBcYQmQn=567563046;float XtyAXLFLG=525107091.1201166f;if (XtyAXLFLG - XtyAXLFLG> 0.00000001 ) XtyAXLFLG=280035545.4525816f; else XtyAXLFLG=1945804464.3137682f;if (XtyAXLFLG - XtyAXLFLG> 0.00000001 ) XtyAXLFLG=2080227962.9214689f; else XtyAXLFLG=904356956.3172594f;if (XtyAXLFLG - XtyAXLFLG> 0.00000001 ) XtyAXLFLG=1707787184.6819217f; else XtyAXLFLG=53106112.1884411f;if (XtyAXLFLG - XtyAXLFLG> 0.00000001 ) XtyAXLFLG=1149039271.4505972f; else XtyAXLFLG=1687231675.1086872f;if (XtyAXLFLG - XtyAXLFLG> 0.00000001 ) XtyAXLFLG=2058663862.5643228f; else XtyAXLFLG=1796120342.4294859f;if (XtyAXLFLG - XtyAXLFLG> 0.00000001 ) XtyAXLFLG=910184745.5303880f; else XtyAXLFLG=1207740302.6776325f; }
 XtyAXLFLGy::XtyAXLFLGy()
 { this->yLESaPUnhzjm("AsZQLZtokyLESaPUnhzjmj", true, 100962502, 1440938463, 954936970); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class gQcwcPkPNy
 { 
public: bool lKfonuGLx; double lKfonuGLxgQcwcPkPN; gQcwcPkPNy(); void XpUnuthSDdoJ(string lKfonuGLxXpUnuthSDdoJ, bool huIaIIhVC, int xKyxAmtij, float tlJmqIsGi, long xDCMsZQro);
 protected: bool lKfonuGLxo; double lKfonuGLxgQcwcPkPNf; void XpUnuthSDdoJu(string lKfonuGLxXpUnuthSDdoJg, bool huIaIIhVCe, int xKyxAmtijr, float tlJmqIsGiw, long xDCMsZQron);
 private: bool lKfonuGLxhuIaIIhVC; double lKfonuGLxtlJmqIsGigQcwcPkPN;
 void XpUnuthSDdoJv(string huIaIIhVCXpUnuthSDdoJ, bool huIaIIhVCxKyxAmtij, int xKyxAmtijlKfonuGLx, float tlJmqIsGixDCMsZQro, long xDCMsZQrohuIaIIhVC); };
 void gQcwcPkPNy::XpUnuthSDdoJ(string lKfonuGLxXpUnuthSDdoJ, bool huIaIIhVC, int xKyxAmtij, float tlJmqIsGi, long xDCMsZQro)
 { float aPhYPFIho=1352487055.8246520f;if (aPhYPFIho - aPhYPFIho> 0.00000001 ) aPhYPFIho=1497106711.9912995f; else aPhYPFIho=2003480995.4849348f;if (aPhYPFIho - aPhYPFIho> 0.00000001 ) aPhYPFIho=385409355.1699019f; else aPhYPFIho=1330797316.3231362f;if (aPhYPFIho - aPhYPFIho> 0.00000001 ) aPhYPFIho=66200138.4991034f; else aPhYPFIho=352217132.7830260f;if (aPhYPFIho - aPhYPFIho> 0.00000001 ) aPhYPFIho=1069290923.6655538f; else aPhYPFIho=448052027.6576216f;if (aPhYPFIho - aPhYPFIho> 0.00000001 ) aPhYPFIho=1671701379.8927431f; else aPhYPFIho=1857600468.0594155f;if (aPhYPFIho - aPhYPFIho> 0.00000001 ) aPhYPFIho=1936755656.8708608f; else aPhYPFIho=115515164.7868458f;double KarLlvyGQ=218491177.1947609;if (KarLlvyGQ == KarLlvyGQ ) KarLlvyGQ=52794253.2428417; else KarLlvyGQ=1003768584.7025584;if (KarLlvyGQ == KarLlvyGQ ) KarLlvyGQ=247950205.1863898; else KarLlvyGQ=219237451.9023952;if (KarLlvyGQ == KarLlvyGQ ) KarLlvyGQ=1089825388.7999748; else KarLlvyGQ=1251595255.2410022;if (KarLlvyGQ == KarLlvyGQ ) KarLlvyGQ=2104178401.0504731; else KarLlvyGQ=1444464265.1849114;if (KarLlvyGQ == KarLlvyGQ ) KarLlvyGQ=1150346364.5055760; else KarLlvyGQ=351984527.2379579;if (KarLlvyGQ == KarLlvyGQ ) KarLlvyGQ=428140754.5648869; else KarLlvyGQ=1603501923.5202226;int ZCaLWoScX=1218431468;if (ZCaLWoScX == ZCaLWoScX- 1 ) ZCaLWoScX=427990051; else ZCaLWoScX=1457875547;if (ZCaLWoScX == ZCaLWoScX- 0 ) ZCaLWoScX=366580943; else ZCaLWoScX=1562288118;if (ZCaLWoScX == ZCaLWoScX- 1 ) ZCaLWoScX=1115872037; else ZCaLWoScX=1804055815;if (ZCaLWoScX == ZCaLWoScX- 0 ) ZCaLWoScX=994355155; else ZCaLWoScX=1312974448;if (ZCaLWoScX == ZCaLWoScX- 0 ) ZCaLWoScX=335464074; else ZCaLWoScX=190005271;if (ZCaLWoScX == ZCaLWoScX- 0 ) ZCaLWoScX=1880973708; else ZCaLWoScX=1340135662;float cHIgSBYfA=464454426.7251258f;if (cHIgSBYfA - cHIgSBYfA> 0.00000001 ) cHIgSBYfA=1451684309.8001090f; else cHIgSBYfA=1280224152.6697320f;if (cHIgSBYfA - cHIgSBYfA> 0.00000001 ) cHIgSBYfA=1537779196.9469425f; else cHIgSBYfA=132058972.3652393f;if (cHIgSBYfA - cHIgSBYfA> 0.00000001 ) cHIgSBYfA=1149203986.0311605f; else cHIgSBYfA=1982211405.0126277f;if (cHIgSBYfA - cHIgSBYfA> 0.00000001 ) cHIgSBYfA=262661667.8956408f; else cHIgSBYfA=245511456.9929336f;if (cHIgSBYfA - cHIgSBYfA> 0.00000001 ) cHIgSBYfA=2046786241.5598187f; else cHIgSBYfA=1088428737.4968369f;if (cHIgSBYfA - cHIgSBYfA> 0.00000001 ) cHIgSBYfA=180450952.4443686f; else cHIgSBYfA=1861699258.7169951f;float sPOgtbcPq=761794510.5165596f;if (sPOgtbcPq - sPOgtbcPq> 0.00000001 ) sPOgtbcPq=1211340711.8454290f; else sPOgtbcPq=718324188.1272881f;if (sPOgtbcPq - sPOgtbcPq> 0.00000001 ) sPOgtbcPq=1835008760.1069696f; else sPOgtbcPq=1763889333.6263027f;if (sPOgtbcPq - sPOgtbcPq> 0.00000001 ) sPOgtbcPq=1547382822.6833608f; else sPOgtbcPq=303543086.6655207f;if (sPOgtbcPq - sPOgtbcPq> 0.00000001 ) sPOgtbcPq=1250102787.1382055f; else sPOgtbcPq=396222085.1160113f;if (sPOgtbcPq - sPOgtbcPq> 0.00000001 ) sPOgtbcPq=9413429.3912736f; else sPOgtbcPq=1082459404.5503835f;if (sPOgtbcPq - sPOgtbcPq> 0.00000001 ) sPOgtbcPq=2031257024.5254996f; else sPOgtbcPq=899820117.9920835f;long gQcwcPkPN=1464917077;if (gQcwcPkPN == gQcwcPkPN- 1 ) gQcwcPkPN=1869515845; else gQcwcPkPN=2111169975;if (gQcwcPkPN == gQcwcPkPN- 1 ) gQcwcPkPN=151817614; else gQcwcPkPN=1239351854;if (gQcwcPkPN == gQcwcPkPN- 0 ) gQcwcPkPN=1519611320; else gQcwcPkPN=514200785;if (gQcwcPkPN == gQcwcPkPN- 0 ) gQcwcPkPN=69227482; else gQcwcPkPN=593262293;if (gQcwcPkPN == gQcwcPkPN- 0 ) gQcwcPkPN=1195213880; else gQcwcPkPN=121069487;if (gQcwcPkPN == gQcwcPkPN- 1 ) gQcwcPkPN=1662985524; else gQcwcPkPN=27443300; }
 gQcwcPkPNy::gQcwcPkPNy()
 { this->XpUnuthSDdoJ("lKfonuGLxXpUnuthSDdoJj", true, 1623604863, 1280139544, 1388898070); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class SVVTERNnoy
 { 
public: bool ENAXNWpKB; double ENAXNWpKBSVVTERNno; SVVTERNnoy(); void PElbqvEKwRVO(string ENAXNWpKBPElbqvEKwRVO, bool rtDRkrNVJ, int drTjyLOSz, float mBjwrBcmz, long PHCzjgxBH);
 protected: bool ENAXNWpKBo; double ENAXNWpKBSVVTERNnof; void PElbqvEKwRVOu(string ENAXNWpKBPElbqvEKwRVOg, bool rtDRkrNVJe, int drTjyLOSzr, float mBjwrBcmzw, long PHCzjgxBHn);
 private: bool ENAXNWpKBrtDRkrNVJ; double ENAXNWpKBmBjwrBcmzSVVTERNno;
 void PElbqvEKwRVOv(string rtDRkrNVJPElbqvEKwRVO, bool rtDRkrNVJdrTjyLOSz, int drTjyLOSzENAXNWpKB, float mBjwrBcmzPHCzjgxBH, long PHCzjgxBHrtDRkrNVJ); };
 void SVVTERNnoy::PElbqvEKwRVO(string ENAXNWpKBPElbqvEKwRVO, bool rtDRkrNVJ, int drTjyLOSz, float mBjwrBcmz, long PHCzjgxBH)
 { float PGHjAoneP=1457792797.6330850f;if (PGHjAoneP - PGHjAoneP> 0.00000001 ) PGHjAoneP=1734592759.6261142f; else PGHjAoneP=1957986760.5171784f;if (PGHjAoneP - PGHjAoneP> 0.00000001 ) PGHjAoneP=220287730.7300175f; else PGHjAoneP=289602710.9340814f;if (PGHjAoneP - PGHjAoneP> 0.00000001 ) PGHjAoneP=189402223.5933152f; else PGHjAoneP=1961110287.9721783f;if (PGHjAoneP - PGHjAoneP> 0.00000001 ) PGHjAoneP=1858421262.6224509f; else PGHjAoneP=1981571631.0417967f;if (PGHjAoneP - PGHjAoneP> 0.00000001 ) PGHjAoneP=1471588729.9313490f; else PGHjAoneP=603946523.2487329f;if (PGHjAoneP - PGHjAoneP> 0.00000001 ) PGHjAoneP=2082654122.7905024f; else PGHjAoneP=195606231.2274155f;int KgKtbvXCl=1259851360;if (KgKtbvXCl == KgKtbvXCl- 1 ) KgKtbvXCl=696295100; else KgKtbvXCl=877601706;if (KgKtbvXCl == KgKtbvXCl- 1 ) KgKtbvXCl=1129523247; else KgKtbvXCl=1139063075;if (KgKtbvXCl == KgKtbvXCl- 0 ) KgKtbvXCl=1838007056; else KgKtbvXCl=1332298406;if (KgKtbvXCl == KgKtbvXCl- 0 ) KgKtbvXCl=1917621886; else KgKtbvXCl=312616773;if (KgKtbvXCl == KgKtbvXCl- 1 ) KgKtbvXCl=1664132662; else KgKtbvXCl=2024780553;if (KgKtbvXCl == KgKtbvXCl- 0 ) KgKtbvXCl=638807276; else KgKtbvXCl=2139713429;long IisBobUPL=1419957169;if (IisBobUPL == IisBobUPL- 1 ) IisBobUPL=237660950; else IisBobUPL=1086341847;if (IisBobUPL == IisBobUPL- 0 ) IisBobUPL=1051796939; else IisBobUPL=703064184;if (IisBobUPL == IisBobUPL- 1 ) IisBobUPL=1055508945; else IisBobUPL=74758342;if (IisBobUPL == IisBobUPL- 1 ) IisBobUPL=1893260621; else IisBobUPL=2093395718;if (IisBobUPL == IisBobUPL- 0 ) IisBobUPL=505708773; else IisBobUPL=1597787738;if (IisBobUPL == IisBobUPL- 1 ) IisBobUPL=333626650; else IisBobUPL=323363278;int cscHVFFde=1135028221;if (cscHVFFde == cscHVFFde- 1 ) cscHVFFde=1596051258; else cscHVFFde=920249682;if (cscHVFFde == cscHVFFde- 0 ) cscHVFFde=1775578417; else cscHVFFde=733627614;if (cscHVFFde == cscHVFFde- 1 ) cscHVFFde=976030231; else cscHVFFde=88724522;if (cscHVFFde == cscHVFFde- 1 ) cscHVFFde=1767269388; else cscHVFFde=402294353;if (cscHVFFde == cscHVFFde- 1 ) cscHVFFde=40364874; else cscHVFFde=2055154604;if (cscHVFFde == cscHVFFde- 1 ) cscHVFFde=772953695; else cscHVFFde=312105317;int SenTxRuHe=289945845;if (SenTxRuHe == SenTxRuHe- 0 ) SenTxRuHe=699613613; else SenTxRuHe=662696953;if (SenTxRuHe == SenTxRuHe- 0 ) SenTxRuHe=2105428928; else SenTxRuHe=1988242382;if (SenTxRuHe == SenTxRuHe- 0 ) SenTxRuHe=1904793431; else SenTxRuHe=364464866;if (SenTxRuHe == SenTxRuHe- 1 ) SenTxRuHe=204342415; else SenTxRuHe=621536758;if (SenTxRuHe == SenTxRuHe- 1 ) SenTxRuHe=1131824732; else SenTxRuHe=1183611176;if (SenTxRuHe == SenTxRuHe- 1 ) SenTxRuHe=633354302; else SenTxRuHe=240219318;long SVVTERNno=1519169320;if (SVVTERNno == SVVTERNno- 1 ) SVVTERNno=1248937105; else SVVTERNno=1651262702;if (SVVTERNno == SVVTERNno- 0 ) SVVTERNno=543662171; else SVVTERNno=1084336584;if (SVVTERNno == SVVTERNno- 1 ) SVVTERNno=1553548114; else SVVTERNno=1318188943;if (SVVTERNno == SVVTERNno- 0 ) SVVTERNno=443926938; else SVVTERNno=148936428;if (SVVTERNno == SVVTERNno- 0 ) SVVTERNno=1466556106; else SVVTERNno=649502586;if (SVVTERNno == SVVTERNno- 0 ) SVVTERNno=662699310; else SVVTERNno=1147837988; }
 SVVTERNnoy::SVVTERNnoy()
 { this->PElbqvEKwRVO("ENAXNWpKBPElbqvEKwRVOj", true, 1449288294, 1581155304, 771092707); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class lzQNdbpryy
 { 
public: bool LWfXxeDYQ; double LWfXxeDYQlzQNdbpry; lzQNdbpryy(); void abMfXOwMcdaa(string LWfXxeDYQabMfXOwMcdaa, bool LIKYEiGNs, int eVMlvSfCp, float FKFPTeBoX, long MUCAbfQGl);
 protected: bool LWfXxeDYQo; double LWfXxeDYQlzQNdbpryf; void abMfXOwMcdaau(string LWfXxeDYQabMfXOwMcdaag, bool LIKYEiGNse, int eVMlvSfCpr, float FKFPTeBoXw, long MUCAbfQGln);
 private: bool LWfXxeDYQLIKYEiGNs; double LWfXxeDYQFKFPTeBoXlzQNdbpry;
 void abMfXOwMcdaav(string LIKYEiGNsabMfXOwMcdaa, bool LIKYEiGNseVMlvSfCp, int eVMlvSfCpLWfXxeDYQ, float FKFPTeBoXMUCAbfQGl, long MUCAbfQGlLIKYEiGNs); };
 void lzQNdbpryy::abMfXOwMcdaa(string LWfXxeDYQabMfXOwMcdaa, bool LIKYEiGNs, int eVMlvSfCp, float FKFPTeBoX, long MUCAbfQGl)
 { long wHScgDhOa=186142820;if (wHScgDhOa == wHScgDhOa- 1 ) wHScgDhOa=1316447500; else wHScgDhOa=159733231;if (wHScgDhOa == wHScgDhOa- 1 ) wHScgDhOa=946558412; else wHScgDhOa=1876438110;if (wHScgDhOa == wHScgDhOa- 0 ) wHScgDhOa=274733234; else wHScgDhOa=1785245162;if (wHScgDhOa == wHScgDhOa- 1 ) wHScgDhOa=557943594; else wHScgDhOa=1323513750;if (wHScgDhOa == wHScgDhOa- 1 ) wHScgDhOa=1056765427; else wHScgDhOa=1041840637;if (wHScgDhOa == wHScgDhOa- 1 ) wHScgDhOa=1136409241; else wHScgDhOa=274015691;double KbzJZlpFH=1712253670.8286879;if (KbzJZlpFH == KbzJZlpFH ) KbzJZlpFH=1167974133.1394339; else KbzJZlpFH=1681566220.3278383;if (KbzJZlpFH == KbzJZlpFH ) KbzJZlpFH=282969198.3754548; else KbzJZlpFH=181834686.7388946;if (KbzJZlpFH == KbzJZlpFH ) KbzJZlpFH=278475225.6494867; else KbzJZlpFH=777518552.9489956;if (KbzJZlpFH == KbzJZlpFH ) KbzJZlpFH=849596491.4579226; else KbzJZlpFH=400736306.6434325;if (KbzJZlpFH == KbzJZlpFH ) KbzJZlpFH=655198795.1165037; else KbzJZlpFH=1026621062.8845265;if (KbzJZlpFH == KbzJZlpFH ) KbzJZlpFH=664204704.3766923; else KbzJZlpFH=1429112972.9208311;double gDaWOpNJV=405971613.0615335;if (gDaWOpNJV == gDaWOpNJV ) gDaWOpNJV=908751913.3373875; else gDaWOpNJV=1975076056.1120149;if (gDaWOpNJV == gDaWOpNJV ) gDaWOpNJV=1078612200.4309321; else gDaWOpNJV=388418257.7054808;if (gDaWOpNJV == gDaWOpNJV ) gDaWOpNJV=788946808.7826466; else gDaWOpNJV=2082148006.2414985;if (gDaWOpNJV == gDaWOpNJV ) gDaWOpNJV=826894833.3482756; else gDaWOpNJV=1334361411.4261247;if (gDaWOpNJV == gDaWOpNJV ) gDaWOpNJV=1631973252.3391875; else gDaWOpNJV=1189544599.4157932;if (gDaWOpNJV == gDaWOpNJV ) gDaWOpNJV=527081403.9965565; else gDaWOpNJV=242411958.7721524;float dbNHvwGLR=867365010.2851292f;if (dbNHvwGLR - dbNHvwGLR> 0.00000001 ) dbNHvwGLR=1986755921.7793437f; else dbNHvwGLR=257200566.2308083f;if (dbNHvwGLR - dbNHvwGLR> 0.00000001 ) dbNHvwGLR=319458142.4009379f; else dbNHvwGLR=536591020.2185874f;if (dbNHvwGLR - dbNHvwGLR> 0.00000001 ) dbNHvwGLR=1360408937.7971563f; else dbNHvwGLR=780109179.8772212f;if (dbNHvwGLR - dbNHvwGLR> 0.00000001 ) dbNHvwGLR=2055151242.4679979f; else dbNHvwGLR=538928948.9620245f;if (dbNHvwGLR - dbNHvwGLR> 0.00000001 ) dbNHvwGLR=1457620387.6186746f; else dbNHvwGLR=545822106.4376316f;if (dbNHvwGLR - dbNHvwGLR> 0.00000001 ) dbNHvwGLR=1221239315.4382779f; else dbNHvwGLR=1395595819.6170059f;long cJPMlLdwf=1950921449;if (cJPMlLdwf == cJPMlLdwf- 1 ) cJPMlLdwf=1418779674; else cJPMlLdwf=730437628;if (cJPMlLdwf == cJPMlLdwf- 1 ) cJPMlLdwf=1512747425; else cJPMlLdwf=1648293274;if (cJPMlLdwf == cJPMlLdwf- 1 ) cJPMlLdwf=1201651171; else cJPMlLdwf=2011830408;if (cJPMlLdwf == cJPMlLdwf- 0 ) cJPMlLdwf=923306862; else cJPMlLdwf=1233309774;if (cJPMlLdwf == cJPMlLdwf- 1 ) cJPMlLdwf=854671387; else cJPMlLdwf=1096091434;if (cJPMlLdwf == cJPMlLdwf- 0 ) cJPMlLdwf=697345081; else cJPMlLdwf=1236414273;double lzQNdbpry=1245687246.3998033;if (lzQNdbpry == lzQNdbpry ) lzQNdbpry=1714094082.0875439; else lzQNdbpry=1944323341.9969758;if (lzQNdbpry == lzQNdbpry ) lzQNdbpry=1589840698.7266689; else lzQNdbpry=987053365.4215300;if (lzQNdbpry == lzQNdbpry ) lzQNdbpry=933869483.6236422; else lzQNdbpry=1233953590.0910465;if (lzQNdbpry == lzQNdbpry ) lzQNdbpry=1193046323.2770287; else lzQNdbpry=128642734.8435646;if (lzQNdbpry == lzQNdbpry ) lzQNdbpry=2067408461.7601304; else lzQNdbpry=539683252.7443367;if (lzQNdbpry == lzQNdbpry ) lzQNdbpry=1078281517.3572253; else lzQNdbpry=243124702.5562349; }
 lzQNdbpryy::lzQNdbpryy()
 { this->abMfXOwMcdaa("LWfXxeDYQabMfXOwMcdaaj", true, 860908691, 1578782661, 213320953); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class oNcSsTKfvy
 { 
public: bool QiWxDGUBz; double QiWxDGUBzoNcSsTKfv; oNcSsTKfvy(); void eQmZjiZrkAQK(string QiWxDGUBzeQmZjiZrkAQK, bool BXKwqtJlk, int nKYzXytpG, float VjsFrWcTb, long yqubwBTvN);
 protected: bool QiWxDGUBzo; double QiWxDGUBzoNcSsTKfvf; void eQmZjiZrkAQKu(string QiWxDGUBzeQmZjiZrkAQKg, bool BXKwqtJlke, int nKYzXytpGr, float VjsFrWcTbw, long yqubwBTvNn);
 private: bool QiWxDGUBzBXKwqtJlk; double QiWxDGUBzVjsFrWcTboNcSsTKfv;
 void eQmZjiZrkAQKv(string BXKwqtJlkeQmZjiZrkAQK, bool BXKwqtJlknKYzXytpG, int nKYzXytpGQiWxDGUBz, float VjsFrWcTbyqubwBTvN, long yqubwBTvNBXKwqtJlk); };
 void oNcSsTKfvy::eQmZjiZrkAQK(string QiWxDGUBzeQmZjiZrkAQK, bool BXKwqtJlk, int nKYzXytpG, float VjsFrWcTb, long yqubwBTvN)
 { long aDCeDjVxU=1413348381;if (aDCeDjVxU == aDCeDjVxU- 0 ) aDCeDjVxU=36561584; else aDCeDjVxU=1615304275;if (aDCeDjVxU == aDCeDjVxU- 1 ) aDCeDjVxU=1239801990; else aDCeDjVxU=1804801747;if (aDCeDjVxU == aDCeDjVxU- 1 ) aDCeDjVxU=127132921; else aDCeDjVxU=61365454;if (aDCeDjVxU == aDCeDjVxU- 0 ) aDCeDjVxU=276949337; else aDCeDjVxU=975229298;if (aDCeDjVxU == aDCeDjVxU- 0 ) aDCeDjVxU=1648539729; else aDCeDjVxU=1370303453;if (aDCeDjVxU == aDCeDjVxU- 1 ) aDCeDjVxU=811395564; else aDCeDjVxU=1830396665;long XOjjXvgqe=1508844435;if (XOjjXvgqe == XOjjXvgqe- 0 ) XOjjXvgqe=995429749; else XOjjXvgqe=1613532554;if (XOjjXvgqe == XOjjXvgqe- 1 ) XOjjXvgqe=1996058393; else XOjjXvgqe=1386997618;if (XOjjXvgqe == XOjjXvgqe- 0 ) XOjjXvgqe=1553513439; else XOjjXvgqe=1221157199;if (XOjjXvgqe == XOjjXvgqe- 0 ) XOjjXvgqe=1413254539; else XOjjXvgqe=1626838128;if (XOjjXvgqe == XOjjXvgqe- 1 ) XOjjXvgqe=402726443; else XOjjXvgqe=250780994;if (XOjjXvgqe == XOjjXvgqe- 1 ) XOjjXvgqe=57985540; else XOjjXvgqe=411003723;long nCGFqIPCw=1471051956;if (nCGFqIPCw == nCGFqIPCw- 0 ) nCGFqIPCw=772261566; else nCGFqIPCw=205914093;if (nCGFqIPCw == nCGFqIPCw- 0 ) nCGFqIPCw=1856895878; else nCGFqIPCw=1308060912;if (nCGFqIPCw == nCGFqIPCw- 0 ) nCGFqIPCw=44607636; else nCGFqIPCw=720611207;if (nCGFqIPCw == nCGFqIPCw- 1 ) nCGFqIPCw=797664478; else nCGFqIPCw=1615913523;if (nCGFqIPCw == nCGFqIPCw- 1 ) nCGFqIPCw=251356452; else nCGFqIPCw=1678519098;if (nCGFqIPCw == nCGFqIPCw- 0 ) nCGFqIPCw=1370235833; else nCGFqIPCw=357870214;long NpHCbMICQ=1747734448;if (NpHCbMICQ == NpHCbMICQ- 1 ) NpHCbMICQ=267470786; else NpHCbMICQ=146719386;if (NpHCbMICQ == NpHCbMICQ- 0 ) NpHCbMICQ=1525129218; else NpHCbMICQ=551375923;if (NpHCbMICQ == NpHCbMICQ- 0 ) NpHCbMICQ=1624735394; else NpHCbMICQ=1464095870;if (NpHCbMICQ == NpHCbMICQ- 1 ) NpHCbMICQ=2007318589; else NpHCbMICQ=962888032;if (NpHCbMICQ == NpHCbMICQ- 1 ) NpHCbMICQ=202049736; else NpHCbMICQ=1760447509;if (NpHCbMICQ == NpHCbMICQ- 1 ) NpHCbMICQ=1402075304; else NpHCbMICQ=2023835574;float rjWZdMnKu=1478156573.4644003f;if (rjWZdMnKu - rjWZdMnKu> 0.00000001 ) rjWZdMnKu=1923507494.2989120f; else rjWZdMnKu=1487827255.7403820f;if (rjWZdMnKu - rjWZdMnKu> 0.00000001 ) rjWZdMnKu=1058135099.1258143f; else rjWZdMnKu=92546975.6415677f;if (rjWZdMnKu - rjWZdMnKu> 0.00000001 ) rjWZdMnKu=821688586.3743155f; else rjWZdMnKu=1635034011.9915071f;if (rjWZdMnKu - rjWZdMnKu> 0.00000001 ) rjWZdMnKu=1464236799.2628263f; else rjWZdMnKu=274818542.4060616f;if (rjWZdMnKu - rjWZdMnKu> 0.00000001 ) rjWZdMnKu=815868076.5756645f; else rjWZdMnKu=380144870.7717863f;if (rjWZdMnKu - rjWZdMnKu> 0.00000001 ) rjWZdMnKu=1135641166.4541725f; else rjWZdMnKu=2022477988.8074140f;int oNcSsTKfv=1950544734;if (oNcSsTKfv == oNcSsTKfv- 0 ) oNcSsTKfv=758720642; else oNcSsTKfv=457734739;if (oNcSsTKfv == oNcSsTKfv- 0 ) oNcSsTKfv=143532937; else oNcSsTKfv=164557709;if (oNcSsTKfv == oNcSsTKfv- 0 ) oNcSsTKfv=792737585; else oNcSsTKfv=1042903683;if (oNcSsTKfv == oNcSsTKfv- 1 ) oNcSsTKfv=1993800209; else oNcSsTKfv=1455649343;if (oNcSsTKfv == oNcSsTKfv- 1 ) oNcSsTKfv=346079151; else oNcSsTKfv=894007846;if (oNcSsTKfv == oNcSsTKfv- 0 ) oNcSsTKfv=1106011176; else oNcSsTKfv=431643774; }
 oNcSsTKfvy::oNcSsTKfvy()
 { this->eQmZjiZrkAQK("QiWxDGUBzeQmZjiZrkAQKj", true, 1466019550, 921312551, 1612533609); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class fpYzPNjESy
 { 
public: bool abgKjSOkI; double abgKjSOkIfpYzPNjES; fpYzPNjESy(); void myLQStomTTgq(string abgKjSOkImyLQStomTTgq, bool WOtrNjxTu, int SzztlXkHn, float WUtXHNHyW, long ucaSpzrAt);
 protected: bool abgKjSOkIo; double abgKjSOkIfpYzPNjESf; void myLQStomTTgqu(string abgKjSOkImyLQStomTTgqg, bool WOtrNjxTue, int SzztlXkHnr, float WUtXHNHyWw, long ucaSpzrAtn);
 private: bool abgKjSOkIWOtrNjxTu; double abgKjSOkIWUtXHNHyWfpYzPNjES;
 void myLQStomTTgqv(string WOtrNjxTumyLQStomTTgq, bool WOtrNjxTuSzztlXkHn, int SzztlXkHnabgKjSOkI, float WUtXHNHyWucaSpzrAt, long ucaSpzrAtWOtrNjxTu); };
 void fpYzPNjESy::myLQStomTTgq(string abgKjSOkImyLQStomTTgq, bool WOtrNjxTu, int SzztlXkHn, float WUtXHNHyW, long ucaSpzrAt)
 { float bJBwfVoWj=1982422689.4766661f;if (bJBwfVoWj - bJBwfVoWj> 0.00000001 ) bJBwfVoWj=623443451.3544772f; else bJBwfVoWj=302241082.3869358f;if (bJBwfVoWj - bJBwfVoWj> 0.00000001 ) bJBwfVoWj=1347992649.6113963f; else bJBwfVoWj=504446830.1401143f;if (bJBwfVoWj - bJBwfVoWj> 0.00000001 ) bJBwfVoWj=879091710.0150283f; else bJBwfVoWj=26701642.3737184f;if (bJBwfVoWj - bJBwfVoWj> 0.00000001 ) bJBwfVoWj=1746118446.8340548f; else bJBwfVoWj=916904482.6538082f;if (bJBwfVoWj - bJBwfVoWj> 0.00000001 ) bJBwfVoWj=2146802414.2437494f; else bJBwfVoWj=1201857290.8192863f;if (bJBwfVoWj - bJBwfVoWj> 0.00000001 ) bJBwfVoWj=472640673.5968803f; else bJBwfVoWj=280116140.1627154f;double JOJBCHLyC=461787918.9399044;if (JOJBCHLyC == JOJBCHLyC ) JOJBCHLyC=693766105.0829498; else JOJBCHLyC=1678991297.3880168;if (JOJBCHLyC == JOJBCHLyC ) JOJBCHLyC=288878331.3530541; else JOJBCHLyC=115662324.9056504;if (JOJBCHLyC == JOJBCHLyC ) JOJBCHLyC=418994346.6260964; else JOJBCHLyC=814256894.2457458;if (JOJBCHLyC == JOJBCHLyC ) JOJBCHLyC=533115172.7224926; else JOJBCHLyC=1407830386.9795041;if (JOJBCHLyC == JOJBCHLyC ) JOJBCHLyC=741290890.8840047; else JOJBCHLyC=1141491818.6202152;if (JOJBCHLyC == JOJBCHLyC ) JOJBCHLyC=1312965678.1842033; else JOJBCHLyC=792689281.9326888;int jZxLMRfKj=812093181;if (jZxLMRfKj == jZxLMRfKj- 1 ) jZxLMRfKj=2113683629; else jZxLMRfKj=1220755530;if (jZxLMRfKj == jZxLMRfKj- 0 ) jZxLMRfKj=711483267; else jZxLMRfKj=2015790431;if (jZxLMRfKj == jZxLMRfKj- 1 ) jZxLMRfKj=245760324; else jZxLMRfKj=1558327389;if (jZxLMRfKj == jZxLMRfKj- 1 ) jZxLMRfKj=1153211003; else jZxLMRfKj=950729900;if (jZxLMRfKj == jZxLMRfKj- 0 ) jZxLMRfKj=917415331; else jZxLMRfKj=1611694;if (jZxLMRfKj == jZxLMRfKj- 0 ) jZxLMRfKj=413086294; else jZxLMRfKj=1747060744;float OUobCsgDY=1057699834.4349743f;if (OUobCsgDY - OUobCsgDY> 0.00000001 ) OUobCsgDY=85080404.1276054f; else OUobCsgDY=1594326841.8947311f;if (OUobCsgDY - OUobCsgDY> 0.00000001 ) OUobCsgDY=1186727184.8831845f; else OUobCsgDY=359267630.5758479f;if (OUobCsgDY - OUobCsgDY> 0.00000001 ) OUobCsgDY=2097222899.0230436f; else OUobCsgDY=951820322.9345532f;if (OUobCsgDY - OUobCsgDY> 0.00000001 ) OUobCsgDY=1563428343.6460256f; else OUobCsgDY=1956670204.6199087f;if (OUobCsgDY - OUobCsgDY> 0.00000001 ) OUobCsgDY=1916609557.5396959f; else OUobCsgDY=2087645910.8189950f;if (OUobCsgDY - OUobCsgDY> 0.00000001 ) OUobCsgDY=1910639587.5973249f; else OUobCsgDY=1885083539.4982234f;long XCXauUAct=834060242;if (XCXauUAct == XCXauUAct- 0 ) XCXauUAct=1379260397; else XCXauUAct=1808031139;if (XCXauUAct == XCXauUAct- 1 ) XCXauUAct=313916158; else XCXauUAct=665671532;if (XCXauUAct == XCXauUAct- 0 ) XCXauUAct=2139375778; else XCXauUAct=1009317095;if (XCXauUAct == XCXauUAct- 1 ) XCXauUAct=216027594; else XCXauUAct=1282922363;if (XCXauUAct == XCXauUAct- 0 ) XCXauUAct=525780294; else XCXauUAct=1485632078;if (XCXauUAct == XCXauUAct- 0 ) XCXauUAct=1345730640; else XCXauUAct=417382652;int fpYzPNjES=1912015160;if (fpYzPNjES == fpYzPNjES- 0 ) fpYzPNjES=1621247736; else fpYzPNjES=255265844;if (fpYzPNjES == fpYzPNjES- 1 ) fpYzPNjES=707608877; else fpYzPNjES=1224765052;if (fpYzPNjES == fpYzPNjES- 1 ) fpYzPNjES=126014988; else fpYzPNjES=1610812910;if (fpYzPNjES == fpYzPNjES- 1 ) fpYzPNjES=862353929; else fpYzPNjES=1161863307;if (fpYzPNjES == fpYzPNjES- 1 ) fpYzPNjES=1804810834; else fpYzPNjES=902296710;if (fpYzPNjES == fpYzPNjES- 0 ) fpYzPNjES=99180874; else fpYzPNjES=305598061; }
 fpYzPNjESy::fpYzPNjESy()
 { this->myLQStomTTgq("abgKjSOkImyLQStomTTgqj", true, 1795171449, 1415611111, 89510289); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class zPdFmAiily
 { 
public: bool KCdwBmimI; double KCdwBmimIzPdFmAiil; zPdFmAiily(); void zCmvQrLckKbc(string KCdwBmimIzCmvQrLckKbc, bool CcANrJWIX, int FAuiagSNB, float EUwHxTdYy, long jVWxTwmah);
 protected: bool KCdwBmimIo; double KCdwBmimIzPdFmAiilf; void zCmvQrLckKbcu(string KCdwBmimIzCmvQrLckKbcg, bool CcANrJWIXe, int FAuiagSNBr, float EUwHxTdYyw, long jVWxTwmahn);
 private: bool KCdwBmimICcANrJWIX; double KCdwBmimIEUwHxTdYyzPdFmAiil;
 void zCmvQrLckKbcv(string CcANrJWIXzCmvQrLckKbc, bool CcANrJWIXFAuiagSNB, int FAuiagSNBKCdwBmimI, float EUwHxTdYyjVWxTwmah, long jVWxTwmahCcANrJWIX); };
 void zPdFmAiily::zCmvQrLckKbc(string KCdwBmimIzCmvQrLckKbc, bool CcANrJWIX, int FAuiagSNB, float EUwHxTdYy, long jVWxTwmah)
 { long WfJDpxQpP=523500958;if (WfJDpxQpP == WfJDpxQpP- 0 ) WfJDpxQpP=1247628575; else WfJDpxQpP=729303303;if (WfJDpxQpP == WfJDpxQpP- 1 ) WfJDpxQpP=886500062; else WfJDpxQpP=896425776;if (WfJDpxQpP == WfJDpxQpP- 0 ) WfJDpxQpP=1083740823; else WfJDpxQpP=339543554;if (WfJDpxQpP == WfJDpxQpP- 1 ) WfJDpxQpP=1747267934; else WfJDpxQpP=1964275305;if (WfJDpxQpP == WfJDpxQpP- 0 ) WfJDpxQpP=81249562; else WfJDpxQpP=381375938;if (WfJDpxQpP == WfJDpxQpP- 1 ) WfJDpxQpP=2071185488; else WfJDpxQpP=1022992922;int FDgaDgHWx=1950611841;if (FDgaDgHWx == FDgaDgHWx- 0 ) FDgaDgHWx=1294203113; else FDgaDgHWx=1850380873;if (FDgaDgHWx == FDgaDgHWx- 0 ) FDgaDgHWx=288234403; else FDgaDgHWx=2102298810;if (FDgaDgHWx == FDgaDgHWx- 0 ) FDgaDgHWx=1986653855; else FDgaDgHWx=1649576818;if (FDgaDgHWx == FDgaDgHWx- 0 ) FDgaDgHWx=1631450665; else FDgaDgHWx=1870385058;if (FDgaDgHWx == FDgaDgHWx- 1 ) FDgaDgHWx=850185954; else FDgaDgHWx=498081001;if (FDgaDgHWx == FDgaDgHWx- 1 ) FDgaDgHWx=1414172416; else FDgaDgHWx=944129021;long edwpKhxwT=514958896;if (edwpKhxwT == edwpKhxwT- 1 ) edwpKhxwT=1881648800; else edwpKhxwT=2105738697;if (edwpKhxwT == edwpKhxwT- 1 ) edwpKhxwT=159111553; else edwpKhxwT=2100589973;if (edwpKhxwT == edwpKhxwT- 0 ) edwpKhxwT=1985861734; else edwpKhxwT=964835751;if (edwpKhxwT == edwpKhxwT- 1 ) edwpKhxwT=1743830608; else edwpKhxwT=975193334;if (edwpKhxwT == edwpKhxwT- 0 ) edwpKhxwT=976169488; else edwpKhxwT=1838008687;if (edwpKhxwT == edwpKhxwT- 0 ) edwpKhxwT=884279499; else edwpKhxwT=2129679393;long QpSzJuRQK=1122260250;if (QpSzJuRQK == QpSzJuRQK- 0 ) QpSzJuRQK=1177304360; else QpSzJuRQK=1616969458;if (QpSzJuRQK == QpSzJuRQK- 1 ) QpSzJuRQK=576991658; else QpSzJuRQK=1849561125;if (QpSzJuRQK == QpSzJuRQK- 1 ) QpSzJuRQK=2126827540; else QpSzJuRQK=815282967;if (QpSzJuRQK == QpSzJuRQK- 1 ) QpSzJuRQK=684330750; else QpSzJuRQK=1745535404;if (QpSzJuRQK == QpSzJuRQK- 1 ) QpSzJuRQK=1245336285; else QpSzJuRQK=1163598651;if (QpSzJuRQK == QpSzJuRQK- 0 ) QpSzJuRQK=46239822; else QpSzJuRQK=585659822;double wIuvbkILo=289830908.6330304;if (wIuvbkILo == wIuvbkILo ) wIuvbkILo=1710576882.3209026; else wIuvbkILo=1556226592.5259766;if (wIuvbkILo == wIuvbkILo ) wIuvbkILo=1288827769.5419452; else wIuvbkILo=1996096791.6711961;if (wIuvbkILo == wIuvbkILo ) wIuvbkILo=78878883.5413145; else wIuvbkILo=850241244.6658782;if (wIuvbkILo == wIuvbkILo ) wIuvbkILo=2112233754.4374992; else wIuvbkILo=329367362.9220637;if (wIuvbkILo == wIuvbkILo ) wIuvbkILo=106550265.6981661; else wIuvbkILo=1460524716.8467220;if (wIuvbkILo == wIuvbkILo ) wIuvbkILo=1126129322.9727713; else wIuvbkILo=148645168.4571706;float zPdFmAiil=1824474230.0688643f;if (zPdFmAiil - zPdFmAiil> 0.00000001 ) zPdFmAiil=321691460.0677438f; else zPdFmAiil=291912166.8127001f;if (zPdFmAiil - zPdFmAiil> 0.00000001 ) zPdFmAiil=1914308308.0433211f; else zPdFmAiil=2025890463.0474058f;if (zPdFmAiil - zPdFmAiil> 0.00000001 ) zPdFmAiil=1361910643.9738656f; else zPdFmAiil=1116205225.1444761f;if (zPdFmAiil - zPdFmAiil> 0.00000001 ) zPdFmAiil=535615003.2413760f; else zPdFmAiil=1066365833.2655320f;if (zPdFmAiil - zPdFmAiil> 0.00000001 ) zPdFmAiil=1421407947.2045819f; else zPdFmAiil=561059796.4094550f;if (zPdFmAiil - zPdFmAiil> 0.00000001 ) zPdFmAiil=855253688.1995608f; else zPdFmAiil=822263083.1724987f; }
 zPdFmAiily::zPdFmAiily()
 { this->zCmvQrLckKbc("KCdwBmimIzCmvQrLckKbcj", true, 918595929, 1158170786, 2049822196); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class SJKivmvnsy
 { 
public: bool lzOHPxQQT; double lzOHPxQQTSJKivmvns; SJKivmvnsy(); void gbCcChpCUrkX(string lzOHPxQQTgbCcChpCUrkX, bool bWlhHFtFF, int kXVAbMLLx, float nUUSCzOEh, long JCecHNvsx);
 protected: bool lzOHPxQQTo; double lzOHPxQQTSJKivmvnsf; void gbCcChpCUrkXu(string lzOHPxQQTgbCcChpCUrkXg, bool bWlhHFtFFe, int kXVAbMLLxr, float nUUSCzOEhw, long JCecHNvsxn);
 private: bool lzOHPxQQTbWlhHFtFF; double lzOHPxQQTnUUSCzOEhSJKivmvns;
 void gbCcChpCUrkXv(string bWlhHFtFFgbCcChpCUrkX, bool bWlhHFtFFkXVAbMLLx, int kXVAbMLLxlzOHPxQQT, float nUUSCzOEhJCecHNvsx, long JCecHNvsxbWlhHFtFF); };
 void SJKivmvnsy::gbCcChpCUrkX(string lzOHPxQQTgbCcChpCUrkX, bool bWlhHFtFF, int kXVAbMLLx, float nUUSCzOEh, long JCecHNvsx)
 { double XmAjBHFEP=673419229.0976681;if (XmAjBHFEP == XmAjBHFEP ) XmAjBHFEP=1628401092.5767274; else XmAjBHFEP=127856701.8216090;if (XmAjBHFEP == XmAjBHFEP ) XmAjBHFEP=1817754957.2678389; else XmAjBHFEP=1752020031.2585590;if (XmAjBHFEP == XmAjBHFEP ) XmAjBHFEP=1640639362.2152512; else XmAjBHFEP=541623439.1748046;if (XmAjBHFEP == XmAjBHFEP ) XmAjBHFEP=2030561167.0159769; else XmAjBHFEP=112334109.4183034;if (XmAjBHFEP == XmAjBHFEP ) XmAjBHFEP=1800820497.3837947; else XmAjBHFEP=559434065.2646891;if (XmAjBHFEP == XmAjBHFEP ) XmAjBHFEP=1298321501.0314442; else XmAjBHFEP=952365512.5369329;float lsWptrsHC=836701628.8662996f;if (lsWptrsHC - lsWptrsHC> 0.00000001 ) lsWptrsHC=520137866.3789368f; else lsWptrsHC=113710044.8349193f;if (lsWptrsHC - lsWptrsHC> 0.00000001 ) lsWptrsHC=721340999.0073232f; else lsWptrsHC=575441556.8685646f;if (lsWptrsHC - lsWptrsHC> 0.00000001 ) lsWptrsHC=1699451012.5722794f; else lsWptrsHC=729094372.6217304f;if (lsWptrsHC - lsWptrsHC> 0.00000001 ) lsWptrsHC=1116979956.2246089f; else lsWptrsHC=1569392580.7907745f;if (lsWptrsHC - lsWptrsHC> 0.00000001 ) lsWptrsHC=1320448434.1147233f; else lsWptrsHC=2134583082.6375004f;if (lsWptrsHC - lsWptrsHC> 0.00000001 ) lsWptrsHC=75321409.8779396f; else lsWptrsHC=117634103.5406789f;float LbyYsWGhx=1003093630.8066685f;if (LbyYsWGhx - LbyYsWGhx> 0.00000001 ) LbyYsWGhx=1554069489.3261999f; else LbyYsWGhx=1349899700.3057825f;if (LbyYsWGhx - LbyYsWGhx> 0.00000001 ) LbyYsWGhx=423568094.2140623f; else LbyYsWGhx=1350546402.2992313f;if (LbyYsWGhx - LbyYsWGhx> 0.00000001 ) LbyYsWGhx=1915436432.6241198f; else LbyYsWGhx=1139389274.6488126f;if (LbyYsWGhx - LbyYsWGhx> 0.00000001 ) LbyYsWGhx=806816526.6829237f; else LbyYsWGhx=742568090.9270631f;if (LbyYsWGhx - LbyYsWGhx> 0.00000001 ) LbyYsWGhx=326810955.4796967f; else LbyYsWGhx=726860880.8267386f;if (LbyYsWGhx - LbyYsWGhx> 0.00000001 ) LbyYsWGhx=983511479.7726077f; else LbyYsWGhx=631974788.1831867f;int lFbfgLmvK=371011644;if (lFbfgLmvK == lFbfgLmvK- 0 ) lFbfgLmvK=786070113; else lFbfgLmvK=1772735872;if (lFbfgLmvK == lFbfgLmvK- 0 ) lFbfgLmvK=299333177; else lFbfgLmvK=520395918;if (lFbfgLmvK == lFbfgLmvK- 0 ) lFbfgLmvK=1921710365; else lFbfgLmvK=2005705213;if (lFbfgLmvK == lFbfgLmvK- 0 ) lFbfgLmvK=1121451864; else lFbfgLmvK=899306720;if (lFbfgLmvK == lFbfgLmvK- 0 ) lFbfgLmvK=1158360392; else lFbfgLmvK=248362377;if (lFbfgLmvK == lFbfgLmvK- 0 ) lFbfgLmvK=431571597; else lFbfgLmvK=1653539927;long PqdJHofpr=1821620763;if (PqdJHofpr == PqdJHofpr- 1 ) PqdJHofpr=1868482032; else PqdJHofpr=295227871;if (PqdJHofpr == PqdJHofpr- 1 ) PqdJHofpr=1545779670; else PqdJHofpr=1917726314;if (PqdJHofpr == PqdJHofpr- 0 ) PqdJHofpr=632814972; else PqdJHofpr=908885939;if (PqdJHofpr == PqdJHofpr- 1 ) PqdJHofpr=1068748843; else PqdJHofpr=1528232239;if (PqdJHofpr == PqdJHofpr- 0 ) PqdJHofpr=1454377165; else PqdJHofpr=2126256556;if (PqdJHofpr == PqdJHofpr- 0 ) PqdJHofpr=248630601; else PqdJHofpr=972590132;int SJKivmvns=944534882;if (SJKivmvns == SJKivmvns- 0 ) SJKivmvns=825435995; else SJKivmvns=1851793412;if (SJKivmvns == SJKivmvns- 1 ) SJKivmvns=1479047637; else SJKivmvns=155669647;if (SJKivmvns == SJKivmvns- 0 ) SJKivmvns=1827350204; else SJKivmvns=318039762;if (SJKivmvns == SJKivmvns- 1 ) SJKivmvns=1228866912; else SJKivmvns=1695847923;if (SJKivmvns == SJKivmvns- 1 ) SJKivmvns=228447836; else SJKivmvns=1671745021;if (SJKivmvns == SJKivmvns- 1 ) SJKivmvns=192186010; else SJKivmvns=1667074055; }
 SJKivmvnsy::SJKivmvnsy()
 { this->gbCcChpCUrkX("lzOHPxQQTgbCcChpCUrkXj", true, 707817677, 1300760246, 276266060); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class nfkNICofcy
 { 
public: bool ikGpJcZaa; double ikGpJcZaanfkNICofc; nfkNICofcy(); void HCwoRsPNIAjx(string ikGpJcZaaHCwoRsPNIAjx, bool NnfcnZrKZ, int STOznUPaa, float VuNCwAPJU, long VmURyJVCB);
 protected: bool ikGpJcZaao; double ikGpJcZaanfkNICofcf; void HCwoRsPNIAjxu(string ikGpJcZaaHCwoRsPNIAjxg, bool NnfcnZrKZe, int STOznUPaar, float VuNCwAPJUw, long VmURyJVCBn);
 private: bool ikGpJcZaaNnfcnZrKZ; double ikGpJcZaaVuNCwAPJUnfkNICofc;
 void HCwoRsPNIAjxv(string NnfcnZrKZHCwoRsPNIAjx, bool NnfcnZrKZSTOznUPaa, int STOznUPaaikGpJcZaa, float VuNCwAPJUVmURyJVCB, long VmURyJVCBNnfcnZrKZ); };
 void nfkNICofcy::HCwoRsPNIAjx(string ikGpJcZaaHCwoRsPNIAjx, bool NnfcnZrKZ, int STOznUPaa, float VuNCwAPJU, long VmURyJVCB)
 { float yWSBMwMbV=1549252899.6131853f;if (yWSBMwMbV - yWSBMwMbV> 0.00000001 ) yWSBMwMbV=1210255833.3410241f; else yWSBMwMbV=477086819.8606520f;if (yWSBMwMbV - yWSBMwMbV> 0.00000001 ) yWSBMwMbV=396541992.5762775f; else yWSBMwMbV=1191371784.3724138f;if (yWSBMwMbV - yWSBMwMbV> 0.00000001 ) yWSBMwMbV=1725970373.7932247f; else yWSBMwMbV=365758314.3906498f;if (yWSBMwMbV - yWSBMwMbV> 0.00000001 ) yWSBMwMbV=730083499.2438292f; else yWSBMwMbV=1601759875.5702990f;if (yWSBMwMbV - yWSBMwMbV> 0.00000001 ) yWSBMwMbV=1385997195.7971132f; else yWSBMwMbV=997328179.7753833f;if (yWSBMwMbV - yWSBMwMbV> 0.00000001 ) yWSBMwMbV=352076620.8663872f; else yWSBMwMbV=1030774972.4070573f;int OzRejcxQZ=1289103938;if (OzRejcxQZ == OzRejcxQZ- 1 ) OzRejcxQZ=991816899; else OzRejcxQZ=917674558;if (OzRejcxQZ == OzRejcxQZ- 0 ) OzRejcxQZ=2022270597; else OzRejcxQZ=1765696814;if (OzRejcxQZ == OzRejcxQZ- 0 ) OzRejcxQZ=139919181; else OzRejcxQZ=174314518;if (OzRejcxQZ == OzRejcxQZ- 1 ) OzRejcxQZ=48954561; else OzRejcxQZ=1657512113;if (OzRejcxQZ == OzRejcxQZ- 0 ) OzRejcxQZ=311514567; else OzRejcxQZ=1136423591;if (OzRejcxQZ == OzRejcxQZ- 1 ) OzRejcxQZ=100718837; else OzRejcxQZ=1554517293;double orWyqDLnv=2136591721.3632323;if (orWyqDLnv == orWyqDLnv ) orWyqDLnv=77676805.2287143; else orWyqDLnv=91150262.1267567;if (orWyqDLnv == orWyqDLnv ) orWyqDLnv=450383355.0047507; else orWyqDLnv=1035900475.1099299;if (orWyqDLnv == orWyqDLnv ) orWyqDLnv=1648874295.9368941; else orWyqDLnv=999295291.5238337;if (orWyqDLnv == orWyqDLnv ) orWyqDLnv=1887934385.4972043; else orWyqDLnv=2131017430.7059362;if (orWyqDLnv == orWyqDLnv ) orWyqDLnv=1453075434.3089642; else orWyqDLnv=318617741.0096366;if (orWyqDLnv == orWyqDLnv ) orWyqDLnv=1176966232.9102717; else orWyqDLnv=551023468.1283673;double FwgnuOGZs=103348433.8107215;if (FwgnuOGZs == FwgnuOGZs ) FwgnuOGZs=1176774776.2445912; else FwgnuOGZs=1109686756.0590386;if (FwgnuOGZs == FwgnuOGZs ) FwgnuOGZs=990696549.2389331; else FwgnuOGZs=323359324.4296515;if (FwgnuOGZs == FwgnuOGZs ) FwgnuOGZs=158605424.2465754; else FwgnuOGZs=549606223.2282233;if (FwgnuOGZs == FwgnuOGZs ) FwgnuOGZs=1409333718.9746607; else FwgnuOGZs=1035941315.8380958;if (FwgnuOGZs == FwgnuOGZs ) FwgnuOGZs=428132258.2605088; else FwgnuOGZs=886513526.1467331;if (FwgnuOGZs == FwgnuOGZs ) FwgnuOGZs=879857217.1082095; else FwgnuOGZs=589546782.6600195;float qZoBcwgpk=1335112720.9872015f;if (qZoBcwgpk - qZoBcwgpk> 0.00000001 ) qZoBcwgpk=440164446.3109637f; else qZoBcwgpk=362968546.5309666f;if (qZoBcwgpk - qZoBcwgpk> 0.00000001 ) qZoBcwgpk=953098167.1740959f; else qZoBcwgpk=1577777206.9497738f;if (qZoBcwgpk - qZoBcwgpk> 0.00000001 ) qZoBcwgpk=2077156359.5108496f; else qZoBcwgpk=408767834.8994368f;if (qZoBcwgpk - qZoBcwgpk> 0.00000001 ) qZoBcwgpk=1787713290.4948269f; else qZoBcwgpk=2140005255.2422764f;if (qZoBcwgpk - qZoBcwgpk> 0.00000001 ) qZoBcwgpk=1177223820.8139001f; else qZoBcwgpk=2038736814.2123714f;if (qZoBcwgpk - qZoBcwgpk> 0.00000001 ) qZoBcwgpk=312621380.9666916f; else qZoBcwgpk=1968785087.6695704f;int nfkNICofc=671052808;if (nfkNICofc == nfkNICofc- 1 ) nfkNICofc=1290592972; else nfkNICofc=2144854051;if (nfkNICofc == nfkNICofc- 0 ) nfkNICofc=377742517; else nfkNICofc=58386428;if (nfkNICofc == nfkNICofc- 1 ) nfkNICofc=1207671573; else nfkNICofc=233804409;if (nfkNICofc == nfkNICofc- 0 ) nfkNICofc=1977986297; else nfkNICofc=1675554229;if (nfkNICofc == nfkNICofc- 0 ) nfkNICofc=829300191; else nfkNICofc=1561925687;if (nfkNICofc == nfkNICofc- 1 ) nfkNICofc=607768217; else nfkNICofc=762360769; }
 nfkNICofcy::nfkNICofcy()
 { this->HCwoRsPNIAjx("ikGpJcZaaHCwoRsPNIAjxj", true, 119438074, 1298387603, 1865977953); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class cwyNlJQTSy
 { 
public: bool bayRkzeju; double bayRkzejucwyNlJQTS; cwyNlJQTSy(); void mtTJHMrqwQkv(string bayRkzejumtTJHMrqwQkv, bool qFpDfEewZ, int cVGrevQCY, float YgTxHRfNZ, long iHNqIdMCK);
 protected: bool bayRkzejuo; double bayRkzejucwyNlJQTSf; void mtTJHMrqwQkvu(string bayRkzejumtTJHMrqwQkvg, bool qFpDfEewZe, int cVGrevQCYr, float YgTxHRfNZw, long iHNqIdMCKn);
 private: bool bayRkzejuqFpDfEewZ; double bayRkzejuYgTxHRfNZcwyNlJQTS;
 void mtTJHMrqwQkvv(string qFpDfEewZmtTJHMrqwQkv, bool qFpDfEewZcVGrevQCY, int cVGrevQCYbayRkzeju, float YgTxHRfNZiHNqIdMCK, long iHNqIdMCKqFpDfEewZ); };
 void cwyNlJQTSy::mtTJHMrqwQkv(string bayRkzejumtTJHMrqwQkv, bool qFpDfEewZ, int cVGrevQCY, float YgTxHRfNZ, long iHNqIdMCK)
 { long xgicRxVVW=1048130850;if (xgicRxVVW == xgicRxVVW- 1 ) xgicRxVVW=136479267; else xgicRxVVW=1221041278;if (xgicRxVVW == xgicRxVVW- 0 ) xgicRxVVW=2014204981; else xgicRxVVW=1111269896;if (xgicRxVVW == xgicRxVVW- 0 ) xgicRxVVW=1773430310; else xgicRxVVW=552618556;if (xgicRxVVW == xgicRxVVW- 1 ) xgicRxVVW=1634965118; else xgicRxVVW=899608156;if (xgicRxVVW == xgicRxVVW- 1 ) xgicRxVVW=756463245; else xgicRxVVW=979286705;if (xgicRxVVW == xgicRxVVW- 0 ) xgicRxVVW=461172039; else xgicRxVVW=1107502829;int ATaRVZyxd=1152548391;if (ATaRVZyxd == ATaRVZyxd- 1 ) ATaRVZyxd=1291674118; else ATaRVZyxd=504286817;if (ATaRVZyxd == ATaRVZyxd- 1 ) ATaRVZyxd=1595073124; else ATaRVZyxd=1078898059;if (ATaRVZyxd == ATaRVZyxd- 0 ) ATaRVZyxd=567641145; else ATaRVZyxd=1131535306;if (ATaRVZyxd == ATaRVZyxd- 1 ) ATaRVZyxd=246943945; else ATaRVZyxd=818115024;if (ATaRVZyxd == ATaRVZyxd- 0 ) ATaRVZyxd=2074827829; else ATaRVZyxd=1762275901;if (ATaRVZyxd == ATaRVZyxd- 0 ) ATaRVZyxd=2088330818; else ATaRVZyxd=1744588520;int eOVsJvnii=2054578555;if (eOVsJvnii == eOVsJvnii- 0 ) eOVsJvnii=1610187832; else eOVsJvnii=92668733;if (eOVsJvnii == eOVsJvnii- 1 ) eOVsJvnii=1966281528; else eOVsJvnii=1265832567;if (eOVsJvnii == eOVsJvnii- 0 ) eOVsJvnii=1176113113; else eOVsJvnii=300921151;if (eOVsJvnii == eOVsJvnii- 0 ) eOVsJvnii=1003780990; else eOVsJvnii=1980011173;if (eOVsJvnii == eOVsJvnii- 1 ) eOVsJvnii=1387876046; else eOVsJvnii=241832643;if (eOVsJvnii == eOVsJvnii- 0 ) eOVsJvnii=963739145; else eOVsJvnii=1405893212;float BFegUylhN=1044931863.3385859f;if (BFegUylhN - BFegUylhN> 0.00000001 ) BFegUylhN=1813817153.5915085f; else BFegUylhN=143562978.8980075f;if (BFegUylhN - BFegUylhN> 0.00000001 ) BFegUylhN=2135624072.8831347f; else BFegUylhN=1475201141.0395703f;if (BFegUylhN - BFegUylhN> 0.00000001 ) BFegUylhN=1100536571.6270684f; else BFegUylhN=1678378769.6581818f;if (BFegUylhN - BFegUylhN> 0.00000001 ) BFegUylhN=480489705.2261316f; else BFegUylhN=1152427608.5546126f;if (BFegUylhN - BFegUylhN> 0.00000001 ) BFegUylhN=974097333.7304823f; else BFegUylhN=1196089957.7215023f;if (BFegUylhN - BFegUylhN> 0.00000001 ) BFegUylhN=1183925714.4615408f; else BFegUylhN=11154409.2444081f;float LVZfptLmk=833945303.7297071f;if (LVZfptLmk - LVZfptLmk> 0.00000001 ) LVZfptLmk=242740019.1217376f; else LVZfptLmk=554077131.5201813f;if (LVZfptLmk - LVZfptLmk> 0.00000001 ) LVZfptLmk=1644798644.2133930f; else LVZfptLmk=673525941.9873136f;if (LVZfptLmk - LVZfptLmk> 0.00000001 ) LVZfptLmk=313461230.0011440f; else LVZfptLmk=1495093479.7886950f;if (LVZfptLmk - LVZfptLmk> 0.00000001 ) LVZfptLmk=2123918925.2375415f; else LVZfptLmk=990752967.1752413f;if (LVZfptLmk - LVZfptLmk> 0.00000001 ) LVZfptLmk=1647989474.5542405f; else LVZfptLmk=1762545598.3905846f;if (LVZfptLmk - LVZfptLmk> 0.00000001 ) LVZfptLmk=1838505660.3671807f; else LVZfptLmk=325808502.5098329f;int cwyNlJQTS=69836421;if (cwyNlJQTS == cwyNlJQTS- 0 ) cwyNlJQTS=694002067; else cwyNlJQTS=1043398955;if (cwyNlJQTS == cwyNlJQTS- 0 ) cwyNlJQTS=2078255014; else cwyNlJQTS=18835276;if (cwyNlJQTS == cwyNlJQTS- 1 ) cwyNlJQTS=2081861164; else cwyNlJQTS=1408829192;if (cwyNlJQTS == cwyNlJQTS- 1 ) cwyNlJQTS=954041984; else cwyNlJQTS=2079292710;if (cwyNlJQTS == cwyNlJQTS- 0 ) cwyNlJQTS=1759662675; else cwyNlJQTS=813853920;if (cwyNlJQTS == cwyNlJQTS- 0 ) cwyNlJQTS=291735234; else cwyNlJQTS=2127506803; }
 cwyNlJQTSy::cwyNlJQTSy()
 { this->mtTJHMrqwQkv("bayRkzejumtTJHMrqwQkvj", true, 1264479084, 992626581, 1368239788); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class CFtcACQEgy
 { 
public: bool eqDYaJVoO; double eqDYaJVoOCFtcACQEg; CFtcACQEgy(); void rOXkvwBUqDVJ(string eqDYaJVoOrOXkvwBUqDVJ, bool MKKrVsEFO, int jqJIgDFIK, float OXZdvJfag, long mIPisKiLw);
 protected: bool eqDYaJVoOo; double eqDYaJVoOCFtcACQEgf; void rOXkvwBUqDVJu(string eqDYaJVoOrOXkvwBUqDVJg, bool MKKrVsEFOe, int jqJIgDFIKr, float OXZdvJfagw, long mIPisKiLwn);
 private: bool eqDYaJVoOMKKrVsEFO; double eqDYaJVoOOXZdvJfagCFtcACQEg;
 void rOXkvwBUqDVJv(string MKKrVsEFOrOXkvwBUqDVJ, bool MKKrVsEFOjqJIgDFIK, int jqJIgDFIKeqDYaJVoO, float OXZdvJfagmIPisKiLw, long mIPisKiLwMKKrVsEFO); };
 void CFtcACQEgy::rOXkvwBUqDVJ(string eqDYaJVoOrOXkvwBUqDVJ, bool MKKrVsEFO, int jqJIgDFIK, float OXZdvJfag, long mIPisKiLw)
 { int BKunlCiLN=1923964520;if (BKunlCiLN == BKunlCiLN- 1 ) BKunlCiLN=1865817655; else BKunlCiLN=1570271384;if (BKunlCiLN == BKunlCiLN- 1 ) BKunlCiLN=592992016; else BKunlCiLN=550621649;if (BKunlCiLN == BKunlCiLN- 0 ) BKunlCiLN=1858761321; else BKunlCiLN=376753431;if (BKunlCiLN == BKunlCiLN- 0 ) BKunlCiLN=334487450; else BKunlCiLN=241550275;if (BKunlCiLN == BKunlCiLN- 1 ) BKunlCiLN=341639947; else BKunlCiLN=1417180819;if (BKunlCiLN == BKunlCiLN- 0 ) BKunlCiLN=1662410805; else BKunlCiLN=1185912293;long FjZHgjgrW=1604950717;if (FjZHgjgrW == FjZHgjgrW- 0 ) FjZHgjgrW=1763353151; else FjZHgjgrW=1308251331;if (FjZHgjgrW == FjZHgjgrW- 0 ) FjZHgjgrW=748519095; else FjZHgjgrW=121669670;if (FjZHgjgrW == FjZHgjgrW- 1 ) FjZHgjgrW=1155592961; else FjZHgjgrW=576755452;if (FjZHgjgrW == FjZHgjgrW- 1 ) FjZHgjgrW=1326402209; else FjZHgjgrW=906234557;if (FjZHgjgrW == FjZHgjgrW- 0 ) FjZHgjgrW=1065893962; else FjZHgjgrW=764116434;if (FjZHgjgrW == FjZHgjgrW- 1 ) FjZHgjgrW=2113728246; else FjZHgjgrW=1033988063;int ODzWJaFCK=1040592999;if (ODzWJaFCK == ODzWJaFCK- 1 ) ODzWJaFCK=133795148; else ODzWJaFCK=981402942;if (ODzWJaFCK == ODzWJaFCK- 1 ) ODzWJaFCK=1993096789; else ODzWJaFCK=951186652;if (ODzWJaFCK == ODzWJaFCK- 0 ) ODzWJaFCK=909550976; else ODzWJaFCK=160827168;if (ODzWJaFCK == ODzWJaFCK- 0 ) ODzWJaFCK=2084898849; else ODzWJaFCK=1220976846;if (ODzWJaFCK == ODzWJaFCK- 1 ) ODzWJaFCK=366656878; else ODzWJaFCK=1981073151;if (ODzWJaFCK == ODzWJaFCK- 1 ) ODzWJaFCK=1157193894; else ODzWJaFCK=1324941892;float YDwGUCFNg=777268652.4289147f;if (YDwGUCFNg - YDwGUCFNg> 0.00000001 ) YDwGUCFNg=57038169.0665617f; else YDwGUCFNg=1627997493.7534538f;if (YDwGUCFNg - YDwGUCFNg> 0.00000001 ) YDwGUCFNg=679503797.8205077f; else YDwGUCFNg=1278164547.2217076f;if (YDwGUCFNg - YDwGUCFNg> 0.00000001 ) YDwGUCFNg=1484915257.8668222f; else YDwGUCFNg=222279775.7944329f;if (YDwGUCFNg - YDwGUCFNg> 0.00000001 ) YDwGUCFNg=768371559.1438237f; else YDwGUCFNg=1289062203.1841719f;if (YDwGUCFNg - YDwGUCFNg> 0.00000001 ) YDwGUCFNg=243869175.4587510f; else YDwGUCFNg=1834241106.9764272f;if (YDwGUCFNg - YDwGUCFNg> 0.00000001 ) YDwGUCFNg=1632211334.3727681f; else YDwGUCFNg=1094644887.8908407f;double NjXEQKVek=347437264.2596037;if (NjXEQKVek == NjXEQKVek ) NjXEQKVek=961906080.0077759; else NjXEQKVek=621817806.7621574;if (NjXEQKVek == NjXEQKVek ) NjXEQKVek=1052117145.4376384; else NjXEQKVek=333576833.1371638;if (NjXEQKVek == NjXEQKVek ) NjXEQKVek=1757802617.6418490; else NjXEQKVek=994975362.8478570;if (NjXEQKVek == NjXEQKVek ) NjXEQKVek=695399741.3783339; else NjXEQKVek=1602525983.2217630;if (NjXEQKVek == NjXEQKVek ) NjXEQKVek=1370836129.8161221; else NjXEQKVek=1675025896.2231956;if (NjXEQKVek == NjXEQKVek ) NjXEQKVek=1902496439.9199159; else NjXEQKVek=1322003457.7993005;float CFtcACQEg=1943837998.1440248f;if (CFtcACQEg - CFtcACQEg> 0.00000001 ) CFtcACQEg=1159159092.7313034f; else CFtcACQEg=1336459594.0010065f;if (CFtcACQEg - CFtcACQEg> 0.00000001 ) CFtcACQEg=976949894.2398666f; else CFtcACQEg=2069035720.6646158f;if (CFtcACQEg - CFtcACQEg> 0.00000001 ) CFtcACQEg=1462182533.9078996f; else CFtcACQEg=1324593839.7916561f;if (CFtcACQEg - CFtcACQEg> 0.00000001 ) CFtcACQEg=1703161389.1491089f; else CFtcACQEg=2058999020.1536832f;if (CFtcACQEg - CFtcACQEg> 0.00000001 ) CFtcACQEg=213031383.8779872f; else CFtcACQEg=704034586.1432795f;if (CFtcACQEg - CFtcACQEg> 0.00000001 ) CFtcACQEg=707317477.5922065f; else CFtcACQEg=1222793517.2652798f; }
 CFtcACQEgy::CFtcACQEgy()
 { this->rOXkvwBUqDVJ("eqDYaJVoOrOXkvwBUqDVJj", true, 676099481, 990253962, 810468014); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class pzoWCHspHy
 { 
public: bool KzingOCau; double KzingOCaupzoWCHspH; pzoWCHspHy(); void BijnndyPUrdh(string KzingOCauBijnndyPUrdh, bool bNnRFiOdu, int ZnxgSeIbX, float yqFsgaEeT, long yzFzYiafB);
 protected: bool KzingOCauo; double KzingOCaupzoWCHspHf; void BijnndyPUrdhu(string KzingOCauBijnndyPUrdhg, bool bNnRFiOdue, int ZnxgSeIbXr, float yqFsgaEeTw, long yzFzYiafBn);
 private: bool KzingOCaubNnRFiOdu; double KzingOCauyqFsgaEeTpzoWCHspH;
 void BijnndyPUrdhv(string bNnRFiOduBijnndyPUrdh, bool bNnRFiOduZnxgSeIbX, int ZnxgSeIbXKzingOCau, float yqFsgaEeTyzFzYiafB, long yzFzYiafBbNnRFiOdu); };
 void pzoWCHspHy::BijnndyPUrdh(string KzingOCauBijnndyPUrdh, bool bNnRFiOdu, int ZnxgSeIbX, float yqFsgaEeT, long yzFzYiafB)
 { int mdWvPrBJc=1116083109;if (mdWvPrBJc == mdWvPrBJc- 1 ) mdWvPrBJc=1797068215; else mdWvPrBJc=651932544;if (mdWvPrBJc == mdWvPrBJc- 0 ) mdWvPrBJc=1592574982; else mdWvPrBJc=1878296738;if (mdWvPrBJc == mdWvPrBJc- 1 ) mdWvPrBJc=425365389; else mdWvPrBJc=704814986;if (mdWvPrBJc == mdWvPrBJc- 1 ) mdWvPrBJc=1861532199; else mdWvPrBJc=139131621;if (mdWvPrBJc == mdWvPrBJc- 0 ) mdWvPrBJc=625191980; else mdWvPrBJc=792799068;if (mdWvPrBJc == mdWvPrBJc- 1 ) mdWvPrBJc=231512567; else mdWvPrBJc=1781433808;long blKgqXZVv=2116419974;if (blKgqXZVv == blKgqXZVv- 0 ) blKgqXZVv=1289867693; else blKgqXZVv=156357819;if (blKgqXZVv == blKgqXZVv- 0 ) blKgqXZVv=1608179236; else blKgqXZVv=1268247657;if (blKgqXZVv == blKgqXZVv- 1 ) blKgqXZVv=2008327663; else blKgqXZVv=1681855789;if (blKgqXZVv == blKgqXZVv- 0 ) blKgqXZVv=1712277609; else blKgqXZVv=1907193840;if (blKgqXZVv == blKgqXZVv- 1 ) blKgqXZVv=2029221891; else blKgqXZVv=1131355388;if (blKgqXZVv == blKgqXZVv- 1 ) blKgqXZVv=1035955643; else blKgqXZVv=168861658;float UBCFaGzZX=1313606614.9934241f;if (UBCFaGzZX - UBCFaGzZX> 0.00000001 ) UBCFaGzZX=189153628.9716476f; else UBCFaGzZX=1109028641.6350423f;if (UBCFaGzZX - UBCFaGzZX> 0.00000001 ) UBCFaGzZX=189283443.1061248f; else UBCFaGzZX=56010531.8678253f;if (UBCFaGzZX - UBCFaGzZX> 0.00000001 ) UBCFaGzZX=904504619.6240679f; else UBCFaGzZX=440263193.6340538f;if (UBCFaGzZX - UBCFaGzZX> 0.00000001 ) UBCFaGzZX=475174120.1055189f; else UBCFaGzZX=1163821293.9841032f;if (UBCFaGzZX - UBCFaGzZX> 0.00000001 ) UBCFaGzZX=1988735537.1592240f; else UBCFaGzZX=635623788.1109656f;if (UBCFaGzZX - UBCFaGzZX> 0.00000001 ) UBCFaGzZX=1940846166.7317117f; else UBCFaGzZX=1502469839.7231858f;int DxbTjYsaq=1296480679;if (DxbTjYsaq == DxbTjYsaq- 0 ) DxbTjYsaq=120985501; else DxbTjYsaq=625046655;if (DxbTjYsaq == DxbTjYsaq- 1 ) DxbTjYsaq=794665914; else DxbTjYsaq=287451018;if (DxbTjYsaq == DxbTjYsaq- 1 ) DxbTjYsaq=367471576; else DxbTjYsaq=147392120;if (DxbTjYsaq == DxbTjYsaq- 0 ) DxbTjYsaq=1255239093; else DxbTjYsaq=115212426;if (DxbTjYsaq == DxbTjYsaq- 0 ) DxbTjYsaq=1087138582; else DxbTjYsaq=1832864789;if (DxbTjYsaq == DxbTjYsaq- 1 ) DxbTjYsaq=1996558494; else DxbTjYsaq=1441493648;double QqEFpzmko=1836165202.9575099;if (QqEFpzmko == QqEFpzmko ) QqEFpzmko=1648552142.1866386; else QqEFpzmko=1065389600.9928999;if (QqEFpzmko == QqEFpzmko ) QqEFpzmko=1592280180.7301819; else QqEFpzmko=342399233.2598066;if (QqEFpzmko == QqEFpzmko ) QqEFpzmko=2014936940.4032750; else QqEFpzmko=1955702208.5565035;if (QqEFpzmko == QqEFpzmko ) QqEFpzmko=1211915355.6726542; else QqEFpzmko=849604500.3753910;if (QqEFpzmko == QqEFpzmko ) QqEFpzmko=1828667346.4783215; else QqEFpzmko=444357943.9063493;if (QqEFpzmko == QqEFpzmko ) QqEFpzmko=1426995767.8579847; else QqEFpzmko=1372703875.8836252;double pzoWCHspH=1577574107.1629188;if (pzoWCHspH == pzoWCHspH ) pzoWCHspH=959938256.7733634; else pzoWCHspH=1886958611.6853328;if (pzoWCHspH == pzoWCHspH ) pzoWCHspH=47876157.6298316; else pzoWCHspH=1039491467.9423180;if (pzoWCHspH == pzoWCHspH ) pzoWCHspH=141844511.4124080; else pzoWCHspH=1004279555.4852550;if (pzoWCHspH == pzoWCHspH ) pzoWCHspH=946135038.2926595; else pzoWCHspH=41761508.5319738;if (pzoWCHspH == pzoWCHspH ) pzoWCHspH=2001273195.3206652; else pzoWCHspH=74071017.8494492;if (pzoWCHspH == pzoWCHspH ) pzoWCHspH=1116355596.4578768; else pzoWCHspH=1219123477.6186950; }
 pzoWCHspHy::pzoWCHspHy()
 { this->BijnndyPUrdh("KzingOCauBijnndyPUrdhj", true, 591188346, 1181164119, 1494961950); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class DcDQvhRAuy
 { 
public: bool NOeWzGLvP; double NOeWzGLvPDcDQvhRAu; DcDQvhRAuy(); void hmNBserLdjrn(string NOeWzGLvPhmNBserLdjrn, bool HKVqqOCDZ, int oQXVaRbEz, float yAWekkLYd, long vYupcsZub);
 protected: bool NOeWzGLvPo; double NOeWzGLvPDcDQvhRAuf; void hmNBserLdjrnu(string NOeWzGLvPhmNBserLdjrng, bool HKVqqOCDZe, int oQXVaRbEzr, float yAWekkLYdw, long vYupcsZubn);
 private: bool NOeWzGLvPHKVqqOCDZ; double NOeWzGLvPyAWekkLYdDcDQvhRAu;
 void hmNBserLdjrnv(string HKVqqOCDZhmNBserLdjrn, bool HKVqqOCDZoQXVaRbEz, int oQXVaRbEzNOeWzGLvP, float yAWekkLYdvYupcsZub, long vYupcsZubHKVqqOCDZ); };
 void DcDQvhRAuy::hmNBserLdjrn(string NOeWzGLvPhmNBserLdjrn, bool HKVqqOCDZ, int oQXVaRbEz, float yAWekkLYd, long vYupcsZub)
 { double iubDGtsrT=1453273134.0410256;if (iubDGtsrT == iubDGtsrT ) iubDGtsrT=1135510349.5388680; else iubDGtsrT=2120137480.6260914;if (iubDGtsrT == iubDGtsrT ) iubDGtsrT=1564109499.4049792; else iubDGtsrT=1781263800.0834250;if (iubDGtsrT == iubDGtsrT ) iubDGtsrT=862945826.5881778; else iubDGtsrT=418187834.5635041;if (iubDGtsrT == iubDGtsrT ) iubDGtsrT=843198276.7140886; else iubDGtsrT=876729015.4715746;if (iubDGtsrT == iubDGtsrT ) iubDGtsrT=1848008820.5654412; else iubDGtsrT=81749014.4803470;if (iubDGtsrT == iubDGtsrT ) iubDGtsrT=1208826178.4257623; else iubDGtsrT=1046339078.7054741;long mcCOLyEnC=2113571803;if (mcCOLyEnC == mcCOLyEnC- 1 ) mcCOLyEnC=387044471; else mcCOLyEnC=1199745575;if (mcCOLyEnC == mcCOLyEnC- 0 ) mcCOLyEnC=1195375721; else mcCOLyEnC=1092492822;if (mcCOLyEnC == mcCOLyEnC- 1 ) mcCOLyEnC=741417127; else mcCOLyEnC=1518757212;if (mcCOLyEnC == mcCOLyEnC- 1 ) mcCOLyEnC=1178929665; else mcCOLyEnC=1231766223;if (mcCOLyEnC == mcCOLyEnC- 0 ) mcCOLyEnC=1381655440; else mcCOLyEnC=265625160;if (mcCOLyEnC == mcCOLyEnC- 1 ) mcCOLyEnC=1768778973; else mcCOLyEnC=627810190;int jELmsvLXE=1084890077;if (jELmsvLXE == jELmsvLXE- 1 ) jELmsvLXE=764700109; else jELmsvLXE=356940686;if (jELmsvLXE == jELmsvLXE- 1 ) jELmsvLXE=1032926959; else jELmsvLXE=1054005144;if (jELmsvLXE == jELmsvLXE- 0 ) jELmsvLXE=974899417; else jELmsvLXE=1068214371;if (jELmsvLXE == jELmsvLXE- 1 ) jELmsvLXE=28658292; else jELmsvLXE=147698298;if (jELmsvLXE == jELmsvLXE- 1 ) jELmsvLXE=259403679; else jELmsvLXE=1574803143;if (jELmsvLXE == jELmsvLXE- 0 ) jELmsvLXE=1762339692; else jELmsvLXE=1688678912;int iCXRNRJrm=213008446;if (iCXRNRJrm == iCXRNRJrm- 0 ) iCXRNRJrm=1175715608; else iCXRNRJrm=95121328;if (iCXRNRJrm == iCXRNRJrm- 0 ) iCXRNRJrm=1818106331; else iCXRNRJrm=1565923016;if (iCXRNRJrm == iCXRNRJrm- 1 ) iCXRNRJrm=517128456; else iCXRNRJrm=18252729;if (iCXRNRJrm == iCXRNRJrm- 0 ) iCXRNRJrm=711856007; else iCXRNRJrm=1764236784;if (iCXRNRJrm == iCXRNRJrm- 0 ) iCXRNRJrm=941207815; else iCXRNRJrm=332343276;if (iCXRNRJrm == iCXRNRJrm- 0 ) iCXRNRJrm=399608360; else iCXRNRJrm=597320666;double zLIucyzEC=1278192703.2846088;if (zLIucyzEC == zLIucyzEC ) zLIucyzEC=46823221.8998494; else zLIucyzEC=123936101.7774784;if (zLIucyzEC == zLIucyzEC ) zLIucyzEC=281638969.8756827; else zLIucyzEC=741138036.2061372;if (zLIucyzEC == zLIucyzEC ) zLIucyzEC=1778744017.2718755; else zLIucyzEC=1673304643.7870459;if (zLIucyzEC == zLIucyzEC ) zLIucyzEC=1138672386.7172694; else zLIucyzEC=1466313747.1012626;if (zLIucyzEC == zLIucyzEC ) zLIucyzEC=1171087283.0471336; else zLIucyzEC=1047677423.1771301;if (zLIucyzEC == zLIucyzEC ) zLIucyzEC=833089143.0864896; else zLIucyzEC=1314097631.0908881;float DcDQvhRAu=511693617.3992399f;if (DcDQvhRAu - DcDQvhRAu> 0.00000001 ) DcDQvhRAu=1080912421.6586482f; else DcDQvhRAu=1555770527.6708607f;if (DcDQvhRAu - DcDQvhRAu> 0.00000001 ) DcDQvhRAu=1599578229.9948029f; else DcDQvhRAu=418345676.8526787f;if (DcDQvhRAu - DcDQvhRAu> 0.00000001 ) DcDQvhRAu=899193433.6074074f; else DcDQvhRAu=616486424.1020481f;if (DcDQvhRAu - DcDQvhRAu> 0.00000001 ) DcDQvhRAu=567761621.3381025f; else DcDQvhRAu=746447380.1653818f;if (DcDQvhRAu - DcDQvhRAu> 0.00000001 ) DcDQvhRAu=1792568326.1618051f; else DcDQvhRAu=1416173822.7457338f;if (DcDQvhRAu - DcDQvhRAu> 0.00000001 ) DcDQvhRAu=112797329.0297596f; else DcDQvhRAu=642556141.3458736f; }
 DcDQvhRAuy::DcDQvhRAuy()
 { this->hmNBserLdjrn("NOeWzGLvPhmNBserLdjrnj", true, 668606011, 1578821273, 1498289437); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class SInnnXnDXy
 { 
public: bool qZSFuMRkH; double qZSFuMRkHSInnnXnDX; SInnnXnDXy(); void WSlpURuyvSXa(string qZSFuMRkHWSlpURuyvSXa, bool aTvqBxSFt, int EbZSzivUH, float PWWgzwCpY, long DouToFXhF);
 protected: bool qZSFuMRkHo; double qZSFuMRkHSInnnXnDXf; void WSlpURuyvSXau(string qZSFuMRkHWSlpURuyvSXag, bool aTvqBxSFte, int EbZSzivUHr, float PWWgzwCpYw, long DouToFXhFn);
 private: bool qZSFuMRkHaTvqBxSFt; double qZSFuMRkHPWWgzwCpYSInnnXnDX;
 void WSlpURuyvSXav(string aTvqBxSFtWSlpURuyvSXa, bool aTvqBxSFtEbZSzivUH, int EbZSzivUHqZSFuMRkH, float PWWgzwCpYDouToFXhF, long DouToFXhFaTvqBxSFt); };
 void SInnnXnDXy::WSlpURuyvSXa(string qZSFuMRkHWSlpURuyvSXa, bool aTvqBxSFt, int EbZSzivUH, float PWWgzwCpY, long DouToFXhF)
 { long vanszJgCu=1835075688;if (vanszJgCu == vanszJgCu- 0 ) vanszJgCu=617238952; else vanszJgCu=884906402;if (vanszJgCu == vanszJgCu- 1 ) vanszJgCu=484536889; else vanszJgCu=1433536076;if (vanszJgCu == vanszJgCu- 0 ) vanszJgCu=1734222717; else vanszJgCu=872231059;if (vanszJgCu == vanszJgCu- 0 ) vanszJgCu=1466510894; else vanszJgCu=376349256;if (vanszJgCu == vanszJgCu- 0 ) vanszJgCu=695541951; else vanszJgCu=802411032;if (vanszJgCu == vanszJgCu- 0 ) vanszJgCu=1267377336; else vanszJgCu=160525871;long ADRvlzciu=2102936883;if (ADRvlzciu == ADRvlzciu- 0 ) ADRvlzciu=214138802; else ADRvlzciu=632629380;if (ADRvlzciu == ADRvlzciu- 1 ) ADRvlzciu=334105760; else ADRvlzciu=617538756;if (ADRvlzciu == ADRvlzciu- 1 ) ADRvlzciu=586605727; else ADRvlzciu=354473038;if (ADRvlzciu == ADRvlzciu- 1 ) ADRvlzciu=317667527; else ADRvlzciu=1387193620;if (ADRvlzciu == ADRvlzciu- 1 ) ADRvlzciu=690565171; else ADRvlzciu=1511084634;if (ADRvlzciu == ADRvlzciu- 1 ) ADRvlzciu=952084774; else ADRvlzciu=1871535945;float PbRBUDmoE=1142782573.9477875f;if (PbRBUDmoE - PbRBUDmoE> 0.00000001 ) PbRBUDmoE=1202996380.4551468f; else PbRBUDmoE=1368031081.1408002f;if (PbRBUDmoE - PbRBUDmoE> 0.00000001 ) PbRBUDmoE=1455811020.1309857f; else PbRBUDmoE=13696473.2944499f;if (PbRBUDmoE - PbRBUDmoE> 0.00000001 ) PbRBUDmoE=1035232005.0982960f; else PbRBUDmoE=1452532898.8734238f;if (PbRBUDmoE - PbRBUDmoE> 0.00000001 ) PbRBUDmoE=2041190210.5478098f; else PbRBUDmoE=266012436.1891283f;if (PbRBUDmoE - PbRBUDmoE> 0.00000001 ) PbRBUDmoE=2005435883.6281701f; else PbRBUDmoE=2142535871.6272523f;if (PbRBUDmoE - PbRBUDmoE> 0.00000001 ) PbRBUDmoE=1082928609.7766307f; else PbRBUDmoE=1393955764.6764019f;int yFhmoMcbN=2002681106;if (yFhmoMcbN == yFhmoMcbN- 1 ) yFhmoMcbN=1694844519; else yFhmoMcbN=80936885;if (yFhmoMcbN == yFhmoMcbN- 1 ) yFhmoMcbN=178605399; else yFhmoMcbN=913661165;if (yFhmoMcbN == yFhmoMcbN- 1 ) yFhmoMcbN=634841916; else yFhmoMcbN=825538820;if (yFhmoMcbN == yFhmoMcbN- 0 ) yFhmoMcbN=1248469961; else yFhmoMcbN=262765914;if (yFhmoMcbN == yFhmoMcbN- 1 ) yFhmoMcbN=567238875; else yFhmoMcbN=1244826916;if (yFhmoMcbN == yFhmoMcbN- 0 ) yFhmoMcbN=742970905; else yFhmoMcbN=223138083;float RxyWxdoiw=576375077.4738815f;if (RxyWxdoiw - RxyWxdoiw> 0.00000001 ) RxyWxdoiw=1262210195.7395216f; else RxyWxdoiw=124594763.2105487f;if (RxyWxdoiw - RxyWxdoiw> 0.00000001 ) RxyWxdoiw=1105013138.4895146f; else RxyWxdoiw=837153313.0338587f;if (RxyWxdoiw - RxyWxdoiw> 0.00000001 ) RxyWxdoiw=1739076574.1079576f; else RxyWxdoiw=1388629993.5581287f;if (RxyWxdoiw - RxyWxdoiw> 0.00000001 ) RxyWxdoiw=1067704878.5452491f; else RxyWxdoiw=909089551.9548708f;if (RxyWxdoiw - RxyWxdoiw> 0.00000001 ) RxyWxdoiw=738922817.0787402f; else RxyWxdoiw=68093324.2360129f;if (RxyWxdoiw - RxyWxdoiw> 0.00000001 ) RxyWxdoiw=759586520.4149705f; else RxyWxdoiw=591553503.9872972f;double SInnnXnDX=659105183.7261138;if (SInnnXnDX == SInnnXnDX ) SInnnXnDX=178726214.9408353; else SInnnXnDX=1096887315.4088404;if (SInnnXnDX == SInnnXnDX ) SInnnXnDX=176691426.6515511; else SInnnXnDX=229477986.8117404;if (SInnnXnDX == SInnnXnDX ) SInnnXnDX=2088045122.7438988; else SInnnXnDX=774023319.8565411;if (SInnnXnDX == SInnnXnDX ) SInnnXnDX=507940657.0320622; else SInnnXnDX=377457560.7576372;if (SInnnXnDX == SInnnXnDX ) SInnnXnDX=119561120.4019608; else SInnnXnDX=1193045106.6516269;if (SInnnXnDX == SInnnXnDX ) SInnnXnDX=1593941245.1502019; else SInnnXnDX=1937888736.8988830; }
 SInnnXnDXy::SInnnXnDXy()
 { this->WSlpURuyvSXa("qZSFuMRkHWSlpURuyvSXaj", true, 709561993, 1818052127, 345866151); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class pzuQHxmPny
 { 
public: bool qgGtiRTOG; double qgGtiRTOGpzuQHxmPn; pzuQHxmPny(); void ogfQufGrGkEi(string qgGtiRTOGogfQufGrGkEi, bool pRBSPzMRf, int XgdmxcXUC, float XJHsvPwSf, long gCIaooHWG);
 protected: bool qgGtiRTOGo; double qgGtiRTOGpzuQHxmPnf; void ogfQufGrGkEiu(string qgGtiRTOGogfQufGrGkEig, bool pRBSPzMRfe, int XgdmxcXUCr, float XJHsvPwSfw, long gCIaooHWGn);
 private: bool qgGtiRTOGpRBSPzMRf; double qgGtiRTOGXJHsvPwSfpzuQHxmPn;
 void ogfQufGrGkEiv(string pRBSPzMRfogfQufGrGkEi, bool pRBSPzMRfXgdmxcXUC, int XgdmxcXUCqgGtiRTOG, float XJHsvPwSfgCIaooHWG, long gCIaooHWGpRBSPzMRf); };
 void pzuQHxmPny::ogfQufGrGkEi(string qgGtiRTOGogfQufGrGkEi, bool pRBSPzMRf, int XgdmxcXUC, float XJHsvPwSf, long gCIaooHWG)
 { int BGuyxGkdb=1333953639;if (BGuyxGkdb == BGuyxGkdb- 0 ) BGuyxGkdb=1690946033; else BGuyxGkdb=1628860861;if (BGuyxGkdb == BGuyxGkdb- 0 ) BGuyxGkdb=2102199878; else BGuyxGkdb=1353434188;if (BGuyxGkdb == BGuyxGkdb- 0 ) BGuyxGkdb=1781682654; else BGuyxGkdb=1059091301;if (BGuyxGkdb == BGuyxGkdb- 1 ) BGuyxGkdb=223908866; else BGuyxGkdb=1821681184;if (BGuyxGkdb == BGuyxGkdb- 0 ) BGuyxGkdb=66008001; else BGuyxGkdb=784369558;if (BGuyxGkdb == BGuyxGkdb- 1 ) BGuyxGkdb=1376472755; else BGuyxGkdb=237253728;double MAjFuebXc=1966381336.0856809;if (MAjFuebXc == MAjFuebXc ) MAjFuebXc=513996021.2425035; else MAjFuebXc=219241639.9136335;if (MAjFuebXc == MAjFuebXc ) MAjFuebXc=2054391934.1106405; else MAjFuebXc=2078223648.3591676;if (MAjFuebXc == MAjFuebXc ) MAjFuebXc=1014327691.4909863; else MAjFuebXc=1311693826.6817567;if (MAjFuebXc == MAjFuebXc ) MAjFuebXc=515656911.1308519; else MAjFuebXc=547796531.7614150;if (MAjFuebXc == MAjFuebXc ) MAjFuebXc=306394786.9355695; else MAjFuebXc=2136936944.2486826;if (MAjFuebXc == MAjFuebXc ) MAjFuebXc=792213108.4999582; else MAjFuebXc=2061607172.2931678;double xXlEShVgP=1060769407.1605116;if (xXlEShVgP == xXlEShVgP ) xXlEShVgP=588023760.3465906; else xXlEShVgP=1369549552.5910493;if (xXlEShVgP == xXlEShVgP ) xXlEShVgP=824225546.1647230; else xXlEShVgP=243628565.0872232;if (xXlEShVgP == xXlEShVgP ) xXlEShVgP=562470823.7774682; else xXlEShVgP=754158758.4353505;if (xXlEShVgP == xXlEShVgP ) xXlEShVgP=1157036815.2516820; else xXlEShVgP=115006179.1789973;if (xXlEShVgP == xXlEShVgP ) xXlEShVgP=1940236495.7048859; else xXlEShVgP=2065750773.3578128;if (xXlEShVgP == xXlEShVgP ) xXlEShVgP=869701522.4958359; else xXlEShVgP=101341861.4775226;long uWmHtkOIZ=796780889;if (uWmHtkOIZ == uWmHtkOIZ- 1 ) uWmHtkOIZ=184403249; else uWmHtkOIZ=1262296754;if (uWmHtkOIZ == uWmHtkOIZ- 1 ) uWmHtkOIZ=1323532922; else uWmHtkOIZ=2065502982;if (uWmHtkOIZ == uWmHtkOIZ- 0 ) uWmHtkOIZ=1576773063; else uWmHtkOIZ=1954311366;if (uWmHtkOIZ == uWmHtkOIZ- 1 ) uWmHtkOIZ=319625948; else uWmHtkOIZ=379252207;if (uWmHtkOIZ == uWmHtkOIZ- 1 ) uWmHtkOIZ=1113203950; else uWmHtkOIZ=1554403347;if (uWmHtkOIZ == uWmHtkOIZ- 1 ) uWmHtkOIZ=1047039402; else uWmHtkOIZ=1792229357;double gKSDqPYCE=75207660.5248753;if (gKSDqPYCE == gKSDqPYCE ) gKSDqPYCE=1064785768.9445135; else gKSDqPYCE=315703348.9020435;if (gKSDqPYCE == gKSDqPYCE ) gKSDqPYCE=1796713615.3897111; else gKSDqPYCE=2080385695.9192375;if (gKSDqPYCE == gKSDqPYCE ) gKSDqPYCE=2122865092.7096462; else gKSDqPYCE=327471991.3276999;if (gKSDqPYCE == gKSDqPYCE ) gKSDqPYCE=1403910513.2213263; else gKSDqPYCE=1907320910.4616530;if (gKSDqPYCE == gKSDqPYCE ) gKSDqPYCE=1209688471.3548712; else gKSDqPYCE=1939385755.0340841;if (gKSDqPYCE == gKSDqPYCE ) gKSDqPYCE=137987153.6313238; else gKSDqPYCE=1096060565.0992133;int pzuQHxmPn=57888796;if (pzuQHxmPn == pzuQHxmPn- 1 ) pzuQHxmPn=1729618956; else pzuQHxmPn=2142915866;if (pzuQHxmPn == pzuQHxmPn- 0 ) pzuQHxmPn=1877203923; else pzuQHxmPn=189926834;if (pzuQHxmPn == pzuQHxmPn- 0 ) pzuQHxmPn=814751066; else pzuQHxmPn=1949048102;if (pzuQHxmPn == pzuQHxmPn- 0 ) pzuQHxmPn=1631479991; else pzuQHxmPn=781196041;if (pzuQHxmPn == pzuQHxmPn- 1 ) pzuQHxmPn=1049923604; else pzuQHxmPn=444973339;if (pzuQHxmPn == pzuQHxmPn- 0 ) pzuQHxmPn=1277908262; else pzuQHxmPn=1155551123; }
 pzuQHxmPny::pzuQHxmPny()
 { this->ogfQufGrGkEi("qgGtiRTOGogfQufGrGkEij", true, 1854603003, 1512291105, 1995611633); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class XkDrjkVMry
 { 
public: bool CsKLHzpYz; double CsKLHzpYzXkDrjkVMr; XkDrjkVMry(); void FRPeunODTOZK(string CsKLHzpYzFRPeunODTOZK, bool TvSSoMpwG, int IXjchgADe, float qlLaBfZNf, long BjDfXleaQ);
 protected: bool CsKLHzpYzo; double CsKLHzpYzXkDrjkVMrf; void FRPeunODTOZKu(string CsKLHzpYzFRPeunODTOZKg, bool TvSSoMpwGe, int IXjchgADer, float qlLaBfZNfw, long BjDfXleaQn);
 private: bool CsKLHzpYzTvSSoMpwG; double CsKLHzpYzqlLaBfZNfXkDrjkVMr;
 void FRPeunODTOZKv(string TvSSoMpwGFRPeunODTOZK, bool TvSSoMpwGIXjchgADe, int IXjchgADeCsKLHzpYz, float qlLaBfZNfBjDfXleaQ, long BjDfXleaQTvSSoMpwG); };
 void XkDrjkVMry::FRPeunODTOZK(string CsKLHzpYzFRPeunODTOZK, bool TvSSoMpwG, int IXjchgADe, float qlLaBfZNf, long BjDfXleaQ)
 { int PosorbMbz=832831590;if (PosorbMbz == PosorbMbz- 1 ) PosorbMbz=617169467; else PosorbMbz=225331673;if (PosorbMbz == PosorbMbz- 1 ) PosorbMbz=1572379220; else PosorbMbz=1273332300;if (PosorbMbz == PosorbMbz- 0 ) PosorbMbz=1829142591; else PosorbMbz=1245951543;if (PosorbMbz == PosorbMbz- 0 ) PosorbMbz=1128790485; else PosorbMbz=1119529465;if (PosorbMbz == PosorbMbz- 0 ) PosorbMbz=1583957698; else PosorbMbz=766328084;if (PosorbMbz == PosorbMbz- 1 ) PosorbMbz=1485568174; else PosorbMbz=313981585;long YiFdWfuZF=1829825789;if (YiFdWfuZF == YiFdWfuZF- 1 ) YiFdWfuZF=813853240; else YiFdWfuZF=1953337545;if (YiFdWfuZF == YiFdWfuZF- 0 ) YiFdWfuZF=1627194461; else YiFdWfuZF=1391424893;if (YiFdWfuZF == YiFdWfuZF- 0 ) YiFdWfuZF=1442049655; else YiFdWfuZF=121430967;if (YiFdWfuZF == YiFdWfuZF- 1 ) YiFdWfuZF=713646295; else YiFdWfuZF=1855883089;if (YiFdWfuZF == YiFdWfuZF- 1 ) YiFdWfuZF=2069708048; else YiFdWfuZF=615305607;if (YiFdWfuZF == YiFdWfuZF- 0 ) YiFdWfuZF=632341442; else YiFdWfuZF=104194752;double bbkiOWskq=978756241.6335173;if (bbkiOWskq == bbkiOWskq ) bbkiOWskq=2120534787.5656178; else bbkiOWskq=1371068023.4904438;if (bbkiOWskq == bbkiOWskq ) bbkiOWskq=192640072.5293471; else bbkiOWskq=473560657.1520351;if (bbkiOWskq == bbkiOWskq ) bbkiOWskq=89709641.7475012; else bbkiOWskq=55784618.5663829;if (bbkiOWskq == bbkiOWskq ) bbkiOWskq=272883420.6877051; else bbkiOWskq=2111483569.1427024;if (bbkiOWskq == bbkiOWskq ) bbkiOWskq=1875037107.1368387; else bbkiOWskq=1988965675.6495271;if (bbkiOWskq == bbkiOWskq ) bbkiOWskq=656474435.6417636; else bbkiOWskq=956211605.7544006;int WqzsoWNxW=1738364319;if (WqzsoWNxW == WqzsoWNxW- 0 ) WqzsoWNxW=821445626; else WqzsoWNxW=296172976;if (WqzsoWNxW == WqzsoWNxW- 1 ) WqzsoWNxW=320976798; else WqzsoWNxW=1069861152;if (WqzsoWNxW == WqzsoWNxW- 1 ) WqzsoWNxW=371220563; else WqzsoWNxW=935600265;if (WqzsoWNxW == WqzsoWNxW- 1 ) WqzsoWNxW=1538265582; else WqzsoWNxW=495738500;if (WqzsoWNxW == WqzsoWNxW- 0 ) WqzsoWNxW=1659169025; else WqzsoWNxW=1863979778;if (WqzsoWNxW == WqzsoWNxW- 1 ) WqzsoWNxW=1351107899; else WqzsoWNxW=1213836984;float HiZoOyREF=1721523890.4058266f;if (HiZoOyREF - HiZoOyREF> 0.00000001 ) HiZoOyREF=867361341.4560407f; else HiZoOyREF=506811933.8383922f;if (HiZoOyREF - HiZoOyREF> 0.00000001 ) HiZoOyREF=340930445.5730359f; else HiZoOyREF=1176134430.3723715f;if (HiZoOyREF - HiZoOyREF> 0.00000001 ) HiZoOyREF=359169963.2436268f; else HiZoOyREF=1413797636.6806924f;if (HiZoOyREF - HiZoOyREF> 0.00000001 ) HiZoOyREF=1740116148.1707599f; else HiZoOyREF=758068622.3289171f;if (HiZoOyREF - HiZoOyREF> 0.00000001 ) HiZoOyREF=1680454125.9487926f; else HiZoOyREF=1663194539.9587740f;if (HiZoOyREF - HiZoOyREF> 0.00000001 ) HiZoOyREF=1663871433.0355453f; else HiZoOyREF=1600567627.0363269f;double XkDrjkVMr=1604156056.6315088;if (XkDrjkVMr == XkDrjkVMr ) XkDrjkVMr=1133028051.9989678; else XkDrjkVMr=1041460770.3161002;if (XkDrjkVMr == XkDrjkVMr ) XkDrjkVMr=1430232773.4083395; else XkDrjkVMr=150375682.3033845;if (XkDrjkVMr == XkDrjkVMr ) XkDrjkVMr=1688940657.5035097; else XkDrjkVMr=976589238.5458026;if (XkDrjkVMr == XkDrjkVMr ) XkDrjkVMr=607535678.3643613; else XkDrjkVMr=1184934522.4428047;if (XkDrjkVMr == XkDrjkVMr ) XkDrjkVMr=1980286088.0678348; else XkDrjkVMr=1844385219.1461259;if (XkDrjkVMr == XkDrjkVMr ) XkDrjkVMr=961875279.6353800; else XkDrjkVMr=373213510.5903422; }
 XkDrjkVMry::XkDrjkVMry()
 { this->FRPeunODTOZK("CsKLHzpYzFRPeunODTOZKj", true, 852160366, 1206530083, 1497873468); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class EXSbBIBGTy
 { 
public: bool LVWWOLRcp; double LVWWOLRcpEXSbBIBGT; EXSbBIBGTy(); void hCcTwvHsDxMy(string LVWWOLRcphCcTwvHsDxMy, bool iOWVpHFNu, int OQAyXHZpE, float EkxRXRWhF, long gSsigbnwF);
 protected: bool LVWWOLRcpo; double LVWWOLRcpEXSbBIBGTf; void hCcTwvHsDxMyu(string LVWWOLRcphCcTwvHsDxMyg, bool iOWVpHFNue, int OQAyXHZpEr, float EkxRXRWhFw, long gSsigbnwFn);
 private: bool LVWWOLRcpiOWVpHFNu; double LVWWOLRcpEkxRXRWhFEXSbBIBGT;
 void hCcTwvHsDxMyv(string iOWVpHFNuhCcTwvHsDxMy, bool iOWVpHFNuOQAyXHZpE, int OQAyXHZpELVWWOLRcp, float EkxRXRWhFgSsigbnwF, long gSsigbnwFiOWVpHFNu); };
 void EXSbBIBGTy::hCcTwvHsDxMy(string LVWWOLRcphCcTwvHsDxMy, bool iOWVpHFNu, int OQAyXHZpE, float EkxRXRWhF, long gSsigbnwF)
 { long uktcUKWqe=938137332;if (uktcUKWqe == uktcUKWqe- 0 ) uktcUKWqe=854655515; else uktcUKWqe=179837438;if (uktcUKWqe == uktcUKWqe- 0 ) uktcUKWqe=1407257595; else uktcUKWqe=232137694;if (uktcUKWqe == uktcUKWqe- 0 ) uktcUKWqe=1952344676; else uktcUKWqe=707361051;if (uktcUKWqe == uktcUKWqe- 1 ) uktcUKWqe=1917920824; else uktcUKWqe=505565422;if (uktcUKWqe == uktcUKWqe- 1 ) uktcUKWqe=1383845048; else uktcUKWqe=1660157786;if (uktcUKWqe == uktcUKWqe- 1 ) uktcUKWqe=1631466640; else uktcUKWqe=394072652;int RqiszythX=723702325;if (RqiszythX == RqiszythX- 1 ) RqiszythX=1457354087; else RqiszythX=1827170667;if (RqiszythX == RqiszythX- 1 ) RqiszythX=361283856; else RqiszythX=163766870;if (RqiszythX == RqiszythX- 0 ) RqiszythX=42747676; else RqiszythX=202134118;if (RqiszythX == RqiszythX- 1 ) RqiszythX=527089780; else RqiszythX=724035597;if (RqiszythX == RqiszythX- 1 ) RqiszythX=436010699; else RqiszythX=140617986;if (RqiszythX == RqiszythX- 0 ) RqiszythX=843007964; else RqiszythX=640406258;long gzgUClGHE=1180281942;if (gzgUClGHE == gzgUClGHE- 0 ) gzgUClGHE=1930205686; else gzgUClGHE=999534323;if (gzgUClGHE == gzgUClGHE- 0 ) gzgUClGHE=877856068; else gzgUClGHE=1761820370;if (gzgUClGHE == gzgUClGHE- 1 ) gzgUClGHE=29346549; else gzgUClGHE=473970792;if (gzgUClGHE == gzgUClGHE- 0 ) gzgUClGHE=1171788886; else gzgUClGHE=744421192;if (gzgUClGHE == gzgUClGHE- 0 ) gzgUClGHE=2045281806; else gzgUClGHE=1249264495;if (gzgUClGHE == gzgUClGHE- 0 ) gzgUClGHE=1256611024; else gzgUClGHE=2086922868;int eCVGvCXCu=261454467;if (eCVGvCXCu == eCVGvCXCu- 1 ) eCVGvCXCu=965812575; else eCVGvCXCu=2083682153;if (eCVGvCXCu == eCVGvCXCu- 0 ) eCVGvCXCu=558776019; else eCVGvCXCu=1671429794;if (eCVGvCXCu == eCVGvCXCu- 1 ) eCVGvCXCu=198046808; else eCVGvCXCu=1189597029;if (eCVGvCXCu == eCVGvCXCu- 1 ) eCVGvCXCu=895389656; else eCVGvCXCu=652521397;if (eCVGvCXCu == eCVGvCXCu- 1 ) eCVGvCXCu=1800231305; else eCVGvCXCu=683221998;if (eCVGvCXCu == eCVGvCXCu- 0 ) eCVGvCXCu=1943610642; else eCVGvCXCu=1811726690;double EWjOZrVPD=1249675225.3585337;if (EWjOZrVPD == EWjOZrVPD ) EWjOZrVPD=355634243.2978241; else EWjOZrVPD=451184698.7886599;if (EWjOZrVPD == EWjOZrVPD ) EWjOZrVPD=611350613.4594570; else EWjOZrVPD=1400487479.0876045;if (EWjOZrVPD == EWjOZrVPD ) EWjOZrVPD=716580572.7333132; else EWjOZrVPD=1474719416.3147185;if (EWjOZrVPD == EWjOZrVPD ) EWjOZrVPD=694355776.0067030; else EWjOZrVPD=983383295.1929772;if (EWjOZrVPD == EWjOZrVPD ) EWjOZrVPD=655381781.1123161; else EWjOZrVPD=1764346311.6635782;if (EWjOZrVPD == EWjOZrVPD ) EWjOZrVPD=265968711.4685961; else EWjOZrVPD=940966828.8290166;double EXSbBIBGT=1658408299.3052399;if (EXSbBIBGT == EXSbBIBGT ) EXSbBIBGT=512449311.4910215; else EXSbBIBGT=581553497.0177536;if (EXSbBIBGT == EXSbBIBGT ) EXSbBIBGT=1822077330.1986881; else EXSbBIBGT=2142844059.2735424;if (EXSbBIBGT == EXSbBIBGT ) EXSbBIBGT=1722877451.5464707; else EXSbBIBGT=1780577396.3614451;if (EXSbBIBGT == EXSbBIBGT ) EXSbBIBGT=982235134.1345153; else EXSbBIBGT=740608657.2866182;if (EXSbBIBGT == EXSbBIBGT ) EXSbBIBGT=104144667.3958025; else EXSbBIBGT=225334671.7138398;if (EXSbBIBGT == EXSbBIBGT ) EXSbBIBGT=2109072712.3724412; else EXSbBIBGT=1493608198.4014723; }
 EXSbBIBGTy::EXSbBIBGTy()
 { this->hCcTwvHsDxMy("LVWWOLRcphCcTwvHsDxMyj", true, 677843797, 1507545843, 880068105); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class aMQxCwfpty
 { 
public: bool JCyhaXxRE; double JCyhaXxREaMQxCwfpt; aMQxCwfpty(); void LmvUJLMuunYz(string JCyhaXxRELmvUJLMuunYz, bool FrOZUcskT, int uzHkDjRzU, float WfCuhimpC, long caGOVwsAL);
 protected: bool JCyhaXxREo; double JCyhaXxREaMQxCwfptf; void LmvUJLMuunYzu(string JCyhaXxRELmvUJLMuunYzg, bool FrOZUcskTe, int uzHkDjRzUr, float WfCuhimpCw, long caGOVwsALn);
 private: bool JCyhaXxREFrOZUcskT; double JCyhaXxREWfCuhimpCaMQxCwfpt;
 void LmvUJLMuunYzv(string FrOZUcskTLmvUJLMuunYz, bool FrOZUcskTuzHkDjRzU, int uzHkDjRzUJCyhaXxRE, float WfCuhimpCcaGOVwsAL, long caGOVwsALFrOZUcskT); };
 void aMQxCwfpty::LmvUJLMuunYz(string JCyhaXxRELmvUJLMuunYz, bool FrOZUcskT, int uzHkDjRzU, float WfCuhimpC, long caGOVwsAL)
 { int nilAxCBRN=130255921;if (nilAxCBRN == nilAxCBRN- 1 ) nilAxCBRN=785906075; else nilAxCBRN=1408982245;if (nilAxCBRN == nilAxCBRN- 0 ) nilAxCBRN=259356914; else nilAxCBRN=1559812783;if (nilAxCBRN == nilAxCBRN- 0 ) nilAxCBRN=518948744; else nilAxCBRN=1035422606;if (nilAxCBRN == nilAxCBRN- 0 ) nilAxCBRN=1297481926; else nilAxCBRN=403146768;if (nilAxCBRN == nilAxCBRN- 1 ) nilAxCBRN=1667397081; else nilAxCBRN=1035776035;if (nilAxCBRN == nilAxCBRN- 0 ) nilAxCBRN=200568402; else nilAxCBRN=989594167;long YvOIkLKoY=1235171582;if (YvOIkLKoY == YvOIkLKoY- 1 ) YvOIkLKoY=983868629; else YvOIkLKoY=675277155;if (YvOIkLKoY == YvOIkLKoY- 1 ) YvOIkLKoY=1220943997; else YvOIkLKoY=1310344857;if (YvOIkLKoY == YvOIkLKoY- 0 ) YvOIkLKoY=895482378; else YvOIkLKoY=1307234455;if (YvOIkLKoY == YvOIkLKoY- 1 ) YvOIkLKoY=912965180; else YvOIkLKoY=1724994880;if (YvOIkLKoY == YvOIkLKoY- 1 ) YvOIkLKoY=1399338628; else YvOIkLKoY=507856940;if (YvOIkLKoY == YvOIkLKoY- 0 ) YvOIkLKoY=1912719008; else YvOIkLKoY=1922763500;int TvnPNxZQM=1453295557;if (TvnPNxZQM == TvnPNxZQM- 1 ) TvnPNxZQM=1985564166; else TvnPNxZQM=1127160022;if (TvnPNxZQM == TvnPNxZQM- 0 ) TvnPNxZQM=1221526369; else TvnPNxZQM=866644249;if (TvnPNxZQM == TvnPNxZQM- 0 ) TvnPNxZQM=24300192; else TvnPNxZQM=753406817;if (TvnPNxZQM == TvnPNxZQM- 0 ) TvnPNxZQM=1709547804; else TvnPNxZQM=687265639;if (TvnPNxZQM == TvnPNxZQM- 0 ) TvnPNxZQM=1519876818; else TvnPNxZQM=2051298779;if (TvnPNxZQM == TvnPNxZQM- 1 ) TvnPNxZQM=2040263296; else TvnPNxZQM=116967168;int lKtGdjrxV=780666494;if (lKtGdjrxV == lKtGdjrxV- 0 ) lKtGdjrxV=1029759907; else lKtGdjrxV=1080731315;if (lKtGdjrxV == lKtGdjrxV- 1 ) lKtGdjrxV=673938136; else lKtGdjrxV=680716265;if (lKtGdjrxV == lKtGdjrxV- 0 ) lKtGdjrxV=1228086774; else lKtGdjrxV=1114709374;if (lKtGdjrxV == lKtGdjrxV- 0 ) lKtGdjrxV=1382257190; else lKtGdjrxV=1626155267;if (lKtGdjrxV == lKtGdjrxV- 0 ) lKtGdjrxV=496017065; else lKtGdjrxV=681845681;if (lKtGdjrxV == lKtGdjrxV- 1 ) lKtGdjrxV=160474155; else lKtGdjrxV=11091804;double HpSwEZSqS=590919516.9827130;if (HpSwEZSqS == HpSwEZSqS ) HpSwEZSqS=1042280305.6555177; else HpSwEZSqS=894756492.0126501;if (HpSwEZSqS == HpSwEZSqS ) HpSwEZSqS=1151513648.8298094; else HpSwEZSqS=1409309879.3749731;if (HpSwEZSqS == HpSwEZSqS ) HpSwEZSqS=973714895.8444875; else HpSwEZSqS=287962615.8753493;if (HpSwEZSqS == HpSwEZSqS ) HpSwEZSqS=1210871390.8582401; else HpSwEZSqS=230461812.7392474;if (HpSwEZSqS == HpSwEZSqS ) HpSwEZSqS=1113212998.9174572; else HpSwEZSqS=533678358.8938470;if (HpSwEZSqS == HpSwEZSqS ) HpSwEZSqS=1937951686.6567026; else HpSwEZSqS=991667246.2784302;double aMQxCwfpt=1292144408.3361681;if (aMQxCwfpt == aMQxCwfpt ) aMQxCwfpt=313228475.3378664; else aMQxCwfpt=1132052514.3376391;if (aMQxCwfpt == aMQxCwfpt ) aMQxCwfpt=893003593.5235159; else aMQxCwfpt=1113299806.7880413;if (aMQxCwfpt == aMQxCwfpt ) aMQxCwfpt=402539429.3630298; else aMQxCwfpt=1460263112.1704991;if (aMQxCwfpt == aMQxCwfpt ) aMQxCwfpt=225208783.0346709; else aMQxCwfpt=870854792.2365436;if (aMQxCwfpt == aMQxCwfpt ) aMQxCwfpt=1892386479.5983510; else aMQxCwfpt=1742854749.7571135;if (aMQxCwfpt == aMQxCwfpt ) aMQxCwfpt=370627184.6322687; else aMQxCwfpt=1489938158.5557251; }
 aMQxCwfpty::aMQxCwfpty()
 { this->LmvUJLMuunYz("JCyhaXxRELmvUJLMuunYzj", true, 592932662, 1698456000, 1564562041); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class SdusKhYBly
 { 
public: bool ylSBEbrzO; double ylSBEbrzOSdusKhYBl; SdusKhYBly(); void zlXypPEzYYuT(string ylSBEbrzOzlXypPEzYYuT, bool kmSsWtURT, int BMXERIDPg, float AlKQlFGOd, long ChqMPjwci);
 protected: bool ylSBEbrzOo; double ylSBEbrzOSdusKhYBlf; void zlXypPEzYYuTu(string ylSBEbrzOzlXypPEzYYuTg, bool kmSsWtURTe, int BMXERIDPgr, float AlKQlFGOdw, long ChqMPjwcin);
 private: bool ylSBEbrzOkmSsWtURT; double ylSBEbrzOAlKQlFGOdSdusKhYBl;
 void zlXypPEzYYuTv(string kmSsWtURTzlXypPEzYYuT, bool kmSsWtURTBMXERIDPg, int BMXERIDPgylSBEbrzO, float AlKQlFGOdChqMPjwci, long ChqMPjwcikmSsWtURT); };
 void SdusKhYBly::zlXypPEzYYuT(string ylSBEbrzOzlXypPEzYYuT, bool kmSsWtURT, int BMXERIDPg, float AlKQlFGOd, long ChqMPjwci)
 { float eihKBTdOX=1889014194.3287843f;if (eihKBTdOX - eihKBTdOX> 0.00000001 ) eihKBTdOX=923265985.0683740f; else eihKBTdOX=1926510473.6660418f;if (eihKBTdOX - eihKBTdOX> 0.00000001 ) eihKBTdOX=435875644.8086974f; else eihKBTdOX=731538700.6101625f;if (eihKBTdOX - eihKBTdOX> 0.00000001 ) eihKBTdOX=1428096709.8154174f; else eihKBTdOX=1126740464.5882755f;if (eihKBTdOX - eihKBTdOX> 0.00000001 ) eihKBTdOX=1862918904.8259895f; else eihKBTdOX=2094344494.2119894f;if (eihKBTdOX - eihKBTdOX> 0.00000001 ) eihKBTdOX=729640860.6831368f; else eihKBTdOX=64889994.5164454f;if (eihKBTdOX - eihKBTdOX> 0.00000001 ) eihKBTdOX=1351262907.2043209f; else eihKBTdOX=105462563.9629307f;int VaOpzvBcD=1813494519;if (VaOpzvBcD == VaOpzvBcD- 1 ) VaOpzvBcD=982784774; else VaOpzvBcD=1325513215;if (VaOpzvBcD == VaOpzvBcD- 1 ) VaOpzvBcD=2087801107; else VaOpzvBcD=564961157;if (VaOpzvBcD == VaOpzvBcD- 1 ) VaOpzvBcD=900900830; else VaOpzvBcD=778433286;if (VaOpzvBcD == VaOpzvBcD- 0 ) VaOpzvBcD=933171910; else VaOpzvBcD=660455252;if (VaOpzvBcD == VaOpzvBcD- 1 ) VaOpzvBcD=83484877; else VaOpzvBcD=129304613;if (VaOpzvBcD == VaOpzvBcD- 0 ) VaOpzvBcD=1281293903; else VaOpzvBcD=118333924;int rhUsWeyAX=579215663;if (rhUsWeyAX == rhUsWeyAX- 1 ) rhUsWeyAX=1562440373; else rhUsWeyAX=877982508;if (rhUsWeyAX == rhUsWeyAX- 1 ) rhUsWeyAX=155327518; else rhUsWeyAX=1429241206;if (rhUsWeyAX == rhUsWeyAX- 0 ) rhUsWeyAX=290831825; else rhUsWeyAX=1696005501;if (rhUsWeyAX == rhUsWeyAX- 1 ) rhUsWeyAX=1392383682; else rhUsWeyAX=197551727;if (rhUsWeyAX == rhUsWeyAX- 0 ) rhUsWeyAX=162405595; else rhUsWeyAX=140089819;if (rhUsWeyAX == rhUsWeyAX- 0 ) rhUsWeyAX=1767534053; else rhUsWeyAX=1033906603;int WzspaOJYF=1361092513;if (WzspaOJYF == WzspaOJYF- 1 ) WzspaOJYF=1302551104; else WzspaOJYF=1369621534;if (WzspaOJYF == WzspaOJYF- 0 ) WzspaOJYF=728356700; else WzspaOJYF=827059650;if (WzspaOJYF == WzspaOJYF- 0 ) WzspaOJYF=788247793; else WzspaOJYF=1484607576;if (WzspaOJYF == WzspaOJYF- 1 ) WzspaOJYF=988113364; else WzspaOJYF=144832699;if (WzspaOJYF == WzspaOJYF- 1 ) WzspaOJYF=993338563; else WzspaOJYF=1922904039;if (WzspaOJYF == WzspaOJYF- 0 ) WzspaOJYF=648053823; else WzspaOJYF=1298792096;float IvysaknBB=2051244911.6012038f;if (IvysaknBB - IvysaknBB> 0.00000001 ) IvysaknBB=1026774120.2226387f; else IvysaknBB=772047244.4504190f;if (IvysaknBB - IvysaknBB> 0.00000001 ) IvysaknBB=690505837.5660166f; else IvysaknBB=2069627313.4298964f;if (IvysaknBB - IvysaknBB> 0.00000001 ) IvysaknBB=1994600321.8965611f; else IvysaknBB=564327862.7892134f;if (IvysaknBB - IvysaknBB> 0.00000001 ) IvysaknBB=1522662694.0501702f; else IvysaknBB=1434262920.5529729f;if (IvysaknBB - IvysaknBB> 0.00000001 ) IvysaknBB=2080613180.1384246f; else IvysaknBB=1890249380.6596909f;if (IvysaknBB - IvysaknBB> 0.00000001 ) IvysaknBB=402555562.8891335f; else IvysaknBB=760811011.7982733f;double SdusKhYBl=1767290287.3089931;if (SdusKhYBl == SdusKhYBl ) SdusKhYBl=472790150.4138244; else SdusKhYBl=2067685037.7680828;if (SdusKhYBl == SdusKhYBl ) SdusKhYBl=963266467.5162109; else SdusKhYBl=866700049.3877429;if (SdusKhYBl == SdusKhYBl ) SdusKhYBl=97522896.7145592; else SdusKhYBl=358539871.7804757;if (SdusKhYBl == SdusKhYBl ) SdusKhYBl=1938451517.6268868; else SdusKhYBl=77832797.0388422;if (SdusKhYBl == SdusKhYBl ) SdusKhYBl=2037352791.4718251; else SdusKhYBl=10494819.6554479;if (SdusKhYBl == SdusKhYBl ) SdusKhYBl=435902643.4695538; else SdusKhYBl=515411433.6107628; }
 SdusKhYBly::SdusKhYBly()
 { this->zlXypPEzYYuT("ylSBEbrzOzlXypPEzYYuTj", true, 1047951678, 93591586, 352105166); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class qEhuNMtiqy
 { 
public: bool PIkDKIdLy; double PIkDKIdLyqEhuNMtiq; qEhuNMtiqy(); void LWHtZcWuGxBc(string PIkDKIdLyLWHtZcWuGxBc, bool KPeiZBojX, int njsOfNEXB, float iksiMAzbb, long UKEhWCpko);
 protected: bool PIkDKIdLyo; double PIkDKIdLyqEhuNMtiqf; void LWHtZcWuGxBcu(string PIkDKIdLyLWHtZcWuGxBcg, bool KPeiZBojXe, int njsOfNEXBr, float iksiMAzbbw, long UKEhWCpkon);
 private: bool PIkDKIdLyKPeiZBojX; double PIkDKIdLyiksiMAzbbqEhuNMtiq;
 void LWHtZcWuGxBcv(string KPeiZBojXLWHtZcWuGxBc, bool KPeiZBojXnjsOfNEXB, int njsOfNEXBPIkDKIdLy, float iksiMAzbbUKEhWCpko, long UKEhWCpkoKPeiZBojX); };
 void qEhuNMtiqy::LWHtZcWuGxBc(string PIkDKIdLyLWHtZcWuGxBc, bool KPeiZBojX, int njsOfNEXB, float iksiMAzbb, long UKEhWCpko)
 { int CBAovHGWw=78720572;if (CBAovHGWw == CBAovHGWw- 0 ) CBAovHGWw=261708119; else CBAovHGWw=1247231762;if (CBAovHGWw == CBAovHGWw- 1 ) CBAovHGWw=407410161; else CBAovHGWw=634505762;if (CBAovHGWw == CBAovHGWw- 0 ) CBAovHGWw=1865677146; else CBAovHGWw=840113312;if (CBAovHGWw == CBAovHGWw- 1 ) CBAovHGWw=844584981; else CBAovHGWw=684458241;if (CBAovHGWw == CBAovHGWw- 0 ) CBAovHGWw=1952457700; else CBAovHGWw=1501323587;if (CBAovHGWw == CBAovHGWw- 1 ) CBAovHGWw=181092871; else CBAovHGWw=1517851480;long GjWxyUNfY=1810646348;if (GjWxyUNfY == GjWxyUNfY- 0 ) GjWxyUNfY=79961552; else GjWxyUNfY=221417324;if (GjWxyUNfY == GjWxyUNfY- 1 ) GjWxyUNfY=1674997592; else GjWxyUNfY=389206322;if (GjWxyUNfY == GjWxyUNfY- 1 ) GjWxyUNfY=1781473941; else GjWxyUNfY=615334709;if (GjWxyUNfY == GjWxyUNfY- 1 ) GjWxyUNfY=399823966; else GjWxyUNfY=2132511282;if (GjWxyUNfY == GjWxyUNfY- 0 ) GjWxyUNfY=1583402073; else GjWxyUNfY=1411058032;if (GjWxyUNfY == GjWxyUNfY- 0 ) GjWxyUNfY=2014117233; else GjWxyUNfY=577282456;int MwwAjsqmr=350499126;if (MwwAjsqmr == MwwAjsqmr- 1 ) MwwAjsqmr=2137986854; else MwwAjsqmr=125894553;if (MwwAjsqmr == MwwAjsqmr- 0 ) MwwAjsqmr=998971034; else MwwAjsqmr=279752172;if (MwwAjsqmr == MwwAjsqmr- 1 ) MwwAjsqmr=361226623; else MwwAjsqmr=176473032;if (MwwAjsqmr == MwwAjsqmr- 1 ) MwwAjsqmr=945867854; else MwwAjsqmr=1328912379;if (MwwAjsqmr == MwwAjsqmr- 0 ) MwwAjsqmr=580557384; else MwwAjsqmr=1079269174;if (MwwAjsqmr == MwwAjsqmr- 1 ) MwwAjsqmr=1589027579; else MwwAjsqmr=1220115676;double NgjkKEEHS=277620280.6426009;if (NgjkKEEHS == NgjkKEEHS ) NgjkKEEHS=209797564.1859559; else NgjkKEEHS=839696207.2772615;if (NgjkKEEHS == NgjkKEEHS ) NgjkKEEHS=1751797117.0450385; else NgjkKEEHS=2105531648.7424273;if (NgjkKEEHS == NgjkKEEHS ) NgjkKEEHS=937904673.1929376; else NgjkKEEHS=1355468185.6735283;if (NgjkKEEHS == NgjkKEEHS ) NgjkKEEHS=444730278.9248367; else NgjkKEEHS=1793857057.0867244;if (NgjkKEEHS == NgjkKEEHS ) NgjkKEEHS=847407796.5363971; else NgjkKEEHS=422382526.9533494;if (NgjkKEEHS == NgjkKEEHS ) NgjkKEEHS=1198587336.8261128; else NgjkKEEHS=454619114.3860272;int iIFPIGRmK=1493272412;if (iIFPIGRmK == iIFPIGRmK- 0 ) iIFPIGRmK=1572528846; else iIFPIGRmK=1978077392;if (iIFPIGRmK == iIFPIGRmK- 1 ) iIFPIGRmK=1527348273; else iIFPIGRmK=320882469;if (iIFPIGRmK == iIFPIGRmK- 1 ) iIFPIGRmK=1758407398; else iIFPIGRmK=281930297;if (iIFPIGRmK == iIFPIGRmK- 0 ) iIFPIGRmK=1449419725; else iIFPIGRmK=2050972167;if (iIFPIGRmK == iIFPIGRmK- 1 ) iIFPIGRmK=1423033117; else iIFPIGRmK=346085213;if (iIFPIGRmK == iIFPIGRmK- 1 ) iIFPIGRmK=1956132585; else iIFPIGRmK=702204767;double qEhuNMtiq=701409797.5082962;if (qEhuNMtiq == qEhuNMtiq ) qEhuNMtiq=593764315.6167054; else qEhuNMtiq=1736496953.5423950;if (qEhuNMtiq == qEhuNMtiq ) qEhuNMtiq=367484892.5919824; else qEhuNMtiq=245554258.3491600;if (qEhuNMtiq == qEhuNMtiq ) qEhuNMtiq=854871818.3466672; else qEhuNMtiq=2118230387.8782421;if (qEhuNMtiq == qEhuNMtiq ) qEhuNMtiq=1560078100.1892670; else qEhuNMtiq=782518669.2831494;if (qEhuNMtiq == qEhuNMtiq ) qEhuNMtiq=1828647922.8775653; else qEhuNMtiq=1352597624.1683888;if (qEhuNMtiq == qEhuNMtiq ) qEhuNMtiq=1579828023.2375132; else qEhuNMtiq=2086327744.6190401; }
 qEhuNMtiqy::qEhuNMtiqy()
 { this->LWHtZcWuGxBc("PIkDKIdLyLWHtZcWuGxBcj", true, 1125369343, 491248740, 355432653); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class bLHvIQZHUy
 { 
public: bool PzDPUvhOa; double PzDPUvhOabLHvIQZHU; bLHvIQZHUy(); void ctyklsPTpBxE(string PzDPUvhOactyklsPTpBxE, bool dJzRIKXYJ, int ofYSvcJjc, float vuYsleizk, long SJFLOJidG);
 protected: bool PzDPUvhOao; double PzDPUvhOabLHvIQZHUf; void ctyklsPTpBxEu(string PzDPUvhOactyklsPTpBxEg, bool dJzRIKXYJe, int ofYSvcJjcr, float vuYsleizkw, long SJFLOJidGn);
 private: bool PzDPUvhOadJzRIKXYJ; double PzDPUvhOavuYsleizkbLHvIQZHU;
 void ctyklsPTpBxEv(string dJzRIKXYJctyklsPTpBxE, bool dJzRIKXYJofYSvcJjc, int ofYSvcJjcPzDPUvhOa, float vuYsleizkSJFLOJidG, long SJFLOJidGdJzRIKXYJ); };
 void bLHvIQZHUy::ctyklsPTpBxE(string PzDPUvhOactyklsPTpBxE, bool dJzRIKXYJ, int ofYSvcJjc, float vuYsleizk, long SJFLOJidG)
 { double dsGMMIDhX=1305926133.8261354;if (dsGMMIDhX == dsGMMIDhX ) dsGMMIDhX=1129305850.0223167; else dsGMMIDhX=555319153.0083994;if (dsGMMIDhX == dsGMMIDhX ) dsGMMIDhX=700653739.4037562; else dsGMMIDhX=562869399.1753949;if (dsGMMIDhX == dsGMMIDhX ) dsGMMIDhX=1718076833.4245774; else dsGMMIDhX=1263717251.7337347;if (dsGMMIDhX == dsGMMIDhX ) dsGMMIDhX=563590724.5741835; else dsGMMIDhX=336173789.3458920;if (dsGMMIDhX == dsGMMIDhX ) dsGMMIDhX=396748357.5813287; else dsGMMIDhX=1829786403.8592208;if (dsGMMIDhX == dsGMMIDhX ) dsGMMIDhX=2003562841.8002357; else dsGMMIDhX=926748809.1221251;float vgpbZHXLV=1607237121.8845101f;if (vgpbZHXLV - vgpbZHXLV> 0.00000001 ) vgpbZHXLV=2054900815.3696033f; else vgpbZHXLV=153383658.6168361f;if (vgpbZHXLV - vgpbZHXLV> 0.00000001 ) vgpbZHXLV=1240603150.4123829f; else vgpbZHXLV=1594369254.5549502f;if (vgpbZHXLV - vgpbZHXLV> 0.00000001 ) vgpbZHXLV=909028508.1495973f; else vgpbZHXLV=1058973356.0653602f;if (vgpbZHXLV - vgpbZHXLV> 0.00000001 ) vgpbZHXLV=963482020.9960755f; else vgpbZHXLV=1211129457.7233839f;if (vgpbZHXLV - vgpbZHXLV> 0.00000001 ) vgpbZHXLV=1330929721.2676416f; else vgpbZHXLV=635217976.7734084f;if (vgpbZHXLV - vgpbZHXLV> 0.00000001 ) vgpbZHXLV=1407898069.6813387f; else vgpbZHXLV=1706656854.6909685f;float fKGYVqzmk=1415579469.7123346f;if (fKGYVqzmk - fKGYVqzmk> 0.00000001 ) fKGYVqzmk=2001496507.7501247f; else fKGYVqzmk=504216237.1237088f;if (fKGYVqzmk - fKGYVqzmk> 0.00000001 ) fKGYVqzmk=1777254712.8707523f; else fKGYVqzmk=1199394833.3036960f;if (fKGYVqzmk - fKGYVqzmk> 0.00000001 ) fKGYVqzmk=1764371098.5529517f; else fKGYVqzmk=962419880.4515762f;if (fKGYVqzmk - fKGYVqzmk> 0.00000001 ) fKGYVqzmk=916637499.2855889f; else fKGYVqzmk=1610464481.4379344f;if (fKGYVqzmk - fKGYVqzmk> 0.00000001 ) fKGYVqzmk=1347424231.6764887f; else fKGYVqzmk=1568243673.7286825f;if (fKGYVqzmk - fKGYVqzmk> 0.00000001 ) fKGYVqzmk=284698360.3938711f; else fKGYVqzmk=1335573932.2911912f;double YyOlSqtaC=1157989718.1087099;if (YyOlSqtaC == YyOlSqtaC ) YyOlSqtaC=637996076.9132877; else YyOlSqtaC=729215019.8543826;if (YyOlSqtaC == YyOlSqtaC ) YyOlSqtaC=809984546.7706672; else YyOlSqtaC=2120316551.2450966;if (YyOlSqtaC == YyOlSqtaC ) YyOlSqtaC=1202231120.6652482; else YyOlSqtaC=2039454874.7880957;if (YyOlSqtaC == YyOlSqtaC ) YyOlSqtaC=396897625.8763954; else YyOlSqtaC=70332494.4925387;if (YyOlSqtaC == YyOlSqtaC ) YyOlSqtaC=1739320780.8929223; else YyOlSqtaC=1637007929.0025450;if (YyOlSqtaC == YyOlSqtaC ) YyOlSqtaC=1379423325.9267355; else YyOlSqtaC=1082858857.7081133;long OhEDaxvfG=1020507538;if (OhEDaxvfG == OhEDaxvfG- 0 ) OhEDaxvfG=2077256666; else OhEDaxvfG=587983372;if (OhEDaxvfG == OhEDaxvfG- 0 ) OhEDaxvfG=1072735949; else OhEDaxvfG=912619817;if (OhEDaxvfG == OhEDaxvfG- 1 ) OhEDaxvfG=1378444813; else OhEDaxvfG=2052617541;if (OhEDaxvfG == OhEDaxvfG- 0 ) OhEDaxvfG=1990349670; else OhEDaxvfG=1092480935;if (OhEDaxvfG == OhEDaxvfG- 0 ) OhEDaxvfG=1384229806; else OhEDaxvfG=1777622316;if (OhEDaxvfG == OhEDaxvfG- 0 ) OhEDaxvfG=246945023; else OhEDaxvfG=1488268482;long bLHvIQZHU=1406267287;if (bLHvIQZHU == bLHvIQZHU- 1 ) bLHvIQZHU=1785874546; else bLHvIQZHU=249908351;if (bLHvIQZHU == bLHvIQZHU- 0 ) bLHvIQZHU=1068660778; else bLHvIQZHU=1570542257;if (bLHvIQZHU == bLHvIQZHU- 1 ) bLHvIQZHU=713739920; else bLHvIQZHU=1927180480;if (bLHvIQZHU == bLHvIQZHU- 0 ) bLHvIQZHU=213348349; else bLHvIQZHU=2109525280;if (bLHvIQZHU == bLHvIQZHU- 1 ) bLHvIQZHU=107318612; else bLHvIQZHU=1706922218;if (bLHvIQZHU == bLHvIQZHU- 0 ) bLHvIQZHU=1607557700; else bLHvIQZHU=127363169; }
 bLHvIQZHUy::bLHvIQZHUy()
 { this->ctyklsPTpBxE("PzDPUvhOactyklsPTpBxEj", true, 1730480202, 1981262289, 1754645299); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class FMOphAmiMy
 { 
public: bool RLGNpOEHQ; double RLGNpOEHQFMOphAmiM; FMOphAmiMy(); void HoCFIifneJSf(string RLGNpOEHQHoCFIifneJSf, bool ifxYMkZRH, int viZzfWfIg, float YXShIARqC, long trHzHYlhc);
 protected: bool RLGNpOEHQo; double RLGNpOEHQFMOphAmiMf; void HoCFIifneJSfu(string RLGNpOEHQHoCFIifneJSfg, bool ifxYMkZRHe, int viZzfWfIgr, float YXShIARqCw, long trHzHYlhcn);
 private: bool RLGNpOEHQifxYMkZRH; double RLGNpOEHQYXShIARqCFMOphAmiM;
 void HoCFIifneJSfv(string ifxYMkZRHHoCFIifneJSf, bool ifxYMkZRHviZzfWfIg, int viZzfWfIgRLGNpOEHQ, float YXShIARqCtrHzHYlhc, long trHzHYlhcifxYMkZRH); };
 void FMOphAmiMy::HoCFIifneJSf(string RLGNpOEHQHoCFIifneJSf, bool ifxYMkZRH, int viZzfWfIg, float YXShIARqC, long trHzHYlhc)
 { float VJqkzsmfg=1575332012.0989421f;if (VJqkzsmfg - VJqkzsmfg> 0.00000001 ) VJqkzsmfg=1547381624.7675278f; else VJqkzsmfg=1693997965.4822203f;if (VJqkzsmfg - VJqkzsmfg> 0.00000001 ) VJqkzsmfg=1062225388.8939676f; else VJqkzsmfg=963313870.2871625f;if (VJqkzsmfg - VJqkzsmfg> 0.00000001 ) VJqkzsmfg=1727665696.7283021f; else VJqkzsmfg=1813302860.7730306f;if (VJqkzsmfg - VJqkzsmfg> 0.00000001 ) VJqkzsmfg=1526347983.4798283f; else VJqkzsmfg=1737411879.1619655f;if (VJqkzsmfg - VJqkzsmfg> 0.00000001 ) VJqkzsmfg=1699987402.8146648f; else VJqkzsmfg=1355809341.6493921f;if (VJqkzsmfg - VJqkzsmfg> 0.00000001 ) VJqkzsmfg=1020514913.3093719f; else VJqkzsmfg=1001795059.2845427f;long oXUjcyfuW=881723701;if (oXUjcyfuW == oXUjcyfuW- 1 ) oXUjcyfuW=35452573; else oXUjcyfuW=670127309;if (oXUjcyfuW == oXUjcyfuW- 1 ) oXUjcyfuW=1232762233; else oXUjcyfuW=1178000133;if (oXUjcyfuW == oXUjcyfuW- 1 ) oXUjcyfuW=1176520620; else oXUjcyfuW=1380711139;if (oXUjcyfuW == oXUjcyfuW- 1 ) oXUjcyfuW=280002524; else oXUjcyfuW=1591699393;if (oXUjcyfuW == oXUjcyfuW- 0 ) oXUjcyfuW=1571522818; else oXUjcyfuW=737598416;if (oXUjcyfuW == oXUjcyfuW- 1 ) oXUjcyfuW=1062757309; else oXUjcyfuW=649916118;float LakvqLkiU=118055046.6940579f;if (LakvqLkiU - LakvqLkiU> 0.00000001 ) LakvqLkiU=100460304.7037824f; else LakvqLkiU=1766002617.3163187f;if (LakvqLkiU - LakvqLkiU> 0.00000001 ) LakvqLkiU=487268503.2634354f; else LakvqLkiU=1973904932.6497547f;if (LakvqLkiU - LakvqLkiU> 0.00000001 ) LakvqLkiU=1085410871.5886655f; else LakvqLkiU=1853249230.7779795f;if (LakvqLkiU - LakvqLkiU> 0.00000001 ) LakvqLkiU=214696497.7990215f; else LakvqLkiU=2067486294.3163362f;if (LakvqLkiU - LakvqLkiU> 0.00000001 ) LakvqLkiU=90760976.6513988f; else LakvqLkiU=1822916616.3876425f;if (LakvqLkiU - LakvqLkiU> 0.00000001 ) LakvqLkiU=1812273084.9766790f; else LakvqLkiU=978781093.5183433f;double HQQuSCPdc=1161336142.9582406;if (HQQuSCPdc == HQQuSCPdc ) HQQuSCPdc=1521376167.8311157; else HQQuSCPdc=1607500242.9516136;if (HQQuSCPdc == HQQuSCPdc ) HQQuSCPdc=260992573.2686376; else HQQuSCPdc=326069485.7954008;if (HQQuSCPdc == HQQuSCPdc ) HQQuSCPdc=554231081.9232683; else HQQuSCPdc=1458131666.1067961;if (HQQuSCPdc == HQQuSCPdc ) HQQuSCPdc=398811392.5304377; else HQQuSCPdc=166670485.9072301;if (HQQuSCPdc == HQQuSCPdc ) HQQuSCPdc=1413995441.5782590; else HQQuSCPdc=1618009642.4845631;if (HQQuSCPdc == HQQuSCPdc ) HQQuSCPdc=1539274699.6304263; else HQQuSCPdc=990067280.7508421;int fBMqLhToa=504680743;if (fBMqLhToa == fBMqLhToa- 1 ) fBMqLhToa=963241751; else fBMqLhToa=902459867;if (fBMqLhToa == fBMqLhToa- 0 ) fBMqLhToa=901334755; else fBMqLhToa=1591550042;if (fBMqLhToa == fBMqLhToa- 0 ) fBMqLhToa=701680462; else fBMqLhToa=430419654;if (fBMqLhToa == fBMqLhToa- 1 ) fBMqLhToa=1943796477; else fBMqLhToa=329686990;if (fBMqLhToa == fBMqLhToa- 0 ) fBMqLhToa=455430812; else fBMqLhToa=1312759586;if (fBMqLhToa == fBMqLhToa- 0 ) fBMqLhToa=1087239157; else fBMqLhToa=1501087651;long FMOphAmiM=477316583;if (FMOphAmiM == FMOphAmiM- 1 ) FMOphAmiM=127535711; else FMOphAmiM=2048904814;if (FMOphAmiM == FMOphAmiM- 1 ) FMOphAmiM=1276023598; else FMOphAmiM=1588723156;if (FMOphAmiM == FMOphAmiM- 1 ) FMOphAmiM=934314086; else FMOphAmiM=66498105;if (FMOphAmiM == FMOphAmiM- 1 ) FMOphAmiM=1711307612; else FMOphAmiM=789812285;if (FMOphAmiM == FMOphAmiM- 1 ) FMOphAmiM=1367191225; else FMOphAmiM=320598018;if (FMOphAmiM == FMOphAmiM- 1 ) FMOphAmiM=559909491; else FMOphAmiM=1614884876; }
 FMOphAmiMy::FMOphAmiMy()
 { this->HoCFIifneJSf("RLGNpOEHQHoCFIifneJSfj", true, 313974531, 1372112864, 1316940743); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class fAmofGbRQy
 { 
public: bool eFxecCcfI; double eFxecCcfIfAmofGbRQ; fAmofGbRQy(); void tsiXQzmPTLjy(string eFxecCcfItsiXQzmPTLjy, bool cjlHDQOGo, int BxwvGuLbO, float FDIYcRGPW, long swwjMgyQP);
 protected: bool eFxecCcfIo; double eFxecCcfIfAmofGbRQf; void tsiXQzmPTLjyu(string eFxecCcfItsiXQzmPTLjyg, bool cjlHDQOGoe, int BxwvGuLbOr, float FDIYcRGPWw, long swwjMgyQPn);
 private: bool eFxecCcfIcjlHDQOGo; double eFxecCcfIFDIYcRGPWfAmofGbRQ;
 void tsiXQzmPTLjyv(string cjlHDQOGotsiXQzmPTLjy, bool cjlHDQOGoBxwvGuLbO, int BxwvGuLbOeFxecCcfI, float FDIYcRGPWswwjMgyQP, long swwjMgyQPcjlHDQOGo); };
 void fAmofGbRQy::tsiXQzmPTLjy(string eFxecCcfItsiXQzmPTLjy, bool cjlHDQOGo, int BxwvGuLbO, float FDIYcRGPW, long swwjMgyQP)
 { float UFOdemYJa=1680637754.7454041f;if (UFOdemYJa - UFOdemYJa> 0.00000001 ) UFOdemYJa=1784867672.6542357f; else UFOdemYJa=1648503724.3465793f;if (UFOdemYJa - UFOdemYJa> 0.00000001 ) UFOdemYJa=897103763.6376099f; else UFOdemYJa=2069602911.7595496f;if (UFOdemYJa - UFOdemYJa> 0.00000001 ) UFOdemYJa=1850867781.7995876f; else UFOdemYJa=1274712368.7380003f;if (UFOdemYJa - UFOdemYJa> 0.00000001 ) UFOdemYJa=167994675.4039672f; else UFOdemYJa=1123447836.1991539f;if (UFOdemYJa - UFOdemYJa> 0.00000001 ) UFOdemYJa=1499874754.0570727f; else UFOdemYJa=102155396.6800380f;if (UFOdemYJa - UFOdemYJa> 0.00000001 ) UFOdemYJa=1166413379.1961073f; else UFOdemYJa=1081886128.6778256f;int yZNVfipDz=1923083892;if (yZNVfipDz == yZNVfipDz- 0 ) yZNVfipDz=678953420; else yZNVfipDz=543960431;if (yZNVfipDz == yZNVfipDz- 0 ) yZNVfipDz=2114335285; else yZNVfipDz=2097825757;if (yZNVfipDz == yZNVfipDz- 1 ) yZNVfipDz=1924702288; else yZNVfipDz=1461414290;if (yZNVfipDz == yZNVfipDz- 0 ) yZNVfipDz=93446015; else yZNVfipDz=459851901;if (yZNVfipDz == yZNVfipDz- 1 ) yZNVfipDz=2085309116; else yZNVfipDz=262910807;if (yZNVfipDz == yZNVfipDz- 1 ) yZNVfipDz=1273423831; else yZNVfipDz=1186127624;int pInFVWKzZ=319580747;if (pInFVWKzZ == pInFVWKzZ- 1 ) pInFVWKzZ=2057614850; else pInFVWKzZ=1394468917;if (pInFVWKzZ == pInFVWKzZ- 1 ) pInFVWKzZ=1172484499; else pInFVWKzZ=1114681004;if (pInFVWKzZ == pInFVWKzZ- 1 ) pInFVWKzZ=1025047779; else pInFVWKzZ=123951757;if (pInFVWKzZ == pInFVWKzZ- 0 ) pInFVWKzZ=1113601963; else pInFVWKzZ=700423907;if (pInFVWKzZ == pInFVWKzZ- 0 ) pInFVWKzZ=261005675; else pInFVWKzZ=1083215436;if (pInFVWKzZ == pInFVWKzZ- 1 ) pInFVWKzZ=264926024; else pInFVWKzZ=2109492356;long VnoMtfNje=1831909937;if (VnoMtfNje == VnoMtfNje- 1 ) VnoMtfNje=1665743116; else VnoMtfNje=1247525764;if (VnoMtfNje == VnoMtfNje- 1 ) VnoMtfNje=498791794; else VnoMtfNje=927638127;if (VnoMtfNje == VnoMtfNje- 1 ) VnoMtfNje=381057316; else VnoMtfNje=1712128428;if (VnoMtfNje == VnoMtfNje- 0 ) VnoMtfNje=1903419113; else VnoMtfNje=323453382;if (VnoMtfNje == VnoMtfNje- 0 ) VnoMtfNje=1555057709; else VnoMtfNje=437251862;if (VnoMtfNje == VnoMtfNje- 1 ) VnoMtfNje=2131777442; else VnoMtfNje=1587956974;long kZTApzleb=32832080;if (kZTApzleb == kZTApzleb- 0 ) kZTApzleb=451514653; else kZTApzleb=846832632;if (kZTApzleb == kZTApzleb- 1 ) kZTApzleb=1171754925; else kZTApzleb=1815903091;if (kZTApzleb == kZTApzleb- 1 ) kZTApzleb=1059091071; else kZTApzleb=491341428;if (kZTApzleb == kZTApzleb- 0 ) kZTApzleb=898036113; else kZTApzleb=555001663;if (kZTApzleb == kZTApzleb- 0 ) kZTApzleb=1577842115; else kZTApzleb=1413911378;if (kZTApzleb == kZTApzleb- 1 ) kZTApzleb=1836820082; else kZTApzleb=841486852;float fAmofGbRQ=531568828.1418561f;if (fAmofGbRQ - fAmofGbRQ> 0.00000001 ) fAmofGbRQ=1654440642.1241895f; else fAmofGbRQ=1588997541.2948409f;if (fAmofGbRQ - fAmofGbRQ> 0.00000001 ) fAmofGbRQ=1667868155.7477782f; else fAmofGbRQ=1433707894.8309759f;if (fAmofGbRQ - fAmofGbRQ> 0.00000001 ) fAmofGbRQ=968250880.6009103f; else fAmofGbRQ=870486263.2599699f;if (fAmofGbRQ - fAmofGbRQ> 0.00000001 ) fAmofGbRQ=2086007078.9070825f; else fAmofGbRQ=345486422.0428894f;if (fAmofGbRQ - fAmofGbRQ> 0.00000001 ) fAmofGbRQ=1638533451.0522577f; else fAmofGbRQ=849031117.0503065f;if (fAmofGbRQ - fAmofGbRQ> 0.00000001 ) fAmofGbRQ=1707106942.9981949f; else fAmofGbRQ=587795917.3409446f; }
 fAmofGbRQy::fAmofGbRQy()
 { this->tsiXQzmPTLjy("eFxecCcfItsiXQzmPTLjyj", true, 139657962, 1673128636, 699135370); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class HDbZmQwxVy
 { 
public: bool CfsRPVVHP; double CfsRPVVHPHDbZmQwxV; HDbZmQwxVy(); void jAsQXDPxUJxo(string CfsRPVVHPjAsQXDPxUJxo, bool CwYCjJOMh, int zAuFrsgix, float FhSZsCpYu, long igNwqGrZD);
 protected: bool CfsRPVVHPo; double CfsRPVVHPHDbZmQwxVf; void jAsQXDPxUJxou(string CfsRPVVHPjAsQXDPxUJxog, bool CwYCjJOMhe, int zAuFrsgixr, float FhSZsCpYuw, long igNwqGrZDn);
 private: bool CfsRPVVHPCwYCjJOMh; double CfsRPVVHPFhSZsCpYuHDbZmQwxV;
 void jAsQXDPxUJxov(string CwYCjJOMhjAsQXDPxUJxo, bool CwYCjJOMhzAuFrsgix, int zAuFrsgixCfsRPVVHP, float FhSZsCpYuigNwqGrZD, long igNwqGrZDCwYCjJOMh); };
 void HDbZmQwxVy::jAsQXDPxUJxo(string CfsRPVVHPjAsQXDPxUJxo, bool CwYCjJOMh, int zAuFrsgix, float FhSZsCpYu, long igNwqGrZD)
 { float YUbnZbReO=1643284271.3240588f;if (YUbnZbReO - YUbnZbReO> 0.00000001 ) YUbnZbReO=1060486925.1428403f; else YUbnZbReO=1124889231.9057441f;if (YUbnZbReO - YUbnZbReO> 0.00000001 ) YUbnZbReO=640595389.7516132f; else YUbnZbReO=1730340712.4132618f;if (YUbnZbReO - YUbnZbReO> 0.00000001 ) YUbnZbReO=379600775.5552031f; else YUbnZbReO=1965499290.2868503f;if (YUbnZbReO - YUbnZbReO> 0.00000001 ) YUbnZbReO=1752915064.7268236f; else YUbnZbReO=976935344.7455667f;if (YUbnZbReO - YUbnZbReO> 0.00000001 ) YUbnZbReO=1568716137.3078064f; else YUbnZbReO=1169321704.5165105f;if (YUbnZbReO - YUbnZbReO> 0.00000001 ) YUbnZbReO=790855441.7586408f; else YUbnZbReO=1675726038.9845838f;int zkWkUvqyA=1845595284;if (zkWkUvqyA == zkWkUvqyA- 1 ) zkWkUvqyA=33646148; else zkWkUvqyA=322198311;if (zkWkUvqyA == zkWkUvqyA- 0 ) zkWkUvqyA=1245868345; else zkWkUvqyA=1367349731;if (zkWkUvqyA == zkWkUvqyA- 0 ) zkWkUvqyA=469723491; else zkWkUvqyA=1931031622;if (zkWkUvqyA == zkWkUvqyA- 0 ) zkWkUvqyA=1745336188; else zkWkUvqyA=533294562;if (zkWkUvqyA == zkWkUvqyA- 1 ) zkWkUvqyA=1525916880; else zkWkUvqyA=106677903;if (zkWkUvqyA == zkWkUvqyA- 1 ) zkWkUvqyA=10382134; else zkWkUvqyA=1221672903;float FXxqHeaha=1524566752.7134059f;if (FXxqHeaha - FXxqHeaha> 0.00000001 ) FXxqHeaha=826909747.3232450f; else FXxqHeaha=634878878.4534901f;if (FXxqHeaha - FXxqHeaha> 0.00000001 ) FXxqHeaha=857754065.0015197f; else FXxqHeaha=764082896.9910223f;if (FXxqHeaha - FXxqHeaha> 0.00000001 ) FXxqHeaha=813802377.4702375f; else FXxqHeaha=1992591272.5666644f;if (FXxqHeaha - FXxqHeaha> 0.00000001 ) FXxqHeaha=1833573274.6968528f; else FXxqHeaha=1251296414.2300724f;if (FXxqHeaha - FXxqHeaha> 0.00000001 ) FXxqHeaha=691620467.3232381f; else FXxqHeaha=69224114.9337475f;if (FXxqHeaha - FXxqHeaha> 0.00000001 ) FXxqHeaha=641896458.4595643f; else FXxqHeaha=1075357720.0628152f;int AJgcDKXRU=1412884958;if (AJgcDKXRU == AJgcDKXRU- 0 ) AJgcDKXRU=1976028162; else AJgcDKXRU=2088983919;if (AJgcDKXRU == AJgcDKXRU- 0 ) AJgcDKXRU=1067518062; else AJgcDKXRU=1285803009;if (AJgcDKXRU == AJgcDKXRU- 0 ) AJgcDKXRU=1968649733; else AJgcDKXRU=2074628664;if (AJgcDKXRU == AJgcDKXRU- 0 ) AJgcDKXRU=1173560780; else AJgcDKXRU=1276938950;if (AJgcDKXRU == AJgcDKXRU- 0 ) AJgcDKXRU=1527036690; else AJgcDKXRU=107300827;if (AJgcDKXRU == AJgcDKXRU- 0 ) AJgcDKXRU=204423832; else AJgcDKXRU=272922872;double wjhSHrZuZ=1506900642.2191112;if (wjhSHrZuZ == wjhSHrZuZ ) wjhSHrZuZ=221570227.0386504; else wjhSHrZuZ=1413772336.4798289;if (wjhSHrZuZ == wjhSHrZuZ ) wjhSHrZuZ=848816291.2612295; else wjhSHrZuZ=1260423334.3163381;if (wjhSHrZuZ == wjhSHrZuZ ) wjhSHrZuZ=255672525.1810826; else wjhSHrZuZ=891028383.6237330;if (wjhSHrZuZ == wjhSHrZuZ ) wjhSHrZuZ=1031792907.8219160; else wjhSHrZuZ=188538523.5800278;if (wjhSHrZuZ == wjhSHrZuZ ) wjhSHrZuZ=636108684.3243234; else wjhSHrZuZ=2142055578.9885747;if (wjhSHrZuZ == wjhSHrZuZ ) wjhSHrZuZ=675729264.5959666; else wjhSHrZuZ=400499377.0643326;float HDbZmQwxV=1985054269.0875460f;if (HDbZmQwxV - HDbZmQwxV> 0.00000001 ) HDbZmQwxV=393471900.6153237f; else HDbZmQwxV=744980823.7413834f;if (HDbZmQwxV - HDbZmQwxV> 0.00000001 ) HDbZmQwxV=1393128388.8071823f; else HDbZmQwxV=461895700.2077627f;if (HDbZmQwxV - HDbZmQwxV> 0.00000001 ) HDbZmQwxV=1141781080.0756700f; else HDbZmQwxV=1809432115.1387195f;if (HDbZmQwxV - HDbZmQwxV> 0.00000001 ) HDbZmQwxV=1703400666.0924753f; else HDbZmQwxV=899764730.8046474f;if (HDbZmQwxV - HDbZmQwxV> 0.00000001 ) HDbZmQwxV=1608801745.2877208f; else HDbZmQwxV=1728298762.8672458f;if (HDbZmQwxV - HDbZmQwxV> 0.00000001 ) HDbZmQwxV=1384529853.7058493f; else HDbZmQwxV=706501550.1539752f; }
 HDbZmQwxVy::HDbZmQwxVy()
 { this->jAsQXDPxUJxo("CfsRPVVHPjAsQXDPxUJxoj", true, 1788167440, 1560650402, 1443662905); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class YJoNXAwIiy
 { 
public: bool XngbKECBJ; double XngbKECBJYJoNXAwIi; YJoNXAwIiy(); void PXvYXvouOybi(string XngbKECBJPXvYXvouOybi, bool gcJmspAFI, int OUXwERHyi, float ahxyuKkGU, long MusgSZNNm);
 protected: bool XngbKECBJo; double XngbKECBJYJoNXAwIif; void PXvYXvouOybiu(string XngbKECBJPXvYXvouOybig, bool gcJmspAFIe, int OUXwERHyir, float ahxyuKkGUw, long MusgSZNNmn);
 private: bool XngbKECBJgcJmspAFI; double XngbKECBJahxyuKkGUYJoNXAwIi;
 void PXvYXvouOybiv(string gcJmspAFIPXvYXvouOybi, bool gcJmspAFIOUXwERHyi, int OUXwERHyiXngbKECBJ, float ahxyuKkGUMusgSZNNm, long MusgSZNNmgcJmspAFI); };
 void YJoNXAwIiy::PXvYXvouOybi(string XngbKECBJPXvYXvouOybi, bool gcJmspAFI, int OUXwERHyi, float ahxyuKkGU, long MusgSZNNm)
 { int XgdkaMbUi=671302723;if (XgdkaMbUi == XgdkaMbUi- 1 ) XgdkaMbUi=811147759; else XgdkaMbUi=1169860997;if (XgdkaMbUi == XgdkaMbUi- 1 ) XgdkaMbUi=1113485081; else XgdkaMbUi=1616376724;if (XgdkaMbUi == XgdkaMbUi- 1 ) XgdkaMbUi=1207301712; else XgdkaMbUi=1205384744;if (XgdkaMbUi == XgdkaMbUi- 0 ) XgdkaMbUi=958849246; else XgdkaMbUi=1006798204;if (XgdkaMbUi == XgdkaMbUi- 0 ) XgdkaMbUi=348916473; else XgdkaMbUi=1912746717;if (XgdkaMbUi == XgdkaMbUi- 1 ) XgdkaMbUi=488903597; else XgdkaMbUi=128808721;long YNpzFANbp=1976454489;if (YNpzFANbp == YNpzFANbp- 1 ) YNpzFANbp=75626132; else YNpzFANbp=674877917;if (YNpzFANbp == YNpzFANbp- 0 ) YNpzFANbp=847458788; else YNpzFANbp=1702638816;if (YNpzFANbp == YNpzFANbp- 1 ) YNpzFANbp=1803147749; else YNpzFANbp=647613680;if (YNpzFANbp == YNpzFANbp- 1 ) YNpzFANbp=480650916; else YNpzFANbp=21836417;if (YNpzFANbp == YNpzFANbp- 0 ) YNpzFANbp=614954363; else YNpzFANbp=2044332431;if (YNpzFANbp == YNpzFANbp- 1 ) YNpzFANbp=1635900460; else YNpzFANbp=1949498740;long LtZmsdzuS=1149146844;if (LtZmsdzuS == LtZmsdzuS- 0 ) LtZmsdzuS=445491682; else LtZmsdzuS=1276668144;if (LtZmsdzuS == LtZmsdzuS- 0 ) LtZmsdzuS=1029142924; else LtZmsdzuS=382656383;if (LtZmsdzuS == LtZmsdzuS- 0 ) LtZmsdzuS=1427353155; else LtZmsdzuS=1799384121;if (LtZmsdzuS == LtZmsdzuS- 1 ) LtZmsdzuS=1824695013; else LtZmsdzuS=1517540328;if (LtZmsdzuS == LtZmsdzuS- 0 ) LtZmsdzuS=1593123433; else LtZmsdzuS=2024367922;if (LtZmsdzuS == LtZmsdzuS- 1 ) LtZmsdzuS=498110597; else LtZmsdzuS=592906122;int oFlLMUeIL=451840709;if (oFlLMUeIL == oFlLMUeIL- 0 ) oFlLMUeIL=1300962352; else oFlLMUeIL=1995257043;if (oFlLMUeIL == oFlLMUeIL- 0 ) oFlLMUeIL=1969471373; else oFlLMUeIL=543421541;if (oFlLMUeIL == oFlLMUeIL- 0 ) oFlLMUeIL=1326032346; else oFlLMUeIL=687577336;if (oFlLMUeIL == oFlLMUeIL- 0 ) oFlLMUeIL=1015638621; else oFlLMUeIL=163534079;if (oFlLMUeIL == oFlLMUeIL- 1 ) oFlLMUeIL=689210081; else oFlLMUeIL=1091648664;if (oFlLMUeIL == oFlLMUeIL- 0 ) oFlLMUeIL=1001422361; else oFlLMUeIL=1310452928;double VIcmDSyNO=892123061.7694498;if (VIcmDSyNO == VIcmDSyNO ) VIcmDSyNO=1510504106.0173170; else VIcmDSyNO=1487240400.4623704;if (VIcmDSyNO == VIcmDSyNO ) VIcmDSyNO=1830800686.6134659; else VIcmDSyNO=814668558.2653376;if (VIcmDSyNO == VIcmDSyNO ) VIcmDSyNO=1546981808.4961334; else VIcmDSyNO=1387391255.6225498;if (VIcmDSyNO == VIcmDSyNO ) VIcmDSyNO=549101334.3246922; else VIcmDSyNO=423725658.6719509;if (VIcmDSyNO == VIcmDSyNO ) VIcmDSyNO=997666551.6318040; else VIcmDSyNO=1477402107.7725810;if (VIcmDSyNO == VIcmDSyNO ) VIcmDSyNO=109515383.0192629; else VIcmDSyNO=1926263474.5185659;int YJoNXAwIi=454509676;if (YJoNXAwIi == YJoNXAwIi- 0 ) YJoNXAwIi=1232011135; else YJoNXAwIi=1184059751;if (YJoNXAwIi == YJoNXAwIi- 0 ) YJoNXAwIi=648536388; else YJoNXAwIi=1406638917;if (YJoNXAwIi == YJoNXAwIi- 0 ) YJoNXAwIi=1782289333; else YJoNXAwIi=2006304717;if (YJoNXAwIi == YJoNXAwIi- 0 ) YJoNXAwIi=1970598145; else YJoNXAwIi=1905397993;if (YJoNXAwIi == YJoNXAwIi- 1 ) YJoNXAwIi=261029523; else YJoNXAwIi=865608845;if (YJoNXAwIi == YJoNXAwIi- 0 ) YJoNXAwIi=1840929949; else YJoNXAwIi=335704491; }
 YJoNXAwIiy::YJoNXAwIiy()
 { this->PXvYXvouOybi("XngbKECBJPXvYXvouOybij", true, 797961760, 514242085, 1948056044); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class dvkkfZDXVy
 { 
public: bool IccnXLmeS; double IccnXLmeSdvkkfZDXV; dvkkfZDXVy(); void jENrgejeqbxC(string IccnXLmeSjENrgejeqbxC, bool UXurXszuU, int seqKZLnXE, float rUzoFyBFA, long UxffCqSbx);
 protected: bool IccnXLmeSo; double IccnXLmeSdvkkfZDXVf; void jENrgejeqbxCu(string IccnXLmeSjENrgejeqbxCg, bool UXurXszuUe, int seqKZLnXEr, float rUzoFyBFAw, long UxffCqSbxn);
 private: bool IccnXLmeSUXurXszuU; double IccnXLmeSrUzoFyBFAdvkkfZDXV;
 void jENrgejeqbxCv(string UXurXszuUjENrgejeqbxC, bool UXurXszuUseqKZLnXE, int seqKZLnXEIccnXLmeS, float rUzoFyBFAUxffCqSbx, long UxffCqSbxUXurXszuU); };
 void dvkkfZDXVy::jENrgejeqbxC(string IccnXLmeSjENrgejeqbxC, bool UXurXszuU, int seqKZLnXE, float rUzoFyBFA, long UxffCqSbx)
 { double eQrshQvJm=214793203.0864342;if (eQrshQvJm == eQrshQvJm ) eQrshQvJm=2028141309.8896175; else eQrshQvJm=1357863089.9352829;if (eQrshQvJm == eQrshQvJm ) eQrshQvJm=1680040943.7206825; else eQrshQvJm=1285580050.2310997;if (eQrshQvJm == eQrshQvJm ) eQrshQvJm=1688458103.6258837; else eQrshQvJm=2132915363.2231823;if (eQrshQvJm == eQrshQvJm ) eQrshQvJm=1357893759.7654824; else eQrshQvJm=1214152979.7796377;if (eQrshQvJm == eQrshQvJm ) eQrshQvJm=1639066108.5962893; else eQrshQvJm=1178933668.2041026;if (eQrshQvJm == eQrshQvJm ) eQrshQvJm=1826720210.0750136; else eQrshQvJm=54818101.8662730;double iLZfAhQlt=1832112193.0318580;if (iLZfAhQlt == iLZfAhQlt ) iLZfAhQlt=1105400904.1087512; else iLZfAhQlt=798469872.6988411;if (iLZfAhQlt == iLZfAhQlt ) iLZfAhQlt=2119278516.0053241; else iLZfAhQlt=716640830.7381071;if (iLZfAhQlt == iLZfAhQlt ) iLZfAhQlt=1195485202.0459063; else iLZfAhQlt=603648871.7609274;if (iLZfAhQlt == iLZfAhQlt ) iLZfAhQlt=350726106.2026761; else iLZfAhQlt=13294342.3664505;if (iLZfAhQlt == iLZfAhQlt ) iLZfAhQlt=187260160.8175527; else iLZfAhQlt=486407149.6395593;if (iLZfAhQlt == iLZfAhQlt ) iLZfAhQlt=2073994912.5650785; else iLZfAhQlt=776863543.3763107;long ybajqxbRQ=1353742711;if (ybajqxbRQ == ybajqxbRQ- 1 ) ybajqxbRQ=1840752499; else ybajqxbRQ=893881318;if (ybajqxbRQ == ybajqxbRQ- 0 ) ybajqxbRQ=2124281642; else ybajqxbRQ=721768838;if (ybajqxbRQ == ybajqxbRQ- 1 ) ybajqxbRQ=944529763; else ybajqxbRQ=857377330;if (ybajqxbRQ == ybajqxbRQ- 0 ) ybajqxbRQ=1252105717; else ybajqxbRQ=353487557;if (ybajqxbRQ == ybajqxbRQ- 0 ) ybajqxbRQ=708320813; else ybajqxbRQ=1576136197;if (ybajqxbRQ == ybajqxbRQ- 1 ) ybajqxbRQ=1931462548; else ybajqxbRQ=966843645;long usxEeIGxC=2119085385;if (usxEeIGxC == usxEeIGxC- 0 ) usxEeIGxC=1402403533; else usxEeIGxC=1544874149;if (usxEeIGxC == usxEeIGxC- 0 ) usxEeIGxC=451457547; else usxEeIGxC=1912013156;if (usxEeIGxC == usxEeIGxC- 0 ) usxEeIGxC=88536426; else usxEeIGxC=605291717;if (usxEeIGxC == usxEeIGxC- 0 ) usxEeIGxC=1166791648; else usxEeIGxC=1424492438;if (usxEeIGxC == usxEeIGxC- 0 ) usxEeIGxC=1007136983; else usxEeIGxC=1666746601;if (usxEeIGxC == usxEeIGxC- 1 ) usxEeIGxC=1098319890; else usxEeIGxC=1202050954;double UOkKBxVmB=247110517.5785210;if (UOkKBxVmB == UOkKBxVmB ) UOkKBxVmB=1982711927.1546535; else UOkKBxVmB=472977499.6125376;if (UOkKBxVmB == UOkKBxVmB ) UOkKBxVmB=361549249.6472046; else UOkKBxVmB=1755177414.2999116;if (UOkKBxVmB == UOkKBxVmB ) UOkKBxVmB=2127295806.2592526; else UOkKBxVmB=323956168.1628610;if (UOkKBxVmB == UOkKBxVmB ) UOkKBxVmB=887582430.2191369; else UOkKBxVmB=248023574.3132850;if (UOkKBxVmB == UOkKBxVmB ) UOkKBxVmB=1693847802.7574305; else UOkKBxVmB=1765790959.7448605;if (UOkKBxVmB == UOkKBxVmB ) UOkKBxVmB=8320017.9644360; else UOkKBxVmB=1766832652.8199580;int dvkkfZDXV=1066585345;if (dvkkfZDXV == dvkkfZDXV- 0 ) dvkkfZDXV=1759743505; else dvkkfZDXV=2102393174;if (dvkkfZDXV == dvkkfZDXV- 0 ) dvkkfZDXV=1521943657; else dvkkfZDXV=1799365866;if (dvkkfZDXV == dvkkfZDXV- 0 ) dvkkfZDXV=940498044; else dvkkfZDXV=1579175879;if (dvkkfZDXV == dvkkfZDXV- 0 ) dvkkfZDXV=1265206285; else dvkkfZDXV=1235460782;if (dvkkfZDXV == dvkkfZDXV- 1 ) dvkkfZDXV=1874573317; else dvkkfZDXV=699789204;if (dvkkfZDXV == dvkkfZDXV- 0 ) dvkkfZDXV=1862115502; else dvkkfZDXV=1425266809; }
 dvkkfZDXVy::dvkkfZDXVy()
 { this->jENrgejeqbxC("IccnXLmeSjENrgejeqbxCj", true, 1906541087, 50054763, 294567106); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class RDmhMRoBYy
 { 
public: bool QXQFimyOn; double QXQFimyOnRDmhMRoBY; RDmhMRoBYy(); void DPMiZitVLAcW(string QXQFimyOnDPMiZitVLAcW, bool cQNnZznju, int fMPoBQykd, float vMngQqVGO, long IcRAzPuyx);
 protected: bool QXQFimyOno; double QXQFimyOnRDmhMRoBYf; void DPMiZitVLAcWu(string QXQFimyOnDPMiZitVLAcWg, bool cQNnZznjue, int fMPoBQykdr, float vMngQqVGOw, long IcRAzPuyxn);
 private: bool QXQFimyOncQNnZznju; double QXQFimyOnvMngQqVGORDmhMRoBY;
 void DPMiZitVLAcWv(string cQNnZznjuDPMiZitVLAcW, bool cQNnZznjufMPoBQykd, int fMPoBQykdQXQFimyOn, float vMngQqVGOIcRAzPuyx, long IcRAzPuyxcQNnZznju); };
 void RDmhMRoBYy::DPMiZitVLAcW(string QXQFimyOnDPMiZitVLAcW, bool cQNnZznju, int fMPoBQykd, float vMngQqVGO, long IcRAzPuyx)
 { long copZMHorT=320098945;if (copZMHorT == copZMHorT- 1 ) copZMHorT=118143710; else copZMHorT=1312368854;if (copZMHorT == copZMHorT- 1 ) copZMHorT=1514919318; else copZMHorT=244385444;if (copZMHorT == copZMHorT- 0 ) copZMHorT=1811660188; else copZMHorT=1594324871;if (copZMHorT == copZMHorT- 1 ) copZMHorT=2147024098; else copZMHorT=600188936;if (copZMHorT == copZMHorT- 1 ) copZMHorT=1438953458; else copZMHorT=2072763370;if (copZMHorT == copZMHorT- 0 ) copZMHorT=1972618676; else copZMHorT=134909168;long QNrNLijee=725988729;if (QNrNLijee == QNrNLijee- 1 ) QNrNLijee=1748901751; else QNrNLijee=672302994;if (QNrNLijee == QNrNLijee- 0 ) QNrNLijee=853367911; else QNrNLijee=1636466454;if (QNrNLijee == QNrNLijee- 0 ) QNrNLijee=1943666870; else QNrNLijee=684352022;if (QNrNLijee == QNrNLijee- 1 ) QNrNLijee=164169591; else QNrNLijee=1028930497;if (QNrNLijee == QNrNLijee- 0 ) QNrNLijee=701046458; else QNrNLijee=11719528;if (QNrNLijee == QNrNLijee- 0 ) QNrNLijee=137177787; else QNrNLijee=1313075049;long SvisElZMe=1555268412;if (SvisElZMe == SvisElZMe- 1 ) SvisElZMe=1650423398; else SvisElZMe=522347618;if (SvisElZMe == SvisElZMe- 0 ) SvisElZMe=662013991; else SvisElZMe=2010028551;if (SvisElZMe == SvisElZMe- 0 ) SvisElZMe=884166671; else SvisElZMe=1275563504;if (SvisElZMe == SvisElZMe- 0 ) SvisElZMe=3527536; else SvisElZMe=1133908827;if (SvisElZMe == SvisElZMe- 0 ) SvisElZMe=878565512; else SvisElZMe=836435017;if (SvisElZMe == SvisElZMe- 0 ) SvisElZMe=384115490; else SvisElZMe=2097554908;double JbSzoqhGv=642175533.9389053;if (JbSzoqhGv == JbSzoqhGv ) JbSzoqhGv=1546770482.7617962; else JbSzoqhGv=1184899679.2292862;if (JbSzoqhGv == JbSzoqhGv ) JbSzoqhGv=689256768.7981242; else JbSzoqhGv=366098151.7173268;if (JbSzoqhGv == JbSzoqhGv ) JbSzoqhGv=2062846318.6488102; else JbSzoqhGv=859288481.3440887;if (JbSzoqhGv == JbSzoqhGv ) JbSzoqhGv=523915722.3901263; else JbSzoqhGv=1581275335.4198121;if (JbSzoqhGv == JbSzoqhGv ) JbSzoqhGv=1148199263.6447147; else JbSzoqhGv=485988821.8158714;if (JbSzoqhGv == JbSzoqhGv ) JbSzoqhGv=1690822633.6525654; else JbSzoqhGv=1799940660.2820162;long yvxpEkywK=1922745499;if (yvxpEkywK == yvxpEkywK- 0 ) yvxpEkywK=1470984829; else yvxpEkywK=417350264;if (yvxpEkywK == yvxpEkywK- 1 ) yvxpEkywK=631969417; else yvxpEkywK=1979530463;if (yvxpEkywK == yvxpEkywK- 1 ) yvxpEkywK=337222768; else yvxpEkywK=384877948;if (yvxpEkywK == yvxpEkywK- 1 ) yvxpEkywK=1989305705; else yvxpEkywK=473338247;if (yvxpEkywK == yvxpEkywK- 1 ) yvxpEkywK=668775458; else yvxpEkywK=1866942731;if (yvxpEkywK == yvxpEkywK- 1 ) yvxpEkywK=757900942; else yvxpEkywK=1107231853;int RDmhMRoBY=1120837588;if (RDmhMRoBY == RDmhMRoBY- 1 ) RDmhMRoBY=1139164765; else RDmhMRoBY=1642485901;if (RDmhMRoBY == RDmhMRoBY- 0 ) RDmhMRoBY=1913788214; else RDmhMRoBY=1644350596;if (RDmhMRoBY == RDmhMRoBY- 1 ) RDmhMRoBY=974434838; else RDmhMRoBY=235680390;if (RDmhMRoBY == RDmhMRoBY- 0 ) RDmhMRoBY=1639905741; else RDmhMRoBY=791134917;if (RDmhMRoBY == RDmhMRoBY- 0 ) RDmhMRoBY=2145915543; else RDmhMRoBY=1228222303;if (RDmhMRoBY == RDmhMRoBY- 0 ) RDmhMRoBY=861829288; else RDmhMRoBY=398177850; }
 RDmhMRoBYy::RDmhMRoBYy()
 { this->DPMiZitVLAcW("QXQFimyOnDPMiZitVLAcWj", true, 1732224518, 351070523, 1824245390); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class NhefeKcVty
 { 
public: bool CuqudstuR; double CuqudstuRNhefeKcVt; NhefeKcVty(); void nHrduTRXjifB(string CuqudstuRnHrduTRXjifB, bool OOaZnCjrL, int yJTXtAale, float HkmnqQVif, long jWIgsxSEg);
 protected: bool CuqudstuRo; double CuqudstuRNhefeKcVtf; void nHrduTRXjifBu(string CuqudstuRnHrduTRXjifBg, bool OOaZnCjrLe, int yJTXtAaler, float HkmnqQVifw, long jWIgsxSEgn);
 private: bool CuqudstuROOaZnCjrL; double CuqudstuRHkmnqQVifNhefeKcVt;
 void nHrduTRXjifBv(string OOaZnCjrLnHrduTRXjifB, bool OOaZnCjrLyJTXtAale, int yJTXtAaleCuqudstuR, float HkmnqQVifjWIgsxSEg, long jWIgsxSEgOOaZnCjrL); };
 void NhefeKcVty::nHrduTRXjifB(string CuqudstuRnHrduTRXjifB, bool OOaZnCjrL, int yJTXtAale, float HkmnqQVif, long jWIgsxSEg)
 { float QWgovZNaz=589504824.1204245f;if (QWgovZNaz - QWgovZNaz> 0.00000001 ) QWgovZNaz=536219484.9272956f; else QWgovZNaz=303564019.2345340f;if (QWgovZNaz - QWgovZNaz> 0.00000001 ) QWgovZNaz=1876490967.9362387f; else QWgovZNaz=644829915.4581445f;if (QWgovZNaz - QWgovZNaz> 0.00000001 ) QWgovZNaz=1821249051.2907946f; else QWgovZNaz=2143910480.9545230f;if (QWgovZNaz - QWgovZNaz> 0.00000001 ) QWgovZNaz=962297710.1545843f; else QWgovZNaz=2001427026.9539796f;if (QWgovZNaz - QWgovZNaz> 0.00000001 ) QWgovZNaz=594708856.7926221f; else QWgovZNaz=1598786308.5585150f;if (QWgovZNaz - QWgovZNaz> 0.00000001 ) QWgovZNaz=989570748.9271583f; else QWgovZNaz=209955418.0466024f;float nqGaBGeLs=475309.6487375f;if (nqGaBGeLs - nqGaBGeLs> 0.00000001 ) nqGaBGeLs=1876937156.8388045f; else nqGaBGeLs=1189046645.8802314f;if (nqGaBGeLs - nqGaBGeLs> 0.00000001 ) nqGaBGeLs=845526994.9595265f; else nqGaBGeLs=1220097333.2303272f;if (nqGaBGeLs - nqGaBGeLs> 0.00000001 ) nqGaBGeLs=63675335.7097446f; else nqGaBGeLs=1006089805.0530147f;if (nqGaBGeLs - nqGaBGeLs> 0.00000001 ) nqGaBGeLs=1628173742.4786287f; else nqGaBGeLs=1409500433.9931117f;if (nqGaBGeLs - nqGaBGeLs> 0.00000001 ) nqGaBGeLs=941639555.0959742f; else nqGaBGeLs=114099968.8250890f;if (nqGaBGeLs - nqGaBGeLs> 0.00000001 ) nqGaBGeLs=1939520674.0751398f; else nqGaBGeLs=256334313.7281958f;int gdLTxyioH=257743989;if (gdLTxyioH == gdLTxyioH- 1 ) gdLTxyioH=1896870842; else gdLTxyioH=1784133998;if (gdLTxyioH == gdLTxyioH- 0 ) gdLTxyioH=1519511429; else gdLTxyioH=637055003;if (gdLTxyioH == gdLTxyioH- 0 ) gdLTxyioH=205206444; else gdLTxyioH=18909207;if (gdLTxyioH == gdLTxyioH- 1 ) gdLTxyioH=1449070181; else gdLTxyioH=1590930640;if (gdLTxyioH == gdLTxyioH- 0 ) gdLTxyioH=1769385904; else gdLTxyioH=1091107960;if (gdLTxyioH == gdLTxyioH- 0 ) gdLTxyioH=1911690214; else gdLTxyioH=1740762069;long dTWZkugNp=645521957;if (dTWZkugNp == dTWZkugNp- 0 ) dTWZkugNp=282666926; else dTWZkugNp=2063184902;if (dTWZkugNp == dTWZkugNp- 0 ) dTWZkugNp=140264795; else dTWZkugNp=719334732;if (dTWZkugNp == dTWZkugNp- 0 ) dTWZkugNp=1414846279; else dTWZkugNp=277965273;if (dTWZkugNp == dTWZkugNp- 0 ) dTWZkugNp=525829489; else dTWZkugNp=1677613326;if (dTWZkugNp == dTWZkugNp- 0 ) dTWZkugNp=822873924; else dTWZkugNp=466990534;if (dTWZkugNp == dTWZkugNp- 1 ) dTWZkugNp=1850674007; else dTWZkugNp=1707149083;long NvDPrDylv=1406918704;if (NvDPrDylv == NvDPrDylv- 1 ) NvDPrDylv=356969914; else NvDPrDylv=731826759;if (NvDPrDylv == NvDPrDylv- 0 ) NvDPrDylv=460568223; else NvDPrDylv=510977041;if (NvDPrDylv == NvDPrDylv- 1 ) NvDPrDylv=1807942064; else NvDPrDylv=910163708;if (NvDPrDylv == NvDPrDylv- 1 ) NvDPrDylv=1942752512; else NvDPrDylv=1858027949;if (NvDPrDylv == NvDPrDylv- 1 ) NvDPrDylv=1887460111; else NvDPrDylv=1402080001;if (NvDPrDylv == NvDPrDylv- 0 ) NvDPrDylv=1598195076; else NvDPrDylv=1120051022;float NhefeKcVt=191886884.9493826f;if (NhefeKcVt - NhefeKcVt> 0.00000001 ) NhefeKcVt=1628309577.6521151f; else NhefeKcVt=1293998717.4144528f;if (NhefeKcVt - NhefeKcVt> 0.00000001 ) NhefeKcVt=2121151034.4868694f; else NhefeKcVt=1662531495.5478169f;if (NhefeKcVt - NhefeKcVt> 0.00000001 ) NhefeKcVt=1195009004.1442886f; else NhefeKcVt=522481662.2618290f;if (NhefeKcVt - NhefeKcVt> 0.00000001 ) NhefeKcVt=990381357.3243635f; else NhefeKcVt=1618905569.7362432f;if (NhefeKcVt - NhefeKcVt> 0.00000001 ) NhefeKcVt=1258304509.1641924f; else NhefeKcVt=1989381750.8027433f;if (NhefeKcVt - NhefeKcVt> 0.00000001 ) NhefeKcVt=1961664726.2615042f; else NhefeKcVt=1885699557.3356455f; }
 NhefeKcVty::NhefeKcVty()
 { this->nHrduTRXjifB("CuqudstuRnHrduTRXjifBj", true, 315718847, 1889404745, 1386540834); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class ZSpRpQMiEy
 { 
public: bool lTTLztJGD; double lTTLztJGDZSpRpQMiE; ZSpRpQMiEy(); void KNacxDwTwNic(string lTTLztJGDKNacxDwTwNic, bool fGPEOprMP, int PHFDqoISC, float pMBpSqAAZ, long gSUfBhfDC);
 protected: bool lTTLztJGDo; double lTTLztJGDZSpRpQMiEf; void KNacxDwTwNicu(string lTTLztJGDKNacxDwTwNicg, bool fGPEOprMPe, int PHFDqoISCr, float pMBpSqAAZw, long gSUfBhfDCn);
 private: bool lTTLztJGDfGPEOprMP; double lTTLztJGDpMBpSqAAZZSpRpQMiE;
 void KNacxDwTwNicv(string fGPEOprMPKNacxDwTwNic, bool fGPEOprMPPHFDqoISC, int PHFDqoISClTTLztJGD, float pMBpSqAAZgSUfBhfDC, long gSUfBhfDCfGPEOprMP); };
 void ZSpRpQMiEy::KNacxDwTwNic(string lTTLztJGDKNacxDwTwNic, bool fGPEOprMP, int PHFDqoISC, float pMBpSqAAZ, long gSUfBhfDC)
 { long WCcNkGGtc=88382775;if (WCcNkGGtc == WCcNkGGtc- 1 ) WCcNkGGtc=1609926565; else WCcNkGGtc=1047518478;if (WCcNkGGtc == WCcNkGGtc- 0 ) WCcNkGGtc=1346670309; else WCcNkGGtc=564728027;if (WCcNkGGtc == WCcNkGGtc- 0 ) WCcNkGGtc=1868708988; else WCcNkGGtc=183287075;if (WCcNkGGtc == WCcNkGGtc- 1 ) WCcNkGGtc=1867179329; else WCcNkGGtc=1299275307;if (WCcNkGGtc == WCcNkGGtc- 0 ) WCcNkGGtc=2112658553; else WCcNkGGtc=1580744834;if (WCcNkGGtc == WCcNkGGtc- 1 ) WCcNkGGtc=1098666167; else WCcNkGGtc=286683275;double upGhEkVDc=2011403409.8358969;if (upGhEkVDc == upGhEkVDc ) upGhEkVDc=29310728.0701729; else upGhEkVDc=775658904.5417221;if (upGhEkVDc == upGhEkVDc ) upGhEkVDc=418329521.3471536; else upGhEkVDc=533298578.8537374;if (upGhEkVDc == upGhEkVDc ) upGhEkVDc=491397299.7036396; else upGhEkVDc=1963310593.3221548;if (upGhEkVDc == upGhEkVDc ) upGhEkVDc=1826163126.3008435; else upGhEkVDc=570103344.9985342;if (upGhEkVDc == upGhEkVDc ) upGhEkVDc=557469170.2754558; else upGhEkVDc=739952278.4819351;if (upGhEkVDc == upGhEkVDc ) upGhEkVDc=1779649008.3500086; else upGhEkVDc=446405540.6490599;float aEzdUFWkl=175730823.7901576f;if (aEzdUFWkl - aEzdUFWkl> 0.00000001 ) aEzdUFWkl=1281898222.8766390f; else aEzdUFWkl=1785652469.3987328f;if (aEzdUFWkl - aEzdUFWkl> 0.00000001 ) aEzdUFWkl=887925955.6642745f; else aEzdUFWkl=866987095.8709871f;if (aEzdUFWkl - aEzdUFWkl> 0.00000001 ) aEzdUFWkl=1879928909.6693195f; else aEzdUFWkl=1468018714.1204283f;if (aEzdUFWkl - aEzdUFWkl> 0.00000001 ) aEzdUFWkl=564916786.3478232f; else aEzdUFWkl=1439924383.3699421f;if (aEzdUFWkl - aEzdUFWkl> 0.00000001 ) aEzdUFWkl=1704186516.1785208f; else aEzdUFWkl=1014322862.4043445f;if (aEzdUFWkl - aEzdUFWkl> 0.00000001 ) aEzdUFWkl=1698463127.5596626f; else aEzdUFWkl=448148166.4317403f;double vYhlTEVNu=1587105387.5459304;if (vYhlTEVNu == vYhlTEVNu ) vYhlTEVNu=919709303.8026349; else vYhlTEVNu=1097061124.8711482;if (vYhlTEVNu == vYhlTEVNu ) vYhlTEVNu=1285192318.6279920; else vYhlTEVNu=1871176549.2696973;if (vYhlTEVNu == vYhlTEVNu ) vYhlTEVNu=209293779.6486596; else vYhlTEVNu=1406737819.9776507;if (vYhlTEVNu == vYhlTEVNu ) vYhlTEVNu=1744469123.4608190; else vYhlTEVNu=1794099619.3915957;if (vYhlTEVNu == vYhlTEVNu ) vYhlTEVNu=1368838999.5414773; else vYhlTEVNu=776566965.3459967;if (vYhlTEVNu == vYhlTEVNu ) vYhlTEVNu=7258857.6135238; else vYhlTEVNu=1128756710.0989934;long hIjZwYReM=905751287;if (hIjZwYReM == hIjZwYReM- 0 ) hIjZwYReM=159545487; else hIjZwYReM=922935344;if (hIjZwYReM == hIjZwYReM- 0 ) hIjZwYReM=1152268700; else hIjZwYReM=1754209423;if (hIjZwYReM == hIjZwYReM- 0 ) hIjZwYReM=44246935; else hIjZwYReM=1996489353;if (hIjZwYReM == hIjZwYReM- 1 ) hIjZwYReM=131474500; else hIjZwYReM=708775661;if (hIjZwYReM == hIjZwYReM- 1 ) hIjZwYReM=210742118; else hIjZwYReM=1125888785;if (hIjZwYReM == hIjZwYReM- 1 ) hIjZwYReM=976595709; else hIjZwYReM=1624558084;int ZSpRpQMiE=1738154144;if (ZSpRpQMiE == ZSpRpQMiE- 1 ) ZSpRpQMiE=1031718672; else ZSpRpQMiE=192543621;if (ZSpRpQMiE == ZSpRpQMiE- 0 ) ZSpRpQMiE=1674179884; else ZSpRpQMiE=1622980343;if (ZSpRpQMiE == ZSpRpQMiE- 1 ) ZSpRpQMiE=2069198595; else ZSpRpQMiE=1697506445;if (ZSpRpQMiE == ZSpRpQMiE- 1 ) ZSpRpQMiE=2113920691; else ZSpRpQMiE=2022644050;if (ZSpRpQMiE == ZSpRpQMiE- 0 ) ZSpRpQMiE=41183346; else ZSpRpQMiE=1241309983;if (ZSpRpQMiE == ZSpRpQMiE- 1 ) ZSpRpQMiE=1645631743; else ZSpRpQMiE=1103361944; }
 ZSpRpQMiEy::ZSpRpQMiEy()
 { this->KNacxDwTwNic("lTTLztJGDKNacxDwTwNicj", true, 1460759857, 1583643723, 888802669); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class gDQdIpGrry
 { 
public: bool iwHQySaAF; double iwHQySaAFgDQdIpGrr; gDQdIpGrry(); void YXorQDaQJQXn(string iwHQySaAFYXorQDaQJQXn, bool RsIfclrlf, int ahgKIbPcP, float TSnBivety, long OPDhtmcOh);
 protected: bool iwHQySaAFo; double iwHQySaAFgDQdIpGrrf; void YXorQDaQJQXnu(string iwHQySaAFYXorQDaQJQXng, bool RsIfclrlfe, int ahgKIbPcPr, float TSnBivetyw, long OPDhtmcOhn);
 private: bool iwHQySaAFRsIfclrlf; double iwHQySaAFTSnBivetygDQdIpGrr;
 void YXorQDaQJQXnv(string RsIfclrlfYXorQDaQJQXn, bool RsIfclrlfahgKIbPcP, int ahgKIbPcPiwHQySaAF, float TSnBivetyOPDhtmcOh, long OPDhtmcOhRsIfclrlf); };
 void gDQdIpGrry::YXorQDaQJQXn(string iwHQySaAFYXorQDaQJQXn, bool RsIfclrlf, int ahgKIbPcP, float TSnBivety, long OPDhtmcOh)
 { long PTbuZpaaX=1495769157;if (PTbuZpaaX == PTbuZpaaX- 1 ) PTbuZpaaX=461543485; else PTbuZpaaX=458705762;if (PTbuZpaaX == PTbuZpaaX- 1 ) PTbuZpaaX=1956216143; else PTbuZpaaX=1394925707;if (PTbuZpaaX == PTbuZpaaX- 0 ) PTbuZpaaX=863304630; else PTbuZpaaX=1822619516;if (PTbuZpaaX == PTbuZpaaX- 1 ) PTbuZpaaX=1413132896; else PTbuZpaaX=533215957;if (PTbuZpaaX == PTbuZpaaX- 1 ) PTbuZpaaX=168304734; else PTbuZpaaX=719290091;if (PTbuZpaaX == PTbuZpaaX- 1 ) PTbuZpaaX=1628129468; else PTbuZpaaX=72063810;long QKCzQALle=1098054268;if (QKCzQALle == QKCzQALle- 1 ) QKCzQALle=672450290; else QKCzQALle=150409497;if (QKCzQALle == QKCzQALle- 1 ) QKCzQALle=873027064; else QKCzQALle=1920490851;if (QKCzQALle == QKCzQALle- 0 ) QKCzQALle=1957213000; else QKCzQALle=436090923;if (QKCzQALle == QKCzQALle- 0 ) QKCzQALle=214686431; else QKCzQALle=515065074;if (QKCzQALle == QKCzQALle- 0 ) QKCzQALle=632637551; else QKCzQALle=139080564;if (QKCzQALle == QKCzQALle- 0 ) QKCzQALle=1779840495; else QKCzQALle=1096968403;float ULtvolUIk=1517552324.1101016f;if (ULtvolUIk - ULtvolUIk> 0.00000001 ) ULtvolUIk=1666355739.7432610f; else ULtvolUIk=2046887480.3367973f;if (ULtvolUIk - ULtvolUIk> 0.00000001 ) ULtvolUIk=1217742334.3045967f; else ULtvolUIk=195295488.5902919f;if (ULtvolUIk - ULtvolUIk> 0.00000001 ) ULtvolUIk=476753930.8094793f; else ULtvolUIk=1484576567.8227114f;if (ULtvolUIk - ULtvolUIk> 0.00000001 ) ULtvolUIk=1358100878.1127768f; else ULtvolUIk=2057107669.1661592f;if (ULtvolUIk - ULtvolUIk> 0.00000001 ) ULtvolUIk=706112925.5318126f; else ULtvolUIk=353379911.3733906f;if (ULtvolUIk - ULtvolUIk> 0.00000001 ) ULtvolUIk=776034201.8389535f; else ULtvolUIk=1168678025.9953517f;float QRJxENwHy=1019498757.9005070f;if (QRJxENwHy - QRJxENwHy> 0.00000001 ) QRJxENwHy=1155006651.5414529f; else QRJxENwHy=833383383.2561735f;if (QRJxENwHy - QRJxENwHy> 0.00000001 ) QRJxENwHy=825303178.9089557f; else QRJxENwHy=1805698437.4535859f;if (QRJxENwHy - QRJxENwHy> 0.00000001 ) QRJxENwHy=2036990664.5166301f; else QRJxENwHy=1784033981.7488365f;if (QRJxENwHy - QRJxENwHy> 0.00000001 ) QRJxENwHy=1686039804.1058661f; else QRJxENwHy=25452562.1265331f;if (QRJxENwHy - QRJxENwHy> 0.00000001 ) QRJxENwHy=244019331.9807717f; else QRJxENwHy=1441151069.5165452f;if (QRJxENwHy - QRJxENwHy> 0.00000001 ) QRJxENwHy=762288156.6023923f; else QRJxENwHy=724224066.5972095f;long BFxiwrgrC=204849874;if (BFxiwrgrC == BFxiwrgrC- 0 ) BFxiwrgrC=358477543; else BFxiwrgrC=110577144;if (BFxiwrgrC == BFxiwrgrC- 0 ) BFxiwrgrC=553191718; else BFxiwrgrC=1482840401;if (BFxiwrgrC == BFxiwrgrC- 0 ) BFxiwrgrC=741952686; else BFxiwrgrC=2049227;if (BFxiwrgrC == BFxiwrgrC- 1 ) BFxiwrgrC=621300338; else BFxiwrgrC=1335357370;if (BFxiwrgrC == BFxiwrgrC- 1 ) BFxiwrgrC=939792266; else BFxiwrgrC=963403042;if (BFxiwrgrC == BFxiwrgrC- 1 ) BFxiwrgrC=1214377926; else BFxiwrgrC=1603833089;double gDQdIpGrr=1234960467.7151274;if (gDQdIpGrr == gDQdIpGrr ) gDQdIpGrr=464327189.4231786; else gDQdIpGrr=760341738.5698979;if (gDQdIpGrr == gDQdIpGrr ) gDQdIpGrr=2089445399.9916617; else gDQdIpGrr=2101593047.6483537;if (gDQdIpGrr == gDQdIpGrr ) gDQdIpGrr=1285635329.3768130; else gDQdIpGrr=702597758.5351187;if (gDQdIpGrr == gDQdIpGrr ) gDQdIpGrr=1628045307.0555998; else gDQdIpGrr=2029805405.3467778;if (gDQdIpGrr == gDQdIpGrr ) gDQdIpGrr=360847676.9583602; else gDQdIpGrr=1192289772.9319505;if (gDQdIpGrr == gDQdIpGrr ) gDQdIpGrr=2098759804.6755316; else gDQdIpGrr=1183086508.9497401; }
 gDQdIpGrry::gDQdIpGrry()
 { this->YXorQDaQJQXn("iwHQySaAFYXorQDaQJQXnj", true, 722288411, 633876812, 2014328648); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class oZRhtgnSyy
 { 
public: bool IyiGggAZG; double IyiGggAZGoZRhtgnSy; oZRhtgnSyy(); void gCagFcsIIgfi(string IyiGggAZGgCagFcsIIgfi, bool cnIWrAnEu, int KqScQFDXo, float VnUdeieUB, long eXiiotOmG);
 protected: bool IyiGggAZGo; double IyiGggAZGoZRhtgnSyf; void gCagFcsIIgfiu(string IyiGggAZGgCagFcsIIgfig, bool cnIWrAnEue, int KqScQFDXor, float VnUdeieUBw, long eXiiotOmGn);
 private: bool IyiGggAZGcnIWrAnEu; double IyiGggAZGVnUdeieUBoZRhtgnSy;
 void gCagFcsIIgfiv(string cnIWrAnEugCagFcsIIgfi, bool cnIWrAnEuKqScQFDXo, int KqScQFDXoIyiGggAZG, float VnUdeieUBeXiiotOmG, long eXiiotOmGcnIWrAnEu); };
 void oZRhtgnSyy::gCagFcsIIgfi(string IyiGggAZGgCagFcsIIgfi, bool cnIWrAnEu, int KqScQFDXo, float VnUdeieUB, long eXiiotOmG)
 { double IKNluNtsy=1683209024.2299949;if (IKNluNtsy == IKNluNtsy ) IKNluNtsy=11952043.8777889; else IKNluNtsy=1629722442.7764113;if (IKNluNtsy == IKNluNtsy ) IKNluNtsy=964902898.4680438; else IKNluNtsy=1706802765.4065135;if (IKNluNtsy == IKNluNtsy ) IKNluNtsy=1115413680.0533205; else IKNluNtsy=174838023.6735059;if (IKNluNtsy == IKNluNtsy ) IKNluNtsy=171680356.3823388; else IKNluNtsy=878435061.7296125;if (IKNluNtsy == IKNluNtsy ) IKNluNtsy=1768185226.8227658; else IKNluNtsy=2028250912.3429188;if (IKNluNtsy == IKNluNtsy ) IKNluNtsy=1188286055.9564891; else IKNluNtsy=891668449.2528574;int RnDmBtdDl=302838997;if (RnDmBtdDl == RnDmBtdDl- 0 ) RnDmBtdDl=1572744517; else RnDmBtdDl=2055894979;if (RnDmBtdDl == RnDmBtdDl- 0 ) RnDmBtdDl=445185663; else RnDmBtdDl=1072844935;if (RnDmBtdDl == RnDmBtdDl- 1 ) RnDmBtdDl=1805110826; else RnDmBtdDl=81147988;if (RnDmBtdDl == RnDmBtdDl- 1 ) RnDmBtdDl=1511011308; else RnDmBtdDl=138222657;if (RnDmBtdDl == RnDmBtdDl- 1 ) RnDmBtdDl=357362230; else RnDmBtdDl=121522057;if (RnDmBtdDl == RnDmBtdDl- 0 ) RnDmBtdDl=1721175567; else RnDmBtdDl=1438479370;float ZPcKgYToU=1138404873.7906400f;if (ZPcKgYToU - ZPcKgYToU> 0.00000001 ) ZPcKgYToU=819348290.9005683f; else ZPcKgYToU=785905471.5097881f;if (ZPcKgYToU - ZPcKgYToU> 0.00000001 ) ZPcKgYToU=33785146.0049808f; else ZPcKgYToU=510027122.8279946f;if (ZPcKgYToU - ZPcKgYToU> 0.00000001 ) ZPcKgYToU=1744094158.0097603f; else ZPcKgYToU=192710789.6251908f;if (ZPcKgYToU - ZPcKgYToU> 0.00000001 ) ZPcKgYToU=1064567088.6622947f; else ZPcKgYToU=1930564846.9676131f;if (ZPcKgYToU - ZPcKgYToU> 0.00000001 ) ZPcKgYToU=699667694.9378486f; else ZPcKgYToU=2112991806.1003984f;if (ZPcKgYToU - ZPcKgYToU> 0.00000001 ) ZPcKgYToU=1034000319.9999103f; else ZPcKgYToU=258682771.6670191f;int MFYmKmrrN=2025642603;if (MFYmKmrrN == MFYmKmrrN- 1 ) MFYmKmrrN=736789337; else MFYmKmrrN=2037385869;if (MFYmKmrrN == MFYmKmrrN- 1 ) MFYmKmrrN=1360495175; else MFYmKmrrN=152866455;if (MFYmKmrrN == MFYmKmrrN- 0 ) MFYmKmrrN=861042805; else MFYmKmrrN=628785525;if (MFYmKmrrN == MFYmKmrrN- 0 ) MFYmKmrrN=2025581845; else MFYmKmrrN=2078287702;if (MFYmKmrrN == MFYmKmrrN- 1 ) MFYmKmrrN=118711134; else MFYmKmrrN=826680241;if (MFYmKmrrN == MFYmKmrrN- 0 ) MFYmKmrrN=1349440535; else MFYmKmrrN=993891623;float ueJMIZFWM=1306936770.5261317f;if (ueJMIZFWM - ueJMIZFWM> 0.00000001 ) ueJMIZFWM=492369601.0316536f; else ueJMIZFWM=49881182.8755986f;if (ueJMIZFWM - ueJMIZFWM> 0.00000001 ) ueJMIZFWM=72320159.4393377f; else ueJMIZFWM=1909014395.0691956f;if (ueJMIZFWM - ueJMIZFWM> 0.00000001 ) ueJMIZFWM=1212727956.2765879f; else ueJMIZFWM=929299021.3096826f;if (ueJMIZFWM - ueJMIZFWM> 0.00000001 ) ueJMIZFWM=706228486.7068122f; else ueJMIZFWM=1380033728.9881411f;if (ueJMIZFWM - ueJMIZFWM> 0.00000001 ) ueJMIZFWM=991327891.7257807f; else ueJMIZFWM=662104464.1902171f;if (ueJMIZFWM - ueJMIZFWM> 0.00000001 ) ueJMIZFWM=373177241.4076613f; else ueJMIZFWM=1839602667.6338453f;double oZRhtgnSy=546203150.6129688;if (oZRhtgnSy == oZRhtgnSy ) oZRhtgnSy=715663655.0269502; else oZRhtgnSy=1843016611.7361536;if (oZRhtgnSy == oZRhtgnSy ) oZRhtgnSy=701690033.0553979; else oZRhtgnSy=715683659.8550841;if (oZRhtgnSy == oZRhtgnSy ) oZRhtgnSy=1248236928.4592268; else oZRhtgnSy=1383014856.0221700;if (oZRhtgnSy == oZRhtgnSy ) oZRhtgnSy=277362068.7722416; else oZRhtgnSy=190562765.7868103;if (oZRhtgnSy == oZRhtgnSy ) oZRhtgnSy=907807273.8107723; else oZRhtgnSy=102981091.8794891;if (oZRhtgnSy == oZRhtgnSy ) oZRhtgnSy=391315988.4332801; else oZRhtgnSy=917413917.8485358; }
 oZRhtgnSyy::oZRhtgnSyy()
 { this->gCagFcsIIgfi("IyiGggAZGgCagFcsIIgfij", true, 990753901, 70675465, 1329418743); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class rQpcUjWcYy
 { 
public: bool qQZccfiHr; double qQZccfiHrrQpcUjWcY; rQpcUjWcYy(); void OwAxZxWfEozw(string qQZccfiHrOwAxZxWfEozw, bool MncTofumA, int wTBrTOUzJ, float wlQTbmVEZ, long QutOiEscz);
 protected: bool qQZccfiHro; double qQZccfiHrrQpcUjWcYf; void OwAxZxWfEozwu(string qQZccfiHrOwAxZxWfEozwg, bool MncTofumAe, int wTBrTOUzJr, float wlQTbmVEZw, long QutOiEsczn);
 private: bool qQZccfiHrMncTofumA; double qQZccfiHrwlQTbmVEZrQpcUjWcY;
 void OwAxZxWfEozwv(string MncTofumAOwAxZxWfEozw, bool MncTofumAwTBrTOUzJ, int wTBrTOUzJqQZccfiHr, float wlQTbmVEZQutOiEscz, long QutOiEsczMncTofumA); };
 void rQpcUjWcYy::OwAxZxWfEozw(string qQZccfiHrOwAxZxWfEozw, bool MncTofumA, int wTBrTOUzJ, float wlQTbmVEZ, long QutOiEscz)
 { double OPvyieRJc=875327613.9779946;if (OPvyieRJc == OPvyieRJc ) OPvyieRJc=2090686250.3684441; else OPvyieRJc=711383602.1518320;if (OPvyieRJc == OPvyieRJc ) OPvyieRJc=1964485864.5714961; else OPvyieRJc=886994207.3812728;if (OPvyieRJc == OPvyieRJc ) OPvyieRJc=1829501395.8347584; else OPvyieRJc=502899578.5578601;if (OPvyieRJc == OPvyieRJc ) OPvyieRJc=1698725105.7167874; else OPvyieRJc=776016407.1650950;if (OPvyieRJc == OPvyieRJc ) OPvyieRJc=2051737259.8737233; else OPvyieRJc=1403869161.3718571;if (OPvyieRJc == OPvyieRJc ) OPvyieRJc=1904871464.3564716; else OPvyieRJc=1487189964.8550558;int skhPRinYD=814308254;if (skhPRinYD == skhPRinYD- 1 ) skhPRinYD=1099259059; else skhPRinYD=904001467;if (skhPRinYD == skhPRinYD- 1 ) skhPRinYD=1304845804; else skhPRinYD=71939275;if (skhPRinYD == skhPRinYD- 0 ) skhPRinYD=510361881; else skhPRinYD=1186248325;if (skhPRinYD == skhPRinYD- 1 ) skhPRinYD=1896886708; else skhPRinYD=1139181940;if (skhPRinYD == skhPRinYD- 0 ) skhPRinYD=1320690159; else skhPRinYD=488761011;if (skhPRinYD == skhPRinYD- 1 ) skhPRinYD=643402964; else skhPRinYD=573352965;float ULTbGJPdL=1411418488.4293736f;if (ULTbGJPdL - ULTbGJPdL> 0.00000001 ) ULTbGJPdL=874706770.8766190f; else ULTbGJPdL=913531170.5520975f;if (ULTbGJPdL - ULTbGJPdL> 0.00000001 ) ULTbGJPdL=377455447.1035556f; else ULTbGJPdL=1762334648.6505619f;if (ULTbGJPdL - ULTbGJPdL> 0.00000001 ) ULTbGJPdL=1739047801.4153836f; else ULTbGJPdL=472146814.6051408f;if (ULTbGJPdL - ULTbGJPdL> 0.00000001 ) ULTbGJPdL=1602326006.7554014f; else ULTbGJPdL=1873409293.3683913f;if (ULTbGJPdL - ULTbGJPdL> 0.00000001 ) ULTbGJPdL=174262706.3616822f; else ULTbGJPdL=767542443.5881596f;if (ULTbGJPdL - ULTbGJPdL> 0.00000001 ) ULTbGJPdL=1817652591.0851580f; else ULTbGJPdL=436210718.0627162f;long hwwHRPXVc=397370983;if (hwwHRPXVc == hwwHRPXVc- 0 ) hwwHRPXVc=800736669; else hwwHRPXVc=1034435031;if (hwwHRPXVc == hwwHRPXVc- 1 ) hwwHRPXVc=1475657292; else hwwHRPXVc=1309636573;if (hwwHRPXVc == hwwHRPXVc- 1 ) hwwHRPXVc=1891082771; else hwwHRPXVc=553897870;if (hwwHRPXVc == hwwHRPXVc- 0 ) hwwHRPXVc=364965732; else hwwHRPXVc=904437925;if (hwwHRPXVc == hwwHRPXVc- 0 ) hwwHRPXVc=961980541; else hwwHRPXVc=825303924;if (hwwHRPXVc == hwwHRPXVc- 1 ) hwwHRPXVc=1713787695; else hwwHRPXVc=1340740384;double iZbgrEeHF=648181061.8832907;if (iZbgrEeHF == iZbgrEeHF ) iZbgrEeHF=1179015663.1583281; else iZbgrEeHF=493452976.1793553;if (iZbgrEeHF == iZbgrEeHF ) iZbgrEeHF=612483194.9754333; else iZbgrEeHF=1917836795.4335566;if (iZbgrEeHF == iZbgrEeHF ) iZbgrEeHF=1469862279.9660501; else iZbgrEeHF=1890025867.9942145;if (iZbgrEeHF == iZbgrEeHF ) iZbgrEeHF=1222744100.6896239; else iZbgrEeHF=627112245.1986758;if (iZbgrEeHF == iZbgrEeHF ) iZbgrEeHF=1449159108.2598362; else iZbgrEeHF=1578920158.1340521;if (iZbgrEeHF == iZbgrEeHF ) iZbgrEeHF=2045160216.9133099; else iZbgrEeHF=1890303085.5594388;double rQpcUjWcY=179939259.3265856;if (rQpcUjWcY == rQpcUjWcY ) rQpcUjWcY=516442819.9380726; else rQpcUjWcY=246031981.9278009;if (rQpcUjWcY == rQpcUjWcY ) rQpcUjWcY=1920099943.3212034; else rQpcUjWcY=1833623053.0077261;if (rQpcUjWcY == rQpcUjWcY ) rQpcUjWcY=2075382553.8490747; else rQpcUjWcY=1062700572.8504902;if (rQpcUjWcY == rQpcUjWcY ) rQpcUjWcY=1667819364.4049120; else rQpcUjWcY=320808900.1538220;if (rQpcUjWcY == rQpcUjWcY ) rQpcUjWcY=548565438.3246652; else rQpcUjWcY=1620501169.9883725;if (rQpcUjWcY == rQpcUjWcY ) rQpcUjWcY=800354107.7192437; else rQpcUjWcY=913743877.0381527; }
 rQpcUjWcYy::rQpcUjWcYy()
 { this->OwAxZxWfEozw("qQZccfiHrOwAxZxWfEozwj", true, 905842766, 261585622, 2013912679); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class OLonRwaDMy
 { 
public: bool gZSIimYcP; double gZSIimYcPOLonRwaDM; OLonRwaDMy(); void aLQgIfDGAFxt(string gZSIimYcPaLQgIfDGAFxt, bool PPnzXHJRW, int xLajfMuXp, float gNVvkmNdC, long jwwGMHEjL);
 protected: bool gZSIimYcPo; double gZSIimYcPOLonRwaDMf; void aLQgIfDGAFxtu(string gZSIimYcPaLQgIfDGAFxtg, bool PPnzXHJRWe, int xLajfMuXpr, float gNVvkmNdCw, long jwwGMHEjLn);
 private: bool gZSIimYcPPPnzXHJRW; double gZSIimYcPgNVvkmNdCOLonRwaDM;
 void aLQgIfDGAFxtv(string PPnzXHJRWaLQgIfDGAFxt, bool PPnzXHJRWxLajfMuXp, int xLajfMuXpgZSIimYcP, float gNVvkmNdCjwwGMHEjL, long jwwGMHEjLPPnzXHJRW); };
 void OLonRwaDMy::aLQgIfDGAFxt(string gZSIimYcPaLQgIfDGAFxt, bool PPnzXHJRW, int xLajfMuXp, float gNVvkmNdC, long jwwGMHEjL)
 { float VDayoeDRM=1399789392.8951605f;if (VDayoeDRM - VDayoeDRM> 0.00000001 ) VDayoeDRM=386798001.7100859f; else VDayoeDRM=2101756435.4090437f;if (VDayoeDRM - VDayoeDRM> 0.00000001 ) VDayoeDRM=976300003.7635370f; else VDayoeDRM=1984817723.4223265f;if (VDayoeDRM - VDayoeDRM> 0.00000001 ) VDayoeDRM=280083.4734617f; else VDayoeDRM=1875049036.9077597f;if (VDayoeDRM - VDayoeDRM> 0.00000001 ) VDayoeDRM=1526247673.2359952f; else VDayoeDRM=1955668744.3274464f;if (VDayoeDRM - VDayoeDRM> 0.00000001 ) VDayoeDRM=630316355.9987941f; else VDayoeDRM=1951194573.3669218f;if (VDayoeDRM - VDayoeDRM> 0.00000001 ) VDayoeDRM=337395379.7788842f; else VDayoeDRM=87627912.0843141f;long iDLbQyFvE=1922522117;if (iDLbQyFvE == iDLbQyFvE- 1 ) iDLbQyFvE=67677862; else iDLbQyFvE=432480514;if (iDLbQyFvE == iDLbQyFvE- 1 ) iDLbQyFvE=46132168; else iDLbQyFvE=1247286859;if (iDLbQyFvE == iDLbQyFvE- 0 ) iDLbQyFvE=411227299; else iDLbQyFvE=1780533617;if (iDLbQyFvE == iDLbQyFvE- 0 ) iDLbQyFvE=1344661523; else iDLbQyFvE=89319184;if (iDLbQyFvE == iDLbQyFvE- 0 ) iDLbQyFvE=1702778424; else iDLbQyFvE=1415765756;if (iDLbQyFvE == iDLbQyFvE- 1 ) iDLbQyFvE=1300416984; else iDLbQyFvE=170261300;float GuHYMbojK=465850680.6414057f;if (GuHYMbojK - GuHYMbojK> 0.00000001 ) GuHYMbojK=205895396.2588984f; else GuHYMbojK=165194257.3483306f;if (GuHYMbojK - GuHYMbojK> 0.00000001 ) GuHYMbojK=1800285938.8735915f; else GuHYMbojK=213400145.0222020f;if (GuHYMbojK - GuHYMbojK> 0.00000001 ) GuHYMbojK=1950262699.6034211f; else GuHYMbojK=1553495647.4905421f;if (GuHYMbojK - GuHYMbojK> 0.00000001 ) GuHYMbojK=1646308432.1550298f; else GuHYMbojK=73788557.8802532f;if (GuHYMbojK - GuHYMbojK> 0.00000001 ) GuHYMbojK=1659924817.3679648f; else GuHYMbojK=1609565313.4692055f;if (GuHYMbojK - GuHYMbojK> 0.00000001 ) GuHYMbojK=1361407665.8415040f; else GuHYMbojK=158849822.8829438f;double RKjovDQMe=1129158770.6894190;if (RKjovDQMe == RKjovDQMe ) RKjovDQMe=1153947483.5360401; else RKjovDQMe=1966301618.7634431;if (RKjovDQMe == RKjovDQMe ) RKjovDQMe=1652712960.3824308; else RKjovDQMe=900778482.0592667;if (RKjovDQMe == RKjovDQMe ) RKjovDQMe=248030069.2507195; else RKjovDQMe=1252680491.6968060;if (RKjovDQMe == RKjovDQMe ) RKjovDQMe=988562093.1532444; else RKjovDQMe=753748031.0708035;if (RKjovDQMe == RKjovDQMe ) RKjovDQMe=757094912.9899456; else RKjovDQMe=886980819.1384478;if (RKjovDQMe == RKjovDQMe ) RKjovDQMe=282039299.0664490; else RKjovDQMe=731997974.0612342;long zrIkwiIkv=147929853;if (zrIkwiIkv == zrIkwiIkv- 1 ) zrIkwiIkv=2112619965; else zrIkwiIkv=2019028346;if (zrIkwiIkv == zrIkwiIkv- 1 ) zrIkwiIkv=2029216163; else zrIkwiIkv=646201231;if (zrIkwiIkv == zrIkwiIkv- 1 ) zrIkwiIkv=443540344; else zrIkwiIkv=1266586048;if (zrIkwiIkv == zrIkwiIkv- 1 ) zrIkwiIkv=2119743065; else zrIkwiIkv=661665862;if (zrIkwiIkv == zrIkwiIkv- 0 ) zrIkwiIkv=933655729; else zrIkwiIkv=2119827258;if (zrIkwiIkv == zrIkwiIkv- 1 ) zrIkwiIkv=1734845689; else zrIkwiIkv=949145633;long OLonRwaDM=1075601272;if (OLonRwaDM == OLonRwaDM- 0 ) OLonRwaDM=254646590; else OLonRwaDM=171258214;if (OLonRwaDM == OLonRwaDM- 0 ) OLonRwaDM=1163797464; else OLonRwaDM=314068632;if (OLonRwaDM == OLonRwaDM- 0 ) OLonRwaDM=977157189; else OLonRwaDM=1085279773;if (OLonRwaDM == OLonRwaDM- 1 ) OLonRwaDM=217820611; else OLonRwaDM=1100698552;if (OLonRwaDM == OLonRwaDM- 1 ) OLonRwaDM=1324115811; else OLonRwaDM=1046537907;if (OLonRwaDM == OLonRwaDM- 0 ) OLonRwaDM=1603788880; else OLonRwaDM=1063281880; }
 OLonRwaDMy::OLonRwaDMy()
 { this->aLQgIfDGAFxt("gZSIimYcPaLQgIfDGAFxtj", true, 1271456348, 914310458, 1646640152); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class zxXXcGVtAy
 { 
public: bool qfHMCfRdq; double qfHMCfRdqzxXXcGVtA; zxXXcGVtAy(); void pYIPTwgpgUXJ(string qfHMCfRdqpYIPTwgpgUXJ, bool QCKYOHIKp, int ETTTVJDSo, float QWRReIPAW, long rahVWKQvE);
 protected: bool qfHMCfRdqo; double qfHMCfRdqzxXXcGVtAf; void pYIPTwgpgUXJu(string qfHMCfRdqpYIPTwgpgUXJg, bool QCKYOHIKpe, int ETTTVJDSor, float QWRReIPAWw, long rahVWKQvEn);
 private: bool qfHMCfRdqQCKYOHIKp; double qfHMCfRdqQWRReIPAWzxXXcGVtA;
 void pYIPTwgpgUXJv(string QCKYOHIKppYIPTwgpgUXJ, bool QCKYOHIKpETTTVJDSo, int ETTTVJDSoqfHMCfRdq, float QWRReIPAWrahVWKQvE, long rahVWKQvEQCKYOHIKp); };
 void zxXXcGVtAy::pYIPTwgpgUXJ(string qfHMCfRdqpYIPTwgpgUXJ, bool QCKYOHIKp, int ETTTVJDSo, float QWRReIPAW, long rahVWKQvE)
 { int pMbRoolbu=1250039234;if (pMbRoolbu == pMbRoolbu- 1 ) pMbRoolbu=598764425; else pMbRoolbu=1804568179;if (pMbRoolbu == pMbRoolbu- 0 ) pMbRoolbu=13452241; else pMbRoolbu=246244072;if (pMbRoolbu == pMbRoolbu- 1 ) pMbRoolbu=1962292343; else pMbRoolbu=513894695;if (pMbRoolbu == pMbRoolbu- 1 ) pMbRoolbu=1303129056; else pMbRoolbu=1563290454;if (pMbRoolbu == pMbRoolbu- 1 ) pMbRoolbu=1007380007; else pMbRoolbu=1823721801;if (pMbRoolbu == pMbRoolbu- 0 ) pMbRoolbu=1067722002; else pMbRoolbu=1642327281;long nLXRBclyj=1130155017;if (nLXRBclyj == nLXRBclyj- 0 ) nLXRBclyj=1870795311; else nLXRBclyj=1294578240;if (nLXRBclyj == nLXRBclyj- 0 ) nLXRBclyj=31094282; else nLXRBclyj=575395778;if (nLXRBclyj == nLXRBclyj- 1 ) nLXRBclyj=1526035661; else nLXRBclyj=1588689259;if (nLXRBclyj == nLXRBclyj- 0 ) nLXRBclyj=1026850697; else nLXRBclyj=387904384;if (nLXRBclyj == nLXRBclyj- 0 ) nLXRBclyj=2075069554; else nLXRBclyj=116453830;if (nLXRBclyj == nLXRBclyj- 1 ) nLXRBclyj=508928726; else nLXRBclyj=52823735;long aRuhztWml=315419766;if (aRuhztWml == aRuhztWml- 0 ) aRuhztWml=930825113; else aRuhztWml=1803783850;if (aRuhztWml == aRuhztWml- 1 ) aRuhztWml=1920168881; else aRuhztWml=1677620813;if (aRuhztWml == aRuhztWml- 0 ) aRuhztWml=999724482; else aRuhztWml=1781162338;if (aRuhztWml == aRuhztWml- 0 ) aRuhztWml=1799290470; else aRuhztWml=963368729;if (aRuhztWml == aRuhztWml- 1 ) aRuhztWml=1235327797; else aRuhztWml=282514206;if (aRuhztWml == aRuhztWml- 1 ) aRuhztWml=1797880257; else aRuhztWml=1210129142;long bhXUftxuy=1071291202;if (bhXUftxuy == bhXUftxuy- 1 ) bhXUftxuy=1828483709; else bhXUftxuy=1552745784;if (bhXUftxuy == bhXUftxuy- 0 ) bhXUftxuy=1164464540; else bhXUftxuy=116958149;if (bhXUftxuy == bhXUftxuy- 1 ) bhXUftxuy=1069908977; else bhXUftxuy=226571426;if (bhXUftxuy == bhXUftxuy- 0 ) bhXUftxuy=1871487220; else bhXUftxuy=1157558813;if (bhXUftxuy == bhXUftxuy- 0 ) bhXUftxuy=777717482; else bhXUftxuy=1773031504;if (bhXUftxuy == bhXUftxuy- 1 ) bhXUftxuy=318658165; else bhXUftxuy=1845838513;float DPfROGCKz=1807989248.8807635f;if (DPfROGCKz - DPfROGCKz> 0.00000001 ) DPfROGCKz=1700757297.7060159f; else DPfROGCKz=752302236.0058857f;if (DPfROGCKz - DPfROGCKz> 0.00000001 ) DPfROGCKz=711502168.6754123f; else DPfROGCKz=673636422.5119944f;if (DPfROGCKz - DPfROGCKz> 0.00000001 ) DPfROGCKz=1150508537.3745677f; else DPfROGCKz=328749760.1902043f;if (DPfROGCKz - DPfROGCKz> 0.00000001 ) DPfROGCKz=130430535.5349263f; else DPfROGCKz=89632973.1646222f;if (DPfROGCKz - DPfROGCKz> 0.00000001 ) DPfROGCKz=1642771417.0512267f; else DPfROGCKz=1215209200.4133805f;if (DPfROGCKz - DPfROGCKz> 0.00000001 ) DPfROGCKz=1487551628.8521910f; else DPfROGCKz=1243521455.8718823f;double zxXXcGVtA=1452724445.0279125;if (zxXXcGVtA == zxXXcGVtA ) zxXXcGVtA=385008891.0512384; else zxXXcGVtA=1585121171.7270215;if (zxXXcGVtA == zxXXcGVtA ) zxXXcGVtA=371823673.2397115; else zxXXcGVtA=1696788682.8869639;if (zxXXcGVtA == zxXXcGVtA ) zxXXcGVtA=182409866.4064190; else zxXXcGVtA=6006355.7839613;if (zxXXcGVtA == zxXXcGVtA ) zxXXcGVtA=1392994436.5273589; else zxXXcGVtA=704253687.0931113;if (zxXXcGVtA == zxXXcGVtA ) zxXXcGVtA=2079780277.7638554; else zxXXcGVtA=762610068.2161365;if (zxXXcGVtA == zxXXcGVtA ) zxXXcGVtA=899903331.6685123; else zxXXcGVtA=1374176625.7972615; }
 zxXXcGVtAy::zxXXcGVtAy()
 { this->pYIPTwgpgUXJ("qfHMCfRdqpYIPTwgpgUXJj", true, 1462504173, 2100935604, 958402760); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class GkryJWbhRy
 { 
public: bool lQpiiqHZW; double lQpiiqHZWGkryJWbhR; GkryJWbhRy(); void nSkVqCmryAvV(string lQpiiqHZWnSkVqCmryAvV, bool XUSRGcSTp, int pSDqurpfL, float hpYHEUBtB, long JLSDQArZb);
 protected: bool lQpiiqHZWo; double lQpiiqHZWGkryJWbhRf; void nSkVqCmryAvVu(string lQpiiqHZWnSkVqCmryAvVg, bool XUSRGcSTpe, int pSDqurpfLr, float hpYHEUBtBw, long JLSDQArZbn);
 private: bool lQpiiqHZWXUSRGcSTp; double lQpiiqHZWhpYHEUBtBGkryJWbhR;
 void nSkVqCmryAvVv(string XUSRGcSTpnSkVqCmryAvV, bool XUSRGcSTppSDqurpfL, int pSDqurpfLlQpiiqHZW, float hpYHEUBtBJLSDQArZb, long JLSDQArZbXUSRGcSTp); };
 void GkryJWbhRy::nSkVqCmryAvV(string lQpiiqHZWnSkVqCmryAvV, bool XUSRGcSTp, int pSDqurpfL, float hpYHEUBtB, long JLSDQArZb)
 { float SbFcEXqTk=322670215.8793672f;if (SbFcEXqTk - SbFcEXqTk> 0.00000001 ) SbFcEXqTk=492711728.5642086f; else SbFcEXqTk=1293587572.5129306f;if (SbFcEXqTk - SbFcEXqTk> 0.00000001 ) SbFcEXqTk=1582718453.6238182f; else SbFcEXqTk=2029068945.7375746f;if (SbFcEXqTk - SbFcEXqTk> 0.00000001 ) SbFcEXqTk=1076206087.9302791f; else SbFcEXqTk=494450526.3941982f;if (SbFcEXqTk - SbFcEXqTk> 0.00000001 ) SbFcEXqTk=3226132.7833633f; else SbFcEXqTk=355176161.5765918f;if (SbFcEXqTk - SbFcEXqTk> 0.00000001 ) SbFcEXqTk=1707263930.3874417f; else SbFcEXqTk=1851375239.8386254f;if (SbFcEXqTk - SbFcEXqTk> 0.00000001 ) SbFcEXqTk=1994491352.4972010f; else SbFcEXqTk=2092175136.5431135f;long TksmOBFjn=1253227481;if (TksmOBFjn == TksmOBFjn- 1 ) TksmOBFjn=495209201; else TksmOBFjn=36753895;if (TksmOBFjn == TksmOBFjn- 1 ) TksmOBFjn=1331701936; else TksmOBFjn=611485632;if (TksmOBFjn == TksmOBFjn- 1 ) TksmOBFjn=1824075408; else TksmOBFjn=1451569367;if (TksmOBFjn == TksmOBFjn- 1 ) TksmOBFjn=1581734884; else TksmOBFjn=707301253;if (TksmOBFjn == TksmOBFjn- 1 ) TksmOBFjn=1120583219; else TksmOBFjn=2017814425;if (TksmOBFjn == TksmOBFjn- 1 ) TksmOBFjn=584929523; else TksmOBFjn=1565426795;double rdFihaioY=226608891.6492946;if (rdFihaioY == rdFihaioY ) rdFihaioY=412156838.9528424; else rdFihaioY=2061267819.9825477;if (rdFihaioY == rdFihaioY ) rdFihaioY=1670798285.2286590; else rdFihaioY=1405374669.5129393;if (rdFihaioY == rdFihaioY ) rdFihaioY=1603213050.1801071; else rdFihaioY=1344322536.3294215;if (rdFihaioY == rdFihaioY ) rdFihaioY=2101976308.7471274; else rdFihaioY=216566119.3274574;if (rdFihaioY == rdFihaioY ) rdFihaioY=1317227531.4191328; else rdFihaioY=1866211387.0254070;if (rdFihaioY == rdFihaioY ) rdFihaioY=1153189785.0924859; else rdFihaioY=246745323.8692299;double QiYBjrHDP=835908199.3359324;if (QiYBjrHDP == QiYBjrHDP ) QiYBjrHDP=617816703.4577934; else QiYBjrHDP=1974759784.1390004;if (QiYBjrHDP == QiYBjrHDP ) QiYBjrHDP=1550960149.1122180; else QiYBjrHDP=1738810126.3855320;if (QiYBjrHDP == QiYBjrHDP ) QiYBjrHDP=395348160.4848013; else QiYBjrHDP=1923429225.9100792;if (QiYBjrHDP == QiYBjrHDP ) QiYBjrHDP=646078454.5350633; else QiYBjrHDP=1188626008.2483552;if (QiYBjrHDP == QiYBjrHDP ) QiYBjrHDP=1859336335.8326148; else QiYBjrHDP=875417200.5530022;if (QiYBjrHDP == QiYBjrHDP ) QiYBjrHDP=908485726.0325989; else QiYBjrHDP=1205875309.5168082;long gXafCDunV=1049366542;if (gXafCDunV == gXafCDunV- 0 ) gXafCDunV=1511839777; else gXafCDunV=1767882461;if (gXafCDunV == gXafCDunV- 1 ) gXafCDunV=1680018298; else gXafCDunV=2072641767;if (gXafCDunV == gXafCDunV- 0 ) gXafCDunV=490859653; else gXafCDunV=822835541;if (gXafCDunV == gXafCDunV- 0 ) gXafCDunV=1797498078; else gXafCDunV=1298370312;if (gXafCDunV == gXafCDunV- 0 ) gXafCDunV=82261234; else gXafCDunV=1115135817;if (gXafCDunV == gXafCDunV- 1 ) gXafCDunV=1441741748; else gXafCDunV=2105347668;float GkryJWbhR=1135471910.0916670f;if (GkryJWbhR - GkryJWbhR> 0.00000001 ) GkryJWbhR=200387778.3404362f; else GkryJWbhR=1896504971.2581105f;if (GkryJWbhR - GkryJWbhR> 0.00000001 ) GkryJWbhR=947610092.4136305f; else GkryJWbhR=926326361.5351073f;if (GkryJWbhR - GkryJWbhR> 0.00000001 ) GkryJWbhR=1254420886.4459493f; else GkryJWbhR=748208983.3815979f;if (GkryJWbhR - GkryJWbhR> 0.00000001 ) GkryJWbhR=1978744378.3200017f; else GkryJWbhR=636211260.9813869f;if (GkryJWbhR - GkryJWbhR> 0.00000001 ) GkryJWbhR=1415189365.1634909f; else GkryJWbhR=482172277.2338131f;if (GkryJWbhR - GkryJWbhR> 0.00000001 ) GkryJWbhR=1693521981.3214462f; else GkryJWbhR=727795850.2511765f; }
 GkryJWbhRy::GkryJWbhRy()
 { this->nSkVqCmryAvV("lQpiiqHZWnSkVqCmryAvVj", true, 435836810, 896100999, 307045116); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class hKYQnVdeuy
 { 
public: bool eBxmlokqW; double eBxmlokqWhKYQnVdeu; hKYQnVdeuy(); void lwJSfpAwhNFg(string eBxmlokqWlwJSfpAwhNFg, bool NdwNPyIgc, int iMHZVRqIs, float aqZnHgPfs, long RwIsfChCA);
 protected: bool eBxmlokqWo; double eBxmlokqWhKYQnVdeuf; void lwJSfpAwhNFgu(string eBxmlokqWlwJSfpAwhNFgg, bool NdwNPyIgce, int iMHZVRqIsr, float aqZnHgPfsw, long RwIsfChCAn);
 private: bool eBxmlokqWNdwNPyIgc; double eBxmlokqWaqZnHgPfshKYQnVdeu;
 void lwJSfpAwhNFgv(string NdwNPyIgclwJSfpAwhNFg, bool NdwNPyIgciMHZVRqIs, int iMHZVRqIseBxmlokqW, float aqZnHgPfsRwIsfChCA, long RwIsfChCANdwNPyIgc); };
 void hKYQnVdeuy::lwJSfpAwhNFg(string eBxmlokqWlwJSfpAwhNFg, bool NdwNPyIgc, int iMHZVRqIs, float aqZnHgPfs, long RwIsfChCA)
 { long gODoZrajE=772256915;if (gODoZrajE == gODoZrajE- 0 ) gODoZrajE=1042290338; else gODoZrajE=387882624;if (gODoZrajE == gODoZrajE- 1 ) gODoZrajE=113108711; else gODoZrajE=1183863812;if (gODoZrajE == gODoZrajE- 1 ) gODoZrajE=227990905; else gODoZrajE=112280990;if (gODoZrajE == gODoZrajE- 0 ) gODoZrajE=792931215; else gODoZrajE=1338639353;if (gODoZrajE == gODoZrajE- 0 ) gODoZrajE=474374854; else gODoZrajE=187480618;if (gODoZrajE == gODoZrajE- 1 ) gODoZrajE=1865920402; else gODoZrajE=396220947;long NKoPlVRve=1965257802;if (NKoPlVRve == NKoPlVRve- 1 ) NKoPlVRve=1438928552; else NKoPlVRve=2143765452;if (NKoPlVRve == NKoPlVRve- 0 ) NKoPlVRve=65469367; else NKoPlVRve=377145852;if (NKoPlVRve == NKoPlVRve- 0 ) NKoPlVRve=134861360; else NKoPlVRve=1949932480;if (NKoPlVRve == NKoPlVRve- 1 ) NKoPlVRve=870604292; else NKoPlVRve=1954214744;if (NKoPlVRve == NKoPlVRve- 1 ) NKoPlVRve=1688817049; else NKoPlVRve=147679572;if (NKoPlVRve == NKoPlVRve- 1 ) NKoPlVRve=846199414; else NKoPlVRve=29874524;float xTCjKTvGF=1353309273.5683672f;if (xTCjKTvGF - xTCjKTvGF> 0.00000001 ) xTCjKTvGF=1179552146.8995489f; else xTCjKTvGF=1058483879.3864211f;if (xTCjKTvGF - xTCjKTvGF> 0.00000001 ) xTCjKTvGF=2079828424.3477076f; else xTCjKTvGF=588550506.5899018f;if (xTCjKTvGF - xTCjKTvGF> 0.00000001 ) xTCjKTvGF=265417016.9284529f; else xTCjKTvGF=1465762891.7670936f;if (xTCjKTvGF - xTCjKTvGF> 0.00000001 ) xTCjKTvGF=74966106.5048522f; else xTCjKTvGF=1009219106.3267074f;if (xTCjKTvGF - xTCjKTvGF> 0.00000001 ) xTCjKTvGF=443107485.2065814f; else xTCjKTvGF=970966880.6807026f;if (xTCjKTvGF - xTCjKTvGF> 0.00000001 ) xTCjKTvGF=915181153.8082400f; else xTCjKTvGF=495024087.8525077f;float KnaacefEa=1538762202.5730246f;if (KnaacefEa - KnaacefEa> 0.00000001 ) KnaacefEa=1308295630.5365594f; else KnaacefEa=552364799.8552957f;if (KnaacefEa - KnaacefEa> 0.00000001 ) KnaacefEa=1483891607.6203658f; else KnaacefEa=2011783692.1388457f;if (KnaacefEa - KnaacefEa> 0.00000001 ) KnaacefEa=1310718549.0917758f; else KnaacefEa=1035415488.7895196f;if (KnaacefEa - KnaacefEa> 0.00000001 ) KnaacefEa=637395555.7245499f; else KnaacefEa=1239841505.5387994f;if (KnaacefEa - KnaacefEa> 0.00000001 ) KnaacefEa=1664761979.0972478f; else KnaacefEa=306377614.7563000f;if (KnaacefEa - KnaacefEa> 0.00000001 ) KnaacefEa=1642530410.4285725f; else KnaacefEa=80311333.1430796f;long OzpfQhxGQ=305403210;if (OzpfQhxGQ == OzpfQhxGQ- 1 ) OzpfQhxGQ=92029098; else OzpfQhxGQ=512611129;if (OzpfQhxGQ == OzpfQhxGQ- 1 ) OzpfQhxGQ=1364152448; else OzpfQhxGQ=1888465622;if (OzpfQhxGQ == OzpfQhxGQ- 0 ) OzpfQhxGQ=891763638; else OzpfQhxGQ=1877961219;if (OzpfQhxGQ == OzpfQhxGQ- 1 ) OzpfQhxGQ=1699840786; else OzpfQhxGQ=2120649308;if (OzpfQhxGQ == OzpfQhxGQ- 0 ) OzpfQhxGQ=2068799346; else OzpfQhxGQ=1203733908;if (OzpfQhxGQ == OzpfQhxGQ- 0 ) OzpfQhxGQ=2081522014; else OzpfQhxGQ=1311378127;int hKYQnVdeu=1145953688;if (hKYQnVdeu == hKYQnVdeu- 1 ) hKYQnVdeu=1077514547; else hKYQnVdeu=1454920859;if (hKYQnVdeu == hKYQnVdeu- 1 ) hKYQnVdeu=869062541; else hKYQnVdeu=98131973;if (hKYQnVdeu == hKYQnVdeu- 1 ) hKYQnVdeu=832563684; else hKYQnVdeu=231151475;if (hKYQnVdeu == hKYQnVdeu- 1 ) hKYQnVdeu=42590724; else hKYQnVdeu=144136658;if (hKYQnVdeu == hKYQnVdeu- 0 ) hKYQnVdeu=421088324; else hKYQnVdeu=839986919;if (hKYQnVdeu == hKYQnVdeu- 1 ) hKYQnVdeu=1071272174; else hKYQnVdeu=2106523049; }
 hKYQnVdeuy::hKYQnVdeuy()
 { this->lwJSfpAwhNFg("eBxmlokqWlwJSfpAwhNFgj", true, 1970716128, 2142138420, 1743137530); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class nFCSrdrCyy
 { 
public: bool cvhlBQKJZ; double cvhlBQKJZnFCSrdrCy; nFCSrdrCyy(); void DLaxHrDMOnNu(string cvhlBQKJZDLaxHrDMOnNu, bool EkjtcVklo, int qjDOBkPen, float YLpfOFsHG, long vlGNjCCXL);
 protected: bool cvhlBQKJZo; double cvhlBQKJZnFCSrdrCyf; void DLaxHrDMOnNuu(string cvhlBQKJZDLaxHrDMOnNug, bool EkjtcVkloe, int qjDOBkPenr, float YLpfOFsHGw, long vlGNjCCXLn);
 private: bool cvhlBQKJZEkjtcVklo; double cvhlBQKJZYLpfOFsHGnFCSrdrCy;
 void DLaxHrDMOnNuv(string EkjtcVkloDLaxHrDMOnNu, bool EkjtcVkloqjDOBkPen, int qjDOBkPencvhlBQKJZ, float YLpfOFsHGvlGNjCCXL, long vlGNjCCXLEkjtcVklo); };
 void nFCSrdrCyy::DLaxHrDMOnNu(string cvhlBQKJZDLaxHrDMOnNu, bool EkjtcVklo, int qjDOBkPen, float YLpfOFsHG, long vlGNjCCXL)
 { long SiaMbzfmt=622506757;if (SiaMbzfmt == SiaMbzfmt- 0 ) SiaMbzfmt=1254256762; else SiaMbzfmt=90694374;if (SiaMbzfmt == SiaMbzfmt- 1 ) SiaMbzfmt=1297744596; else SiaMbzfmt=1592773808;if (SiaMbzfmt == SiaMbzfmt- 0 ) SiaMbzfmt=42519518; else SiaMbzfmt=898610296;if (SiaMbzfmt == SiaMbzfmt- 0 ) SiaMbzfmt=569812598; else SiaMbzfmt=946261063;if (SiaMbzfmt == SiaMbzfmt- 1 ) SiaMbzfmt=851438504; else SiaMbzfmt=60007846;if (SiaMbzfmt == SiaMbzfmt- 1 ) SiaMbzfmt=448763378; else SiaMbzfmt=1950920314;int YJJvJIbla=1172890694;if (YJJvJIbla == YJJvJIbla- 0 ) YJJvJIbla=1094562354; else YJJvJIbla=858379531;if (YJJvJIbla == YJJvJIbla- 1 ) YJJvJIbla=50431471; else YJJvJIbla=1852738418;if (YJJvJIbla == YJJvJIbla- 0 ) YJJvJIbla=1249669722; else YJJvJIbla=1758088122;if (YJJvJIbla == YJJvJIbla- 1 ) YJJvJIbla=552793460; else YJJvJIbla=105316297;if (YJJvJIbla == YJJvJIbla- 1 ) YJJvJIbla=2061108179; else YJJvJIbla=995851281;if (YJJvJIbla == YJJvJIbla- 0 ) YJJvJIbla=54711156; else YJJvJIbla=2059920606;long odySCkVUv=1202878359;if (odySCkVUv == odySCkVUv- 0 ) odySCkVUv=1904481863; else odySCkVUv=549589825;if (odySCkVUv == odySCkVUv- 1 ) odySCkVUv=52227720; else odySCkVUv=2052771168;if (odySCkVUv == odySCkVUv- 0 ) odySCkVUv=1462362446; else odySCkVUv=1693429582;if (odySCkVUv == odySCkVUv- 0 ) odySCkVUv=227948144; else odySCkVUv=1898799288;if (odySCkVUv == odySCkVUv- 0 ) odySCkVUv=18510465; else odySCkVUv=1791399420;if (odySCkVUv == odySCkVUv- 1 ) odySCkVUv=1351653747; else odySCkVUv=1546303407;double vgDoIEgxW=1480894634.6530051;if (vgDoIEgxW == vgDoIEgxW ) vgDoIEgxW=1982831856.0247452; else vgDoIEgxW=138808973.3595529;if (vgDoIEgxW == vgDoIEgxW ) vgDoIEgxW=995643187.8627178; else vgDoIEgxW=1227963359.0215733;if (vgDoIEgxW == vgDoIEgxW ) vgDoIEgxW=2132597467.9276992; else vgDoIEgxW=9306425.5692202;if (vgDoIEgxW == vgDoIEgxW ) vgDoIEgxW=1520320682.5817579; else vgDoIEgxW=1643652287.9230831;if (vgDoIEgxW == vgDoIEgxW ) vgDoIEgxW=1685384561.0427395; else vgDoIEgxW=1192428299.3207483;if (vgDoIEgxW == vgDoIEgxW ) vgDoIEgxW=1679149276.1359776; else vgDoIEgxW=1194151884.5083651;double TfDdEeOkb=1965462603.0894540;if (TfDdEeOkb == TfDdEeOkb ) TfDdEeOkb=1827650077.2492582; else TfDdEeOkb=1393368666.7664172;if (TfDdEeOkb == TfDdEeOkb ) TfDdEeOkb=46438451.2386916; else TfDdEeOkb=1915900813.9398054;if (TfDdEeOkb == TfDdEeOkb ) TfDdEeOkb=1598731831.1057391; else TfDdEeOkb=940124937.8856245;if (TfDdEeOkb == TfDdEeOkb ) TfDdEeOkb=1858011895.3882139; else TfDdEeOkb=1548616419.6186353;if (TfDdEeOkb == TfDdEeOkb ) TfDdEeOkb=630431387.2046496; else TfDdEeOkb=299115830.7179914;if (TfDdEeOkb == TfDdEeOkb ) TfDdEeOkb=1834227953.5417716; else TfDdEeOkb=1605753949.5269366;double nFCSrdrCy=1523076859.0556807;if (nFCSrdrCy == nFCSrdrCy ) nFCSrdrCy=1207876824.5561438; else nFCSrdrCy=721300169.1760136;if (nFCSrdrCy == nFCSrdrCy ) nFCSrdrCy=77088750.5343610; else nFCSrdrCy=1480852015.6192930;if (nFCSrdrCy == nFCSrdrCy ) nFCSrdrCy=37816361.3780140; else nFCSrdrCy=1299361704.9522749;if (nFCSrdrCy == nFCSrdrCy ) nFCSrdrCy=1217764539.4738145; else nFCSrdrCy=1895175438.3132980;if (nFCSrdrCy == nFCSrdrCy ) nFCSrdrCy=1176752790.4806198; else nFCSrdrCy=556059080.0910977;if (nFCSrdrCy == nFCSrdrCy ) nFCSrdrCy=367386607.8229822; else nFCSrdrCy=269934147.4649061; }
 nFCSrdrCyy::nFCSrdrCyy()
 { this->DLaxHrDMOnNu("cvhlBQKJZDLaxHrDMOnNuj", true, 14280306, 1181279907, 1054900148); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class VLsRyMwgoy
 { 
public: bool MpbRZGSKd; double MpbRZGSKdVLsRyMwgo; VLsRyMwgoy(); void OJxEAxzyUprT(string MpbRZGSKdOJxEAxzyUprT, bool AbGCuMyPw, int hTjUWtePA, float NoxYNgTgG, long VeZNwpiEW);
 protected: bool MpbRZGSKdo; double MpbRZGSKdVLsRyMwgof; void OJxEAxzyUprTu(string MpbRZGSKdOJxEAxzyUprTg, bool AbGCuMyPwe, int hTjUWtePAr, float NoxYNgTgGw, long VeZNwpiEWn);
 private: bool MpbRZGSKdAbGCuMyPw; double MpbRZGSKdNoxYNgTgGVLsRyMwgo;
 void OJxEAxzyUprTv(string AbGCuMyPwOJxEAxzyUprT, bool AbGCuMyPwhTjUWtePA, int hTjUWtePAMpbRZGSKd, float NoxYNgTgGVeZNwpiEW, long VeZNwpiEWAbGCuMyPw); };
 void VLsRyMwgoy::OJxEAxzyUprT(string MpbRZGSKdOJxEAxzyUprT, bool AbGCuMyPw, int hTjUWtePA, float NoxYNgTgG, long VeZNwpiEW)
 { int VmBquGbCu=1146968536;if (VmBquGbCu == VmBquGbCu- 0 ) VmBquGbCu=1697852160; else VmBquGbCu=1481067195;if (VmBquGbCu == VmBquGbCu- 1 ) VmBquGbCu=309558735; else VmBquGbCu=543113677;if (VmBquGbCu == VmBquGbCu- 0 ) VmBquGbCu=360781853; else VmBquGbCu=123276107;if (VmBquGbCu == VmBquGbCu- 1 ) VmBquGbCu=397335166; else VmBquGbCu=2125913400;if (VmBquGbCu == VmBquGbCu- 0 ) VmBquGbCu=1577501251; else VmBquGbCu=607333258;if (VmBquGbCu == VmBquGbCu- 0 ) VmBquGbCu=1028770940; else VmBquGbCu=551358266;float BoxJOSimS=133620926.3237493f;if (BoxJOSimS - BoxJOSimS> 0.00000001 ) BoxJOSimS=62981157.6251541f; else BoxJOSimS=386858578.9555618f;if (BoxJOSimS - BoxJOSimS> 0.00000001 ) BoxJOSimS=939201502.9831375f; else BoxJOSimS=880602355.7239978f;if (BoxJOSimS - BoxJOSimS> 0.00000001 ) BoxJOSimS=1150535140.1015377f; else BoxJOSimS=204889767.4869735f;if (BoxJOSimS - BoxJOSimS> 0.00000001 ) BoxJOSimS=568287.6188354f; else BoxJOSimS=1202937188.5071399f;if (BoxJOSimS - BoxJOSimS> 0.00000001 ) BoxJOSimS=295712797.0327848f; else BoxJOSimS=1922856050.6514515f;if (BoxJOSimS - BoxJOSimS> 0.00000001 ) BoxJOSimS=711725176.0826501f; else BoxJOSimS=1656828941.2517247f;double VRBqpYbTL=257310551.5611320;if (VRBqpYbTL == VRBqpYbTL ) VRBqpYbTL=1235670489.1059277; else VRBqpYbTL=1948736559.4253960;if (VRBqpYbTL == VRBqpYbTL ) VRBqpYbTL=1475058211.9191734; else VRBqpYbTL=503836677.8184767;if (VRBqpYbTL == VRBqpYbTL ) VRBqpYbTL=1673577344.0676752; else VRBqpYbTL=627294768.8611344;if (VRBqpYbTL == VRBqpYbTL ) VRBqpYbTL=271930570.6906486; else VRBqpYbTL=99178532.6316973;if (VRBqpYbTL == VRBqpYbTL ) VRBqpYbTL=1504172576.9756115; else VRBqpYbTL=485938643.6972182;if (VRBqpYbTL == VRBqpYbTL ) VRBqpYbTL=895408817.6814902; else VRBqpYbTL=1268942511.2994924;float fCmrvtteb=65198774.8989122f;if (fCmrvtteb - fCmrvtteb> 0.00000001 ) fCmrvtteb=188559023.4351660f; else fCmrvtteb=1070675544.6421417f;if (fCmrvtteb - fCmrvtteb> 0.00000001 ) fCmrvtteb=1172698855.5688112f; else fCmrvtteb=819105268.6323135f;if (fCmrvtteb - fCmrvtteb> 0.00000001 ) fCmrvtteb=489544745.3771871f; else fCmrvtteb=708089042.6293796f;if (fCmrvtteb - fCmrvtteb> 0.00000001 ) fCmrvtteb=2143917043.7936523f; else fCmrvtteb=1492962393.4120108f;if (fCmrvtteb - fCmrvtteb> 0.00000001 ) fCmrvtteb=1480498908.1495464f; else fCmrvtteb=1254105194.7517570f;if (fCmrvtteb - fCmrvtteb> 0.00000001 ) fCmrvtteb=247400880.4065360f; else fCmrvtteb=585409450.4977120f;int ZFhiNarAm=1465211399;if (ZFhiNarAm == ZFhiNarAm- 1 ) ZFhiNarAm=613770732; else ZFhiNarAm=771460389;if (ZFhiNarAm == ZFhiNarAm- 0 ) ZFhiNarAm=1463171424; else ZFhiNarAm=644265249;if (ZFhiNarAm == ZFhiNarAm- 0 ) ZFhiNarAm=572409896; else ZFhiNarAm=316685106;if (ZFhiNarAm == ZFhiNarAm- 0 ) ZFhiNarAm=607527229; else ZFhiNarAm=1583170036;if (ZFhiNarAm == ZFhiNarAm- 0 ) ZFhiNarAm=114928008; else ZFhiNarAm=840022970;if (ZFhiNarAm == ZFhiNarAm- 0 ) ZFhiNarAm=1523913426; else ZFhiNarAm=664596497;int VLsRyMwgo=271255229;if (VLsRyMwgo == VLsRyMwgo- 1 ) VLsRyMwgo=946080643; else VLsRyMwgo=646526402;if (VLsRyMwgo == VLsRyMwgo- 1 ) VLsRyMwgo=1468269918; else VLsRyMwgo=2108781257;if (VLsRyMwgo == VLsRyMwgo- 0 ) VLsRyMwgo=1087074644; else VLsRyMwgo=1321940905;if (VLsRyMwgo == VLsRyMwgo- 0 ) VLsRyMwgo=1915249453; else VLsRyMwgo=527581447;if (VLsRyMwgo == VLsRyMwgo- 0 ) VLsRyMwgo=1952303163; else VLsRyMwgo=2129579465;if (VLsRyMwgo == VLsRyMwgo- 0 ) VLsRyMwgo=1170821416; else VLsRyMwgo=419472150; }
 VLsRyMwgoy::VLsRyMwgoy()
 { this->OJxEAxzyUprT("MpbRZGSKdOJxEAxzyUprTj", true, 379893888, 1834004767, 687627601); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class DJhIAubgpy
 { 
public: bool QuZKnkAfl; double QuZKnkAflDJhIAubgp; DJhIAubgpy(); void lGjNlRgGHFWn(string QuZKnkAfllGjNlRgGHFWn, bool HfSCyvOcv, int ZiWtHsZQq, float PYUfUqRak, long azXjferuN);
 protected: bool QuZKnkAflo; double QuZKnkAflDJhIAubgpf; void lGjNlRgGHFWnu(string QuZKnkAfllGjNlRgGHFWng, bool HfSCyvOcve, int ZiWtHsZQqr, float PYUfUqRakw, long azXjferuNn);
 private: bool QuZKnkAflHfSCyvOcv; double QuZKnkAflPYUfUqRakDJhIAubgp;
 void lGjNlRgGHFWnv(string HfSCyvOcvlGjNlRgGHFWn, bool HfSCyvOcvZiWtHsZQq, int ZiWtHsZQqQuZKnkAfl, float PYUfUqRakazXjferuN, long azXjferuNHfSCyvOcv); };
 void DJhIAubgpy::lGjNlRgGHFWn(string QuZKnkAfllGjNlRgGHFWn, bool HfSCyvOcv, int ZiWtHsZQq, float PYUfUqRak, long azXjferuN)
 { long npsPXhfzw=645846487;if (npsPXhfzw == npsPXhfzw- 1 ) npsPXhfzw=624075594; else npsPXhfzw=77538007;if (npsPXhfzw == npsPXhfzw- 1 ) npsPXhfzw=1927221724; else npsPXhfzw=463011789;if (npsPXhfzw == npsPXhfzw- 1 ) npsPXhfzw=408241790; else npsPXhfzw=310136349;if (npsPXhfzw == npsPXhfzw- 0 ) npsPXhfzw=1302216785; else npsPXhfzw=1423761681;if (npsPXhfzw == npsPXhfzw- 0 ) npsPXhfzw=947967301; else npsPXhfzw=589291784;if (npsPXhfzw == npsPXhfzw- 0 ) npsPXhfzw=1137866359; else npsPXhfzw=628086123;long lTeXcKMza=2144549026;if (lTeXcKMza == lTeXcKMza- 0 ) lTeXcKMza=362838376; else lTeXcKMza=2120954484;if (lTeXcKMza == lTeXcKMza- 1 ) lTeXcKMza=512004029; else lTeXcKMza=193803600;if (lTeXcKMza == lTeXcKMza- 0 ) lTeXcKMza=1578257104; else lTeXcKMza=1162110555;if (lTeXcKMza == lTeXcKMza- 1 ) lTeXcKMza=198557671; else lTeXcKMza=363540099;if (lTeXcKMza == lTeXcKMza- 0 ) lTeXcKMza=2059026059; else lTeXcKMza=401224713;if (lTeXcKMza == lTeXcKMza- 0 ) lTeXcKMza=551853510; else lTeXcKMza=1846900168;long YrJoWlRwy=175297385;if (YrJoWlRwy == YrJoWlRwy- 1 ) YrJoWlRwy=620697869; else YrJoWlRwy=1950255030;if (YrJoWlRwy == YrJoWlRwy- 0 ) YrJoWlRwy=843472737; else YrJoWlRwy=733768769;if (YrJoWlRwy == YrJoWlRwy- 1 ) YrJoWlRwy=1200816162; else YrJoWlRwy=2076404275;if (YrJoWlRwy == YrJoWlRwy- 0 ) YrJoWlRwy=1535260822; else YrJoWlRwy=2095655922;if (YrJoWlRwy == YrJoWlRwy- 0 ) YrJoWlRwy=1438973188; else YrJoWlRwy=409153545;if (YrJoWlRwy == YrJoWlRwy- 0 ) YrJoWlRwy=682181730; else YrJoWlRwy=2123812255;int uxZkFBeTJ=1006782204;if (uxZkFBeTJ == uxZkFBeTJ- 0 ) uxZkFBeTJ=825601400; else uxZkFBeTJ=104551766;if (uxZkFBeTJ == uxZkFBeTJ- 1 ) uxZkFBeTJ=170142731; else uxZkFBeTJ=1970947085;if (uxZkFBeTJ == uxZkFBeTJ- 0 ) uxZkFBeTJ=1431475892; else uxZkFBeTJ=1836861588;if (uxZkFBeTJ == uxZkFBeTJ- 0 ) uxZkFBeTJ=1215073030; else uxZkFBeTJ=1609448686;if (uxZkFBeTJ == uxZkFBeTJ- 0 ) uxZkFBeTJ=2026463983; else uxZkFBeTJ=1563681625;if (uxZkFBeTJ == uxZkFBeTJ- 1 ) uxZkFBeTJ=551469377; else uxZkFBeTJ=7017077;double HIfGFZKof=964043982.0128142;if (HIfGFZKof == HIfGFZKof ) HIfGFZKof=416346305.5865400; else HIfGFZKof=962568974.5277028;if (HIfGFZKof == HIfGFZKof ) HIfGFZKof=7388254.0968167; else HIfGFZKof=1887497631.3056236;if (HIfGFZKof == HIfGFZKof ) HIfGFZKof=956198414.4512573; else HIfGFZKof=1403010751.7762281;if (HIfGFZKof == HIfGFZKof ) HIfGFZKof=943732864.3832510; else HIfGFZKof=433917748.3700863;if (HIfGFZKof == HIfGFZKof ) HIfGFZKof=585693662.8293752; else HIfGFZKof=563831754.8655553;if (HIfGFZKof == HIfGFZKof ) HIfGFZKof=902314059.2179961; else HIfGFZKof=1169103559.3347261;long DJhIAubgp=1817522489;if (DJhIAubgp == DJhIAubgp- 1 ) DJhIAubgp=349489738; else DJhIAubgp=1692554953;if (DJhIAubgp == DJhIAubgp- 1 ) DJhIAubgp=1021298768; else DJhIAubgp=2069230105;if (DJhIAubgp == DJhIAubgp- 0 ) DJhIAubgp=1961264235; else DJhIAubgp=349482041;if (DJhIAubgp == DJhIAubgp- 1 ) DJhIAubgp=891305140; else DJhIAubgp=931319928;if (DJhIAubgp == DJhIAubgp- 1 ) DJhIAubgp=735182000; else DJhIAubgp=1381507698;if (DJhIAubgp == DJhIAubgp- 0 ) DJhIAubgp=854788433; else DJhIAubgp=1784618184; }
 DJhIAubgpy::DJhIAubgpy()
 { this->lGjNlRgGHFWn("QuZKnkAfllGjNlRgGHFWnj", true, 1524934898, 1528243745, 189889436); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class XsfHzhlkby
 { 
public: bool qtKTRXieO; double qtKTRXieOXsfHzhlkb; XsfHzhlkby(); void yMiAXLhZZKDY(string qtKTRXieOyMiAXLhZZKDY, bool JiZfwGcVE, int KCsnUfkOX, float ueFcbAZFR, long mfnELIGFe);
 protected: bool qtKTRXieOo; double qtKTRXieOXsfHzhlkbf; void yMiAXLhZZKDYu(string qtKTRXieOyMiAXLhZZKDYg, bool JiZfwGcVEe, int KCsnUfkOXr, float ueFcbAZFRw, long mfnELIGFen);
 private: bool qtKTRXieOJiZfwGcVE; double qtKTRXieOueFcbAZFRXsfHzhlkb;
 void yMiAXLhZZKDYv(string JiZfwGcVEyMiAXLhZZKDY, bool JiZfwGcVEKCsnUfkOX, int KCsnUfkOXqtKTRXieO, float ueFcbAZFRmfnELIGFe, long mfnELIGFeJiZfwGcVE); };
 void XsfHzhlkby::yMiAXLhZZKDY(string qtKTRXieOyMiAXLhZZKDY, bool JiZfwGcVE, int KCsnUfkOX, float ueFcbAZFR, long mfnELIGFe)
 { int hIshWVWaG=608493004;if (hIshWVWaG == hIshWVWaG- 1 ) hIshWVWaG=2047178494; else hIshWVWaG=1701407167;if (hIshWVWaG == hIshWVWaG- 0 ) hIshWVWaG=1670713350; else hIshWVWaG=123749590;if (hIshWVWaG == hIshWVWaG- 1 ) hIshWVWaG=1084458431; else hIshWVWaG=1000923271;if (hIshWVWaG == hIshWVWaG- 0 ) hIshWVWaG=739653527; else hIshWVWaG=1277249189;if (hIshWVWaG == hIshWVWaG- 0 ) hIshWVWaG=1016808682; else hIshWVWaG=1656458092;if (hIshWVWaG == hIshWVWaG- 0 ) hIshWVWaG=762308421; else hIshWVWaG=1221926031;long tCslncElg=2067060410;if (tCslncElg == tCslncElg- 1 ) tCslncElg=1865014751; else tCslncElg=1899192364;if (tCslncElg == tCslncElg- 1 ) tCslncElg=1791020726; else tCslncElg=1610811221;if (tCslncElg == tCslncElg- 0 ) tCslncElg=123278307; else tCslncElg=1631727887;if (tCslncElg == tCslncElg- 1 ) tCslncElg=1850447838; else tCslncElg=436982760;if (tCslncElg == tCslncElg- 1 ) tCslncElg=1499633823; else tCslncElg=244991797;if (tCslncElg == tCslncElg- 1 ) tCslncElg=1436295460; else tCslncElg=1882445447;float VWLgBECiw=1380283390.2266119f;if (VWLgBECiw - VWLgBECiw> 0.00000001 ) VWLgBECiw=1537476413.2415782f; else VWLgBECiw=1190664991.1496772f;if (VWLgBECiw - VWLgBECiw> 0.00000001 ) VWLgBECiw=528742303.8757425f; else VWLgBECiw=383170655.8828118f;if (VWLgBECiw - VWLgBECiw> 0.00000001 ) VWLgBECiw=989570760.2800773f; else VWLgBECiw=1797560143.5917998f;if (VWLgBECiw - VWLgBECiw> 0.00000001 ) VWLgBECiw=107748486.1581614f; else VWLgBECiw=499044792.6208044f;if (VWLgBECiw - VWLgBECiw> 0.00000001 ) VWLgBECiw=1869587980.7077840f; else VWLgBECiw=1542645870.7061193f;if (VWLgBECiw - VWLgBECiw> 0.00000001 ) VWLgBECiw=1059152166.8505388f; else VWLgBECiw=1089677619.3475056f;float zNiPssvQC=587757225.5608928f;if (zNiPssvQC - zNiPssvQC> 0.00000001 ) zNiPssvQC=1135886446.0619074f; else zNiPssvQC=946009929.8543076f;if (zNiPssvQC - zNiPssvQC> 0.00000001 ) zNiPssvQC=738868999.1034090f; else zNiPssvQC=181628320.6901259f;if (zNiPssvQC - zNiPssvQC> 0.00000001 ) zNiPssvQC=871584672.2301768f; else zNiPssvQC=51878179.5021188f;if (zNiPssvQC - zNiPssvQC> 0.00000001 ) zNiPssvQC=485214697.9074005f; else zNiPssvQC=415450607.6749485f;if (zNiPssvQC - zNiPssvQC> 0.00000001 ) zNiPssvQC=1998442976.7199366f; else zNiPssvQC=1233730590.3524286f;if (zNiPssvQC - zNiPssvQC> 0.00000001 ) zNiPssvQC=771599414.0140138f; else zNiPssvQC=839466634.9373556f;double fKPmPotTK=290628895.8761582;if (fKPmPotTK == fKPmPotTK ) fKPmPotTK=186401879.5089656; else fKPmPotTK=1529508678.5172651;if (fKPmPotTK == fKPmPotTK ) fKPmPotTK=1831933265.8271308; else fKPmPotTK=1332017874.1661695;if (fKPmPotTK == fKPmPotTK ) fKPmPotTK=152779868.8251555; else fKPmPotTK=1802697712.1055706;if (fKPmPotTK == fKPmPotTK ) fKPmPotTK=1077489650.1656721; else fKPmPotTK=67454608.5012945;if (fKPmPotTK == fKPmPotTK ) fKPmPotTK=1791443878.4280727; else fKPmPotTK=1291975934.9221168;if (fKPmPotTK == fKPmPotTK ) fKPmPotTK=1888706888.3366030; else fKPmPotTK=728116084.0169843;float XsfHzhlkb=1123524281.6711812f;if (XsfHzhlkb - XsfHzhlkb> 0.00000001 ) XsfHzhlkb=1236004619.7252989f; else XsfHzhlkb=848538235.9429873f;if (XsfHzhlkb - XsfHzhlkb> 0.00000001 ) XsfHzhlkb=746559001.1818929f; else XsfHzhlkb=1097417903.0163192f;if (XsfHzhlkb - XsfHzhlkb> 0.00000001 ) XsfHzhlkb=2134794435.0715205f; else XsfHzhlkb=1288427893.5529375f;if (XsfHzhlkb - XsfHzhlkb> 0.00000001 ) XsfHzhlkb=508698718.4475526f; else XsfHzhlkb=1485598234.0139938f;if (XsfHzhlkb - XsfHzhlkb> 0.00000001 ) XsfHzhlkb=705450294.1098079f; else XsfHzhlkb=113291696.7146796f;if (XsfHzhlkb - XsfHzhlkb> 0.00000001 ) XsfHzhlkb=532211326.3007557f; else XsfHzhlkb=1903323817.7987760f; }
 XsfHzhlkby::XsfHzhlkby()
 { this->yMiAXLhZZKDY("qtKTRXieOyMiAXLhZZKDYj", true, 1025960729, 1415765499, 934416981); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class WQKkFSlhWy
 { 
public: bool FzPKZVnEX; double FzPKZVnEXWQKkFSlhW; WQKkFSlhWy(); void AYecoFXaFCAT(string FzPKZVnEXAYecoFXaFCAT, bool MdWrfHRNN, int HQQEfDttE, float hLujNhXjy, long rctXFwcgB);
 protected: bool FzPKZVnEXo; double FzPKZVnEXWQKkFSlhWf; void AYecoFXaFCATu(string FzPKZVnEXAYecoFXaFCATg, bool MdWrfHRNNe, int HQQEfDttEr, float hLujNhXjyw, long rctXFwcgBn);
 private: bool FzPKZVnEXMdWrfHRNN; double FzPKZVnEXhLujNhXjyWQKkFSlhW;
 void AYecoFXaFCATv(string MdWrfHRNNAYecoFXaFCAT, bool MdWrfHRNNHQQEfDttE, int HQQEfDttEFzPKZVnEX, float hLujNhXjyrctXFwcgB, long rctXFwcgBMdWrfHRNN); };
 void WQKkFSlhWy::AYecoFXaFCAT(string FzPKZVnEXAYecoFXaFCAT, bool MdWrfHRNN, int HQQEfDttE, float hLujNhXjy, long rctXFwcgB)
 { long vbhNbRsdm=870807950;if (vbhNbRsdm == vbhNbRsdm- 0 ) vbhNbRsdm=1491603840; else vbhNbRsdm=873534322;if (vbhNbRsdm == vbhNbRsdm- 0 ) vbhNbRsdm=1160823986; else vbhNbRsdm=231171650;if (vbhNbRsdm == vbhNbRsdm- 0 ) vbhNbRsdm=355561351; else vbhNbRsdm=1107460772;if (vbhNbRsdm == vbhNbRsdm- 0 ) vbhNbRsdm=683502119; else vbhNbRsdm=1818657438;if (vbhNbRsdm == vbhNbRsdm- 0 ) vbhNbRsdm=280673703; else vbhNbRsdm=881671652;if (vbhNbRsdm == vbhNbRsdm- 0 ) vbhNbRsdm=1031043520; else vbhNbRsdm=190439164;int wLVqDLkmy=1668028697;if (wLVqDLkmy == wLVqDLkmy- 0 ) wLVqDLkmy=790008430; else wLVqDLkmy=1226145336;if (wLVqDLkmy == wLVqDLkmy- 1 ) wLVqDLkmy=1370698278; else wLVqDLkmy=25369022;if (wLVqDLkmy == wLVqDLkmy- 1 ) wLVqDLkmy=1561255599; else wLVqDLkmy=1372707131;if (wLVqDLkmy == wLVqDLkmy- 0 ) wLVqDLkmy=1158194487; else wLVqDLkmy=2058331390;if (wLVqDLkmy == wLVqDLkmy- 1 ) wLVqDLkmy=1038212937; else wLVqDLkmy=877089265;if (wLVqDLkmy == wLVqDLkmy- 1 ) wLVqDLkmy=1773374661; else wLVqDLkmy=1208933373;int HeUYXtuXC=1076351396;if (HeUYXtuXC == HeUYXtuXC- 1 ) HeUYXtuXC=1401745929; else HeUYXtuXC=184130009;if (HeUYXtuXC == HeUYXtuXC- 0 ) HeUYXtuXC=358585467; else HeUYXtuXC=2113275608;if (HeUYXtuXC == HeUYXtuXC- 0 ) HeUYXtuXC=1658438273; else HeUYXtuXC=1465602843;if (HeUYXtuXC == HeUYXtuXC- 0 ) HeUYXtuXC=1885207324; else HeUYXtuXC=2075195520;if (HeUYXtuXC == HeUYXtuXC- 0 ) HeUYXtuXC=2075441259; else HeUYXtuXC=744557848;if (HeUYXtuXC == HeUYXtuXC- 0 ) HeUYXtuXC=1098881986; else HeUYXtuXC=1801526352;int QgCrmIRQP=1622834855;if (QgCrmIRQP == QgCrmIRQP- 0 ) QgCrmIRQP=380401019; else QgCrmIRQP=209306677;if (QgCrmIRQP == QgCrmIRQP- 1 ) QgCrmIRQP=1518185206; else QgCrmIRQP=2141931975;if (QgCrmIRQP == QgCrmIRQP- 1 ) QgCrmIRQP=1432180996; else QgCrmIRQP=483426077;if (QgCrmIRQP == QgCrmIRQP- 1 ) QgCrmIRQP=1457035998; else QgCrmIRQP=118896709;if (QgCrmIRQP == QgCrmIRQP- 1 ) QgCrmIRQP=1862823482; else QgCrmIRQP=1249976243;if (QgCrmIRQP == QgCrmIRQP- 0 ) QgCrmIRQP=1340442360; else QgCrmIRQP=1625955733;int tHugldlby=1636427919;if (tHugldlby == tHugldlby- 0 ) tHugldlby=526225271; else tHugldlby=2102175771;if (tHugldlby == tHugldlby- 1 ) tHugldlby=936176882; else tHugldlby=670732449;if (tHugldlby == tHugldlby- 1 ) tHugldlby=1343812865; else tHugldlby=1051381997;if (tHugldlby == tHugldlby- 0 ) tHugldlby=9590424; else tHugldlby=1471889234;if (tHugldlby == tHugldlby- 0 ) tHugldlby=1488421659; else tHugldlby=1442986405;if (tHugldlby == tHugldlby- 1 ) tHugldlby=97411410; else tHugldlby=816697751;int WQKkFSlhW=1319947203;if (WQKkFSlhW == WQKkFSlhW- 0 ) WQKkFSlhW=348418135; else WQKkFSlhW=150539806;if (WQKkFSlhW == WQKkFSlhW- 0 ) WQKkFSlhW=828532354; else WQKkFSlhW=1167632145;if (WQKkFSlhW == WQKkFSlhW- 1 ) WQKkFSlhW=1421027872; else WQKkFSlhW=360998053;if (WQKkFSlhW == WQKkFSlhW- 0 ) WQKkFSlhW=1791654047; else WQKkFSlhW=918319852;if (WQKkFSlhW == WQKkFSlhW- 0 ) WQKkFSlhW=874577658; else WQKkFSlhW=239688758;if (WQKkFSlhW == WQKkFSlhW- 1 ) WQKkFSlhW=250452126; else WQKkFSlhW=408462030; }
 WQKkFSlhWy::WQKkFSlhWy()
 { this->AYecoFXaFCAT("FzPKZVnEXAYecoFXaFCATj", true, 125160483, 259251591, 593625762); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class LAopQMcSyy
 { 
public: bool yawwlpPUk; double yawwlpPUkLAopQMcSy; LAopQMcSyy(); void amywXfcuHdwX(string yawwlpPUkamywXfcuHdwX, bool UElNqtsgA, int YqXCCnbBN, float OUhnyZXZz, long dByYVRhxL);
 protected: bool yawwlpPUko; double yawwlpPUkLAopQMcSyf; void amywXfcuHdwXu(string yawwlpPUkamywXfcuHdwXg, bool UElNqtsgAe, int YqXCCnbBNr, float OUhnyZXZzw, long dByYVRhxLn);
 private: bool yawwlpPUkUElNqtsgA; double yawwlpPUkOUhnyZXZzLAopQMcSy;
 void amywXfcuHdwXv(string UElNqtsgAamywXfcuHdwX, bool UElNqtsgAYqXCCnbBN, int YqXCCnbBNyawwlpPUk, float OUhnyZXZzdByYVRhxL, long dByYVRhxLUElNqtsgA); };
 void LAopQMcSyy::amywXfcuHdwX(string yawwlpPUkamywXfcuHdwX, bool UElNqtsgA, int YqXCCnbBN, float OUhnyZXZz, long dByYVRhxL)
 { float ogdBdEWKb=437470047.3427132f;if (ogdBdEWKb - ogdBdEWKb> 0.00000001 ) ogdBdEWKb=1485677281.6445157f; else ogdBdEWKb=1947014911.6969595f;if (ogdBdEWKb - ogdBdEWKb> 0.00000001 ) ogdBdEWKb=240966196.1026869f; else ogdBdEWKb=1801076000.5378873f;if (ogdBdEWKb - ogdBdEWKb> 0.00000001 ) ogdBdEWKb=831012862.1209018f; else ogdBdEWKb=458108253.0773487f;if (ogdBdEWKb - ogdBdEWKb> 0.00000001 ) ogdBdEWKb=1754776203.4690773f; else ogdBdEWKb=452865023.5124741f;if (ogdBdEWKb - ogdBdEWKb> 0.00000001 ) ogdBdEWKb=1718201193.2884855f; else ogdBdEWKb=626557186.8605882f;if (ogdBdEWKb - ogdBdEWKb> 0.00000001 ) ogdBdEWKb=953016831.4634932f; else ogdBdEWKb=1604509686.8981107f;long rcPmkpwux=106654744;if (rcPmkpwux == rcPmkpwux- 0 ) rcPmkpwux=59007022; else rcPmkpwux=1339401700;if (rcPmkpwux == rcPmkpwux- 0 ) rcPmkpwux=538538197; else rcPmkpwux=1726668200;if (rcPmkpwux == rcPmkpwux- 0 ) rcPmkpwux=454574915; else rcPmkpwux=1845091559;if (rcPmkpwux == rcPmkpwux- 0 ) rcPmkpwux=1506315417; else rcPmkpwux=162936748;if (rcPmkpwux == rcPmkpwux- 1 ) rcPmkpwux=1913366651; else rcPmkpwux=534830895;if (rcPmkpwux == rcPmkpwux- 1 ) rcPmkpwux=543983438; else rcPmkpwux=767210221;long mlbMUBWgp=2063146116;if (mlbMUBWgp == mlbMUBWgp- 1 ) mlbMUBWgp=1115872346; else mlbMUBWgp=319257792;if (mlbMUBWgp == mlbMUBWgp- 1 ) mlbMUBWgp=1860629718; else mlbMUBWgp=419208561;if (mlbMUBWgp == mlbMUBWgp- 1 ) mlbMUBWgp=1935032116; else mlbMUBWgp=504350531;if (mlbMUBWgp == mlbMUBWgp- 0 ) mlbMUBWgp=1256479103; else mlbMUBWgp=451044465;if (mlbMUBWgp == mlbMUBWgp- 1 ) mlbMUBWgp=1537573268; else mlbMUBWgp=1352279162;if (mlbMUBWgp == mlbMUBWgp- 1 ) mlbMUBWgp=1327057350; else mlbMUBWgp=1051914361;double tGyYFVMrF=1477599628.0959680;if (tGyYFVMrF == tGyYFVMrF ) tGyYFVMrF=1188793412.6056323; else tGyYFVMrF=2129939651.7539523;if (tGyYFVMrF == tGyYFVMrF ) tGyYFVMrF=2088061472.4337639; else tGyYFVMrF=2071525562.2044685;if (tGyYFVMrF == tGyYFVMrF ) tGyYFVMrF=1024285425.8043090; else tGyYFVMrF=2064382442.5196846;if (tGyYFVMrF == tGyYFVMrF ) tGyYFVMrF=2130378779.0284347; else tGyYFVMrF=1788069369.6220615;if (tGyYFVMrF == tGyYFVMrF ) tGyYFVMrF=440699494.0238499; else tGyYFVMrF=78029448.6075439;if (tGyYFVMrF == tGyYFVMrF ) tGyYFVMrF=2035192996.2528932; else tGyYFVMrF=296181967.9714592;int GNUldXyis=1093114796;if (GNUldXyis == GNUldXyis- 1 ) GNUldXyis=1988570485; else GNUldXyis=1037354362;if (GNUldXyis == GNUldXyis- 0 ) GNUldXyis=488637340; else GNUldXyis=1633773409;if (GNUldXyis == GNUldXyis- 1 ) GNUldXyis=20689164; else GNUldXyis=1330024323;if (GNUldXyis == GNUldXyis- 1 ) GNUldXyis=319106275; else GNUldXyis=1702140138;if (GNUldXyis == GNUldXyis- 0 ) GNUldXyis=82922597; else GNUldXyis=87493732;if (GNUldXyis == GNUldXyis- 0 ) GNUldXyis=189094932; else GNUldXyis=1249779400;float LAopQMcSy=581801028.2486111f;if (LAopQMcSy - LAopQMcSy> 0.00000001 ) LAopQMcSy=1531140206.7239493f; else LAopQMcSy=1213867457.7105251f;if (LAopQMcSy - LAopQMcSy> 0.00000001 ) LAopQMcSy=1725900456.6133401f; else LAopQMcSy=488754295.3149664f;if (LAopQMcSy - LAopQMcSy> 0.00000001 ) LAopQMcSy=684508572.7304474f; else LAopQMcSy=861428433.2307121f;if (LAopQMcSy - LAopQMcSy> 0.00000001 ) LAopQMcSy=1038860691.5085647f; else LAopQMcSy=1198973551.4537115f;if (LAopQMcSy - LAopQMcSy> 0.00000001 ) LAopQMcSy=336362660.1908400f; else LAopQMcSy=72560349.8118985f;if (LAopQMcSy - LAopQMcSy> 0.00000001 ) LAopQMcSy=2125992714.8474818f; else LAopQMcSy=1857002668.2751283f; }
 LAopQMcSyy::LAopQMcSyy()
 { this->amywXfcuHdwX("yawwlpPUkamywXfcuHdwXj", true, 616641182, 960297136, 536919650); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class warWHVxVby
 { 
public: bool jOKIgzZSa; double jOKIgzZSawarWHVxVb; warWHVxVby(); void lZViuwTEUKBO(string jOKIgzZSalZViuwTEUKBO, bool TtLBVoNYd, int RHohAeXJt, float sAqpCQYjr, long fRNmhDMdV);
 protected: bool jOKIgzZSao; double jOKIgzZSawarWHVxVbf; void lZViuwTEUKBOu(string jOKIgzZSalZViuwTEUKBOg, bool TtLBVoNYde, int RHohAeXJtr, float sAqpCQYjrw, long fRNmhDMdVn);
 private: bool jOKIgzZSaTtLBVoNYd; double jOKIgzZSasAqpCQYjrwarWHVxVb;
 void lZViuwTEUKBOv(string TtLBVoNYdlZViuwTEUKBO, bool TtLBVoNYdRHohAeXJt, int RHohAeXJtjOKIgzZSa, float sAqpCQYjrfRNmhDMdV, long fRNmhDMdVTtLBVoNYd); };
 void warWHVxVby::lZViuwTEUKBO(string jOKIgzZSalZViuwTEUKBO, bool TtLBVoNYd, int RHohAeXJt, float sAqpCQYjr, long fRNmhDMdV)
 { float JoIeLliNj=287719889.4972382f;if (JoIeLliNj - JoIeLliNj> 0.00000001 ) JoIeLliNj=1697643705.5225903f; else JoIeLliNj=1649826661.8310222f;if (JoIeLliNj - JoIeLliNj> 0.00000001 ) JoIeLliNj=1425602081.6024936f; else JoIeLliNj=62502349.5203278f;if (JoIeLliNj - JoIeLliNj> 0.00000001 ) JoIeLliNj=645541475.3154257f; else JoIeLliNj=1244437559.3778481f;if (JoIeLliNj - JoIeLliNj> 0.00000001 ) JoIeLliNj=1531657586.6629568f; else JoIeLliNj=60486733.0684671f;if (JoIeLliNj - JoIeLliNj> 0.00000001 ) JoIeLliNj=2095264843.0337455f; else JoIeLliNj=499084414.3761764f;if (JoIeLliNj - JoIeLliNj> 0.00000001 ) JoIeLliNj=1683343454.3665650f; else JoIeLliNj=1011725406.7847114f;double jxiqdPWUF=1461771283.6906114;if (jxiqdPWUF == jxiqdPWUF ) jxiqdPWUF=1862124471.8985635; else jxiqdPWUF=54015779.5443494;if (jxiqdPWUF == jxiqdPWUF ) jxiqdPWUF=523500301.4567260; else jxiqdPWUF=1054777119.0649762;if (jxiqdPWUF == jxiqdPWUF ) jxiqdPWUF=1569383277.0207030; else jxiqdPWUF=1653247201.6862407;if (jxiqdPWUF == jxiqdPWUF ) jxiqdPWUF=1188504585.6294912; else jxiqdPWUF=461521948.5400659;if (jxiqdPWUF == jxiqdPWUF ) jxiqdPWUF=138174134.4470845; else jxiqdPWUF=1383002604.3564749;if (jxiqdPWUF == jxiqdPWUF ) jxiqdPWUF=1899978827.7159645; else jxiqdPWUF=649772656.5659606;long BnRqJMYyJ=1912715202;if (BnRqJMYyJ == BnRqJMYyJ- 1 ) BnRqJMYyJ=1840802063; else BnRqJMYyJ=1957847385;if (BnRqJMYyJ == BnRqJMYyJ- 0 ) BnRqJMYyJ=1980512661; else BnRqJMYyJ=1883429223;if (BnRqJMYyJ == BnRqJMYyJ- 0 ) BnRqJMYyJ=984493899; else BnRqJMYyJ=732017222;if (BnRqJMYyJ == BnRqJMYyJ- 1 ) BnRqJMYyJ=1409461141; else BnRqJMYyJ=1340624647;if (BnRqJMYyJ == BnRqJMYyJ- 0 ) BnRqJMYyJ=1112976248; else BnRqJMYyJ=25228055;if (BnRqJMYyJ == BnRqJMYyJ- 0 ) BnRqJMYyJ=1763529944; else BnRqJMYyJ=2103193681;long bRHsJuKBb=1419732060;if (bRHsJuKBb == bRHsJuKBb- 0 ) bRHsJuKBb=1863329638; else bRHsJuKBb=1716383825;if (bRHsJuKBb == bRHsJuKBb- 1 ) bRHsJuKBb=1599813052; else bRHsJuKBb=1287705229;if (bRHsJuKBb == bRHsJuKBb- 0 ) bRHsJuKBb=1846164343; else bRHsJuKBb=1038273379;if (bRHsJuKBb == bRHsJuKBb- 0 ) bRHsJuKBb=865820259; else bRHsJuKBb=44396504;if (bRHsJuKBb == bRHsJuKBb- 0 ) bRHsJuKBb=461322076; else bRHsJuKBb=964080133;if (bRHsJuKBb == bRHsJuKBb- 1 ) bRHsJuKBb=2071811862; else bRHsJuKBb=1410022518;float qpUJddEyi=605690542.4337122f;if (qpUJddEyi - qpUJddEyi> 0.00000001 ) qpUJddEyi=1576707817.0075229f; else qpUJddEyi=1918111899.1647464f;if (qpUJddEyi - qpUJddEyi> 0.00000001 ) qpUJddEyi=1318406990.6207754f; else qpUJddEyi=1661208600.0125005f;if (qpUJddEyi - qpUJddEyi> 0.00000001 ) qpUJddEyi=727657357.1700643f; else qpUJddEyi=392188041.4458213f;if (qpUJddEyi - qpUJddEyi> 0.00000001 ) qpUJddEyi=477277384.1647868f; else qpUJddEyi=1130107249.2415891f;if (qpUJddEyi - qpUJddEyi> 0.00000001 ) qpUJddEyi=792038285.0513240f; else qpUJddEyi=1330359301.9478323f;if (qpUJddEyi - qpUJddEyi> 0.00000001 ) qpUJddEyi=2089284518.8595429f; else qpUJddEyi=1544155222.5982580f;double warWHVxVb=958924199.7852747;if (warWHVxVb == warWHVxVb ) warWHVxVb=1661502483.6906807; else warWHVxVb=480246767.2465855;if (warWHVxVb == warWHVxVb ) warWHVxVb=933926665.2875229; else warWHVxVb=1871474337.5003760;if (warWHVxVb == warWHVxVb ) warWHVxVb=2037244896.7971860; else warWHVxVb=1929638662.6807838;if (warWHVxVb == warWHVxVb ) warWHVxVb=66550859.1506795; else warWHVxVb=802528684.0875382;if (warWHVxVb == warWHVxVb ) warWHVxVb=1092027126.9031476; else warWHVxVb=1936116157.5050956;if (warWHVxVb == warWHVxVb ) warWHVxVb=1422107147.0885914; else warWHVxVb=20413766.5181867; }
 warWHVxVby::warWHVxVby()
 { this->lZViuwTEUKBO("jOKIgzZSalZViuwTEUKBOj", true, 807689007, 2146922270, 1996165915); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class aNCYGFjluy
 { 
public: bool dsuLZsTVw; double dsuLZsTVwaNCYGFjlu; aNCYGFjluy(); void hzNAIBKkaLUW(string dsuLZsTVwhzNAIBKkaLUW, bool gbsOoXxEY, int ATiJVwZGF, float OzHYPtwSN, long oVaUEUFAi);
 protected: bool dsuLZsTVwo; double dsuLZsTVwaNCYGFjluf; void hzNAIBKkaLUWu(string dsuLZsTVwhzNAIBKkaLUWg, bool gbsOoXxEYe, int ATiJVwZGFr, float OzHYPtwSNw, long oVaUEUFAin);
 private: bool dsuLZsTVwgbsOoXxEY; double dsuLZsTVwOzHYPtwSNaNCYGFjlu;
 void hzNAIBKkaLUWv(string gbsOoXxEYhzNAIBKkaLUW, bool gbsOoXxEYATiJVwZGF, int ATiJVwZGFdsuLZsTVw, float OzHYPtwSNoVaUEUFAi, long oVaUEUFAigbsOoXxEY); };
 void aNCYGFjluy::hzNAIBKkaLUW(string dsuLZsTVwhzNAIBKkaLUW, bool gbsOoXxEY, int ATiJVwZGF, float OzHYPtwSN, long oVaUEUFAi)
 { int vKJmYWaJO=1582709596;if (vKJmYWaJO == vKJmYWaJO- 0 ) vKJmYWaJO=1485607796; else vKJmYWaJO=1287440188;if (vKJmYWaJO == vKJmYWaJO- 1 ) vKJmYWaJO=1328808527; else vKJmYWaJO=1640872224;if (vKJmYWaJO == vKJmYWaJO- 0 ) vKJmYWaJO=925932736; else vKJmYWaJO=831828737;if (vKJmYWaJO == vKJmYWaJO- 1 ) vKJmYWaJO=1417055794; else vKJmYWaJO=1196045232;if (vKJmYWaJO == vKJmYWaJO- 0 ) vKJmYWaJO=459133291; else vKJmYWaJO=590474238;if (vKJmYWaJO == vKJmYWaJO- 0 ) vKJmYWaJO=1171207669; else vKJmYWaJO=1757965398;float SSzEohSzF=1981027289.5417263f;if (SSzEohSzF - SSzEohSzF> 0.00000001 ) SSzEohSzF=658721460.6593531f; else SSzEohSzF=512626218.5710016f;if (SSzEohSzF - SSzEohSzF> 0.00000001 ) SSzEohSzF=1831626888.4753961f; else SSzEohSzF=353070690.1888487f;if (SSzEohSzF - SSzEohSzF> 0.00000001 ) SSzEohSzF=1310018843.5492658f; else SSzEohSzF=1612049488.9109070f;if (SSzEohSzF - SSzEohSzF> 0.00000001 ) SSzEohSzF=1902294179.6502842f; else SSzEohSzF=631626217.8744125f;if (SSzEohSzF - SSzEohSzF> 0.00000001 ) SSzEohSzF=1145025881.7261541f; else SSzEohSzF=1786535503.3285686f;if (SSzEohSzF - SSzEohSzF> 0.00000001 ) SSzEohSzF=224240106.7549026f; else SSzEohSzF=1147352675.3876567f;long XqZQPIuYp=1899119784;if (XqZQPIuYp == XqZQPIuYp- 1 ) XqZQPIuYp=2033410753; else XqZQPIuYp=322294734;if (XqZQPIuYp == XqZQPIuYp- 1 ) XqZQPIuYp=597458770; else XqZQPIuYp=879072739;if (XqZQPIuYp == XqZQPIuYp- 0 ) XqZQPIuYp=989509752; else XqZQPIuYp=1255085898;if (XqZQPIuYp == XqZQPIuYp- 1 ) XqZQPIuYp=1635655960; else XqZQPIuYp=149031961;if (XqZQPIuYp == XqZQPIuYp- 0 ) XqZQPIuYp=1407174492; else XqZQPIuYp=1198708966;if (XqZQPIuYp == XqZQPIuYp- 0 ) XqZQPIuYp=900603178; else XqZQPIuYp=614170202;double TEYKUiaXs=1213282841.4644662;if (TEYKUiaXs == TEYKUiaXs ) TEYKUiaXs=315394519.1477210; else TEYKUiaXs=197692103.0928229;if (TEYKUiaXs == TEYKUiaXs ) TEYKUiaXs=82949224.0298708; else TEYKUiaXs=80241902.2323361;if (TEYKUiaXs == TEYKUiaXs ) TEYKUiaXs=760664082.3501610; else TEYKUiaXs=26960242.4611520;if (TEYKUiaXs == TEYKUiaXs ) TEYKUiaXs=272690753.1084825; else TEYKUiaXs=2021041955.5569740;if (TEYKUiaXs == TEYKUiaXs ) TEYKUiaXs=1532629656.2540508; else TEYKUiaXs=697182310.4276106;if (TEYKUiaXs == TEYKUiaXs ) TEYKUiaXs=495846343.6972891; else TEYKUiaXs=1286880880.3405569;double TKziBLBkH=90779960.3162446;if (TKziBLBkH == TKziBLBkH ) TKziBLBkH=1593721631.3646495; else TKziBLBkH=1419571532.5928089;if (TKziBLBkH == TKziBLBkH ) TKziBLBkH=1872038292.1315371; else TKziBLBkH=1972754526.7993643;if (TKziBLBkH == TKziBLBkH ) TKziBLBkH=788266200.4824818; else TKziBLBkH=1355191972.9208489;if (TKziBLBkH == TKziBLBkH ) TKziBLBkH=991517537.1291262; else TKziBLBkH=1551119209.8672867;if (TKziBLBkH == TKziBLBkH ) TKziBLBkH=1024453905.8539531; else TKziBLBkH=1682594927.2042823;if (TKziBLBkH == TKziBLBkH ) TKziBLBkH=1093379845.2189027; else TKziBLBkH=111309877.7135917;double aNCYGFjlu=1526851899.0848158;if (aNCYGFjlu == aNCYGFjlu ) aNCYGFjlu=337958372.2304522; else aNCYGFjlu=1158440912.7073315;if (aNCYGFjlu == aNCYGFjlu ) aNCYGFjlu=831958156.3929392; else aNCYGFjlu=409651983.3648099;if (aNCYGFjlu == aNCYGFjlu ) aNCYGFjlu=285404107.7271049; else aNCYGFjlu=1063994352.5779904;if (aNCYGFjlu == aNCYGFjlu ) aNCYGFjlu=1138455702.3130417; else aNCYGFjlu=2006450511.9309770;if (aNCYGFjlu == aNCYGFjlu ) aNCYGFjlu=49603981.7775441; else aNCYGFjlu=723900462.9033869;if (aNCYGFjlu == aNCYGFjlu ) aNCYGFjlu=1493926730.2605980; else aNCYGFjlu=292327442.6287928; }
 aNCYGFjluy::aNCYGFjluy()
 { this->hzNAIBKkaLUW("dsuLZsTVwhzNAIBKkaLUWj", true, 759239555, 348775080, 1688926977); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class fzyyWNVohy
 { 
public: bool gPKzDqCUB; double gPKzDqCUBfzyyWNVoh; fzyyWNVohy(); void hQIIccnCJCBw(string gPKzDqCUBhQIIccnCJCBw, bool AOxipptlh, int mYFfSjCsI, float brXNtJTCy, long QheZyhBJa);
 protected: bool gPKzDqCUBo; double gPKzDqCUBfzyyWNVohf; void hQIIccnCJCBwu(string gPKzDqCUBhQIIccnCJCBwg, bool AOxipptlhe, int mYFfSjCsIr, float brXNtJTCyw, long QheZyhBJan);
 private: bool gPKzDqCUBAOxipptlh; double gPKzDqCUBbrXNtJTCyfzyyWNVoh;
 void hQIIccnCJCBwv(string AOxipptlhhQIIccnCJCBw, bool AOxipptlhmYFfSjCsI, int mYFfSjCsIgPKzDqCUB, float brXNtJTCyQheZyhBJa, long QheZyhBJaAOxipptlh); };
 void fzyyWNVohy::hQIIccnCJCBw(string gPKzDqCUBhQIIccnCJCBw, bool AOxipptlh, int mYFfSjCsI, float brXNtJTCy, long QheZyhBJa)
 { double vZsMlvDFu=662431510.8210117;if (vZsMlvDFu == vZsMlvDFu ) vZsMlvDFu=205721880.0544974; else vZsMlvDFu=595527579.1180424;if (vZsMlvDFu == vZsMlvDFu ) vZsMlvDFu=1622052105.9592708; else vZsMlvDFu=1569235861.1009738;if (vZsMlvDFu == vZsMlvDFu ) vZsMlvDFu=778332423.2483118; else vZsMlvDFu=1255432676.3654965;if (vZsMlvDFu == vZsMlvDFu ) vZsMlvDFu=1136061537.5981069; else vZsMlvDFu=847760780.7294190;if (vZsMlvDFu == vZsMlvDFu ) vZsMlvDFu=1050907595.5562479; else vZsMlvDFu=918937054.8174167;if (vZsMlvDFu == vZsMlvDFu ) vZsMlvDFu=846193992.0488436; else vZsMlvDFu=1166862727.1388896;int uuwKsoFwJ=1777618062;if (uuwKsoFwJ == uuwKsoFwJ- 0 ) uuwKsoFwJ=486177076; else uuwKsoFwJ=444592552;if (uuwKsoFwJ == uuwKsoFwJ- 1 ) uuwKsoFwJ=1397232446; else uuwKsoFwJ=1558233622;if (uuwKsoFwJ == uuwKsoFwJ- 0 ) uuwKsoFwJ=437573410; else uuwKsoFwJ=2055688135;if (uuwKsoFwJ == uuwKsoFwJ- 0 ) uuwKsoFwJ=318468586; else uuwKsoFwJ=1857728039;if (uuwKsoFwJ == uuwKsoFwJ- 0 ) uuwKsoFwJ=892553529; else uuwKsoFwJ=1010695447;if (uuwKsoFwJ == uuwKsoFwJ- 0 ) uuwKsoFwJ=1765504589; else uuwKsoFwJ=129243426;double wTVPNudGF=816716480.8719535;if (wTVPNudGF == wTVPNudGF ) wTVPNudGF=1896920406.3221854; else wTVPNudGF=700616418.6420605;if (wTVPNudGF == wTVPNudGF ) wTVPNudGF=1375742448.5900213; else wTVPNudGF=1798715400.0752473;if (wTVPNudGF == wTVPNudGF ) wTVPNudGF=245170580.3264949; else wTVPNudGF=2041032746.7918571;if (wTVPNudGF == wTVPNudGF ) wTVPNudGF=1606425605.7547993; else wTVPNudGF=430584063.8104334;if (wTVPNudGF == wTVPNudGF ) wTVPNudGF=26557692.5805813; else wTVPNudGF=1687683465.3667778;if (wTVPNudGF == wTVPNudGF ) wTVPNudGF=1743757606.1028423; else wTVPNudGF=729628458.3255905;long jDiFaKHGN=2093652279;if (jDiFaKHGN == jDiFaKHGN- 0 ) jDiFaKHGN=743593031; else jDiFaKHGN=87210915;if (jDiFaKHGN == jDiFaKHGN- 0 ) jDiFaKHGN=1288620300; else jDiFaKHGN=95026805;if (jDiFaKHGN == jDiFaKHGN- 0 ) jDiFaKHGN=1024990529; else jDiFaKHGN=710946931;if (jDiFaKHGN == jDiFaKHGN- 0 ) jDiFaKHGN=224858100; else jDiFaKHGN=297517392;if (jDiFaKHGN == jDiFaKHGN- 1 ) jDiFaKHGN=277058993; else jDiFaKHGN=1911807713;if (jDiFaKHGN == jDiFaKHGN- 0 ) jDiFaKHGN=676682332; else jDiFaKHGN=1915120623;double rOqZDjQxG=1765498733.1158152;if (rOqZDjQxG == rOqZDjQxG ) rOqZDjQxG=2098449451.6794195; else rOqZDjQxG=29477512.5311652;if (rOqZDjQxG == rOqZDjQxG ) rOqZDjQxG=1417425968.4460901; else rOqZDjQxG=417008227.2363688;if (rOqZDjQxG == rOqZDjQxG ) rOqZDjQxG=408303615.9852519; else rOqZDjQxG=978395569.7892439;if (rOqZDjQxG == rOqZDjQxG ) rOqZDjQxG=1532447482.7700678; else rOqZDjQxG=592627977.7082514;if (rOqZDjQxG == rOqZDjQxG ) rOqZDjQxG=985650594.4315276; else rOqZDjQxG=966648383.5792538;if (rOqZDjQxG == rOqZDjQxG ) rOqZDjQxG=1531675930.7796736; else rOqZDjQxG=897373592.7741112;float fzyyWNVoh=84225742.6037666f;if (fzyyWNVoh - fzyyWNVoh> 0.00000001 ) fzyyWNVoh=1530068603.8583896f; else fzyyWNVoh=1819335957.1135562f;if (fzyyWNVoh - fzyyWNVoh> 0.00000001 ) fzyyWNVoh=1533134042.2460430f; else fzyyWNVoh=1734639982.5914119f;if (fzyyWNVoh - fzyyWNVoh> 0.00000001 ) fzyyWNVoh=144272209.7495255f; else fzyyWNVoh=872944445.2915405f;if (fzyyWNVoh - fzyyWNVoh> 0.00000001 ) fzyyWNVoh=1939209598.8876584f; else fzyyWNVoh=1185973475.6772373f;if (fzyyWNVoh - fzyyWNVoh> 0.00000001 ) fzyyWNVoh=475758318.6808984f; else fzyyWNVoh=1078225056.7414281f;if (fzyyWNVoh - fzyyWNVoh> 0.00000001 ) fzyyWNVoh=1521656407.6661458f; else fzyyWNVoh=480846514.1486352f; }
 fzyyWNVohy::fzyyWNVohy()
 { this->hQIIccnCJCBw("gPKzDqCUBhQIIccnCJCBwj", true, 1364350414, 1838788629, 940655976); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class dDRXBbsxFy
 { 
public: bool OyOKybLeh; double OyOKybLehdDRXBbsxF; dDRXBbsxFy(); void GpCtaFHbnMCS(string OyOKybLehGpCtaFHbnMCS, bool BvWOOebWk, int WSTLgVyMk, float BznqsjRcW, long QVnldLZVH);
 protected: bool OyOKybLeho; double OyOKybLehdDRXBbsxFf; void GpCtaFHbnMCSu(string OyOKybLehGpCtaFHbnMCSg, bool BvWOOebWke, int WSTLgVyMkr, float BznqsjRcWw, long QVnldLZVHn);
 private: bool OyOKybLehBvWOOebWk; double OyOKybLehBznqsjRcWdDRXBbsxF;
 void GpCtaFHbnMCSv(string BvWOOebWkGpCtaFHbnMCS, bool BvWOOebWkWSTLgVyMk, int WSTLgVyMkOyOKybLeh, float BznqsjRcWQVnldLZVH, long QVnldLZVHBvWOOebWk); };
 void dDRXBbsxFy::GpCtaFHbnMCS(string OyOKybLehGpCtaFHbnMCS, bool BvWOOebWk, int WSTLgVyMk, float BznqsjRcW, long QVnldLZVH)
 { double IOicLLbxp=692862173.4902099;if (IOicLLbxp == IOicLLbxp ) IOicLLbxp=549191140.9625937; else IOicLLbxp=401439216.8047130;if (IOicLLbxp == IOicLLbxp ) IOicLLbxp=975506599.1417773; else IOicLLbxp=732496253.0943365;if (IOicLLbxp == IOicLLbxp ) IOicLLbxp=1882540638.6326799; else IOicLLbxp=1110006837.3982223;if (IOicLLbxp == IOicLLbxp ) IOicLLbxp=739890744.5015243; else IOicLLbxp=37607592.6054269;if (IOicLLbxp == IOicLLbxp ) IOicLLbxp=1039326771.8927723; else IOicLLbxp=1749030370.8225529;if (IOicLLbxp == IOicLLbxp ) IOicLLbxp=283513946.5365606; else IOicLLbxp=950561655.9391320;int mJWLyaCeb=275311048;if (mJWLyaCeb == mJWLyaCeb- 0 ) mJWLyaCeb=957494824; else mJWLyaCeb=749474537;if (mJWLyaCeb == mJWLyaCeb- 0 ) mJWLyaCeb=123802898; else mJWLyaCeb=1068371882;if (mJWLyaCeb == mJWLyaCeb- 0 ) mJWLyaCeb=1743159259; else mJWLyaCeb=2040469107;if (mJWLyaCeb == mJWLyaCeb- 1 ) mJWLyaCeb=2120490305; else mJWLyaCeb=875173147;if (mJWLyaCeb == mJWLyaCeb- 0 ) mJWLyaCeb=1592485392; else mJWLyaCeb=2033835510;if (mJWLyaCeb == mJWLyaCeb- 0 ) mJWLyaCeb=1580426982; else mJWLyaCeb=1680477973;int ixstIiWjJ=943026724;if (ixstIiWjJ == ixstIiWjJ- 1 ) ixstIiWjJ=995314340; else ixstIiWjJ=74635691;if (ixstIiWjJ == ixstIiWjJ- 0 ) ixstIiWjJ=1047158092; else ixstIiWjJ=1671601800;if (ixstIiWjJ == ixstIiWjJ- 0 ) ixstIiWjJ=783280203; else ixstIiWjJ=1499310442;if (ixstIiWjJ == ixstIiWjJ- 1 ) ixstIiWjJ=434338443; else ixstIiWjJ=1655795419;if (ixstIiWjJ == ixstIiWjJ- 0 ) ixstIiWjJ=2131987528; else ixstIiWjJ=1358198555;if (ixstIiWjJ == ixstIiWjJ- 1 ) ixstIiWjJ=414646844; else ixstIiWjJ=238495734;float PicXLLmkI=587808643.0453168f;if (PicXLLmkI - PicXLLmkI> 0.00000001 ) PicXLLmkI=1225228093.1694534f; else PicXLLmkI=1667942175.5866774f;if (PicXLLmkI - PicXLLmkI> 0.00000001 ) PicXLLmkI=1282295311.9432299f; else PicXLLmkI=1378427104.4599413f;if (PicXLLmkI - PicXLLmkI> 0.00000001 ) PicXLLmkI=1262756228.5969997f; else PicXLLmkI=1525630986.7136745f;if (PicXLLmkI - PicXLLmkI> 0.00000001 ) PicXLLmkI=1097186561.9933091f; else PicXLLmkI=656205680.1310708f;if (PicXLLmkI - PicXLLmkI> 0.00000001 ) PicXLLmkI=428432558.2052311f; else PicXLLmkI=100333452.9179973f;if (PicXLLmkI - PicXLLmkI> 0.00000001 ) PicXLLmkI=1287494508.3065645f; else PicXLLmkI=1996188775.6775334f;int YxKtyZDoY=1049937942;if (YxKtyZDoY == YxKtyZDoY- 1 ) YxKtyZDoY=1380791019; else YxKtyZDoY=1487970869;if (YxKtyZDoY == YxKtyZDoY- 0 ) YxKtyZDoY=2102730962; else YxKtyZDoY=1728820695;if (YxKtyZDoY == YxKtyZDoY- 1 ) YxKtyZDoY=45456497; else YxKtyZDoY=570399205;if (YxKtyZDoY == YxKtyZDoY- 1 ) YxKtyZDoY=1639514492; else YxKtyZDoY=1605668029;if (YxKtyZDoY == YxKtyZDoY- 0 ) YxKtyZDoY=315136094; else YxKtyZDoY=615491126;if (YxKtyZDoY == YxKtyZDoY- 0 ) YxKtyZDoY=1083868001; else YxKtyZDoY=384960704;long dDRXBbsxF=1400781395;if (dDRXBbsxF == dDRXBbsxF- 1 ) dDRXBbsxF=2048412837; else dDRXBbsxF=992618339;if (dDRXBbsxF == dDRXBbsxF- 0 ) dDRXBbsxF=455249880; else dDRXBbsxF=123501090;if (dDRXBbsxF == dDRXBbsxF- 1 ) dDRXBbsxF=854577165; else dDRXBbsxF=1137295894;if (dDRXBbsxF == dDRXBbsxF- 1 ) dDRXBbsxF=1827754143; else dDRXBbsxF=1617167001;if (dDRXBbsxF == dDRXBbsxF- 0 ) dDRXBbsxF=1124932777; else dDRXBbsxF=390952412;if (dDRXBbsxF == dDRXBbsxF- 1 ) dDRXBbsxF=1243169242; else dDRXBbsxF=682946751; }
 dDRXBbsxFy::dDRXBbsxFy()
 { this->GpCtaFHbnMCS("OyOKybLehGpCtaFHbnMCSj", true, 211815934, 585633315, 2126215564); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class BpXBZSDozy
 { 
public: bool yRqdkazOc; double yRqdkazOcBpXBZSDoz; BpXBZSDozy(); void hTjhiWNlHKGM(string yRqdkazOchTjhiWNlHKGM, bool FwUWnUrwp, int CsUrEQUFM, float HNPaMbhrn, long dxgWsYdGB);
 protected: bool yRqdkazOco; double yRqdkazOcBpXBZSDozf; void hTjhiWNlHKGMu(string yRqdkazOchTjhiWNlHKGMg, bool FwUWnUrwpe, int CsUrEQUFMr, float HNPaMbhrnw, long dxgWsYdGBn);
 private: bool yRqdkazOcFwUWnUrwp; double yRqdkazOcHNPaMbhrnBpXBZSDoz;
 void hTjhiWNlHKGMv(string FwUWnUrwphTjhiWNlHKGM, bool FwUWnUrwpCsUrEQUFM, int CsUrEQUFMyRqdkazOc, float HNPaMbhrndxgWsYdGB, long dxgWsYdGBFwUWnUrwp); };
 void BpXBZSDozy::hTjhiWNlHKGM(string yRqdkazOchTjhiWNlHKGM, bool FwUWnUrwp, int CsUrEQUFM, float HNPaMbhrn, long dxgWsYdGB)
 { float qBeGKVckL=184649191.1951994f;if (qBeGKVckL - qBeGKVckL> 0.00000001 ) qBeGKVckL=649247793.4829333f; else qBeGKVckL=1326325677.0807014f;if (qBeGKVckL - qBeGKVckL> 0.00000001 ) qBeGKVckL=1721708575.8514881f; else qBeGKVckL=359371954.5548827f;if (qBeGKVckL - qBeGKVckL> 0.00000001 ) qBeGKVckL=1191514632.8437810f; else qBeGKVckL=853818971.8213510f;if (qBeGKVckL - qBeGKVckL> 0.00000001 ) qBeGKVckL=625863696.3646294f; else qBeGKVckL=623109679.4571139f;if (qBeGKVckL - qBeGKVckL> 0.00000001 ) qBeGKVckL=517902440.4815262f; else qBeGKVckL=1430179518.4712140f;if (qBeGKVckL - qBeGKVckL> 0.00000001 ) qBeGKVckL=1644392392.3024813f; else qBeGKVckL=2068240038.0036344f;int eblmEXWxn=465237192;if (eblmEXWxn == eblmEXWxn- 0 ) eblmEXWxn=54310317; else eblmEXWxn=1293779764;if (eblmEXWxn == eblmEXWxn- 1 ) eblmEXWxn=1431607521; else eblmEXWxn=1359983696;if (eblmEXWxn == eblmEXWxn- 1 ) eblmEXWxn=1193882756; else eblmEXWxn=269447709;if (eblmEXWxn == eblmEXWxn- 1 ) eblmEXWxn=162222175; else eblmEXWxn=1276554752;if (eblmEXWxn == eblmEXWxn- 1 ) eblmEXWxn=506301024; else eblmEXWxn=1041921177;if (eblmEXWxn == eblmEXWxn- 0 ) eblmEXWxn=2102775277; else eblmEXWxn=106294215;double MUFostIJJ=1854605987.3581941;if (MUFostIJJ == MUFostIJJ ) MUFostIJJ=2145647439.5589304; else MUFostIJJ=2102800094.7689235;if (MUFostIJJ == MUFostIJJ ) MUFostIJJ=1535401991.6175801; else MUFostIJJ=709645087.3212447;if (MUFostIJJ == MUFostIJJ ) MUFostIJJ=1658346761.2872528; else MUFostIJJ=1725633299.2374331;if (MUFostIJJ == MUFostIJJ ) MUFostIJJ=2029584888.7168887; else MUFostIJJ=476434450.4172413;if (MUFostIJJ == MUFostIJJ ) MUFostIJJ=1381821027.3879775; else MUFostIJJ=228652492.8278275;if (MUFostIJJ == MUFostIJJ ) MUFostIJJ=861058504.9115816; else MUFostIJJ=14523403.2656718;long zDEHZsZBW=413639632;if (zDEHZsZBW == zDEHZsZBW- 1 ) zDEHZsZBW=223404952; else zDEHZsZBW=1234313585;if (zDEHZsZBW == zDEHZsZBW- 1 ) zDEHZsZBW=1608047367; else zDEHZsZBW=1989852348;if (zDEHZsZBW == zDEHZsZBW- 0 ) zDEHZsZBW=1265800111; else zDEHZsZBW=1519790995;if (zDEHZsZBW == zDEHZsZBW- 0 ) zDEHZsZBW=1138250082; else zDEHZsZBW=379800084;if (zDEHZsZBW == zDEHZsZBW- 1 ) zDEHZsZBW=1164103502; else zDEHZsZBW=445153823;if (zDEHZsZBW == zDEHZsZBW- 1 ) zDEHZsZBW=2000554577; else zDEHZsZBW=149593455;double LCtrZbCsW=262912693.7572733;if (LCtrZbCsW == LCtrZbCsW ) LCtrZbCsW=489721252.7012703; else LCtrZbCsW=1937270052.3244775;if (LCtrZbCsW == LCtrZbCsW ) LCtrZbCsW=2070076246.5883088; else LCtrZbCsW=1631837427.5602084;if (LCtrZbCsW == LCtrZbCsW ) LCtrZbCsW=149558716.0905068; else LCtrZbCsW=380123387.8287807;if (LCtrZbCsW == LCtrZbCsW ) LCtrZbCsW=954374078.1173213; else LCtrZbCsW=476160665.7007653;if (LCtrZbCsW == LCtrZbCsW ) LCtrZbCsW=1411678523.5207204; else LCtrZbCsW=955173071.3507287;if (LCtrZbCsW == LCtrZbCsW ) LCtrZbCsW=2125646316.6163814; else LCtrZbCsW=965230264.6409823;long BpXBZSDoz=1924938630;if (BpXBZSDoz == BpXBZSDoz- 0 ) BpXBZSDoz=75090588; else BpXBZSDoz=1689135645;if (BpXBZSDoz == BpXBZSDoz- 0 ) BpXBZSDoz=2030372910; else BpXBZSDoz=135983265;if (BpXBZSDoz == BpXBZSDoz- 1 ) BpXBZSDoz=794426027; else BpXBZSDoz=1098089565;if (BpXBZSDoz == BpXBZSDoz- 0 ) BpXBZSDoz=588805876; else BpXBZSDoz=625856444;if (BpXBZSDoz == BpXBZSDoz- 1 ) BpXBZSDoz=964550012; else BpXBZSDoz=1155601907;if (BpXBZSDoz == BpXBZSDoz- 0 ) BpXBZSDoz=1693025232; else BpXBZSDoz=1213192938; }
 BpXBZSDozy::BpXBZSDozy()
 { this->hTjhiWNlHKGM("yRqdkazOchTjhiWNlHKGMj", true, 1872562369, 1879991433, 1725390756); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class eNrSMBQiMy
 { 
public: bool rFKBEeZwJ; double rFKBEeZwJeNrSMBQiM; eNrSMBQiMy(); void YgjvTeDmhRoz(string rFKBEeZwJYgjvTeDmhRoz, bool ohFhIXtXN, int vfQDGjLIv, float steCWHxLu, long HihCYDiVJ);
 protected: bool rFKBEeZwJo; double rFKBEeZwJeNrSMBQiMf; void YgjvTeDmhRozu(string rFKBEeZwJYgjvTeDmhRozg, bool ohFhIXtXNe, int vfQDGjLIvr, float steCWHxLuw, long HihCYDiVJn);
 private: bool rFKBEeZwJohFhIXtXN; double rFKBEeZwJsteCWHxLueNrSMBQiM;
 void YgjvTeDmhRozv(string ohFhIXtXNYgjvTeDmhRoz, bool ohFhIXtXNvfQDGjLIv, int vfQDGjLIvrFKBEeZwJ, float steCWHxLuHihCYDiVJ, long HihCYDiVJohFhIXtXN); };
 void eNrSMBQiMy::YgjvTeDmhRoz(string rFKBEeZwJYgjvTeDmhRoz, bool ohFhIXtXN, int vfQDGjLIv, float steCWHxLu, long HihCYDiVJ)
 { int gayxcUxMe=1224582998;if (gayxcUxMe == gayxcUxMe- 1 ) gayxcUxMe=411692260; else gayxcUxMe=712245183;if (gayxcUxMe == gayxcUxMe- 1 ) gayxcUxMe=827188884; else gayxcUxMe=1240362784;if (gayxcUxMe == gayxcUxMe- 1 ) gayxcUxMe=1163232421; else gayxcUxMe=1766129947;if (gayxcUxMe == gayxcUxMe- 0 ) gayxcUxMe=1646496595; else gayxcUxMe=1980253931;if (gayxcUxMe == gayxcUxMe- 1 ) gayxcUxMe=1606430837; else gayxcUxMe=500266868;if (gayxcUxMe == gayxcUxMe- 1 ) gayxcUxMe=1716684764; else gayxcUxMe=2141604685;float QFvEiQTQP=1298249562.7631126f;if (QFvEiQTQP - QFvEiQTQP> 0.00000001 ) QFvEiQTQP=10523908.8295556f; else QFvEiQTQP=593171160.7370638f;if (QFvEiQTQP - QFvEiQTQP> 0.00000001 ) QFvEiQTQP=1843123180.0017685f; else QFvEiQTQP=1214044209.0866356f;if (QFvEiQTQP - QFvEiQTQP> 0.00000001 ) QFvEiQTQP=1301145016.2318136f; else QFvEiQTQP=2103186134.3544843f;if (QFvEiQTQP - QFvEiQTQP> 0.00000001 ) QFvEiQTQP=744757458.4989348f; else QFvEiQTQP=729608066.7355529f;if (QFvEiQTQP - QFvEiQTQP> 0.00000001 ) QFvEiQTQP=1371657603.5493106f; else QFvEiQTQP=620829771.1725138f;if (QFvEiQTQP - QFvEiQTQP> 0.00000001 ) QFvEiQTQP=1572365423.5738426f; else QFvEiQTQP=2097708810.0980195f;double iOfEhoIYJ=1489053954.3375441;if (iOfEhoIYJ == iOfEhoIYJ ) iOfEhoIYJ=1106031300.9417250; else iOfEhoIYJ=329887089.9386928;if (iOfEhoIYJ == iOfEhoIYJ ) iOfEhoIYJ=1734498694.6535837; else iOfEhoIYJ=2028733205.7022702;if (iOfEhoIYJ == iOfEhoIYJ ) iOfEhoIYJ=773187489.5705896; else iOfEhoIYJ=2058182492.2504755;if (iOfEhoIYJ == iOfEhoIYJ ) iOfEhoIYJ=1509856279.5651297; else iOfEhoIYJ=1541484313.9416142;if (iOfEhoIYJ == iOfEhoIYJ ) iOfEhoIYJ=1081177552.4956584; else iOfEhoIYJ=814783476.6912424;if (iOfEhoIYJ == iOfEhoIYJ ) iOfEhoIYJ=1981951388.0312933; else iOfEhoIYJ=593551628.4825156;float ttfbVoeao=1626232697.7924107f;if (ttfbVoeao - ttfbVoeao> 0.00000001 ) ttfbVoeao=1353122757.5376206f; else ttfbVoeao=1809524146.5814121f;if (ttfbVoeao - ttfbVoeao> 0.00000001 ) ttfbVoeao=1512619545.1183439f; else ttfbVoeao=1544483693.0662998f;if (ttfbVoeao - ttfbVoeao> 0.00000001 ) ttfbVoeao=1175352513.8307463f; else ttfbVoeao=1375855676.0302503f;if (ttfbVoeao - ttfbVoeao> 0.00000001 ) ttfbVoeao=2070921629.8248337f; else ttfbVoeao=455989773.9427886f;if (ttfbVoeao - ttfbVoeao> 0.00000001 ) ttfbVoeao=2114971372.7144198f; else ttfbVoeao=97580818.5277691f;if (ttfbVoeao - ttfbVoeao> 0.00000001 ) ttfbVoeao=2016188828.8919473f; else ttfbVoeao=542402650.5346720f;int qAfnjOLer=1879910171;if (qAfnjOLer == qAfnjOLer- 1 ) qAfnjOLer=606599496; else qAfnjOLer=227630810;if (qAfnjOLer == qAfnjOLer- 1 ) qAfnjOLer=1035573385; else qAfnjOLer=1746465495;if (qAfnjOLer == qAfnjOLer- 1 ) qAfnjOLer=559725143; else qAfnjOLer=344369250;if (qAfnjOLer == qAfnjOLer- 0 ) qAfnjOLer=525062073; else qAfnjOLer=99825063;if (qAfnjOLer == qAfnjOLer- 1 ) qAfnjOLer=1230798528; else qAfnjOLer=301638867;if (qAfnjOLer == qAfnjOLer- 0 ) qAfnjOLer=132866657; else qAfnjOLer=486361540;long eNrSMBQiM=668253613;if (eNrSMBQiM == eNrSMBQiM- 1 ) eNrSMBQiM=1649971165; else eNrSMBQiM=2093616373;if (eNrSMBQiM == eNrSMBQiM- 1 ) eNrSMBQiM=744586053; else eNrSMBQiM=211896231;if (eNrSMBQiM == eNrSMBQiM- 1 ) eNrSMBQiM=361384768; else eNrSMBQiM=496667326;if (eNrSMBQiM == eNrSMBQiM- 1 ) eNrSMBQiM=313701441; else eNrSMBQiM=1877659271;if (eNrSMBQiM == eNrSMBQiM- 1 ) eNrSMBQiM=406449107; else eNrSMBQiM=1278508921;if (eNrSMBQiM == eNrSMBQiM- 0 ) eNrSMBQiM=2061245480; else eNrSMBQiM=675606671; }
 eNrSMBQiMy::eNrSMBQiMy()
 { this->YgjvTeDmhRoz("rFKBEeZwJYgjvTeDmhRozj", true, 41993664, 967453629, 1347719789); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class CehnvcnTby
 { 
public: bool KiSUZdNgV; double KiSUZdNgVCehnvcnTb; CehnvcnTby(); void njulQgYswCZs(string KiSUZdNgVnjulQgYswCZs, bool kuOumCewP, int aeolqyKHM, float VLOXnFJza, long JUMdiIZJN);
 protected: bool KiSUZdNgVo; double KiSUZdNgVCehnvcnTbf; void njulQgYswCZsu(string KiSUZdNgVnjulQgYswCZsg, bool kuOumCewPe, int aeolqyKHMr, float VLOXnFJzaw, long JUMdiIZJNn);
 private: bool KiSUZdNgVkuOumCewP; double KiSUZdNgVVLOXnFJzaCehnvcnTb;
 void njulQgYswCZsv(string kuOumCewPnjulQgYswCZs, bool kuOumCewPaeolqyKHM, int aeolqyKHMKiSUZdNgV, float VLOXnFJzaJUMdiIZJN, long JUMdiIZJNkuOumCewP); };
 void CehnvcnTby::njulQgYswCZs(string KiSUZdNgVnjulQgYswCZs, bool kuOumCewP, int aeolqyKHM, float VLOXnFJza, long JUMdiIZJN)
 { long lYAkkENdv=1142616986;if (lYAkkENdv == lYAkkENdv- 1 ) lYAkkENdv=1691508691; else lYAkkENdv=744583057;if (lYAkkENdv == lYAkkENdv- 0 ) lYAkkENdv=1621787637; else lYAkkENdv=1151795371;if (lYAkkENdv == lYAkkENdv- 0 ) lYAkkENdv=1405752608; else lYAkkENdv=1716246492;if (lYAkkENdv == lYAkkENdv- 0 ) lYAkkENdv=1589770443; else lYAkkENdv=924234945;if (lYAkkENdv == lYAkkENdv- 1 ) lYAkkENdv=1903072282; else lYAkkENdv=135721104;if (lYAkkENdv == lYAkkENdv- 0 ) lYAkkENdv=112405632; else lYAkkENdv=738679425;long oHlocbjSP=1228547703;if (oHlocbjSP == oHlocbjSP- 0 ) oHlocbjSP=782782730; else oHlocbjSP=1981912991;if (oHlocbjSP == oHlocbjSP- 0 ) oHlocbjSP=1423122686; else oHlocbjSP=782767414;if (oHlocbjSP == oHlocbjSP- 0 ) oHlocbjSP=881550730; else oHlocbjSP=1426505416;if (oHlocbjSP == oHlocbjSP- 0 ) oHlocbjSP=577078178; else oHlocbjSP=2119679360;if (oHlocbjSP == oHlocbjSP- 0 ) oHlocbjSP=855789185; else oHlocbjSP=500890812;if (oHlocbjSP == oHlocbjSP- 0 ) oHlocbjSP=1858841255; else oHlocbjSP=1348476866;float MALQMpxyB=259947279.3555644f;if (MALQMpxyB - MALQMpxyB> 0.00000001 ) MALQMpxyB=12576407.4402029f; else MALQMpxyB=2102085994.8371289f;if (MALQMpxyB - MALQMpxyB> 0.00000001 ) MALQMpxyB=1840527715.9865986f; else MALQMpxyB=1568954734.6460315f;if (MALQMpxyB - MALQMpxyB> 0.00000001 ) MALQMpxyB=572004297.9480074f; else MALQMpxyB=2022971011.0532290f;if (MALQMpxyB - MALQMpxyB> 0.00000001 ) MALQMpxyB=1918263491.7554215f; else MALQMpxyB=957919687.8007788f;if (MALQMpxyB - MALQMpxyB> 0.00000001 ) MALQMpxyB=183911929.1528140f; else MALQMpxyB=172238781.0912269f;if (MALQMpxyB - MALQMpxyB> 0.00000001 ) MALQMpxyB=712342784.3438070f; else MALQMpxyB=40349213.0271112f;float rSSrbxBBX=481546472.2564867f;if (rSSrbxBBX - rSSrbxBBX> 0.00000001 ) rSSrbxBBX=51525352.2492367f; else rSSrbxBBX=2135241417.7617591f;if (rSSrbxBBX - rSSrbxBBX> 0.00000001 ) rSSrbxBBX=449319868.8932641f; else rSSrbxBBX=1685898777.6916341f;if (rSSrbxBBX - rSSrbxBBX> 0.00000001 ) rSSrbxBBX=647404703.0233086f; else rSSrbxBBX=801930430.5434202f;if (rSSrbxBBX - rSSrbxBBX> 0.00000001 ) rSSrbxBBX=261066256.2517324f; else rSSrbxBBX=265003275.7422367f;if (rSSrbxBBX - rSSrbxBBX> 0.00000001 ) rSSrbxBBX=167504879.5870368f; else rSSrbxBBX=1649591924.4955164f;if (rSSrbxBBX - rSSrbxBBX> 0.00000001 ) rSSrbxBBX=296006186.6085404f; else rSSrbxBBX=904861796.4190284f;double EBpJuyfhV=1350340213.4027308;if (EBpJuyfhV == EBpJuyfhV ) EBpJuyfhV=1854506469.2203928; else EBpJuyfhV=1999942000.5433522;if (EBpJuyfhV == EBpJuyfhV ) EBpJuyfhV=726103018.1027416; else EBpJuyfhV=1493709264.1506462;if (EBpJuyfhV == EBpJuyfhV ) EBpJuyfhV=1707264764.8305601; else EBpJuyfhV=746333290.3811494;if (EBpJuyfhV == EBpJuyfhV ) EBpJuyfhV=656543406.6735583; else EBpJuyfhV=907295366.0100032;if (EBpJuyfhV == EBpJuyfhV ) EBpJuyfhV=63649500.8176677; else EBpJuyfhV=465202999.2389229;if (EBpJuyfhV == EBpJuyfhV ) EBpJuyfhV=598855485.3271326; else EBpJuyfhV=709311949.8820809;double CehnvcnTb=908446998.4244952;if (CehnvcnTb == CehnvcnTb ) CehnvcnTb=1412162795.3228865; else CehnvcnTb=1377294783.6100737;if (CehnvcnTb == CehnvcnTb ) CehnvcnTb=1296951514.8554707; else CehnvcnTb=955289583.0022679;if (CehnvcnTb == CehnvcnTb ) CehnvcnTb=103412201.2939840; else CehnvcnTb=890283152.2602201;if (CehnvcnTb == CehnvcnTb ) CehnvcnTb=1760026223.5015337; else CehnvcnTb=1358129624.8902653;if (CehnvcnTb == CehnvcnTb ) CehnvcnTb=1841019738.3163974; else CehnvcnTb=1575524440.2729986;if (CehnvcnTb == CehnvcnTb ) CehnvcnTb=1401449855.9526066; else CehnvcnTb=1069896020.0273525; }
 CehnvcnTby::CehnvcnTby()
 { this->njulQgYswCZs("KiSUZdNgVnjulQgYswCZsj", true, 1726964825, 1013401695, 1100514450); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class LXdHKtLvyy
 { 
public: bool ggmqQTtOp; double ggmqQTtOpLXdHKtLvy; LXdHKtLvyy(); void BLClBLYbfwsp(string ggmqQTtOpBLClBLYbfwsp, bool FyJLbVJhm, int USworhBZh, float ADofuuOuX, long cKkamOWTd);
 protected: bool ggmqQTtOpo; double ggmqQTtOpLXdHKtLvyf; void BLClBLYbfwspu(string ggmqQTtOpBLClBLYbfwspg, bool FyJLbVJhme, int USworhBZhr, float ADofuuOuXw, long cKkamOWTdn);
 private: bool ggmqQTtOpFyJLbVJhm; double ggmqQTtOpADofuuOuXLXdHKtLvy;
 void BLClBLYbfwspv(string FyJLbVJhmBLClBLYbfwsp, bool FyJLbVJhmUSworhBZh, int USworhBZhggmqQTtOp, float ADofuuOuXcKkamOWTd, long cKkamOWTdFyJLbVJhm); };
 void LXdHKtLvyy::BLClBLYbfwsp(string ggmqQTtOpBLClBLYbfwsp, bool FyJLbVJhm, int USworhBZh, float ADofuuOuX, long cKkamOWTd)
 { double oigAZLrGF=1898963048.5028824;if (oigAZLrGF == oigAZLrGF ) oigAZLrGF=1236060175.6901474; else oigAZLrGF=1501171414.6072394;if (oigAZLrGF == oigAZLrGF ) oigAZLrGF=770257918.3696326; else oigAZLrGF=1046296908.0712961;if (oigAZLrGF == oigAZLrGF ) oigAZLrGF=2038393295.1229103; else oigAZLrGF=1192875643.5608033;if (oigAZLrGF == oigAZLrGF ) oigAZLrGF=1757312396.7031673; else oigAZLrGF=1307965072.4435096;if (oigAZLrGF == oigAZLrGF ) oigAZLrGF=1904580868.2906235; else oigAZLrGF=1225650407.9633929;if (oigAZLrGF == oigAZLrGF ) oigAZLrGF=1523828339.0084934; else oigAZLrGF=671415223.8923097;double tXFFlOjBM=1292553212.8827119;if (tXFFlOjBM == tXFFlOjBM ) tXFFlOjBM=352361111.1507327; else tXFFlOjBM=532463025.1269816;if (tXFFlOjBM == tXFFlOjBM ) tXFFlOjBM=1017516140.7361397; else tXFFlOjBM=862534539.7768368;if (tXFFlOjBM == tXFFlOjBM ) tXFFlOjBM=914807591.7865462; else tXFFlOjBM=1776988980.0579499;if (tXFFlOjBM == tXFFlOjBM ) tXFFlOjBM=1825545211.6719642; else tXFFlOjBM=1526236479.5678325;if (tXFFlOjBM == tXFFlOjBM ) tXFFlOjBM=76524701.9491704; else tXFFlOjBM=1036852950.4055547;if (tXFFlOjBM == tXFFlOjBM ) tXFFlOjBM=890528436.9930191; else tXFFlOjBM=868122227.0697273;long ykGVmFAor=1031620880;if (ykGVmFAor == ykGVmFAor- 0 ) ykGVmFAor=109640615; else ykGVmFAor=973194826;if (ykGVmFAor == ykGVmFAor- 1 ) ykGVmFAor=1274302079; else ykGVmFAor=1877238778;if (ykGVmFAor == ykGVmFAor- 1 ) ykGVmFAor=913977085; else ykGVmFAor=1166601201;if (ykGVmFAor == ykGVmFAor- 0 ) ykGVmFAor=616824623; else ykGVmFAor=1656721980;if (ykGVmFAor == ykGVmFAor- 0 ) ykGVmFAor=1917481130; else ykGVmFAor=545658539;if (ykGVmFAor == ykGVmFAor- 0 ) ykGVmFAor=1624938442; else ykGVmFAor=965969774;long hkvYEvXdA=1606771878;if (hkvYEvXdA == hkvYEvXdA- 1 ) hkvYEvXdA=1315099324; else hkvYEvXdA=749673500;if (hkvYEvXdA == hkvYEvXdA- 0 ) hkvYEvXdA=1412016732; else hkvYEvXdA=1953944042;if (hkvYEvXdA == hkvYEvXdA- 1 ) hkvYEvXdA=1474666283; else hkvYEvXdA=1117576896;if (hkvYEvXdA == hkvYEvXdA- 1 ) hkvYEvXdA=984155457; else hkvYEvXdA=1606554842;if (hkvYEvXdA == hkvYEvXdA- 0 ) hkvYEvXdA=1823109850; else hkvYEvXdA=1391505086;if (hkvYEvXdA == hkvYEvXdA- 1 ) hkvYEvXdA=969772207; else hkvYEvXdA=1001540345;float PfdAUdAJV=763965171.7889935f;if (PfdAUdAJV - PfdAUdAJV> 0.00000001 ) PfdAUdAJV=1698108948.7818768f; else PfdAUdAJV=492207459.8568980f;if (PfdAUdAJV - PfdAUdAJV> 0.00000001 ) PfdAUdAJV=561774608.3918521f; else PfdAUdAJV=396459454.2135717f;if (PfdAUdAJV - PfdAUdAJV> 0.00000001 ) PfdAUdAJV=87339297.5439777f; else PfdAUdAJV=1927057773.6020470f;if (PfdAUdAJV - PfdAUdAJV> 0.00000001 ) PfdAUdAJV=378576127.0136165f; else PfdAUdAJV=1333243557.0814155f;if (PfdAUdAJV - PfdAUdAJV> 0.00000001 ) PfdAUdAJV=2063122049.7830514f; else PfdAUdAJV=1508277807.2303237f;if (PfdAUdAJV - PfdAUdAJV> 0.00000001 ) PfdAUdAJV=1092537056.9992613f; else PfdAUdAJV=369149052.1197635f;double LXdHKtLvy=683976278.1898931;if (LXdHKtLvy == LXdHKtLvy ) LXdHKtLvy=1891919471.6140707; else LXdHKtLvy=1431240205.5197745;if (LXdHKtLvy == LXdHKtLvy ) LXdHKtLvy=1700506550.1136316; else LXdHKtLvy=1117088288.2434175;if (LXdHKtLvy == LXdHKtLvy ) LXdHKtLvy=1876082612.5989159; else LXdHKtLvy=1868564711.5835848;if (LXdHKtLvy == LXdHKtLvy ) LXdHKtLvy=1704438244.5703641; else LXdHKtLvy=1139547366.8626254;if (LXdHKtLvy == LXdHKtLvy ) LXdHKtLvy=2136523016.8166421; else LXdHKtLvy=1815230884.2186066;if (LXdHKtLvy == LXdHKtLvy ) LXdHKtLvy=54128928.3026787; else LXdHKtLvy=1669955646.8316457; }
 LXdHKtLvyy::LXdHKtLvyy()
 { this->BLClBLYbfwsp("ggmqQTtOpBLClBLYbfwspj", true, 196828994, 1762767925, 1354374773); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class sbozSBBnRy
 { 
public: bool XvUbhFsJb; double XvUbhFsJbsbozSBBnR; sbozSBBnRy(); void IOREVJGHiICs(string XvUbhFsJbIOREVJGHiICs, bool zHkNXuwsv, int giNVDMQFB, float oiQiWjDeS, long tWSvNIwvV);
 protected: bool XvUbhFsJbo; double XvUbhFsJbsbozSBBnRf; void IOREVJGHiICsu(string XvUbhFsJbIOREVJGHiICsg, bool zHkNXuwsve, int giNVDMQFBr, float oiQiWjDeSw, long tWSvNIwvVn);
 private: bool XvUbhFsJbzHkNXuwsv; double XvUbhFsJboiQiWjDeSsbozSBBnR;
 void IOREVJGHiICsv(string zHkNXuwsvIOREVJGHiICs, bool zHkNXuwsvgiNVDMQFB, int giNVDMQFBXvUbhFsJb, float oiQiWjDeStWSvNIwvV, long tWSvNIwvVzHkNXuwsv); };
 void sbozSBBnRy::IOREVJGHiICs(string XvUbhFsJbIOREVJGHiICs, bool zHkNXuwsv, int giNVDMQFB, float oiQiWjDeS, long tWSvNIwvV)
 { float guDSXFAGt=1091081637.7343290f;if (guDSXFAGt - guDSXFAGt> 0.00000001 ) guDSXFAGt=1167310735.4734285f; else guDSXFAGt=582832574.6697564f;if (guDSXFAGt - guDSXFAGt> 0.00000001 ) guDSXFAGt=1769840884.0352951f; else guDSXFAGt=226488350.2833782f;if (guDSXFAGt - guDSXFAGt> 0.00000001 ) guDSXFAGt=604997363.0668503f; else guDSXFAGt=1520937198.2463190f;if (guDSXFAGt - guDSXFAGt> 0.00000001 ) guDSXFAGt=1136873498.1681697f; else guDSXFAGt=1205546418.1023402f;if (guDSXFAGt - guDSXFAGt> 0.00000001 ) guDSXFAGt=40649254.9116146f; else guDSXFAGt=601268656.0400628f;if (guDSXFAGt - guDSXFAGt> 0.00000001 ) guDSXFAGt=92930101.9909722f; else guDSXFAGt=1266936738.3532959f;float UZDCEPQck=1804022469.9342585f;if (UZDCEPQck - UZDCEPQck> 0.00000001 ) UZDCEPQck=2026359300.7805601f; else UZDCEPQck=1528053160.6963140f;if (UZDCEPQck - UZDCEPQck> 0.00000001 ) UZDCEPQck=1877176281.8846308f; else UZDCEPQck=2009112526.8600622f;if (UZDCEPQck - UZDCEPQck> 0.00000001 ) UZDCEPQck=1767542293.9418411f; else UZDCEPQck=734605670.8378412f;if (UZDCEPQck - UZDCEPQck> 0.00000001 ) UZDCEPQck=63936964.9219371f; else UZDCEPQck=379712115.5173879f;if (UZDCEPQck - UZDCEPQck> 0.00000001 ) UZDCEPQck=1039852630.3160997f; else UZDCEPQck=1404091904.6667300f;if (UZDCEPQck - UZDCEPQck> 0.00000001 ) UZDCEPQck=1960239480.6780079f; else UZDCEPQck=2995822.4924524f;int WahUKbIHp=1304634495;if (WahUKbIHp == WahUKbIHp- 0 ) WahUKbIHp=164999095; else WahUKbIHp=1100820525;if (WahUKbIHp == WahUKbIHp- 1 ) WahUKbIHp=1617972380; else WahUKbIHp=982062657;if (WahUKbIHp == WahUKbIHp- 1 ) WahUKbIHp=908930728; else WahUKbIHp=1446037226;if (WahUKbIHp == WahUKbIHp- 0 ) WahUKbIHp=1154583541; else WahUKbIHp=1599566427;if (WahUKbIHp == WahUKbIHp- 0 ) WahUKbIHp=1392076142; else WahUKbIHp=1347692823;if (WahUKbIHp == WahUKbIHp- 0 ) WahUKbIHp=261107067; else WahUKbIHp=1143497721;long fvtrBsYJw=2125983905;if (fvtrBsYJw == fvtrBsYJw- 0 ) fvtrBsYJw=1379046656; else fvtrBsYJw=1894206309;if (fvtrBsYJw == fvtrBsYJw- 0 ) fvtrBsYJw=1527178849; else fvtrBsYJw=963230513;if (fvtrBsYJw == fvtrBsYJw- 0 ) fvtrBsYJw=357222602; else fvtrBsYJw=1042689241;if (fvtrBsYJw == fvtrBsYJw- 1 ) fvtrBsYJw=1471022991; else fvtrBsYJw=432705065;if (fvtrBsYJw == fvtrBsYJw- 0 ) fvtrBsYJw=518895610; else fvtrBsYJw=1390128769;if (fvtrBsYJw == fvtrBsYJw- 0 ) fvtrBsYJw=1334119367; else fvtrBsYJw=1348389106;float oSVbGuVkg=105209462.2409394f;if (oSVbGuVkg - oSVbGuVkg> 0.00000001 ) oSVbGuVkg=237271363.7526622f; else oSVbGuVkg=935779253.6780106f;if (oSVbGuVkg - oSVbGuVkg> 0.00000001 ) oSVbGuVkg=1101937643.3762542f; else oSVbGuVkg=405281854.5730864f;if (oSVbGuVkg - oSVbGuVkg> 0.00000001 ) oSVbGuVkg=344473620.6963326f; else oSVbGuVkg=740300972.9042149f;if (oSVbGuVkg - oSVbGuVkg> 0.00000001 ) oSVbGuVkg=895091741.2830729f; else oSVbGuVkg=580322074.7488523f;if (oSVbGuVkg - oSVbGuVkg> 0.00000001 ) oSVbGuVkg=373469619.9078690f; else oSVbGuVkg=277609854.8279814f;if (oSVbGuVkg - oSVbGuVkg> 0.00000001 ) oSVbGuVkg=617036384.7315133f; else oSVbGuVkg=419849470.0012450f;int sbozSBBnR=317712387;if (sbozSBBnR == sbozSBBnR- 0 ) sbozSBBnR=1692698635; else sbozSBBnR=1981739222;if (sbozSBBnR == sbozSBBnR- 0 ) sbozSBBnR=771432813; else sbozSBBnR=87544035;if (sbozSBBnR == sbozSBBnR- 1 ) sbozSBBnR=555744590; else sbozSBBnR=1548250427;if (sbozSBBnR == sbozSBBnR- 0 ) sbozSBBnR=947411893; else sbozSBBnR=1269793501;if (sbozSBBnR == sbozSBBnR- 0 ) sbozSBBnR=1777281181; else sbozSBBnR=1185267315;if (sbozSBBnR == sbozSBBnR- 1 ) sbozSBBnR=463167047; else sbozSBBnR=1666285606; }
 sbozSBBnRy::sbozSBBnRy()
 { this->IOREVJGHiICs("XvUbhFsJbIOREVJGHiICsj", true, 111917859, 1953678082, 2038868709); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class bUyJchxpIy
 { 
public: bool IOEywuCyB; double IOEywuCyBbUyJchxpI; bUyJchxpIy(); void JLAqpGceKJUv(string IOEywuCyBJLAqpGceKJUv, bool ttRIyTmaV, int LyOnTDSXK, float BXvFHuKeW, long AxdEnQxPn);
 protected: bool IOEywuCyBo; double IOEywuCyBbUyJchxpIf; void JLAqpGceKJUvu(string IOEywuCyBJLAqpGceKJUvg, bool ttRIyTmaVe, int LyOnTDSXKr, float BXvFHuKeWw, long AxdEnQxPnn);
 private: bool IOEywuCyBttRIyTmaV; double IOEywuCyBBXvFHuKeWbUyJchxpI;
 void JLAqpGceKJUvv(string ttRIyTmaVJLAqpGceKJUv, bool ttRIyTmaVLyOnTDSXK, int LyOnTDSXKIOEywuCyB, float BXvFHuKeWAxdEnQxPn, long AxdEnQxPnttRIyTmaV); };
 void bUyJchxpIy::JLAqpGceKJUv(string IOEywuCyBJLAqpGceKJUv, bool ttRIyTmaV, int LyOnTDSXK, float BXvFHuKeW, long AxdEnQxPn)
 { float OzAinrjGE=1772552620.3406523f;if (OzAinrjGE - OzAinrjGE> 0.00000001 ) OzAinrjGE=817845431.5785232f; else OzAinrjGE=1190826791.7936498f;if (OzAinrjGE - OzAinrjGE> 0.00000001 ) OzAinrjGE=436887284.0799370f; else OzAinrjGE=325444885.5853934f;if (OzAinrjGE - OzAinrjGE> 0.00000001 ) OzAinrjGE=71160533.3287888f; else OzAinrjGE=1390731002.3917409f;if (OzAinrjGE - OzAinrjGE> 0.00000001 ) OzAinrjGE=119114319.8395384f; else OzAinrjGE=1393087400.8282641f;if (OzAinrjGE - OzAinrjGE> 0.00000001 ) OzAinrjGE=230689670.0324085f; else OzAinrjGE=1627461573.8507117f;if (OzAinrjGE - OzAinrjGE> 0.00000001 ) OzAinrjGE=795774296.8820717f; else OzAinrjGE=903280401.5796606f;int BaMVnTexR=1471844444;if (BaMVnTexR == BaMVnTexR- 0 ) BaMVnTexR=1423754582; else BaMVnTexR=509652057;if (BaMVnTexR == BaMVnTexR- 0 ) BaMVnTexR=1464050812; else BaMVnTexR=679192287;if (BaMVnTexR == BaMVnTexR- 1 ) BaMVnTexR=210719688; else BaMVnTexR=989167055;if (BaMVnTexR == BaMVnTexR- 0 ) BaMVnTexR=1153498596; else BaMVnTexR=2083045481;if (BaMVnTexR == BaMVnTexR- 1 ) BaMVnTexR=446733711; else BaMVnTexR=1290398103;if (BaMVnTexR == BaMVnTexR- 0 ) BaMVnTexR=596182532; else BaMVnTexR=537664224;int mjlhVnoix=2001092639;if (mjlhVnoix == mjlhVnoix- 1 ) mjlhVnoix=1698269985; else mjlhVnoix=1864965977;if (mjlhVnoix == mjlhVnoix- 0 ) mjlhVnoix=37946392; else mjlhVnoix=2022457047;if (mjlhVnoix == mjlhVnoix- 0 ) mjlhVnoix=1849376231; else mjlhVnoix=1777242585;if (mjlhVnoix == mjlhVnoix- 0 ) mjlhVnoix=2077119339; else mjlhVnoix=595675139;if (mjlhVnoix == mjlhVnoix- 0 ) mjlhVnoix=765863186; else mjlhVnoix=2131328851;if (mjlhVnoix == mjlhVnoix- 0 ) mjlhVnoix=1391939017; else mjlhVnoix=447274295;int NCOovNIkx=1074791880;if (NCOovNIkx == NCOovNIkx- 0 ) NCOovNIkx=832405094; else NCOovNIkx=301860459;if (NCOovNIkx == NCOovNIkx- 0 ) NCOovNIkx=98267856; else NCOovNIkx=1913107435;if (NCOovNIkx == NCOovNIkx- 1 ) NCOovNIkx=1595423616; else NCOovNIkx=1919022994;if (NCOovNIkx == NCOovNIkx- 0 ) NCOovNIkx=1561832932; else NCOovNIkx=1976162023;if (NCOovNIkx == NCOovNIkx- 1 ) NCOovNIkx=37328195; else NCOovNIkx=501325450;if (NCOovNIkx == NCOovNIkx- 1 ) NCOovNIkx=2026194821; else NCOovNIkx=928246077;double WZXQNGOki=1422605945.3984647;if (WZXQNGOki == WZXQNGOki ) WZXQNGOki=2022426155.8333993; else WZXQNGOki=942165304.7281954;if (WZXQNGOki == WZXQNGOki ) WZXQNGOki=1352494063.7000876; else WZXQNGOki=395491463.9831136;if (WZXQNGOki == WZXQNGOki ) WZXQNGOki=151774073.2503734; else WZXQNGOki=1452107299.1910199;if (WZXQNGOki == WZXQNGOki ) WZXQNGOki=1769951860.8981306; else WZXQNGOki=1793995644.0949819;if (WZXQNGOki == WZXQNGOki ) WZXQNGOki=580016365.5038686; else WZXQNGOki=868375673.7992306;if (WZXQNGOki == WZXQNGOki ) WZXQNGOki=2060812748.1017881; else WZXQNGOki=226874484.0609402;int bUyJchxpI=1355545081;if (bUyJchxpI == bUyJchxpI- 0 ) bUyJchxpI=1163894686; else bUyJchxpI=1668874299;if (bUyJchxpI == bUyJchxpI- 1 ) bUyJchxpI=1852742777; else bUyJchxpI=940702781;if (bUyJchxpI == bUyJchxpI- 0 ) bUyJchxpI=857299516; else bUyJchxpI=1986895277;if (bUyJchxpI == bUyJchxpI- 1 ) bUyJchxpI=405669023; else bUyJchxpI=1926730638;if (bUyJchxpI == bUyJchxpI- 0 ) bUyJchxpI=303133045; else bUyJchxpI=209268016;if (bUyJchxpI == bUyJchxpI- 1 ) bUyJchxpI=1985128852; else bUyJchxpI=1348050781; }
 bUyJchxpIy::bUyJchxpIy()
 { this->JLAqpGceKJUv("IOEywuCyBJLAqpGceKJUvj", true, 1898531411, 1148873262, 1948610316); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class DBpCXmsRmy
 { 
public: bool aMERkWpaL; double aMERkWpaLDBpCXmsRm; DBpCXmsRmy(); void IHWeTXZORswm(string aMERkWpaLIHWeTXZORswm, bool PRvuTYEOT, int DUCdahTFL, float liTzKeddj, long bRQNuRBqV);
 protected: bool aMERkWpaLo; double aMERkWpaLDBpCXmsRmf; void IHWeTXZORswmu(string aMERkWpaLIHWeTXZORswmg, bool PRvuTYEOTe, int DUCdahTFLr, float liTzKeddjw, long bRQNuRBqVn);
 private: bool aMERkWpaLPRvuTYEOT; double aMERkWpaLliTzKeddjDBpCXmsRm;
 void IHWeTXZORswmv(string PRvuTYEOTIHWeTXZORswm, bool PRvuTYEOTDUCdahTFL, int DUCdahTFLaMERkWpaL, float liTzKeddjbRQNuRBqV, long bRQNuRBqVPRvuTYEOT); };
 void DBpCXmsRmy::IHWeTXZORswm(string aMERkWpaLIHWeTXZORswm, bool PRvuTYEOT, int DUCdahTFL, float liTzKeddj, long bRQNuRBqV)
 { int QJqdbLAIr=194143281;if (QJqdbLAIr == QJqdbLAIr- 1 ) QJqdbLAIr=1404727298; else QJqdbLAIr=2025247251;if (QJqdbLAIr == QJqdbLAIr- 1 ) QJqdbLAIr=545077943; else QJqdbLAIr=1172573615;if (QJqdbLAIr == QJqdbLAIr- 0 ) QJqdbLAIr=823119322; else QJqdbLAIr=1356067190;if (QJqdbLAIr == QJqdbLAIr- 0 ) QJqdbLAIr=1588283428; else QJqdbLAIr=1334762584;if (QJqdbLAIr == QJqdbLAIr- 1 ) QJqdbLAIr=728952353; else QJqdbLAIr=1459015410;if (QJqdbLAIr == QJqdbLAIr- 1 ) QJqdbLAIr=457019405; else QJqdbLAIr=1500483521;long znIKnEXht=424787919;if (znIKnEXht == znIKnEXht- 1 ) znIKnEXht=1122090938; else znIKnEXht=575110800;if (znIKnEXht == znIKnEXht- 1 ) znIKnEXht=1904354387; else znIKnEXht=1555340640;if (znIKnEXht == znIKnEXht- 1 ) znIKnEXht=1223684242; else znIKnEXht=582266750;if (znIKnEXht == znIKnEXht- 0 ) znIKnEXht=273359223; else znIKnEXht=1864037739;if (znIKnEXht == znIKnEXht- 1 ) znIKnEXht=785298158; else znIKnEXht=33625268;if (znIKnEXht == znIKnEXht- 0 ) znIKnEXht=1851162670; else znIKnEXht=919349782;double oCcAkOixX=1342133864.7232705;if (oCcAkOixX == oCcAkOixX ) oCcAkOixX=892208401.6576946; else oCcAkOixX=732323767.2289557;if (oCcAkOixX == oCcAkOixX ) oCcAkOixX=1040017428.8269632; else oCcAkOixX=582702913.3849885;if (oCcAkOixX == oCcAkOixX ) oCcAkOixX=2050528919.4218187; else oCcAkOixX=467475120.0975977;if (oCcAkOixX == oCcAkOixX ) oCcAkOixX=285182217.0259219; else oCcAkOixX=2077975173.0831844;if (oCcAkOixX == oCcAkOixX ) oCcAkOixX=1431922065.7382629; else oCcAkOixX=454421447.1815709;if (oCcAkOixX == oCcAkOixX ) oCcAkOixX=434789480.3958763; else oCcAkOixX=1836464825.6906864;int skOVQNevP=384757266;if (skOVQNevP == skOVQNevP- 0 ) skOVQNevP=650014712; else skOVQNevP=1749467922;if (skOVQNevP == skOVQNevP- 1 ) skOVQNevP=1907349469; else skOVQNevP=1720999142;if (skOVQNevP == skOVQNevP- 1 ) skOVQNevP=2067911131; else skOVQNevP=1406747448;if (skOVQNevP == skOVQNevP- 0 ) skOVQNevP=1117942686; else skOVQNevP=822460548;if (skOVQNevP == skOVQNevP- 0 ) skOVQNevP=1751888028; else skOVQNevP=828523851;if (skOVQNevP == skOVQNevP- 0 ) skOVQNevP=387275457; else skOVQNevP=789494054;float BtiyzFhEv=778509612.2355692f;if (BtiyzFhEv - BtiyzFhEv> 0.00000001 ) BtiyzFhEv=1478179058.9530445f; else BtiyzFhEv=1262369188.9186333f;if (BtiyzFhEv - BtiyzFhEv> 0.00000001 ) BtiyzFhEv=608275120.9172358f; else BtiyzFhEv=968616020.2592357f;if (BtiyzFhEv - BtiyzFhEv> 0.00000001 ) BtiyzFhEv=1469461265.3744352f; else BtiyzFhEv=826390389.7319849f;if (BtiyzFhEv - BtiyzFhEv> 0.00000001 ) BtiyzFhEv=521742647.5895674f; else BtiyzFhEv=654615818.2934548f;if (BtiyzFhEv - BtiyzFhEv> 0.00000001 ) BtiyzFhEv=289928583.0481997f; else BtiyzFhEv=1973862861.5521822f;if (BtiyzFhEv - BtiyzFhEv> 0.00000001 ) BtiyzFhEv=123418575.9645107f; else BtiyzFhEv=769262795.7178932f;double DBpCXmsRm=1317015505.5063199;if (DBpCXmsRm == DBpCXmsRm ) DBpCXmsRm=2026421756.4244986; else DBpCXmsRm=1466405404.0196867;if (DBpCXmsRm == DBpCXmsRm ) DBpCXmsRm=269335070.3308230; else DBpCXmsRm=2000910116.5038701;if (DBpCXmsRm == DBpCXmsRm ) DBpCXmsRm=190576919.4819526; else DBpCXmsRm=407320857.3997996;if (DBpCXmsRm == DBpCXmsRm ) DBpCXmsRm=1421706380.5592412; else DBpCXmsRm=1632944600.8750609;if (DBpCXmsRm == DBpCXmsRm ) DBpCXmsRm=1761864728.3172956; else DBpCXmsRm=217556880.4873420;if (DBpCXmsRm == DBpCXmsRm ) DBpCXmsRm=978298532.4224551; else DBpCXmsRm=1222005068.5563007; }
 DBpCXmsRmy::DBpCXmsRmy()
 { this->IHWeTXZORswm("aMERkWpaLIHWeTXZORswmj", true, 80199663, 1643171810, 425587006); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class nnVQOJYEHy
 { 
public: bool AsvIcGLJh; double AsvIcGLJhnnVQOJYEH; nnVQOJYEHy(); void ojUaVEPiOlJM(string AsvIcGLJhojUaVEPiOlJM, bool PSzEBqtFI, int VtoqfZWwj, float YqJxxuzba, long OHkcTVqKv);
 protected: bool AsvIcGLJho; double AsvIcGLJhnnVQOJYEHf; void ojUaVEPiOlJMu(string AsvIcGLJhojUaVEPiOlJMg, bool PSzEBqtFIe, int VtoqfZWwjr, float YqJxxuzbaw, long OHkcTVqKvn);
 private: bool AsvIcGLJhPSzEBqtFI; double AsvIcGLJhYqJxxuzbannVQOJYEH;
 void ojUaVEPiOlJMv(string PSzEBqtFIojUaVEPiOlJM, bool PSzEBqtFIVtoqfZWwj, int VtoqfZWwjAsvIcGLJh, float YqJxxuzbaOHkcTVqKv, long OHkcTVqKvPSzEBqtFI); };
 void nnVQOJYEHy::ojUaVEPiOlJM(string AsvIcGLJhojUaVEPiOlJM, bool PSzEBqtFI, int VtoqfZWwj, float YqJxxuzba, long OHkcTVqKv)
 { int bwtjnzUZM=463549160;if (bwtjnzUZM == bwtjnzUZM- 1 ) bwtjnzUZM=1822803072; else bwtjnzUZM=1016442416;if (bwtjnzUZM == bwtjnzUZM- 1 ) bwtjnzUZM=906649592; else bwtjnzUZM=1573018086;if (bwtjnzUZM == bwtjnzUZM- 0 ) bwtjnzUZM=832708185; else bwtjnzUZM=1905652799;if (bwtjnzUZM == bwtjnzUZM- 1 ) bwtjnzUZM=403557040; else bwtjnzUZM=588517027;if (bwtjnzUZM == bwtjnzUZM- 0 ) bwtjnzUZM=2032191398; else bwtjnzUZM=985038348;if (bwtjnzUZM == bwtjnzUZM- 1 ) bwtjnzUZM=1621455124; else bwtjnzUZM=1575529771;float ayYYvngvb=1846758146.3079086f;if (ayYYvngvb - ayYYvngvb> 0.00000001 ) ayYYvngvb=1250126343.2351567f; else ayYYvngvb=1091854451.2745502f;if (ayYYvngvb - ayYYvngvb> 0.00000001 ) ayYYvngvb=1896513470.6789619f; else ayYYvngvb=1138971519.1555068f;if (ayYYvngvb - ayYYvngvb> 0.00000001 ) ayYYvngvb=1491176354.9088250f; else ayYYvngvb=904004533.9790757f;if (ayYYvngvb - ayYYvngvb> 0.00000001 ) ayYYvngvb=1737363374.9513708f; else ayYYvngvb=97124028.4904882f;if (ayYYvngvb - ayYYvngvb> 0.00000001 ) ayYYvngvb=1025891255.9066103f; else ayYYvngvb=136005708.7673638f;if (ayYYvngvb - ayYYvngvb> 0.00000001 ) ayYYvngvb=1506021910.0009723f; else ayYYvngvb=2010092693.0434716f;long qQYjqBkNU=44609441;if (qQYjqBkNU == qQYjqBkNU- 1 ) qQYjqBkNU=1138655845; else qQYjqBkNU=1994110147;if (qQYjqBkNU == qQYjqBkNU- 0 ) qQYjqBkNU=1897514866; else qQYjqBkNU=1357213012;if (qQYjqBkNU == qQYjqBkNU- 1 ) qQYjqBkNU=1371568692; else qQYjqBkNU=1358304470;if (qQYjqBkNU == qQYjqBkNU- 0 ) qQYjqBkNU=1730724862; else qQYjqBkNU=387513339;if (qQYjqBkNU == qQYjqBkNU- 0 ) qQYjqBkNU=175258810; else qQYjqBkNU=709094390;if (qQYjqBkNU == qQYjqBkNU- 0 ) qQYjqBkNU=1962364204; else qQYjqBkNU=1479671986;float GMXPAxtue=388103690.2677118f;if (GMXPAxtue - GMXPAxtue> 0.00000001 ) GMXPAxtue=1533394803.6470397f; else GMXPAxtue=480269498.0687462f;if (GMXPAxtue - GMXPAxtue> 0.00000001 ) GMXPAxtue=1358357496.0153192f; else GMXPAxtue=2074235723.7309267f;if (GMXPAxtue - GMXPAxtue> 0.00000001 ) GMXPAxtue=1419911092.6354772f; else GMXPAxtue=825424240.4459691f;if (GMXPAxtue - GMXPAxtue> 0.00000001 ) GMXPAxtue=1119856453.8306533f; else GMXPAxtue=918798539.6341379f;if (GMXPAxtue - GMXPAxtue> 0.00000001 ) GMXPAxtue=1426562689.2721314f; else GMXPAxtue=809525564.3448016f;if (GMXPAxtue - GMXPAxtue> 0.00000001 ) GMXPAxtue=547126831.8056010f; else GMXPAxtue=696702477.0138441f;int EPWxQKiSr=262682817;if (EPWxQKiSr == EPWxQKiSr- 0 ) EPWxQKiSr=364164143; else EPWxQKiSr=1576845683;if (EPWxQKiSr == EPWxQKiSr- 1 ) EPWxQKiSr=436873926; else EPWxQKiSr=1647546245;if (EPWxQKiSr == EPWxQKiSr- 1 ) EPWxQKiSr=792696914; else EPWxQKiSr=1351676149;if (EPWxQKiSr == EPWxQKiSr- 1 ) EPWxQKiSr=475189454; else EPWxQKiSr=2039305520;if (EPWxQKiSr == EPWxQKiSr- 0 ) EPWxQKiSr=1508613236; else EPWxQKiSr=1509000131;if (EPWxQKiSr == EPWxQKiSr- 0 ) EPWxQKiSr=963712709; else EPWxQKiSr=782081964;int nnVQOJYEH=388064801;if (nnVQOJYEH == nnVQOJYEH- 0 ) nnVQOJYEH=368082921; else nnVQOJYEH=1117918220;if (nnVQOJYEH == nnVQOJYEH- 1 ) nnVQOJYEH=476697890; else nnVQOJYEH=2019091015;if (nnVQOJYEH == nnVQOJYEH- 1 ) nnVQOJYEH=411151085; else nnVQOJYEH=694122129;if (nnVQOJYEH == nnVQOJYEH- 0 ) nnVQOJYEH=772181996; else nnVQOJYEH=313231605;if (nnVQOJYEH == nnVQOJYEH- 1 ) nnVQOJYEH=874253694; else nnVQOJYEH=978716327;if (nnVQOJYEH == nnVQOJYEH- 0 ) nnVQOJYEH=2078133970; else nnVQOJYEH=562043128; }
 nnVQOJYEHy::nnVQOJYEHy()
 { this->ojUaVEPiOlJM("AsvIcGLJhojUaVEPiOlJMj", true, 811177639, 1034022385, 2135366097); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class VSTSAgbhQy
 { 
public: bool ltSFFpmon; double ltSFFpmonVSTSAgbhQ; VSTSAgbhQy(); void gMYzQpqgWTlJ(string ltSFFpmongMYzQpqgWTlJ, bool SmoFuSjql, int BtYzjmYeb, float FoCJFSozy, long pXiCBcceT);
 protected: bool ltSFFpmono; double ltSFFpmonVSTSAgbhQf; void gMYzQpqgWTlJu(string ltSFFpmongMYzQpqgWTlJg, bool SmoFuSjqle, int BtYzjmYebr, float FoCJFSozyw, long pXiCBcceTn);
 private: bool ltSFFpmonSmoFuSjql; double ltSFFpmonFoCJFSozyVSTSAgbhQ;
 void gMYzQpqgWTlJv(string SmoFuSjqlgMYzQpqgWTlJ, bool SmoFuSjqlBtYzjmYeb, int BtYzjmYebltSFFpmon, float FoCJFSozypXiCBcceT, long pXiCBcceTSmoFuSjql); };
 void VSTSAgbhQy::gMYzQpqgWTlJ(string ltSFFpmongMYzQpqgWTlJ, bool SmoFuSjql, int BtYzjmYeb, float FoCJFSozy, long pXiCBcceT)
 { long CNbHeZull=1152111076;if (CNbHeZull == CNbHeZull- 0 ) CNbHeZull=299504549; else CNbHeZull=1443504631;if (CNbHeZull == CNbHeZull- 1 ) CNbHeZull=445157005; else CNbHeZull=1964997032;if (CNbHeZull == CNbHeZull- 1 ) CNbHeZull=1037357298; else CNbHeZull=71011064;if (CNbHeZull == CNbHeZull- 0 ) CNbHeZull=404706528; else CNbHeZull=1635887850;if (CNbHeZull == CNbHeZull- 0 ) CNbHeZull=2114122195; else CNbHeZull=164556996;if (CNbHeZull == CNbHeZull- 1 ) CNbHeZull=1072516292; else CNbHeZull=170922908;int LNQLCVfRq=1188098430;if (LNQLCVfRq == LNQLCVfRq- 1 ) LNQLCVfRq=1850563351; else LNQLCVfRq=1263244027;if (LNQLCVfRq == LNQLCVfRq- 0 ) LNQLCVfRq=1895869552; else LNQLCVfRq=978124358;if (LNQLCVfRq == LNQLCVfRq- 0 ) LNQLCVfRq=911352216; else LNQLCVfRq=1739324457;if (LNQLCVfRq == LNQLCVfRq- 1 ) LNQLCVfRq=688215226; else LNQLCVfRq=559678700;if (LNQLCVfRq == LNQLCVfRq- 1 ) LNQLCVfRq=1134786319; else LNQLCVfRq=1640078550;if (LNQLCVfRq == LNQLCVfRq- 0 ) LNQLCVfRq=1607228648; else LNQLCVfRq=14048786;double GlJqALXli=1894958803.4669385;if (GlJqALXli == GlJqALXli ) GlJqALXli=906621016.5899066; else GlJqALXli=731609667.1112006;if (GlJqALXli == GlJqALXli ) GlJqALXli=1345143152.8039449; else GlJqALXli=1442012560.8138687;if (GlJqALXli == GlJqALXli ) GlJqALXli=964186455.3607372; else GlJqALXli=764812832.2727204;if (GlJqALXli == GlJqALXli ) GlJqALXli=173860820.3942236; else GlJqALXli=411976763.6309578;if (GlJqALXli == GlJqALXli ) GlJqALXli=234012967.7625999; else GlJqALXli=398007736.5167456;if (GlJqALXli == GlJqALXli ) GlJqALXli=286073760.4233455; else GlJqALXli=1862290635.2975618;int xmryVaCCK=452664106;if (xmryVaCCK == xmryVaCCK- 1 ) xmryVaCCK=478135112; else xmryVaCCK=502912107;if (xmryVaCCK == xmryVaCCK- 1 ) xmryVaCCK=748621970; else xmryVaCCK=1417045571;if (xmryVaCCK == xmryVaCCK- 0 ) xmryVaCCK=1449515723; else xmryVaCCK=688886883;if (xmryVaCCK == xmryVaCCK- 1 ) xmryVaCCK=240758860; else xmryVaCCK=707663739;if (xmryVaCCK == xmryVaCCK- 0 ) xmryVaCCK=755289405; else xmryVaCCK=2032961952;if (xmryVaCCK == xmryVaCCK- 1 ) xmryVaCCK=830210713; else xmryVaCCK=1544762395;int tAiimOiMl=1865937132;if (tAiimOiMl == tAiimOiMl- 1 ) tAiimOiMl=695480628; else tAiimOiMl=1325041136;if (tAiimOiMl == tAiimOiMl- 1 ) tAiimOiMl=1411785539; else tAiimOiMl=830487857;if (tAiimOiMl == tAiimOiMl- 1 ) tAiimOiMl=879683666; else tAiimOiMl=1192600292;if (tAiimOiMl == tAiimOiMl- 0 ) tAiimOiMl=223911975; else tAiimOiMl=1085750519;if (tAiimOiMl == tAiimOiMl- 0 ) tAiimOiMl=1089383207; else tAiimOiMl=1483892789;if (tAiimOiMl == tAiimOiMl- 1 ) tAiimOiMl=744111391; else tAiimOiMl=513344480;double VSTSAgbhQ=300523873.7763708;if (VSTSAgbhQ == VSTSAgbhQ ) VSTSAgbhQ=1216010316.2754049; else VSTSAgbhQ=1154564542.4109052;if (VSTSAgbhQ == VSTSAgbhQ ) VSTSAgbhQ=1683397321.4941253; else VSTSAgbhQ=672732787.4505382;if (VSTSAgbhQ == VSTSAgbhQ ) VSTSAgbhQ=1647046740.9284695; else VSTSAgbhQ=199514444.8206655;if (VSTSAgbhQ == VSTSAgbhQ ) VSTSAgbhQ=445443080.8765313; else VSTSAgbhQ=217734133.9236658;if (VSTSAgbhQ == VSTSAgbhQ ) VSTSAgbhQ=490850807.2607686; else VSTSAgbhQ=637479413.0354777;if (VSTSAgbhQ == VSTSAgbhQ ) VSTSAgbhQ=686723155.7566197; else VSTSAgbhQ=1078708150.9400890; }
 VSTSAgbhQy::VSTSAgbhQy()
 { this->gMYzQpqgWTlJ("ltSFFpmongMYzQpqgWTlJj", true, 2082085766, 776582072, 1948194347); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class BoAjqfCGuy
 { 
public: bool PCKCZmpmp; double PCKCZmpmpBoAjqfCGu; BoAjqfCGuy(); void IyKRJgPUMXBy(string PCKCZmpmpIyKRJgPUMXBy, bool EYsqqRhzn, int mhpNEZSeL, float mMaWnkrmP, long JbEalbrLl);
 protected: bool PCKCZmpmpo; double PCKCZmpmpBoAjqfCGuf; void IyKRJgPUMXByu(string PCKCZmpmpIyKRJgPUMXByg, bool EYsqqRhzne, int mhpNEZSeLr, float mMaWnkrmPw, long JbEalbrLln);
 private: bool PCKCZmpmpEYsqqRhzn; double PCKCZmpmpmMaWnkrmPBoAjqfCGu;
 void IyKRJgPUMXByv(string EYsqqRhznIyKRJgPUMXBy, bool EYsqqRhznmhpNEZSeL, int mhpNEZSeLPCKCZmpmp, float mMaWnkrmPJbEalbrLl, long JbEalbrLlEYsqqRhzn); };
 void BoAjqfCGuy::IyKRJgPUMXBy(string PCKCZmpmpIyKRJgPUMXBy, bool EYsqqRhzn, int mhpNEZSeL, float mMaWnkrmP, long JbEalbrLl)
 { long mBWEGqTPh=950657456;if (mBWEGqTPh == mBWEGqTPh- 0 ) mBWEGqTPh=1542017723; else mBWEGqTPh=1883200744;if (mBWEGqTPh == mBWEGqTPh- 0 ) mBWEGqTPh=1809439004; else mBWEGqTPh=184095756;if (mBWEGqTPh == mBWEGqTPh- 1 ) mBWEGqTPh=1827187161; else mBWEGqTPh=1821105532;if (mBWEGqTPh == mBWEGqTPh- 0 ) mBWEGqTPh=1815999997; else mBWEGqTPh=1621656872;if (mBWEGqTPh == mBWEGqTPh- 1 ) mBWEGqTPh=679611881; else mBWEGqTPh=452046421;if (mBWEGqTPh == mBWEGqTPh- 1 ) mBWEGqTPh=1825904748; else mBWEGqTPh=769807633;double eouRXFRZP=729999770.9929814;if (eouRXFRZP == eouRXFRZP ) eouRXFRZP=1720721521.8222974; else eouRXFRZP=398571378.4288776;if (eouRXFRZP == eouRXFRZP ) eouRXFRZP=1916816561.0190793; else eouRXFRZP=1583843077.1198833;if (eouRXFRZP == eouRXFRZP ) eouRXFRZP=2084546622.0871481; else eouRXFRZP=1967907157.1892856;if (eouRXFRZP == eouRXFRZP ) eouRXFRZP=689544727.0403740; else eouRXFRZP=1268187580.8491227;if (eouRXFRZP == eouRXFRZP ) eouRXFRZP=848587284.2342425; else eouRXFRZP=906777573.4274069;if (eouRXFRZP == eouRXFRZP ) eouRXFRZP=899994233.3199472; else eouRXFRZP=1642546307.7962042;int mAHdVvcXw=304027638;if (mAHdVvcXw == mAHdVvcXw- 1 ) mAHdVvcXw=1386623015; else mAHdVvcXw=486183195;if (mAHdVvcXw == mAHdVvcXw- 1 ) mAHdVvcXw=858131276; else mAHdVvcXw=1605164060;if (mAHdVvcXw == mAHdVvcXw- 1 ) mAHdVvcXw=1371538188; else mAHdVvcXw=13325524;if (mAHdVvcXw == mAHdVvcXw- 1 ) mAHdVvcXw=347194952; else mAHdVvcXw=1286248737;if (mAHdVvcXw == mAHdVvcXw- 0 ) mAHdVvcXw=2091535713; else mAHdVvcXw=537125938;if (mAHdVvcXw == mAHdVvcXw- 1 ) mAHdVvcXw=1883089708; else mAHdVvcXw=168176454;float nmFmozwEp=700866498.8042933f;if (nmFmozwEp - nmFmozwEp> 0.00000001 ) nmFmozwEp=49407016.3223905f; else nmFmozwEp=106110577.8151111f;if (nmFmozwEp - nmFmozwEp> 0.00000001 ) nmFmozwEp=2104139432.2766939f; else nmFmozwEp=2023542514.0955793f;if (nmFmozwEp - nmFmozwEp> 0.00000001 ) nmFmozwEp=1364450787.1500782f; else nmFmozwEp=1886707093.6162395f;if (nmFmozwEp - nmFmozwEp> 0.00000001 ) nmFmozwEp=1013594481.0191596f; else nmFmozwEp=1721594213.3961143f;if (nmFmozwEp - nmFmozwEp> 0.00000001 ) nmFmozwEp=1193656017.4893138f; else nmFmozwEp=541251424.7524397f;if (nmFmozwEp - nmFmozwEp> 0.00000001 ) nmFmozwEp=1482992119.7046451f; else nmFmozwEp=920409588.9642078f;float VsiVvKNly=1236500175.3542325f;if (VsiVvKNly - VsiVvKNly> 0.00000001 ) VsiVvKNly=1067824019.3693025f; else VsiVvKNly=1521877110.3391289f;if (VsiVvKNly - VsiVvKNly> 0.00000001 ) VsiVvKNly=1530668265.3907538f; else VsiVvKNly=1967914571.3153816f;if (VsiVvKNly - VsiVvKNly> 0.00000001 ) VsiVvKNly=1110440080.9657949f; else VsiVvKNly=1127923273.2421425f;if (VsiVvKNly - VsiVvKNly> 0.00000001 ) VsiVvKNly=1505945229.9590390f; else VsiVvKNly=1707395997.6459971f;if (VsiVvKNly - VsiVvKNly> 0.00000001 ) VsiVvKNly=51376426.6402104f; else VsiVvKNly=630567824.7443512f;if (VsiVvKNly - VsiVvKNly> 0.00000001 ) VsiVvKNly=1639791011.5961144f; else VsiVvKNly=1547420684.6636374f;float BoAjqfCGu=589728612.8706163f;if (BoAjqfCGu - BoAjqfCGu> 0.00000001 ) BoAjqfCGu=992801645.7820115f; else BoAjqfCGu=199127735.5730359f;if (BoAjqfCGu - BoAjqfCGu> 0.00000001 ) BoAjqfCGu=1593139291.8271519f; else BoAjqfCGu=1675208063.2454845f;if (BoAjqfCGu - BoAjqfCGu> 0.00000001 ) BoAjqfCGu=1633939568.9217166f; else BoAjqfCGu=1655647182.1102382f;if (BoAjqfCGu - BoAjqfCGu> 0.00000001 ) BoAjqfCGu=1087060498.7242720f; else BoAjqfCGu=1647399569.5357556f;if (BoAjqfCGu - BoAjqfCGu> 0.00000001 ) BoAjqfCGu=1620072361.4764817f; else BoAjqfCGu=1284020710.5333938f;if (BoAjqfCGu - BoAjqfCGu> 0.00000001 ) BoAjqfCGu=411508043.2702485f; else BoAjqfCGu=830286764.2232354f; }
 BoAjqfCGuy::BoAjqfCGuy()
 { this->IyKRJgPUMXBy("PCKCZmpmpIyKRJgPUMXByj", true, 677817052, 1574269011, 365137438); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class iwOxAMWSYy
 { 
public: bool NKiInMutR; double NKiInMutRiwOxAMWSY; iwOxAMWSYy(); void KwLGiYRZfWdi(string NKiInMutRKwLGiYRZfWdi, bool yMXzDrSnF, int ttmjbasJa, float YmDBibkiu, long mPVqWybzW);
 protected: bool NKiInMutRo; double NKiInMutRiwOxAMWSYf; void KwLGiYRZfWdiu(string NKiInMutRKwLGiYRZfWdig, bool yMXzDrSnFe, int ttmjbasJar, float YmDBibkiuw, long mPVqWybzWn);
 private: bool NKiInMutRyMXzDrSnF; double NKiInMutRYmDBibkiuiwOxAMWSY;
 void KwLGiYRZfWdiv(string yMXzDrSnFKwLGiYRZfWdi, bool yMXzDrSnFttmjbasJa, int ttmjbasJaNKiInMutR, float YmDBibkiumPVqWybzW, long mPVqWybzWyMXzDrSnF); };
 void iwOxAMWSYy::KwLGiYRZfWdi(string NKiInMutRKwLGiYRZfWdi, bool yMXzDrSnF, int ttmjbasJa, float YmDBibkiu, long mPVqWybzW)
 { int smcRaJuRq=135685112;if (smcRaJuRq == smcRaJuRq- 0 ) smcRaJuRq=499617855; else smcRaJuRq=1145793906;if (smcRaJuRq == smcRaJuRq- 0 ) smcRaJuRq=1937560957; else smcRaJuRq=1218748434;if (smcRaJuRq == smcRaJuRq- 0 ) smcRaJuRq=1802788933; else smcRaJuRq=1706118979;if (smcRaJuRq == smcRaJuRq- 1 ) smcRaJuRq=176652432; else smcRaJuRq=659408377;if (smcRaJuRq == smcRaJuRq- 1 ) smcRaJuRq=1071273533; else smcRaJuRq=1674338939;if (smcRaJuRq == smcRaJuRq- 1 ) smcRaJuRq=1646789537; else smcRaJuRq=258796027;long XWGXDRJFI=1567950718;if (XWGXDRJFI == XWGXDRJFI- 0 ) XWGXDRJFI=44194337; else XWGXDRJFI=204370834;if (XWGXDRJFI == XWGXDRJFI- 0 ) XWGXDRJFI=216511504; else XWGXDRJFI=1561347986;if (XWGXDRJFI == XWGXDRJFI- 0 ) XWGXDRJFI=1960282857; else XWGXDRJFI=344765308;if (XWGXDRJFI == XWGXDRJFI- 1 ) XWGXDRJFI=1066646260; else XWGXDRJFI=1362441910;if (XWGXDRJFI == XWGXDRJFI- 0 ) XWGXDRJFI=1109901230; else XWGXDRJFI=1803733531;if (XWGXDRJFI == XWGXDRJFI- 0 ) XWGXDRJFI=504441591; else XWGXDRJFI=1160648564;long mrtQsjUtN=1570633682;if (mrtQsjUtN == mrtQsjUtN- 0 ) mrtQsjUtN=1059803567; else mrtQsjUtN=492971179;if (mrtQsjUtN == mrtQsjUtN- 0 ) mrtQsjUtN=174147303; else mrtQsjUtN=1665582781;if (mrtQsjUtN == mrtQsjUtN- 0 ) mrtQsjUtN=566835924; else mrtQsjUtN=1217458546;if (mrtQsjUtN == mrtQsjUtN- 0 ) mrtQsjUtN=1216870063; else mrtQsjUtN=200738472;if (mrtQsjUtN == mrtQsjUtN- 0 ) mrtQsjUtN=881163612; else mrtQsjUtN=286399257;if (mrtQsjUtN == mrtQsjUtN- 0 ) mrtQsjUtN=1178897080; else mrtQsjUtN=1414345973;long iJUDkfdkA=104326084;if (iJUDkfdkA == iJUDkfdkA- 1 ) iJUDkfdkA=621972477; else iJUDkfdkA=1783138574;if (iJUDkfdkA == iJUDkfdkA- 1 ) iJUDkfdkA=1400126082; else iJUDkfdkA=492412412;if (iJUDkfdkA == iJUDkfdkA- 0 ) iJUDkfdkA=1455603489; else iJUDkfdkA=677206901;if (iJUDkfdkA == iJUDkfdkA- 0 ) iJUDkfdkA=322885902; else iJUDkfdkA=154852547;if (iJUDkfdkA == iJUDkfdkA- 1 ) iJUDkfdkA=79147646; else iJUDkfdkA=575119047;if (iJUDkfdkA == iJUDkfdkA- 1 ) iJUDkfdkA=108847204; else iJUDkfdkA=2146539049;float DbkZuZdNC=291886634.5762688f;if (DbkZuZdNC - DbkZuZdNC> 0.00000001 ) DbkZuZdNC=1060824741.0431911f; else DbkZuZdNC=76155855.9270146f;if (DbkZuZdNC - DbkZuZdNC> 0.00000001 ) DbkZuZdNC=1346476107.8247788f; else DbkZuZdNC=636521321.3211756f;if (DbkZuZdNC - DbkZuZdNC> 0.00000001 ) DbkZuZdNC=1087888104.4029398f; else DbkZuZdNC=812048656.5847897f;if (DbkZuZdNC - DbkZuZdNC> 0.00000001 ) DbkZuZdNC=1001114794.9791477f; else DbkZuZdNC=974219438.5359008f;if (DbkZuZdNC - DbkZuZdNC> 0.00000001 ) DbkZuZdNC=1134984418.3303665f; else DbkZuZdNC=15773032.2628584f;if (DbkZuZdNC - DbkZuZdNC> 0.00000001 ) DbkZuZdNC=680184374.5119015f; else DbkZuZdNC=1673883600.5214990f;float iwOxAMWSY=1348838343.2468523f;if (iwOxAMWSY - iwOxAMWSY> 0.00000001 ) iwOxAMWSY=1564333112.0603407f; else iwOxAMWSY=400115507.5815826f;if (iwOxAMWSY - iwOxAMWSY> 0.00000001 ) iwOxAMWSY=538676087.1733416f; else iwOxAMWSY=697697137.7203136f;if (iwOxAMWSY - iwOxAMWSY> 0.00000001 ) iwOxAMWSY=1526744464.0911931f; else iwOxAMWSY=121101786.9379211f;if (iwOxAMWSY - iwOxAMWSY> 0.00000001 ) iwOxAMWSY=115030193.7527521f; else iwOxAMWSY=382596666.7451173f;if (iwOxAMWSY - iwOxAMWSY> 0.00000001 ) iwOxAMWSY=170085277.4014715f; else iwOxAMWSY=19294756.9050953f;if (iwOxAMWSY - iwOxAMWSY> 0.00000001 ) iwOxAMWSY=1586435135.4752161f; else iwOxAMWSY=2139200524.8877264f; }
 iwOxAMWSYy::iwOxAMWSYy()
 { this->KwLGiYRZfWdi("NKiInMutRKwLGiYRZfWdij", true, 1108611342, 1217814661, 1146544731); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class YoybGSjkxy
 { 
public: bool oIZJLlaQe; double oIZJLlaQeYoybGSjkx; YoybGSjkxy(); void AhNpvUgMRWvs(string oIZJLlaQeAhNpvUgMRWvs, bool YfYGklLyC, int XgYsQvcfC, float VHbqIkyAs, long AtVCsDaXc);
 protected: bool oIZJLlaQeo; double oIZJLlaQeYoybGSjkxf; void AhNpvUgMRWvsu(string oIZJLlaQeAhNpvUgMRWvsg, bool YfYGklLyCe, int XgYsQvcfCr, float VHbqIkyAsw, long AtVCsDaXcn);
 private: bool oIZJLlaQeYfYGklLyC; double oIZJLlaQeVHbqIkyAsYoybGSjkx;
 void AhNpvUgMRWvsv(string YfYGklLyCAhNpvUgMRWvs, bool YfYGklLyCXgYsQvcfC, int XgYsQvcfCoIZJLlaQe, float VHbqIkyAsAtVCsDaXc, long AtVCsDaXcYfYGklLyC); };
 void YoybGSjkxy::AhNpvUgMRWvs(string oIZJLlaQeAhNpvUgMRWvs, bool YfYGklLyC, int XgYsQvcfC, float VHbqIkyAs, long AtVCsDaXc)
 { int IBeeAaVUu=1594774956;if (IBeeAaVUu == IBeeAaVUu- 0 ) IBeeAaVUu=468171672; else IBeeAaVUu=1967580480;if (IBeeAaVUu == IBeeAaVUu- 0 ) IBeeAaVUu=219977030; else IBeeAaVUu=2091273739;if (IBeeAaVUu == IBeeAaVUu- 0 ) IBeeAaVUu=1969566972; else IBeeAaVUu=234202611;if (IBeeAaVUu == IBeeAaVUu- 0 ) IBeeAaVUu=235677560; else IBeeAaVUu=1662685362;if (IBeeAaVUu == IBeeAaVUu- 0 ) IBeeAaVUu=938493676; else IBeeAaVUu=397921999;if (IBeeAaVUu == IBeeAaVUu- 1 ) IBeeAaVUu=5707358; else IBeeAaVUu=999991202;float gJVeIBLJs=320333121.3242995f;if (gJVeIBLJs - gJVeIBLJs> 0.00000001 ) gJVeIBLJs=472809531.1593730f; else gJVeIBLJs=1305891802.6018554f;if (gJVeIBLJs - gJVeIBLJs> 0.00000001 ) gJVeIBLJs=635224132.3459153f; else gJVeIBLJs=1670930459.4844156f;if (gJVeIBLJs - gJVeIBLJs> 0.00000001 ) gJVeIBLJs=1220228867.3643909f; else gJVeIBLJs=544602227.8621346f;if (gJVeIBLJs - gJVeIBLJs> 0.00000001 ) gJVeIBLJs=1283512873.4647701f; else gJVeIBLJs=897479960.9038428f;if (gJVeIBLJs - gJVeIBLJs> 0.00000001 ) gJVeIBLJs=1843559776.7506954f; else gJVeIBLJs=636850844.5757655f;if (gJVeIBLJs - gJVeIBLJs> 0.00000001 ) gJVeIBLJs=420379235.8398280f; else gJVeIBLJs=65276341.3184554f;int GXZlHFHNW=57988140;if (GXZlHFHNW == GXZlHFHNW- 0 ) GXZlHFHNW=1689188802; else GXZlHFHNW=490738608;if (GXZlHFHNW == GXZlHFHNW- 0 ) GXZlHFHNW=1110858501; else GXZlHFHNW=147476683;if (GXZlHFHNW == GXZlHFHNW- 1 ) GXZlHFHNW=2100738289; else GXZlHFHNW=65686751;if (GXZlHFHNW == GXZlHFHNW- 1 ) GXZlHFHNW=1989702061; else GXZlHFHNW=833229976;if (GXZlHFHNW == GXZlHFHNW- 0 ) GXZlHFHNW=1895937549; else GXZlHFHNW=306770644;if (GXZlHFHNW == GXZlHFHNW- 0 ) GXZlHFHNW=1243408449; else GXZlHFHNW=585302039;int biAfzurIH=1378133141;if (biAfzurIH == biAfzurIH- 1 ) biAfzurIH=1960534147; else biAfzurIH=1502706545;if (biAfzurIH == biAfzurIH- 1 ) biAfzurIH=1243954707; else biAfzurIH=1184100671;if (biAfzurIH == biAfzurIH- 1 ) biAfzurIH=2042760591; else biAfzurIH=978057439;if (biAfzurIH == biAfzurIH- 0 ) biAfzurIH=374546089; else biAfzurIH=2071053092;if (biAfzurIH == biAfzurIH- 1 ) biAfzurIH=684067607; else biAfzurIH=1469980717;if (biAfzurIH == biAfzurIH- 1 ) biAfzurIH=247713963; else biAfzurIH=1332716128;int ZKHNtnegb=1880481569;if (ZKHNtnegb == ZKHNtnegb- 1 ) ZKHNtnegb=475550738; else ZKHNtnegb=2095202865;if (ZKHNtnegb == ZKHNtnegb- 1 ) ZKHNtnegb=1458286047; else ZKHNtnegb=1402644423;if (ZKHNtnegb == ZKHNtnegb- 0 ) ZKHNtnegb=114321987; else ZKHNtnegb=91932920;if (ZKHNtnegb == ZKHNtnegb- 0 ) ZKHNtnegb=367078479; else ZKHNtnegb=407122780;if (ZKHNtnegb == ZKHNtnegb- 0 ) ZKHNtnegb=1463673388; else ZKHNtnegb=1949477803;if (ZKHNtnegb == ZKHNtnegb- 1 ) ZKHNtnegb=1922476557; else ZKHNtnegb=913458223;double YoybGSjkx=933563096.6777121;if (YoybGSjkx == YoybGSjkx ) YoybGSjkx=1350512553.7582893; else YoybGSjkx=1189729741.1758449;if (YoybGSjkx == YoybGSjkx ) YoybGSjkx=252225841.4608732; else YoybGSjkx=1556554599.2046115;if (YoybGSjkx == YoybGSjkx ) YoybGSjkx=2109024694.3848058; else YoybGSjkx=885754237.2356083;if (YoybGSjkx == YoybGSjkx ) YoybGSjkx=162711196.0961602; else YoybGSjkx=711131363.1795005;if (YoybGSjkx == YoybGSjkx ) YoybGSjkx=116192519.6477989; else YoybGSjkx=1187289056.9115013;if (YoybGSjkx == YoybGSjkx ) YoybGSjkx=1610892723.4537693; else YoybGSjkx=630757572.1966132; }
 YoybGSjkxy::YoybGSjkxy()
 { this->AhNpvUgMRWvs("oIZJLlaQeAhNpvUgMRWvsj", true, 1965456435, 656985933, 1019406600); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class OUTlMjMfAy
 { 
public: bool aAnJgOMNJ; double aAnJgOMNJOUTlMjMfA; OUTlMjMfAy(); void yKleOlxrrpot(string aAnJgOMNJyKleOlxrrpot, bool prPKiHxxO, int nIGlGTnPB, float RJpBqKUbc, long NPDutrTIl);
 protected: bool aAnJgOMNJo; double aAnJgOMNJOUTlMjMfAf; void yKleOlxrrpotu(string aAnJgOMNJyKleOlxrrpotg, bool prPKiHxxOe, int nIGlGTnPBr, float RJpBqKUbcw, long NPDutrTIln);
 private: bool aAnJgOMNJprPKiHxxO; double aAnJgOMNJRJpBqKUbcOUTlMjMfA;
 void yKleOlxrrpotv(string prPKiHxxOyKleOlxrrpot, bool prPKiHxxOnIGlGTnPB, int nIGlGTnPBaAnJgOMNJ, float RJpBqKUbcNPDutrTIl, long NPDutrTIlprPKiHxxO); };
 void OUTlMjMfAy::yKleOlxrrpot(string aAnJgOMNJyKleOlxrrpot, bool prPKiHxxO, int nIGlGTnPB, float RJpBqKUbc, long NPDutrTIl)
 { double ucTevYIOn=135853225.2848406;if (ucTevYIOn == ucTevYIOn ) ucTevYIOn=1092356796.1541840; else ucTevYIOn=247159054.0439900;if (ucTevYIOn == ucTevYIOn ) ucTevYIOn=1905968090.3831070; else ucTevYIOn=335769038.0341000;if (ucTevYIOn == ucTevYIOn ) ucTevYIOn=26732438.8850071; else ucTevYIOn=547044523.1334210;if (ucTevYIOn == ucTevYIOn ) ucTevYIOn=236827048.3793899; else ucTevYIOn=562572538.0185371;if (ucTevYIOn == ucTevYIOn ) ucTevYIOn=1020424471.3009403; else ucTevYIOn=1724924294.7899303;if (ucTevYIOn == ucTevYIOn ) ucTevYIOn=1604252173.6178708; else ucTevYIOn=1742867984.6682129;long hemzyoONX=1809157044;if (hemzyoONX == hemzyoONX- 1 ) hemzyoONX=1073246539; else hemzyoONX=1477281378;if (hemzyoONX == hemzyoONX- 1 ) hemzyoONX=634580204; else hemzyoONX=1510083298;if (hemzyoONX == hemzyoONX- 1 ) hemzyoONX=640404729; else hemzyoONX=1379922151;if (hemzyoONX == hemzyoONX- 0 ) hemzyoONX=234364719; else hemzyoONX=1360034632;if (hemzyoONX == hemzyoONX- 0 ) hemzyoONX=1952454840; else hemzyoONX=2140923674;if (hemzyoONX == hemzyoONX- 0 ) hemzyoONX=521585973; else hemzyoONX=216716081;double JNtcBXLvu=1908337502.9980992;if (JNtcBXLvu == JNtcBXLvu ) JNtcBXLvu=1457153973.0254753; else JNtcBXLvu=1375721775.6994035;if (JNtcBXLvu == JNtcBXLvu ) JNtcBXLvu=558486787.7593644; else JNtcBXLvu=232276225.6498413;if (JNtcBXLvu == JNtcBXLvu ) JNtcBXLvu=1693356052.5836418; else JNtcBXLvu=1619678760.7438550;if (JNtcBXLvu == JNtcBXLvu ) JNtcBXLvu=432838019.1186282; else JNtcBXLvu=857693410.4074694;if (JNtcBXLvu == JNtcBXLvu ) JNtcBXLvu=1954691706.9664512; else JNtcBXLvu=2143167637.1787370;if (JNtcBXLvu == JNtcBXLvu ) JNtcBXLvu=1714601654.1761046; else JNtcBXLvu=967920688.3122412;float fKrMRrqgU=1442693557.8462081f;if (fKrMRrqgU - fKrMRrqgU> 0.00000001 ) fKrMRrqgU=905274456.1303204f; else fKrMRrqgU=1525349162.7520913f;if (fKrMRrqgU - fKrMRrqgU> 0.00000001 ) fKrMRrqgU=634219181.7676399f; else fKrMRrqgU=526910519.9902089f;if (fKrMRrqgU - fKrMRrqgU> 0.00000001 ) fKrMRrqgU=2072365232.6613697f; else fKrMRrqgU=841520084.4671928f;if (fKrMRrqgU - fKrMRrqgU> 0.00000001 ) fKrMRrqgU=1642932143.0132561f; else fKrMRrqgU=1859918292.8068932f;if (fKrMRrqgU - fKrMRrqgU> 0.00000001 ) fKrMRrqgU=12794335.4123351f; else fKrMRrqgU=545933458.0284363f;if (fKrMRrqgU - fKrMRrqgU> 0.00000001 ) fKrMRrqgU=530797845.1064720f; else fKrMRrqgU=33292411.9815289f;long YYgeZzaYq=1336252235;if (YYgeZzaYq == YYgeZzaYq- 1 ) YYgeZzaYq=806867223; else YYgeZzaYq=1843398318;if (YYgeZzaYq == YYgeZzaYq- 0 ) YYgeZzaYq=285714011; else YYgeZzaYq=585586035;if (YYgeZzaYq == YYgeZzaYq- 0 ) YYgeZzaYq=201308739; else YYgeZzaYq=2080340716;if (YYgeZzaYq == YYgeZzaYq- 0 ) YYgeZzaYq=115800992; else YYgeZzaYq=1601051426;if (YYgeZzaYq == YYgeZzaYq- 1 ) YYgeZzaYq=1044443359; else YYgeZzaYq=1924370441;if (YYgeZzaYq == YYgeZzaYq- 1 ) YYgeZzaYq=1702875239; else YYgeZzaYq=644720739;double OUTlMjMfA=846022166.4543014;if (OUTlMjMfA == OUTlMjMfA ) OUTlMjMfA=50956277.8129267; else OUTlMjMfA=1226376063.7393440;if (OUTlMjMfA == OUTlMjMfA ) OUTlMjMfA=1458925272.7814801; else OUTlMjMfA=210196363.1046879;if (OUTlMjMfA == OUTlMjMfA ) OUTlMjMfA=1197436702.9870804; else OUTlMjMfA=391146552.7946071;if (OUTlMjMfA == OUTlMjMfA ) OUTlMjMfA=1983455917.8066508; else OUTlMjMfA=615633889.7302247;if (OUTlMjMfA == OUTlMjMfA ) OUTlMjMfA=1880273279.1834088; else OUTlMjMfA=846052142.6346460;if (OUTlMjMfA == OUTlMjMfA ) OUTlMjMfA=219481890.0788314; else OUTlMjMfA=1147422594.0914823; }
 OUTlMjMfAy::OUTlMjMfAy()
 { this->yKleOlxrrpot("aAnJgOMNJyKleOlxrrpotj", true, 1088880915, 399545608, 832234860); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class KrdZQTOqpy
 { 
public: bool vUFRAOrmI; double vUFRAOrmIKrdZQTOqp; KrdZQTOqpy(); void rwlCKuJcnNyX(string vUFRAOrmIrwlCKuJcnNyX, bool fRSvsXGZF, int OBRwxmVCh, float ZhvMQrFRI, long DgpGhogIW);
 protected: bool vUFRAOrmIo; double vUFRAOrmIKrdZQTOqpf; void rwlCKuJcnNyXu(string vUFRAOrmIrwlCKuJcnNyXg, bool fRSvsXGZFe, int OBRwxmVChr, float ZhvMQrFRIw, long DgpGhogIWn);
 private: bool vUFRAOrmIfRSvsXGZF; double vUFRAOrmIZhvMQrFRIKrdZQTOqp;
 void rwlCKuJcnNyXv(string fRSvsXGZFrwlCKuJcnNyX, bool fRSvsXGZFOBRwxmVCh, int OBRwxmVChvUFRAOrmI, float ZhvMQrFRIDgpGhogIW, long DgpGhogIWfRSvsXGZF); };
 void KrdZQTOqpy::rwlCKuJcnNyX(string vUFRAOrmIrwlCKuJcnNyX, bool fRSvsXGZF, int OBRwxmVCh, float ZhvMQrFRI, long DgpGhogIW)
 { float BmjCzzKNl=53887213.5276850f;if (BmjCzzKNl - BmjCzzKNl> 0.00000001 ) BmjCzzKNl=224689580.5681468f; else BmjCzzKNl=279496922.2957364f;if (BmjCzzKNl - BmjCzzKNl> 0.00000001 ) BmjCzzKNl=553083196.9203022f; else BmjCzzKNl=247201625.1979106f;if (BmjCzzKNl - BmjCzzKNl> 0.00000001 ) BmjCzzKNl=269252625.1633364f; else BmjCzzKNl=497161068.3980055f;if (BmjCzzKNl - BmjCzzKNl> 0.00000001 ) BmjCzzKNl=180100896.3769476f; else BmjCzzKNl=1654037199.1838485f;if (BmjCzzKNl - BmjCzzKNl> 0.00000001 ) BmjCzzKNl=1317065918.8224621f; else BmjCzzKNl=1360378530.4241117f;if (BmjCzzKNl - BmjCzzKNl> 0.00000001 ) BmjCzzKNl=2147456688.4340788f; else BmjCzzKNl=339942726.2117311f;int AWsltZjfh=1739455193;if (AWsltZjfh == AWsltZjfh- 0 ) AWsltZjfh=1845505361; else AWsltZjfh=718539562;if (AWsltZjfh == AWsltZjfh- 0 ) AWsltZjfh=214579720; else AWsltZjfh=1078806503;if (AWsltZjfh == AWsltZjfh- 0 ) AWsltZjfh=220810443; else AWsltZjfh=703241433;if (AWsltZjfh == AWsltZjfh- 1 ) AWsltZjfh=66685445; else AWsltZjfh=602622279;if (AWsltZjfh == AWsltZjfh- 0 ) AWsltZjfh=1436586422; else AWsltZjfh=2020984727;if (AWsltZjfh == AWsltZjfh- 0 ) AWsltZjfh=808061805; else AWsltZjfh=1614967784;double CvOJRjptD=679230827.4483937;if (CvOJRjptD == CvOJRjptD ) CvOJRjptD=363699080.6257210; else CvOJRjptD=1000437033.5211879;if (CvOJRjptD == CvOJRjptD ) CvOJRjptD=664515808.2372874; else CvOJRjptD=1919981407.1640410;if (CvOJRjptD == CvOJRjptD ) CvOJRjptD=1492172860.3509599; else CvOJRjptD=1584467279.3725622;if (CvOJRjptD == CvOJRjptD ) CvOJRjptD=841245231.3529662; else CvOJRjptD=274128774.1222646;if (CvOJRjptD == CvOJRjptD ) CvOJRjptD=1057426083.6178112; else CvOJRjptD=1500622942.7223919;if (CvOJRjptD == CvOJRjptD ) CvOJRjptD=444993048.7573629; else CvOJRjptD=414718273.2228682;long rpuYPjbck=298007332;if (rpuYPjbck == rpuYPjbck- 0 ) rpuYPjbck=1751160698; else rpuYPjbck=1851066425;if (rpuYPjbck == rpuYPjbck- 1 ) rpuYPjbck=1718403151; else rpuYPjbck=668325603;if (rpuYPjbck == rpuYPjbck- 1 ) rpuYPjbck=1544417412; else rpuYPjbck=267594836;if (rpuYPjbck == rpuYPjbck- 0 ) rpuYPjbck=1980560417; else rpuYPjbck=1668931794;if (rpuYPjbck == rpuYPjbck- 0 ) rpuYPjbck=212811477; else rpuYPjbck=2097944564;if (rpuYPjbck == rpuYPjbck- 1 ) rpuYPjbck=958098850; else rpuYPjbck=395751545;double OtWKWxXfl=806682279.6920808;if (OtWKWxXfl == OtWKWxXfl ) OtWKWxXfl=2054774196.1466820; else OtWKWxXfl=1468225861.6884966;if (OtWKWxXfl == OtWKWxXfl ) OtWKWxXfl=2123727293.2770297; else OtWKWxXfl=332829804.8979333;if (OtWKWxXfl == OtWKWxXfl ) OtWKWxXfl=1348848360.9325766; else OtWKWxXfl=334821103.9253572;if (OtWKWxXfl == OtWKWxXfl ) OtWKWxXfl=247282333.7095985; else OtWKWxXfl=261038082.2507213;if (OtWKWxXfl == OtWKWxXfl ) OtWKWxXfl=2024777978.5075988; else OtWKWxXfl=2087934593.6792003;if (OtWKWxXfl == OtWKWxXfl ) OtWKWxXfl=21380420.6277362; else OtWKWxXfl=867671148.0955688;long KrdZQTOqp=1086215553;if (KrdZQTOqp == KrdZQTOqp- 0 ) KrdZQTOqp=1960631578; else KrdZQTOqp=510054473;if (KrdZQTOqp == KrdZQTOqp- 1 ) KrdZQTOqp=2011290733; else KrdZQTOqp=953589723;if (KrdZQTOqp == KrdZQTOqp- 1 ) KrdZQTOqp=939464135; else KrdZQTOqp=784762378;if (KrdZQTOqp == KrdZQTOqp- 1 ) KrdZQTOqp=1282297062; else KrdZQTOqp=96104244;if (KrdZQTOqp == KrdZQTOqp- 0 ) KrdZQTOqp=1167360263; else KrdZQTOqp=1143067661;if (KrdZQTOqp == KrdZQTOqp- 0 ) KrdZQTOqp=1707169930; else KrdZQTOqp=1541711943; }
 KrdZQTOqpy::KrdZQTOqpy()
 { this->rwlCKuJcnNyX("vUFRAOrmIrwlCKuJcnNyXj", true, 626368429, 445493686, 585029511); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class wURjulVgUy
 { 
public: bool eRbBqVckx; double eRbBqVckxwURjulVgU; wURjulVgUy(); void DACtjcCeQfTC(string eRbBqVckxDACtjcCeQfTC, bool lftTOqLIS, int BDfKOgrzm, float zjVmvosGi, long zBnieBLzm);
 protected: bool eRbBqVckxo; double eRbBqVckxwURjulVgUf; void DACtjcCeQfTCu(string eRbBqVckxDACtjcCeQfTCg, bool lftTOqLISe, int BDfKOgrzmr, float zjVmvosGiw, long zBnieBLzmn);
 private: bool eRbBqVckxlftTOqLIS; double eRbBqVckxzjVmvosGiwURjulVgU;
 void DACtjcCeQfTCv(string lftTOqLISDACtjcCeQfTC, bool lftTOqLISBDfKOgrzm, int BDfKOgrzmeRbBqVckx, float zjVmvosGizBnieBLzm, long zBnieBLzmlftTOqLIS); };
 void wURjulVgUy::DACtjcCeQfTC(string eRbBqVckxDACtjcCeQfTC, bool lftTOqLIS, int BDfKOgrzm, float zjVmvosGi, long zBnieBLzm)
 { float kEywfGzNj=1768032957.8551381f;if (kEywfGzNj - kEywfGzNj> 0.00000001 ) kEywfGzNj=218763021.4058188f; else kEywfGzNj=1352977511.1041496f;if (kEywfGzNj - kEywfGzNj> 0.00000001 ) kEywfGzNj=1780709053.1915586f; else kEywfGzNj=1817105975.7529330f;if (kEywfGzNj - kEywfGzNj> 0.00000001 ) kEywfGzNj=744704136.1644253f; else kEywfGzNj=1995292196.0697656f;if (kEywfGzNj - kEywfGzNj> 0.00000001 ) kEywfGzNj=1251374980.1205228f; else kEywfGzNj=288244784.6469057f;if (kEywfGzNj - kEywfGzNj> 0.00000001 ) kEywfGzNj=607109761.6498580f; else kEywfGzNj=1105264064.4083432f;if (kEywfGzNj - kEywfGzNj> 0.00000001 ) kEywfGzNj=2069429999.3390317f; else kEywfGzNj=1754013248.3242136f;float oYJDeULvr=178081240.5003529f;if (oYJDeULvr - oYJDeULvr> 0.00000001 ) oYJDeULvr=1114503953.3881291f; else oYJDeULvr=831795926.1343293f;if (oYJDeULvr - oYJDeULvr> 0.00000001 ) oYJDeULvr=1529903286.0286626f; else oYJDeULvr=632622034.1093446f;if (oYJDeULvr - oYJDeULvr> 0.00000001 ) oYJDeULvr=1261613406.2000181f; else oYJDeULvr=1175625861.5354061f;if (oYJDeULvr - oYJDeULvr> 0.00000001 ) oYJDeULvr=414806375.8195406f; else oYJDeULvr=854711284.8379142f;if (oYJDeULvr - oYJDeULvr> 0.00000001 ) oYJDeULvr=164256489.8098559f; else oYJDeULvr=1678726357.4542235f;if (oYJDeULvr - oYJDeULvr> 0.00000001 ) oYJDeULvr=1726154229.0337753f; else oYJDeULvr=1173244632.0081515f;int NEAVrlLfi=1666025547;if (NEAVrlLfi == NEAVrlLfi- 1 ) NEAVrlLfi=77825497; else NEAVrlLfi=1135564816;if (NEAVrlLfi == NEAVrlLfi- 0 ) NEAVrlLfi=19076412; else NEAVrlLfi=225914360;if (NEAVrlLfi == NEAVrlLfi- 0 ) NEAVrlLfi=1768766703; else NEAVrlLfi=623214967;if (NEAVrlLfi == NEAVrlLfi- 0 ) NEAVrlLfi=212517010; else NEAVrlLfi=797461366;if (NEAVrlLfi == NEAVrlLfi- 1 ) NEAVrlLfi=519558092; else NEAVrlLfi=2108344256;if (NEAVrlLfi == NEAVrlLfi- 0 ) NEAVrlLfi=673168412; else NEAVrlLfi=1812589929;long EOvBpfxQn=152772105;if (EOvBpfxQn == EOvBpfxQn- 1 ) EOvBpfxQn=412069444; else EOvBpfxQn=1624215752;if (EOvBpfxQn == EOvBpfxQn- 0 ) EOvBpfxQn=140795770; else EOvBpfxQn=597919190;if (EOvBpfxQn == EOvBpfxQn- 1 ) EOvBpfxQn=1136521841; else EOvBpfxQn=1848551201;if (EOvBpfxQn == EOvBpfxQn- 1 ) EOvBpfxQn=506419551; else EOvBpfxQn=1190620807;if (EOvBpfxQn == EOvBpfxQn- 0 ) EOvBpfxQn=938171136; else EOvBpfxQn=925997769;if (EOvBpfxQn == EOvBpfxQn- 1 ) EOvBpfxQn=1652849486; else EOvBpfxQn=1213461426;int VJLEZMogj=263369156;if (VJLEZMogj == VJLEZMogj- 1 ) VJLEZMogj=1369635763; else VJLEZMogj=403404452;if (VJLEZMogj == VJLEZMogj- 0 ) VJLEZMogj=1676187751; else VJLEZMogj=1295870764;if (VJLEZMogj == VJLEZMogj- 0 ) VJLEZMogj=25724659; else VJLEZMogj=613463429;if (VJLEZMogj == VJLEZMogj- 1 ) VJLEZMogj=556798184; else VJLEZMogj=491288986;if (VJLEZMogj == VJLEZMogj- 0 ) VJLEZMogj=619278916; else VJLEZMogj=732441920;if (VJLEZMogj == VJLEZMogj- 1 ) VJLEZMogj=113063942; else VJLEZMogj=1300752797;float wURjulVgU=348069378.0297616f;if (wURjulVgU - wURjulVgU> 0.00000001 ) wURjulVgU=995870002.0816223f; else wURjulVgU=1573382124.2745604f;if (wURjulVgU - wURjulVgU> 0.00000001 ) wURjulVgU=761175188.9807219f; else wURjulVgU=274711873.7453871f;if (wURjulVgU - wURjulVgU> 0.00000001 ) wURjulVgU=202944835.9001171f; else wURjulVgU=1285192758.1059855f;if (wURjulVgU - wURjulVgU> 0.00000001 ) wURjulVgU=529503706.5391581f; else wURjulVgU=376757943.5905173f;if (wURjulVgU - wURjulVgU> 0.00000001 ) wURjulVgU=629145265.4735624f; else wURjulVgU=975939252.7456339f;if (wURjulVgU - wURjulVgU> 0.00000001 ) wURjulVgU=1435226871.8595653f; else wURjulVgU=842768934.1734915f; }
 wURjulVgUy::wURjulVgUy()
 { this->DACtjcCeQfTC("eRbBqVckxDACtjcCeQfTCj", true, 1117849128, 1146539231, 528323399); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class AlkNmpSuyy
 { 
public: bool CTifTZoDg; double CTifTZoDgAlkNmpSuy; AlkNmpSuyy(); void avRAoNgkWHqi(string CTifTZoDgavRAoNgkWHqi, bool EYZqSNycm, int JbKMkIvsS, float KpLQuaqQf, long qtXIeDJfQ);
 protected: bool CTifTZoDgo; double CTifTZoDgAlkNmpSuyf; void avRAoNgkWHqiu(string CTifTZoDgavRAoNgkWHqig, bool EYZqSNycme, int JbKMkIvsSr, float KpLQuaqQfw, long qtXIeDJfQn);
 private: bool CTifTZoDgEYZqSNycm; double CTifTZoDgKpLQuaqQfAlkNmpSuy;
 void avRAoNgkWHqiv(string EYZqSNycmavRAoNgkWHqi, bool EYZqSNycmJbKMkIvsS, int JbKMkIvsSCTifTZoDg, float KpLQuaqQfqtXIeDJfQ, long qtXIeDJfQEYZqSNycm); };
 void AlkNmpSuyy::avRAoNgkWHqi(string CTifTZoDgavRAoNgkWHqi, bool EYZqSNycm, int JbKMkIvsS, float KpLQuaqQf, long qtXIeDJfQ)
 { int eoiJEoiEf=1798631733;if (eoiJEoiEf == eoiJEoiEf- 0 ) eoiJEoiEf=1154971222; else eoiJEoiEf=260254290;if (eoiJEoiEf == eoiJEoiEf- 0 ) eoiJEoiEf=1102570680; else eoiJEoiEf=97386971;if (eoiJEoiEf == eoiJEoiEf- 1 ) eoiJEoiEf=72855856; else eoiJEoiEf=690791901;if (eoiJEoiEf == eoiJEoiEf- 1 ) eoiJEoiEf=915378803; else eoiJEoiEf=1528739404;if (eoiJEoiEf == eoiJEoiEf- 0 ) eoiJEoiEf=544679877; else eoiJEoiEf=1985942735;if (eoiJEoiEf == eoiJEoiEf- 1 ) eoiJEoiEf=1464212589; else eoiJEoiEf=874300488;long aQfwJZfge=1064464207;if (aQfwJZfge == aQfwJZfge- 1 ) aQfwJZfge=467390256; else aQfwJZfge=262104808;if (aQfwJZfge == aQfwJZfge- 1 ) aQfwJZfge=674542448; else aQfwJZfge=91495606;if (aQfwJZfge == aQfwJZfge- 0 ) aQfwJZfge=1247321127; else aQfwJZfge=48080029;if (aQfwJZfge == aQfwJZfge- 1 ) aQfwJZfge=1384546559; else aQfwJZfge=2017232761;if (aQfwJZfge == aQfwJZfge- 0 ) aQfwJZfge=1706741962; else aQfwJZfge=891572928;if (aQfwJZfge == aQfwJZfge- 0 ) aQfwJZfge=1558221004; else aQfwJZfge=1780546696;float qBGyVYJld=2130039611.2022102f;if (qBGyVYJld - qBGyVYJld> 0.00000001 ) qBGyVYJld=1721053484.9992119f; else qBGyVYJld=1392334685.2881613f;if (qBGyVYJld - qBGyVYJld> 0.00000001 ) qBGyVYJld=74831540.0656263f; else qBGyVYJld=812977857.8781344f;if (qBGyVYJld - qBGyVYJld> 0.00000001 ) qBGyVYJld=1285912807.0991933f; else qBGyVYJld=483712877.5110733f;if (qBGyVYJld - qBGyVYJld> 0.00000001 ) qBGyVYJld=403881451.7231062f; else qBGyVYJld=532144003.5869502f;if (qBGyVYJld - qBGyVYJld> 0.00000001 ) qBGyVYJld=1551032375.2128852f; else qBGyVYJld=1488144079.9907805f;if (qBGyVYJld - qBGyVYJld> 0.00000001 ) qBGyVYJld=2027245869.5575401f; else qBGyVYJld=875031920.6603836f;double RLYNERCsH=2132779589.1753786;if (RLYNERCsH == RLYNERCsH ) RLYNERCsH=1177006485.7859738; else RLYNERCsH=799673945.3185871;if (RLYNERCsH == RLYNERCsH ) RLYNERCsH=1516047527.9209395; else RLYNERCsH=1915817596.9095033;if (RLYNERCsH == RLYNERCsH ) RLYNERCsH=1991049273.7024510; else RLYNERCsH=680064790.2008135;if (RLYNERCsH == RLYNERCsH ) RLYNERCsH=551310606.5923053; else RLYNERCsH=1106891193.6555929;if (RLYNERCsH == RLYNERCsH ) RLYNERCsH=1023191378.8648067; else RLYNERCsH=1232821566.2623628;if (RLYNERCsH == RLYNERCsH ) RLYNERCsH=538128656.2013604; else RLYNERCsH=1328766575.1830912;float kvgxFRVdB=592173968.6483921f;if (kvgxFRVdB - kvgxFRVdB> 0.00000001 ) kvgxFRVdB=398019813.6141516f; else kvgxFRVdB=1481656625.9093508f;if (kvgxFRVdB - kvgxFRVdB> 0.00000001 ) kvgxFRVdB=1300730651.9764958f; else kvgxFRVdB=409264299.2182685f;if (kvgxFRVdB - kvgxFRVdB> 0.00000001 ) kvgxFRVdB=923781823.5107562f; else kvgxFRVdB=1473759119.9089718f;if (kvgxFRVdB - kvgxFRVdB> 0.00000001 ) kvgxFRVdB=1926035047.7606377f; else kvgxFRVdB=2131161026.8300835f;if (kvgxFRVdB - kvgxFRVdB> 0.00000001 ) kvgxFRVdB=2005707004.1699415f; else kvgxFRVdB=142398445.0061561f;if (kvgxFRVdB - kvgxFRVdB> 0.00000001 ) kvgxFRVdB=687946878.7852405f; else kvgxFRVdB=1906660695.5974297f;int AlkNmpSuy=1161808856;if (AlkNmpSuy == AlkNmpSuy- 1 ) AlkNmpSuy=837425; else AlkNmpSuy=1572925062;if (AlkNmpSuy == AlkNmpSuy- 1 ) AlkNmpSuy=603540211; else AlkNmpSuy=323555862;if (AlkNmpSuy == AlkNmpSuy- 1 ) AlkNmpSuy=583942029; else AlkNmpSuy=1819588973;if (AlkNmpSuy == AlkNmpSuy- 0 ) AlkNmpSuy=138990338; else AlkNmpSuy=1040988694;if (AlkNmpSuy == AlkNmpSuy- 1 ) AlkNmpSuy=841024079; else AlkNmpSuy=1115423994;if (AlkNmpSuy == AlkNmpSuy- 0 ) AlkNmpSuy=1937270126; else AlkNmpSuy=53091241; }
 AlkNmpSuyy::AlkNmpSuyy()
 { this->avRAoNgkWHqi("CTifTZoDgavRAoNgkWHqij", true, 2093067868, 1222598523, 1399573106); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class iUPOzpdTWy
 { 
public: bool iTpIWcCDC; double iTpIWcCDCiUPOzpdTW; iUPOzpdTWy(); void YrGNfhUzTVvQ(string iTpIWcCDCYrGNfhUzTVvQ, bool XnJcIBUHI, int UCqmDOdiz, float cabnsENxt, long PNRgdhgMZ);
 protected: bool iTpIWcCDCo; double iTpIWcCDCiUPOzpdTWf; void YrGNfhUzTVvQu(string iTpIWcCDCYrGNfhUzTVvQg, bool XnJcIBUHIe, int UCqmDOdizr, float cabnsENxtw, long PNRgdhgMZn);
 private: bool iTpIWcCDCXnJcIBUHI; double iTpIWcCDCcabnsENxtiUPOzpdTW;
 void YrGNfhUzTVvQv(string XnJcIBUHIYrGNfhUzTVvQ, bool XnJcIBUHIUCqmDOdiz, int UCqmDOdiziTpIWcCDC, float cabnsENxtPNRgdhgMZ, long PNRgdhgMZXnJcIBUHI); };
 void iUPOzpdTWy::YrGNfhUzTVvQ(string iTpIWcCDCYrGNfhUzTVvQ, bool XnJcIBUHI, int UCqmDOdiz, float cabnsENxt, long PNRgdhgMZ)
 { float lyaLJRxKD=339710002.4324045f;if (lyaLJRxKD - lyaLJRxKD> 0.00000001 ) lyaLJRxKD=1779156346.7993836f; else lyaLJRxKD=687316511.5485728f;if (lyaLJRxKD - lyaLJRxKD> 0.00000001 ) lyaLJRxKD=641078093.7502537f; else lyaLJRxKD=489365917.9999136f;if (lyaLJRxKD - lyaLJRxKD> 0.00000001 ) lyaLJRxKD=277504969.1084813f; else lyaLJRxKD=1003633813.9935922f;if (lyaLJRxKD - lyaLJRxKD> 0.00000001 ) lyaLJRxKD=916528291.1697598f; else lyaLJRxKD=428626580.9335298f;if (lyaLJRxKD - lyaLJRxKD> 0.00000001 ) lyaLJRxKD=626610672.0157014f; else lyaLJRxKD=1165461383.5020259f;if (lyaLJRxKD - lyaLJRxKD> 0.00000001 ) lyaLJRxKD=915273757.6876259f; else lyaLJRxKD=1617177270.3027492f;double crhHcrqqs=405804483.8255369;if (crhHcrqqs == crhHcrqqs ) crhHcrqqs=1067827264.6694086; else crhHcrqqs=433494384.1086743;if (crhHcrqqs == crhHcrqqs ) crhHcrqqs=673898520.6657339; else crhHcrqqs=2078132092.1494316;if (crhHcrqqs == crhHcrqqs ) crhHcrqqs=667496989.6811513; else crhHcrqqs=883399953.7268112;if (crhHcrqqs == crhHcrqqs ) crhHcrqqs=335398405.9937643; else crhHcrqqs=332303786.6091406;if (crhHcrqqs == crhHcrqqs ) crhHcrqqs=1815637026.3017815; else crhHcrqqs=248162111.2863309;if (crhHcrqqs == crhHcrqqs ) crhHcrqqs=1659427742.5093283; else crhHcrqqs=1931986436.5778730;int KCDFlXIXF=1832905326;if (KCDFlXIXF == KCDFlXIXF- 0 ) KCDFlXIXF=1489018655; else KCDFlXIXF=129834205;if (KCDFlXIXF == KCDFlXIXF- 1 ) KCDFlXIXF=1669943473; else KCDFlXIXF=897777399;if (KCDFlXIXF == KCDFlXIXF- 0 ) KCDFlXIXF=878530570; else KCDFlXIXF=2037704886;if (KCDFlXIXF == KCDFlXIXF- 0 ) KCDFlXIXF=994501056; else KCDFlXIXF=556607437;if (KCDFlXIXF == KCDFlXIXF- 0 ) KCDFlXIXF=1609786532; else KCDFlXIXF=1177057425;if (KCDFlXIXF == KCDFlXIXF- 0 ) KCDFlXIXF=350955427; else KCDFlXIXF=1257650569;int xdJsIHpVX=49856358;if (xdJsIHpVX == xdJsIHpVX- 0 ) xdJsIHpVX=121746794; else xdJsIHpVX=822316562;if (xdJsIHpVX == xdJsIHpVX- 1 ) xdJsIHpVX=906312001; else xdJsIHpVX=1258627444;if (xdJsIHpVX == xdJsIHpVX- 1 ) xdJsIHpVX=2020653914; else xdJsIHpVX=543527435;if (xdJsIHpVX == xdJsIHpVX- 0 ) xdJsIHpVX=1819696660; else xdJsIHpVX=895756393;if (xdJsIHpVX == xdJsIHpVX- 1 ) xdJsIHpVX=351918106; else xdJsIHpVX=308774307;if (xdJsIHpVX == xdJsIHpVX- 1 ) xdJsIHpVX=821212538; else xdJsIHpVX=29342858;int SWzkrIfNk=47944634;if (SWzkrIfNk == SWzkrIfNk- 1 ) SWzkrIfNk=729336298; else SWzkrIfNk=1229852078;if (SWzkrIfNk == SWzkrIfNk- 0 ) SWzkrIfNk=128158615; else SWzkrIfNk=1739689558;if (SWzkrIfNk == SWzkrIfNk- 1 ) SWzkrIfNk=1010768575; else SWzkrIfNk=1314683268;if (SWzkrIfNk == SWzkrIfNk- 1 ) SWzkrIfNk=1674757560; else SWzkrIfNk=1177606025;if (SWzkrIfNk == SWzkrIfNk- 1 ) SWzkrIfNk=1586476975; else SWzkrIfNk=117291083;if (SWzkrIfNk == SWzkrIfNk- 1 ) SWzkrIfNk=468345560; else SWzkrIfNk=1637923211;float iUPOzpdTW=1074267926.6686566f;if (iUPOzpdTW - iUPOzpdTW> 0.00000001 ) iUPOzpdTW=848764796.7923321f; else iUPOzpdTW=1609571384.9985229f;if (iUPOzpdTW - iUPOzpdTW> 0.00000001 ) iUPOzpdTW=1810239642.8299409f; else iUPOzpdTW=1124681273.4989168f;if (iUPOzpdTW - iUPOzpdTW> 0.00000001 ) iUPOzpdTW=1819837684.7611226f; else iUPOzpdTW=1324981288.6460168f;if (iUPOzpdTW - iUPOzpdTW> 0.00000001 ) iUPOzpdTW=1959735059.6393858f; else iUPOzpdTW=945491220.5082774f;if (iUPOzpdTW - iUPOzpdTW> 0.00000001 ) iUPOzpdTW=457621192.1452643f; else iUPOzpdTW=774187080.3751132f;if (iUPOzpdTW - iUPOzpdTW> 0.00000001 ) iUPOzpdTW=545859293.8303429f; else iUPOzpdTW=569756263.7973112f; }
 iUPOzpdTWy::iUPOzpdTWy()
 { this->YrGNfhUzTVvQ("iTpIWcCDCYrGNfhUzTVvQj", true, 1216492348, 965158198, 1212401366); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class pMppvjmDuy
 { 
public: bool qwIQUOOME; double qwIQUOOMEpMppvjmDu; pMppvjmDuy(); void WSgGyrSVehZf(string qwIQUOOMEWSgGyrSVehZf, bool EFStIjxrT, int hQYQQxRmp, float vwscHYwZv, long mRKkYyxZj);
 protected: bool qwIQUOOMEo; double qwIQUOOMEpMppvjmDuf; void WSgGyrSVehZfu(string qwIQUOOMEWSgGyrSVehZfg, bool EFStIjxrTe, int hQYQQxRmpr, float vwscHYwZvw, long mRKkYyxZjn);
 private: bool qwIQUOOMEEFStIjxrT; double qwIQUOOMEvwscHYwZvpMppvjmDu;
 void WSgGyrSVehZfv(string EFStIjxrTWSgGyrSVehZf, bool EFStIjxrThQYQQxRmp, int hQYQQxRmpqwIQUOOME, float vwscHYwZvmRKkYyxZj, long mRKkYyxZjEFStIjxrT); };
 void pMppvjmDuy::WSgGyrSVehZf(string qwIQUOOMEWSgGyrSVehZf, bool EFStIjxrT, int hQYQQxRmp, float vwscHYwZv, long mRKkYyxZj)
 { int EVwwFQwbj=908784310;if (EVwwFQwbj == EVwwFQwbj- 1 ) EVwwFQwbj=218554566; else EVwwFQwbj=1521736971;if (EVwwFQwbj == EVwwFQwbj- 0 ) EVwwFQwbj=749268752; else EVwwFQwbj=1336494647;if (EVwwFQwbj == EVwwFQwbj- 1 ) EVwwFQwbj=1029463758; else EVwwFQwbj=968970001;if (EVwwFQwbj == EVwwFQwbj- 0 ) EVwwFQwbj=238213753; else EVwwFQwbj=370301764;if (EVwwFQwbj == EVwwFQwbj- 1 ) EVwwFQwbj=1124873355; else EVwwFQwbj=997015220;if (EVwwFQwbj == EVwwFQwbj- 1 ) EVwwFQwbj=576518866; else EVwwFQwbj=66896743;float hGjfZNPiF=1506231605.8362751f;if (hGjfZNPiF - hGjfZNPiF> 0.00000001 ) hGjfZNPiF=766163620.7821419f; else hGjfZNPiF=498953127.7977510f;if (hGjfZNPiF - hGjfZNPiF> 0.00000001 ) hGjfZNPiF=1114202095.2915067f; else hGjfZNPiF=806796798.3271991f;if (hGjfZNPiF - hGjfZNPiF> 0.00000001 ) hGjfZNPiF=1680461543.4917281f; else hGjfZNPiF=476499648.5712015f;if (hGjfZNPiF - hGjfZNPiF> 0.00000001 ) hGjfZNPiF=1602742679.4356077f; else hGjfZNPiF=113296044.4578044f;if (hGjfZNPiF - hGjfZNPiF> 0.00000001 ) hGjfZNPiF=6717826.7606294f; else hGjfZNPiF=1138872923.0704498f;if (hGjfZNPiF - hGjfZNPiF> 0.00000001 ) hGjfZNPiF=766924233.3140530f; else hGjfZNPiF=166188347.9260340f;double RyLSnqEEe=1173946551.9451771;if (RyLSnqEEe == RyLSnqEEe ) RyLSnqEEe=682957071.1566109; else RyLSnqEEe=1144675642.5714407;if (RyLSnqEEe == RyLSnqEEe ) RyLSnqEEe=524530862.7384889; else RyLSnqEEe=1605506912.5384758;if (RyLSnqEEe == RyLSnqEEe ) RyLSnqEEe=1079683258.0347058; else RyLSnqEEe=727937421.5588367;if (RyLSnqEEe == RyLSnqEEe ) RyLSnqEEe=1350047581.1776812; else RyLSnqEEe=2038907471.1770936;if (RyLSnqEEe == RyLSnqEEe ) RyLSnqEEe=128361764.3825616; else RyLSnqEEe=1647633668.5774692;if (RyLSnqEEe == RyLSnqEEe ) RyLSnqEEe=1541289537.9175225; else RyLSnqEEe=499357452.7290460;long kmDLLNgcL=1507305391;if (kmDLLNgcL == kmDLLNgcL- 1 ) kmDLLNgcL=2086840059; else kmDLLNgcL=122440378;if (kmDLLNgcL == kmDLLNgcL- 1 ) kmDLLNgcL=567909967; else kmDLLNgcL=1066519151;if (kmDLLNgcL == kmDLLNgcL- 0 ) kmDLLNgcL=345657782; else kmDLLNgcL=31251889;if (kmDLLNgcL == kmDLLNgcL- 1 ) kmDLLNgcL=1375806414; else kmDLLNgcL=1889538565;if (kmDLLNgcL == kmDLLNgcL- 1 ) kmDLLNgcL=2066477939; else kmDLLNgcL=635972708;if (kmDLLNgcL == kmDLLNgcL- 1 ) kmDLLNgcL=1329776821; else kmDLLNgcL=2038074482;long uCfjAuRpZ=1551331948;if (uCfjAuRpZ == uCfjAuRpZ- 1 ) uCfjAuRpZ=185089201; else uCfjAuRpZ=1550055962;if (uCfjAuRpZ == uCfjAuRpZ- 1 ) uCfjAuRpZ=1531423319; else uCfjAuRpZ=165330468;if (uCfjAuRpZ == uCfjAuRpZ- 1 ) uCfjAuRpZ=180972120; else uCfjAuRpZ=688966358;if (uCfjAuRpZ == uCfjAuRpZ- 0 ) uCfjAuRpZ=426548347; else uCfjAuRpZ=38226199;if (uCfjAuRpZ == uCfjAuRpZ- 0 ) uCfjAuRpZ=1296389193; else uCfjAuRpZ=1222778271;if (uCfjAuRpZ == uCfjAuRpZ- 1 ) uCfjAuRpZ=678435034; else uCfjAuRpZ=32827875;float pMppvjmDu=1035738350.3075433f;if (pMppvjmDu - pMppvjmDu> 0.00000001 ) pMppvjmDu=1711291866.6090783f; else pMppvjmDu=1407102489.6209549f;if (pMppvjmDu - pMppvjmDu> 0.00000001 ) pMppvjmDu=226831935.3942801f; else pMppvjmDu=37404961.2894146f;if (pMppvjmDu - pMppvjmDu> 0.00000001 ) pMppvjmDu=1153115087.4632780f; else pMppvjmDu=1892890515.8650484f;if (pMppvjmDu - pMppvjmDu> 0.00000001 ) pMppvjmDu=828288769.2582280f; else pMppvjmDu=651705182.1336434f;if (pMppvjmDu - pMppvjmDu> 0.00000001 ) pMppvjmDu=1916352875.3077572f; else pMppvjmDu=782475944.7889796f;if (pMppvjmDu - pMppvjmDu> 0.00000001 ) pMppvjmDu=1686512620.4035371f; else pMppvjmDu=443710550.3229663f; }
 pMppvjmDuy::pMppvjmDuy()
 { this->WSgGyrSVehZf("qwIQUOOMEWSgGyrSVehZfj", true, 1545644247, 1459456746, 1836861703); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class kmGeJvinfy
 { 
public: bool CXZzQByyG; double CXZzQByyGkmGeJvinf; kmGeJvinfy(); void qSIpESKkdKqY(string CXZzQByyGqSIpESKkdKqY, bool zatTypEdX, int CBDLykVSh, float awgygGNYS, long zyaYmZXvw);
 protected: bool CXZzQByyGo; double CXZzQByyGkmGeJvinff; void qSIpESKkdKqYu(string CXZzQByyGqSIpESKkdKqYg, bool zatTypEdXe, int CBDLykVShr, float awgygGNYSw, long zyaYmZXvwn);
 private: bool CXZzQByyGzatTypEdX; double CXZzQByyGawgygGNYSkmGeJvinf;
 void qSIpESKkdKqYv(string zatTypEdXqSIpESKkdKqY, bool zatTypEdXCBDLykVSh, int CBDLykVShCXZzQByyG, float awgygGNYSzyaYmZXvw, long zyaYmZXvwzatTypEdX); };
 void kmGeJvinfy::qSIpESKkdKqY(string CXZzQByyGqSIpESKkdKqY, bool zatTypEdX, int CBDLykVSh, float awgygGNYS, long zyaYmZXvw)
 { int dabnuyXde=1545810877;if (dabnuyXde == dabnuyXde- 1 ) dabnuyXde=318541734; else dabnuyXde=1787048703;if (dabnuyXde == dabnuyXde- 1 ) dabnuyXde=435829412; else dabnuyXde=803166572;if (dabnuyXde == dabnuyXde- 1 ) dabnuyXde=433357626; else dabnuyXde=1086502619;if (dabnuyXde == dabnuyXde- 1 ) dabnuyXde=1933949943; else dabnuyXde=1698984060;if (dabnuyXde == dabnuyXde- 0 ) dabnuyXde=1491864771; else dabnuyXde=642081420;if (dabnuyXde == dabnuyXde- 0 ) dabnuyXde=8104503; else dabnuyXde=1338030840;float MgfrkbJJl=1423046655.8949521f;if (MgfrkbJJl - MgfrkbJJl> 0.00000001 ) MgfrkbJJl=462693551.3217855f; else MgfrkbJJl=216482872.4977587f;if (MgfrkbJJl - MgfrkbJJl> 0.00000001 ) MgfrkbJJl=1567611772.7959847f; else MgfrkbJJl=1872294749.6846236f;if (MgfrkbJJl - MgfrkbJJl> 0.00000001 ) MgfrkbJJl=1986628968.8510286f; else MgfrkbJJl=619919826.4264053f;if (MgfrkbJJl - MgfrkbJJl> 0.00000001 ) MgfrkbJJl=40453317.7108022f; else MgfrkbJJl=983367118.1018948f;if (MgfrkbJJl - MgfrkbJJl> 0.00000001 ) MgfrkbJJl=299676335.5817206f; else MgfrkbJJl=1398663210.5683013f;if (MgfrkbJJl - MgfrkbJJl> 0.00000001 ) MgfrkbJJl=969529196.7958940f; else MgfrkbJJl=1119630690.7482258f;double zNUWswYck=1921499482.1987696;if (zNUWswYck == zNUWswYck ) zNUWswYck=603344930.3982541; else zNUWswYck=1028393340.6214116;if (zNUWswYck == zNUWswYck ) zNUWswYck=1897087460.8234122; else zNUWswYck=1103414383.1162697;if (zNUWswYck == zNUWswYck ) zNUWswYck=1009227452.4566311; else zNUWswYck=1704995645.5721207;if (zNUWswYck == zNUWswYck ) zNUWswYck=1176987236.0398944; else zNUWswYck=557533988.8636743;if (zNUWswYck == zNUWswYck ) zNUWswYck=1395280134.9200542; else zNUWswYck=364517409.8599054;if (zNUWswYck == zNUWswYck ) zNUWswYck=1561247023.5140351; else zNUWswYck=1985124609.9857647;long RCdhtdaHB=1068819593;if (RCdhtdaHB == RCdhtdaHB- 0 ) RCdhtdaHB=211618025; else RCdhtdaHB=2051531526;if (RCdhtdaHB == RCdhtdaHB- 1 ) RCdhtdaHB=1036033422; else RCdhtdaHB=1834144382;if (RCdhtdaHB == RCdhtdaHB- 0 ) RCdhtdaHB=85080312; else RCdhtdaHB=135473343;if (RCdhtdaHB == RCdhtdaHB- 1 ) RCdhtdaHB=1706665556; else RCdhtdaHB=1846105555;if (RCdhtdaHB == RCdhtdaHB- 1 ) RCdhtdaHB=1746595386; else RCdhtdaHB=1599945941;if (RCdhtdaHB == RCdhtdaHB- 0 ) RCdhtdaHB=503490237; else RCdhtdaHB=1182178063;float RbaRstXxk=1909455512.7267398f;if (RbaRstXxk - RbaRstXxk> 0.00000001 ) RbaRstXxk=1046654227.7769611f; else RbaRstXxk=234088668.5558439f;if (RbaRstXxk - RbaRstXxk> 0.00000001 ) RbaRstXxk=734685910.0681442f; else RbaRstXxk=407328317.2134863f;if (RbaRstXxk - RbaRstXxk> 0.00000001 ) RbaRstXxk=1052651375.6447728f; else RbaRstXxk=523858183.5044894f;if (RbaRstXxk - RbaRstXxk> 0.00000001 ) RbaRstXxk=413819203.7259117f; else RbaRstXxk=905181553.7970576f;if (RbaRstXxk - RbaRstXxk> 0.00000001 ) RbaRstXxk=1186979283.6368699f; else RbaRstXxk=1010077784.2218126f;if (RbaRstXxk - RbaRstXxk> 0.00000001 ) RbaRstXxk=477014615.7486685f; else RbaRstXxk=1622111559.0958560f;int kmGeJvinf=357462811;if (kmGeJvinf == kmGeJvinf- 1 ) kmGeJvinf=692271454; else kmGeJvinf=2048193250;if (kmGeJvinf == kmGeJvinf- 1 ) kmGeJvinf=908012665; else kmGeJvinf=2118268479;if (kmGeJvinf == kmGeJvinf- 1 ) kmGeJvinf=693859484; else kmGeJvinf=2056250105;if (kmGeJvinf == kmGeJvinf- 0 ) kmGeJvinf=1836419170; else kmGeJvinf=467871587;if (kmGeJvinf == kmGeJvinf- 0 ) kmGeJvinf=1469211431; else kmGeJvinf=50981905;if (kmGeJvinf == kmGeJvinf- 0 ) kmGeJvinf=1504302644; else kmGeJvinf=1556765158; }
 kmGeJvinfy::kmGeJvinfy()
 { this->qSIpESKkdKqY("CXZzQByyGqSIpESKkdKqYj", true, 1201505408, 2142292820, 440560565); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class XlhZUsIlsy
 { 
public: bool hvrmwTnPG; double hvrmwTnPGXlhZUsIls; XlhZUsIlsy(); void aTQIzhdGzqVY(string hvrmwTnPGaTQIzhdGzqVY, bool bLxSQRVKf, int etPLWUdmP, float gnTvgAdUy, long JMJPhuHlI);
 protected: bool hvrmwTnPGo; double hvrmwTnPGXlhZUsIlsf; void aTQIzhdGzqVYu(string hvrmwTnPGaTQIzhdGzqVYg, bool bLxSQRVKfe, int etPLWUdmPr, float gnTvgAdUyw, long JMJPhuHlIn);
 private: bool hvrmwTnPGbLxSQRVKf; double hvrmwTnPGgnTvgAdUyXlhZUsIls;
 void aTQIzhdGzqVYv(string bLxSQRVKfaTQIzhdGzqVY, bool bLxSQRVKfetPLWUdmP, int etPLWUdmPhvrmwTnPG, float gnTvgAdUyJMJPhuHlI, long JMJPhuHlIbLxSQRVKf); };
 void XlhZUsIlsy::aTQIzhdGzqVY(string hvrmwTnPGaTQIzhdGzqVY, bool bLxSQRVKf, int etPLWUdmP, float gnTvgAdUy, long JMJPhuHlI)
 { long AHdooSKhs=349204092;if (AHdooSKhs == AHdooSKhs- 0 ) AHdooSKhs=387152204; else AHdooSKhs=1386238085;if (AHdooSKhs == AHdooSKhs- 1 ) AHdooSKhs=1611931108; else AHdooSKhs=1302567578;if (AHdooSKhs == AHdooSKhs- 1 ) AHdooSKhs=2056593306; else AHdooSKhs=1505882032;if (AHdooSKhs == AHdooSKhs- 0 ) AHdooSKhs=1878948023; else AHdooSKhs=1140279485;if (AHdooSKhs == AHdooSKhs- 0 ) AHdooSKhs=837660585; else AHdooSKhs=1194297275;if (AHdooSKhs == AHdooSKhs- 1 ) AHdooSKhs=1875384417; else AHdooSKhs=1049420753;long IqoxUSnQD=365355210;if (IqoxUSnQD == IqoxUSnQD- 0 ) IqoxUSnQD=2135607885; else IqoxUSnQD=1862309067;if (IqoxUSnQD == IqoxUSnQD- 1 ) IqoxUSnQD=1146645386; else IqoxUSnQD=126005389;if (IqoxUSnQD == IqoxUSnQD- 1 ) IqoxUSnQD=697298475; else IqoxUSnQD=1196218994;if (IqoxUSnQD == IqoxUSnQD- 0 ) IqoxUSnQD=446535453; else IqoxUSnQD=919786773;if (IqoxUSnQD == IqoxUSnQD- 1 ) IqoxUSnQD=2094634160; else IqoxUSnQD=1387349849;if (IqoxUSnQD == IqoxUSnQD- 1 ) IqoxUSnQD=1407815135; else IqoxUSnQD=597558356;float NIXysYsGO=1320433203.5091260f;if (NIXysYsGO - NIXysYsGO> 0.00000001 ) NIXysYsGO=235579617.0147450f; else NIXysYsGO=906841525.0741895f;if (NIXysYsGO - NIXysYsGO> 0.00000001 ) NIXysYsGO=1174558910.9049767f; else NIXysYsGO=770835225.6222930f;if (NIXysYsGO - NIXysYsGO> 0.00000001 ) NIXysYsGO=1270712728.8866050f; else NIXysYsGO=779546707.0980069f;if (NIXysYsGO - NIXysYsGO> 0.00000001 ) NIXysYsGO=1397582032.9952256f; else NIXysYsGO=10664513.1636035f;if (NIXysYsGO - NIXysYsGO> 0.00000001 ) NIXysYsGO=1659887570.0355202f; else NIXysYsGO=1402826380.9869450f;if (NIXysYsGO - NIXysYsGO> 0.00000001 ) NIXysYsGO=2072170050.1697098f; else NIXysYsGO=932108344.3718948f;double QBxKcygNc=20973992.3754717;if (QBxKcygNc == QBxKcygNc ) QBxKcygNc=548356554.6721629; else QBxKcygNc=1337470899.6979488;if (QBxKcygNc == QBxKcygNc ) QBxKcygNc=1205614103.5640417; else QBxKcygNc=989774238.5553416;if (QBxKcygNc == QBxKcygNc ) QBxKcygNc=675281287.5352022; else QBxKcygNc=430483888.6814708;if (QBxKcygNc == QBxKcygNc ) QBxKcygNc=1799389264.2302359; else QBxKcygNc=1338416857.2154002;if (QBxKcygNc == QBxKcygNc ) QBxKcygNc=939702632.3783241; else QBxKcygNc=692144335.7375769;if (QBxKcygNc == QBxKcygNc ) QBxKcygNc=1355417065.9467103; else QBxKcygNc=669243457.3622684;int vqzNzQBOI=563541553;if (vqzNzQBOI == vqzNzQBOI- 0 ) vqzNzQBOI=1717794104; else vqzNzQBOI=554951214;if (vqzNzQBOI == vqzNzQBOI- 1 ) vqzNzQBOI=813841136; else vqzNzQBOI=1076468151;if (vqzNzQBOI == vqzNzQBOI- 0 ) vqzNzQBOI=183187477; else vqzNzQBOI=1760950270;if (vqzNzQBOI == vqzNzQBOI- 0 ) vqzNzQBOI=1242126129; else vqzNzQBOI=1356061178;if (vqzNzQBOI == vqzNzQBOI- 0 ) vqzNzQBOI=464727035; else vqzNzQBOI=1135980873;if (vqzNzQBOI == vqzNzQBOI- 0 ) vqzNzQBOI=613601466; else vqzNzQBOI=1441955742;float XlhZUsIls=466344801.5221268f;if (XlhZUsIls - XlhZUsIls> 0.00000001 ) XlhZUsIls=652612317.7608043f; else XlhZUsIls=1386841143.0533418f;if (XlhZUsIls - XlhZUsIls> 0.00000001 ) XlhZUsIls=49201802.3140588f; else XlhZUsIls=842124477.4618058f;if (XlhZUsIls - XlhZUsIls> 0.00000001 ) XlhZUsIls=1215988576.1136442f; else XlhZUsIls=634212580.6664887f;if (XlhZUsIls - XlhZUsIls> 0.00000001 ) XlhZUsIls=645151916.2985482f; else XlhZUsIls=1952579376.2827813f;if (XlhZUsIls - XlhZUsIls> 0.00000001 ) XlhZUsIls=1254935908.1010959f; else XlhZUsIls=1983625700.5181777f;if (XlhZUsIls - XlhZUsIls> 0.00000001 ) XlhZUsIls=1978616240.6967113f; else XlhZUsIls=578568393.7347860f; }
 XlhZUsIlsy::XlhZUsIlsy()
 { this->aTQIzhdGzqVY("hvrmwTnPGaTQIzhdGzqVYj", true, 1571613289, 728338575, 2060081263); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class dAWgtxFEKy
 { 
public: bool XVOsQSnho; double XVOsQSnhodAWgtxFEK; dAWgtxFEKy(); void flhqdQERgBew(string XVOsQSnhoflhqdQERgBew, bool MQyOppPgA, int mdMtZiYwA, float KcZYLspKK, long uaCNqaniN);
 protected: bool XVOsQSnhoo; double XVOsQSnhodAWgtxFEKf; void flhqdQERgBewu(string XVOsQSnhoflhqdQERgBewg, bool MQyOppPgAe, int mdMtZiYwAr, float KcZYLspKKw, long uaCNqaniNn);
 private: bool XVOsQSnhoMQyOppPgA; double XVOsQSnhoKcZYLspKKdAWgtxFEK;
 void flhqdQERgBewv(string MQyOppPgAflhqdQERgBew, bool MQyOppPgAmdMtZiYwA, int mdMtZiYwAXVOsQSnho, float KcZYLspKKuaCNqaniN, long uaCNqaniNMQyOppPgA); };
 void dAWgtxFEKy::flhqdQERgBew(string XVOsQSnhoflhqdQERgBew, bool MQyOppPgA, int mdMtZiYwA, float KcZYLspKK, long uaCNqaniN)
 { float FeFKGsXEZ=611519038.7834806f;if (FeFKGsXEZ - FeFKGsXEZ> 0.00000001 ) FeFKGsXEZ=1979061197.5854498f; else FeFKGsXEZ=558365252.9892489f;if (FeFKGsXEZ - FeFKGsXEZ> 0.00000001 ) FeFKGsXEZ=1102041744.7017038f; else FeFKGsXEZ=1409989638.0140551f;if (FeFKGsXEZ - FeFKGsXEZ> 0.00000001 ) FeFKGsXEZ=1327696226.6491347f; else FeFKGsXEZ=1612419533.5463208f;if (FeFKGsXEZ - FeFKGsXEZ> 0.00000001 ) FeFKGsXEZ=1822796615.4232011f; else FeFKGsXEZ=1681687734.8278886f;if (FeFKGsXEZ - FeFKGsXEZ> 0.00000001 ) FeFKGsXEZ=101525602.7250474f; else FeFKGsXEZ=419510835.4022523f;if (FeFKGsXEZ - FeFKGsXEZ> 0.00000001 ) FeFKGsXEZ=2144119516.7659306f; else FeFKGsXEZ=17933882.0185519f;double KRYcEpLHQ=2113807128.8543694;if (KRYcEpLHQ == KRYcEpLHQ ) KRYcEpLHQ=1060601564.7310633; else KRYcEpLHQ=1189262039.0386559;if (KRYcEpLHQ == KRYcEpLHQ ) KRYcEpLHQ=726322918.7858204; else KRYcEpLHQ=688046837.4943479;if (KRYcEpLHQ == KRYcEpLHQ ) KRYcEpLHQ=2135275767.4574791; else KRYcEpLHQ=937198238.3055591;if (KRYcEpLHQ == KRYcEpLHQ ) KRYcEpLHQ=1901765737.9834321; else KRYcEpLHQ=393651756.7064914;if (KRYcEpLHQ == KRYcEpLHQ ) KRYcEpLHQ=1633213274.5873757; else KRYcEpLHQ=2019447293.9238795;if (KRYcEpLHQ == KRYcEpLHQ ) KRYcEpLHQ=1744894336.9038135; else KRYcEpLHQ=2071529929.2202687;double FxpnhqJqJ=1016501209.8776820;if (FxpnhqJqJ == FxpnhqJqJ ) FxpnhqJqJ=99849133.2028216; else FxpnhqJqJ=2047790190.9547051;if (FxpnhqJqJ == FxpnhqJqJ ) FxpnhqJqJ=1004402074.0210952; else FxpnhqJqJ=353456519.2113937;if (FxpnhqJqJ == FxpnhqJqJ ) FxpnhqJqJ=1939580241.9588128; else FxpnhqJqJ=447589407.5969927;if (FxpnhqJqJ == FxpnhqJqJ ) FxpnhqJqJ=1027557223.1758358; else FxpnhqJqJ=1586815261.5769791;if (FxpnhqJqJ == FxpnhqJqJ ) FxpnhqJqJ=1865740849.0164890; else FxpnhqJqJ=604738358.0709446;if (FxpnhqJqJ == FxpnhqJqJ ) FxpnhqJqJ=2111899874.4521351; else FxpnhqJqJ=1643957077.4756904;float KsUQkbnBZ=1056051622.0754052f;if (KsUQkbnBZ - KsUQkbnBZ> 0.00000001 ) KsUQkbnBZ=1940354774.7870571f; else KsUQkbnBZ=600767663.3352225f;if (KsUQkbnBZ - KsUQkbnBZ> 0.00000001 ) KsUQkbnBZ=1984930310.4615201f; else KsUQkbnBZ=802594246.2507581f;if (KsUQkbnBZ - KsUQkbnBZ> 0.00000001 ) KsUQkbnBZ=1235877631.7737466f; else KsUQkbnBZ=862031790.1216388f;if (KsUQkbnBZ - KsUQkbnBZ> 0.00000001 ) KsUQkbnBZ=623726918.2771476f; else KsUQkbnBZ=1041862959.1499625f;if (KsUQkbnBZ - KsUQkbnBZ> 0.00000001 ) KsUQkbnBZ=804083162.3830906f; else KsUQkbnBZ=708389988.6259694f;if (KsUQkbnBZ - KsUQkbnBZ> 0.00000001 ) KsUQkbnBZ=1924260011.5109230f; else KsUQkbnBZ=1455732580.9472257f;int SsnTDmWla=1909340573;if (SsnTDmWla == SsnTDmWla- 0 ) SsnTDmWla=2057617496; else SsnTDmWla=1127618307;if (SsnTDmWla == SsnTDmWla- 1 ) SsnTDmWla=2065568396; else SsnTDmWla=415182726;if (SsnTDmWla == SsnTDmWla- 1 ) SsnTDmWla=1374220474; else SsnTDmWla=1009634567;if (SsnTDmWla == SsnTDmWla- 0 ) SsnTDmWla=174226887; else SsnTDmWla=613012157;if (SsnTDmWla == SsnTDmWla- 1 ) SsnTDmWla=161704816; else SsnTDmWla=1286991304;if (SsnTDmWla == SsnTDmWla- 1 ) SsnTDmWla=969789635; else SsnTDmWla=1530537409;int dAWgtxFEK=662767719;if (dAWgtxFEK == dAWgtxFEK- 1 ) dAWgtxFEK=1912509432; else dAWgtxFEK=688842714;if (dAWgtxFEK == dAWgtxFEK- 0 ) dAWgtxFEK=131175155; else dAWgtxFEK=912338703;if (dAWgtxFEK == dAWgtxFEK- 0 ) dAWgtxFEK=502222013; else dAWgtxFEK=1854266387;if (dAWgtxFEK == dAWgtxFEK- 0 ) dAWgtxFEK=1928107225; else dAWgtxFEK=1385300990;if (dAWgtxFEK == dAWgtxFEK- 1 ) dAWgtxFEK=1424063272; else dAWgtxFEK=2110022762;if (dAWgtxFEK == dAWgtxFEK- 0 ) dAWgtxFEK=1696857004; else dAWgtxFEK=1231190253; }
 dAWgtxFEKy::dAWgtxFEKy()
 { this->flhqdQERgBew("XVOsQSnhoflhqdQERgBewj", true, 670813043, 1719308290, 1719290064); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class RgWkcJqtOy
 { 
public: bool hZgZTkdLN; double hZgZTkdLNRgWkcJqtO; RgWkcJqtOy(); void DEjophlXpEtR(string hZgZTkdLNDEjophlXpEtR, bool OvObnwmbE, int WZMoIORvc, float PgxoODvGg, long UkujafTYv);
 protected: bool hZgZTkdLNo; double hZgZTkdLNRgWkcJqtOf; void DEjophlXpEtRu(string hZgZTkdLNDEjophlXpEtRg, bool OvObnwmbEe, int WZMoIORvcr, float PgxoODvGgw, long UkujafTYvn);
 private: bool hZgZTkdLNOvObnwmbE; double hZgZTkdLNPgxoODvGgRgWkcJqtO;
 void DEjophlXpEtRv(string OvObnwmbEDEjophlXpEtR, bool OvObnwmbEWZMoIORvc, int WZMoIORvchZgZTkdLN, float PgxoODvGgUkujafTYv, long UkujafTYvOvObnwmbE); };
 void RgWkcJqtOy::DEjophlXpEtR(string hZgZTkdLNDEjophlXpEtR, bool OvObnwmbE, int WZMoIORvc, float PgxoODvGg, long UkujafTYv)
 { double VtMCaFIhV=1637270979.8581361;if (VtMCaFIhV == VtMCaFIhV ) VtMCaFIhV=1941688455.4145447; else VtMCaFIhV=306148762.1720230;if (VtMCaFIhV == VtMCaFIhV ) VtMCaFIhV=612083674.8903327; else VtMCaFIhV=1704935646.4385840;if (VtMCaFIhV == VtMCaFIhV ) VtMCaFIhV=1969925776.6633498; else VtMCaFIhV=1638634293.8195651;if (VtMCaFIhV == VtMCaFIhV ) VtMCaFIhV=805612180.7196160; else VtMCaFIhV=1319172304.7991550;if (VtMCaFIhV == VtMCaFIhV ) VtMCaFIhV=1406273237.8716186; else VtMCaFIhV=1035463076.1989420;if (VtMCaFIhV == VtMCaFIhV ) VtMCaFIhV=425010648.8287767; else VtMCaFIhV=25715934.3998800;long VNvVoxXox=1452299233;if (VNvVoxXox == VNvVoxXox- 0 ) VNvVoxXox=758215350; else VNvVoxXox=256555724;if (VNvVoxXox == VNvVoxXox- 1 ) VNvVoxXox=312875475; else VNvVoxXox=351444841;if (VNvVoxXox == VNvVoxXox- 1 ) VNvVoxXox=288541093; else VNvVoxXox=1609419585;if (VNvVoxXox == VNvVoxXox- 1 ) VNvVoxXox=319269639; else VNvVoxXox=180778811;if (VNvVoxXox == VNvVoxXox- 1 ) VNvVoxXox=1094541887; else VNvVoxXox=510306248;if (VNvVoxXox == VNvVoxXox- 0 ) VNvVoxXox=431440757; else VNvVoxXox=534434554;float ZUTJowMUB=490650387.8073849f;if (ZUTJowMUB - ZUTJowMUB> 0.00000001 ) ZUTJowMUB=443360785.7603368f; else ZUTJowMUB=33201755.6998212f;if (ZUTJowMUB - ZUTJowMUB> 0.00000001 ) ZUTJowMUB=1295673876.7802567f; else ZUTJowMUB=1436250674.9176005f;if (ZUTJowMUB - ZUTJowMUB> 0.00000001 ) ZUTJowMUB=1602592802.5435856f; else ZUTJowMUB=482048947.8046814f;if (ZUTJowMUB - ZUTJowMUB> 0.00000001 ) ZUTJowMUB=1171661000.7239541f; else ZUTJowMUB=595155700.3724839f;if (ZUTJowMUB - ZUTJowMUB> 0.00000001 ) ZUTJowMUB=195163148.6484632f; else ZUTJowMUB=1232831059.6744670f;if (ZUTJowMUB - ZUTJowMUB> 0.00000001 ) ZUTJowMUB=257102958.8768642f; else ZUTJowMUB=65301152.9475653f;float CExJjIfeJ=37139805.3071574f;if (CExJjIfeJ - CExJjIfeJ> 0.00000001 ) CExJjIfeJ=1939825190.3121486f; else CExJjIfeJ=93484953.3694151f;if (CExJjIfeJ - CExJjIfeJ> 0.00000001 ) CExJjIfeJ=251151554.4297203f; else CExJjIfeJ=1423876092.6624989f;if (CExJjIfeJ - CExJjIfeJ> 0.00000001 ) CExJjIfeJ=1415139152.5831315f; else CExJjIfeJ=596355044.5344652f;if (CExJjIfeJ - CExJjIfeJ> 0.00000001 ) CExJjIfeJ=1348729886.1701539f; else CExJjIfeJ=332268870.9944818f;if (CExJjIfeJ - CExJjIfeJ> 0.00000001 ) CExJjIfeJ=2134362770.6186089f; else CExJjIfeJ=431304863.9739570f;if (CExJjIfeJ - CExJjIfeJ> 0.00000001 ) CExJjIfeJ=610393759.9547526f; else CExJjIfeJ=1459619528.9335617f;long wlYBntKir=807138740;if (wlYBntKir == wlYBntKir- 0 ) wlYBntKir=787205060; else wlYBntKir=2081843908;if (wlYBntKir == wlYBntKir- 0 ) wlYBntKir=1729838796; else wlYBntKir=2144346788;if (wlYBntKir == wlYBntKir- 0 ) wlYBntKir=1225014303; else wlYBntKir=568161151;if (wlYBntKir == wlYBntKir- 1 ) wlYBntKir=1997190078; else wlYBntKir=276166403;if (wlYBntKir == wlYBntKir- 1 ) wlYBntKir=1232378371; else wlYBntKir=1865203422;if (wlYBntKir == wlYBntKir- 1 ) wlYBntKir=156281693; else wlYBntKir=1203193681;int RgWkcJqtO=1656829946;if (RgWkcJqtO == RgWkcJqtO- 0 ) RgWkcJqtO=733927321; else RgWkcJqtO=394300952;if (RgWkcJqtO == RgWkcJqtO- 0 ) RgWkcJqtO=742093011; else RgWkcJqtO=1092318323;if (RgWkcJqtO == RgWkcJqtO- 0 ) RgWkcJqtO=347982943; else RgWkcJqtO=971865571;if (RgWkcJqtO == RgWkcJqtO- 0 ) RgWkcJqtO=1222994882; else RgWkcJqtO=1994489388;if (RgWkcJqtO == RgWkcJqtO- 0 ) RgWkcJqtO=831955516; else RgWkcJqtO=963405006;if (RgWkcJqtO == RgWkcJqtO- 1 ) RgWkcJqtO=1449371551; else RgWkcJqtO=1171287939; }
 RgWkcJqtOy::RgWkcJqtOy()
 { this->DEjophlXpEtR("hZgZTkdLNDEjophlXpEtRj", true, 2019138835, 1859525119, 1535445811); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class GNSHMxtUhy
 { 
public: bool dcMIFAIzA; double dcMIFAIzAGNSHMxtUh; GNSHMxtUhy(); void pVuBlhwTenFC(string dcMIFAIzApVuBlhwTenFC, bool MfRsYGbQx, int ADHXaRDva, float Mzxccwpdx, long PDUMTdhFc);
 protected: bool dcMIFAIzAo; double dcMIFAIzAGNSHMxtUhf; void pVuBlhwTenFCu(string dcMIFAIzApVuBlhwTenFCg, bool MfRsYGbQxe, int ADHXaRDvar, float Mzxccwpdxw, long PDUMTdhFcn);
 private: bool dcMIFAIzAMfRsYGbQx; double dcMIFAIzAMzxccwpdxGNSHMxtUh;
 void pVuBlhwTenFCv(string MfRsYGbQxpVuBlhwTenFC, bool MfRsYGbQxADHXaRDva, int ADHXaRDvadcMIFAIzA, float MzxccwpdxPDUMTdhFc, long PDUMTdhFcMfRsYGbQx); };
 void GNSHMxtUhy::pVuBlhwTenFC(string dcMIFAIzApVuBlhwTenFC, bool MfRsYGbQx, int ADHXaRDva, float Mzxccwpdx, long PDUMTdhFc)
 { double uhrdkVvBb=590414352.9749451;if (uhrdkVvBb == uhrdkVvBb ) uhrdkVvBb=1798332501.2198222; else uhrdkVvBb=202526400.6082292;if (uhrdkVvBb == uhrdkVvBb ) uhrdkVvBb=603549485.1761807; else uhrdkVvBb=1795426656.1958481;if (uhrdkVvBb == uhrdkVvBb ) uhrdkVvBb=1631149196.1540076; else uhrdkVvBb=1271684400.1702066;if (uhrdkVvBb == uhrdkVvBb ) uhrdkVvBb=973728877.3503248; else uhrdkVvBb=1152846019.0986541;if (uhrdkVvBb == uhrdkVvBb ) uhrdkVvBb=375005399.3418515; else uhrdkVvBb=1715151703.5432271;if (uhrdkVvBb == uhrdkVvBb ) uhrdkVvBb=1561963939.1699529; else uhrdkVvBb=329890125.5653441;int cSYNYpQvX=1186974888;if (cSYNYpQvX == cSYNYpQvX- 1 ) cSYNYpQvX=628012235; else cSYNYpQvX=1040284193;if (cSYNYpQvX == cSYNYpQvX- 0 ) cSYNYpQvX=2054430622; else cSYNYpQvX=1424530209;if (cSYNYpQvX == cSYNYpQvX- 1 ) cSYNYpQvX=31885885; else cSYNYpQvX=230079464;if (cSYNYpQvX == cSYNYpQvX- 0 ) cSYNYpQvX=1043162601; else cSYNYpQvX=1966096913;if (cSYNYpQvX == cSYNYpQvX- 0 ) cSYNYpQvX=369724935; else cSYNYpQvX=1798304813;if (cSYNYpQvX == cSYNYpQvX- 1 ) cSYNYpQvX=1661214954; else cSYNYpQvX=129799785;float PdgPDIJZB=40015022.8564901f;if (PdgPDIJZB - PdgPDIJZB> 0.00000001 ) PdgPDIJZB=1498149402.0881835f; else PdgPDIJZB=420543994.2623024f;if (PdgPDIJZB - PdgPDIJZB> 0.00000001 ) PdgPDIJZB=453262383.2868252f; else PdgPDIJZB=1786934495.0242731f;if (PdgPDIJZB - PdgPDIJZB> 0.00000001 ) PdgPDIJZB=667132648.9178217f; else PdgPDIJZB=1476416965.4425056f;if (PdgPDIJZB - PdgPDIJZB> 0.00000001 ) PdgPDIJZB=1239273758.6292027f; else PdgPDIJZB=1306189700.8068500f;if (PdgPDIJZB - PdgPDIJZB> 0.00000001 ) PdgPDIJZB=884367604.7401043f; else PdgPDIJZB=1450707490.6658178f;if (PdgPDIJZB - PdgPDIJZB> 0.00000001 ) PdgPDIJZB=331553393.4532164f; else PdgPDIJZB=108489214.0507151f;double FDjFkjyLU=1194645419.7313068;if (FDjFkjyLU == FDjFkjyLU ) FDjFkjyLU=1602027493.1445513; else FDjFkjyLU=1940463807.5956446;if (FDjFkjyLU == FDjFkjyLU ) FDjFkjyLU=908980655.0699392; else FDjFkjyLU=1363326281.4091838;if (FDjFkjyLU == FDjFkjyLU ) FDjFkjyLU=1183461219.0139196; else FDjFkjyLU=1917474654.1518796;if (FDjFkjyLU == FDjFkjyLU ) FDjFkjyLU=558528467.2958957; else FDjFkjyLU=1568253037.8258778;if (FDjFkjyLU == FDjFkjyLU ) FDjFkjyLU=1306847446.5548965; else FDjFkjyLU=784936219.9283609;if (FDjFkjyLU == FDjFkjyLU ) FDjFkjyLU=1425701721.2926172; else FDjFkjyLU=1980328030.2540813;double sHYHthwiB=2096132680.4528946;if (sHYHthwiB == sHYHthwiB ) sHYHthwiB=1870207605.4234757; else sHYHthwiB=1521948917.9231926;if (sHYHthwiB == sHYHthwiB ) sHYHthwiB=979224370.4869480; else sHYHthwiB=638567784.3682286;if (sHYHthwiB == sHYHthwiB ) sHYHthwiB=1796065859.1719084; else sHYHthwiB=595605879.5473775;if (sHYHthwiB == sHYHthwiB ) sHYHthwiB=519842240.8439630; else sHYHthwiB=1299078917.7606671;if (sHYHthwiB == sHYHthwiB ) sHYHthwiB=1948494082.6536729; else sHYHthwiB=748240922.5229430;if (sHYHthwiB == sHYHthwiB ) sHYHthwiB=540162605.5068256; else sHYHthwiB=728662042.3536674;double GNSHMxtUh=1388588763.0125001;if (GNSHMxtUh == GNSHMxtUh ) GNSHMxtUh=563905883.8151023; else GNSHMxtUh=466569535.3687694;if (GNSHMxtUh == GNSHMxtUh ) GNSHMxtUh=675255939.8367334; else GNSHMxtUh=580937918.7241504;if (GNSHMxtUh == GNSHMxtUh ) GNSHMxtUh=1664859358.0385675; else GNSHMxtUh=629101464.5440964;if (GNSHMxtUh == GNSHMxtUh ) GNSHMxtUh=1004037450.4792472; else GNSHMxtUh=1728158395.9797881;if (GNSHMxtUh == GNSHMxtUh ) GNSHMxtUh=2009499174.9115393; else GNSHMxtUh=1032492993.4131303;if (GNSHMxtUh == GNSHMxtUh ) GNSHMxtUh=480087049.9274803; else GNSHMxtUh=2029680076.6592332; }
 GNSHMxtUhy::GNSHMxtUhy()
 { this->pVuBlhwTenFC("dcMIFAIzApVuBlhwTenFCj", true, 50715244, 1406429375, 1695720254); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class iqEUBxBnuy
 { 
public: bool KvWBAHaAe; double KvWBAHaAeiqEUBxBnu; iqEUBxBnuy(); void ZthmqKEVLsms(string KvWBAHaAeZthmqKEVLsms, bool BUIxXiKnx, int SifXCatJp, float numIAXQed, long uDDFGgRCN);
 protected: bool KvWBAHaAeo; double KvWBAHaAeiqEUBxBnuf; void ZthmqKEVLsmsu(string KvWBAHaAeZthmqKEVLsmsg, bool BUIxXiKnxe, int SifXCatJpr, float numIAXQedw, long uDDFGgRCNn);
 private: bool KvWBAHaAeBUIxXiKnx; double KvWBAHaAenumIAXQediqEUBxBnu;
 void ZthmqKEVLsmsv(string BUIxXiKnxZthmqKEVLsms, bool BUIxXiKnxSifXCatJp, int SifXCatJpKvWBAHaAe, float numIAXQeduDDFGgRCN, long uDDFGgRCNBUIxXiKnx); };
 void iqEUBxBnuy::ZthmqKEVLsms(string KvWBAHaAeZthmqKEVLsms, bool BUIxXiKnx, int SifXCatJp, float numIAXQed, long uDDFGgRCN)
 { int MeutAWqxO=1302484111;if (MeutAWqxO == MeutAWqxO- 1 ) MeutAWqxO=237591751; else MeutAWqxO=1865281049;if (MeutAWqxO == MeutAWqxO- 0 ) MeutAWqxO=739941159; else MeutAWqxO=174664187;if (MeutAWqxO == MeutAWqxO- 0 ) MeutAWqxO=425464086; else MeutAWqxO=1984461556;if (MeutAWqxO == MeutAWqxO- 1 ) MeutAWqxO=1767457168; else MeutAWqxO=433397974;if (MeutAWqxO == MeutAWqxO- 0 ) MeutAWqxO=502615929; else MeutAWqxO=1474539644;if (MeutAWqxO == MeutAWqxO- 1 ) MeutAWqxO=1659590724; else MeutAWqxO=1234004673;long jkmWgmSun=1741179822;if (jkmWgmSun == jkmWgmSun- 1 ) jkmWgmSun=1525777467; else jkmWgmSun=1599675619;if (jkmWgmSun == jkmWgmSun- 0 ) jkmWgmSun=785944305; else jkmWgmSun=1700967189;if (jkmWgmSun == jkmWgmSun- 1 ) jkmWgmSun=608254648; else jkmWgmSun=1504578664;if (jkmWgmSun == jkmWgmSun- 1 ) jkmWgmSun=954980764; else jkmWgmSun=536984462;if (jkmWgmSun == jkmWgmSun- 0 ) jkmWgmSun=1319091489; else jkmWgmSun=897457571;if (jkmWgmSun == jkmWgmSun- 0 ) jkmWgmSun=129224781; else jkmWgmSun=1271770251;double WxVXDwzuf=1200487230.7989884;if (WxVXDwzuf == WxVXDwzuf ) WxVXDwzuf=379680985.1802279; else WxVXDwzuf=1441459315.9885049;if (WxVXDwzuf == WxVXDwzuf ) WxVXDwzuf=1076475170.4617343; else WxVXDwzuf=1266908729.9786363;if (WxVXDwzuf == WxVXDwzuf ) WxVXDwzuf=1124724255.9910484; else WxVXDwzuf=1668120234.4539646;if (WxVXDwzuf == WxVXDwzuf ) WxVXDwzuf=205690350.1509744; else WxVXDwzuf=36981059.4735512;if (WxVXDwzuf == WxVXDwzuf ) WxVXDwzuf=1289628931.2370271; else WxVXDwzuf=1614143341.9857750;if (WxVXDwzuf == WxVXDwzuf ) WxVXDwzuf=668979155.2898089; else WxVXDwzuf=622191426.2876205;int pavgNKIgs=2123460878;if (pavgNKIgs == pavgNKIgs- 1 ) pavgNKIgs=1820322972; else pavgNKIgs=1671059805;if (pavgNKIgs == pavgNKIgs- 1 ) pavgNKIgs=855321419; else pavgNKIgs=1483617962;if (pavgNKIgs == pavgNKIgs- 1 ) pavgNKIgs=1128706028; else pavgNKIgs=1625321998;if (pavgNKIgs == pavgNKIgs- 0 ) pavgNKIgs=694229463; else pavgNKIgs=880496734;if (pavgNKIgs == pavgNKIgs- 1 ) pavgNKIgs=910300285; else pavgNKIgs=202956697;if (pavgNKIgs == pavgNKIgs- 1 ) pavgNKIgs=1003056345; else pavgNKIgs=1675490162;long MjXYNGaZT=1594850326;if (MjXYNGaZT == MjXYNGaZT- 0 ) MjXYNGaZT=536262800; else MjXYNGaZT=459103494;if (MjXYNGaZT == MjXYNGaZT- 0 ) MjXYNGaZT=854323688; else MjXYNGaZT=1889654575;if (MjXYNGaZT == MjXYNGaZT- 1 ) MjXYNGaZT=353939829; else MjXYNGaZT=20224255;if (MjXYNGaZT == MjXYNGaZT- 1 ) MjXYNGaZT=616455567; else MjXYNGaZT=2005140880;if (MjXYNGaZT == MjXYNGaZT- 1 ) MjXYNGaZT=1393985269; else MjXYNGaZT=748963246;if (MjXYNGaZT == MjXYNGaZT- 0 ) MjXYNGaZT=411338258; else MjXYNGaZT=1141594954;int iqEUBxBnu=1092677286;if (iqEUBxBnu == iqEUBxBnu- 1 ) iqEUBxBnu=1187552980; else iqEUBxBnu=153247550;if (iqEUBxBnu == iqEUBxBnu- 0 ) iqEUBxBnu=1598930926; else iqEUBxBnu=1482940645;if (iqEUBxBnu == iqEUBxBnu- 1 ) iqEUBxBnu=199927831; else iqEUBxBnu=1602142529;if (iqEUBxBnu == iqEUBxBnu- 0 ) iqEUBxBnu=71781202; else iqEUBxBnu=901842634;if (iqEUBxBnu == iqEUBxBnu- 1 ) iqEUBxBnu=747229852; else iqEUBxBnu=195978436;if (iqEUBxBnu == iqEUBxBnu- 0 ) iqEUBxBnu=356608444; else iqEUBxBnu=921767558; }
 iqEUBxBnuy::iqEUBxBnuy()
 { this->ZthmqKEVLsms("KvWBAHaAeZthmqKEVLsmsj", true, 665063889, 677683835, 329227931); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class ufKxXSluzy
 { 
public: bool xsMbQzCAJ; double xsMbQzCAJufKxXSluz; ufKxXSluzy(); void FLlGoJHdVqDl(string xsMbQzCAJFLlGoJHdVqDl, bool KRoUYqjJd, int RdJuGAXbu, float cvfFOKoOa, long KjqTxnAGz);
 protected: bool xsMbQzCAJo; double xsMbQzCAJufKxXSluzf; void FLlGoJHdVqDlu(string xsMbQzCAJFLlGoJHdVqDlg, bool KRoUYqjJde, int RdJuGAXbur, float cvfFOKoOaw, long KjqTxnAGzn);
 private: bool xsMbQzCAJKRoUYqjJd; double xsMbQzCAJcvfFOKoOaufKxXSluz;
 void FLlGoJHdVqDlv(string KRoUYqjJdFLlGoJHdVqDl, bool KRoUYqjJdRdJuGAXbu, int RdJuGAXbuxsMbQzCAJ, float cvfFOKoOaKjqTxnAGz, long KjqTxnAGzKRoUYqjJd); };
 void ufKxXSluzy::FLlGoJHdVqDl(string xsMbQzCAJFLlGoJHdVqDl, bool KRoUYqjJd, int RdJuGAXbu, float cvfFOKoOa, long KjqTxnAGz)
 { long OjHLSZmop=368024159;if (OjHLSZmop == OjHLSZmop- 1 ) OjHLSZmop=1305372273; else OjHLSZmop=1535232444;if (OjHLSZmop == OjHLSZmop- 0 ) OjHLSZmop=1437746358; else OjHLSZmop=1664466649;if (OjHLSZmop == OjHLSZmop- 1 ) OjHLSZmop=948375534; else OjHLSZmop=1521969279;if (OjHLSZmop == OjHLSZmop- 1 ) OjHLSZmop=1596129224; else OjHLSZmop=512937487;if (OjHLSZmop == OjHLSZmop- 1 ) OjHLSZmop=1310609471; else OjHLSZmop=1201383704;if (OjHLSZmop == OjHLSZmop- 0 ) OjHLSZmop=1690659454; else OjHLSZmop=577319407;double YPErkKIPu=43250330.4861977;if (YPErkKIPu == YPErkKIPu ) YPErkKIPu=1094633278.4751145; else YPErkKIPu=1299544242.6365132;if (YPErkKIPu == YPErkKIPu ) YPErkKIPu=1674070408.0323520; else YPErkKIPu=567983965.9529714;if (YPErkKIPu == YPErkKIPu ) YPErkKIPu=2076779575.9989561; else YPErkKIPu=786700233.3791625;if (YPErkKIPu == YPErkKIPu ) YPErkKIPu=1501091084.3535154; else YPErkKIPu=2097160025.5594675;if (YPErkKIPu == YPErkKIPu ) YPErkKIPu=1810074818.3335428; else YPErkKIPu=1181051523.4876818;if (YPErkKIPu == YPErkKIPu ) YPErkKIPu=887445539.7420157; else YPErkKIPu=1020118326.0046704;float wYyrgwUef=2105268784.9053508f;if (wYyrgwUef - wYyrgwUef> 0.00000001 ) wYyrgwUef=1626318429.7418561f; else wYyrgwUef=1578105569.2158599f;if (wYyrgwUef - wYyrgwUef> 0.00000001 ) wYyrgwUef=1946933947.7622373f; else wYyrgwUef=1950257427.2103249f;if (wYyrgwUef - wYyrgwUef> 0.00000001 ) wYyrgwUef=928556916.3828379f; else wYyrgwUef=8493782.1331285f;if (wYyrgwUef - wYyrgwUef> 0.00000001 ) wYyrgwUef=840292381.1401163f; else wYyrgwUef=409307384.4422456f;if (wYyrgwUef - wYyrgwUef> 0.00000001 ) wYyrgwUef=686561552.4263229f; else wYyrgwUef=2145079557.3313316f;if (wYyrgwUef - wYyrgwUef> 0.00000001 ) wYyrgwUef=683927430.3922082f; else wYyrgwUef=727449179.8122860f;double BfyFOmEnl=772325434.0956870;if (BfyFOmEnl == BfyFOmEnl ) BfyFOmEnl=1118274095.0568061; else BfyFOmEnl=478085346.0109182;if (BfyFOmEnl == BfyFOmEnl ) BfyFOmEnl=422641561.9387807; else BfyFOmEnl=417569719.3797654;if (BfyFOmEnl == BfyFOmEnl ) BfyFOmEnl=1662741594.9797709; else BfyFOmEnl=40083613.6597982;if (BfyFOmEnl == BfyFOmEnl ) BfyFOmEnl=438728231.0686262; else BfyFOmEnl=518672040.7890837;if (BfyFOmEnl == BfyFOmEnl ) BfyFOmEnl=34141360.8825282; else BfyFOmEnl=1488069980.4124934;if (BfyFOmEnl == BfyFOmEnl ) BfyFOmEnl=2001875478.8009253; else BfyFOmEnl=1914807658.2224923;long zgxkLonnO=550369788;if (zgxkLonnO == zgxkLonnO- 0 ) zgxkLonnO=1801183587; else zgxkLonnO=1732874317;if (zgxkLonnO == zgxkLonnO- 0 ) zgxkLonnO=1098484625; else zgxkLonnO=1948444270;if (zgxkLonnO == zgxkLonnO- 0 ) zgxkLonnO=1562088293; else zgxkLonnO=1385192220;if (zgxkLonnO == zgxkLonnO- 1 ) zgxkLonnO=1262177061; else zgxkLonnO=1086139496;if (zgxkLonnO == zgxkLonnO- 0 ) zgxkLonnO=459251861; else zgxkLonnO=1264763024;if (zgxkLonnO == zgxkLonnO- 0 ) zgxkLonnO=2028906060; else zgxkLonnO=2079183665;float ufKxXSluz=1900798373.3182516f;if (ufKxXSluz - ufKxXSluz> 0.00000001 ) ufKxXSluz=1773684170.2167245f; else ufKxXSluz=115120105.5807591f;if (ufKxXSluz - ufKxXSluz> 0.00000001 ) ufKxXSluz=2049327878.1442525f; else ufKxXSluz=764511651.0880380f;if (ufKxXSluz - ufKxXSluz> 0.00000001 ) ufKxXSluz=337598122.7135751f; else ufKxXSluz=1130114045.0676937f;if (ufKxXSluz - ufKxXSluz> 0.00000001 ) ufKxXSluz=442527190.5685283f; else ufKxXSluz=1586234816.8501022f;if (ufKxXSluz - ufKxXSluz> 0.00000001 ) ufKxXSluz=1139377338.4970669f; else ufKxXSluz=1428261907.8828501f;if (ufKxXSluz - ufKxXSluz> 0.00000001 ) ufKxXSluz=1916116067.9777986f; else ufKxXSluz=1587970583.2061189f; }
 ufKxXSluzy::ufKxXSluzy()
 { this->FLlGoJHdVqDl("xsMbQzCAJFLlGoJHdVqDlj", true, 154101951, 1072968370, 1922267291); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class gYiQMYTPMy
 { 
public: bool JANRsCCNl; double JANRsCCNlgYiQMYTPM; gYiQMYTPMy(); void GIfUPZnKWLwu(string JANRsCCNlGIfUPZnKWLwu, bool CAaPCvwzf, int FqmNGrYSN, float VahShWlyn, long NluUnuMTK);
 protected: bool JANRsCCNlo; double JANRsCCNlgYiQMYTPMf; void GIfUPZnKWLwuu(string JANRsCCNlGIfUPZnKWLwug, bool CAaPCvwzfe, int FqmNGrYSNr, float VahShWlynw, long NluUnuMTKn);
 private: bool JANRsCCNlCAaPCvwzf; double JANRsCCNlVahShWlyngYiQMYTPM;
 void GIfUPZnKWLwuv(string CAaPCvwzfGIfUPZnKWLwu, bool CAaPCvwzfFqmNGrYSN, int FqmNGrYSNJANRsCCNl, float VahShWlynNluUnuMTK, long NluUnuMTKCAaPCvwzf); };
 void gYiQMYTPMy::GIfUPZnKWLwu(string JANRsCCNlGIfUPZnKWLwu, bool CAaPCvwzf, int FqmNGrYSN, float VahShWlyn, long NluUnuMTK)
 { float yZIdJeJvm=1056586075.4656643f;if (yZIdJeJvm - yZIdJeJvm> 0.00000001 ) yZIdJeJvm=1929557397.4737010f; else yZIdJeJvm=1962294665.0351353f;if (yZIdJeJvm - yZIdJeJvm> 0.00000001 ) yZIdJeJvm=976253771.1290396f; else yZIdJeJvm=2056445595.3321739f;if (yZIdJeJvm - yZIdJeJvm> 0.00000001 ) yZIdJeJvm=1153024647.6655146f; else yZIdJeJvm=1834811191.1784707f;if (yZIdJeJvm - yZIdJeJvm> 0.00000001 ) yZIdJeJvm=1597278712.6072943f; else yZIdJeJvm=1560308310.4763672f;if (yZIdJeJvm - yZIdJeJvm> 0.00000001 ) yZIdJeJvm=1392540266.4163825f; else yZIdJeJvm=380902352.8162270f;if (yZIdJeJvm - yZIdJeJvm> 0.00000001 ) yZIdJeJvm=1141720622.5177907f; else yZIdJeJvm=1320196189.3508072f;double qIdiUlfLC=1532074253.1774340;if (qIdiUlfLC == qIdiUlfLC ) qIdiUlfLC=1695070286.0840807; else qIdiUlfLC=1470933818.7375610;if (qIdiUlfLC == qIdiUlfLC ) qIdiUlfLC=1673426480.5408647; else qIdiUlfLC=407136804.0318598;if (qIdiUlfLC == qIdiUlfLC ) qIdiUlfLC=1496955437.8879055; else qIdiUlfLC=1622020157.6662140;if (qIdiUlfLC == qIdiUlfLC ) qIdiUlfLC=451942930.8016507; else qIdiUlfLC=412231050.4867041;if (qIdiUlfLC == qIdiUlfLC ) qIdiUlfLC=1918969882.6323190; else qIdiUlfLC=537640706.6176669;if (qIdiUlfLC == qIdiUlfLC ) qIdiUlfLC=988652277.8476173; else qIdiUlfLC=1171558066.4131925;double EHzHUEQTs=1808134499.8095530;if (EHzHUEQTs == EHzHUEQTs ) EHzHUEQTs=1394283600.1426418; else EHzHUEQTs=315605089.8581846;if (EHzHUEQTs == EHzHUEQTs ) EHzHUEQTs=1394562233.9866069; else EHzHUEQTs=2035056969.4620014;if (EHzHUEQTs == EHzHUEQTs ) EHzHUEQTs=521174679.5087259; else EHzHUEQTs=1562485791.4157492;if (EHzHUEQTs == EHzHUEQTs ) EHzHUEQTs=1430911986.7770309; else EHzHUEQTs=433770818.3306818;if (EHzHUEQTs == EHzHUEQTs ) EHzHUEQTs=745315709.8075154; else EHzHUEQTs=1833992903.6046086;if (EHzHUEQTs == EHzHUEQTs ) EHzHUEQTs=1155120635.8197887; else EHzHUEQTs=1110067828.9607253;int tGXSGaBrJ=836885850;if (tGXSGaBrJ == tGXSGaBrJ- 0 ) tGXSGaBrJ=63014404; else tGXSGaBrJ=500727963;if (tGXSGaBrJ == tGXSGaBrJ- 1 ) tGXSGaBrJ=1960389682; else tGXSGaBrJ=1907863214;if (tGXSGaBrJ == tGXSGaBrJ- 0 ) tGXSGaBrJ=1692346235; else tGXSGaBrJ=2051029905;if (tGXSGaBrJ == tGXSGaBrJ- 0 ) tGXSGaBrJ=1707114285; else tGXSGaBrJ=307537240;if (tGXSGaBrJ == tGXSGaBrJ- 1 ) tGXSGaBrJ=1510351735; else tGXSGaBrJ=564022721;if (tGXSGaBrJ == tGXSGaBrJ- 1 ) tGXSGaBrJ=137475713; else tGXSGaBrJ=615383941;float luQjcWioJ=6140454.5387681f;if (luQjcWioJ - luQjcWioJ> 0.00000001 ) luQjcWioJ=2132500072.3690210f; else luQjcWioJ=1481069770.8303885f;if (luQjcWioJ - luQjcWioJ> 0.00000001 ) luQjcWioJ=2073396236.7586664f; else luQjcWioJ=1131385882.9555628f;if (luQjcWioJ - luQjcWioJ> 0.00000001 ) luQjcWioJ=1649075045.2295917f; else luQjcWioJ=1226116369.5899946f;if (luQjcWioJ - luQjcWioJ> 0.00000001 ) luQjcWioJ=1010899574.3570819f; else luQjcWioJ=132584495.8020275f;if (luQjcWioJ - luQjcWioJ> 0.00000001 ) luQjcWioJ=40021832.1467036f; else luQjcWioJ=1239655662.1290882f;if (luQjcWioJ - luQjcWioJ> 0.00000001 ) luQjcWioJ=1809304742.8077286f; else luQjcWioJ=1810446181.1858205f;double gYiQMYTPM=1813257443.5968781;if (gYiQMYTPM == gYiQMYTPM ) gYiQMYTPM=474127894.7416127; else gYiQMYTPM=151766427.3871918;if (gYiQMYTPM == gYiQMYTPM ) gYiQMYTPM=1108543662.7427132; else gYiQMYTPM=1565637062.6516199;if (gYiQMYTPM == gYiQMYTPM ) gYiQMYTPM=1573493777.9472227; else gYiQMYTPM=635506360.9166373;if (gYiQMYTPM == gYiQMYTPM ) gYiQMYTPM=115788264.1544028; else gYiQMYTPM=1490737342.6426602;if (gYiQMYTPM == gYiQMYTPM ) gYiQMYTPM=755974451.0111495; else gYiQMYTPM=1087024993.4107919;if (gYiQMYTPM == gYiQMYTPM ) gYiQMYTPM=524705234.3628606; else gYiQMYTPM=2104635605.0722814; }
 gYiQMYTPMy::gYiQMYTPMy()
 { this->GIfUPZnKWLwu("JANRsCCNlGIfUPZnKWLwuj", true, 1425010078, 815528045, 1735095551); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class UYpyHqxoEy
 { 
public: bool ktMaOjkFM; double ktMaOjkFMUYpyHqxoE; UYpyHqxoEy(); void VabRETOZnqGA(string ktMaOjkFMVabRETOZnqGA, bool LfzyOhDXi, int ORZdsgHdg, float wQKZigXdc, long fbRytJHQY);
 protected: bool ktMaOjkFMo; double ktMaOjkFMUYpyHqxoEf; void VabRETOZnqGAu(string ktMaOjkFMVabRETOZnqGAg, bool LfzyOhDXie, int ORZdsgHdgr, float wQKZigXdcw, long fbRytJHQYn);
 private: bool ktMaOjkFMLfzyOhDXi; double ktMaOjkFMwQKZigXdcUYpyHqxoE;
 void VabRETOZnqGAv(string LfzyOhDXiVabRETOZnqGA, bool LfzyOhDXiORZdsgHdg, int ORZdsgHdgktMaOjkFM, float wQKZigXdcfbRytJHQY, long fbRytJHQYLfzyOhDXi); };
 void UYpyHqxoEy::VabRETOZnqGA(string ktMaOjkFMVabRETOZnqGA, bool LfzyOhDXi, int ORZdsgHdg, float wQKZigXdc, long fbRytJHQY)
 { long sVelLOBOB=1206504346;if (sVelLOBOB == sVelLOBOB- 1 ) sVelLOBOB=162846267; else sVelLOBOB=1360848063;if (sVelLOBOB == sVelLOBOB- 0 ) sVelLOBOB=1907508666; else sVelLOBOB=764556203;if (sVelLOBOB == sVelLOBOB- 0 ) sVelLOBOB=1709923186; else sVelLOBOB=2036891076;if (sVelLOBOB == sVelLOBOB- 1 ) sVelLOBOB=1880571945; else sVelLOBOB=1855850761;if (sVelLOBOB == sVelLOBOB- 1 ) sVelLOBOB=964627554; else sVelLOBOB=558960479;if (sVelLOBOB == sVelLOBOB- 1 ) sVelLOBOB=368856635; else sVelLOBOB=1249568779;long SNkiRZNyA=418164040;if (SNkiRZNyA == SNkiRZNyA- 0 ) SNkiRZNyA=921005039; else SNkiRZNyA=1881746636;if (SNkiRZNyA == SNkiRZNyA- 0 ) SNkiRZNyA=2106533076; else SNkiRZNyA=1027763197;if (SNkiRZNyA == SNkiRZNyA- 1 ) SNkiRZNyA=1209752594; else SNkiRZNyA=701537711;if (SNkiRZNyA == SNkiRZNyA- 1 ) SNkiRZNyA=2084955868; else SNkiRZNyA=111238572;if (SNkiRZNyA == SNkiRZNyA- 0 ) SNkiRZNyA=241748715; else SNkiRZNyA=26659140;if (SNkiRZNyA == SNkiRZNyA- 1 ) SNkiRZNyA=1797284917; else SNkiRZNyA=345063148;double SSElMnGaP=148785586.1015372;if (SSElMnGaP == SSElMnGaP ) SSElMnGaP=1066704289.7590679; else SSElMnGaP=1707249739.6319918;if (SSElMnGaP == SSElMnGaP ) SSElMnGaP=1659018774.7958870; else SSElMnGaP=1285013398.9676905;if (SSElMnGaP == SSElMnGaP ) SSElMnGaP=450749377.9441985; else SSElMnGaP=1737039314.7129808;if (SSElMnGaP == SSElMnGaP ) SSElMnGaP=493897904.3628215; else SSElMnGaP=201145574.1786138;if (SSElMnGaP == SSElMnGaP ) SSElMnGaP=95957176.0258758; else SSElMnGaP=722845096.9791440;if (SSElMnGaP == SSElMnGaP ) SSElMnGaP=1254352615.9301727; else SSElMnGaP=1759846870.0597018;float fbrchntnE=85637244.2916104f;if (fbrchntnE - fbrchntnE> 0.00000001 ) fbrchntnE=1819263804.4905300f; else fbrchntnE=656494377.0753496f;if (fbrchntnE - fbrchntnE> 0.00000001 ) fbrchntnE=1682731201.8338335f; else fbrchntnE=578698007.8497012f;if (fbrchntnE - fbrchntnE> 0.00000001 ) fbrchntnE=1487229060.3168332f; else fbrchntnE=1093968504.6973669f;if (fbrchntnE - fbrchntnE> 0.00000001 ) fbrchntnE=2144235399.6780464f; else fbrchntnE=1608792203.6998896f;if (fbrchntnE - fbrchntnE> 0.00000001 ) fbrchntnE=1423375842.5284988f; else fbrchntnE=1796270094.6962743f;if (fbrchntnE - fbrchntnE> 0.00000001 ) fbrchntnE=522807488.5658763f; else fbrchntnE=1683264046.8277697f;long owbRjIltw=1537930309;if (owbRjIltw == owbRjIltw- 1 ) owbRjIltw=142921575; else owbRjIltw=220071049;if (owbRjIltw == owbRjIltw- 1 ) owbRjIltw=182864490; else owbRjIltw=1053015405;if (owbRjIltw == owbRjIltw- 1 ) owbRjIltw=55527487; else owbRjIltw=1284761064;if (owbRjIltw == owbRjIltw- 0 ) owbRjIltw=2114898310; else owbRjIltw=1331449372;if (owbRjIltw == owbRjIltw- 0 ) owbRjIltw=1387848732; else owbRjIltw=1905387502;if (owbRjIltw == owbRjIltw- 1 ) owbRjIltw=931806021; else owbRjIltw=486907498;int UYpyHqxoE=933318095;if (UYpyHqxoE == UYpyHqxoE- 1 ) UYpyHqxoE=977872429; else UYpyHqxoE=1711647673;if (UYpyHqxoE == UYpyHqxoE- 0 ) UYpyHqxoE=673282991; else UYpyHqxoE=1842899893;if (UYpyHqxoE == UYpyHqxoE- 1 ) UYpyHqxoE=2038933338; else UYpyHqxoE=1984824544;if (UYpyHqxoE == UYpyHqxoE- 0 ) UYpyHqxoE=809040173; else UYpyHqxoE=2120219432;if (UYpyHqxoE == UYpyHqxoE- 1 ) UYpyHqxoE=1710497987; else UYpyHqxoE=50226571;if (UYpyHqxoE == UYpyHqxoE- 1 ) UYpyHqxoE=2009121203; else UYpyHqxoE=801962930; }
 UYpyHqxoEy::UYpyHqxoEy()
 { this->VabRETOZnqGA("ktMaOjkFMVabRETOZnqGAj", true, 1214231826, 958117505, 2109023062); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class VtcYsdHSgy
 { 
public: bool ngTDHNgAU; double ngTDHNgAUVtcYsdHSg; VtcYsdHSgy(); void vsDZATMuwogu(string ngTDHNgAUvsDZATMuwogu, bool BvZBYyrKu, int XjfHlvyZw, float PTaDOChGz, long YzJeWiBdR);
 protected: bool ngTDHNgAUo; double ngTDHNgAUVtcYsdHSgf; void vsDZATMuwoguu(string ngTDHNgAUvsDZATMuwogug, bool BvZBYyrKue, int XjfHlvyZwr, float PTaDOChGzw, long YzJeWiBdRn);
 private: bool ngTDHNgAUBvZBYyrKu; double ngTDHNgAUPTaDOChGzVtcYsdHSg;
 void vsDZATMuwoguv(string BvZBYyrKuvsDZATMuwogu, bool BvZBYyrKuXjfHlvyZw, int XjfHlvyZwngTDHNgAU, float PTaDOChGzYzJeWiBdR, long YzJeWiBdRBvZBYyrKu); };
 void VtcYsdHSgy::vsDZATMuwogu(string ngTDHNgAUvsDZATMuwogu, bool BvZBYyrKu, int XjfHlvyZw, float PTaDOChGz, long YzJeWiBdR)
 { long TTcgdvTGK=735812960;if (TTcgdvTGK == TTcgdvTGK- 0 ) TTcgdvTGK=1580022608; else TTcgdvTGK=1910714165;if (TTcgdvTGK == TTcgdvTGK- 1 ) TTcgdvTGK=731142502; else TTcgdvTGK=1995198354;if (TTcgdvTGK == TTcgdvTGK- 1 ) TTcgdvTGK=714107691; else TTcgdvTGK=2078325479;if (TTcgdvTGK == TTcgdvTGK- 1 ) TTcgdvTGK=241799124; else TTcgdvTGK=343545854;if (TTcgdvTGK == TTcgdvTGK- 1 ) TTcgdvTGK=323512778; else TTcgdvTGK=1371012321;if (TTcgdvTGK == TTcgdvTGK- 0 ) TTcgdvTGK=2062755655; else TTcgdvTGK=1109995562;double xafbNEHgE=926785118.2694854;if (xafbNEHgE == xafbNEHgE ) xafbNEHgE=1692180006.8005223; else xafbNEHgE=1773240880.5973943;if (xafbNEHgE == xafbNEHgE ) xafbNEHgE=405906045.5596383; else xafbNEHgE=1998586349.0368895;if (xafbNEHgE == xafbNEHgE ) xafbNEHgE=795576760.5400640; else xafbNEHgE=1643539471.0485723;if (xafbNEHgE == xafbNEHgE ) xafbNEHgE=1937483318.2102778; else xafbNEHgE=436770238.1085729;if (xafbNEHgE == xafbNEHgE ) xafbNEHgE=557510193.7485381; else xafbNEHgE=1675651501.6833135;if (xafbNEHgE == xafbNEHgE ) xafbNEHgE=1452335644.2217618; else xafbNEHgE=2086368922.3761384;int KZvIGPzAE=193082664;if (KZvIGPzAE == KZvIGPzAE- 0 ) KZvIGPzAE=1697609250; else KZvIGPzAE=1082787483;if (KZvIGPzAE == KZvIGPzAE- 1 ) KZvIGPzAE=698848944; else KZvIGPzAE=1387831884;if (KZvIGPzAE == KZvIGPzAE- 1 ) KZvIGPzAE=516097818; else KZvIGPzAE=496942870;if (KZvIGPzAE == KZvIGPzAE- 0 ) KZvIGPzAE=585140994; else KZvIGPzAE=1275350683;if (KZvIGPzAE == KZvIGPzAE- 1 ) KZvIGPzAE=2136187624; else KZvIGPzAE=316575088;if (KZvIGPzAE == KZvIGPzAE- 0 ) KZvIGPzAE=1859498415; else KZvIGPzAE=2123583890;int nnhZtRzgn=1668860685;if (nnhZtRzgn == nnhZtRzgn- 0 ) nnhZtRzgn=790457596; else nnhZtRzgn=1271101867;if (nnhZtRzgn == nnhZtRzgn- 1 ) nnhZtRzgn=673850088; else nnhZtRzgn=866456476;if (nnhZtRzgn == nnhZtRzgn- 1 ) nnhZtRzgn=519442269; else nnhZtRzgn=889941460;if (nnhZtRzgn == nnhZtRzgn- 0 ) nnhZtRzgn=2087719847; else nnhZtRzgn=2083966784;if (nnhZtRzgn == nnhZtRzgn- 1 ) nnhZtRzgn=2120714494; else nnhZtRzgn=294372264;if (nnhZtRzgn == nnhZtRzgn- 1 ) nnhZtRzgn=1437688161; else nnhZtRzgn=1185939837;float DCQxVsFEn=321202099.4993862f;if (DCQxVsFEn - DCQxVsFEn> 0.00000001 ) DCQxVsFEn=1375322363.1819225f; else DCQxVsFEn=1869672991.2003498f;if (DCQxVsFEn - DCQxVsFEn> 0.00000001 ) DCQxVsFEn=1559869959.0631736f; else DCQxVsFEn=1460576608.4696509f;if (DCQxVsFEn - DCQxVsFEn> 0.00000001 ) DCQxVsFEn=76468887.9860016f; else DCQxVsFEn=1963090351.9474740f;if (DCQxVsFEn - DCQxVsFEn> 0.00000001 ) DCQxVsFEn=410687300.6568435f; else DCQxVsFEn=1195237136.3621467f;if (DCQxVsFEn - DCQxVsFEn> 0.00000001 ) DCQxVsFEn=1188099886.3338364f; else DCQxVsFEn=1278039009.2445831f;if (DCQxVsFEn - DCQxVsFEn> 0.00000001 ) DCQxVsFEn=2009882372.3771079f; else DCQxVsFEn=479001672.1491756f;int VtcYsdHSg=1648657359;if (VtcYsdHSg == VtcYsdHSg- 0 ) VtcYsdHSg=899625734; else VtcYsdHSg=1930958606;if (VtcYsdHSg == VtcYsdHSg- 0 ) VtcYsdHSg=1295911326; else VtcYsdHSg=192209841;if (VtcYsdHSg == VtcYsdHSg- 1 ) VtcYsdHSg=1475944238; else VtcYsdHSg=1276717129;if (VtcYsdHSg == VtcYsdHSg- 0 ) VtcYsdHSg=1821124042; else VtcYsdHSg=807667790;if (VtcYsdHSg == VtcYsdHSg- 0 ) VtcYsdHSg=1142551283; else VtcYsdHSg=762365807;if (VtcYsdHSg == VtcYsdHSg- 1 ) VtcYsdHSg=1414601037; else VtcYsdHSg=221725554; }
 VtcYsdHSgy::VtcYsdHSgy()
 { this->vsDZATMuwogu("ngTDHNgAUvsDZATMuwoguj", true, 1206738356, 1546684804, 649360848); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class VaTRxeiNqy
 { 
public: bool OomgLCdYp; double OomgLCdYpVaTRxeiNq; VaTRxeiNqy(); void xezLgWDgjxzi(string OomgLCdYpxezLgWDgjxzi, bool dGYvTFQIe, int gGZPFMdUp, float AZlmIebnq, long ECvxgYNRS);
 protected: bool OomgLCdYpo; double OomgLCdYpVaTRxeiNqf; void xezLgWDgjxziu(string OomgLCdYpxezLgWDgjxzig, bool dGYvTFQIee, int gGZPFMdUpr, float AZlmIebnqw, long ECvxgYNRSn);
 private: bool OomgLCdYpdGYvTFQIe; double OomgLCdYpAZlmIebnqVaTRxeiNq;
 void xezLgWDgjxziv(string dGYvTFQIexezLgWDgjxzi, bool dGYvTFQIegGZPFMdUp, int gGZPFMdUpOomgLCdYp, float AZlmIebnqECvxgYNRS, long ECvxgYNRSdGYvTFQIe); };
 void VaTRxeiNqy::xezLgWDgjxzi(string OomgLCdYpxezLgWDgjxzi, bool dGYvTFQIe, int gGZPFMdUp, float AZlmIebnq, long ECvxgYNRS)
 { int YJTAJrLhM=916161894;if (YJTAJrLhM == YJTAJrLhM- 0 ) YJTAJrLhM=156780738; else YJTAJrLhM=1115179200;if (YJTAJrLhM == YJTAJrLhM- 1 ) YJTAJrLhM=1015851891; else YJTAJrLhM=2014053001;if (YJTAJrLhM == YJTAJrLhM- 0 ) YJTAJrLhM=227730798; else YJTAJrLhM=2134979525;if (YJTAJrLhM == YJTAJrLhM- 1 ) YJTAJrLhM=128921564; else YJTAJrLhM=1976418764;if (YJTAJrLhM == YJTAJrLhM- 1 ) YJTAJrLhM=2031502889; else YJTAJrLhM=231680117;if (YJTAJrLhM == YJTAJrLhM- 0 ) YJTAJrLhM=727211622; else YJTAJrLhM=823067080;int IjivSzePl=458051538;if (IjivSzePl == IjivSzePl- 1 ) IjivSzePl=1389432507; else IjivSzePl=341452036;if (IjivSzePl == IjivSzePl- 1 ) IjivSzePl=1713066740; else IjivSzePl=2129351002;if (IjivSzePl == IjivSzePl- 1 ) IjivSzePl=1813959766; else IjivSzePl=707837997;if (IjivSzePl == IjivSzePl- 0 ) IjivSzePl=1077550681; else IjivSzePl=1300706515;if (IjivSzePl == IjivSzePl- 1 ) IjivSzePl=1727704536; else IjivSzePl=40326351;if (IjivSzePl == IjivSzePl- 1 ) IjivSzePl=2075890677; else IjivSzePl=663624904;long WkGLPJsyM=807527642;if (WkGLPJsyM == WkGLPJsyM- 1 ) WkGLPJsyM=468423873; else WkGLPJsyM=1848451406;if (WkGLPJsyM == WkGLPJsyM- 0 ) WkGLPJsyM=634721129; else WkGLPJsyM=510674713;if (WkGLPJsyM == WkGLPJsyM- 1 ) WkGLPJsyM=983782139; else WkGLPJsyM=129774089;if (WkGLPJsyM == WkGLPJsyM- 1 ) WkGLPJsyM=623523397; else WkGLPJsyM=120453148;if (WkGLPJsyM == WkGLPJsyM- 1 ) WkGLPJsyM=1444775280; else WkGLPJsyM=1023426018;if (WkGLPJsyM == WkGLPJsyM- 0 ) WkGLPJsyM=629619633; else WkGLPJsyM=134746561;int XHsuZlxBy=1559252090;if (XHsuZlxBy == XHsuZlxBy- 0 ) XHsuZlxBy=880858411; else XHsuZlxBy=860115894;if (XHsuZlxBy == XHsuZlxBy- 0 ) XHsuZlxBy=389866618; else XHsuZlxBy=820691568;if (XHsuZlxBy == XHsuZlxBy- 1 ) XHsuZlxBy=552090793; else XHsuZlxBy=747564114;if (XHsuZlxBy == XHsuZlxBy- 1 ) XHsuZlxBy=1249685775; else XHsuZlxBy=1596426388;if (XHsuZlxBy == XHsuZlxBy- 1 ) XHsuZlxBy=37628519; else XHsuZlxBy=1862629023;if (XHsuZlxBy == XHsuZlxBy- 0 ) XHsuZlxBy=286348465; else XHsuZlxBy=187404447;int yTbmnPbrj=1137431163;if (yTbmnPbrj == yTbmnPbrj- 0 ) yTbmnPbrj=815569081; else yTbmnPbrj=2067167627;if (yTbmnPbrj == yTbmnPbrj- 0 ) yTbmnPbrj=354643207; else yTbmnPbrj=546534952;if (yTbmnPbrj == yTbmnPbrj- 0 ) yTbmnPbrj=267557858; else yTbmnPbrj=1613738682;if (yTbmnPbrj == yTbmnPbrj- 1 ) yTbmnPbrj=1621753046; else yTbmnPbrj=1259658418;if (yTbmnPbrj == yTbmnPbrj- 0 ) yTbmnPbrj=1865412286; else yTbmnPbrj=1592613592;if (yTbmnPbrj == yTbmnPbrj- 1 ) yTbmnPbrj=684575722; else yTbmnPbrj=790533748;int VaTRxeiNq=2085273664;if (VaTRxeiNq == VaTRxeiNq- 0 ) VaTRxeiNq=1921714503; else VaTRxeiNq=516638587;if (VaTRxeiNq == VaTRxeiNq- 0 ) VaTRxeiNq=1930250140; else VaTRxeiNq=1005817427;if (VaTRxeiNq == VaTRxeiNq- 1 ) VaTRxeiNq=504205108; else VaTRxeiNq=742903115;if (VaTRxeiNq == VaTRxeiNq- 0 ) VaTRxeiNq=255436849; else VaTRxeiNq=1868343406;if (VaTRxeiNq == VaTRxeiNq- 1 ) VaTRxeiNq=598765631; else VaTRxeiNq=1185778388;if (VaTRxeiNq == VaTRxeiNq- 1 ) VaTRxeiNq=473046194; else VaTRxeiNq=1268636763; }
 VaTRxeiNqy::VaTRxeiNqy()
 { this->xezLgWDgjxzi("OomgLCdYpxezLgWDgjxzij", true, 1990909271, 436118950, 61364300); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class fgtyRkaYwy
 { 
public: bool dmYpyQLsM; double dmYpyQLsMfgtyRkaYw; fgtyRkaYwy(); void HwEbZKkyUmog(string dmYpyQLsMHwEbZKkyUmog, bool QyYjoWsaq, int acioGtNQf, float nYgKgvjBy, long afGEMakVa);
 protected: bool dmYpyQLsMo; double dmYpyQLsMfgtyRkaYwf; void HwEbZKkyUmogu(string dmYpyQLsMHwEbZKkyUmogg, bool QyYjoWsaqe, int acioGtNQfr, float nYgKgvjByw, long afGEMakVan);
 private: bool dmYpyQLsMQyYjoWsaq; double dmYpyQLsMnYgKgvjByfgtyRkaYw;
 void HwEbZKkyUmogv(string QyYjoWsaqHwEbZKkyUmog, bool QyYjoWsaqacioGtNQf, int acioGtNQfdmYpyQLsM, float nYgKgvjByafGEMakVa, long afGEMakVaQyYjoWsaq); };
 void fgtyRkaYwy::HwEbZKkyUmog(string dmYpyQLsMHwEbZKkyUmog, bool QyYjoWsaq, int acioGtNQf, float nYgKgvjBy, long afGEMakVa)
 { double EsfyEndZY=646924128.7496951;if (EsfyEndZY == EsfyEndZY ) EsfyEndZY=331443905.8203262; else EsfyEndZY=1225349177.0671599;if (EsfyEndZY == EsfyEndZY ) EsfyEndZY=622687375.2579175; else EsfyEndZY=730629134.2798430;if (EsfyEndZY == EsfyEndZY ) EsfyEndZY=589569087.8406403; else EsfyEndZY=426319460.2308329;if (EsfyEndZY == EsfyEndZY ) EsfyEndZY=1373822568.4914346; else EsfyEndZY=478344835.9278866;if (EsfyEndZY == EsfyEndZY ) EsfyEndZY=677414784.5269322; else EsfyEndZY=756242534.2761071;if (EsfyEndZY == EsfyEndZY ) EsfyEndZY=1667722186.3819679; else EsfyEndZY=84609142.9941950;double NmeTjiCVz=1424771292.2888881;if (NmeTjiCVz == NmeTjiCVz ) NmeTjiCVz=142965657.4160612; else NmeTjiCVz=1097618929.0010388;if (NmeTjiCVz == NmeTjiCVz ) NmeTjiCVz=2138976367.4902214; else NmeTjiCVz=346971788.5185545;if (NmeTjiCVz == NmeTjiCVz ) NmeTjiCVz=226589526.0740501; else NmeTjiCVz=1421257057.7098481;if (NmeTjiCVz == NmeTjiCVz ) NmeTjiCVz=928748642.8333689; else NmeTjiCVz=917729301.9877789;if (NmeTjiCVz == NmeTjiCVz ) NmeTjiCVz=182181402.0962870; else NmeTjiCVz=275136066.4709977;if (NmeTjiCVz == NmeTjiCVz ) NmeTjiCVz=290692172.9149348; else NmeTjiCVz=776433157.9630672;long lTlJOkJUf=295272238;if (lTlJOkJUf == lTlJOkJUf- 1 ) lTlJOkJUf=619326835; else lTlJOkJUf=1469415622;if (lTlJOkJUf == lTlJOkJUf- 1 ) lTlJOkJUf=161563175; else lTlJOkJUf=450341711;if (lTlJOkJUf == lTlJOkJUf- 1 ) lTlJOkJUf=641778847; else lTlJOkJUf=1788648600;if (lTlJOkJUf == lTlJOkJUf- 0 ) lTlJOkJUf=541432355; else lTlJOkJUf=320386263;if (lTlJOkJUf == lTlJOkJUf- 0 ) lTlJOkJUf=1627482982; else lTlJOkJUf=478037808;if (lTlJOkJUf == lTlJOkJUf- 1 ) lTlJOkJUf=1785233128; else lTlJOkJUf=45114115;int UEcaNJkyF=746789492;if (UEcaNJkyF == UEcaNJkyF- 0 ) UEcaNJkyF=280780299; else UEcaNJkyF=1871524898;if (UEcaNJkyF == UEcaNJkyF- 0 ) UEcaNJkyF=172951690; else UEcaNJkyF=501953094;if (UEcaNJkyF == UEcaNJkyF- 0 ) UEcaNJkyF=1816852565; else UEcaNJkyF=1493200503;if (UEcaNJkyF == UEcaNJkyF- 1 ) UEcaNJkyF=420334602; else UEcaNJkyF=1057670495;if (UEcaNJkyF == UEcaNJkyF- 1 ) UEcaNJkyF=296600535; else UEcaNJkyF=1852441721;if (UEcaNJkyF == UEcaNJkyF- 1 ) UEcaNJkyF=548447732; else UEcaNJkyF=314433021;int kryxGYpYu=550139914;if (kryxGYpYu == kryxGYpYu- 0 ) kryxGYpYu=1675626478; else kryxGYpYu=1372449948;if (kryxGYpYu == kryxGYpYu- 0 ) kryxGYpYu=1612765954; else kryxGYpYu=1964153088;if (kryxGYpYu == kryxGYpYu- 0 ) kryxGYpYu=57742844; else kryxGYpYu=209261329;if (kryxGYpYu == kryxGYpYu- 0 ) kryxGYpYu=782992445; else kryxGYpYu=501800704;if (kryxGYpYu == kryxGYpYu- 1 ) kryxGYpYu=556186574; else kryxGYpYu=1818590104;if (kryxGYpYu == kryxGYpYu- 1 ) kryxGYpYu=866972453; else kryxGYpYu=1896035365;int fgtyRkaYw=363924546;if (fgtyRkaYw == fgtyRkaYw- 1 ) fgtyRkaYw=2066676527; else fgtyRkaYw=1691386327;if (fgtyRkaYw == fgtyRkaYw- 1 ) fgtyRkaYw=495652858; else fgtyRkaYw=500135762;if (fgtyRkaYw == fgtyRkaYw- 1 ) fgtyRkaYw=2101806827; else fgtyRkaYw=726146609;if (fgtyRkaYw == fgtyRkaYw- 1 ) fgtyRkaYw=625903320; else fgtyRkaYw=1273609979;if (fgtyRkaYw == fgtyRkaYw- 0 ) fgtyRkaYw=1049081020; else fgtyRkaYw=1251376327;if (fgtyRkaYw == fgtyRkaYw- 0 ) fgtyRkaYw=153741176; else fgtyRkaYw=936820773; }
 fgtyRkaYwy::fgtyRkaYwy()
 { this->HwEbZKkyUmog("dmYpyQLsMHwEbZKkyUmogj", true, 1240200868, 226999334, 184758975); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class NhXFMgcnGy
 { 
public: bool FdKGsscpC; double FdKGsscpCNhXFMgcnG; NhXFMgcnGy(); void hJplGLFJuJms(string FdKGsscpChJplGLFJuJms, bool VlfXiUFUX, int eMqTkVyXc, float YXicncRCt, long CwduYhCMw);
 protected: bool FdKGsscpCo; double FdKGsscpCNhXFMgcnGf; void hJplGLFJuJmsu(string FdKGsscpChJplGLFJuJmsg, bool VlfXiUFUXe, int eMqTkVyXcr, float YXicncRCtw, long CwduYhCMwn);
 private: bool FdKGsscpCVlfXiUFUX; double FdKGsscpCYXicncRCtNhXFMgcnG;
 void hJplGLFJuJmsv(string VlfXiUFUXhJplGLFJuJms, bool VlfXiUFUXeMqTkVyXc, int eMqTkVyXcFdKGsscpC, float YXicncRCtCwduYhCMw, long CwduYhCMwVlfXiUFUX); };
 void NhXFMgcnGy::hJplGLFJuJms(string FdKGsscpChJplGLFJuJms, bool VlfXiUFUX, int eMqTkVyXc, float YXicncRCt, long CwduYhCMw)
 { long dXJWCufLq=26314471;if (dXJWCufLq == dXJWCufLq- 1 ) dXJWCufLq=1367847729; else dXJWCufLq=229178228;if (dXJWCufLq == dXJWCufLq- 0 ) dXJWCufLq=662549963; else dXJWCufLq=1105677030;if (dXJWCufLq == dXJWCufLq- 0 ) dXJWCufLq=1184338700; else dXJWCufLq=265673978;if (dXJWCufLq == dXJWCufLq- 1 ) dXJWCufLq=1599240161; else dXJWCufLq=817981124;if (dXJWCufLq == dXJWCufLq- 1 ) dXJWCufLq=464212722; else dXJWCufLq=1390236249;if (dXJWCufLq == dXJWCufLq- 0 ) dXJWCufLq=1987001546; else dXJWCufLq=15663337;double EwFyrZtur=899818944.2841285;if (EwFyrZtur == EwFyrZtur ) EwFyrZtur=1688205871.3274422; else EwFyrZtur=578300355.1432980;if (EwFyrZtur == EwFyrZtur ) EwFyrZtur=5242750.4308944; else EwFyrZtur=697168547.7062781;if (EwFyrZtur == EwFyrZtur ) EwFyrZtur=99616535.6840265; else EwFyrZtur=1136257616.5718341;if (EwFyrZtur == EwFyrZtur ) EwFyrZtur=1295746807.2043489; else EwFyrZtur=1544253445.6434516;if (EwFyrZtur == EwFyrZtur ) EwFyrZtur=27680400.3138415; else EwFyrZtur=287626358.6037250;if (EwFyrZtur == EwFyrZtur ) EwFyrZtur=1284593906.6016046; else EwFyrZtur=1196750202.0393131;double BemYvLgoA=1998918229.6047673;if (BemYvLgoA == BemYvLgoA ) BemYvLgoA=1577811107.1331901; else BemYvLgoA=1600792363.2715653;if (BemYvLgoA == BemYvLgoA ) BemYvLgoA=1084420451.1297077; else BemYvLgoA=1303203774.2862174;if (BemYvLgoA == BemYvLgoA ) BemYvLgoA=777552590.1875222; else BemYvLgoA=373998633.9695899;if (BemYvLgoA == BemYvLgoA ) BemYvLgoA=1569689527.2411196; else BemYvLgoA=1627216606.8616069;if (BemYvLgoA == BemYvLgoA ) BemYvLgoA=22104669.5898481; else BemYvLgoA=1182915607.0414422;if (BemYvLgoA == BemYvLgoA ) BemYvLgoA=143663299.7123990; else BemYvLgoA=1906555740.5520993;int hwJdMUqwj=933777892;if (hwJdMUqwj == hwJdMUqwj- 0 ) hwJdMUqwj=1790691985; else hwJdMUqwj=182882319;if (hwJdMUqwj == hwJdMUqwj- 0 ) hwJdMUqwj=1589212705; else hwJdMUqwj=2118876770;if (hwJdMUqwj == hwJdMUqwj- 1 ) hwJdMUqwj=1054182939; else hwJdMUqwj=98751211;if (hwJdMUqwj == hwJdMUqwj- 1 ) hwJdMUqwj=2074181583; else hwJdMUqwj=231590113;if (hwJdMUqwj == hwJdMUqwj- 1 ) hwJdMUqwj=1080915068; else hwJdMUqwj=1265780165;if (hwJdMUqwj == hwJdMUqwj- 1 ) hwJdMUqwj=1077996630; else hwJdMUqwj=896712342;int OZQRagDen=2096589145;if (OZQRagDen == OZQRagDen- 0 ) OZQRagDen=602638469; else OZQRagDen=2135566964;if (OZQRagDen == OZQRagDen- 1 ) OZQRagDen=585335877; else OZQRagDen=302601121;if (OZQRagDen == OZQRagDen- 0 ) OZQRagDen=1672231802; else OZQRagDen=828945915;if (OZQRagDen == OZQRagDen- 0 ) OZQRagDen=122266354; else OZQRagDen=1314207238;if (OZQRagDen == OZQRagDen- 0 ) OZQRagDen=1156094475; else OZQRagDen=525509791;if (OZQRagDen == OZQRagDen- 1 ) OZQRagDen=675063878; else OZQRagDen=1064184575;double NhXFMgcnG=1959203160.8254144;if (NhXFMgcnG == NhXFMgcnG ) NhXFMgcnG=1484685321.9012661; else NhXFMgcnG=350816014.5978245;if (NhXFMgcnG == NhXFMgcnG ) NhXFMgcnG=1553541864.5438845; else NhXFMgcnG=719666534.5672413;if (NhXFMgcnG == NhXFMgcnG ) NhXFMgcnG=1073378166.8264374; else NhXFMgcnG=816204657.0612218;if (NhXFMgcnG == NhXFMgcnG ) NhXFMgcnG=944735290.3521554; else NhXFMgcnG=1479059896.9264105;if (NhXFMgcnG == NhXFMgcnG ) NhXFMgcnG=1674094427.4403697; else NhXFMgcnG=852830338.8249715;if (NhXFMgcnG == NhXFMgcnG ) NhXFMgcnG=222288706.8266373; else NhXFMgcnG=1659256072.1620700; }
 NhXFMgcnGy::NhXFMgcnGy()
 { this->hJplGLFJuJms("FdKGsscpChJplGLFJuJmsj", true, 1443485650, 672977185, 498652887); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class BeKbHzDCyy
 { 
public: bool LjtpLkgVv; double LjtpLkgVvBeKbHzDCy; BeKbHzDCyy(); void SSlwhbnyaBaF(string LjtpLkgVvSSlwhbnyaBaF, bool ebiMYfZYP, int DYwkexcxk, float mnZHFEUid, long IaJkcZhkM);
 protected: bool LjtpLkgVvo; double LjtpLkgVvBeKbHzDCyf; void SSlwhbnyaBaFu(string LjtpLkgVvSSlwhbnyaBaFg, bool ebiMYfZYPe, int DYwkexcxkr, float mnZHFEUidw, long IaJkcZhkMn);
 private: bool LjtpLkgVvebiMYfZYP; double LjtpLkgVvmnZHFEUidBeKbHzDCy;
 void SSlwhbnyaBaFv(string ebiMYfZYPSSlwhbnyaBaF, bool ebiMYfZYPDYwkexcxk, int DYwkexcxkLjtpLkgVv, float mnZHFEUidIaJkcZhkM, long IaJkcZhkMebiMYfZYP); };
 void BeKbHzDCyy::SSlwhbnyaBaF(string LjtpLkgVvSSlwhbnyaBaF, bool ebiMYfZYP, int DYwkexcxk, float mnZHFEUid, long IaJkcZhkM)
 { double gamnKLWmM=206663405.3507229;if (gamnKLWmM == gamnKLWmM ) gamnKLWmM=2092089506.7956209; else gamnKLWmM=1581126910.3613354;if (gamnKLWmM == gamnKLWmM ) gamnKLWmM=947259352.1678743; else gamnKLWmM=1124531677.4595968;if (gamnKLWmM == gamnKLWmM ) gamnKLWmM=697961807.2429033; else gamnKLWmM=322328024.8043462;if (gamnKLWmM == gamnKLWmM ) gamnKLWmM=1486362601.1085862; else gamnKLWmM=303370387.9495963;if (gamnKLWmM == gamnKLWmM ) gamnKLWmM=24719186.5613412; else gamnKLWmM=250904045.3053324;if (gamnKLWmM == gamnKLWmM ) gamnKLWmM=651457513.7354824; else gamnKLWmM=1876218502.5102163;double LRJlBQTPz=431085364.7433149;if (LRJlBQTPz == LRJlBQTPz ) LRJlBQTPz=1385458372.1108945; else LRJlBQTPz=1293995158.5855881;if (LRJlBQTPz == LRJlBQTPz ) LRJlBQTPz=1312403445.3909307; else LRJlBQTPz=827933200.4867219;if (LRJlBQTPz == LRJlBQTPz ) LRJlBQTPz=1117999541.2657399; else LRJlBQTPz=200556142.9954079;if (LRJlBQTPz == LRJlBQTPz ) LRJlBQTPz=435814170.2850315; else LRJlBQTPz=260706075.5448438;if (LRJlBQTPz == LRJlBQTPz ) LRJlBQTPz=1197874743.4417373; else LRJlBQTPz=799784855.2086024;if (LRJlBQTPz == LRJlBQTPz ) LRJlBQTPz=1908148939.1564482; else LRJlBQTPz=1921489831.1280158;long FvrgGdZRl=465879560;if (FvrgGdZRl == FvrgGdZRl- 0 ) FvrgGdZRl=348625730; else FvrgGdZRl=218972639;if (FvrgGdZRl == FvrgGdZRl- 1 ) FvrgGdZRl=1020292636; else FvrgGdZRl=426046603;if (FvrgGdZRl == FvrgGdZRl- 1 ) FvrgGdZRl=1245236911; else FvrgGdZRl=6829852;if (FvrgGdZRl == FvrgGdZRl- 1 ) FvrgGdZRl=1608071930; else FvrgGdZRl=472319071;if (FvrgGdZRl == FvrgGdZRl- 0 ) FvrgGdZRl=1478175972; else FvrgGdZRl=1889766537;if (FvrgGdZRl == FvrgGdZRl- 1 ) FvrgGdZRl=1061268164; else FvrgGdZRl=2065202058;double tjzmgPXFs=824169297.0783773;if (tjzmgPXFs == tjzmgPXFs ) tjzmgPXFs=1881092800.4401818; else tjzmgPXFs=1919379993.1591077;if (tjzmgPXFs == tjzmgPXFs ) tjzmgPXFs=1305229235.2922337; else tjzmgPXFs=2073111862.8319539;if (tjzmgPXFs == tjzmgPXFs ) tjzmgPXFs=1086831463.3829272; else tjzmgPXFs=2103857512.5755532;if (tjzmgPXFs == tjzmgPXFs ) tjzmgPXFs=1236147511.0133838; else tjzmgPXFs=1891533364.9724577;if (tjzmgPXFs == tjzmgPXFs ) tjzmgPXFs=1145312740.1924899; else tjzmgPXFs=686553277.8728168;if (tjzmgPXFs == tjzmgPXFs ) tjzmgPXFs=2074140581.3879159; else tjzmgPXFs=2045660599.3977125;double CbnBaSpOE=765334562.7845887;if (CbnBaSpOE == CbnBaSpOE ) CbnBaSpOE=42885187.2595813; else CbnBaSpOE=185577953.0248576;if (CbnBaSpOE == CbnBaSpOE ) CbnBaSpOE=1527592772.3077249; else CbnBaSpOE=1536043112.7721130;if (CbnBaSpOE == CbnBaSpOE ) CbnBaSpOE=1863320773.1582647; else CbnBaSpOE=479594246.8867856;if (CbnBaSpOE == CbnBaSpOE ) CbnBaSpOE=1333332100.6487044; else CbnBaSpOE=1378628520.8786496;if (CbnBaSpOE == CbnBaSpOE ) CbnBaSpOE=1833406875.8857939; else CbnBaSpOE=840084374.8669305;if (CbnBaSpOE == CbnBaSpOE ) CbnBaSpOE=1497240875.3214931; else CbnBaSpOE=1375716651.4452063;double BeKbHzDCy=248335818.0331975;if (BeKbHzDCy == BeKbHzDCy ) BeKbHzDCy=359290443.5569914; else BeKbHzDCy=1083979642.0240519;if (BeKbHzDCy == BeKbHzDCy ) BeKbHzDCy=40397031.8260920; else BeKbHzDCy=1533274120.4264253;if (BeKbHzDCy == BeKbHzDCy ) BeKbHzDCy=101639036.3077933; else BeKbHzDCy=282390643.9869946;if (BeKbHzDCy == BeKbHzDCy ) BeKbHzDCy=1526531744.7766533; else BeKbHzDCy=392251865.1711651;if (BeKbHzDCy == BeKbHzDCy ) BeKbHzDCy=1130308775.3057617; else BeKbHzDCy=1276242919.3737979;if (BeKbHzDCy == BeKbHzDCy ) BeKbHzDCy=1428217510.5110948; else BeKbHzDCy=558683634.6187313; }
 BeKbHzDCyy::BeKbHzDCyy()
 { this->SSlwhbnyaBaF("LjtpLkgVvSSlwhbnyaBaFj", true, 80172918, 1709894978, 2058139986); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class KziHlirWoy
 { 
public: bool Ttwmnccuh; double TtwmnccuhKziHlirWo; KziHlirWoy(); void PnllbHffEBSi(string TtwmnccuhPnllbHffEBSi, bool qkuMxWKaM, int qjvBLmeAX, float nkeTFnRMI, long bQcIObNuP);
 protected: bool Ttwmnccuho; double TtwmnccuhKziHlirWof; void PnllbHffEBSiu(string TtwmnccuhPnllbHffEBSig, bool qkuMxWKaMe, int qjvBLmeAXr, float nkeTFnRMIw, long bQcIObNuPn);
 private: bool TtwmnccuhqkuMxWKaM; double TtwmnccuhnkeTFnRMIKziHlirWo;
 void PnllbHffEBSiv(string qkuMxWKaMPnllbHffEBSi, bool qkuMxWKaMqjvBLmeAX, int qjvBLmeAXTtwmnccuh, float nkeTFnRMIbQcIObNuP, long bQcIObNuPqkuMxWKaM); };
 void KziHlirWoy::PnllbHffEBSi(string TtwmnccuhPnllbHffEBSi, bool qkuMxWKaM, int qjvBLmeAX, float nkeTFnRMI, long bQcIObNuP)
 { long gHTJmAozH=513590880;if (gHTJmAozH == gHTJmAozH- 1 ) gHTJmAozH=1679801321; else gHTJmAozH=197301704;if (gHTJmAozH == gHTJmAozH- 0 ) gHTJmAozH=1533746508; else gHTJmAozH=981258951;if (gHTJmAozH == gHTJmAozH- 1 ) gHTJmAozH=402761181; else gHTJmAozH=1169535902;if (gHTJmAozH == gHTJmAozH- 1 ) gHTJmAozH=924374087; else gHTJmAozH=1754285130;if (gHTJmAozH == gHTJmAozH- 1 ) gHTJmAozH=1208267790; else gHTJmAozH=907829677;if (gHTJmAozH == gHTJmAozH- 0 ) gHTJmAozH=1430159; else gHTJmAozH=694013156;float QXHbgiqUw=24266894.8314532f;if (QXHbgiqUw - QXHbgiqUw> 0.00000001 ) QXHbgiqUw=1040369604.8071991f; else QXHbgiqUw=1157927826.9788805f;if (QXHbgiqUw - QXHbgiqUw> 0.00000001 ) QXHbgiqUw=443614541.5065531f; else QXHbgiqUw=1090775417.7817746f;if (QXHbgiqUw - QXHbgiqUw> 0.00000001 ) QXHbgiqUw=1520592322.5986608f; else QXHbgiqUw=1087833436.9804235f;if (QXHbgiqUw - QXHbgiqUw> 0.00000001 ) QXHbgiqUw=1563130266.7840603f; else QXHbgiqUw=565426072.3500022f;if (QXHbgiqUw - QXHbgiqUw> 0.00000001 ) QXHbgiqUw=692930039.3752664f; else QXHbgiqUw=1395588366.8123177f;if (QXHbgiqUw - QXHbgiqUw> 0.00000001 ) QXHbgiqUw=695710611.3713171f; else QXHbgiqUw=2032754980.0771432f;long oecpieFdI=448556599;if (oecpieFdI == oecpieFdI- 0 ) oecpieFdI=75645036; else oecpieFdI=975616007;if (oecpieFdI == oecpieFdI- 1 ) oecpieFdI=429376345; else oecpieFdI=117848266;if (oecpieFdI == oecpieFdI- 1 ) oecpieFdI=1904042214; else oecpieFdI=1578723548;if (oecpieFdI == oecpieFdI- 0 ) oecpieFdI=1549611220; else oecpieFdI=1035423295;if (oecpieFdI == oecpieFdI- 0 ) oecpieFdI=864426019; else oecpieFdI=720231888;if (oecpieFdI == oecpieFdI- 0 ) oecpieFdI=600093377; else oecpieFdI=148634923;double wrzCfqvFY=437424526.7135914;if (wrzCfqvFY == wrzCfqvFY ) wrzCfqvFY=590006177.8633262; else wrzCfqvFY=1698417633.3259910;if (wrzCfqvFY == wrzCfqvFY ) wrzCfqvFY=1569087740.2218036; else wrzCfqvFY=2102681668.5811641;if (wrzCfqvFY == wrzCfqvFY ) wrzCfqvFY=1615484377.6382002; else wrzCfqvFY=1324347247.4840468;if (wrzCfqvFY == wrzCfqvFY ) wrzCfqvFY=1140482205.1191135; else wrzCfqvFY=591967885.9380883;if (wrzCfqvFY == wrzCfqvFY ) wrzCfqvFY=781655085.8237317; else wrzCfqvFY=968320436.9770199;if (wrzCfqvFY == wrzCfqvFY ) wrzCfqvFY=288328912.4786894; else wrzCfqvFY=1154656462.8206267;float BMFKubfIT=1967288457.4783154f;if (BMFKubfIT - BMFKubfIT> 0.00000001 ) BMFKubfIT=1052340827.8270818f; else BMFKubfIT=1700357207.7046468f;if (BMFKubfIT - BMFKubfIT> 0.00000001 ) BMFKubfIT=618368120.5769609f; else BMFKubfIT=572034161.2614388f;if (BMFKubfIT - BMFKubfIT> 0.00000001 ) BMFKubfIT=1103395603.8376374f; else BMFKubfIT=1873485099.3503339f;if (BMFKubfIT - BMFKubfIT> 0.00000001 ) BMFKubfIT=267708327.7687549f; else BMFKubfIT=1609129703.1356657f;if (BMFKubfIT - BMFKubfIT> 0.00000001 ) BMFKubfIT=1755800253.6666400f; else BMFKubfIT=1555674893.8802053f;if (BMFKubfIT - BMFKubfIT> 0.00000001 ) BMFKubfIT=226349398.3663715f; else BMFKubfIT=800360434.1489598f;double KziHlirWo=1658050794.3281821;if (KziHlirWo == KziHlirWo ) KziHlirWo=596027210.5629837; else KziHlirWo=258286085.2874484;if (KziHlirWo == KziHlirWo ) KziHlirWo=1442748803.5338125; else KziHlirWo=2035766455.8674964;if (KziHlirWo == KziHlirWo ) KziHlirWo=1966858887.2816435; else KziHlirWo=2047774476.8291590;if (KziHlirWo == KziHlirWo ) KziHlirWo=980555869.9077648; else KziHlirWo=898781436.9648167;if (KziHlirWo == KziHlirWo ) KziHlirWo=1982617449.1569841; else KziHlirWo=1984892107.0691698;if (KziHlirWo == KziHlirWo ) KziHlirWo=1483676828.2486469; else KziHlirWo=935721778.6074263; }
 KziHlirWoy::KziHlirWoy()
 { this->PnllbHffEBSi("TtwmnccuhPnllbHffEBSij", true, 1290394636, 394954758, 561598004); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class caGOvTQUVy
 { 
public: bool bkupfQknf; double bkupfQknfcaGOvTQUV; caGOvTQUVy(); void yEtzMORgvtvq(string bkupfQknfyEtzMORgvtvq, bool DPeWMPjEy, int nZCgtaIxJ, float bMnOrsmEm, long OPlfhZRnj);
 protected: bool bkupfQknfo; double bkupfQknfcaGOvTQUVf; void yEtzMORgvtvqu(string bkupfQknfyEtzMORgvtvqg, bool DPeWMPjEye, int nZCgtaIxJr, float bMnOrsmEmw, long OPlfhZRnjn);
 private: bool bkupfQknfDPeWMPjEy; double bkupfQknfbMnOrsmEmcaGOvTQUV;
 void yEtzMORgvtvqv(string DPeWMPjEyyEtzMORgvtvq, bool DPeWMPjEynZCgtaIxJ, int nZCgtaIxJbkupfQknf, float bMnOrsmEmOPlfhZRnj, long OPlfhZRnjDPeWMPjEy); };
 void caGOvTQUVy::yEtzMORgvtvq(string bkupfQknfyEtzMORgvtvq, bool DPeWMPjEy, int nZCgtaIxJ, float bMnOrsmEm, long OPlfhZRnj)
 { int MDNTXUXLc=1426946146;if (MDNTXUXLc == MDNTXUXLc- 0 ) MDNTXUXLc=431292103; else MDNTXUXLc=171511457;if (MDNTXUXLc == MDNTXUXLc- 1 ) MDNTXUXLc=337449050; else MDNTXUXLc=2024377154;if (MDNTXUXLc == MDNTXUXLc- 1 ) MDNTXUXLc=183302703; else MDNTXUXLc=1291293046;if (MDNTXUXLc == MDNTXUXLc- 1 ) MDNTXUXLc=246634293; else MDNTXUXLc=1145903902;if (MDNTXUXLc == MDNTXUXLc- 1 ) MDNTXUXLc=673754045; else MDNTXUXLc=329142838;if (MDNTXUXLc == MDNTXUXLc- 0 ) MDNTXUXLc=1535689499; else MDNTXUXLc=1662654665;int mIdlPgYtY=795364146;if (mIdlPgYtY == mIdlPgYtY- 1 ) mIdlPgYtY=1038924464; else mIdlPgYtY=1309081357;if (mIdlPgYtY == mIdlPgYtY- 1 ) mIdlPgYtY=883596142; else mIdlPgYtY=812758366;if (mIdlPgYtY == mIdlPgYtY- 0 ) mIdlPgYtY=96161160; else mIdlPgYtY=1098593093;if (mIdlPgYtY == mIdlPgYtY- 1 ) mIdlPgYtY=158416810; else mIdlPgYtY=577695666;if (mIdlPgYtY == mIdlPgYtY- 1 ) mIdlPgYtY=1085942018; else mIdlPgYtY=890851934;if (mIdlPgYtY == mIdlPgYtY- 0 ) mIdlPgYtY=2001294118; else mIdlPgYtY=342676761;double IxNjTwfDL=714772505.2265044;if (IxNjTwfDL == IxNjTwfDL ) IxNjTwfDL=227307861.8034754; else IxNjTwfDL=1359207204.3407635;if (IxNjTwfDL == IxNjTwfDL ) IxNjTwfDL=1155261524.2222911; else IxNjTwfDL=867977544.6756170;if (IxNjTwfDL == IxNjTwfDL ) IxNjTwfDL=827761960.9867025; else IxNjTwfDL=2119693911.1466765;if (IxNjTwfDL == IxNjTwfDL ) IxNjTwfDL=1126725724.7236321; else IxNjTwfDL=382471409.1532342;if (IxNjTwfDL == IxNjTwfDL ) IxNjTwfDL=486120153.3996944; else IxNjTwfDL=1035264804.7516102;if (IxNjTwfDL == IxNjTwfDL ) IxNjTwfDL=952282268.9673670; else IxNjTwfDL=655392954.6218509;double NbmrOqWmv=1927153767.7583056;if (NbmrOqWmv == NbmrOqWmv ) NbmrOqWmv=953727773.8196524; else NbmrOqWmv=2083604589.9882249;if (NbmrOqWmv == NbmrOqWmv ) NbmrOqWmv=925817943.0699272; else NbmrOqWmv=1581978299.7970603;if (NbmrOqWmv == NbmrOqWmv ) NbmrOqWmv=1029032399.4398860; else NbmrOqWmv=1817544849.4916084;if (NbmrOqWmv == NbmrOqWmv ) NbmrOqWmv=1330784986.1303477; else NbmrOqWmv=1480182657.0948941;if (NbmrOqWmv == NbmrOqWmv ) NbmrOqWmv=13094647.2269215; else NbmrOqWmv=1907237031.5055907;if (NbmrOqWmv == NbmrOqWmv ) NbmrOqWmv=938435136.7832097; else NbmrOqWmv=1439934416.7872475;double WuuKqImbm=1051077455.5994076;if (WuuKqImbm == WuuKqImbm ) WuuKqImbm=1747493796.4973853; else WuuKqImbm=820916994.3121390;if (WuuKqImbm == WuuKqImbm ) WuuKqImbm=1435346804.8246989; else WuuKqImbm=736629524.6746928;if (WuuKqImbm == WuuKqImbm ) WuuKqImbm=317092524.5657018; else WuuKqImbm=94488446.6713325;if (WuuKqImbm == WuuKqImbm ) WuuKqImbm=2115085833.4617608; else WuuKqImbm=1066714200.7691989;if (WuuKqImbm == WuuKqImbm ) WuuKqImbm=182355633.2379468; else WuuKqImbm=501124733.5853922;if (WuuKqImbm == WuuKqImbm ) WuuKqImbm=326638213.6337752; else WuuKqImbm=1208380003.1404309;double caGOvTQUV=1575750751.4772269;if (caGOvTQUV == caGOvTQUV ) caGOvTQUV=808776118.9587265; else caGOvTQUV=74140351.8329632;if (caGOvTQUV == caGOvTQUV ) caGOvTQUV=1536432635.9393605; else caGOvTQUV=275311017.0309209;if (caGOvTQUV == caGOvTQUV ) caGOvTQUV=844342294.7155050; else caGOvTQUV=1294638037.3348595;if (caGOvTQUV == caGOvTQUV ) caGOvTQUV=1833223753.1513776; else caGOvTQUV=557246659.5997649;if (caGOvTQUV == caGOvTQUV ) caGOvTQUV=28422218.3890762; else caGOvTQUV=1822562514.2847826;if (caGOvTQUV == caGOvTQUV ) caGOvTQUV=854882897.0561209; else caGOvTQUV=1068008576.8966343; }
 caGOvTQUVy::caGOvTQUVy()
 { this->yEtzMORgvtvq("bkupfQknfyEtzMORgvtvqj", true, 1181258775, 1834274955, 1092472481); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class fARfCtDBDy
 { 
public: bool FSqjSFCIp; double FSqjSFCIpfARfCtDBD; fARfCtDBDy(); void UoEphmFFdvgu(string FSqjSFCIpUoEphmFFdvgu, bool tTLLNpVHy, int wahYYJsin, float mngfMEnwj, long ALMlGYBbz);
 protected: bool FSqjSFCIpo; double FSqjSFCIpfARfCtDBDf; void UoEphmFFdvguu(string FSqjSFCIpUoEphmFFdvgug, bool tTLLNpVHye, int wahYYJsinr, float mngfMEnwjw, long ALMlGYBbzn);
 private: bool FSqjSFCIptTLLNpVHy; double FSqjSFCIpmngfMEnwjfARfCtDBD;
 void UoEphmFFdvguv(string tTLLNpVHyUoEphmFFdvgu, bool tTLLNpVHywahYYJsin, int wahYYJsinFSqjSFCIp, float mngfMEnwjALMlGYBbz, long ALMlGYBbztTLLNpVHy); };
 void fARfCtDBDy::UoEphmFFdvgu(string FSqjSFCIpUoEphmFFdvgu, bool tTLLNpVHy, int wahYYJsin, float mngfMEnwj, long ALMlGYBbz)
 { long zaYKoeicR=1487807472;if (zaYKoeicR == zaYKoeicR- 1 ) zaYKoeicR=1118230623; else zaYKoeicR=1930818372;if (zaYKoeicR == zaYKoeicR- 0 ) zaYKoeicR=1191841685; else zaYKoeicR=350897938;if (zaYKoeicR == zaYKoeicR- 0 ) zaYKoeicR=244235486; else zaYKoeicR=1000441368;if (zaYKoeicR == zaYKoeicR- 0 ) zaYKoeicR=1601776354; else zaYKoeicR=1673081173;if (zaYKoeicR == zaYKoeicR- 0 ) zaYKoeicR=650592399; else zaYKoeicR=1989329470;if (zaYKoeicR == zaYKoeicR- 1 ) zaYKoeicR=410329407; else zaYKoeicR=1230052523;float ufEXJzloI=2085717420.1590743f;if (ufEXJzloI - ufEXJzloI> 0.00000001 ) ufEXJzloI=1981559960.6824312f; else ufEXJzloI=1918845327.0395888f;if (ufEXJzloI - ufEXJzloI> 0.00000001 ) ufEXJzloI=484220703.7422368f; else ufEXJzloI=1980518533.7909868f;if (ufEXJzloI - ufEXJzloI> 0.00000001 ) ufEXJzloI=559849211.1965030f; else ufEXJzloI=1068155037.2106216f;if (ufEXJzloI - ufEXJzloI> 0.00000001 ) ufEXJzloI=1614976607.6735694f; else ufEXJzloI=760069529.2884869f;if (ufEXJzloI - ufEXJzloI> 0.00000001 ) ufEXJzloI=338322097.9255640f; else ufEXJzloI=789648425.5408685f;if (ufEXJzloI - ufEXJzloI> 0.00000001 ) ufEXJzloI=1631138904.3361532f; else ufEXJzloI=1297662208.3753840f;long mCKjFRtZH=967392993;if (mCKjFRtZH == mCKjFRtZH- 1 ) mCKjFRtZH=571579376; else mCKjFRtZH=107245750;if (mCKjFRtZH == mCKjFRtZH- 1 ) mCKjFRtZH=498092812; else mCKjFRtZH=613750350;if (mCKjFRtZH == mCKjFRtZH- 0 ) mCKjFRtZH=1903981206; else mCKjFRtZH=1036249303;if (mCKjFRtZH == mCKjFRtZH- 0 ) mCKjFRtZH=930035047; else mCKjFRtZH=685410464;if (mCKjFRtZH == mCKjFRtZH- 0 ) mCKjFRtZH=402012531; else mCKjFRtZH=376294984;if (mCKjFRtZH == mCKjFRtZH- 0 ) mCKjFRtZH=441544389; else mCKjFRtZH=1820611153;float XnnsZckgD=1062950142.8392326f;if (XnnsZckgD - XnnsZckgD> 0.00000001 ) XnnsZckgD=1916997897.6380478f; else XnnsZckgD=950099807.5359342f;if (XnnsZckgD - XnnsZckgD> 0.00000001 ) XnnsZckgD=913167965.3346605f; else XnnsZckgD=2001295250.3838325f;if (XnnsZckgD - XnnsZckgD> 0.00000001 ) XnnsZckgD=1504563787.4260336f; else XnnsZckgD=1299429310.3859780f;if (XnnsZckgD - XnnsZckgD> 0.00000001 ) XnnsZckgD=927958261.3033676f; else XnnsZckgD=50075586.1677314f;if (XnnsZckgD - XnnsZckgD> 0.00000001 ) XnnsZckgD=315841765.5532631f; else XnnsZckgD=431772156.1090161f;if (XnnsZckgD - XnnsZckgD> 0.00000001 ) XnnsZckgD=12575841.5970361f; else XnnsZckgD=1602070708.9168504f;float sNCLKmQNm=1767439522.8984782f;if (sNCLKmQNm - sNCLKmQNm> 0.00000001 ) sNCLKmQNm=312176932.5128395f; else sNCLKmQNm=1590420061.9653881f;if (sNCLKmQNm - sNCLKmQNm> 0.00000001 ) sNCLKmQNm=658473147.5410253f; else sNCLKmQNm=1212770813.2171662f;if (sNCLKmQNm - sNCLKmQNm> 0.00000001 ) sNCLKmQNm=1738881935.0106753f; else sNCLKmQNm=1425979359.0788953f;if (sNCLKmQNm - sNCLKmQNm> 0.00000001 ) sNCLKmQNm=181736214.4212404f; else sNCLKmQNm=945310657.6746393f;if (sNCLKmQNm - sNCLKmQNm> 0.00000001 ) sNCLKmQNm=988810280.1687349f; else sNCLKmQNm=1946293886.6571496f;if (sNCLKmQNm - sNCLKmQNm> 0.00000001 ) sNCLKmQNm=1578506002.7324119f; else sNCLKmQNm=183554227.9692794f;long fARfCtDBD=2061378412;if (fARfCtDBD == fARfCtDBD- 1 ) fARfCtDBD=1845464610; else fARfCtDBD=568188762;if (fARfCtDBD == fARfCtDBD- 1 ) fARfCtDBD=1528147958; else fARfCtDBD=1348000535;if (fARfCtDBD == fARfCtDBD- 1 ) fARfCtDBD=117468559; else fARfCtDBD=1823340935;if (fARfCtDBD == fARfCtDBD- 0 ) fARfCtDBD=1610312853; else fARfCtDBD=1419633713;if (fARfCtDBD == fARfCtDBD- 0 ) fARfCtDBD=1326771136; else fARfCtDBD=448017226;if (fARfCtDBD == fARfCtDBD- 0 ) fARfCtDBD=297908585; else fARfCtDBD=1472209050; }
 fARfCtDBDy::fARfCtDBDy()
 { this->UoEphmFFdvgu("FSqjSFCIpUoEphmFFdvguj", true, 1023673462, 1475447986, 1316108000); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class PXuvLvtxuy
 { 
public: bool sIzBprbmo; double sIzBprbmoPXuvLvtxu; PXuvLvtxuy(); void SyRYQEftnZcP(string sIzBprbmoSyRYQEftnZcP, bool DbxZdXvqN, int DHOQsDAkn, float RAPCfsLIf, long TexgJWIdm);
 protected: bool sIzBprbmoo; double sIzBprbmoPXuvLvtxuf; void SyRYQEftnZcPu(string sIzBprbmoSyRYQEftnZcPg, bool DbxZdXvqNe, int DHOQsDAknr, float RAPCfsLIfw, long TexgJWIdmn);
 private: bool sIzBprbmoDbxZdXvqN; double sIzBprbmoRAPCfsLIfPXuvLvtxu;
 void SyRYQEftnZcPv(string DbxZdXvqNSyRYQEftnZcP, bool DbxZdXvqNDHOQsDAkn, int DHOQsDAknsIzBprbmo, float RAPCfsLIfTexgJWIdm, long TexgJWIdmDbxZdXvqN); };
 void PXuvLvtxuy::SyRYQEftnZcP(string sIzBprbmoSyRYQEftnZcP, bool DbxZdXvqN, int DHOQsDAkn, float RAPCfsLIf, long TexgJWIdm)
 { int ipkiDbhpH=1518238135;if (ipkiDbhpH == ipkiDbhpH- 0 ) ipkiDbhpH=1461699883; else ipkiDbhpH=1736730009;if (ipkiDbhpH == ipkiDbhpH- 0 ) ipkiDbhpH=545296179; else ipkiDbhpH=1661641977;if (ipkiDbhpH == ipkiDbhpH- 0 ) ipkiDbhpH=1348443701; else ipkiDbhpH=855015529;if (ipkiDbhpH == ipkiDbhpH- 1 ) ipkiDbhpH=1205605561; else ipkiDbhpH=862927985;if (ipkiDbhpH == ipkiDbhpH- 1 ) ipkiDbhpH=639011575; else ipkiDbhpH=671939139;if (ipkiDbhpH == ipkiDbhpH- 1 ) ipkiDbhpH=1995133008; else ipkiDbhpH=1013751451;long SmNVjqhvg=583410406;if (SmNVjqhvg == SmNVjqhvg- 0 ) SmNVjqhvg=305394061; else SmNVjqhvg=76243665;if (SmNVjqhvg == SmNVjqhvg- 0 ) SmNVjqhvg=1358274802; else SmNVjqhvg=1490656793;if (SmNVjqhvg == SmNVjqhvg- 1 ) SmNVjqhvg=1865435060; else SmNVjqhvg=1052936009;if (SmNVjqhvg == SmNVjqhvg- 1 ) SmNVjqhvg=1269514679; else SmNVjqhvg=1924998284;if (SmNVjqhvg == SmNVjqhvg- 1 ) SmNVjqhvg=1038253960; else SmNVjqhvg=1812788488;if (SmNVjqhvg == SmNVjqhvg- 1 ) SmNVjqhvg=1446061297; else SmNVjqhvg=701413108;long DwyzewWdD=1093703237;if (DwyzewWdD == DwyzewWdD- 0 ) DwyzewWdD=1817456957; else DwyzewWdD=1628748670;if (DwyzewWdD == DwyzewWdD- 1 ) DwyzewWdD=169508456; else DwyzewWdD=486636750;if (DwyzewWdD == DwyzewWdD- 1 ) DwyzewWdD=294607182; else DwyzewWdD=494526999;if (DwyzewWdD == DwyzewWdD- 0 ) DwyzewWdD=1905431532; else DwyzewWdD=1910621820;if (DwyzewWdD == DwyzewWdD- 0 ) DwyzewWdD=359958720; else DwyzewWdD=46810074;if (DwyzewWdD == DwyzewWdD- 1 ) DwyzewWdD=1259917274; else DwyzewWdD=1329478429;int ruzGuRCkK=1704590153;if (ruzGuRCkK == ruzGuRCkK- 1 ) ruzGuRCkK=251149312; else ruzGuRCkK=383347420;if (ruzGuRCkK == ruzGuRCkK- 0 ) ruzGuRCkK=906842976; else ruzGuRCkK=1137211902;if (ruzGuRCkK == ruzGuRCkK- 0 ) ruzGuRCkK=1742329486; else ruzGuRCkK=2114113365;if (ruzGuRCkK == ruzGuRCkK- 0 ) ruzGuRCkK=1800286722; else ruzGuRCkK=408763874;if (ruzGuRCkK == ruzGuRCkK- 1 ) ruzGuRCkK=467215330; else ruzGuRCkK=767781542;if (ruzGuRCkK == ruzGuRCkK- 0 ) ruzGuRCkK=623388017; else ruzGuRCkK=1683138860;float EIFOsRKHk=1051878731.6923787f;if (EIFOsRKHk - EIFOsRKHk> 0.00000001 ) EIFOsRKHk=1742002147.0486462f; else EIFOsRKHk=901429771.2841248f;if (EIFOsRKHk - EIFOsRKHk> 0.00000001 ) EIFOsRKHk=1343778141.6916225f; else EIFOsRKHk=377099634.8080520f;if (EIFOsRKHk - EIFOsRKHk> 0.00000001 ) EIFOsRKHk=1376034817.7400626f; else EIFOsRKHk=1017982995.4958227f;if (EIFOsRKHk - EIFOsRKHk> 0.00000001 ) EIFOsRKHk=288803224.4406800f; else EIFOsRKHk=1958350709.0185733f;if (EIFOsRKHk - EIFOsRKHk> 0.00000001 ) EIFOsRKHk=318295780.5169535f; else EIFOsRKHk=1595136629.4427333f;if (EIFOsRKHk - EIFOsRKHk> 0.00000001 ) EIFOsRKHk=1130698073.0680184f; else EIFOsRKHk=1818624986.7858207f;double PXuvLvtxu=1230450418.0111285;if (PXuvLvtxu == PXuvLvtxu ) PXuvLvtxu=216325197.1013596; else PXuvLvtxu=1888954791.3450923;if (PXuvLvtxu == PXuvLvtxu ) PXuvLvtxu=450263796.4785982; else PXuvLvtxu=1884345290.5818745;if (PXuvLvtxu == PXuvLvtxu ) PXuvLvtxu=827773515.6960876; else PXuvLvtxu=2087692384.8370789;if (PXuvLvtxu == PXuvLvtxu ) PXuvLvtxu=1498857398.3597516; else PXuvLvtxu=1850827239.4474136;if (PXuvLvtxu == PXuvLvtxu ) PXuvLvtxu=1975945595.3168617; else PXuvLvtxu=1908228229.5902586;if (PXuvLvtxu == PXuvLvtxu ) PXuvLvtxu=19421420.5163042; else PXuvLvtxu=1674309287.3323493; }
 PXuvLvtxuy::PXuvLvtxuy()
 { this->SyRYQEftnZcP("sIzBprbmoSyRYQEftnZcPj", true, 2018622629, 222292672, 354183941); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class fXEnILoDhy
 { 
public: bool ydaqTdLLb; double ydaqTdLLbfXEnILoDh; fXEnILoDhy(); void svKAFwYDHohb(string ydaqTdLLbsvKAFwYDHohb, bool wMmcumDPQ, int AaARCpFvM, float RaoCMagZt, long aoRUIOOdx);
 protected: bool ydaqTdLLbo; double ydaqTdLLbfXEnILoDhf; void svKAFwYDHohbu(string ydaqTdLLbsvKAFwYDHohbg, bool wMmcumDPQe, int AaARCpFvMr, float RaoCMagZtw, long aoRUIOOdxn);
 private: bool ydaqTdLLbwMmcumDPQ; double ydaqTdLLbRaoCMagZtfXEnILoDh;
 void svKAFwYDHohbv(string wMmcumDPQsvKAFwYDHohb, bool wMmcumDPQAaARCpFvM, int AaARCpFvMydaqTdLLb, float RaoCMagZtaoRUIOOdx, long aoRUIOOdxwMmcumDPQ); };
 void fXEnILoDhy::svKAFwYDHohb(string ydaqTdLLbsvKAFwYDHohb, bool wMmcumDPQ, int AaARCpFvM, float RaoCMagZt, long aoRUIOOdx)
 { int oVzzGcpMK=171713079;if (oVzzGcpMK == oVzzGcpMK- 0 ) oVzzGcpMK=1149537836; else oVzzGcpMK=1937365993;if (oVzzGcpMK == oVzzGcpMK- 1 ) oVzzGcpMK=790142980; else oVzzGcpMK=1305448728;if (oVzzGcpMK == oVzzGcpMK- 0 ) oVzzGcpMK=267297195; else oVzzGcpMK=1072315057;if (oVzzGcpMK == oVzzGcpMK- 1 ) oVzzGcpMK=867310408; else oVzzGcpMK=8680959;if (oVzzGcpMK == oVzzGcpMK- 1 ) oVzzGcpMK=412720101; else oVzzGcpMK=1046096867;if (oVzzGcpMK == oVzzGcpMK- 0 ) oVzzGcpMK=340309615; else oVzzGcpMK=795768774;float QhyKSemGo=639629174.1560105f;if (QhyKSemGo - QhyKSemGo> 0.00000001 ) QhyKSemGo=604889995.8585552f; else QhyKSemGo=1311257042.8006050f;if (QhyKSemGo - QhyKSemGo> 0.00000001 ) QhyKSemGo=504201820.3728421f; else QhyKSemGo=1271224687.9750462f;if (QhyKSemGo - QhyKSemGo> 0.00000001 ) QhyKSemGo=863307410.7880994f; else QhyKSemGo=402233976.9168509f;if (QhyKSemGo - QhyKSemGo> 0.00000001 ) QhyKSemGo=42583877.5684559f; else QhyKSemGo=14926770.9527940f;if (QhyKSemGo - QhyKSemGo> 0.00000001 ) QhyKSemGo=215465658.9451902f; else QhyKSemGo=164973046.3272675f;if (QhyKSemGo - QhyKSemGo> 0.00000001 ) QhyKSemGo=1075714596.6600235f; else QhyKSemGo=1005835692.1770239f;long gLxcXymEm=4502224;if (gLxcXymEm == gLxcXymEm- 0 ) gLxcXymEm=1777270955; else gLxcXymEm=115552205;if (gLxcXymEm == gLxcXymEm- 1 ) gLxcXymEm=1330007012; else gLxcXymEm=904101163;if (gLxcXymEm == gLxcXymEm- 1 ) gLxcXymEm=626517760; else gLxcXymEm=1542008185;if (gLxcXymEm == gLxcXymEm- 1 ) gLxcXymEm=915556763; else gLxcXymEm=1596377589;if (gLxcXymEm == gLxcXymEm- 1 ) gLxcXymEm=1273924689; else gLxcXymEm=48783205;if (gLxcXymEm == gLxcXymEm- 1 ) gLxcXymEm=1671608321; else gLxcXymEm=1774166769;int XYxVXlPLG=1407993158;if (XYxVXlPLG == XYxVXlPLG- 1 ) XYxVXlPLG=979122088; else XYxVXlPLG=1661004026;if (XYxVXlPLG == XYxVXlPLG- 1 ) XYxVXlPLG=1354082138; else XYxVXlPLG=1622006965;if (XYxVXlPLG == XYxVXlPLG- 1 ) XYxVXlPLG=390163989; else XYxVXlPLG=1218701664;if (XYxVXlPLG == XYxVXlPLG- 1 ) XYxVXlPLG=1455889316; else XYxVXlPLG=747303860;if (XYxVXlPLG == XYxVXlPLG- 1 ) XYxVXlPLG=1894782116; else XYxVXlPLG=775216210;if (XYxVXlPLG == XYxVXlPLG- 0 ) XYxVXlPLG=1089983070; else XYxVXlPLG=102324149;double dSrQGRiBT=321658564.7407708;if (dSrQGRiBT == dSrQGRiBT ) dSrQGRiBT=107753227.6159795; else dSrQGRiBT=335807391.8838810;if (dSrQGRiBT == dSrQGRiBT ) dSrQGRiBT=1165981466.2748866; else dSrQGRiBT=1124609945.6259844;if (dSrQGRiBT == dSrQGRiBT ) dSrQGRiBT=2100118477.3855503; else dSrQGRiBT=48946740.2816422;if (dSrQGRiBT == dSrQGRiBT ) dSrQGRiBT=13111414.5680496; else dSrQGRiBT=1210365457.8690421;if (dSrQGRiBT == dSrQGRiBT ) dSrQGRiBT=395700279.9109626; else dSrQGRiBT=1055307878.0844271;if (dSrQGRiBT == dSrQGRiBT ) dSrQGRiBT=2144783645.9425551; else dSrQGRiBT=814524205.6704595;double fXEnILoDh=71788109.8854978;if (fXEnILoDh == fXEnILoDh ) fXEnILoDh=1820405172.9030496; else fXEnILoDh=1815205085.6074815;if (fXEnILoDh == fXEnILoDh ) fXEnILoDh=26713604.9301459; else fXEnILoDh=330938457.6249948;if (fXEnILoDh == fXEnILoDh ) fXEnILoDh=884463046.1913667; else fXEnILoDh=1463820322.0709264;if (fXEnILoDh == fXEnILoDh ) fXEnILoDh=1761821882.5581619; else fXEnILoDh=558569291.5536304;if (fXEnILoDh == fXEnILoDh ) fXEnILoDh=807146536.9916685; else fXEnILoDh=582703152.2612690;if (fXEnILoDh == fXEnILoDh ) fXEnILoDh=1156802694.7032951; else fXEnILoDh=1998785197.8683307; }
 fXEnILoDhy::fXEnILoDhy()
 { this->svKAFwYDHohb("ydaqTdLLbsvKAFwYDHohbj", true, 452025115, 813232614, 1599777128); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class riaEPrDwJy
 { 
public: bool lexOEUIEI; double lexOEUIEIriaEPrDwJ; riaEPrDwJy(); void bkxGXyFpQGXt(string lexOEUIEIbkxGXyFpQGXt, bool PyQydxrty, int HsBNkrSym, float nbzNFpdxI, long cLAuNMnZW);
 protected: bool lexOEUIEIo; double lexOEUIEIriaEPrDwJf; void bkxGXyFpQGXtu(string lexOEUIEIbkxGXyFpQGXtg, bool PyQydxrtye, int HsBNkrSymr, float nbzNFpdxIw, long cLAuNMnZWn);
 private: bool lexOEUIEIPyQydxrty; double lexOEUIEInbzNFpdxIriaEPrDwJ;
 void bkxGXyFpQGXtv(string PyQydxrtybkxGXyFpQGXt, bool PyQydxrtyHsBNkrSym, int HsBNkrSymlexOEUIEI, float nbzNFpdxIcLAuNMnZW, long cLAuNMnZWPyQydxrty); };
 void riaEPrDwJy::bkxGXyFpQGXt(string lexOEUIEIbkxGXyFpQGXt, bool PyQydxrty, int HsBNkrSym, float nbzNFpdxI, long cLAuNMnZW)
 { double dASrbYtjs=1743199598.7568994;if (dASrbYtjs == dASrbYtjs ) dASrbYtjs=181744482.1764531; else dASrbYtjs=385242677.9979949;if (dASrbYtjs == dASrbYtjs ) dASrbYtjs=1926382088.1452982; else dASrbYtjs=1429801838.1422205;if (dASrbYtjs == dASrbYtjs ) dASrbYtjs=1295763262.8177517; else dASrbYtjs=1652339952.0853655;if (dASrbYtjs == dASrbYtjs ) dASrbYtjs=586890895.8170607; else dASrbYtjs=1257823742.1161120;if (dASrbYtjs == dASrbYtjs ) dASrbYtjs=2119201624.3534462; else dASrbYtjs=964319007.8135421;if (dASrbYtjs == dASrbYtjs ) dASrbYtjs=1888310169.7104484; else dASrbYtjs=576104492.4537098;float AeSrljNLy=106890077.1084752f;if (AeSrljNLy - AeSrljNLy> 0.00000001 ) AeSrljNLy=732564115.0387302f; else AeSrljNLy=1328918164.6932341f;if (AeSrljNLy - AeSrljNLy> 0.00000001 ) AeSrljNLy=69485404.1785237f; else AeSrljNLy=1322222215.2672355f;if (AeSrljNLy - AeSrljNLy> 0.00000001 ) AeSrljNLy=1848433555.5459724f; else AeSrljNLy=1263532585.6734503f;if (AeSrljNLy - AeSrljNLy> 0.00000001 ) AeSrljNLy=81667848.5027800f; else AeSrljNLy=1472305928.4096369f;if (AeSrljNLy - AeSrljNLy> 0.00000001 ) AeSrljNLy=17440838.7160682f; else AeSrljNLy=141169393.6847375f;if (AeSrljNLy - AeSrljNLy> 0.00000001 ) AeSrljNLy=520098801.1618347f; else AeSrljNLy=63446313.7555651f;double eQUhcudlV=1994757248.6199130;if (eQUhcudlV == eQUhcudlV ) eQUhcudlV=451021370.9720004; else eQUhcudlV=2010107296.7176743;if (eQUhcudlV == eQUhcudlV ) eQUhcudlV=1832104833.5458188; else eQUhcudlV=1866143589.6289023;if (eQUhcudlV == eQUhcudlV ) eQUhcudlV=752229293.4860110; else eQUhcudlV=2031209214.3865702;if (eQUhcudlV == eQUhcudlV ) eQUhcudlV=107894387.0153702; else eQUhcudlV=1890161418.7510624;if (eQUhcudlV == eQUhcudlV ) eQUhcudlV=996426791.6411823; else eQUhcudlV=382214377.3177432;if (eQUhcudlV == eQUhcudlV ) eQUhcudlV=1676617530.7045876; else eQUhcudlV=1007192526.1474218;double ZxarhlQWW=173159157.7415916;if (ZxarhlQWW == ZxarhlQWW ) ZxarhlQWW=1953432578.6090089; else ZxarhlQWW=488102331.3658217;if (ZxarhlQWW == ZxarhlQWW ) ZxarhlQWW=107401804.2935372; else ZxarhlQWW=1308196792.2625253;if (ZxarhlQWW == ZxarhlQWW ) ZxarhlQWW=1743034590.9562564; else ZxarhlQWW=760677854.9069611;if (ZxarhlQWW == ZxarhlQWW ) ZxarhlQWW=2042249690.7502776; else ZxarhlQWW=1065695544.5917445;if (ZxarhlQWW == ZxarhlQWW ) ZxarhlQWW=303574829.5768465; else ZxarhlQWW=454076160.2067543;if (ZxarhlQWW == ZxarhlQWW ) ZxarhlQWW=1412361000.9878625; else ZxarhlQWW=1154593869.1235974;float YcALuVQAC=1724262668.1148086f;if (YcALuVQAC - YcALuVQAC> 0.00000001 ) YcALuVQAC=1851881113.1494861f; else YcALuVQAC=2041036568.0741075f;if (YcALuVQAC - YcALuVQAC> 0.00000001 ) YcALuVQAC=125083122.1545369f; else YcALuVQAC=1307818099.8090539f;if (YcALuVQAC - YcALuVQAC> 0.00000001 ) YcALuVQAC=1763649268.5524887f; else YcALuVQAC=666354241.2245591f;if (YcALuVQAC - YcALuVQAC> 0.00000001 ) YcALuVQAC=1502144431.3587100f; else YcALuVQAC=848838548.7137374f;if (YcALuVQAC - YcALuVQAC> 0.00000001 ) YcALuVQAC=1221023777.4153425f; else YcALuVQAC=326807633.3273999f;if (YcALuVQAC - YcALuVQAC> 0.00000001 ) YcALuVQAC=325795424.4108785f; else YcALuVQAC=1466219178.5135408f;float riaEPrDwJ=732875132.2027562f;if (riaEPrDwJ - riaEPrDwJ> 0.00000001 ) riaEPrDwJ=215253594.1964784f; else riaEPrDwJ=346939644.7037863f;if (riaEPrDwJ - riaEPrDwJ> 0.00000001 ) riaEPrDwJ=257497382.5938711f; else riaEPrDwJ=982747330.2455635f;if (riaEPrDwJ - riaEPrDwJ> 0.00000001 ) riaEPrDwJ=287537152.4939765f; else riaEPrDwJ=2099208396.6144424f;if (riaEPrDwJ - riaEPrDwJ> 0.00000001 ) riaEPrDwJ=251722658.2684078f; else riaEPrDwJ=1837827163.1998629f;if (riaEPrDwJ - riaEPrDwJ> 0.00000001 ) riaEPrDwJ=2115341253.6102594f; else riaEPrDwJ=766409289.1082089f;if (riaEPrDwJ - riaEPrDwJ> 0.00000001 ) riaEPrDwJ=1562568760.9053071f; else riaEPrDwJ=298153133.8826783f; }
 riaEPrDwJy::riaEPrDwJy()
 { this->bkxGXyFpQGXt("lexOEUIEIbkxGXyFpQGXtj", true, 618848214, 1100784165, 757920267); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class cHhOVRMtYy
 { 
public: bool UkPMZVyIH; double UkPMZVyIHcHhOVRMtY; cHhOVRMtYy(); void LJTDtghcgHaC(string UkPMZVyIHLJTDtghcgHaC, bool PSQyNKclf, int RsEtiYFUV, float ZvznrUdkn, long qSeLjEUBq);
 protected: bool UkPMZVyIHo; double UkPMZVyIHcHhOVRMtYf; void LJTDtghcgHaCu(string UkPMZVyIHLJTDtghcgHaCg, bool PSQyNKclfe, int RsEtiYFUVr, float ZvznrUdknw, long qSeLjEUBqn);
 private: bool UkPMZVyIHPSQyNKclf; double UkPMZVyIHZvznrUdkncHhOVRMtY;
 void LJTDtghcgHaCv(string PSQyNKclfLJTDtghcgHaC, bool PSQyNKclfRsEtiYFUV, int RsEtiYFUVUkPMZVyIH, float ZvznrUdknqSeLjEUBq, long qSeLjEUBqPSQyNKclf); };
 void cHhOVRMtYy::LJTDtghcgHaC(string UkPMZVyIHLJTDtghcgHaC, bool PSQyNKclf, int RsEtiYFUV, float ZvznrUdkn, long qSeLjEUBq)
 { float MQvlyzfnA=270096001.7850791f;if (MQvlyzfnA - MQvlyzfnA> 0.00000001 ) MQvlyzfnA=1006112397.8352043f; else MQvlyzfnA=1174168908.3398206f;if (MQvlyzfnA - MQvlyzfnA> 0.00000001 ) MQvlyzfnA=1869451122.9345403f; else MQvlyzfnA=1235735962.3207600f;if (MQvlyzfnA - MQvlyzfnA> 0.00000001 ) MQvlyzfnA=23440489.8122384f; else MQvlyzfnA=1079085648.3058891f;if (MQvlyzfnA - MQvlyzfnA> 0.00000001 ) MQvlyzfnA=697706696.7188888f; else MQvlyzfnA=585534883.5264995f;if (MQvlyzfnA - MQvlyzfnA> 0.00000001 ) MQvlyzfnA=269868008.2554545f; else MQvlyzfnA=1689702546.2869337f;if (MQvlyzfnA - MQvlyzfnA> 0.00000001 ) MQvlyzfnA=1695453744.4077127f; else MQvlyzfnA=1253398677.2399224f;int bsUrsHWxU=101193727;if (bsUrsHWxU == bsUrsHWxU- 0 ) bsUrsHWxU=1074401318; else bsUrsHWxU=1268210029;if (bsUrsHWxU == bsUrsHWxU- 0 ) bsUrsHWxU=1391362011; else bsUrsHWxU=970712545;if (bsUrsHWxU == bsUrsHWxU- 0 ) bsUrsHWxU=1462096130; else bsUrsHWxU=937335431;if (bsUrsHWxU == bsUrsHWxU- 1 ) bsUrsHWxU=1162455601; else bsUrsHWxU=121450694;if (bsUrsHWxU == bsUrsHWxU- 0 ) bsUrsHWxU=869791583; else bsUrsHWxU=557192572;if (bsUrsHWxU == bsUrsHWxU- 0 ) bsUrsHWxU=1985745461; else bsUrsHWxU=981343377;long EMiQKCiJI=1537324174;if (EMiQKCiJI == EMiQKCiJI- 1 ) EMiQKCiJI=1602114332; else EMiQKCiJI=505931386;if (EMiQKCiJI == EMiQKCiJI- 1 ) EMiQKCiJI=1371908218; else EMiQKCiJI=1714649162;if (EMiQKCiJI == EMiQKCiJI- 1 ) EMiQKCiJI=893018889; else EMiQKCiJI=1139627923;if (EMiQKCiJI == EMiQKCiJI- 1 ) EMiQKCiJI=1362346378; else EMiQKCiJI=2005399085;if (EMiQKCiJI == EMiQKCiJI- 1 ) EMiQKCiJI=1832730369; else EMiQKCiJI=113089440;if (EMiQKCiJI == EMiQKCiJI- 0 ) EMiQKCiJI=1319604584; else EMiQKCiJI=1379610672;float wRowjNLll=153698338.1604314f;if (wRowjNLll - wRowjNLll> 0.00000001 ) wRowjNLll=1915409145.9340897f; else wRowjNLll=1575735332.0525152f;if (wRowjNLll - wRowjNLll> 0.00000001 ) wRowjNLll=6798991.8623282f; else wRowjNLll=1717657141.8385203f;if (wRowjNLll - wRowjNLll> 0.00000001 ) wRowjNLll=2042348360.4046942f; else wRowjNLll=502399074.7206826f;if (wRowjNLll - wRowjNLll> 0.00000001 ) wRowjNLll=955483518.5700243f; else wRowjNLll=68776966.1921322f;if (wRowjNLll - wRowjNLll> 0.00000001 ) wRowjNLll=11713307.0666946f; else wRowjNLll=1748000428.6903111f;if (wRowjNLll - wRowjNLll> 0.00000001 ) wRowjNLll=365944379.5275764f; else wRowjNLll=1613731564.7951604f;double KacIzhcUA=608317668.5271239;if (KacIzhcUA == KacIzhcUA ) KacIzhcUA=795906918.8991914; else KacIzhcUA=158129570.6945174;if (KacIzhcUA == KacIzhcUA ) KacIzhcUA=1798767992.0069492; else KacIzhcUA=2105295705.1621480;if (KacIzhcUA == KacIzhcUA ) KacIzhcUA=1291263422.7380101; else KacIzhcUA=101559117.7090687;if (KacIzhcUA == KacIzhcUA ) KacIzhcUA=1355658485.0015855; else KacIzhcUA=2082257042.3128477;if (KacIzhcUA == KacIzhcUA ) KacIzhcUA=2053347298.4706450; else KacIzhcUA=1533446573.7761844;if (KacIzhcUA == KacIzhcUA ) KacIzhcUA=1285465823.0898152; else KacIzhcUA=1349006690.7177364;float cHhOVRMtY=748597797.9210532f;if (cHhOVRMtY - cHhOVRMtY> 0.00000001 ) cHhOVRMtY=457201900.6605658f; else cHhOVRMtY=1832047123.4122157f;if (cHhOVRMtY - cHhOVRMtY> 0.00000001 ) cHhOVRMtY=1213417879.7931514f; else cHhOVRMtY=1887939387.2385281f;if (cHhOVRMtY - cHhOVRMtY> 0.00000001 ) cHhOVRMtY=1802234996.3533935f; else cHhOVRMtY=1323622134.3389723f;if (cHhOVRMtY - cHhOVRMtY> 0.00000001 ) cHhOVRMtY=1642459461.7552152f; else cHhOVRMtY=1099715258.3901385f;if (cHhOVRMtY - cHhOVRMtY> 0.00000001 ) cHhOVRMtY=1697931515.3204882f; else cHhOVRMtY=1303131252.6002324f;if (cHhOVRMtY - cHhOVRMtY> 0.00000001 ) cHhOVRMtY=1702935855.6538925f; else cHhOVRMtY=1292502108.9432490f; }
 cHhOVRMtYy::cHhOVRMtYy()
 { this->LJTDtghcgHaC("UkPMZVyIHLJTDtghcgHaCj", true, 773683544, 1896098461, 764575251); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class mjVKDmJsIy
 { 
public: bool fWhOPXePf; double fWhOPXePfmjVKDmJsI; mjVKDmJsIy(); void COEkECqEIyMp(string fWhOPXePfCOEkECqEIyMp, bool DEjVQaykT, int nAVSgPsHo, float MyoNvudiY, long rkCFBIJVu);
 protected: bool fWhOPXePfo; double fWhOPXePfmjVKDmJsIf; void COEkECqEIyMpu(string fWhOPXePfCOEkECqEIyMpg, bool DEjVQaykTe, int nAVSgPsHor, float MyoNvudiYw, long rkCFBIJVun);
 private: bool fWhOPXePfDEjVQaykT; double fWhOPXePfMyoNvudiYmjVKDmJsI;
 void COEkECqEIyMpv(string DEjVQaykTCOEkECqEIyMp, bool DEjVQaykTnAVSgPsHo, int nAVSgPsHofWhOPXePf, float MyoNvudiYrkCFBIJVu, long rkCFBIJVuDEjVQaykT); };
 void mjVKDmJsIy::COEkECqEIyMp(string fWhOPXePfCOEkECqEIyMp, bool DEjVQaykT, int nAVSgPsHo, float MyoNvudiY, long rkCFBIJVu)
 { double WuhDZOUDx=1647219833.4511397;if (WuhDZOUDx == WuhDZOUDx ) WuhDZOUDx=106998998.0574297; else WuhDZOUDx=2028293344.6739484;if (WuhDZOUDx == WuhDZOUDx ) WuhDZOUDx=946465948.1757199; else WuhDZOUDx=2019693854.5799240;if (WuhDZOUDx == WuhDZOUDx ) WuhDZOUDx=432738715.9127073; else WuhDZOUDx=1704769472.3261601;if (WuhDZOUDx == WuhDZOUDx ) WuhDZOUDx=700005672.0434513; else WuhDZOUDx=532792882.8753196;if (WuhDZOUDx == WuhDZOUDx ) WuhDZOUDx=433729600.8851578; else WuhDZOUDx=48739842.7135118;if (WuhDZOUDx == WuhDZOUDx ) WuhDZOUDx=597576080.6965985; else WuhDZOUDx=591668596.4667371;float kWtqmaRFC=931357934.1024273f;if (kWtqmaRFC - kWtqmaRFC> 0.00000001 ) kWtqmaRFC=127791687.0154769f; else kWtqmaRFC=1610989181.5832098f;if (kWtqmaRFC - kWtqmaRFC> 0.00000001 ) kWtqmaRFC=1390074165.7629573f; else kWtqmaRFC=649018223.2696381f;if (kWtqmaRFC - kWtqmaRFC> 0.00000001 ) kWtqmaRFC=302447854.1431700f; else kWtqmaRFC=460491632.6441396f;if (kWtqmaRFC - kWtqmaRFC> 0.00000001 ) kWtqmaRFC=1211642946.4950605f; else kWtqmaRFC=1046560038.5157019f;if (kWtqmaRFC - kWtqmaRFC> 0.00000001 ) kWtqmaRFC=1087581711.5695985f; else kWtqmaRFC=1417854597.4123081f;if (kWtqmaRFC - kWtqmaRFC> 0.00000001 ) kWtqmaRFC=40675290.3893978f; else kWtqmaRFC=1284222857.7467877f;int qVisEInce=943055604;if (qVisEInce == qVisEInce- 1 ) qVisEInce=1138044674; else qVisEInce=128414073;if (qVisEInce == qVisEInce- 1 ) qVisEInce=267164790; else qVisEInce=1884248252;if (qVisEInce == qVisEInce- 1 ) qVisEInce=78254415; else qVisEInce=2100128294;if (qVisEInce == qVisEInce- 0 ) qVisEInce=396101941; else qVisEInce=2054325943;if (qVisEInce == qVisEInce- 1 ) qVisEInce=1950238683; else qVisEInce=1638399779;if (qVisEInce == qVisEInce- 1 ) qVisEInce=114507345; else qVisEInce=2144847970;int nARXVqUxK=282819170;if (nARXVqUxK == nARXVqUxK- 0 ) nARXVqUxK=1952373410; else nARXVqUxK=1621020558;if (nARXVqUxK == nARXVqUxK- 1 ) nARXVqUxK=934811586; else nARXVqUxK=403276837;if (nARXVqUxK == nARXVqUxK- 0 ) nARXVqUxK=2101557632; else nARXVqUxK=229324362;if (nARXVqUxK == nARXVqUxK- 0 ) nARXVqUxK=1344771979; else nARXVqUxK=1793991013;if (nARXVqUxK == nARXVqUxK- 0 ) nARXVqUxK=816650398; else nARXVqUxK=2047389557;if (nARXVqUxK == nARXVqUxK- 0 ) nARXVqUxK=932112143; else nARXVqUxK=1162367765;int ICcxSwrMA=1667342649;if (ICcxSwrMA == ICcxSwrMA- 0 ) ICcxSwrMA=1458539888; else ICcxSwrMA=1802004123;if (ICcxSwrMA == ICcxSwrMA- 1 ) ICcxSwrMA=1601107569; else ICcxSwrMA=471178929;if (ICcxSwrMA == ICcxSwrMA- 1 ) ICcxSwrMA=1465236926; else ICcxSwrMA=1930891056;if (ICcxSwrMA == ICcxSwrMA- 0 ) ICcxSwrMA=853103519; else ICcxSwrMA=175147040;if (ICcxSwrMA == ICcxSwrMA- 1 ) ICcxSwrMA=1214887240; else ICcxSwrMA=1483231869;if (ICcxSwrMA == ICcxSwrMA- 0 ) ICcxSwrMA=846263187; else ICcxSwrMA=811531722;int mjVKDmJsI=573515939;if (mjVKDmJsI == mjVKDmJsI- 0 ) mjVKDmJsI=5573019; else mjVKDmJsI=1905339767;if (mjVKDmJsI == mjVKDmJsI- 0 ) mjVKDmJsI=1479333094; else mjVKDmJsI=1342706570;if (mjVKDmJsI == mjVKDmJsI- 0 ) mjVKDmJsI=2126542659; else mjVKDmJsI=334406764;if (mjVKDmJsI == mjVKDmJsI- 1 ) mjVKDmJsI=988981619; else mjVKDmJsI=908720312;if (mjVKDmJsI == mjVKDmJsI- 0 ) mjVKDmJsI=931125741; else mjVKDmJsI=620657424;if (mjVKDmJsI == mjVKDmJsI- 0 ) mjVKDmJsI=1067597854; else mjVKDmJsI=178348505; }
 mjVKDmJsIy::mjVKDmJsIy()
 { this->COEkECqEIyMp("fWhOPXePfCOEkECqEIyMpj", true, 1168016151, 1381217823, 390231761); }
#pragma optimize("", off)
 // <delete/>


// <delete>
#pragma optimize("", off)
 #include <stdio.h>
   #include <string>
 #include <iostream>
 using namespace std;
 class mVZaZReEDy
 { 
public: bool bqWPsutWv; double bqWPsutWvmVZaZReED; mVZaZReEDy(); void QygztRjMPNHq(string bqWPsutWvQygztRjMPNHq, bool QGVXtagzv, int roiTAHrBL, float rMSpuaDCA, long GhtTWFLfk);
 protected: bool bqWPsutWvo; double bqWPsutWvmVZaZReEDf; void QygztRjMPNHqu(string bqWPsutWvQygztRjMPNHqg, bool QGVXtagzve, int roiTAHrBLr, float rMSpuaDCAw, long GhtTWFLfkn);
 private: bool bqWPsutWvQGVXtagzv; double bqWPsutWvrMSpuaDCAmVZaZReED;
 void QygztRjMPNHqv(string QGVXtagzvQygztRjMPNHq, bool QGVXtagzvroiTAHrBL, int roiTAHrBLbqWPsutWv, float rMSpuaDCAGhtTWFLfk, long GhtTWFLfkQGVXtagzv); };
 void mVZaZReEDy::QygztRjMPNHq(string bqWPsutWvQygztRjMPNHq, bool QGVXtagzv, int roiTAHrBL, float rMSpuaDCA, long GhtTWFLfk)
 { double hJpQkUtqg=1445766213.9621678;if (hJpQkUtqg == hJpQkUtqg ) hJpQkUtqg=1349512172.5945920; else hJpQkUtqg=320505816.0250346;if (hJpQkUtqg == hJpQkUtqg ) hJpQkUtqg=163264300.2720765; else hJpQkUtqg=238792578.3926916;if (hJpQkUtqg == hJpQkUtqg ) hJpQkUtqg=1222568578.9838872; else hJpQkUtqg=1307380293.3456152;if (hJpQkUtqg == hJpQkUtqg ) hJpQkUtqg=2111299141.7652357; else hJpQkUtqg=518561904.9029142;if (hJpQkUtqg == hJpQkUtqg ) hJpQkUtqg=1146702931.0391241; else hJpQkUtqg=336229267.5325750;if (hJpQkUtqg == hJpQkUtqg ) hJpQkUtqg=1350964536.4847237; else hJpQkUtqg=1190553319.4856691;double HwjSzOFcY=473259266.8208350;if (HwjSzOFcY == HwjSzOFcY ) HwjSzOFcY=2145433504.3095992; else HwjSzOFcY=746316532.6066135;if (HwjSzOFcY == HwjSzOFcY ) HwjSzOFcY=1411021164.9861101; else HwjSzOFcY=1254736942.7106527;if (HwjSzOFcY == HwjSzOFcY ) HwjSzOFcY=1475642260.9618133; else HwjSzOFcY=689074332.8649542;if (HwjSzOFcY == HwjSzOFcY ) HwjSzOFcY=1212972441.7653379; else HwjSzOFcY=1755068918.5582607;if (HwjSzOFcY == HwjSzOFcY ) HwjSzOFcY=801382676.9905857; else HwjSzOFcY=684553608.5680122;if (HwjSzOFcY == HwjSzOFcY ) HwjSzOFcY=1480924522.2226790; else HwjSzOFcY=765236731.6632594;long QecMgphWX=1499608086;if (QecMgphWX == QecMgphWX- 1 ) QecMgphWX=1618046673; else QecMgphWX=2030471248;if (QecMgphWX == QecMgphWX- 1 ) QecMgphWX=1927636561; else QecMgphWX=2047399746;if (QecMgphWX == QecMgphWX- 1 ) QecMgphWX=485606148; else QecMgphWX=1348640986;if (QecMgphWX == QecMgphWX- 1 ) QecMgphWX=569436073; else QecMgphWX=781114280;if (QecMgphWX == QecMgphWX- 0 ) QecMgphWX=1660277782; else QecMgphWX=1777517981;if (QecMgphWX == QecMgphWX- 1 ) QecMgphWX=1711523295; else QecMgphWX=450733789;long pbrmKlxmY=531021562;if (pbrmKlxmY == pbrmKlxmY- 1 ) pbrmKlxmY=1523645314; else pbrmKlxmY=1224219036;if (pbrmKlxmY == pbrmKlxmY- 1 ) pbrmKlxmY=142845401; else pbrmKlxmY=1009773780;if (pbrmKlxmY == pbrmKlxmY- 0 ) pbrmKlxmY=2016492706; else pbrmKlxmY=1427144574;if (pbrmKlxmY == pbrmKlxmY- 1 ) pbrmKlxmY=2117607600; else pbrmKlxmY=660437840;if (pbrmKlxmY == pbrmKlxmY- 1 ) pbrmKlxmY=1255017022; else pbrmKlxmY=555679029;if (pbrmKlxmY == pbrmKlxmY- 0 ) pbrmKlxmY=1584893549; else pbrmKlxmY=538014970;long hIUxgJlGf=1037905690;if (hIUxgJlGf == hIUxgJlGf- 1 ) hIUxgJlGf=1830883279; else hIUxgJlGf=1998840097;if (hIUxgJlGf == hIUxgJlGf- 0 ) hIUxgJlGf=1719990293; else hIUxgJlGf=1608605643;if (hIUxgJlGf == hIUxgJlGf- 0 ) hIUxgJlGf=1695993340; else hIUxgJlGf=1866214043;if (hIUxgJlGf == hIUxgJlGf- 1 ) hIUxgJlGf=2135136765; else hIUxgJlGf=796792518;if (hIUxgJlGf == hIUxgJlGf- 0 ) hIUxgJlGf=176880459; else hIUxgJlGf=629906884;if (hIUxgJlGf == hIUxgJlGf- 1 ) hIUxgJlGf=1741942807; else hIUxgJlGf=1845607926;double mVZaZReED=862720676.3597136;if (mVZaZReED == mVZaZReED ) mVZaZReED=1929847971.6304965; else mVZaZReED=949902960.4154624;if (mVZaZReED == mVZaZReED ) mVZaZReED=1389075064.5616941; else mVZaZReED=197698191.2739929;if (mVZaZReED == mVZaZReED ) mVZaZReED=2113435487.2174971; else mVZaZReED=1790539502.5568540;if (mVZaZReED == mVZaZReED ) mVZaZReED=1630599027.7807159; else mVZaZReED=190902099.0813965;if (mVZaZReED == mVZaZReED ) mVZaZReED=2060347295.7760472; else mVZaZReED=1267198721.0807540;if (mVZaZReED == mVZaZReED ) mVZaZReED=792382724.2594015; else mVZaZReED=2077410766.9329813; }
 mVZaZReEDy::mVZaZReEDy()
 { this->QygztRjMPNHq("bqWPsutWvQygztRjMPNHqj", true, 1911231084, 31421103, 954658509); }
#pragma optimize("", off)
 // <delete/>

