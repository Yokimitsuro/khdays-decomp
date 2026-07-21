extern int func_02021980(int vm, unsigned short *pc);
/* Script op: read an int operand and store it into the VM's register block (*(vm+0x128))+0x484. */
int func_ov023_02085844(int vm, unsigned short *pc) {
    int v = func_02021980(vm, pc);
    *(int *)(*(int *)(vm + 0x128) + 0x484) = v;
    return 1;
}
