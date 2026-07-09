extern int data_ov002_0207f99c;

int func_ov002_0206629c(void) {
    int p = *(int *)&data_ov002_0207f99c;
    return p == 0 ? 0 : *(int *)(p + 0x14);
}
