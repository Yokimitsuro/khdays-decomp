/* Count the set bits among bits 0-3 of a 16-bit value: from *param_1 when the
 * pointer is non-null, else from OS_IsTickAvailable(). */
extern int OS_IsTickAvailable_0x01ff8138(void);

int func_ov008_0207bc94(unsigned short *param_1) {
    int value;
    unsigned char count = 0;
    unsigned char i;
    if (param_1 != 0) value = *param_1;
    else value = OS_IsTickAvailable_0x01ff8138();
    for (i = 0; i < 4; i++) {
        if (value & (1 << i)) count++;
    }
    return count;
}
