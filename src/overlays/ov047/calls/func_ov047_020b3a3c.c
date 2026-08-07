/* Creates the ov047 panel's sub-object: allocates it from the default expanding heap,
 * hangs it off the runtime at +0x2644, resets it, then builds a two-entry parameter
 * table on the stack and opens it. The second entry is a copy of the first with two
 * bits added, which is why the ROM emits an inline four-word copy loop rather than a
 * second run of stores. Finally installs the sub-object's tick handler at its +0x20.
 *
 * Three things are load-bearing and none of them shows in the semantics.
 *
 * The allocation result must NOT be held in a local. Naming it costs a fifth
 * callee-saved register: the ROM pushes r4-r7 plus r3 for alignment and parks the
 * pooled 0x1c9 in ip, while the named form spills it to r8 and changes the push list.
 *
 * The two blocks must be an ARRAY. Written as two separate locals, mwcc sees the
 * second one is never read -- only the first one's address is passed -- and deletes
 * it, and the function comes out 56 bytes short.
 *
 * The assignment order below is the ROM's store order, not ascending by offset, and
 * two positions in it are measurable rather than cosmetic: field0c comes AFTER the
 * zero run (before it, zero and 0x800 swap the callee-saved pair they land in) and
 * field40 comes BEFORE field2c. The zero run must also be eight separate statements;
 * chaining them into one assignment moves the stores. */
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

extern void *NNSi_FndAllocFromDefaultExpHeap(int nBytes);
extern void func_ov022_020911f0(void *pSub, int a, int b);
extern void func_ov022_02091298(void *pSub, char *self, void *pDesc,
                                struct PanelSubCfg *pCfg, int a, int b);
extern void func_ov047_020b3b98(void);
extern int data_ov047_020b4354;

void func_ov047_020b3a3c(char *self)
{
    struct PanelSubCfg cfg[2];

    *(void **)(self + 0x2000 + 0x644) = NNSi_FndAllocFromDefaultExpHeap(0x30);
    func_ov022_020911f0(*(void **)(self + 0x2000 + 0x644), 0, 0);

    cfg[0].flags00 = 0x1c9;
    cfg[0].field04 = 0;
    cfg[0].field0a = 0;
    cfg[0].field10 = 0;
    cfg[0].field14 = 0;
    cfg[0].field18 = 0;
    cfg[0].field1c = 0;
    cfg[0].field20 = 0;
    cfg[0].field28 = 0;
    cfg[0].field0c = 0x800;
    cfg[0].field40 = 0x2000;
    cfg[0].field2c = 0x100;
    cfg[0].field30 = 0x300;
    cfg[0].field34 = 0x100;
    cfg[0].field38 = 5;
    cfg[0].field4c = 0xa;

    cfg[1] = cfg[0];
    cfg[1].flags00 |= 0x200;
    cfg[1].field38 |= 0x20;

    func_ov022_02091298(*(void **)(self + 0x2000 + 0x644), self,
                        &data_ov047_020b4354, cfg, 2, 0xa);
    *(void **)(*(char **)(self + 0x2000 + 0x644) + 0x20) =
        (void *)&func_ov047_020b3b98;
}
