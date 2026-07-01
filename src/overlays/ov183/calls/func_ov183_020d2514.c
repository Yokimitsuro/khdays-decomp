extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void func_ov183_020d2548(void);

void func_ov183_020d2514(char *obj) {
    char *p = *(char **)(obj + 4);
    if (**(char **)(p + 0xc) != 0) return;
    *(int *)(p + 0x1c) = 0;
    SetIndexedSlot(obj, *(signed char *)(obj + 0x20), func_ov183_020d2548);
}
