extern int func_02021980(int obj, void *key);
extern void *func_02021948(int obj, void *key);
extern void *func_02024ee8(void *res, int type);

int func_02022510(int obj, unsigned short *keys, int arg3, int arg4) {
    int idx = func_02021980(obj, keys);
    void *res = func_02021948(obj, keys + 4);
    void *node = func_02024ee8(res, 0xf);
    *(void **)(*(int *)(obj + 0x128) + idx * 4 + 0x48c) = node;
    return 1;
}
