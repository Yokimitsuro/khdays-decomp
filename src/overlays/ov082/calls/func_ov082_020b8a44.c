/* func_ov082_020b8a44 -- spawn four particle emitters into the owner's emitter pool
 * (self+0x234, stride 0x170, up to 8 slots).
 *
 * Per emitter: find the first free slot (byte +0x12c == 0, else reuse the last), zero the
 * transform accumulators, reset the 3x scale (+0xb0/+0xb4/+0xb8) and orientation (+0x150) to
 * 1.0 via 020b4048, copy the owner's palette handle (ctx+0x490), seed life 0xa000, kind 0x119a
 * and the sprite id (low byte of ctx+0x66), mark the slot used, stamp the per-emitter angle
 * (+0x2000 each) and spin (+0x3fff each), and hand off to 020b4024. ctx = *(int *)(self+0xdb4).
 * One of a 5-member family (ov030/044/063/082/099); the analysis lives in the ov030 member.
 *
 * Two shapes are load-bearing:
 *  - the accumulator pair and the three scale stores are CHAINED assignments. As separate
 *    statements mwcc hoists the 0x119a literal-pool load above the 0xa000 store; merging the
 *    statements puts it back, which is the same lever as func_02023c60. (Chaining also gives
 *    the ROM's descending store order for free.)
 *  - the three loop increments run angle, spin, index. The spin step needs two instructions
 *    (0xff then 0x3f00) and the ROM issues them either side of the index compare; only that
 *    source order reproduces the split. */
extern void func_ov082_020b8b5c(int slot, int b);
extern void func_ov082_020b8b38(int slot);

void func_ov082_020b8a44(int self) {
    int ctx = *(int *)(self + 0xdb4);
    int i = 0;
    int slot;
    int angle = 0;
    int spin = 0;

    do {
        int j = 0;
        int p = self + 0x234;

        do {
            slot = p;
            if (*(unsigned char *)(slot + 0x12c) == 0) break;
            j++;
            p = slot + 0x170;
        } while (j < 8);

        *(int *)(slot + 0x14c) = *(int *)(slot + 0x148) = 0;
        *(int *)(slot + 0x150) = 0x1000;
        func_ov082_020b8b5c(slot, 0);
        *(int *)(slot + 0xb0) = *(int *)(slot + 0xb4) = *(int *)(slot + 0xb8) = 0x1000;
        *(int *)(slot + 0x138) = *(int *)(ctx + 0x490);
        *(int *)(slot + 0x154) = 0xa000;
        *(int *)(slot + 0x158) = 0x119a;
        *(signed char *)(slot + 0x15c) = *(short *)(ctx + 0x66);
        *(unsigned char *)(slot + 0x12c) = 1;
        *(int *)(slot + 0x130) = 0;
        *(int *)(slot + 0x134) = angle;
        *(short *)(slot + 0x15e) = spin;
        func_ov082_020b8b38(slot);

        angle += 0x2000;
        spin += 0x3fff;
        i++;
    } while (i < 4);
}
