#pragma opt_common_subs off

/*
 * Ov002_ShutDownMissionScene - tear the whole mission scene down.
 *
 * The scene's own exit hook runs first and its overlay - plus overlay 0x45 when
 * this was scene kind 7 - is unloaded, then every subsystem the scene brought
 * up is closed in the reverse order it was opened: link session, key sharing,
 * pause buffers, slot table, deferred draws, link state and scene context. The
 * saved global slots are cleared, the two heap buffers the scene owns are
 * freed, and the scene pointer is dropped.
 *
 * The boot-mode flag bit 2 marks a run that never claimed those globals, so it
 * skips the two frees that go with them.
 *
 * THUMB.
 */

typedef unsigned int u32;
typedef u32 FSOverlayID;

extern u32 OVERLAY_69_ID[1];
#define FS_OVERLAY_ID_ov069 ((FSOverlayID)(u32) & (OVERLAY_69_ID))

extern int data_ov002_0207fa00;
extern unsigned char data_0204c240;

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void NNSi_FndFreeFromDefaultHeap(int pBlock);
extern void func_0201e4a8(int nProcessor, FSOverlayID nOverlay);
extern void func_0202ded8(void);
extern void func_02033500(int nArg);
extern int func_0202b788(void);
extern void func_02035708(void);
extern void func_02035c44(void);
extern void func_02020aa8(int nIndex, int nValue);
extern void func_02020cf8(int nValue);
extern void func_02024fd4(int pBlock);

extern void OSi_IrqTimer3_0x0206fb74(void);
extern void func_ov002_02069844(void);
extern void func_ov002_02069ce0(void);
extern void func_ov002_02078eac(void);
extern void func_ov002_020763f0(void);
extern void func_ov002_0206a098(void);
extern void func_ov002_0206a0f4(void);
extern void func_ov002_0206a27c(void);
extern void func_ov002_0206a29c(void);
extern void func_ov002_0206a2cc(void);
extern void func_ov002_0206edc8(void);
extern void func_ov002_0206ead8(void);
extern void func_ov002_0206f46c(void);
extern void func_ov002_02073514(void);
extern void func_ov002_02071958(void);
extern void func_ov002_020711a4(void);
extern void func_ov002_02063714(void);
extern void func_ov002_020697c0(void);
extern void func_ov002_020697cc(void);
extern void func_ov002_0206da54(int nIndex, int nValue);
extern void func_ov002_02075fb8(void);

void func_ov002_02067e34(void)
{
    char *ctx;

    ctx = NNSi_FndGetCurrentRootHeap();
    OSi_IrqTimer3_0x0206fb74();
    if (*(int *)(ctx + 0x8b4c) != -1) {
        (*(void (**)(void))(ctx + 0x8b84))();
        func_0201e4a8(0, *(FSOverlayID *)(ctx + 0x8b50));
        if (*(int *)(ctx + 0x8b58) == 7) {
            func_0201e4a8(0, FS_OVERLAY_ID_ov069);
        }
        *(int *)(ctx + 0x8b4c) = -1;
    }
    if ((data_0204c240 & 4) == 0) {
        func_02035c44();
    }
    func_02033500(0);
    func_02035708();
    func_ov002_02069844();
    func_ov002_02069ce0();
    func_ov002_02078eac();
    func_ov002_020763f0();
    func_ov002_0206a098();
    func_ov002_0206a0f4();
    func_ov002_0206a27c();
    func_ov002_0206a29c();
    func_ov002_0206a2cc();
    func_0202ded8();
    func_0202b788();
    func_ov002_0206edc8();
    func_ov002_0206ead8();
    func_ov002_0206f46c();
    func_ov002_02073514();
    func_ov002_02071958();
    func_ov002_020711a4();
    func_ov002_02063714();
    func_02020cf8(-1);
    func_ov002_020697c0();
    func_ov002_020697cc();
    func_02024fd4(*(int *)(ctx + 4));
    func_ov002_0206da54(0, 0);
    func_ov002_0206da54(1, 0);
    func_ov002_0206da54(2, 0);
    func_ov002_0206da54(3, 0);
    func_02020aa8(2, 0);
    func_02020aa8(1, 0);
    func_02020aa8(0x13, 0);
    if ((data_0204c240 & 4) == 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(ctx + 0x8dac));
        *(int *)(ctx + 0x8dac) = 0;
    }
    func_ov002_02075fb8();
    if (*(int *)(ctx + 0x8dbc) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(ctx + 0x8dbc));
        *(int *)(ctx + 0x8dbc) = 0;
    }
    data_ov002_0207fa00 = 0;
}
