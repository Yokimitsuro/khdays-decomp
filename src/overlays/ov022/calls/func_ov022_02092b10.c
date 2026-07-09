extern int func_ov022_02092af8(unsigned char *arg0);
int func_ov022_02092b10(unsigned char *arg0, int arg1) {
    unsigned short *pf = (unsigned short *)(arg0 + 0x178);
    if (!func_ov022_02092af8(arg0)) return 0;
    if ((int)pf[1] <= arg1) return 0;
    return *(int *)(arg0 + 0x170) == 0;
}
