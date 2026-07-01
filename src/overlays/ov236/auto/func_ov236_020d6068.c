void func_ov236_020d6068(char *obj) {
    int *base = *(int **)(obj + 4);
    int i = 0;
    do {
        int *elem = (int *)base[i + 1];
        *(int *)((char *)elem + 0x5c) |= 2;
        i++;
    } while (i < 2);
}
