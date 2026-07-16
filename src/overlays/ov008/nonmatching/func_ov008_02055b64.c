/* NONMATCHING: instruction-selection tie — the ROM reuses a zero register both to clear the +4
 * half-word and as the index in the `**(node+0x2c)` deref (ldr [r0,r2]); mwcc uses an immediate
 * #0 offset (ldr [r1]). Semantically identical, one byte-pattern apart. */
/* func_ov008_02055b64 -- (re)arm a tag-tracker node: zero its accumulators (+0x14/+0x18), stamp
 * the current time (+0x1c, 64-bit), clear its state half-word (+4), and re-resolve its first tag
 * (func_ov008_0205589c on **(node+0x2c)). */
extern long long func_020031d4(void);
extern void func_ov008_0205589c(int owner, int tag);

void func_ov008_02055b64(int param_1, int param_2) {
    *(int *)(param_2 + 0x14) = 0;
    *(int *)(param_2 + 0x18) = 0;
    *(long long *)(param_2 + 0x1c) = func_020031d4();
    *(short *)(param_2 + 4) = 0;
    func_ov008_0205589c(param_1, **(int **)(param_2 + 0x2c));
}
