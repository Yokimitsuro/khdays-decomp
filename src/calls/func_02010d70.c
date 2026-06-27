extern int func_02010ce4(unsigned int *p);

int func_02010d70(unsigned int **arg0, unsigned int arg1) {
    unsigned int *p = arg0[1];
    if (arg1 > p[10]) return 0;
    return func_02010ce4(p);
}
