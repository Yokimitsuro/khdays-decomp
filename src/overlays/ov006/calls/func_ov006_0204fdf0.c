/* func_ov006_0204fdf0 -- store param_1 at ctx+0x42a, and (only when the tick source is up)
 * mirror it into the per-tick slot at ctx + tick + 0x48e. */
extern int data_ov006_020565e4;   /* -> title-screen context */
extern int OS_IsTickAvailable(void);

void func_ov006_0204fdf0(unsigned char param_1) {
    *(unsigned char *)(data_ov006_020565e4 + 0x42a) = param_1;
    if (OS_IsTickAvailable() != 0) {
        return;
    }
    *(unsigned char *)(data_ov006_020565e4 + OS_IsTickAvailable() + 0x48e) = param_1;
}
