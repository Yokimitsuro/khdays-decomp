extern void DestroyInstance(int *obj);
extern void FreeInstanceMemory(int obj);
extern void func_ov107_020c9eac(int v);
extern void func_ov107_020c68ec(char *obj);

void func_ov161_020cc214(char *obj) {
    int i;
    DestroyInstance(*(int **)(obj + 0x384));
    func_ov107_020c9eac(*(int *)(obj + 0x3c8));
    for (i = 0; i < 6; i++) {
        DestroyInstance(*(int **)(*(char **)(obj + 0x3c4) + i * 8));
    }
    FreeInstanceMemory(*(int *)(obj + 0x3c4));
    func_ov107_020c68ec(obj);
}
