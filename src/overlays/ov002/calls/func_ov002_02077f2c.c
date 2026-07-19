extern int func_ov002_0207285c(int slot);
extern char data_ov002_0207fa28;

extern void func_0202c5b8(void *actor, unsigned short id);

/* Same as func_ov002_02077ef8 but binds the resolved model id instead. */
void func_ov002_02077f2c(int slot) {
    int off = slot * 0x184;
    int id;
    if (*(int *)(*(char **)((char *)&data_ov002_0207fa28 + 4) + off + 0xc4) != 0) {
        id = func_ov002_0207285c(slot);
        if (id >= 0) {
            func_0202c5b8(*(char **)((char *)&data_ov002_0207fa28 + 4) + 0xb8 + off,
                          (unsigned short)id);
        }
    }
}
