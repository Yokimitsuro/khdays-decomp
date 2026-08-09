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
 *    2. Read the boot mode (0..5) and pick the initial game mode:
 *         SetGameMode(valid boot mode 1..5, otherwise 1, 0)
 *    3. Load the boot resource tables and INSTANTIATE THE ROOT/BOOT TASK:
 *         func_02023930(&data_02042534, 1)
 *       data_02042534 -> BootTask_Construct (0x02020928, THUMB)
 *       which, on a fresh boot (state @0x027ffc20 == 0), selects Scene 1 (the
 *       boot/logo scene) via StoreGlobalPairAt10(1, 0).
 *    4. Run the frame loop forever (label FRAME @0x02000cac):
 *         VBlank sync -> update the task queue -> 3D/capture render -> present ->
 *         poll the current scene; when it ends, run the fade/teardown transition
 *         and loop.  The active scene id lives in data_027e0060.
 * ==========================================================================*/

typedef unsigned int u32;
typedef u32 FSOverlayID;

extern u32 OVERLAY_1_ID[1];
#define FS_OVERLAY_ID_ov001 ((FSOverlayID)(u32)&OVERLAY_1_ID)

/* ---- core services / overlays ---- */
extern void  func_020027f0(void);                 /* early system init            */
extern void  FS_Init(int mode);                   /* 0x0200a9a8                   */
extern int   FS_LoadOverlay(int proc, FSOverlayID overlay);
extern int   FS_UnloadOverlay(int proc, FSOverlayID overlay);
extern void  func_ov001_0204cd7c(void);           /* ov001_BootInit  (HW init)    */
extern void  func_020285f0(void);                 /* subsystem init               */
extern void  func_02023f58(void);                 /* task-system init             */
struct BootSettings {
    unsigned char mode;
    unsigned char flags;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char data04[0x14];
    unsigned short reserved18;
    unsigned short field1a;
    unsigned char data1c[0x34];
    unsigned short reserved50;
    unsigned short field52;
};

extern void  func_02003a20(struct BootSettings *out);
extern void  func_02024e34(int mode, int arg);    /* SetGameMode                  */
extern int   func_02016264(void *list);           /* init global list             */
extern int   FS_TryLoadTable(int a, int b);       /* 0x0200b100  resource table   */
extern int   func_020236cc(int handle, int arena);
extern void  func_0202390c(void);
extern void  func_02020834(void);
extern void  func_02032db8(void);
extern void  func_02023930(void *classDesc, int ctorArg);

/* ---- per-frame ---- */
extern void  OS_WaitVBlankIntr(void);             /* 0x02003878  frame begin      */
extern unsigned int OS_IsThreadAvailable(void);   /* GetVBlankCount               */
extern void  func_01ff80b8(void);                 /* present / VBlank swap        */
extern void  func_020115b8(void);                 /* FrameStep_UpdateTaskQueue    */
extern void  func_02023f78(void);                 /* per-frame update B           */
extern void  G3X_ResetMtxStack(void);             /* 0x02006d6c                   */
extern void  func_02023adc(int a);                /* render path A (3D)           */
extern void  func_020208a4(int a);                /* render path B (capture)      */
extern void  func_02032f5c(void);
extern int   func_02001030(void);                 /* Game_PollSceneAlive          */

/* ---- transition / teardown ---- */
extern void  func_02005630(void);
extern void  func_0200566c(void);
extern int   func_0200d49c(int a);                /* DispatchNormalizedArg        */
extern int   func_0200d164(int a, int b, int c);
extern int   func_0200d4bc(void);
extern int   func_02020914(void);
extern void  func_0201a014(int flag);
extern int   func_02033c64(int flag);
extern void  OS_Sleep(unsigned int ms);
extern void  func_0201e428(void);
extern void  func_0201e374(void);
extern void  func_0201e438(void);
extern void  func_0201e3cc(void);

/* ---- globals ---- */
extern unsigned char data_027e0060;   /* current scene id (0 = none)              */
extern void         *data_027e0350;   /* boot resource list head                  */
extern int           data_0204c024;   /* default arena ref                        */
extern unsigned char data_0204c215;   /* "present pending" flag                   */
extern unsigned char data_0204bd84;   /* display mode byte (0/1/2)                */
extern unsigned char data_0204c058;   /* frame-rate/skip mode byte                */
extern void         *data_02042534;       /* root task class descriptor           */

/* scene-render state struct @ data_020442a0: +0x00 u8 phase flag, +0x04 handle */
struct SceneState { unsigned char phase; unsigned char _p[3]; int handle; };
extern struct SceneState data_020442a0;

/* held-keys mirror @ 0x027fffa8; bit 0x8000 gates transitions */
#define HELD_KEYS  (*(volatile unsigned short *)0x027fffa8)
#define HELD_TRANSITION ((HELD_KEYS & 0x8000) >> 15)
#define REG_0540   (*(volatile unsigned int   *)0x04000540)

int main(void) {
    struct BootSettings boot;
    unsigned int  frameTarget;

    /* --- 1. core services + ov001 one-shot HW init --- */
    func_020027f0();
    FS_Init(3);
    FS_LoadOverlay(0, FS_OVERLAY_ID_ov001);
    func_ov001_0204cd7c();         /* ov001_BootInit -- DS hardware bring-up  */
    FS_UnloadOverlay(0, FS_OVERLAY_ID_ov001);
    func_020285f0();
    func_02023f58();

    /* --- 2. boot mode -> initial game mode --- */
    func_02003a20(&boot);
    {
        int mode = boot.mode;
        switch (mode) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    default:
            mode = 1;
        break;
        }
        func_02024e34(mode, 0);
    }

    /* --- 3. boot resource tables + root/boot task --- */
    func_02016264(&data_027e0350);
    data_020442a0.handle = func_020236cc(FS_TryLoadTable(0, 0), data_0204c024);
    FS_TryLoadTable(data_020442a0.handle, FS_TryLoadTable(0, 0));
    func_0202390c();
    data_0204c215 = 0;
    func_02020834();
    func_02032db8();
    func_02023930(&data_02042534, 1);   /* -> BootTask_Construct -> Scene 1 */

    /* --- 4. FRAME LOOP (0x02000cac) --- */
    for (;;) {
        OS_WaitVBlankIntr();                     /* frame begin              */
        frameTarget = OS_IsThreadAvailable();    /* VBlank count snapshot    */
        func_020115b8();                         /* update task queue        */
        func_02023f78();
        G3X_ResetMtxStack();

        switch (data_0204bd84) {                 /* display mode             */
        case 0: func_02023adc(0); break;
        case 1: func_020208a4(1); frameTarget = OS_IsThreadAvailable(); break;
        case 2: func_02023adc(0); func_020208a4(1); break;
        }
        func_02032f5c();

        /* frame-rate pacing: advance whole frames until we reach the target */
        if (data_0204c058 != 2) {
            frameTarget += (data_0204c058 == 1) ? 2 : 1;
            while (OS_IsThreadAvailable() < frameTarget) {
                OS_WaitVBlankIntr();
                func_020115b8();
            }
        }

        /* present (unless mode 1 already did its own swap) */
        if (data_0204bd84 != 1) {
            func_01ff80b8();
            REG_0540 = 1;
            data_0204c215 = 1;
        }

        /* --- poll the current scene --- */
        if (func_02001030() != 0) {
            unsigned char phase = data_020442a0.phase;

            /* scene still running: handle its transition request via input */
            if (phase == 0) {
                if (HELD_TRANSITION != 0) {
                    func_02005630();
                    func_0200d49c(0);
                    data_020442a0.phase = 1;
                    continue;
                }
            }
            if (phase != 0) {
                if (HELD_TRANSITION == 0 && func_0200d49c(1) != 0) {
                    data_020442a0.phase = 0;
                    func_0201e428(); func_0201e374();
                    func_0201e438(); func_0201e3cc();
                    func_0200566c();
                }
            }
            continue;
        }

        /* --- scene ended: run fade/teardown transition --- */
        if (func_02020914() == 0) continue;
        if (HELD_TRANSITION != 1) continue;

        if (data_0204bd84 == 0) func_0201a014(1); else func_02033c64(1);
        func_0200d164(0xc, 0, 0);
        if (data_0204bd84 == 0) func_0201a014(0); else func_02033c64(0);

        if (func_0200d4bc() == 0) {
            if (func_0200d49c(1) == 0) {
                do { OS_Sleep(0x64); } while (func_0200d49c(1) == 0);
            }
            func_0200566c();
            data_020442a0.phase = 0;
        }
        func_0201e428(); func_0201e374();
        func_0201e438(); func_0201e3cc();
    }
}
