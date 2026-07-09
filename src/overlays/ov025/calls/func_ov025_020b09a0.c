extern int OS_IsThreadTerminated();
extern void NNSi_FndFreeFromDefaultHeap();
extern int data_ov025_020b5760;

int func_ov025_020b09a0(void) {
    int r = -1;
    if (*(int *)((char *)&data_ov025_020b5760 + 8) != 0 &&
        OS_IsThreadTerminated(*(int *)((char *)&data_ov025_020b5760 + 8))) {
        r = *(int *)(*(int *)((char *)&data_ov025_020b5760 + 8) + 0x2cc);
        NNSi_FndFreeFromDefaultHeap(*(int *)((char *)&data_ov025_020b5760 + 8));
        *(int *)((char *)&data_ov025_020b5760 + 8) = 0;
    }
    return r;
}
