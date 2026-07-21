extern int func_02021994(int vm, unsigned short *pc);
extern int func_02021980(int vm, unsigned short *pc);
/* Script op: read an fx32 value and a slot index, store the value into the VM's per-slot block
 * (*(vm+0x128) + idx*0x104 + 0x11c). */
int func_ov023_020862bc(int vm, unsigned short *pc) {
    int value = func_02021994(vm, pc);
    int idx = func_02021980(vm, pc + 4);
    *(int *)(*(int *)(vm + 0x128) + idx * 0x104 + 0x11c) = value;
    return 1;
}
