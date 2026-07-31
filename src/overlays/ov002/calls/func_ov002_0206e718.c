/*
 * Ov002_SetLazyClassEnabled - enable or disable the ov002 lazy-init subsystem and record
 * its state in bit0 of the root context flag byte (ctx+0x8d0a). Called from the ov002
 * gameplay scene tick (func_ov002_020679d4).
 *
 * No-op while the global mode byte (LoadGlobalS8_027e0084) is 0x10. Otherwise, when enabling
 * (param_1 != 0) it runs Ov002_LazyInitClass and sets bit0; when disabling it runs the
 * teardown counterpart (func_ov002_02075fb8) and clears bit0. `&= ~1` (not `& 0xfe`) so mwcc
 * emits `bic #1`. The root context pointer is held at data_ov002_0207fa00.
 */

typedef unsigned char u8;

extern int  func_0201e428(void);
extern void func_ov002_02075f98(void);
extern void func_ov002_02075fb8(void);
extern int  data_ov002_0207fa00;

void func_ov002_0206e718(int param_1)
{
    int ctx = data_ov002_0207fa00;

    if (func_0201e428() == 0x10) {
        return;
    }
    if (param_1 != 0) {
        func_ov002_02075f98();
        *(u8 *)(ctx + 0x8d0a) |= 1;
        return;
    }
    func_ov002_02075fb8();
    *(u8 *)(ctx + 0x8d0a) &= ~1;
}
