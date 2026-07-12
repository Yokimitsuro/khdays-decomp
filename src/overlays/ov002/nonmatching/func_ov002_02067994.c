/* PROVEN TIE (THUMB addressing/allocation). Dedup twin of func_ov025_020b0864.
 * mwcc build 139 materializes param_1+0xc as a pointer (two extra THUMB adds)
 * while the ROM re-uses [r0,#0xc] addressing for the store, keeping the node data
 * pointer in a scratch. Same semantics; kept here so the ov002 blob stays byte-exact. */
int func_ov002_02067994(int param_1) {
    int node = *(int *)(param_1 + 0xc);
    int result = 0;
    if (node != 0) {
        int delta = *(int *)node;
        result = node + 4;
        if (delta != 0) {
            *(int *)(param_1 + 0xc) = node + delta;
        } else {
            *(int *)(param_1 + 0xc) = 0;
        }
    }
    return result;
}
