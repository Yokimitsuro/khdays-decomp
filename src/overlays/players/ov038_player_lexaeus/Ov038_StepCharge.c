/* Drives the ov038 charge sequence. Instruction-for-instruction the same
 * routine as the matched ov084 driver on a different block layout: the
 * state/timer pair lives at +0 and +0x10c, the emitter at +4, and each of the
 * two transitions also rebinds the scene's default animations and re-arms the
 * sequence block at +0x118 of it.
 *
 * NO `default:` and NO `case 0:` -- state 0 and anything above 4 fall through
 * the jump table to the function's implicit end, which is why the ROM's default
 * and case-0 slots are bare pop instructions rather than branches.
 *
 * The release guard tests a 64-bit flag word: the mask 0x40 belongs to the high
 * half, so written as a long long the compiler ands the low word with zero,
 * which is exactly what the ROM does. */
extern void Ov038_ReleaseGlobalSlotIfSet(int self, int *p2);
extern void Ov038_BindChargeTracks(int p2, int a);
extern void Ov038_BindDefaultAnims(int self, void *block);
extern void Ov038_RearmSequenceSlots(int self, void *block, int a);
extern unsigned short Sequence_UpdateTracks(void *p, int a);
extern void Ov022_PlayEntityVoice(int self, int nSeqArc, int nSeq);
extern int Ov022_IsSlotReady(void *p);

extern int data_ov038_020b4ca0;

struct Ov038Self {
    char pad000[0x464];
    long long flags464;
    char pad46c[0x250];
    int nStage6bc;
};

void Ov038_StepCharge(int self, int *p2, int p3) {
    char *blk = (char *)(*(int *)&data_ov038_020b4ca0 + 0x2c + 0x2c00);

    if (*p2 != 0 && (((struct Ov038Self *)self)->nStage6bc != 0x31 ||
                     (((struct Ov038Self *)self)->flags464 & 0x4000000000LL) != 0)) {
        Ov038_ReleaseGlobalSlotIfSet(self, p2);
    }
    if (*p2 == 0) {
        return;
    }
    if (*p2 != 4) {
        *(int *)((char *)p2 + 0x10c) += p3;
    }
    switch (*p2) {
    case 1:
        if (*(int *)((char *)p2 + 0x10c) < 0) {
            return;
        }
        Ov038_BindChargeTracks((int)p2, 0);
        *p2 = 2;
        *(int *)((char *)p2 + 0x10c) = 0;
        return;
    case 2:
        Sequence_UpdateTracks((void *)((char *)p2 + 4), p3);
        if (*(int *)((char *)p2 + 0x10c) < 0xf000) {
            return;
        }
        Ov022_PlayEntityVoice(self, 0xc8, 2);
        Ov038_BindChargeTracks((int)p2, 1);
        Ov038_BindDefaultAnims(self, blk);
        Ov038_RearmSequenceSlots(self, blk + 0x118, 0);
        *p2 = 3;
        *(int *)((char *)p2 + 0x10c) = 0;
        return;
    case 3:
        Sequence_UpdateTracks((void *)((char *)p2 + 4), p3);
        if (*(int *)((char *)p2 + 0x10c) < 0xf000) {
            return;
        }
        if (Ov022_IsSlotReady((void *)(self + 0x22f8)) == 0) {
            return;
        }
        Ov022_PlayEntityVoice(self, 0xc8, 3);
        Ov038_BindChargeTracks((int)p2, 2);
        Ov038_BindDefaultAnims(self, blk);
        Ov038_RearmSequenceSlots(self, blk + 0x118, 2);
        *p2 = 4;
        *(int *)((char *)p2 + 0x10c) = 0;
        return;
    case 4:
        Sequence_UpdateTracks((void *)((char *)p2 + 4), p3);
        return;
    }
}
