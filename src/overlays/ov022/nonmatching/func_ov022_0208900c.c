/*
 * [nonmatching: register-allocation: param_3 held across NNSi + the loop needs one extra callee-saved reg vs the original (push 5 regs vs 4, +4B)]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_02089078(int arg0, int arg1, int arg2);

void func_ov022_0208900c(int arg0, int arg1, int arg2) {
    unsigned char *p = (unsigned char *)NNSi_FndGetCurrentRootHeap();
    int i;
    if ((((unsigned int)p[1] << 0x1c) >> 0x1f) == 0) return;
    if (((unsigned int)*p << 0x18) >> 0x1a == 0) return;
    i = 0;
    do {
        int e = *(int *)(p + 0xc);
        if (*(char *)(e + i * 0x114) != 0) {
            func_ov022_02089078(e + i * 0x114, e, arg2);
        }
        i = i + 1;
    } while (i < (int)(((unsigned int)*p << 0x18) >> 0x1a));
}
