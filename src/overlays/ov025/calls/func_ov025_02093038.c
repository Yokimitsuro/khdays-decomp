/* func_ov025_02093038 -- rebuild every grid hit cell: resets the layer (func_ov025_02092f5c),
 * re-registers each node in the list at obj+0x1e7c with its (page, col, row) keys, then flushes
 * the renderer at obj+0xac. */
extern void func_ov025_02092f5c(int obj);
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern void func_ov025_02092a34(int obj, int node, unsigned int page, unsigned int col,
                                unsigned int row, int flag);
extern void func_020300f8(int renderer);

void func_ov025_02093038(int param_1) {
    int n;
    func_ov025_02092f5c(param_1);
    for (n = NNS_FndGetNextListObject((void *)(param_1 + 0x1e7c), 0); n != 0;
         n = NNS_FndGetNextListObject((void *)(param_1 + 0x1e7c), n)) {
        func_ov025_02092a34(param_1, n, *(unsigned short *)(n + 10),
                            *(unsigned short *)(n + 0xc), *(unsigned short *)(n + 0xe), 0);
    }
    func_020300f8(param_1 + 0xac);
}
