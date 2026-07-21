extern int func_02021980(int vm, unsigned short *pc);
extern int func_ov023_02086b34(int slot);
/* Script op: read a slot index (-1 selects the VM's current slot at +0x488), then run the
 * predicate on that slot's block; returns 1 when it holds. */
int func_ov023_02086bb8(int vm, unsigned short *pc) {
    int idx = func_02021980(vm, pc);
    if (idx == -1) {
        idx = *(int *)(*(int *)(vm + 0x128) + 0x488);
    }
    if (func_ov023_02086b34(*(int *)(vm + 0x128) + 0x30 + idx * 0x104) != 0) {
        return 1;
    }
    return 0;
}
