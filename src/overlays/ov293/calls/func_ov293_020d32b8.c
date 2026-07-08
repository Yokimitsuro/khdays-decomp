typedef struct {
    int x;
    int y;
    int z;
} Vec3i;

extern int func_ov107_020c9f48(void *src, void *out);
extern void func_0202f384(void *dst, void *base, void *vec);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void func_0203c634(void *node, int idx, void *next);
extern void func_ov293_020d3340(void);

void func_ov293_020d32b8(void *node)
{
    int vec[3];
    int *state;
    int scale;

    state = *(int **)((char *)node + 4);
    scale = func_ov107_020c9f48(*(void **)(state[0] + 0x39c), vec);
    func_0202f384(state + 7, (void *)(state[0] + 0xa0), vec);
    func_01ffa724(scale, state + 7, state + 7);

    if (**(unsigned char **)((char *)state + 0x4c) != 0) {
        return;
    }

    *(Vec3i *)((char *)state + 0x28) = *(Vec3i *)((char *)state + 0x1c);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov293_020d3340);
}
