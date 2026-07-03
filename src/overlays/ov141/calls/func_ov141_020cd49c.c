struct b1 { unsigned char b : 1; };
extern int func_ov107_020c9f48(void *obj, int *vec);
extern void func_0202f384(void *dst, void *mtx, int *vec);
extern void func_01ffa724(int scale, void *v, void *out);
extern void VEC_Add(void *a, void *b, void *out);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov141_020cd49c(char *obj) {
    int *state = *(int **)(obj + 4);
    int vec[3];
    int scale;
    scale = func_ov107_020c9f48(*(void **)(*state + 0x3cc), vec);
    func_0202f384((void *)(state + 6), (void *)(*state + 0xa0), vec);
    func_01ffa724(scale, (void *)(state + 6), (void *)(state + 6));
    VEC_Add((void *)(state + 6), (void *)(state + 9), (void *)(state + 6));
    func_01ffa724(0xb00, (void *)(state + 9), (void *)(state + 9));
    if (*(unsigned char *)state[0x11] == 0) {
        if (((struct b1 *)(*state + 0x17a))->b || ((struct b1 *)(*state + 0x17c))->b) {
            *(signed char *)(*state + 0x1c7) = 2;
            func_0203c634(obj, *(signed char *)(obj + 0x20), (void *)0);
        }
    }
}
