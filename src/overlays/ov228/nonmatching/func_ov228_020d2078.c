/*
 * NON-MATCHING (344/348 bytes; x3 ov228/...). Fully reconstructed and semantically exact -- the two
 * bitfield RMWs (self+0x60 high byte |= 0xe via the explicit `((v<<16)>>24 | 0xe)<<24` insert, and the
 * *(self+0x388)+8 low-byte |= 2), all field/callback stores, the phantom-arg calls (the ROM sets only
 * r0,r1 before 0203bfb4 and 0203c7ac -- Ghidra's uVar3/uVar5 are invented), and both subitem-creation
 * sequences all match. The ONLY gap is a register-allocation coin-flip on `size2` (= data_2cd8, read
 * early, used once at the 2nd 020c9440 call): the ROM SPILLS it to the r3 padding slot
 * (`push {r3,r4,r5,lr}` ... `str r2,[sp,#0]` ... `ldr r1,[sp,#0]`) and keeps self in r5; mwcc/patch4
 * instead parks size2 in callee-saved r5 and bumps self to r6 (`push {r4,r5,r6,lr}`, `mov r1,r5`),
 * which renames the self base register throughout -> a 1-instruction (`str [sp,#0]`) size gap plus a
 * pervasive r5<->r6 byte diff. Tried: size2 as an early local (this, self->r6), inlining size2 at the
 * use site (self->r5 but no spill, 340 bytes), and dropping the `child` temp -- none reproduce the
 * spill. This is definition-order vs usage-priority allocation, i.e. a compiler-BUILD difference
 * (retail >=140 hypothesis), not a reachable C form. See deferred-ties.md "constructor size2 spill".
 *
 * func_ov228_020d2078 -- x3 (ov228/...). Construct/initialise this scene object.
 * Install its five behaviour callbacks (self+8/+0xc/+0x1c/+0x30/+0x1dc), raise the pending-state
 * nibble (self+0x60 high byte |= 0xe) and status bits (self+0x1ae |= 0x14), seed the timing window
 * (self+0x70 = 0xe00, mirrored to self+0x68) and mark the owner (*(self+0x9c)+0x5c |= 4). Then build
 * two child sub-items from the parent id *(self+0x38c): a fixed-size one (0x24) registered as a
 * subscriber (self+0x384), and a variable-size one (data_2cd8) linked to self (self+0x390, +0x5c |= 2).
 * Finally insert a 0x10-stride node into the sorted list at self+0x22c (cap 100), point it at the
 * timing block self+0x64, and raise its low-byte flag (|= 2).
 */
struct b8 { unsigned int lo : 8, hi : 24; };

extern int func_ov107_020c9440(int self, int x);
extern int func_0203b898(int r0);
extern void func_0203bfb4(int a, int b);
extern void func_0203c7ac(int a, int b);
extern void func_ov107_020c9074(int self, int child);
extern int *func_01fffca8(int list, int a, int b);
extern int func_ov107_020c319c(int p);
extern void func_ov228_020d21d4(void);
extern void func_ov228_020d21f8(void);
extern void func_ov228_020d2230(void);
extern void func_ov228_020d2340(void);
extern void func_ov228_020d22a8(void);
extern int data_ov228_020d2cd8;

void func_ov228_020d2078(int self) {
    int parent = *(int *)(self + 0x38c);
    int size2 = data_ov228_020d2cd8;

    *(int *)(self + 8) = (int)func_ov228_020d21d4;
    *(int *)(self + 0xc) = (int)func_ov228_020d21f8;
    *(int *)(self + 0x1c) = (int)func_ov228_020d2230;
    *(int *)(self + 0x30) = (int)func_ov228_020d2340;
    *(int *)(self + 0x1dc) = (int)func_ov228_020d22a8;

    {
        unsigned short v60 = *(unsigned short *)(self + 0x60);
        unsigned int hi = (((unsigned)v60 << 16) >> 24 | 0xe) << 24;
        *(unsigned short *)(self + 0x60) = (v60 & ~0xff00) | (hi >> 16);
    }
    *(unsigned short *)(self + 0x1ae) |= 0x14;
    *(int *)(self + 0x70) = 0xe00;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = *(int *)(self + 0x70);
    *(int *)(self + 0x6c) = 0;

    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(parent, 0x24));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);

    *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(parent, size2));
    func_ov107_020c9074(self, *(int *)(self + 0x390));
    *(int *)(*(int *)(self + 0x390) + 0x5c) |= 2;

    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((struct b8 *)(*(int *)(self + 0x388) + 8))->lo |= 2;
}
