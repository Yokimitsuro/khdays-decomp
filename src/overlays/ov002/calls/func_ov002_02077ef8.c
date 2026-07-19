extern int func_ov002_0207285c(int slot);
extern char data_ov002_0207fa28;

extern void func_0202c5e4(void *actor);

/* Kicks the slot's actor into its default pose, if the slot is occupied and mapped. */
void func_ov002_02077ef8(int slot) {
    int off = slot * 0x184;
    if (*(int *)(*(char **)((char *)&data_ov002_0207fa28 + 4) + off + 0xc4) != 0) {
        if (func_ov002_0207285c(slot) >= 0) {
            func_0202c5e4(*(char **)((char *)&data_ov002_0207fa28 + 4) + 0xb8 + off);
        }
    }
}
