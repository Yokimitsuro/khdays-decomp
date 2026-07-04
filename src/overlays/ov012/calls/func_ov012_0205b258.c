extern int NNSi_FndGetCurrentRootHeap();

int func_ov012_0205b258(void) {
    int h = NNSi_FndGetCurrentRootHeap();
    return *(int *)(h + 0x8bd8) == 2 || *(int *)(h + 0x8bdc) == 2;
}
