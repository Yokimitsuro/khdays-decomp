typedef unsigned short u16;
typedef unsigned int u32;

extern void func_0201e1d0(void);
extern void func_02032f0c(void);
extern int func_02001030(void);
extern void func_ov105_020bf9c0(void);
extern void func_ov105_020bf928(void);
extern u16 *GXx_SetMasterBrightness_(u16 *reg, int brightness);
extern int func_ov008_0207bc80(void);
extern u16 func_ov105_020bf25c(void);
extern u16 func_ov105_020bf26c(void);
extern void func_0202362c(int value);
extern void func_02003948(u32 value);

void *func_ov008_0207d5d8(void) {
    u32 packed;

    *(volatile u16 *)0x05000000 = 0;
    *(volatile u16 *)0x05000400 = 0;
    *(volatile u32 *)0x04000000 &= ~0x1f00;
    *(volatile u32 *)0x04001000 &= ~0x1f00;

    func_0201e1d0();
    func_02032f0c();

    if (func_02001030() != 0) {
        int waiting = 1;
        int stopped = 0;

        do {
            switch (func_02001030()) {
            case 1:
                func_ov105_020bf9c0();
                break;
            case 0:
                waiting = stopped;
                break;
            case 3:
                break;
            default:
                func_ov105_020bf928();
                break;
            }
        } while (waiting != 0);
    }

    GXx_SetMasterBrightness_((u16 *)0x0400006c, 0x10);
    GXx_SetMasterBrightness_((u16 *)0x0400106c, 0x10);

    if (func_ov008_0207bc80() != 0) {
        packed = (u32)-1;
    } else {
        u16 high = func_ov105_020bf25c();
        u16 low = func_ov105_020bf26c();

        packed = ((u32)high << 16) | low | 0x80000000;
    }

    func_0202362c(0);
    func_02003948(packed);
    return 0;
}
