extern int func_0202a7dc(void *);

int func_ov075_020b989c(void *obj) {
    char *p = (char *)obj + 0x2c80;
    *(int *)p = 0;
    return func_0202a7dc(p + 0xc);
}
