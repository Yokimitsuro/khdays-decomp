extern int data_ov002_0207f60c;

void func_ov002_02053d94(int arg0) {
    int p = *(int *)&data_ov002_0207f60c;
    if (p != 0) {
        *(int *)(p + 4) = arg0;
    }
}
