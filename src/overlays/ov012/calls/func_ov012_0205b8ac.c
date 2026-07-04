extern int NNSi_FndGetCurrentRootHeap();
extern void func_02020a78();

int func_ov012_0205b8ac(void) {
    unsigned short *p = (unsigned short *)(NNSi_FndGetCurrentRootHeap() + 2);
    unsigned int v = *p | 8;
    *p = v;
    if ((v & 0x10) == 0) return 0;
    func_02020a78(5, 0x190);
    return -2;
}
