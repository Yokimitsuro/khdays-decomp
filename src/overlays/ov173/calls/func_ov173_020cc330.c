extern void DestroyInstance(int *obj);
extern void FreeInstanceMemory(int obj);
extern void func_ov107_020c68ec(char *obj);

void func_ov173_020cc330(char *obj) {
    int i;
    DestroyInstance(*(int **)(obj + 0x384));
    for (i = 0; i < 4; i++) {
        DestroyInstance(*(int **)(*(char **)(obj + 0x39c) + i * 8));
    }
    FreeInstanceMemory(*(int *)(obj + 0x39c));
    func_ov107_020c68ec(obj);
}
