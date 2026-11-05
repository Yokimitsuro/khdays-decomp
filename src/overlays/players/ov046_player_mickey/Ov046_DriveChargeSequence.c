/* Drive the charge sequence (x4: ov046 + 3 twins). Instruction-for-instruction the same
 * routine as ov048's 020b3e88, on a different block layout: the state/timer pair lives at
 * +0x110/+0x114 (ov048: +0x358/+0x35c), the emitter at +4 (ov048: +0x24c), and it retunes
 * channel 0xd6 rather than 0xd5.
 *
 * NO `default:` and NO `case 0:` -- state 0 and anything above 4 fall through the jump table
 * to the function's implicit end, which is why the ROM's default and case-0 slots are bare
 * `pop {r3,r4,r5,pc}` instructions rather than branches. See codegen-cracks.md. */
extern void Ov046_BindChargeTracks(int p2, int a);
extern unsigned short Sequence_UpdateTracks(void *p, int a);
extern void Ov022_PlayEntityVoice(int self, int nSeqArc, int nSeq);
extern int Ov022_IsSlotReady(void *p);

void Ov046_DriveChargeSequence(int self, int p2, int p3) {
    if (*(int *)(p2 + 0x110) != 0 && *(int *)(self + 0x6bc) != 0x2f) {
        *(int *)(p2 + 0x110) = 0;
    }
    if (*(int *)(p2 + 0x110) == 0) {
        return;
    }
    if (*(int *)(p2 + 0x110) != 4) {
        *(int *)(p2 + 0x114) += p3;
    }
    switch (*(int *)(p2 + 0x110)) {
    case 1:
        if (*(int *)(p2 + 0x114) < 0) {
            return;
        }
        Ov046_BindChargeTracks(p2, 0);
        *(int *)(p2 + 0x110) = 2;
        *(int *)(p2 + 0x114) = 0;
        return;
    case 2:
        Sequence_UpdateTracks((void *)(p2 + 4), p3);
        if (*(int *)(p2 + 0x114) < 0xf000) {
            return;
        }
        Ov046_BindChargeTracks(p2, 1);
        Ov022_PlayEntityVoice(self, 0xd6, 2);
        *(int *)(p2 + 0x110) = 3;
        *(int *)(p2 + 0x114) = 0;
        return;
    case 3:
        Sequence_UpdateTracks((void *)(p2 + 4), p3);
        if (*(int *)(p2 + 0x114) < 0xf000) {
            return;
        }
        if (Ov022_IsSlotReady((void *)(self + 0x22f8)) == 0) {
            return;
        }
        Ov046_BindChargeTracks(p2, 2);
        Ov022_PlayEntityVoice(self, 0xd6, 3);
        *(int *)(p2 + 0x110) = 4;
        *(int *)(p2 + 0x114) = 0;
        return;
    case 4:
        Sequence_UpdateTracks((void *)(p2 + 4), p3);
        return;
    }
}
