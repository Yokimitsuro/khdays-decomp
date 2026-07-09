extern int data_ov002_0207fa10;

int func_ov002_0207299c(void) {
    int p = *(int *)(*(int *)&data_ov002_0207fa10 + 4);
    if (p == 0) {
        return 0xff;
    }
    return *(unsigned char *)(p + 1);
}
