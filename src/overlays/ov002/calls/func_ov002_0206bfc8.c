/*
 * Packs whatever the tally bookkeeping has changed into one variable-length
 * message and sends it.
 *
 * A change mask drives the whole thing: nothing set means nothing to send. Bit
 * zero appends the scalar, bit one appends the pair split into its two halves,
 * bit two appends the five mission ids packed three bits apiece, and the top
 * four bits each append their slot if it carries a value. The message is a kind
 * byte, the mask, and only the halves the mask selected, so its length is the
 * distance the cursor travelled plus the two-byte header.
 *
 * Only once the sender takes it is the bookkeeping cleared and success
 * reported.
 *
 * Three things here are load-bearing rather than style.
 *
 * The mask is read into a local once. Read through the context twice, the
 * compiler reloads it for the first bit test instead of reusing what it just
 * stored into the message.
 *
 * The mask is written into the message before the kind byte, which is the
 * order the original stores them in.
 *
 * The id-packing loop initialises its counter and its shift together in the
 * for statement, with the accumulator cleared before it. That order is what
 * makes the counter, not the shift, the register the cleared accumulator is
 * stored from.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Ov002RootContext {
    char pad0000[0x8b6a];
    u16 nTallyChangedMask;
    s16 nTallyScalar;
    s16 anTallySlots[4];
    char pad8b76[2];
    int nTallyPair;
    char pad8b7c[0x109];
    s8 anTallyIds[5];
} Ov002RootContext;

typedef struct Ov002TallyCmd {
    u8 nKind;
    u8 nMask;
    s16 aBody[9];
} Ov002TallyCmd;

extern Ov002RootContext *data_ov002_0207fa00;

extern void func_ov002_020679c4(int nPair, s16 *pFirst, s16 *pSecond);
extern int func_02031384(int nKind, void *pCmd, u16 nSize);
extern void MIi_CpuClear16(u16 nValue, void *pDest, u32 nSize);

int func_ov002_0206bfc8(void)
{
    Ov002RootContext *pCtx;
    s16 *pOut;
    int i;
    int nShift;
    s16 nFirst;
    s16 nSecond;
    u16 nMask;
    Ov002TallyCmd cmd;

    pCtx = data_ov002_0207fa00;
    pOut = cmd.aBody;
    nMask = pCtx->nTallyChangedMask;
    if (nMask == 0) {
        return;
    }

    cmd.nMask = (u8)nMask;
    cmd.nKind = 10;

    if ((cmd.nMask & 1) != 0 && pCtx->nTallyScalar != 0) {
        *pOut++ = pCtx->nTallyScalar;
    }

    if ((cmd.nMask & 2) != 0 && pCtx->nTallyPair != 0) {
        nFirst = 0;
        nSecond = 0;
        func_ov002_020679c4(pCtx->nTallyPair, &nFirst, &nSecond);
        pOut[0] = nFirst;
        pOut[1] = nSecond;
        pOut += 2;
    }

    if ((cmd.nMask & 4) != 0) {
        *pOut = 0;
        for (i = 0, nShift = 0; i < 5; i++, nShift += 3) {
            *pOut = (s16)(*pOut | ((pCtx->anTallyIds[i] & 7) << nShift));
        }
        pOut++;
    }

    for (i = 0; i < 4; i++) {
        if ((cmd.nMask & (1 << (i + 3))) != 0 && pCtx->anTallySlots[i] != 0) {
            *pOut++ = pCtx->anTallySlots[i];
        }
    }

    if (func_02031384(7, &cmd,
                      (u16)((char *)pOut - (char *)cmd.aBody + 2)) != 0xffff) {
        pCtx->nTallyChangedMask = 0;
        pCtx->nTallyPair = 0;
        pCtx->nTallyScalar = 0;
        MIi_CpuClear16(0, pCtx->anTallySlots, 8);
        return 1;
    }
    return 0;
}
