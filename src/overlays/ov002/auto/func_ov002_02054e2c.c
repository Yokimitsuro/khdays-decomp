/*
 * Set a background scroll register: pack the 9-bit H offset (param_1) and 9-bit V
 * offset (param_2) into the 32-bit register at 0x04001010 (BGxOFS pair).
 */
void func_ov002_02054e2c(unsigned int param_1, unsigned int param_2) {
    *(volatile unsigned int *)0x04001010 =
        (param_1 & 0x1ff) | ((param_2 << 16) & (0x1ff << 16));
}
