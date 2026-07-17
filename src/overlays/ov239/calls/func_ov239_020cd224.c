/*
 * Tick the falling-debris node: advance its timer, fire the impact cue once past 0x330, and
 * between 0x440 and 0x880 push a spin offset through the node's matrix into its position.
 *
 * The timer at node+0x2c accumulates the owner's per-frame delta. Once it reaches 0x330 the
 * one-shot flag at node+0x32 gates a single 020c5af8 cue (event 0x138, phase 5). While the timer
 * is in [0x440, 0x880] a fixed offset vector (0, 0x100, 0x1350) is transformed by the node's
 * matrix (node+0xa0), added to its base position (node+0x74), and handed to 020cc778. Finally,
 * unless the sub-node's byte at +0xad is set, the owner's state byte is set to 2 and the slot
 * advances.
 *
 * ★ FOUND BY THE VEC_Set SIGNATURE SWEEP (see codegen-cracks.md): an `ldm` plus individual
 * `str`s to [sp] and no `stm`. The offset vector is built by `VEC_Set(&b.v, 0, 0x100, 0x1350)`
 * -- three separate field stores from the inline's body -- not by assigning a struct. Second
 * function matched off that crack; the sweep found 12 candidates and this was the smallest.
 *
 * Three other things it cost, all catalogued traps:
 *  - ★ GHIDRA NORMALISES COMPARISONS TO NON-ENCODABLE CONSTANTS. It prints `0x32f <` and
 *    `< 0x881`; the ROM has `cmp r0, #0x330 ; blt` and `cmp r0, #0x880 ; bgt`. 0x32f and 0x43f
 *    are not ARM immediates, so writing Ghidra's form literally makes mwcc load them from the
 *    POOL -- 4 extra instructions and two pool entries. Write `>= 0x330` and `<= 0x880`: the
 *    immediate in the ROM tells you which side of the off-by-one the source was on.
 *  - PHANTOM ARGUMENT: Ghidra renders the 020cc778 call with FOUR arguments (it invents
 *    `uVar1 = 0` for the fourth). It takes THREE. The ROM never sets r3 before that `bl`, and
 *    VEC_Add -- called two instructions earlier -- has already clobbered it, so a fourth
 *    argument would be garbage. 020cc778's own prologue confirms it: r0/r1/r2 only.
 *  - The flags at node+0x32 and sub-node+0xad are `ldrb` = UNSIGNED. Each cost a byte.
 */
struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0202f384(void *a, int m, void *d);
extern int VEC_Add(void *a, int b, void *d);
extern void func_ov239_020cc778(int *node, int a, struct Vecx32 *v);
extern void func_0203c634(int *self, int slot, int arg);

void func_ov239_020cd224(int *self) {
    int *node = (int *)self[1];
    struct { struct Vecx32 v; int w; } b;

    node[0xb] += *(int *)(*self + 0x2c);
    if (*(unsigned char *)((int)node + 0x32) == 0 && node[0xb] >= 0x330) {
        func_ov107_020c5af8(*node, 0x138, 5, node[2]);
        *(char *)((int)node + 0x32) = 1;
    }
    if (node[0xb] >= 0x440 && node[0xb] <= 0x880) {
        b.w = *(int *)(*node + 0x80);
        VEC_Set(&b.v, 0, 0x100, 0x1350);
        func_0202f384(&b.v, *node + 0xa0, &b.v);
        VEC_Add(&b.v, *node + 0x74, &b.v);
        func_ov239_020cc778(node, 0, &b.v);
    }
    if (*(unsigned char *)(node[1] + 0xad) == 0) {
        *(char *)(*node + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)((int)self + 0x20), 0);
    }
}
