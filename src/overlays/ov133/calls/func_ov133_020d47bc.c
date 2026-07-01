extern int CreateRegistryEntry(int pool, unsigned int size1, unsigned int size2, void *cb, int flags, void **out_entry);
extern void func_ov133_020d484c(void);
extern void func_ov133_020d48cc(void);

void func_ov133_020d47bc(char *obj) {
    void *entry = 0;
    CreateRegistryEntry(*(int *)(obj + 0x3c), 0x64, 0xc, func_ov133_020d484c, (int)func_ov133_020d48cc, &entry);
    *(char **)entry = obj;
}
