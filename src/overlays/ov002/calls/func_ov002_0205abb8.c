extern int data_ov002_0207f620;
extern int func_ov002_02053510();

int func_ov002_0205abb8(int arg0, int arg1) {
    int base = *(int *)&data_ov002_0207f620;
    return func_ov002_02053510(*(int *)(base + arg0 * 4 + 0x620), *(int *)(base + arg1 * 4 + 0x5f4));
}
