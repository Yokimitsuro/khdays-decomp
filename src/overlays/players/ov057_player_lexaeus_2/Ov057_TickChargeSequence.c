/* Drives the ov057 charge sequence. Instruction-for-instruction the same
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
extern void Ov057_ReleaseGlobalSlotIfSet(int pActor, int *pCharge);
extern void Ov057_BindChargeTracks(int pCharge, int a);
extern void Ov057_BindDefaultAnims(int pActor, void *block);
extern void Ov057_BindSwingSequencePhase(int pActor, void *block, int a);
extern unsigned short Sequence_UpdateTracks(void *p, int a);
extern void Ov022_PlayEntityVoice(int pActor, int nSeqArc, int nSeq);
extern int Ov022_IsSlotReady(void *p);

extern int data_ov057_020b74a0;

struct Ov057ActorCodegenView {
    char pad000[0x464];
    long long flags464;
    char pad46c[0x250];
    int nStage6bc;
};

void Ov057_TickChargeSequence(int pActor, int *pCharge, int delta) {
    char *pSceneBlock = (char *)(*(int *)&data_ov057_020b74a0 + 0x2c + 0x2c00);

    if (*pCharge != 0 && (((struct Ov057ActorCodegenView *)pActor)->nStage6bc != 0x31 ||
                     (((struct Ov057ActorCodegenView *)pActor)->flags464 & 0x4000000000LL) != 0)) {
        Ov057_ReleaseGlobalSlotIfSet(pActor, pCharge);
    }
    if (*pCharge == 0) {
        return;
    }
    if (*pCharge != 4) {
        *(int *)((char *)pCharge + 0x10c) += delta;
    }
    switch (*pCharge) {
    case 1:
        if (*(int *)((char *)pCharge + 0x10c) < 0) {
            return;
        }
        Ov057_BindChargeTracks((int)pCharge, 0);
        *pCharge = 2;
        *(int *)((char *)pCharge + 0x10c) = 0;
        return;
    case 2:
        Sequence_UpdateTracks((void *)((char *)pCharge + 4), delta);
        if (*(int *)((char *)pCharge + 0x10c) < 0xf000) {
            return;
        }
        Ov022_PlayEntityVoice(pActor, 0xc8, 2);
        Ov057_BindChargeTracks((int)pCharge, 1);
        Ov057_BindDefaultAnims(pActor, pSceneBlock);
        Ov057_BindSwingSequencePhase(pActor, pSceneBlock + 0x118, 0);
        *pCharge = 3;
        *(int *)((char *)pCharge + 0x10c) = 0;
        return;
    case 3:
        Sequence_UpdateTracks((void *)((char *)pCharge + 4), delta);
        if (*(int *)((char *)pCharge + 0x10c) < 0xf000) {
            return;
        }
        if (Ov022_IsSlotReady((void *)(pActor + 0x22f8)) == 0) {
            return;
        }
        Ov022_PlayEntityVoice(pActor, 0xc8, 3);
        Ov057_BindChargeTracks((int)pCharge, 2);
        Ov057_BindDefaultAnims(pActor, pSceneBlock);
        Ov057_BindSwingSequencePhase(pActor, pSceneBlock + 0x118, 2);
        *pCharge = 4;
        *(int *)((char *)pCharge + 0x10c) = 0;
        return;
    case 4:
        Sequence_UpdateTracks((void *)((char *)pCharge + 4), delta);
        return;
    }
}
