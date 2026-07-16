extern int NNSi_FndGetCurrentRootHeap();
extern void func_ov026_020829e0();

int func_ov026_020829b4(void) {
    unsigned int *h = (unsigned int *)NNSi_FndGetCurrentRootHeap();
    if ((*h & 8) != 0) {
        *h &= 0xfffffff7;
        return (int)func_ov026_020829e0;
    }
    return 0;
}
