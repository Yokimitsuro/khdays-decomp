extern int data_ov002_0207f60c;

int func_ov002_02053dc4(void) {
    int p = *(int *)&data_ov002_0207f60c;
    return p == 0 ? 0 : *(unsigned char *)(p + 0x11);
}
