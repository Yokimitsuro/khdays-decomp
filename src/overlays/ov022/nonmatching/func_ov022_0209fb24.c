/*
 * [nonmatching: dead `| 0` self-store — unreproducible from clean C]
 *
 * Sets bit0 on the root heap's word 0, installs a handler pointer at [0x118],
 * and returns func_ov022_02095940.
 *
 * The original also emits `p[1] = p[1] | 0` (`movs r2,#0; orrs r2,p[1];
 * str r2,[p,#4]`) — an OR with a build-time 0-valued flag macro. mwcc 3.0/139
 * constant-folds any literal `| 0` and drops the store entirely (4B short);
 * omitting it is equally short. Same class as the dead `& 0` guard terms — the
 * held-0 flag cannot be reproduced without the original header's 0 constant, so
 * this is left uncarved (byte-exact in the blob).
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_020a37d0(void);
extern void func_ov022_02095940(void);

int func_ov022_0209fb24(void) {
    unsigned int *p = (unsigned int *)NNSi_FndGetCurrentRootHeap();
    *p |= 1;
    p[1] = p[1];
    p[0x118] = (unsigned int)func_ov022_020a37d0;
    return (int)func_ov022_02095940;
}
