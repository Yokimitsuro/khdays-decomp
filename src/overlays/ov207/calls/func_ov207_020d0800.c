/* Spawn a size-8 registry entry (func_0203c5c0, cbs ccc0/cc3c) into *entry, then link it:
 * entry[0]=self, entry[1]=self's active node (**(self->f3e0)), stamp that node's +0x6c with
 * the ccb78 handler and back-link it to the entry at +0x84. */
extern int func_0203c5c0(int list, int a, int b, void *cb2, void *cb1, int **out);
extern void func_ov207_020d0900(void);
extern void func_ov207_020d087c(void);
extern void func_ov207_020d07b8(void);
int func_ov207_020d0800(int param_1) {
    int *entry;
    int spawn = func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 8,
                              &func_ov207_020d087c, &func_ov207_020d0900, &entry);
    entry[0] = param_1;
    entry[1] = **(int **)(*entry + 0x3e0);
    *(int *)(entry[1] + 0x6c) = (int)&func_ov207_020d07b8;
    *(int **)(entry[1] + 0x84) = entry;
    return spawn;
}
