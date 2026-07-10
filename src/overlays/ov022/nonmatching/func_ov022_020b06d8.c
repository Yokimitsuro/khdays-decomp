/*
 * [nonmatching: range-reduce guard (==0||==1 -> cmp#1;bls vs orig cmp#0;cmpne#1;bxeq) + byte-bitfield &=0xfc split (bic#1;and#0xff;bic#2)]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
void func_ov022_020b06d8(int arg0, unsigned int arg1) {
    int i = 0;
    do {
        ((short *)arg0)[i + 0x1c] = -1;
        i = i + 1;
    } while (i < 8);
    if (arg1 == 0 || arg1 == 1) return;
    if (arg1 != 2) return;
    *(unsigned char *)(arg0 + 0x34) &= 0xfc;
}
