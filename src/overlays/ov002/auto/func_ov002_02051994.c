extern int data_ov002_0207f600;

void func_ov002_02051994(void) {
    int p = *(int *)&data_ov002_0207f600;
    *(int *)p |= 8;
}
