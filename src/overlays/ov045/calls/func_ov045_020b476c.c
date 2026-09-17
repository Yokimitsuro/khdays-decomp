/* Creates the ov045 enemy's sub-object (x4: ov045/064/083/100; the ov047 shape): allocates it
 * from the default expanding heap, hangs it off the runtime at +0x2644, resets it with kind 2,
 * builds the two-entry parameter table on the stack field by field (the second entry with its
 * own flags 0x3e1, speed 0x2000 - 0x1333, range 0x2000, kind 3 and spin 0x25) and opens it with
 * kind 10; then installs the sub-object's tick and finish handlers at +0x20/+0x24. The
 * assignment order is NOT the ROM's store order: each entry is filled in turn and the order
 * inside cfg[0] (zeros, then the single-use constants, then 0x100, 5, 10) is the pre-image that
 * gives the ROM's constant registers (found by sweeping the constant groups). */
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
    char pad44[4];
    u16 field48;
    u16 field4a;
    u8 field4c;
    char pad4d[3];
};

extern void *NNSi_FndAllocFromDefaultExpHeap(int nBytes);
extern void func_ov022_020911f0(void *pSub, int a, int b);
extern void func_ov022_02091298(void *pSub, char *self, void *pDesc,
                                struct PanelSubCfg *pCfg, int a, int b);
extern void func_ov045_020b4968(void);
extern void func_ov045_020b4900(void);
extern int data_ov045_020b4c08;

void func_ov045_020b476c(char *self)
{
    struct PanelSubCfg cfg[2];

    *(void **)(self + 0x2000 + 0x644) = NNSi_FndAllocFromDefaultExpHeap(0x30);
    func_ov022_020911f0(*(void **)(self + 0x2000 + 0x644), 0, 2);

    cfg[0].field40 = 0x1333;
    cfg[0].field04 = 0;
    cfg[0].field0a = 0;
    cfg[0].field10 = 0;
    cfg[0].field1c = 0;
    cfg[0].field20 = 0;
    cfg[0].field28 = 0;
    cfg[0].field14 = 0xa000;
    cfg[0].field18 = 0x12000;
    cfg[0].field30 = 0x300;
    cfg[0].flags00 = 0x1e1;
    cfg[0].field0c = 0x800;
    cfg[0].field3c = 2;
    cfg[0].field2c = 0x100;
    cfg[0].field34 = 0x100;
    cfg[0].field38 = 5;
    cfg[0].field4c = 10;
    cfg[1].field0c = 0x2000 - 0x1333;
    cfg[1].field14 = 0xa000;
    cfg[1].field18 = 0x12000;
    cfg[1].field30 = 0x300;
    cfg[1].flags00 = 0x3e1;
    cfg[1].field40 = 0x2000;
    cfg[1].field3c = 3;
    cfg[1].field38 = 0x25;
    cfg[1].field04 = 0;
    cfg[1].field0a = 0;
    cfg[1].field10 = 0;
    cfg[1].field1c = 0;
    cfg[1].field20 = 0;
    cfg[1].field28 = 0;
    cfg[1].field2c = 0x100;
    cfg[1].field34 = 0x100;
    cfg[1].field4c = 10;

    func_ov022_02091298(*(void **)(self + 0x2000 + 0x644), self,
                        &data_ov045_020b4c08, cfg, 2, 10);
    *(void **)(*(char **)(self + 0x2000 + 0x644) + 0x20) = (void *)&func_ov045_020b4968;
    *(void **)(*(char **)(self + 0x2000 + 0x644) + 0x24) = (void *)&func_ov045_020b4900;
}
