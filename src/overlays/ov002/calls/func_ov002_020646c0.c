extern int data_ov002_0207f634;
extern int func_ov002_02065698();

void func_ov002_020646c0(void) {
    int p = *(int *)&data_ov002_0207f634;
    if (p != 0) {
        func_ov002_02065698(p);
    }
}
