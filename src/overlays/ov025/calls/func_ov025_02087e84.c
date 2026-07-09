extern int NNS_FndGetNextListObject();
extern void func_ov025_02087e0c();

void func_ov025_02087e84(int arg0) {
    int e = NNS_FndGetNextListObject((void *)(arg0 + 19000), 0);
    if (e != 0) {
        do {
            func_ov025_02087e0c(arg0, e);
            e = NNS_FndGetNextListObject((void *)(arg0 + 19000), e);
        } while (e != 0);
    }
}
