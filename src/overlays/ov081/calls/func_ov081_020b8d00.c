/* Creates the ov081 enemy's sub-objects (byte-identical twin of ov042 020b3e20): allocates two
 * 0x30 slots from
 * the default expanding heap, hangs them off the runtime at +0x2644 and resets them (kinds 2 and
 * 0); slot 0 is opened with a three-entry parameter table (one entry per kind 1/2/3, otherwise
 * identical: flags 0xd93, speeds 0xe66/0xccd, ranges 0x12000/0xa000, cue 0xc7) with kind 6 and
 * gets the per-slot tick handler; slot 1 is opened from a single block (flags 0x783, speeds
 * 0x1000/0x1800, range 0x12000, kind 0x25) and gets the tick and finish handlers. The
 * assignment orders are the pre-images of the ROM's store orders. */
typedef unsigned char u8;
typedef unsigned short u16;

struct PanelSubCfg {
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

extern void *NNSi_FndAllocFromDefaultExpHeap(int nBytes);
extern void func_ov022_020911f0(void *pSub, int a, int b);
extern void func_ov022_02091298(void *pSub, char *self, void *pDesc, struct PanelSubCfg *pCfg, int a, int b);
extern void func_ov022_02091254(void *pSub, char *self, void *pDesc, struct PanelSubCfg *pCfg);
extern void func_ov081_020b8f74(void);
extern void func_ov081_020b9080(void);
extern int data_ov081_020b96a8;
extern int data_ov081_020b96bc;

void func_ov081_020b8d00(char *self)
{
    struct PanelSubCfg cfg2;
    struct PanelSubCfg cfg[3];

    *(void **)(self + 0x2000 + 0x644) = NNSi_FndAllocFromDefaultExpHeap(0x60);
    func_ov022_020911f0(*(void **)(self + 0x2000 + 0x644), 0, 2);
    func_ov022_020911f0((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, 1, 0);

    cfg[0].flags00 = 0xd93;
    cfg[0].field0c = 0xe66;
    cfg[0].field10 = 0xccd;
    cfg[0].field04 = 0;
    cfg[0].field0a = 0;
    cfg[0].field1c = 0;
    cfg[0].field20 = 0;
    cfg[0].field28 = 0;
    cfg[0].field14 = 0x12000;
    cfg[0].field18 = 0xa000;
    cfg[0].field40 = 0x2000;
    cfg[0].field3c = 1;
    cfg[0].field44 = 0x12c0;
    cfg[0].field48 = 0xc7;
    cfg[0].field4a = 4;
    cfg[0].field2c = 0x100;
    cfg[0].field30 = 0x300;
    cfg[0].field34 = 0x100;
    cfg[0].field38 = 5;
    cfg[0].field4c = 6;
    cfg[1] = cfg[0];
    cfg[1].field3c = 2;
    cfg[2] = cfg[0];
    cfg[2].field3c = 3;

    func_ov022_02091298(*(void **)(self + 0x2000 + 0x644), self, &data_ov081_020b96a8, cfg, 3, 6);
    *(void **)(*(char **)(self + 0x2000 + 0x644) + 0x20) = (void *)&func_ov081_020b8f74;

    cfg2.field04 = 0;
    cfg2.flags00 = 0x783;
    cfg2.field0c = 0x1000;
    cfg2.field10 = 0x1800;
    cfg2.field14 = 0x12000;
    cfg2.field48 = 0xc7;
    cfg2.field0a = 0;
    cfg2.field18 = 0x4000;
    cfg2.field1c = 0;
    cfg2.field20 = 0;
    cfg2.field28 = 0;
    cfg2.field40 = 0x4000;
    cfg2.field3c = 0;
    cfg2.field4a = 4;
    cfg2.field2c = 0x100;
    cfg2.field30 = 0x300;
    cfg2.field34 = 0x100;
    cfg2.field38 = 0x25;
    cfg2.field4c = 1;
    func_ov022_02091254((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, self, &data_ov081_020b96bc, &cfg2);
    *(void **)(*(char **)(self + 0x2000 + 0x644) + 0x50) = (void *)&func_ov081_020b8f74;
    *(void **)(*(char **)(self + 0x2000 + 0x644) + 0x54) = (void *)&func_ov081_020b9080;
}
