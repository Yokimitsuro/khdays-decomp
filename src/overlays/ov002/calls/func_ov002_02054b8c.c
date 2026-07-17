/* func_ov002_02054b8c -- (re)arm an animation node: zero its accumulator
 * (+0x14/+0x18), stamp the current time (+0x1c), rewind to frame 0 (+4) and hand
 * that frame to the resolver. See func_ov002_020540f0 for the ticker. */
extern long long func_020031d4(void);
extern void func_ov002_02054878(int owner, int tag);

void func_ov002_02054b8c(int param_1, int param_2) {
    *(int *)(param_2 + 0x14) = 0;
    *(int *)(param_2 + 0x18) = 0;
    *(long long *)(param_2 + 0x1c) = func_020031d4();
    *(unsigned short *)(param_2 + 4) = 0;
    func_ov002_02054878(param_1,
        *(int *)(*(int *)(param_2 + 0x2c) + *(unsigned short *)(param_2 + 4) * 4));
}
