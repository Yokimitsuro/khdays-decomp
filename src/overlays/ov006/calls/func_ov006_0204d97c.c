/* Update slot param_1's cached key/payload in the global table (data_ov006_020565e4): if
 * param_2's key (*param_2) differs from the slot's (+0xc), store it, copy param_2's payload
 * (param_2+1) into the slot's buffer (table+param_1*8+8), and if the table's dirty flag
 * (+0x28) is set, mark slot param_1 dirty (table+param_1*4+0x30 = 1). */
extern void MI_CpuCopy8(void *src, void *dst, unsigned int n);
extern int data_ov006_020565e4;
void func_ov006_0204d97c(int param_1, int *param_2, unsigned int param_3) {
    int key;
    if (param_2 == 0) {
        return;
    }
    key = *param_2;
    if (key != *(int *)(data_ov006_020565e4 + param_1 * 8 + 0xc)) {
        *(int *)(data_ov006_020565e4 + param_1 * 8 + 0xc) = key;
        MI_CpuCopy8(param_2 + 1, *(void **)(data_ov006_020565e4 + param_1 * 8 + 8), param_3);
        if (*(int *)(data_ov006_020565e4 + 0x28) != 0) {
            *(int *)(data_ov006_020565e4 + param_1 * 4 + 0x30) = 1;
        }
    }
}
