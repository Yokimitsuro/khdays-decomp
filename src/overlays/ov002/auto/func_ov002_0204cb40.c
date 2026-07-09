int func_ov002_0204cb40(int arg0) {
    if (arg0 == -1) {
        return 0;
    }
    int p = *(int *)(arg0 + 0x20);
    return p != 0 ? (*(int *)(p + 0x38) & 0x2000) : 0;
}
