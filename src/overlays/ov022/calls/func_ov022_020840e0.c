extern int data_ov022_020b2e6c;
extern void func_ov022_02085380(void);

int func_ov022_020840e0(void) {
    int v = ((int *)&data_ov022_020b2e6c)[1];
    if (v > 2) {
        return (int)func_ov022_02085380;
    }
    ((int *)&data_ov022_020b2e6c)[1] = v + 1;
    return 0;
}
