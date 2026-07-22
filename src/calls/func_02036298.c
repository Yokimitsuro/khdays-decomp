/* Zeroes the 0x1a-byte header, then takes the two limits from `src` (defaults 0xf and 4
 * when src is NULL or the stored value is negative) and clears the 0x14-byte body at +6.
 *
 * Each limit is `src[k] >= 0 ? (unsigned short)src[k] : default` -- the positive arm has
 * to be inline (that is the ROM's `blt` to the default) and the cast has to be a single
 * (unsigned short); a (short)(unsigned short) pair adds a second lsl/asr round trip. */
extern void MI_CpuFill8(void *p, int v, unsigned int n);
extern void MIi_CpuClear16(int v, void *p, unsigned int n);

int func_02036298(short *o, short *src) {
    MI_CpuFill8(o, 0, 0x1a);
    if (src != 0) {
        o[1] = src[0] >= 0 ? (unsigned short)src[0] : 0xf;
        o[2] = src[1] >= 0 ? (unsigned short)src[1] : 4;
    } else {
        o[1] = 0xf;
        o[2] = 4;
    }
    MIi_CpuClear16(0, o + 3, 0x14);
    return 1;
}
