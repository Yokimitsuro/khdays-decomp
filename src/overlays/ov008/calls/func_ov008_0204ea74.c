/* Touch the current root heap, then return the address of func_ov008_0204e04c. */
extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov008_0204e04c(void);

void *func_ov008_0204ea74(void) {
    NNSi_FndGetCurrentRootHeap();
    return (void *)&func_ov008_0204e04c;
}
