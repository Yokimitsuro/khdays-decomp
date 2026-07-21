/* When the node is not busy (+0x30 == 0) and fully idle (+0x24/+0x28/+0x2c all zero), sample the
 * touch state (func_ov008_02055dcc); if it is clear, advance the timed value (func_02020400 of
 * +0x18+1 and +0x1e78, a 64-bit result) and publish its high word via func_ov008_02062d00.
 *
 * NON-MATCHING (equivalent). Semantics, the idle 3-way AND, the stack touch record, and the
 * 64-bit high-word pass (r1 left in place from func_02020400's return) are all right. The only
 * residue is a guard-merge heuristic: build 139 folds the standalone `if (+0x30 != 0) return;`
 * into the following idle-AND conditional-compare chain (one shared predicated exit), whereas the
 * ROM keeps the +0x30 test as its own predicated return and starts the AND with a fresh
 * unconditional load. 8 bytes. Same over-aggressive late-merge theme as func_ov008_0208a5e8;
 * tried simple-AND, explicit-boolean, and volatile-guard spellings. */
extern void func_ov008_02055dcc(void *out);
extern long long func_02020400(int a, unsigned int b);
extern void func_ov008_02062d00(int ctx, int high, int flag);

void func_ov008_02066a4c(int param_1) {
    short local[3];
    if (*(int *)(param_1 + 0x30) != 0) {
        return;
    }
    if (*(int *)(param_1 + 0x24) == 0 && *(int *)(param_1 + 0x28) == 0 && *(int *)(param_1 + 0x2c) == 0) {
        func_ov008_02055dcc(local);
        if (local[2] == 0) {
            long long r = func_02020400(*(int *)(param_1 + 0x18) + 1, *(unsigned int *)(param_1 + 0x1e78));
            func_ov008_02062d00(param_1, (int)((unsigned long long)r >> 32), 1);
        }
    }
}
