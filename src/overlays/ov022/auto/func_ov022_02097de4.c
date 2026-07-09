void func_ov022_02097de4(int arg0) {
    char *p = (char *)(arg0 + 0x2bb0);
    if ((*(unsigned int *)(arg0 + 0x24) & 4) == 0) return;
    p[0] = 0;
    p[1] = 0;
    *(int *)(arg0 + 0x1c70) = 0;
    *(int *)(arg0 + 0x1d98) = 0;
}
