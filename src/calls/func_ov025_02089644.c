extern int NNS_FndRemoveListObject();
extern int *NNS_FndGetNextListObject();

void func_ov025_02089644(int *r6) {
    int *r5;
    int *r4;

    r5 = NNS_FndGetNextListObject(r6, 0);
    if (r5 != 0) {
        do {
            r4 = NNS_FndGetNextListObject(r6, r5);
            r5[8] &= ~1;
            NNS_FndRemoveListObject(r6, r5);
            r5 = r4;
        } while (r4 != 0);
    }
    r6[6] = 0;
}
