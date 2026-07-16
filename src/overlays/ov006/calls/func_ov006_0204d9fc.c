/* func_ov006_0204d9fc -- upload slot param_1's tile data, then clear its pending pointer.
 * If param_2 is non-null, copy param_3 bytes from the slot's source (ctx[param_1].src at
 * ctx+param_1*8+8) into param_2; then zero the per-slot word at ctx+param_1*4+0x30. */
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int  data_ov006_020565e4;   /* -> title-screen context */

void func_ov006_0204d9fc(int param_1, unsigned short *param_2, unsigned int param_3) {
    if (param_2 != 0) {
        MI_CpuCopy8(*(unsigned short **)(data_ov006_020565e4 + param_1 * 8 + 8), param_2, param_3);
    }
    *(int *)(data_ov006_020565e4 + param_1 * 4 + 0x30) = 0;
}
