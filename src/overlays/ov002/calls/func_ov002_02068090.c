/*
 * Ov002_BeginMissionRun - answer the session request and start the run.
 *
 * Nothing happens until the session request goes through. Once it does, the
 * scene's ready hook runs, the world is put to sleep unless it was never armed,
 * and the saved slot decides whether this is a fresh run: with no slot the
 * remembered pair is blanked and the "no save" bit raised, otherwise the bit is
 * dropped. The run then takes over and the mission step is handed back.
 *
 * THUMB.
 */

typedef unsigned short u16;
typedef unsigned char u8;

extern char *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_02069454(void);
extern void func_ov002_0206eaf8(void);
extern void func_ov002_020765f8(int bActive);
extern int func_02020d04(void);
extern void func_02020878(int nValue);
extern void func_ov002_0206e718(int bEnabled);
extern void func_ov002_02068118(void);

void *func_ov002_02068090(void)
{
    char *ctx;
    void *pfnStep;

    ctx = NNSi_FndGetCurrentRootHeap();
    pfnStep = 0;
    if (func_ov002_02069454() != 0) {
        if (*(void (**)(void))(ctx + 0x8b88) != 0) {
            (*(void (**)(void))(ctx + 0x8b88))();
        }
        if (*(int *)(ctx + 0x8bcc) != -1) {
            func_ov002_0206eaf8();
            func_ov002_020765f8(0);
        }
        if (func_02020d04() == -1) {
            if ((*(u8 *)(ctx + 0x8d0c) & 1) == 0) {
                *(u16 *)(ctx + 0x8d0e) = 0;
                *(char *)(ctx + 0x8d0d) = -1;
            }
            *(u8 *)(ctx + 0x8d0c) |= 1;
        } else {
            *(u8 *)(ctx + 0x8d0c) &= ~1;
        }
        func_02020878(1);
        func_ov002_0206e718(0);
        pfnStep = func_ov002_02068118;
    }
    return pfnStep;
}
