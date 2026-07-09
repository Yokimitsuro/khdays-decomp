extern int NNSi_FndGetCurrentRootHeap();
extern void func_ov025_020829f8();

int func_ov025_020829cc(void) {
    unsigned int *h = (unsigned int *)NNSi_FndGetCurrentRootHeap();
    if ((*h & 8) != 0) {
        *h &= 0xfffffff7;
        return (int)func_ov025_020829f8;
    }
    return 0;
}
