extern int data_ov002_0207f60c;

void func_ov002_02053790(int arg0) {
    int p = *(int *)&data_ov002_0207f60c;
    if ((unsigned int)arg0 > 0x10) {
        arg0 = 0x10;
    }
    *(char *)(p + 0x11) = arg0;
    *(char *)(p + 0x10) = (arg0 & 0xff) != 0 ? 1 : 2;
}
