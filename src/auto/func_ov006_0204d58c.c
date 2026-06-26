void *func_ov006_0204d58c(int *s, int idx) {
    unsigned int count = s[1];
    char *p = (char *)s[2];
    int i;
    if ((unsigned int)idx >= count) {
        return 0;
    }
    for (i = 0; i < idx; i++) {
        p += *(int *)p;
    }
    return p + 4;
}
