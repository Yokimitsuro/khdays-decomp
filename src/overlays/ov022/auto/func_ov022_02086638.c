void func_ov022_02086638(int arg0, int arg1) {
    unsigned int *p = *(unsigned int **)(arg0 + 0x20);
    if (arg1 != 0) *p = *p | 8;
    else *p = *p & 0xfffffff7;
}
