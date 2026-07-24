/* Idle-tick for a node: when it is not busy (+0x30 == 0) and fully idle (+0x24/+0x28/+0x2c all
 * zero), sample the touch state (func_ov008_02055dcc); if it is clear, advance the timed value
 * (func_02020400 over +0x18+1 and +0x1e78, a 64-bit result) and publish its high word.
 *
 * The old NONMATCHING note blamed "a guard-merge heuristic: build 139 folds the standalone
 * `if (+0x30 != 0) return;` into the following idle-AND conditional-compare chain". It is not a
 * heuristic and not the build. Two ordinary source bugs:
 *   - the touch record is `unsigned short`, not `short`: the ROM reads it with `ldrh`, and a
 *     signed array gives `ldrsh`;
 *   - the ROM has THREE separate predicated early returns, so all three guards must be written
 *     as early returns. Writing the idle test as a nested `if (a==0 && b==0 && c==0) { ... }`
 *     instead of `if (a!=0 || b!=0 || c!=0) return;` is what let mwcc fold the +0x30 guard into
 *     the same conditional-compare chain, costing 8 bytes. */
extern void func_ov008_02055dcc(void *out);
extern long long func_02020400(int a, unsigned int b);
extern void func_ov008_02062d00(int ctx, int high, int flag);

void func_ov008_02066a4c(int param_1) {
    unsigned short local[3];
    long long r;
    if (*(int *)(param_1 + 0x30) != 0) {
        return;
    }
    if (*(int *)(param_1 + 0x24) != 0 || *(int *)(param_1 + 0x28) != 0 ||
        *(int *)(param_1 + 0x2c) != 0) {
        return;
    }
    func_ov008_02055dcc(local);
    if (local[2] != 0) {
        return;
    }
    r = func_02020400(*(int *)(param_1 + 0x18) + 1, *(unsigned int *)(param_1 + 0x1e78));
    func_ov008_02062d00(param_1, (int)((unsigned long long)r >> 32), 1);
}
