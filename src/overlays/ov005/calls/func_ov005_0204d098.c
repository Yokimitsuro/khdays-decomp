/* Construct the 0x4c-byte container at param_1 from the config at param_2: zero it, init
 * its embedded list (link offset 0x2c), copy the five counts/config words to +0x30..+0x40,
 * then allocate and zero the three element arrays (counts * 0x38 / 0x30 / 0x10) at +0xc/+0x10/+0x14. */
extern void MI_CpuFill8(void *dst, int val, int size);
extern void NNS_FndInitList(int list, int offset);
extern int NNSi_FndAllocFromDefaultExpHeap(int size);
void func_ov005_0204d098(int param_1, int param_2) {
    MI_CpuFill8((void *)param_1, 0, 0x4c);
    NNS_FndInitList(param_1, 0x2c);
    *(int *)(param_1 + 0x30) = *(int *)param_2;
    *(int *)(param_1 + 0x34) = *(int *)(param_2 + 4);
    *(int *)(param_1 + 0x38) = *(int *)(param_2 + 8);
    *(int *)(param_1 + 0x3c) = *(int *)(param_2 + 0xc);
    *(int *)(param_1 + 0x40) = *(int *)(param_2 + 0x10);
    *(int *)(param_1 + 0xc) = NNSi_FndAllocFromDefaultExpHeap(*(int *)param_2 * 0x38);
    *(int *)(param_1 + 0x10) = NNSi_FndAllocFromDefaultExpHeap(*(int *)(param_2 + 4) * 0x30);
    *(int *)(param_1 + 0x14) = NNSi_FndAllocFromDefaultExpHeap(*(int *)(param_2 + 8) << 4);
    MI_CpuFill8((void *)*(int *)(param_1 + 0xc), 0, *(int *)param_2 * 0x38);
    MI_CpuFill8((void *)*(int *)(param_1 + 0x10), 0, *(int *)(param_2 + 4) * 0x30);
    MI_CpuFill8((void *)*(int *)(param_1 + 0x14), 0, *(int *)(param_2 + 8) << 4);
}
