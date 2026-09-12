typedef unsigned short u16;
typedef unsigned int u32;

extern char *data_0204be08;
extern char data_02042748[16];

extern int func_02020a9c(void);
extern void G2x_SetBlendBrightness_(u16 *dst, u32 attr, int value);
extern void func_020056b4(u16 param_1, u32 param_2, int param_3);
extern void func_02000fb4(int unused, const char *name);
extern void func_ov002_020571b8(void);
extern int func_ov106_020b8208(void);

/* GBATEK: DISPCNT, main engine. */
#define REG_DISPCNT (*(volatile u32 *)0x04000000)

void func_02023100(void)
{
    char *heap = (&data_0204be08)[1];

    if ((func_02020a9c() & 8) != 0) {
        REG_DISPCNT = (REG_DISPCNT & 0xffffe0ff) | 0x100;
    } else {
        REG_DISPCNT = (REG_DISPCNT & 0xffffe0ff) | 0x1f00;
    }

    G2x_SetBlendBrightness_((u16 *)0x04000050, 1, 0);

    {
        volatile u32 *subDispCnt = (volatile u32 *)0x04001000;
        u32 attr = (*subDispCnt & 0x1f00) >> 8;
        G2x_SetBlendBrightness_((u16 *)((char *)subDispCnt + 0x50), attr, 0);
    }

    if (*(int *)(heap + 0xe4) != 0) {
        func_020056b4(0xe, 4, 1);
    }

    func_02000fb4(1, data_02042748);
    func_ov002_020571b8();

    if (func_02020a9c() == 0x2a) {
        G2x_SetBlendBrightness_((u16 *)0x04000050, 1, func_ov106_020b8208());
    }
}
