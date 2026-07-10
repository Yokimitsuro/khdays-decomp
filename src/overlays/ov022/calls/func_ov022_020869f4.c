extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_02086970(void);

int func_ov022_020869f4(void) {
    int h = NNSi_FndGetCurrentRootHeap();
    if (*(char *)(h + 0xc3) == 0) {
        *(unsigned char *)(h + 0xc0) = 3;
        return (int)func_ov022_02086970;
    }
    *(unsigned char *)(h + 0xc2) = 4;
    *(unsigned char *)(h + 0xc0) = 3;
    return (int)func_ov022_02086970;
}
