/* ============================================================================
 *  main  (0x02000bcc, 0x350 bytes)  --  KH 358/2 Days ARM9 static game entry
 * ----------------------------------------------------------------------------
 *  READABLE RECONSTRUCTION for the PC port (Fase 4).  This is NOT byte-verified,
 *  so it lives in nonmatching/ (ignored by the build).  It follows the original
 *  control flow instruction-for-instruction; extern names are the project's real
 *  func_/named symbols, annotated with the role discovered while tracing.
 *
 *  BOOT CHAIN
 *    crt0 (0x02000800): set stacks/CPU modes, clear .bss, flush cache,
 *                       NitroSDK init, then `ldr r1,[=main]; bx r1`  -> main().
 *
 *  main() DOES, IN ORDER:
 *    1. Core services up + the ov001 ONE-SHOT hardware-init overlay:
 *         FS_LoadOverlay(0, OV_BOOT)  ->  ov001_BootInit()  ->  FS_UnloadOverlay
 *       (ov001 only exists to run the DS HW bring-up once; the PC port replaces
 *        ov001_BootInit entirely with its platform layer.)
 *    2. Read the boot mode (0..5) and pick the initial game mode:
 *         SetGameMode(bootmode == 0 ? 1 : bootmode, 0)
 *    3. Load the boot resource tables and INSTANTIATE THE ROOT/BOOT TASK:
 *         InstantiateClass(&g_BootTaskClassDesc, 1)
 *       g_BootTaskClassDesc (@0x02042534) -> BootTask_Construct (0x02020928,THUMB)
 *       which, on a fresh boot (state @0x027ffc20 == 0), selects Scene 1 (the
 *       boot/logo scene) via StoreGlobalPairAt10(1, 0).
 *    4. Run the frame loop forever (label FRAME @0x02000cac):
 *         VBlank sync -> update the task queue -> 3D/capture render -> present ->
 *         poll the current scene; when it ends, run the fade/teardown transition
 *         and loop.  The active scene id lives in data_027e0060.
 * ==========================================================================*/

/* ---- core services / overlays ---- */
extern void  func_020027f0(void);                 /* early system init            */
extern void  FS_Init(int mode);                   /* 0x0200a9a8                   */
extern void  FS_LoadOverlay(int proc, int ovId);  /* 0x0200b6ac  (ovId 1 = ov001) */
extern void  FS_UnloadOverlay(int proc, int ovId); /* 0x0200b700                  */
extern void  func_0204cd7c(void);                 /* ov001_BootInit  (HW init)    */
extern void  func_020285f0(void);                 /* subsystem init               */
extern void  func_02023f58(void);                 /* task-system init             */
extern void  func_02003a20(unsigned char *out);   /* ReadBootMode -> *out = 0..5  */
extern void  func_02024e34(int mode, int arg);    /* SetGameMode                  */
extern int   func_02016264(void *list);           /* init global list             */
extern int   FS_TryLoadTable(int a, int b);       /* 0x0200b100  resource table   */
extern int   func_020236cc(int handle, int arena);
extern void  func_0202390c(void);
extern void  func_02020834(void);
extern void  func_02032db8(void);
extern void  InstantiateClass(void *classDesc, int ctorArg); /* 0x02023930       */

/* ---- per-frame ---- */
extern void  OS_WaitVBlankIntr(void);             /* 0x02003878  frame begin      */
extern unsigned int func_01ff80a8(void);          /* GetVBlankCount               */
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
extern void  func_0201a014(void);
extern void  func_02033c64(void);
extern void  func_020020dc(int a);
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
extern void         *g_BootTaskClassDesc; /* 0x02042534                           */

/* scene-render state struct @ data_020442a0: +0x00 u8 phase flag, +0x04 handle */
struct SceneState { unsigned char phase; unsigned char _p[3]; int handle; };
extern struct SceneState data_020442a0;

/* held-keys mirror @ 0x027fffa8; bit 0x8000 gates transitions */
#define HELD_KEYS  (*(volatile unsigned short *)0x027fffa8)
#define REG_0540   (*(volatile unsigned int   *)0x04000540)

int main(void) {
    unsigned char bootmode;
    unsigned int  frameTarget;

    /* --- 1. core services + ov001 one-shot HW init --- */
    func_020027f0();
    FS_Init(3);
    FS_LoadOverlay(0, 1);          /* load ov001 (boot overlay)               */
    func_0204cd7c();               /* ov001_BootInit -- DS hardware bring-up  */
    FS_UnloadOverlay(0, 1);        /* ov001's job is done                     */
    func_020285f0();
    func_02023f58();

    /* --- 2. boot mode -> initial game mode --- */
    func_02003a20(&bootmode);
    func_02024e34(bootmode == 0 ? 1 : bootmode, 0);   /* SetGameMode          */

    /* --- 3. boot resource tables + root/boot task --- */
    func_02016264(&data_027e0350);
    data_020442a0.handle = func_020236cc(FS_TryLoadTable(0, 0), data_0204c024);
    FS_TryLoadTable(data_020442a0.handle, FS_TryLoadTable(0, 0));
    func_0202390c();
    data_0204c215 = 0;
    func_02020834();
    func_02032db8();
    InstantiateClass(&g_BootTaskClassDesc, 1);   /* -> BootTask_Construct -> Scene 1 */

    /* --- 4. FRAME LOOP (0x02000cac) --- */
    for (;;) {
        OS_WaitVBlankIntr();                     /* frame begin              */
        frameTarget = func_01ff80a8();           /* VBlank count snapshot    */
        func_020115b8();                         /* update task queue        */
        func_02023f78();
        G3X_ResetMtxStack();

        switch (data_0204bd84) {                 /* display mode             */
        case 0: func_02023adc(0); break;
        case 1: func_020208a4(1); frameTarget = func_01ff80a8(); break;
        case 2: func_02023adc(0); func_020208a4(1); break;
        }
        func_02032f5c();

        /* frame-rate pacing: advance whole frames until we reach the target */
        frameTarget += (data_0204c058 == 2) ? 0 : (data_0204c058 == 1) ? 2 : 1;
        if (data_0204c058 != 2) {
            while (func_01ff80a8() < frameTarget) {
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
            /* scene still running: handle its transition request via input */
            if (data_020442a0.phase == 0) {
                if ((short)(HELD_KEYS & 0x8000) < 0) {
                    func_02005630();
                    func_0200d49c(0);
                    data_020442a0.phase = 1;
                }
            } else if ((short)(HELD_KEYS & 0x8000) >= 0 && func_0200d49c(1) != 0) {
                data_020442a0.phase = 0;
                func_0201e428(); func_0201e374();
                func_0201e438(); func_0201e3cc();
                func_0200566c();
            }
            continue;
        }

        /* --- scene ended: run fade/teardown transition --- */
        if (func_02020914() == 0) continue;
        if ((short)(HELD_KEYS & 0x8000) >= 0) continue;

        if (data_0204bd84 == 0) func_0201a014(); else func_02033c64();
        func_0200d164(0xc, 0, 0);
        if (data_0204bd84 == 0) func_0201a014(); else func_02033c64();

        if (func_0200d4bc() == 0) {
            if (func_0200d49c(1) == 0) {
                do { func_020020dc(0x64); } while (func_0200d49c(1) == 0);
            }
            func_0200566c();
            data_020442a0.phase = 0;
        }
        func_0201e428(); func_0201e374();
        func_0201e438(); func_0201e3cc();
    }
}
