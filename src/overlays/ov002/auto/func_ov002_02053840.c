extern int data_ov002_0207f60c;

int func_ov002_02053840(void) {
    int p = *(int *)&data_ov002_0207f60c;
    return p == 0 ? 1 : (*(unsigned int *)(p + 0xd8) << 0x1d >> 0x1f);
}
