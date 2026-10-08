/* ============================================================================
 *  main  (0x02000bcc, 0x350 bytes)  --  KH 358/2 Days ARM9 static game entry
 * ----------------------------------------------------------------------------
 *  Byte-exact reconstruction of the ARM9 game entry point.  The source retains
 *  the matching-sensitive control flow, overlay-ID idiom, and structure layouts.
 *
 *  BOOT CHAIN
 *    crt0 (0x02000800): set stacks/CPU modes, clear .bss, flush cache,
 *                       NitroSDK init, then `ldr r1,[=main]; bx r1`  -> main().
 *
 *  main() DOES, IN ORDER:
 *    1. Core services up + the ov001 ONE-SHOT hardware-init overlay:
 *         FS_LoadOverlay(0, OV_BOOT)  ->  ov001_BootInit()  ->  FS_UnloadOverlay
 *       (ov001 only exists to run the DS HW bring-up once.)
 *    2. Take the game's language from the firmware's owner profile:
 *         Msg_SetLanguage(the firmware language if it is 1..5 (English .. Spanish),
 *                         otherwise 1, English; 0)
 *    3. Load the boot resource tables and INSTANTIATE THE ROOT/BOOT TASK:
 *         InstantiateClass(&gBootTaskClass, 1)
 *       gBootTaskClass -> BootTask_Construct (0x02020928, THUMB)
 *       which, on a fresh boot (state @0x027ffc20 == 0), selects Scene 1 (the
 *       boot/logo scene) via Scene_RequestPending(SCENE_TITLE, 0).
 *    4. Run the frame loop forever (label FRAME @0x02000cac):
 *         VBlank sync -> update the task queue -> 3D/capture render -> present ->
 *         poll the current scene; when it ends, run the fade/teardown transition
 *         and loop.  The active scene id lives in data_027e0060.
 * ==========================================================================*/

#include "nitro/types.h"
#include "nitro/os_types.h"

#include "game/scene.h"
typedef u32 FSOverlayID;

extern u32 OVERLAY_1_ID[1];
#define FS_OVERLAY_ID_ov001 ((FSOverlayID)(u32)&OVERLAY_1_ID)

/* ---- core services / overlays ---- */
extern void  OS_Init(void);                 /* early system init            */
extern void  FS_Init(int mode);                   /* 0x0200a9a8                   */
extern int   FS_LoadOverlay(int proc, FSOverlayID overlay);
extern int   FS_UnloadOverlay(int proc, FSOverlayID overlay);
extern void  Ov001_BootInit(void);           /* ov001_BootInit  (HW init)    */
extern void  G3d_InitSbcFuncTable(void);                 /* subsystem init               */
extern void  InputState_Init(void);                 /* task-system init             */
extern void  OS_GetOwnerInfo(OSOwnerInfo *info);
/* The game's language; main passes a second word, 0, which the function does not read. */
extern void  Msg_SetLanguage(int language, int unused);
extern int   func_02016264(void *list);           /* init global list             */
extern int   FS_TryLoadTable(int a, int b);       /* 0x0200b100  resource table   */
extern int   AllocFromExpHeapWrapper(int handle, int arena);
extern void  Obj_InitSystem(void);
extern void  Callbacks_Init(void);
extern void  SoundCtx_Init(void);
extern void  InstantiateClass(void *classDesc, int ctorArg);

/* ---- per-frame ---- */
extern void  OS_WaitVBlankIntr(void);             /* 0x02003878  frame begin      */
extern unsigned int VBlank_GetCount(void);   /* GetVBlankCount               */
extern void  GXi_FlushCommandList(void);                 /* present / VBlank swap        */
extern void  FrameStep_UpdateTaskQueue(void);                 /* FrameStep_UpdateTaskQueue    */
extern void  Pad_Sample(void);                 /* per-frame update B           */
extern void  G3X_ResetMtxStack(void);             /* 0x02006d6c                   */
extern void  Obj_UpdateAll(int a);                /* render path A (3D)           */
extern void  Callbacks_Run(int a);                /* render path B (capture)      */
extern void  SoundMgr_Update(void);
extern int   Game_PollSceneAlive(void);                 /* Game_PollSceneAlive          */

/* ---- transition / teardown ---- */
extern void  GX_DispOff(void);
extern void  DispCnt_ApplyPendingMode(void);
extern int   PM_SetLCDPower(int a);                /* DispatchNormalizedArg        */
extern int   PM_GoSleepMode(int a, int b, int c);
extern int   PM_GetLCDPower(void);
extern int   Sleep_IsAllowed(void);
extern void  NNS_SndPlayerPauseAll(int flag);
extern int   SoundMgr_PauseBgm(int flag);
extern void  OS_Sleep(unsigned int ms);
extern int  GetMasterBrightnessMain(void);
extern void  SetMasterBrightnessMain(int brightness);
extern int  GetMasterBrightnessSub(void);
extern void  SetMasterBrightnessSub(int brightness);

/* ---- globals ---- */
extern unsigned char data_027e0060;   /* current scene id (0 = none)              */
extern void         *data_027e0350;   /* boot resource list head                  */
extern int           data_0204c024;   /* default arena ref                        */
extern unsigned char data_0204c215;   /* "present pending" flag                   */
extern unsigned char gPauseMode;   /* display mode byte (0/1/2)                */
extern unsigned char gObjSystem;   /* frame-rate/skip mode byte                */
extern void         *gBootTaskClass;       /* root task class descriptor           */

/* scene-render state struct @ data_020442a0: +0x00 u8 displays off (lid closed), +0x04 handle */
struct SceneState { unsigned char phase; unsigned char _p[3]; int handle; };
extern struct SceneState data_020442a0;

/* the ARM7's X/Y word @ 0x027fffa8: X, Y and debug in bits 10, 11 and 13 (active low), the
 * hinge in bit 15 (1 = lid closed) */
#define ARM7_KEYS  (*(volatile unsigned short *)0x027fffa8)
#define LID_CLOSED ((ARM7_KEYS & 0x8000) >> 15)
#define REG_0540   (*(volatile unsigned int   *)0x04000540)

int main(void) {
    OSOwnerInfo owner;
    unsigned int  frameTarget;

    /* --- 1. core services + ov001 one-shot HW init --- */
    OS_Init();
    FS_Init(3);
    FS_LoadOverlay(0, FS_OVERLAY_ID_ov001);
    Ov001_BootInit();         /* ov001_BootInit -- DS hardware bring-up  */
    FS_UnloadOverlay(0, FS_OVERLAY_ID_ov001);
    G3d_InitSbcFuncTable();
    InputState_Init();

    /* --- 2. the firmware's language -> the game's (English unless it is one of the five) --- */
    OS_GetOwnerInfo(&owner);
    {
        int language = owner.language;
        switch (language) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    default:
            language = OS_LANGUAGE_ENGLISH;
        break;
        }
        Msg_SetLanguage(language, 0);
    }

    /* --- 3. boot resource tables + root/boot task --- */
    func_02016264(&data_027e0350);
    data_020442a0.handle = AllocFromExpHeapWrapper(FS_TryLoadTable(0, 0), data_0204c024);
    FS_TryLoadTable(data_020442a0.handle, FS_TryLoadTable(0, 0));
    Obj_InitSystem();
    data_0204c215 = 0;
    Callbacks_Init();
    SoundCtx_Init();
    InstantiateClass(&gBootTaskClass, 1);   /* -> BootTask_Construct -> Scene 1 */

    /* --- 4. FRAME LOOP (0x02000cac) --- */
    for (;;) {
        OS_WaitVBlankIntr();                     /* frame begin              */
        frameTarget = VBlank_GetCount();    /* VBlank count snapshot    */
        FrameStep_UpdateTaskQueue();                         /* update task queue        */
        Pad_Sample();
        G3X_ResetMtxStack();

        switch (gPauseMode) {                 /* display mode             */
        case 0: Obj_UpdateAll(0); break;
        case 1: Callbacks_Run(1); frameTarget = VBlank_GetCount(); break;
        case 2: Obj_UpdateAll(0); Callbacks_Run(1); break;
        }
        SoundMgr_Update();

        /* frame-rate pacing: advance whole frames until we reach the target */
        if (gObjSystem != 2) {
            frameTarget += (gObjSystem == 1) ? 2 : 1;
            while (VBlank_GetCount() < frameTarget) {
                OS_WaitVBlankIntr();
                FrameStep_UpdateTaskQueue();
            }
        }

        /* present (unless mode 1 already did its own swap) */
        if (gPauseMode != 1) {
            GXi_FlushCommandList();
            REG_0540 = 1;
            data_0204c215 = 1;
        }

        /* --- poll the current scene --- */
        if (Game_PollSceneAlive() != 0) {
            unsigned char phase = data_020442a0.phase;

            /* scene running: closing the lid turns the displays off, opening it turns them on */
            if (phase == 0) {
                if (LID_CLOSED != 0) {
                    GX_DispOff();
                    PM_SetLCDPower(0);
                    data_020442a0.phase = 1;
                    continue;
                }
            }
            if (phase != 0) {
                if (LID_CLOSED == 0 && PM_SetLCDPower(1) != 0) {
                    data_020442a0.phase = 0;
                    SetMasterBrightnessMain(GetMasterBrightnessMain());
                    SetMasterBrightnessSub(GetMasterBrightnessSub());
                    DispCnt_ApplyPendingMode();
                }
            }
            continue;
        }

        /* --- scene ended: run fade/teardown transition --- */
        if (Sleep_IsAllowed() == 0) continue;
        if (LID_CLOSED != 1) continue;

        if (gPauseMode == 0) NNS_SndPlayerPauseAll(1); else SoundMgr_PauseBgm(1);
        PM_GoSleepMode(0xc, 0, 0);
        if (gPauseMode == 0) NNS_SndPlayerPauseAll(0); else SoundMgr_PauseBgm(0);

        if (PM_GetLCDPower() == 0) {
            if (PM_SetLCDPower(1) == 0) {
                do { OS_Sleep(0x64); } while (PM_SetLCDPower(1) == 0);
            }
            DispCnt_ApplyPendingMode();
            data_020442a0.phase = 0;
        }
        SetMasterBrightnessMain(GetMasterBrightnessMain());
        SetMasterBrightnessSub(GetMasterBrightnessSub());
    }
}
