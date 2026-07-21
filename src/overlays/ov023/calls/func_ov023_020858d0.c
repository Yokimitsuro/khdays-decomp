extern int func_02021980(int vm, unsigned short *pc);
extern int func_ov023_02089208(int entry, int arg);
/* Script op: read an entity index and an argument, then run the action on that entity's entry
 * (*(vm+0x128)+0x440, stride 0x1a64); returns 1 on success. */
int func_ov023_020858d0(int vm, unsigned short *pc) {
    int idx = func_02021980(vm, pc);
    int arg = func_02021980(vm, pc + 4);
    if (func_ov023_02089208(*(int *)(*(int *)(vm + 0x128) + 0x440) + idx * 0x1a64, arg) != 0) {
        return 1;
    }
    return 0;
}
