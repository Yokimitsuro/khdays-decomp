extern int NNS_FndGetNextListObject();
extern void func_ov025_02084b78();
extern int data_ov025_020b5744;

void func_ov025_02084bf8(void) {
    int e = NNS_FndGetNextListObject((void *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x9660), 0);
    if (e != 0) {
        do {
            int next = NNS_FndGetNextListObject((void *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x9660), e);
            func_ov025_02084b78(e);
            e = next;
        } while (e != 0);
    }
}
