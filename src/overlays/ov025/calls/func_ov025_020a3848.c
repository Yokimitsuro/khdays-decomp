extern int NNS_FndGetNextListObject();
extern void func_ov025_020a3754();

void func_ov025_020a3848(int arg0) {
    int e = NNS_FndGetNextListObject((void *)(arg0 + 0x1cc), 0);
    if (e == 0) return;
    do {
        int next = NNS_FndGetNextListObject((void *)(arg0 + 0x1cc), e);
        func_ov025_020a3754(arg0, e);
        e = next;
    } while (e != 0);
}
