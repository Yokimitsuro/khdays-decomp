/* NON-MATCHING: compiler-scheduler artifact only (register allocation + structure are exact).
 * Family of 5: ov030_020b3f30 / ov044_020b3b64 / ov063_020b6364 / ov082_020b8a44 / ov099_020bb104.
 *
 * Spawn four particle emitters into the owner's emitter pool (self+0x234, stride 0x170, up to 8
 * slots). Per emitter: find the first free slot (byte +0x12c == 0, else reuse the last), zero the
 * transform accumulators, reset the 3x scale (+0xb0/+0xb4/+0xb8 = 0x1000) and orientation
 * (+0x150 = 0x1000) via 020b4048, copy the owner's palette handle (ctx+0x490), seed life 0xa000 /
 * kind 0x119a / sprite id (ctx+0x66 low byte), mark used, stamp per-emitter angle (+0x2000 each)
 * and spin (+0x3fff each), hand off to 020b4024. ctx = *(int*)(self+0xdb4).
 *
 * After steering the callee-saved allocation to the ROM's (ctx=r4, i=r5, slot=r6, angle=r7,
 * spin=r8 -- via the ctx/i/slot/angle/spin decl order + declaring j before p), the ONLY residue is
 * instruction scheduling the retail compiler does differently:
 *   (A) the 0x119a pool load: the ROM emits it AFTER the 0xa000 store and hoists `mov r1,#1` up;
 *       mwcc hoists the `ldr [pc]` before the 0xa000 store and drops `mov r1,#1` to last.
 *   (B) the loop-tail spin split: the ROM brackets angle between i++ and the second half of the
 *       spin add; mwcc emits both spin halves adjacent.
 * Neither is reachable from source (a pool load cannot be de-hoisted; the split recombines when
 * spelled explicitly). build_sweep reports "24 off" on every one of the 27 mwcc builds, so no
 * available compiler schedules it this way -- the retail scheduler (likely 3.0 >=140, a build we
 * do not have) is the difference. Filed as a scheduler-version tie, not a source defect.
 */

extern void func_ov030_020b4048(int slot, int b);
extern void func_ov030_020b4024(int slot);

void func_ov030_020b3f30(int self) {
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
        *(int *)(slot + 0x148) = 0;
        *(int *)(slot + 0x14c) = 0;
        *(int *)(slot + 0x150) = 0x1000;
        func_ov030_020b4048(slot, 0);
        *(int *)(slot + 0xb8) = 0x1000;
        *(int *)(slot + 0xb4) = 0x1000;
        *(int *)(slot + 0xb0) = 0x1000;
        *(int *)(slot + 0x138) = *(int *)(ctx + 0x490);
        *(int *)(slot + 0x154) = 0xa000;
        *(int *)(slot + 0x158) = 0x119a;
        *(signed char *)(slot + 0x15c) = *(short *)(ctx + 0x66);
        *(unsigned char *)(slot + 0x12c) = 1;
        *(int *)(slot + 0x130) = 0;
        *(int *)(slot + 0x134) = angle;
        *(short *)(slot + 0x15e) = spin;
        func_ov030_020b4024(slot);
        spin += 0x3fff;
        i++;
        angle += 0x2000;
    } while (i < 4);
}
