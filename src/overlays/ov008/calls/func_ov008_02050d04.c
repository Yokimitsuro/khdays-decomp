/* func_ov008_02050d04 -- allocate and register a 0x10-byte UI-code node holding param_1.
 * Returns 0 for a zero code; otherwise allocs+zeros the node, stores the code, appends it to the
 * shared code list (ctx+0x9660), and returns it. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MI_CpuFill8(void *dst, int val, unsigned int size);
extern void NNS_FndAppendListObject(void *list, void *obj);
extern int  data_ov008_02090f04[];   /* [1] -> shared screen context */

unsigned int *func_ov008_02050d04(unsigned int param_1) {
    unsigned int *node;
    if (param_1 == 0) {
        return (unsigned int *)param_1;
    }
    node = (unsigned int *)NNSi_FndAllocFromDefaultExpHeap(0x10);
    MI_CpuFill8(node, 0, 0x10);
    *node = param_1;
    NNS_FndAppendListObject((void *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x9660), node);
    return node;
}
