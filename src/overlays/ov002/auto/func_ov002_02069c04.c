extern int data_ov002_0207fa00;

void func_ov002_02069c04(void) {
    int p = *(int *)&data_ov002_0207fa00 + 0x8c94;
    *(char *)(p + 5) = 0;
    *(char *)(p + 6) = 1;
    *(char *)(p + 7) = 2;
}
