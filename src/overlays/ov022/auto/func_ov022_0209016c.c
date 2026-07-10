void func_ov022_0209016c(char *obj) {
    int i;
    int *q;
    *(short *)obj = 0;
    *(int *)(obj + 8) = 0;
    obj[2] = 0;
    *(int *)(obj + 0x54) = 0;
    *(int *)(obj + 0xc) = -1;
    *(int *)(obj + 0x10) = -1;
    q = (int *)obj;
    for (i = 0; i < 15; i++) { q[6] = 0; q++; }
    *(unsigned short *)(obj + 0x6c) = 0xffff;
}
