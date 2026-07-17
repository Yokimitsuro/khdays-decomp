/* func_ov008_02055aec -- arm or disarm an animation node (see func_ov008_020551a4
 * for the ticker that consumes these). Arming a node that was not already armed
 * resets its accumulator (+0x14/+0x18), stamps the current time (+0x1c) and
 * re-resolves its selected frame. Bit 0 of node+0x24 records the armed state. */
extern long long func_020031d4(void);
extern void func_ov008_0205589c(int owner, int tag);

struct NodeFlags { unsigned char armed : 1, visible : 1; };

void func_ov008_02055aec(int param_1, int param_2, int param_3) {
    char armed = 0;
    if (param_3 != 0) {
        armed = 1;
        if (((struct NodeFlags *)(param_2 + 0x24))->armed != 1) {
            *(int *)(param_2 + 0x14) = 0;
            *(int *)(param_2 + 0x18) = 0;
            *(long long *)(param_2 + 0x1c) = func_020031d4();
            func_ov008_0205589c(param_1,
                *(int *)(*(int *)(param_2 + 0x2c) + *(unsigned short *)(param_2 + 4) * 4));
        }
    }
    ((struct NodeFlags *)(param_2 + 0x24))->armed = armed;
}
