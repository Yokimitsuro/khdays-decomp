extern int data_ov002_0207fa04;
extern void func_ov002_0206e99c(int id);

void func_ov002_0206eda0(void) {
    char *ctx = (char *)*(int *)&data_ov002_0207fa04;
    int i;

    for (i = 0; i < 0x20; i++) {
        func_ov002_0206e99c(0x1000 | i);
        ctx[i + 0x22c] = 0;
    }
}
