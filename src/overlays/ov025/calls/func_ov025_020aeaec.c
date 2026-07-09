extern int data_0204c18c;
extern void func_ov025_020adee0();

void func_ov025_020aeaec(int arg0) {
    if (*(int *)(arg0 + 0xc) != 0) return;
    if (*(int *)(arg0 + 0x10) != 0) return;
    if ((*(unsigned short *)&data_0204c18c & 0xf0) != 0x80) return;
    int nv = *(int *)(arg0 + 0x2c8) + 1;
    if (nv >= *(int *)(arg0 + 8)) nv = 0;
    if (nv != *(int *)(arg0 + 0x2c8)) func_ov025_020adee0(arg0, nv, 1);
}
