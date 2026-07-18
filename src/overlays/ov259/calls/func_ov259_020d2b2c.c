extern void func_01ffa724(int scale, void *src, void *dst);

struct vec3 { int a, b, c; };
extern struct vec3 data_02041dc8;

void func_ov259_020d2b2c(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c6) == 0) {
        *(struct vec3 *)(state + 3) = data_02041dc8;
    } else if (*(signed char *)(*state + 0x1c6) == 1) {
        func_01ffa724(0x500, state + 6, state + 3);
    }
    *(struct vec3 *)(*state + 0xf0) = *(struct vec3 *)(state + 3);
}
