/* Reset the eight channel handles at +0x38 to "unset", and for mode 2 also drop
 * the two playing bits at +0x34. Modes 0 and 1 leave the flags alone.
 *
 * Three details: the unset value is -1 (mvn), not 0xffff -- spelled 0xffff it
 * goes through the literal pool and drags in a stack frame; the two accepted
 * modes must be a SWITCH, since `== 0 || == 1` range-folds to an unsigned
 * compare; and the two bits come off in TWO steps with a byte narrowing between
 * them, which is the bic / and #0xff / bic sequence. */
typedef struct {
    unsigned char bPlaying : 1;
    unsigned char bLooping : 1;
    unsigned char bRest : 6;
} Ov022ChannelFlags;

void func_ov022_020b06d8(unsigned char *self, int mode) {
    int i;

    for (i = 0; i < 8; i++) {
        ((short *)self)[i + 0x1c] = -1;
    }

    switch (mode) {
    case 0:
    case 1:
        return;
    }

    if (mode != 2) {
        return;
    }

    {
        Ov022ChannelFlags *flags = (Ov022ChannelFlags *)(self + 0x34);

        flags->bPlaying = 0;
        flags->bLooping = 0;
    }
}
