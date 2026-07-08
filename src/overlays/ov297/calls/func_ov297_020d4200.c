extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *dst, void *src);

int func_ov297_020d4200(int node, int x, int y, int z) {
    int diff[3];

    VEC_Subtract(&x, (void *)(**(int **)(node + 4) + 0xb0), diff);
    return func_01ff8d18(diff, diff);
}
