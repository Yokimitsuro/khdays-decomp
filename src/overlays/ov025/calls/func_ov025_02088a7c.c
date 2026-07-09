extern int NNS_FndGetNextListObject();
extern void func_ov025_02088a38();

void func_ov025_02088a7c(int arg0, unsigned int arg1) {
    int e = NNS_FndGetNextListObject((void *)(arg0 + 19000), 0);
    if (e != 0) {
        do {
            func_ov025_02088a38(arg0, e, arg1);
            e = NNS_FndGetNextListObject((void *)(arg0 + 19000), e);
        } while (e != 0);
    }
}
