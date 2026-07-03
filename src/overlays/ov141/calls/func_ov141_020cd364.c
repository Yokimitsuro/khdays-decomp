extern int func_ov107_020c9f48(void *obj, int *vec);
extern void func_0202f384(void *dst, void *mtx, int *vec);
extern void func_01ffa724(int scale, void *v, void *out);
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov141_020ce9d0[];

void func_ov141_020cd364(char *obj) {
    int *state = *(int **)(obj + 4);
    short pair[2];
    int vec[3];
    int scale;
    scale = func_ov107_020c9f48(*(void **)(*state + 0x3cc), vec);
    func_0202f384((void *)(state + 6), (void *)(*state + 0xa0), vec);
    func_01ffa724(scale, (void *)(state + 6), (void *)(state + 6));
    if (*(unsigned char *)state[0x11] == 0) {
        short *pp = pair;
        void (*cb)();
        pp[1] = data_ov141_020ce9d0[1];
        pp[0] = data_ov141_020ce9d0[0];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(obj, *(signed char *)(obj + 0x20), (void *)0);
    }
}
