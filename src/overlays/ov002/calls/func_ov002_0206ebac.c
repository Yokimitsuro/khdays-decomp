extern int data_ov002_0207fa04;
extern int func_01fff974(void);

int func_ov002_0206ebac(void) {
    int ctx = *(int *)&data_ov002_0207fa04;
    return *(unsigned char *)(ctx + 0xa) == func_01fff974();
}
