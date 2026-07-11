/* LCG random (state at data_0204c168 = {seed, a, c}); returns a 16-bit value,
 * scaled into [0,range) when range != 0. */
extern unsigned int data_0204c168;
unsigned int func_02023e80(unsigned int range) {
    unsigned int *st = &data_0204c168;
    unsigned int r = st[1] * st[0] + st[2];
    st[0] = r;
    if (range == 0) {
        return (unsigned short)(r >> 16);
    }
    return (unsigned short)(((r >> 16) * range) >> 16);
}
