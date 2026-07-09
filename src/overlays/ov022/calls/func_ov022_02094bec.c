extern int func_ov022_02095648(int arg0);
int func_ov022_02094bec(int arg0) {
    int r = 0;
    int a = *(int *)(arg0 + 0x328);
    int b = func_ov022_02095648(arg0);
    if (*(unsigned short *)(a + 0x12) <= b) r = 1;
    return r;
}
