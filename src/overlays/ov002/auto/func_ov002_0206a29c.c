extern int data_ov002_0207fa00;

void func_ov002_0206a29c(void) {
    int base = *(int *)&data_ov002_0207fa00 + 0x8d64;
    *(char *)(base + 4) = -1;
    *(int *)base = -1;
}
