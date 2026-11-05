/*
 * Ov002_OpenTutorialPage - build the tutorial page and hand back its step.
 *
 * The page object is taken from the scene, cleared and given its text writer.
 * The sub screen's background layers are remembered and switched to the pair
 * this screen needs, the tile map is filled and slot 0x1a claimed. Both text
 * containers are opened, the two entries this page answers to are registered,
 * and the surfaces are built - the wide set for tutorial 0x12, the plain one
 * otherwise. Unless the panel is already showing, the two side nodes are armed.
 *
 * THUMB.
 */

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

extern int *data_ov002_0207f9fc;
extern char gOv002UiTutorialRootTextPath[];
extern char gOv002UiBtlttrTtrPath[];
extern char gOv002UiBtlttrTtrPath_2[];
extern char gOv002UiBtlttrTtrPath_3[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDst, int nValue, int nSize);
extern void Ov002_InitResourceRecord(int pWriter, int pResource);
extern void Ov002_FillMapRows(int nSlot, int nX, int nY, short nWidth,
                                short nHeight);
extern void Ov002_SelectEntry(int nSlot);
extern int Msg_OpenContainerAndReadHeader(char *pName, u32 nId);
extern void Ov002_AppendEntry(int nKey, int pfnDone, int nArg);
extern void Ov002_RebuildHudSurface(void);
extern void Ov002_BuildHudRecordSurfaces(void);
extern int Ov002_GetPanelField005c(void);
extern int Ov002_Ctx_FindActiveEntryByTag(int nTag);
extern void Ov002_Ctx_SetTagTrackerNodeArmed_5(int hNode, int nArg);
extern void Ov002_TakePageIntoSubObject(void);
extern void Ov002_UploadPageToSubBg2Char(void);
extern void Ov002_RunSceneStateHandler(void);

#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)

void *Ov002_OpenTutorialPage(u16 nTutorial)
{
    int hud;

    hud = (int)NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f9fc = (int *)hud;
    MI_CpuFill8((void *)hud, 0, 0x1b0);
    Ov002_InitResourceRecord(hud + 0x19c, (int)gOv002UiTutorialRootTextPath);
    *(int *)(hud + 0x2c) = (REG_DISPCNT_SUB & 0x1f00) >> 8;
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & 0xffffe0ff) | 0xc00;
    Ov002_FillMapRows(0x1a, 0, 0, 0x20, 0x20);
    Ov002_SelectEntry(0x1a);
    *(u16 *)hud = nTutorial;
    *(int *)(hud + 4) = Msg_OpenContainerAndReadHeader(gOv002UiBtlttrTtrPath, 0xe);
    *(int *)(hud + 8) = Msg_OpenContainerAndReadHeader(gOv002UiBtlttrTtrPath_2, 0xe);
    Ov002_AppendEntry((int)gOv002UiBtlttrTtrPath_3, (int)Ov002_TakePageIntoSubObject, 0);
    Ov002_AppendEntry(ARCHIVE_HANDLE(*(int *)(hud + 8), 0x30), (int)Ov002_UploadPageToSubBg2Char, 0);
    *(int *)(hud + 0x30) = *(u16 *)hud == 0x12;
    *(int *)(hud + 0x28) = 2;
    if (*(int *)(hud + 0x30) != 0) {
        Ov002_BuildHudRecordSurfaces();
    } else {
        Ov002_RebuildHudSurface();
    }
    if (Ov002_GetPanelField005c() == 0) {
        Ov002_Ctx_SetTagTrackerNodeArmed_5(Ov002_Ctx_FindActiveEntryByTag(0x18), 1);
        Ov002_Ctx_SetTagTrackerNodeArmed_5(Ov002_Ctx_FindActiveEntryByTag(0x19), 1);
    }
    PlaySound(0, 2);
    return Ov002_RunSceneStateHandler;
}
