extern int func_ov107_020c9f48(void *obj, int *vec);
extern void func_0202f384(void *dst, void *mtx, int *vec);
extern void func_01ffa724(int scale, void *v, void *out);
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov133_020d49cc[];
extern void func_ov133_020d3404(void);

void func_ov133_020d3338(char *obj) {
    int *state = *(int **)(obj + 4);
    short pair[2];
    int vec[3];
    int scale;
    scale = func_ov107_020c9f48(*(void **)(*state + 0x3c8), vec);
    func_0202f384((void *)(state + 6), (void *)(*state + 0xa0), vec);
    func_01ffa724(scale, (void *)(state + 6), (void *)(state + 6));
    if (*(unsigned char *)state[0x12] == 0) {
        short *pp = pair;
        void (*cb)();
        pp[1] = data_ov133_020d49cc[1];
        pp[0] = data_ov133_020d49cc[0];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
        func_ov107_020c9264(*state, 10, 1);
        state[0x15] = 0;
        state[0xf] = 0x300;
        func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov133_020d3404);
    }
}
