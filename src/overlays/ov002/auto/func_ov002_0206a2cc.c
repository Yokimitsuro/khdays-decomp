extern int data_ov002_0207fa00;

void func_ov002_0206a2cc(void) {
    int p = *(int *)&data_ov002_0207fa00 + 0x8d6c;
    *(char *)p = 0;
    *(char *)(p + 0xc) = -1;
}
