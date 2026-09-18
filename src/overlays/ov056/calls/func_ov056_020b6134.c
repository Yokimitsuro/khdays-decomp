/*
 * Build the enemy's peer group: allocates the 0x30-byte group block at +0x2644, opens it with
 * one peer slot and describes that peer -- kind 1 (plus bit 0 when the actor's +9 slot evaluates
 * packed parameter 0x30), spin 0x19a, extents 0x333 / 0x1000 / 0xa000 / 0x14000, no limit
 * (0x7fffffff), the 0x100/0x300/0x100 triple, 4 and tag 8 -- keyed by the packed identity word
 * built from the +0x2bd0 anchor (rounded, bits 2..23 shifted up 7) and the +0x918 byte (+0xbe,
 * 9 bits) with bit 31 set.
 *
 * THUMB. The +0x918 byte is read through a pointer local declared at the top: mwcc keeps the
 * 0x918 offset in r4 across the calls and folds it into the register-offset ldrb, which is the
 * ROM's early `ldr r4,[pc]`. Field order is the ov036_020b4b9c one (f1c before f20).
 */
extern int NNSi_FndAllocFromDefaultExpHeap(int size);
extern void func_ov022_020911f0(int a, int b, int c);
extern int func_020358f4(int a, int b);
extern void func_ov022_02091254(int a, int b, unsigned int key, void *d);

typedef struct {
    int f00;
    int f04;
    char pad08[2];
    unsigned short f0a;
    int f0c;
    int f10;
    int f14;
    int f18;
    int f1c;
    int f20;
    int f24;
    int f28;
    int f2c;
    int f30;
    int f34;
    int f38;
    char pad3c[0x4c - 0x3c];
    unsigned char f4c;
    char pad4d[3];
} Params;

void func_ov056_020b6134(int self) {
    Params p;
    unsigned char *slot = (unsigned char *)(self + 0x918);
    *(int *)(self + 0x2644) = NNSi_FndAllocFromDefaultExpHeap(0x30);
    func_ov022_020911f0(*(int *)(self + 0x2644), 0, 1);
    p.f00 = 1;
    p.f04 = 0;
    p.f0a = 0x19a;
    p.f0c = 0x333;
    p.f10 = 0x1000;
    p.f14 = 0xa000;
    p.f18 = 0x14000;
    p.f1c = 0;
    p.f20 = 0x7fffffff;
    p.f28 = 0;
    p.f30 = 0x300;
    p.f2c = 0x100;
    p.f34 = 0x100;
    p.f38 = 4;
    p.f4c = 8;
    if (func_020358f4(*(unsigned char *)(self + 9), 0x30) != 0) {
        p.f00 |= 1;
    }
    func_ov022_02091254(*(int *)(self + 0x2644), self,
                        (((*(int *)(self + 0x2bd0) + 0x8000) & 0xfffffc) << 7) | 0x80000000
                            | ((*slot + 0xbe) & 0x1ff),
                        &p);
}
