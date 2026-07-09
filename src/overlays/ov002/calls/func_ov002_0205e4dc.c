extern int data_ov002_0207f620;
extern int func_ov002_0205ca00();

void func_ov002_0205e4dc(void) {
    int p = *(int *)&data_ov002_0207f620;
    if (p != 0) {
        func_ov002_0205ca00(p);
    }
}
