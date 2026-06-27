extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_02030d60(void);

int func_02030a2c(void) {
    void **h = (void **)NNSi_FndGetCurrentRootHeap();
    if (*h == 0) {
        func_02030d60();
    }
    return 0;
}
