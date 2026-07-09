extern int data_ov002_0207f624;

int func_ov002_0205f488(void) {
    int p = *(int *)&data_ov002_0207f624;
    return p != 0 && *(int *)p == 0;
}
