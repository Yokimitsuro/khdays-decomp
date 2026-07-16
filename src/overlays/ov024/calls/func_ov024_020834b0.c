/* func_ov024_020834b0 -- MobiClip: initialise the decoder from the parsed stream header.
 * Copies the header into the decoder's own copy (7 u16s, with the slot at +0xc forced to 0
 * and the version/flags word landing at +0xe), then derives the active picture size from the
 * macroblock dimensions minus the four crop margins:
 *     width  = mb_width  * 8 - crop_left - crop_right
 *     height = mb_height * 8 - crop_top  - crop_bottom
 * and clears the per-frame reconstruction state. */
struct MobiClipHeader {
    unsigned short f0;
    unsigned short f2;
    unsigned short mb_width;
    unsigned short mb_height;
    unsigned short f8;
    unsigned short fa;
    unsigned short flags;
    unsigned short crop_left;
    unsigned short crop_right;
    unsigned short crop_top;
    unsigned short crop_bottom;
};

void func_ov024_020834b0(int ctx, unsigned short *dst, unsigned short *src) {
    int i;

    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = 0;
    dst[7] = src[6];

    *(int *)(ctx + 0x60) = 1;
    *(int *)(ctx + 0x64) = 0;
    *(int *)(ctx + 0x74) = 0;
    *(int *)(ctx + 0x6c) = 0;

    *(unsigned int *)(ctx + 0x54) = src[6];
    *(unsigned short *)(ctx + 0x48) = src[7];
    *(unsigned short *)(ctx + 0x4a) = src[8];
    *(unsigned short *)(ctx + 0x4c) = src[9];
    *(unsigned short *)(ctx + 0x4e) = src[10];

    *(unsigned int *)(ctx + 0x40) =
        (src[2] * 8 - *(unsigned short *)(ctx + 0x48)) - *(unsigned short *)(ctx + 0x4a);
    *(unsigned int *)(ctx + 0x44) =
        (src[3] * 8 - *(unsigned short *)(ctx + 0x4c)) - *(unsigned short *)(ctx + 0x4e);

    *(int *)(ctx + 0x70) = 0;
    *(int *)(ctx + 0x58) = 0;
    *(int *)(ctx + 0x5c) = 0;
    *(int *)(ctx + 0x88) = 0;

    i = 0;
    do {
        ((int *)ctx)[i + 0x1e] = 0;
        i = i + 1;
    } while (i < 4);

    *(int *)(ctx + 0x50) = 0;
}
