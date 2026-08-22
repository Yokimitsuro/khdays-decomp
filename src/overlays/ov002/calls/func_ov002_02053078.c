/*
 * Ov002_SampleBlendTween - advance the blend level from its tween.
 *
 * The tween at +0xc0 drives the level; the flag word this reads at +0xd8 is
 * that tween's own, and bit 2 is the one the sampler sets when the tween
 * finishes. So the function does nothing once the fade is over, samples it
 * otherwise, and asks for the layer to be shown on the frame the sample
 * completes it.
 *
 * The maths coprocessor's context is saved around the sample - the sampler
 * divides, and this runs from a frame update that may itself be interrupting
 * one - and the hardware divider is waited out before the fixed-point result is
 * read back. The level is the sample's whole part. A fade that has landed on
 * zero is left alone.
 *
 * ARM. The flag is read as a one-bit field rather than masked, which is what
 * gives the ROM's lsl #29 / lsrs #31 pair instead of a tst.
 */

typedef struct {
    unsigned int pad0 : 2;
    unsigned int bFinished : 1;   /* set by the sampler when the tween ends */
} Ov002TweenFlags;

extern void CP_SaveContext(void *pContext);
extern void CPi_RestoreContext(void *pContext);
extern void func_0203602c(void *pTween, int *pValue);

extern int data_ov002_0207f60c;

void func_ov002_02053078(void)
{
    volatile unsigned short *pRegDivCnt = (volatile unsigned short *)0x04000280;
    unsigned char *pUi;
    int nSample;
    int nContext[7];

    pUi = *(unsigned char **)&data_ov002_0207f60c;
    nSample = 0;
    if (((Ov002TweenFlags *)(pUi + 0xd8))->bFinished) {
        return;
    }

    CP_SaveContext(nContext);
    func_0203602c(pUi + 0xc0, &nSample);
    CPi_RestoreContext(nContext);
    while ((*pRegDivCnt & 0x8000) != 0) {
    }

    pUi[0x11] = (unsigned char)(nSample >> 12);
    if (*(int *)(pUi + 8) != 0 && pUi[0x11] == 0) {
        return;
    }
    if (((Ov002TweenFlags *)(pUi + 0xd8))->bFinished) {
        pUi[0x10] = 1;
    }
}
