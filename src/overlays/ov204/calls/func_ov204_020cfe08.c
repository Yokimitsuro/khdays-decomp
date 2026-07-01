extern void DestroyInstance(int *obj);
extern void FreeInstanceMemory(int obj);
extern void func_ov107_020c9eac(int v);
extern void func_ov107_020c68ec(char *obj);

void func_ov204_020cfe08(char *obj) {
    int i;
    DestroyInstance(*(int **)(obj + 0x384));
    func_ov107_020c9eac(*(int *)(obj + 0x390));
    for (i = 0; i < 7; i++) {
        DestroyInstance(*(int **)(*(char **)(obj + 0x394) + i * 8));
    }
    FreeInstanceMemory(*(int *)(obj + 0x394));
    func_ov107_020c68ec(obj);
}
