extern void func_02032450();
extern void NNS_FndRemoveListObject();
extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_02088354(int *arg0, int arg1) {
    if (*(int *)((int)arg0 + 0x4a70) == arg1)
        *(int *)((int)arg0 + 0x4a70) = 0;
    int i = 0;
    do {
        int v = ((int *)arg1)[i + 5];
        if (v != -1) func_02032450(arg0, v);
        i++;
    } while (i < 2);
    NNS_FndRemoveListObject((void *)((int)arg0 + 0x4a38), arg1);
    if (arg1 != 0) NNSi_FndFreeFromDefaultHeap(arg1);
}
