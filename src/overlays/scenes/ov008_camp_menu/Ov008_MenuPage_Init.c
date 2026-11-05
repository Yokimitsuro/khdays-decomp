/* Resets the page's slot state, widgets and texts and moves the cursor to the first entry; returns
 * 1. */

extern void Ov008_GetMenuContext(void);
extern void Ov008_ResetMissionSlotState(void);
extern void Ov008_SetupGridMenuDisplay(void);
extern void Ov008_LoadMenuBgWithAltChars(void);
extern void Ov008_Config_Setup(void);
extern void Ov008_SetupMenuSurface(void);
extern void Ov008_MoveMenuCursor(int arg0);

int Ov008_MenuPage_Init(void)
{
    Ov008_GetMenuContext();
    Ov008_ResetMissionSlotState();
    Ov008_SetupGridMenuDisplay();
    Ov008_LoadMenuBgWithAltChars();
    Ov008_Config_Setup();
    Ov008_SetupMenuSurface();
    Ov008_MoveMenuCursor(0);
    return 1;
}
