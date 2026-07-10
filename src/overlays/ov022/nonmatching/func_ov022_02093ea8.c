/*
 * NONMATCHING (base-coalescing / loop-invariant-hoist tie, +4B):
 * The original keeps param_1 fixed in its own register (sb) and reads the
 * loop-invariant fields via immediate offsets ([sb,#0x1c], [sb,#0x4d8]),
 * while iVar5/puVar6 walk by +0x108. mwcc instead folds param_1 into the
 * iVar5 walker (walking that register) and hoists the two invariant base
 * addresses (param_1+0x1c, param_1+0x4d8) into extra callee-saved registers
 * before the loop (turning the single [.,#0x4d8] ldr into add#0xd8/ldr#0x400).
 * Tried: decl-order swaps, an explicit fixed `base` local for the invariant
 * reads. The allocator still coalesces param_1 into the walker. Logic is
 * byte-equivalent; only the induction/LICM shape differs.
 *
 * Loop i=0..3: if (*(u32)(param_1+0x1c) & (1<<i)) copy the 3-word block at
 * *(param_1+0x4d8)+0x48c through a stack buffer, add 0xe00 to its middle word,
 * store it to (param_1 + i*0x108)+0xc4, then func_0202aa9c(param_1+0x20 + i*0x108).
 */
extern void func_0202aa9c(unsigned short *p);

struct blk3_02093ea8 {
    int a;
    int b;
    int c;
};

void func_ov022_02093ea8(int param_1) {
    unsigned short *puVar6 = (unsigned short *)(param_1 + 0x20);
    int iVar5 = param_1;
    unsigned int i = 0;
    do {
        if ((*(unsigned int *)(param_1 + 0x1c) & (1 << i)) != 0) {
            struct blk3_02093ea8 tmp =
                *(struct blk3_02093ea8 *)(*(int *)(param_1 + 0x4d8) + 0x48c);
            tmp.b += 0xe00;
            *(struct blk3_02093ea8 *)(iVar5 + 0xc4) = tmp;
            func_0202aa9c(puVar6);
        }
        i = i + 1;
        iVar5 = iVar5 + 0x108;
        puVar6 = puVar6 + 0x84;
    } while ((int)i < 4);
}
