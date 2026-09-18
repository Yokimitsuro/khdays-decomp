/* Creates the ov032 enemy's sub-object (and its byte-identical twins): allocates it (0x60
 * bytes), hangs it off the runtime at +0x2644, resets it, builds a three-entry parameter table
 * on the stack (a 0x333/0xccd entry over 0xa000..0x1e000 with the +0x92c count of parts, a
 * kind-2 0x800/0x1333 entry over 0x19000..0x1e000 and a 0xb33/0xe66 entry over
 * 0x5000..0x1e000, all flagged when property 0x30 of the actor's +9 kind is set) and opens it
 * with the packed heading/slot word for that many parts; the sub-object's +0x18 takes the
 * global's +0x10 byte when non-negative, every part gets its own +0x74 back-link and the joint
 * hook (470c) armed with mode 6/3, and the four bone descriptors resolve the rig's +0x4c
 * bone (or -1) into the mission root's +0x2e68..+0x2e74.
 *
 * Codegen: the part stride is written UNSIGNED (`i * 0x1c8u`); the signed product becomes an
 * induction pointer, the ROM multiplies every iteration. The loop is the `goto test` shape. */
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
extern int func_020358f4(int kind, int property);
extern void func_ov022_02091298(void *pSub, char *self, int packed, struct PanelSubCfg *pCfg, int a, int b);
extern void func_02014e18(void *part, void *cb, int ptr, int timing, int opt);
extern int func_02016f10(void *node, void *desc);
extern void func_ov032_020b470c(void);
extern char data_0204c4d8[];
extern int data_ov032_020b5768;
extern int data_ov032_020b5778;
extern int data_ov032_020b5758;
extern int data_ov032_020b5738;

struct Part { char pad[0x1c8]; };

/* The rig hangs off the sub-object's +0xc; the bone block starts 0x40 past its +0x4c. */
static inline int bone(char *rig) {
    int p = *(int *)(rig + 0x4c);
    return p != 0 ? p + 0x40 : 0;
}

void func_ov032_020b43dc(char *self)
{
    struct PanelSubCfg cfg[3];
    char *slot = self + 0x918;
    int count = *(int *)(slot + 0x14) >> 12;
    int nSlot = *(u8 *)(slot + 0x13);
    int i;
    char *part;
    char *rig;
    int b;
    signed char v;

    *(void **)(self + 0x2644) = NNSi_FndAllocFromDefaultExpHeap(0x60);
    func_ov022_020911f0(*(void **)(self + 0x2644), 0, 1);

    cfg[0].flags00 = 0;
    cfg[0].field04 = 1;
    cfg[0].field0a = 0x2e1;
    cfg[0].field0c = 0x2e1 + 0x52;
    cfg[0].field10 = 0xccd;
    cfg[0].field14 = 0xa000;
    cfg[0].field18 = 0x1e000;
    cfg[0].field1c = 0x2000;
    cfg[0].field20 = 0x3000;
    cfg[0].field28 = 0;
    cfg[0].field2c = 0x100;
    cfg[0].field30 = 0x300;
    cfg[0].field34 = 0x100;
    cfg[0].field38 = 4;
    cfg[0].field4c = count;

    cfg[1].flags00 = 2;
    cfg[1].field04 = 1;
    cfg[1].field0a = 0;
    cfg[1].field0c = 0x800;
    cfg[1].field10 = 0x1333;
    cfg[1].field14 = 0x19000;
    cfg[1].field18 = 0x1e000;
    cfg[1].field1c = 0x1000;
    cfg[1].field20 = 0;
    cfg[1].field28 = 0;
    cfg[1].field2c = 0x200;
    cfg[1].field30 = 0x400;
    cfg[1].field34 = 0x200;
    cfg[1].field38 = 4;
    cfg[1].field4c = 6;

    cfg[2].flags00 = 0;
    cfg[2].field04 = 1;
    cfg[2].field0a = 0;
    cfg[2].field0c = 0xb33;
    cfg[2].field10 = 0xe66;
    cfg[2].field14 = 0x5000;
    cfg[2].field18 = 0x1e000;
    cfg[2].field1c = 0x3000;
    cfg[2].field20 = 0;
    cfg[2].field28 = 0;
    cfg[2].field2c = 0x200;
    cfg[2].field30 = 0x400;
    cfg[2].field34 = 0x200;
    cfg[2].field38 = 4;
    cfg[2].field4c = 10;

    if (func_020358f4(*(u8 *)(self + 9), 0x30) != 0) {
        cfg[0].flags00 |= 1;
        cfg[1].flags00 |= 1;
        cfg[2].flags00 |= 1;
    }
    func_ov022_02091298(*(void **)(self + 0x2644), self,
                        (((*(int *)(self + 0x2bd0) + 0x8000) & 0xfffffc) << 7) | 0x80000000 | ((nSlot + 0x8c) & 0x1ff),
                        cfg, 3, count);
    v = *(signed char *)(data_0204c4d8 + 0x10);
    if (v >= 0) {
        *(u8 *)(*(char **)(self + 0x2644) + 0x18) = v;
    }
    i = 0;
    goto test;
body:
    part = *(char **)(*(char **)(self + 0x2644) + 0xc) + i * 0x1c8u;
    *(char **)(part + 0x74) = part;
    func_02014e18(part + 0x48, func_ov032_020b470c, 0, 6, 3);
    i++;
test:
    if (i < count) {
        goto body;
    }
    rig = *(char **)(*(char **)(self + 0x2644) + 0xc);
    b = bone(rig);
    *(int *)(self + 0x2e68) = b != 0 ? func_02016f10((void *)b, &data_ov032_020b5768) : -1;
    b = bone(rig);
    *(int *)(self + 0x2e6c) = b != 0 ? func_02016f10((void *)b, &data_ov032_020b5778) : -1;
    b = bone(rig);
    *(int *)(self + 0x2e70) = b != 0 ? func_02016f10((void *)b, &data_ov032_020b5758) : -1;
    b = bone(rig);
    *(int *)(self + 0x2e74) = b != 0 ? func_02016f10((void *)b, &data_ov032_020b5738) : -1;
}
