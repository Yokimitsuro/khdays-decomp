/* Opens the mission enemy's secondary sub-object: resets slot 1 of the sub-object block at
 * +0x2644, opens it from a parameter block rebuilt on the stack (flags 0x349, sub-kind 1,
 * extents 0x666 / 0x1000 / 0x6000, the 0x100/0x300/0x100 triple, 0x25, tag 2) described by
 * data_ov062_020b80c4, and installs the slot's two handlers at +0x50 / +0x54.
 *
 * THUMB. Same shape as func_ov092_020bb170 with a single slot. */
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
extern void func_ov062_020b7acc(void);
extern void func_ov062_020b7b30(void);
extern int data_ov062_020b80c4;

void func_ov062_020b79ec(char *self)
{
    struct ActorSubCfg cfg;

    func_ov022_020911f0((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, 1, 0);

    cfg.flags00 = 0x349;
    cfg.field04 = 1;
    cfg.field0a = 0;
    cfg.field0c = 0x666;
    cfg.field10 = 0x1000;
    cfg.field14 = 0x6000;
    cfg.field18 = 0;
    cfg.field1c = 0;
    cfg.field20 = 0;
    cfg.field28 = 0;
    cfg.field2c = 0x100;
    cfg.field30 = 0x300;
    cfg.field34 = 0x100;
    cfg.field38 = 0x25;
    cfg.field4c = 2;
    func_ov022_02091254((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, self,
                        &data_ov062_020b80c4, &cfg);
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x50) = (void *)&func_ov062_020b7acc;
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x54) = (void *)&func_ov062_020b7b30;
}
