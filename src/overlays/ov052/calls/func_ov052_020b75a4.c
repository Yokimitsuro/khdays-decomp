/* Opens the ov032 enemy's +0x2644 item's +0x30 sub-object (and its byte-identical twins): resets
 * it and builds a two-entry parameter table on the stack (a 0x181 entry with the 0x99a/0x119a
 * ranges and a 0x383 entry with 0x1400/0x1000, both spanning 0x19000..0x32000 at 0x3000) that
 * the overlay's descriptor opens with modes 2/4. */
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
    char pad44[8];
    u8 field4c;
    char pad4d[3];
};

extern void func_ov022_020911f0(void *pSub, int a, int b);
extern void func_ov022_02091298(void *pSub, char *self, void *pDesc,
                                struct PanelSubCfg *pCfg, int a, int b);
extern int data_ov052_020b8090;

void func_ov052_020b75a4(char *self)
{
    struct PanelSubCfg cfg[2];

    func_ov022_020911f0(*(char **)(self + 0x2644) + 0x30, 1, 1);

    cfg[0].flags00 = 0x181;
    cfg[0].field04 = 1;
    cfg[0].field0a = 0;
    cfg[0].field0c = 0x99a;
    cfg[0].field10 = 0x119a;
    cfg[0].field14 = 0x19000;
    cfg[0].field18 = 0x32000;
    cfg[0].field1c = 0x3000;
    cfg[0].field20 = 0;
    cfg[0].field28 = 0;
    cfg[0].field2c = 0x100;
    cfg[0].field30 = 0x300;
    cfg[0].field34 = 0x100;
    cfg[0].field38 = 5;
    cfg[0].field4c = 4;

    cfg[1].flags00 = 0x383;
    cfg[1].field04 = 1;
    cfg[1].field0a = 0;
    cfg[1].field0c = 0x1400;
    cfg[1].field10 = 0x1000;
    cfg[1].field14 = 0x19000;
    cfg[1].field18 = 0x32000;
    cfg[1].field1c = 0x3000;
    cfg[1].field20 = 0;
    cfg[1].field28 = 0;
    cfg[1].field2c = 0x200;
    cfg[1].field30 = 0x400;
    cfg[1].field34 = 0x200;
    cfg[1].field38 = 0x25;
    cfg[1].field4c = 4;

    func_ov022_02091298(*(char **)(self + 0x2644) + 0x30, self, &data_ov052_020b8090, cfg, 2, 4);
}
