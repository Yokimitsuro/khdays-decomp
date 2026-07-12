/*
 * Build a 5-bit mask over an array of slots at param_1. For each slot i (0..4):
 * skip it unless its signed tag at +i*2+2 is >= 0; then follow the pointer at
 * +i*4+0xc and set bit i when its first field is >= (halfword@[+8]+4) * 0x1000
 * minus param_2. Result is kept to 16 bits.
 */
unsigned int func_0202a928(int param_1, int param_2) {
    unsigned int result = 0;
    unsigned int i = 0;

    do {
        if (((short *)param_1)[i + 1] >= 0) {
            int *p = ((int **)param_1)[i + 3];
            if (*p >= (int)((unsigned int)*(unsigned short *)(p[2] + 4) * 0x1000 - param_2)) {
                result = (result | 1 << i) & 0xffff;
            }
        }
        i = i + 1;
    } while ((int)i < 5);

    return result;
}
