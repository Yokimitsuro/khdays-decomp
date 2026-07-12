/* Construct the 0x24-byte manager at param_1 from the config at param_2: zero it, init its
 * embedded list (link offset 0x4c), load the default config table, cache count (+0xc) and
 * acquire resource 0xe (+0x14), then run the sub-init with the two config words. */
extern void MI_CpuFill8(void *dst, int val, int size);
extern void NNS_FndInitList(int list, int offset);
extern void func_ov005_0204e4c0(int a, void *b);
extern int func_0201ef9c(int a, int b);
extern void func_ov005_0204ebdc(int a, int b, int c);
extern int data_ov005_0205b4c0;
void func_ov005_0204ec90(int param_1, int param_2) {
    MI_CpuFill8((void *)param_1, 0, 0x24);
    NNS_FndInitList(param_1 + 0x18, 0x4c);
    func_ov005_0204e4c0(param_1, &data_ov005_0205b4c0);
    *(int *)(param_1 + 0xc) = *(int *)(param_2 + 8);
    *(int *)(param_1 + 0x14) = func_0201ef9c(*(int *)param_2, 0xe);
    func_ov005_0204ebdc(param_1, *(int *)(param_2 + 8), *(int *)(param_2 + 4));
}
