extern void func_01ffa724(int scale, void *src, void *dst);

struct vec3 { int a, b, c; };
extern struct vec3 data_02041dc8;

void func_ov148_020d1eac(int *node) {
    int *state = (int *)node[1];
    if (*(signed char *)(*state + 0x1c6) == 0) {
        *(struct vec3 *)(state + 2) = data_02041dc8;
    } else if (*(signed char *)(*state + 0x1c6) == 1) {
        func_01ffa724(0x800, state + 5, state + 2);
    }
    *(struct vec3 *)(*state + 0xf0) = *(struct vec3 *)(state + 2);
}
