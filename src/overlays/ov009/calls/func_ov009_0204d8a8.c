/* func_ov009_0204d8a8 -- resolve UI code param_1 to its slot's tile buffer.
 * Maps the code to a slot index (func_ov009_0204d818); if valid, returns the slot's tile pointer
 * at ctx+idx*4+0x95a4 (else 0). When param_2 is non-null, also writes the slot index there. */
extern int func_ov009_0204d818(int code);
extern int data_ov009_020563e4[];   /* [1] -> shared screen context */

int func_ov009_0204d8a8(int param_1, int *param_2) {
    int idx = func_ov009_0204d818(param_1);
    int val = 0;
    if (idx != -1) {
        val = *(int *)(*(int *)((int)data_ov009_020563e4 + 4) + idx * 4 + 0x95a4);
    }
    if (param_2 != 0) {
        *param_2 = idx;
    }
    return val;
}
