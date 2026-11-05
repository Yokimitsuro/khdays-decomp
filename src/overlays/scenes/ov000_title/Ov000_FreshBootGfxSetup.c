/* Ov000_FreshBootGfxSetup -- Scene 1 (boot/logo) fresh-boot graphics setup, ov000.
 * Reached from the scene-1 ctor Ov000_TitleInit on a fresh boot. Brings up the
 * 2D/3D display for the first screen: assigns VRAM banks (tex/OBJ-ext-pltt/BG/subBG/
 * subOBJ), programs both display engines (DISPCNT, BG control regs), loads the logo
 * archive (Archive_LoadFile) and 8 sub-resources into the scene heap, wires up the
 * animation/sequence players (Bg_LoadPaletteForScreen/ae0), copies a 0x200-byte palette, and
 * returns the scene's running state fn. arg selects the entry variant (0=fresh). */

#include "nitro/types.h"
#include "game/archive.h"

typedef void          *StateFn;

#define reg_GX_DISPCNT  (*(vu32 *)0x04000000)
#define reg_G2_BG0CNT   (*(vu16 *)0x04000008)

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  Ov000_PreloadLogoResources(void *heap);
extern void  SetMasterBrightnessMain(int);
extern void  SetMasterBrightnessSub(int);
extern void  GX_SetBankForTex(int);
extern void  GX_SetBankForTexPltt(int);
extern void  GX_SetBankForBG(int);
extern void  GX_SetBankForSubBG(int);
extern void  GX_SetBankForSubOBJ(int);
extern void  NNS_GfdInitFrmTexVramManager(int, int);
extern void  NNS_GfdInitFrmPlttVramManager(int, int);
extern void  GX_SetGraphicsMode(int, int, int);
extern void  GXS_SetGraphicsMode(int);
extern void  RegisterSeqAndInit(void *, u32, int, int);
extern void  BindAnimTrack(void *, int, void *, int);
extern void  Projection_LoadDefaults(void *);
extern u32   Archive_LoadFile(u32 addr, int mode);
extern void  Res_LoadSpriteSet(void *slot, u32 handle, int, int, int);
extern void  Bg_LoadPaletteForScreen(int, void *, void *, int, int);
extern void  Gfx_EnqueueTableCmdAt14(int, u32, int, u32);
extern void  MIi_CpuCopy32(void *src, void *dst, int size);
extern void  Ov000_Title_CreateLogoObjects(void);
extern void  SetGameMode(int);
extern void  Touch_StartAutoSampling(void);
extern void  Header_InitWithLimits(void *, void *);
extern void  Ov000_RestoreReentryGraphics(void);
extern int   Anim_GetLengthQ12(void *, int);
extern void  Anim_SetFrameWrapped(void *, int, int);
extern int   SoundStrm_HasPlaybackPos(int);
extern void  StampByteAndInvokeSubStructAt(int, int);
extern void  Ov000_HandoffState(void);
extern void  Ov000_LogoFadeState(void);
extern void  Ov000_ReentryState(void);
extern signed char data_ov000_0205a9d4[];

StateFn Ov000_FreshBootGfxSetup(int arg) {
    u32 *h = (u32 *)NNSi_FndGetCurrentRootHeap();
    Ov000_PreloadLogoResources(h);
    if (arg == 0) {
        SetMasterBrightnessMain(0x10);
        SetMasterBrightnessSub(0x10);
    } else {
        SetMasterBrightnessMain(-0x10);
        SetMasterBrightnessSub(-0x10);
    }
    GX_SetBankForTex(3);
    GX_SetBankForTexPltt(0x60);
    GX_SetBankForBG(0x10);
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    NNS_GfdInitFrmTexVramManager(2, 1);
    NNS_GfdInitFrmPlttVramManager(0x8000, 1);
    GX_SetGraphicsMode(1, 0, 1);

    {
        vu16 *bg1 = (vu16 *)0x0400000a;
        *bg1 = (*bg1 & 0x43) | 0x84;
        reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | 0x300;
        reg_G2_BG0CNT = reg_G2_BG0CNT & ~3;
        *bg1 = (*bg1 & ~3) | 1;
    }
    GXS_SetGraphicsMode(0);

    {
        vu16 *sub = (vu16 *)0x0400100a;
        vu32 *subd = (vu32 *)0x04001000;
        sub[0] = (sub[0] & 0x43) | 0x4084;
        sub[1] = (sub[1] & 0x43) | 0x4284;
        sub[2] = (sub[2] & 0x43) | 0x404;
        *subd = (*subd & ~0x1f00) | 0x1200;
        *subd = (*subd & 0xffcfffefu) | 0x10;
        sub[0] = (sub[0] & ~3) | 3;
        sub[1] = (sub[1] & ~3) | 2;
        sub[2] = (sub[2] & ~3) | 1;
    }

    RegisterSeqAndInit((void *)(h + 3), ARCHIVE_HANDLE(h[1], 0), 1, 0xe);
    BindAnimTrack((void *)(h + 3), 0, (void *)(h + 0x3b), 0);
    BindAnimTrack((void *)(h + 3), 2, (void *)(h + 0x3b), 0);
    Projection_LoadDefaults((void *)(h + 0x45));
    h[0x53] = Archive_LoadFile(ARCHIVE_HANDLE(h[1], 1), 0xe);

    {
        int i = 0;
        signed char *tbl = data_ov000_0205a9d4;
        u32 *slot = h + 0x54;
        do {
            Res_LoadSpriteSet(slot, h[0x53], tbl[0], tbl[1], tbl[2]);
            i++;
            tbl += 3;
            slot += 3;
        } while (i < 8);
    }

    Bg_LoadPaletteForScreen(1, (void *)h[0x62], (void *)h[0x60], 0, *(int *)(h[0x62] + 8));
    Gfx_EnqueueTableCmdAt14(1, h[0x61], 0, *(u32 *)(h[0x61] + 0x10));
    Bg_LoadPaletteForScreen(5, (void *)h[0x56], (void *)h[0x54], 0, *(int *)(h[0x56] + 8));
    Gfx_EnqueueTableCmdAt14(5, h[0x55], 0, *(u32 *)(h[0x55] + 0x10));

    MIi_CpuCopy32(*(void **)(h[0x6b] + 0xc), h + 0x131b, 0x200);

    if (arg != 1) {
        *((u8 *)h + 0x4c2e) = 0;
        *((u8 *)h + 0x4c2f) = 0;
    }
    if (arg == 2) {
        *((u8 *)h + 0x4c2d) = 0;
    }
    h[0x1316] = (arg != 0);

    Ov000_Title_CreateLogoObjects();
    SetGameMode(0);
    Touch_StartAutoSampling();
    h[0x130f] = 0;
    Header_InitWithLimits(h + 0x12fa, 0);

    if (arg != 0) {
        int n;
        Ov000_RestoreReentryGraphics();
        n = Anim_GetLengthQ12((void *)(h + 3), 0);
        Anim_SetFrameWrapped((void *)(h + 3), 0, n - 1);
        n = Anim_GetLengthQ12((void *)(h + 3), 2);
        Anim_SetFrameWrapped((void *)(h + 3), 2, n - 1);
        reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | 0x300;
        if (SoundStrm_HasPlaybackPos(0) == 0) {
            StampByteAndInvokeSubStructAt(0, 0);
        }
    }

    if (h[0x1311] != 0) {
        h[0] = 0x38;
        return (StateFn)Ov000_HandoffState;
    }
    h[0] = 0;
    return (arg == 0) ? (StateFn)Ov000_LogoFadeState : (StateFn)Ov000_ReentryState;
}
