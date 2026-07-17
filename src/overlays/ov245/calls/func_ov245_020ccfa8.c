/* Commit the queued move and dispatch its handler (ov245). First refresh the approach
 * factor: FX_Inv(gap, reach) over the distance from the target's point (ctx[2]+8) to the
 * actor's reach envelope, both measured from ctx+0x3c + 0xf000. Then, if a move is queued
 * at owner+0x1c7 (-1 = none), latch it as the current move (+0x1c6), clear the two stance
 * flags (hw60 hi 0x82 and owner+0x1ae bits 0-1), mark the sub-object at owner+0x3b4 live
 * (bit 0) and not-done (bit 1), reset the timer, run the move's handler and clear the
 * queue slot.
 *
 * The case order below is the ROM's SOURCE order, recovered from the jump table with
 * tools/switchorder.py -- the bodies are laid out in source order while the table is
 * indexed by value, so sorting the table's targets by address gives it directly. It is
 * 0, 2, 4, 5, 6, 7, 8, 9, 10, 3 (case 3 last, and its pool entry is likewise the highest
 * -- it reads like a move added after the others). Case 1 has no body of its own and
 * falls to the default. Written this way the whole 552-byte layout was byte-exact on the
 * first compile.
 *
 * FX_Inv takes TWO arguments here despite the name -- the ROM computes both r0 and r1,
 * and the tree's other callers agree (`FX_Inv(gap, reach)`); it is a divide. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };

extern int FX_Inv(int a, int b);
extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov245_020cd668(void);
extern void func_ov245_020cd73c(void);
extern void func_ov245_020cd814(void);
extern void func_ov245_020cd8f0(void);
extern void func_ov245_020cd958(void);
extern void func_ov245_020cdcb4(void);
extern void func_ov245_020cdedc(void);
extern void func_ov245_020ce130(void);
extern void func_ov245_020ce394(void);
extern void func_ov245_020ce7ec(void);

void func_ov245_020ccfa8(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    int t;
    signed char slot;

    t = ctx[0xf] + 0xf000;
    ctx[0xe] = FX_Inv(*(int *)(ctx[2] + 8) - t, -0xb000 - t);
    slot = *(signed char *)(*ctx + 0x1c7);
    if (slot == -1) {
        return;
    }
    *(char *)(*ctx + 0x1c6) = slot;
    ((struct hw60 *)(*ctx + 0x60))->hi &= ~0x82;
    *(unsigned short *)(*ctx + 0x1ae) &= ~3;
    ((struct b8 *)(*(int *)(*ctx + 0x3b4) + 8))->f |= 1;
    ((struct b8 *)(*(int *)(*ctx + 0x3b4) + 8))->f &= ~2;
    ctx[0xf] = 0;
    switch (*(signed char *)(*ctx + 0x1c6)) {
    case 0:  func_0203c634(self, 1, func_ov245_020cd668); break;
    case 2:  func_0203c634(self, 1, func_ov245_020cd73c); break;
    case 4:  func_0203c634(self, 1, func_ov245_020cd814); break;
    case 5:  func_0203c634(self, 1, func_ov245_020cd8f0); break;
    case 6:  func_0203c634(self, 1, func_ov245_020cd958); break;
    case 7:  func_0203c634(self, 1, func_ov245_020cdcb4); break;
    case 8:  func_0203c634(self, 1, func_ov245_020cdedc); break;
    case 9:  func_0203c634(self, 1, func_ov245_020ce130); break;
    case 10: func_0203c634(self, 1, func_ov245_020ce394); break;
    case 3:  func_0203c634(self, 1, func_ov245_020ce7ec); break;
    }
    *(char *)(*ctx + 0x1c7) = -1;
}
