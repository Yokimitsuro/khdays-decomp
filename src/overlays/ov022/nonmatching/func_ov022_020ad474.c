/*
 * [nonmatching: dead `& 0` flag term: the (*p&0x10) guard has a companion (p[0x11b]&0) that the compiler emits as `and r1,r1,#0; cmp r1,#0`; mwcc folds any literal & 0]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
void func_ov022_020ad474(unsigned int *arg0) {
    arg0[0x119] = 0;
    arg0[0x11a] = 0;
    if ((*arg0 & 0x10) != 0) {
        arg0[0x119] = 0x100;
        arg0[0x11a] = 0;
    }
    if (arg0[0x11c] != 0 || arg0[0x11b] != 0) {
        arg0[0x119] = arg0[0x119] | arg0[0x11b];
        arg0[0x11a] = arg0[0x11a] | arg0[0x11c];
        arg0[0x11b] = 0;
        arg0[0x11c] = 0;
    }
}
