extern int NNS_FndGetNextListObject();

int func_ov025_02087844(int arg0) {
    int count = 0;
    int e;
    for (e = NNS_FndGetNextListObject((void *)(arg0 + 0x20), 0); e != 0;
         e = NNS_FndGetNextListObject((void *)(arg0 + 0x20), e))
        count++;
    return count;
}
