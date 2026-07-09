extern int data_ov002_0207f9f8;

int func_ov002_02067044(int arg0) {
    int p = *(int *)&data_ov002_0207f9f8;
    return p == 0 ? 0 : arg0 * 0xc + *(int *)(p + 8);
}
