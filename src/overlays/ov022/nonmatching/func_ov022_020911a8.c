/* NONMATCHING: branch-layout tie. mwcc lays the state==0 vs state==1 dispatch
 * blocks (out-of-line/inline) opposite to the original regardless of if-order or
 * switch. Same 72B. Dispatches to func_ov022_020a0fb8 (state 0) or _020a1064
 * (state 1) on *(arg1+4), passing *(arg0+8). */
extern int *func_ov022_020a0fb8(unsigned int *a, int *b, unsigned int *c);
extern int *func_ov022_020a1064(unsigned int *a, int *b, unsigned int *c);
int *func_ov022_020911a8(int arg0, int arg1, int *arg2, unsigned int *arg3) {
    int state = *(int *)(arg1 + 4);
    unsigned int *base = *(unsigned int **)(arg0 + 8);
    if (state == 0) arg2 = func_ov022_020a0fb8(base, arg2, arg3);
    else if (state == 1) arg2 = func_ov022_020a1064(base, arg2, arg3);
    return arg2;
}
