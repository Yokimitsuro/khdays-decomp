/* Opens the ov036 enemy's two secondary sub-objects (x4: ov036/054/074/091): resets slots 1 and
 * 2 of the sub-object block at +0x2644, then opens each from a parameter block rebuilt on the
 * stack (slot 1: flags 0x1c9, speed 0x119a, spin 5; slot 2: flags 0x3c9, speed 0x2f9a, spin
 * 0x25; both kind 12) and installs the shared tick handler at +0x50 / +0x80. */
typedef unsigned char u8;
typedef unsigned short u16;

struct ActorSubCfg {
    int flags00;
    int field04;
    char pad08[2];
    u16 field0a;
    int field0c;
    int field10;
    int field14;
    int field18;
    int field1c;
    int field20;
    char pad24[4];
    int field28;
    int field2c;
    int field30;
    int field34;
    int field38;
    int field3c;
    int field40;
    int field44;
    u16 field48;
    u16 field4a;
    u8 field4c;
    char pad4d[3];
};

extern void func_ov022_020911f0(void *pSub, int a, int b);
extern void func_ov022_02091254(void *pSub, char *self, void *pDesc, struct ActorSubCfg *pCfg);
extern void func_ov055_020b65e0(void);
extern int data_ov055_020b76dc;
extern int data_ov055_020b76f0;

void func_ov055_020b63d0(char *self)
{
    struct ActorSubCfg cfg;

    func_ov022_020911f0((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, 1, 0);
    func_ov022_020911f0((char *)*(void **)(self + 0x2000 + 0x644) + 0x60, 2, 0);

    cfg.flags00 = 0x1c9;
    cfg.field04 = 1;
    cfg.field40 = 0x119a;
    cfg.field30 = 0x300;
    cfg.field0a = 0;
    cfg.field0c = 0;
    cfg.field10 = 0;
    cfg.field14 = 0;
    cfg.field18 = 0;
    cfg.field1c = 0;
    cfg.field20 = 0;
    cfg.field28 = 0;
    cfg.field2c = 0x100;
    cfg.field34 = 0x100;
    cfg.field38 = 5;
    cfg.field4c = 0xc;
    func_ov022_02091254((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, self,
                        &data_ov055_020b76dc, &cfg);
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x50) = (void *)&func_ov055_020b65e0;

    cfg.flags00 = 0x3c9;
    cfg.field04 = 0;
    cfg.field40 = 0x2f9a;
    cfg.field0a = 0;
    cfg.field0c = 0;
    cfg.field10 = 0;
    cfg.field14 = 0;
    cfg.field18 = 0;
    cfg.field1c = 0;
    cfg.field20 = 0;
    cfg.field28 = 0;
    cfg.field2c = 0x100;
    cfg.field34 = 0x100;
    cfg.field30 = 0x300;
    cfg.field38 = 0x25;
    cfg.field4c = 0xc;
    func_ov022_02091254((char *)*(void **)(self + 0x2000 + 0x644) + 0x60, self,
                        &data_ov055_020b76f0, &cfg);
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x80) = (void *)&func_ov055_020b65e0;
}
