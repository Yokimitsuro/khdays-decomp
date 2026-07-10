/* NONMATCHING: byte-perfect structure, unsteerable callee-saved register-
 * coloring tie. Orig colors {result=r4, arg0=r5, base=r6, p=r7} by live-range
 * priority; mwcc permutes to {arg0=r4, p=r5, result=r6, base=r7} and no
 * declaration order (6 permutations tried) flips it. Semantics are exact. */
extern int func_ov022_020ad114(int arg0);
extern int func_ov022_020ad0c0(int arg0);
extern void func_01ff8bc4(int *a, int *b, int *c);
extern int func_01ff8cb8(int *a);
extern int func_ov022_0209bd04(int arg0);

int func_ov022_02095dc8(int arg0) {
    int result = 0;
    char *base = (char *)(arg0 + 0x8c);
    if (func_ov022_020ad114(arg0)) {
        int *p = (int *)func_ov022_020ad0c0(arg0);
        int stack[3];
        func_01ff8bc4(p, (int *)(base + 0x400), stack);
        stack[1] = 0;
        if (p[1] - *(int *)(base + 0x404) >= 0x2000 &&
            func_01ff8cb8(stack) <= 0x6000 &&
            func_ov022_0209bd04(arg0) != 1) {
            result = 1;
        }
    }
    return result;
}
