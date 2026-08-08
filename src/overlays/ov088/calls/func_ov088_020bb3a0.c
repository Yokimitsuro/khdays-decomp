/* Creates the ov088 actor's three sub-objects: allocates one 0x90 block from the
 * default expanding heap, hangs it off the runtime at +0x2644, resets the three 0x30
 * slots, then opens each of them in turn from a parameter block rebuilt on the stack,
 * and installs each slot's tick handler.
 *
 * Slots 0 and 1 share the handler at 020b6d3c; slot 2 gets 020b6e30. The three
 * parameter blocks are rebuilt field by field rather than copied, so unlike the ov047
 * sibling there is no array and no inline copy loop.
 *
 * Load-bearing, from the ov047 sibling and confirmed here: the allocation result is
 * NOT held in a local -- naming it costs an extra callee-saved register and changes
 * the push list.
 *
 * The assignment order in each block is NOT the ROM's store order and is not
 * meaningful to read: mwcc reorders stores into a stack aggregate, so the source order
 * that produces the ROM's output is a pre-image of it, not a copy. In particular each
 * block's zero run and the 0x48/0x4a halfword pair sit where they do because of that
 * reordering, and moving any single assignment breaks the block. Treat this order as
 * load-bearing and do not tidy it. */
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

extern void *NNSi_FndAllocFromDefaultExpHeap(int nBytes);
extern void func_ov022_020911f0(void *pSub, int a, int b);
extern void func_ov022_02091254(void *pSub, char *self, void *pDesc,
                                struct ActorSubCfg *pCfg);
extern void func_ov088_020bbadc(void);
extern void func_ov088_020bbbd0(void);
extern int data_ov088_020bc310;
extern int data_ov088_020bc324;
extern int data_ov088_020bc338;

void func_ov088_020bb3a0(char *self)
{
    struct ActorSubCfg cfg;

    *(void **)(self + 0x2000 + 0x644) = NNSi_FndAllocFromDefaultExpHeap(0x90);
    func_ov022_020911f0(*(void **)(self + 0x2000 + 0x644), 0, 2);
    func_ov022_020911f0((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, 1, 0);
    func_ov022_020911f0((char *)*(void **)(self + 0x2000 + 0x644) + 0x60, 2, 2);
    cfg.flags00 = 0xd93;
    cfg.field04 = 0;
    cfg.field10 = 0xccd;
    cfg.field14 = 0x12000;
    cfg.field18 = 0x4000;
    cfg.field40 = 0x3000;
    cfg.field44 = 0x1e00;
    cfg.field3c = 1;
    cfg.field48 = 0xcb;
    cfg.field4a = 4;
    cfg.field2c = 0x100;
    cfg.field34 = 0x100;
    cfg.field30 = 0x300;
    cfg.field38 = 5;
    cfg.field4c = 3;
    cfg.field0a = 0;
    cfg.field1c = 0;
    cfg.field20 = 0;
    cfg.field28 = 0;
    cfg.field0c = 0x99a;
    func_ov022_02091254(*(void **)(self + 0x2000 + 0x644), self,
                        &data_ov088_020bc310, &cfg);
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x20) =
        (void *)&func_ov088_020bbadc;

    cfg.flags00 = 0x783;
    cfg.field04 = 0;
    cfg.field0c = 0x1333;
    cfg.field10 = 0xccd;
    cfg.field14 = 0xf000;
    cfg.field0a = 0;
    cfg.field1c = 0;
    cfg.field20 = 0;
    cfg.field28 = 0;
    cfg.field18 = 0x7000;
    cfg.field40 = 0;
    cfg.field3c = 1;
    cfg.field48 = 0xcb;
    cfg.field4a = 4;
    cfg.field2c = 0x200;
    cfg.field30 = 0x400;
    cfg.field38 = 5;
    cfg.field4c = 3;
    cfg.field34 = 0x200;
    func_ov022_02091254((char *)*(void **)(self + 0x2000 + 0x644) + 0x30, self,
                        &data_ov088_020bc324, &cfg);
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x50) =
        (void *)&func_ov088_020bbadc;

    cfg.field04 = 1;
    cfg.field0a = 0;
    cfg.flags00 = 0x783;
    cfg.field0c = 0x99a;
    cfg.field10 = 0x1800;
    cfg.field14 = 0x12000;
    cfg.field18 = 0x9000;
    cfg.field40 = 0x2000;
    cfg.field48 = 0xcb;
    cfg.field4a = 4;
    cfg.field2c = 0x100;
    cfg.field30 = 0x300;
    cfg.field34 = 0x100;
    cfg.field38 = 0x25;
    cfg.field4c = 3;
    cfg.field3c = 1;
    cfg.field1c = 0;
    cfg.field20 = 0;
    cfg.field28 = 0;
    func_ov022_02091254((char *)*(void **)(self + 0x2000 + 0x644) + 0x60, self,
                        &data_ov088_020bc338, &cfg);
    *(void **)((char *)*(void **)(self + 0x2000 + 0x644) + 0x80) =
        (void *)&func_ov088_020bbbd0;
}
