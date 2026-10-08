/* Tear down the ov106 scene: field 0x248c is cleared, the scene layers close (020b7c50), window 0
 * spans the whole screen and the sub engine's windows are disabled, the gOv106Dual3DUpdateName resource
 * is released, the +0x8b38 model, the +0x8cd0 and +0x8bc4 widgets and the +0x8e40 handle are freed,
 * and the scene pointer clears. */

#include "nitro/types.h"

extern char *data_ov106_020b8b60;
extern char gOv106Dual3DUpdateName[];
extern void GameState_SetField(int field, int width, int value);
extern void Ov106_SelectScreenLayers(void);
extern void VBlank_UnregisterCallback(int a, void *b);
extern void Gfx_SetupSubEngine(void *p);
extern void ReleaseField74AndCleanup(void *p);
extern void SoundMgr_SetSeEnabled(char arg0);
extern void VeneerTo_Obj_Destroy(int handle);
extern void StoreGlobalArrayEntry(int nId, int nFlags);

void Ov106_TeardownScene(void)
{
    GameState_SetField(0x248c, 1, 0);
    Ov106_SelectScreenLayers();
    *(volatile u16 *)0x04000040 = 0xff;
    *(volatile u16 *)0x04000044 = 0xc0;
    *(volatile u32 *)0x04001000 &= ~0xe000;
    VBlank_UnregisterCallback(1, gOv106Dual3DUpdateName);
    Gfx_SetupSubEngine(data_ov106_020b8b60 + 0x8b38);
    ReleaseField74AndCleanup(data_ov106_020b8b60 + 0x8cd0);
    ReleaseField74AndCleanup(data_ov106_020b8b60 + 0x8bc4);
    SoundMgr_SetSeEnabled(1);
    VeneerTo_Obj_Destroy(*(int *)(data_ov106_020b8b60 + 0x8e40));
    StoreGlobalArrayEntry(0x14, 0);
    data_ov106_020b8b60 = 0;
}
