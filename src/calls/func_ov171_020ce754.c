extern void func_0203c9d0(void *a, void *b);

struct vec3 { int a, b, c; };
extern struct vec3 data_02041dc8;

void func_ov171_020ce754(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c6) == 1) {
        func_0203c9d0((void *)(*state + 0xa0), state + 8);
    } else {
        *(struct vec3 *)(state + 0xc) = data_02041dc8;
    }
    *(struct vec3 *)(*state + 0xf0) = *(struct vec3 *)(state + 0xc);
}
