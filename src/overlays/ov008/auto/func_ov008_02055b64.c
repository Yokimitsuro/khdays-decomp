/* func_ov008_02055b64 -- (re)arm an animation node: zero its accumulator
 * (+0x14/+0x18), stamp the current time (+0x1c), rewind to frame 0 (+4) and hand
 * that frame to the resolver. See func_ov008_020551a4 for the ticker. */
extern long long func_020031d4(void);
extern void func_ov008_0205589c(int owner, int tag);

void func_ov008_02055b64(int param_1, int param_2) {
    *(int *)(param_2 + 0x14) = 0;
    *(int *)(param_2 + 0x18) = 0;
    *(long long *)(param_2 + 0x1c) = func_020031d4();
    *(unsigned short *)(param_2 + 4) = 0;
    func_ov008_0205589c(param_1,
        *(int *)(*(int *)(param_2 + 0x2c) + *(unsigned short *)(param_2 + 4) * 4));
}
