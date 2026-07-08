extern void func_01ffa724(int factor, void *src, void *dst);
extern void func_0202f384(void *dst, void *mtx, int *vec);
extern void func_0203c634(void *node, int idx, void *value);
extern int func_ov107_020c9f48(void *obj, int *vec);
extern void func_ov205_020d5060(void);

void func_ov205_020d4ff0(int node)
{
    int vec[3];
    int *state = *(int **)(node + 4);
    int factor = func_ov107_020c9f48(*(void **)(*state + 0x390), vec);

    func_0202f384((void *)(state + 2), (void *)(*state + 0xa0), vec);
    func_01ffa724(factor, state + 2, state + 2);
    if (factor != 0) {
        return;
    }
    func_0203c634((void *)node, *(signed char *)(node + 0x20), func_ov205_020d5060);
}
