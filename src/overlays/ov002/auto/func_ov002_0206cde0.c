extern int data_ov002_0207fa00;

void func_ov002_0206cde0(int arg0, int arg1, int arg2) {
    int base = *(int *)&data_ov002_0207fa00 + 0x8c94;
    *(char *)(base + arg0 + 0x1b) = arg1;
    *(unsigned short *)(base + arg0 * 2 + 0x20) = arg2;
}
