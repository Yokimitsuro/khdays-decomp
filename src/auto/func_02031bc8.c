/*
 * Number of fixed-size blocks needed to cover a byte span, where the block
 * size is selected by a 2-bit field of the descriptor at param_2.
 *   span = *(param_1+0x4610) - *(param_1+0x460c)
 *   sel  = (*(int*)(param_2+8) >> 0x14) & 3  ->  block size 32/64/128/256
 * Returns ceil(span / blocksize) via round-up-then-logical-shift.
 */
unsigned int func_02031bc8(unsigned int param_1, int param_2) {
    int span = *(int *)(param_1 + 0x4610) - *(int *)(param_1 + 0x460c);

    switch ((*(int *)(param_2 + 8) >> 0x14) & 3) {
    case 0: return (unsigned int)(span + 0x1f) >> 5;
    case 1: return (unsigned int)(span + 0x3f) >> 6;
    case 2: return (unsigned int)(span + 0x7f) >> 7;
    case 3: return (unsigned int)(span + 0xff) >> 8;
    }
    return param_1;
}
