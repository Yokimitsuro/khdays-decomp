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
extern void func_ov057_020b6304(int pActor, int *pCharge);
extern void func_ov057_020b69e0(int pCharge, int a);
extern void func_ov057_020b64fc(int pActor, void *block);
extern void func_ov057_020b6a34(int pActor, void *block, int a);
extern unsigned int func_0202a818(void *p, int a);
extern void func_ov022_020a4490(int pActor, int a, int b);
extern int func_ov022_02095554(void *p);

extern int data_ov057_020b74a0;

struct Ov057ActorCodegenView {
    char pad000[0x464];
    long long flags464;
    char pad46c[0x250];
    int nStage6bc;
};

void func_ov057_020b6340(int pActor, int *pCharge, int delta) {
    char *pSceneBlock = (char *)(*(int *)&data_ov057_020b74a0 + 0x2c + 0x2c00);

    if (*pCharge != 0 && (((struct Ov057ActorCodegenView *)pActor)->nStage6bc != 0x31 ||
                     (((struct Ov057ActorCodegenView *)pActor)->flags464 & 0x4000000000LL) != 0)) {
        func_ov057_020b6304(pActor, pCharge);
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
        func_ov057_020b69e0((int)pCharge, 0);
        *pCharge = 2;
        *(int *)((char *)pCharge + 0x10c) = 0;
        return;
    case 2:
        func_0202a818((void *)((char *)pCharge + 4), delta);
        if (*(int *)((char *)pCharge + 0x10c) < 0xf000) {
            return;
        }
        func_ov022_020a4490(pActor, 0xc8, 2);
        func_ov057_020b69e0((int)pCharge, 1);
        func_ov057_020b64fc(pActor, pSceneBlock);
        func_ov057_020b6a34(pActor, pSceneBlock + 0x118, 0);
        *pCharge = 3;
        *(int *)((char *)pCharge + 0x10c) = 0;
        return;
    case 3:
        func_0202a818((void *)((char *)pCharge + 4), delta);
        if (*(int *)((char *)pCharge + 0x10c) < 0xf000) {
            return;
        }
        if (func_ov022_02095554((void *)(pActor + 0x22f8)) == 0) {
            return;
        }
        func_ov022_020a4490(pActor, 0xc8, 3);
        func_ov057_020b69e0((int)pCharge, 2);
        func_ov057_020b64fc(pActor, pSceneBlock);
        func_ov057_020b6a34(pActor, pSceneBlock + 0x118, 2);
        *pCharge = 4;
        *(int *)((char *)pCharge + 0x10c) = 0;
        return;
    case 4:
        func_0202a818((void *)((char *)pCharge + 4), delta);
        return;
    }
}
