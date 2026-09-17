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
    char pad3c[4];
    int field40;
    char pad44[4];
    u16 field48;
    u16 field4a;
    u8 field4c;
    char pad4d[3];
};

/* Creates the ov039 enemy's sub-object (the ov047 shape): allocates it from the default expanding
 * heap, hangs it off the runtime at +0x2644, resets it, builds the two-entry parameter table on
 * the stack (the second entry is a copy of the first with two bits added and its own range 0x2000)
 * and opens it with kind 6; then installs the sub-object's tick and finish handlers at +0x20/+0x24.
 * The assignment order is the ROM's store order (see func_ov047_020b3a3c). */
extern void *NNSi_FndAllocFromDefaultExpHeap(int nBytes);
extern void func_ov022_020911f0(void *pSub, int a, int b);
extern void func_ov022_02091298(void *pSub, char *self, void *pDesc,
                                struct PanelSubCfg *pCfg, int a, int b);
extern void func_ov095_020bba20(void);
extern void func_ov095_020bbb60(void);
extern int data_ov095_020bcb7c;

void func_ov095_020bb874(char *self)
{
    struct PanelSubCfg cfg[2];

    *(void **)(self + 0x2000 + 0x644) = NNSi_FndAllocFromDefaultExpHeap(0x30);
    func_ov022_020911f0(*(void **)(self + 0x2000 + 0x644), 0, 0);

    cfg[0].flags00 = 0x5c9;
    cfg[0].field10 = 0x1000;
    cfg[0].field40 = 0x1333;
    cfg[0].field04 = 0;
    cfg[0].field48 = 0xcd;
    cfg[0].field0a = 0;
    cfg[0].field0c = 0;
    cfg[0].field14 = 0;
    cfg[0].field18 = 0;
    cfg[0].field1c = 0;
    cfg[0].field20 = 0;
    cfg[0].field28 = 0;
    cfg[0].field4a = 3;
    cfg[0].field2c = 0x100;
    cfg[0].field30 = 0x300;
    cfg[0].field34 = 0x100;
    cfg[0].field38 = 5;
    cfg[0].field4c = 6;

    cfg[1] = cfg[0];
    cfg[1].flags00 |= 0x200;
    cfg[1].field40 = 0x2000;
    cfg[1].field38 |= 0x20;

    func_ov022_02091298(*(void **)(self + 0x2000 + 0x644), self,
                        &data_ov095_020bcb7c, cfg, 2, 6);
    *(void **)(*(char **)(self + 0x2000 + 0x644) + 0x20) = (void *)&func_ov095_020bba20;
    *(void **)(*(char **)(self + 0x2000 + 0x644) + 0x24) = (void *)&func_ov095_020bbb60;
}
