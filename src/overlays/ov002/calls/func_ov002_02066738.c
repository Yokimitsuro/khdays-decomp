/* Clear the VRAM/OAM region *(param_1+8) sized (u8@+6 * u8@+7) * 0x20 bytes. */
extern void INITi_CpuClear32_0x01ff86fc(int val, int dst, int size);

void func_ov002_02066738(int param_1) {
    INITi_CpuClear32_0x01ff86fc(0, *(int *)(param_1 + 8),
        (*(unsigned char *)(param_1 + 6) * *(unsigned char *)(param_1 + 7)) << 5);
}
