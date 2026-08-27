extern void func_01ffa724(int scale, void *src, void *dst);
extern void func_0202ed60(void *out, void *mtx, void *vec);
extern void func_0203c9d0(void *a, void *b);

struct vec3 { int a, b, c; };
extern struct vec3 data_02041dc8;
extern int data_02042258;

void func_ov176_020d2238(int *node) {
    int *state = (int *)node[1];
    unsigned int tmp[4];
    if (*(signed char *)(*state + 0x1c6) == 1) {
        func_01ffa724(0x600, state + 5, state + 2);
        func_0202ed60(tmp, &data_02042258, state + 5);
        func_0203c9d0((void *)(*state + 0xa0), tmp);
    } else {
        *(struct vec3 *)(state + 2) = data_02041dc8;
    }
    *(struct vec3 *)(*state + 0xf0) = *(struct vec3 *)(state + 2);
}
