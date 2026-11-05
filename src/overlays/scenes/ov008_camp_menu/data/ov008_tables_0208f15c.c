/* ov008 .rodata tables, 0x0208f15c-0x0208f8d0.
 *
 * 41 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208f15c: Ov008_InitGridMenuWidgets
 *   data_ov008_0208f180: Ov008_DrawMenuEntry
 *   data_ov008_0208f198: Ov008_ShowGridPage
 *   data_ov008_0208f1b0: Ov008_HideGridMenu
 *   data_ov008_0208f1cc: Ov008_FinishMenuModeSwitch
 *   data_ov008_0208f208: Ov008_BuildInventoryLists
 *   data_ov008_0208f248: Ov008_InitGridMenuSurfaces
 *   data_ov008_0208f270: Ov008_InitGridMenuSurfaces
 *   data_ov008_0208f298: Ov008_InitGridMenuSurfaces
 *   data_ov008_0208f2c0: Ov008_SetSavePageGroupVisible
 *   data_ov008_0208f2e8: Ov008_Menu_ChangePage
 *   data_ov008_0208f328: Ov008_GetPlayerSlotConfig
 *   data_ov008_0208f378: Ov008_DrawTextRow
 *   data_ov008_0208f3c8: Ov008_ComputeGridChanges
 *   data_ov008_0208f420: Ov008_InitGridMenuSurfaces
 *   data_ov008_0208f4e8: Ov008_SetMenuEntriesVisible, Ov008_SaveMenu_SlideArrows
 *   data_ov008_0208f4f0: Ov008_SetMenuEntriesVisible
 *   data_ov008_0208f500: Ov008_SaveMenu_BuildLayout
 *   data_ov008_0208f510: Ov008_SaveMenu_BuildTextSurfaces
 *   data_ov008_0208f538: Ov008_SaveMenu_BuildTextSurfaces
 *   data_ov008_0208f560: Ov008_SaveMenu_BuildTextSurfaces
 *   data_ov008_0208f588: Ov008_SaveMenu_BuildLayout, Ov008_TickPageScroll, Ov008_RefreshSaveRowDigits, Ov008_SaveMenu_RefreshRows
 *   data_ov008_0208f5e8: Ov008_Config_Setup
 *   data_ov008_0208f5f8: Ov008_DrawMenuPageTexts
 *   data_ov008_0208f618: Ov008_SetupMenuSurface
 *   data_ov008_0208f648: Ov008_LayoutMissionEntries
 *   data_ov008_0208f658: Ov008_LayoutMissionEntries
 *   data_ov008_0208f668: Ov008_DrawStatusPanelLabels
 *   data_ov008_0208f688: Ov008_InitStatusPanelSurfaces
 *   data_ov008_0208f6b0: Ov008_InitStatusPanelSurfaces
 *   data_ov008_0208f6d8: Ov008_InitStatusPanelSurfaces
 *   data_ov008_0208f700: Ov008_InitStatusPanelSurfaces
 *   data_ov008_0208f728: Ov008_InitStatusPanelSurfaces
 *   data_ov008_0208f750: Ov008_InitStatusPanelSurfaces
 *   data_ov008_0208f778: Ov008_DrawStatBar
 *   data_ov008_0208f7b0: Ov008_DrawPageBWidget
 *   data_ov008_0208f7f8: Ov008_RefreshEquipPanel
 *   data_ov008_0208f850: Ov008_GetLocalPlayerStatA
 *   data_ov008_0208f852: Ov008_GetLocalPlayerStatB
 *   data_ov008_0208f854: Ov008_GetLocalPlayerStatC
 *   data_ov008_0208f8c8: Ov008_PositionListCursor
 */

#include "nitro/types.h"

const int data_ov008_0208f15c[9] = {
    0, 1, 0, 0, 2, 3, 4, 14,
    15,
};

const int data_ov008_0208f180[6] = {
    12, 13, 19, 20, 21, 22,
};

const int data_ov008_0208f198[6] = {
    63, 64, 65, 60, 61, 62,
};

const int data_ov008_0208f1b0[7] = {
    41, 42, 43, 44, 45, 46, 47,
};

const int data_ov008_0208f1cc[15] = {
    41, 42, 43, 44, 45, 46, 47, 7,
    0, 1, 4, 3, 5, 6, 2,
};

const int data_ov008_0208f208[16] = {
    7, 0, 3, 1, 5, 4, 6, 2,
    7, 0, 3, 1, 5, 4, 6, 2,
};

const int data_ov008_0208f248[10] = {
    3, 13, 16, 24, 352, 15, 0, 6,
    0, 64,
};

const int data_ov008_0208f270[10] = {
    19, 0, 32, 4, 224, 15, 0, 7,
    0, 64,
};

const int data_ov008_0208f298[10] = {
    4, 14, 16, 10, 800, 15, 0, 5,
    0, 64,
};

const int data_ov008_0208f2c0[10] = {
    5, 6, 40, 41, 42, 43, 44, 45,
    46, 47,
};

const int data_ov008_0208f2e8[16] = {
    40, 41, 42, 43, 44, 45, 46, 47,
    20, 21, 22, 23, 24, 25, 26, 27,
};

const int data_ov008_0208f328[20] = {
    10, 0, 16, 11, 14, 12, 1, 4,
    5, 6, 7, 9, 13, 15, 17, 18,
    8, 2, 3, 10,
};

const u8 data_ov008_0208f378[80] = {
    3, 0, 0, 0, 16, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255,
    2, 0, 0, 0, 17, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255,
    5, 0, 0, 0, 18, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255,
    6, 0, 0, 0, 14, 0, 0, 0, 5, 0, 0, 0, 255, 255, 255, 255,
    4, 0, 0, 0, 15, 0, 0, 0, 2, 0, 0, 0, 255, 255, 255, 255,
};

const u8 data_ov008_0208f3c8[88] = {
    12, 0, 0, 0, 7, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0,
    2, 0, 0, 0, 12, 0, 0, 0, 8, 0, 0, 0, 11, 0, 0, 0,
    4, 0, 0, 0, 9, 0, 0, 0, 10, 0, 0, 0, 255, 255, 255, 255,
    3, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 5, 0, 0, 0,
    12, 0, 0, 0, 12, 0, 0, 0, 12, 0, 0, 0, 12, 0, 0, 0,
    12, 0, 0, 0, 12, 0, 0, 0,
};

const int data_ov008_0208f420[50] = {
    4, 15, 14, 2, 800, 15, 0, 5,
    0, 64, 7, 15, 14, 2, 828, 15,
    0, 5, 0, 64, 10, 15, 14, 2,
    856, 15, 0, 5, 0, 64, 13, 15,
    14, 2, 968, 15, 0, 5, 0, 64,
    16, 15, 14, 2, 996, 15, 0, 5,
    0, 64,
};

const int data_ov008_0208f4e8[2] = {
    20, 21,
};

const int data_ov008_0208f4f0[4] = {
    14, 16, 15, 61,
};

const int data_ov008_0208f500[4] = {
    0, 1, 0, 0,
};

const int data_ov008_0208f510[10] = {
    19, 0, 32, 4, 453, 15, 0, 5,
    0, 32,
};

const int data_ov008_0208f538[10] = {
    0, 14, 18, 2, 1, 15, 0, 5,
    0, 32,
};

const int data_ov008_0208f560[10] = {
    4, 0, 32, 13, 37, 15, 0, 5,
    0, 32,
};

const int data_ov008_0208f588[24] = {
    1, 31, 34, 37, 40, 50, 51, 52,
    2, 32, 35, 38, 41, 53, 54, 55,
    3, 33, 36, 39, 42, 56, 57, 58,
};

const int data_ov008_0208f5e8[4] = {
    0, 1, 0, 0,
};

const u8 data_ov008_0208f5f8[32] = {
    182, 255, 255, 255, 2, 0, 0, 0, 7, 0, 0, 0, 2, 0, 0, 0,
    204, 255, 255, 255, 2, 0, 0, 0, 7, 0, 0, 0, 2, 0, 0, 0,
};

const int data_ov008_0208f618[12] = {
    0, 0, 32, 24, 0, 15, 0, 5,
    0, 32, 7, 7,
};

const int data_ov008_0208f648[4] = {
    201, 203, 205, 207,
};

const int data_ov008_0208f658[4] = {
    0, 2, 0, 0,
};

const int data_ov008_0208f668[8] = {
    201, 202, 203, 204, 205, 206, 207, 208,
};

const int data_ov008_0208f688[10] = {
    0, 1, 20, 32, 256, 0, 0, 22,
    0, 64,
};

const int data_ov008_0208f6b0[10] = {
    18, 1, 22, 8, 256, 0, 0, 20,
    0, 64,
};

const int data_ov008_0208f6d8[10] = {
    1, 24, 8, 2, 432, 0, 0, 20,
    0, 64,
};

const int data_ov008_0208f700[10] = {
    10, 24, 9, 10, 448, 0, 0, 20,
    0, 64,
};

const int data_ov008_0208f728[10] = {
    1, 34, 22, 17, 538, 0, 0, 20,
    0, 64,
};

const int data_ov008_0208f750[10] = {
    22, 34, 22, 2, 955, 0, 0, 20,
    0, 64,
};

const int data_ov008_0208f778[14] = {
    40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53,
};

const int data_ov008_0208f7b0[18] = {
    201, 202, 203, 204, 205, 206, 207, 208,
    209, 210, 215, 216, 211, 212, 217, 218,
    213, 214,
};

const u8 data_ov008_0208f7f8[88] = {
    12, 0, 0, 0, 7, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0,
    2, 0, 0, 0, 12, 0, 0, 0, 8, 0, 0, 0, 11, 0, 0, 0,
    4, 0, 0, 0, 9, 0, 0, 0, 10, 0, 0, 0, 255, 255, 255, 255,
    3, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 5, 0, 0, 0,
    12, 0, 0, 0, 12, 0, 0, 0, 12, 0, 0, 0, 12, 0, 0, 0,
    12, 0, 0, 0, 12, 0, 0, 0,
};

const u16 data_ov008_0208f850[1] = {
    33,
};

const u16 data_ov008_0208f852[1] = {
    10,
};

const u8 data_ov008_0208f854[116] = {
    54, 0, 28, 0, 0, 0, 49, 0, 22, 0, 16, 0, 43, 0, 27, 0,
    11, 0, 48, 0, 23, 0, 14, 0, 44, 0, 36, 0, 12, 0, 57, 0,
    29, 0, 1, 0, 50, 0, 32, 0, 4, 0, 53, 0, 25, 0, 5, 0,
    46, 0, 30, 0, 6, 0, 51, 0, 31, 0, 7, 0, 52, 0, 37, 0,
    9, 0, 58, 0, 24, 0, 13, 0, 45, 0, 21, 0, 15, 0, 42, 0,
    34, 0, 17, 0, 55, 0, 26, 0, 18, 0, 47, 0, 35, 0, 8, 0,
    56, 0, 38, 0, 2, 0, 59, 0, 39, 0, 3, 0, 60, 0, 33, 0,
    10, 0, 54, 0,
};

const u8 data_ov008_0208f8c8[8] = {
    0, 128, 255, 255, 0, 128, 253, 255,
};
