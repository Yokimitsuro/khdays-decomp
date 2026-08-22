/*
 * Ov002_StartBlendFade - drive the blend level from one value to another.
 *
 * Both ends are clamped to the sixteen levels the hardware has. The starting
 * level may be given as -1, which means "from wherever it is now", so its clamp
 * floor is -1 rather than zero. The level is written straight away and the
 * tween is set running from it, and the layer request is set so the display
 * commit acts on the change next frame.
 *
 * ARM. The level is kept as fixed point and the byte written back is its whole
 * part, which is what gives the ROM's shift up and straight back down instead
 * of a plain store of the argument.
 */

extern void func_02035fb0(void *pTween, int nMode, int nFrom, int nTo,
                          int nDuration);
extern void func_02035ffc(void *pTween);

extern int data_ov002_0207f60c;

void func_ov002_020537bc(int nFrom, int nTo, int nDuration)
{
    unsigned char *pUi;
    int nFromFx;

    pUi = *(unsigned char **)&data_ov002_0207f60c;

    if (nFrom > 0x10) {
        nFrom = 0x10;
    } else if (nFrom < -1) {
        nFrom = -1;
    }
    if (nTo > 0x10) {
        nTo = 0x10;
    } else if (nTo < 0) {
        nTo = 0;
    }
    if (nFrom < 0) {
        nFrom = pUi[0x11];
    }

    nFromFx = nFrom << 12;
    pUi[0x11] = (unsigned char)(nFromFx >> 12);
    func_02035fb0(pUi + 0xc0, 0, nFromFx, nTo << 12, nDuration);
    func_02035ffc(pUi + 0xc0);
    pUi[0x10] = 2;
}
