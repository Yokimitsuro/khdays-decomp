extern int func_ov022_020a1064(unsigned int *arg0, int *arg1, unsigned int *arg2);
int func_ov022_0208ac80(int arg0, int *arg1, unsigned int *arg2) {
    unsigned int *p = *(unsigned int **)(arg0 + 0x58);
    int r = 0;
    if (func_ov022_020a1064(p, arg1, arg2) != 0) {
        unsigned int f = p[0x9af];
        if (f & 1) r = 2;
        else if (f & 4) r = 2;
        else r = 1;
    }
    return r;
}
