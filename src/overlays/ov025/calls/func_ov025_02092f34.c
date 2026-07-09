extern int NNS_FndRemoveListObject();
extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_02092f34(int arg0, int arg1) {
    NNS_FndRemoveListObject(arg0 + 0x1e7c, arg1);
    if (arg1 == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap(arg1);
}
