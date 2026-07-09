extern int func_ov002_02061830();
extern int data_ov002_0207f628;

void func_ov002_0205f980(void) {
    int p = *(int *)&data_ov002_0207f628;
    func_ov002_02061830(p + 0x1f0, 1);
    *(int *)(p + 0x48) = 1;
}
