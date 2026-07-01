extern void DestroyInstance(int *obj);
extern void FreeInstanceMemory(int obj);
extern void func_ov107_020c9eac(int v);
extern void func_ov107_020c68ec(char *obj);

void func_ov293_020d1c74(char *obj) {
    int i;
    DestroyInstance(*(int **)(obj + 0x384));
    func_ov107_020c9eac(*(int *)(obj + 0x39c));
    for (i = 0; i < 2; i++) {
        DestroyInstance(*(int **)(*(char **)(obj + 0x3a0) + i * 8));
    }
    FreeInstanceMemory(*(int *)(obj + 0x3a0));
    func_ov107_020c68ec(obj);
}
