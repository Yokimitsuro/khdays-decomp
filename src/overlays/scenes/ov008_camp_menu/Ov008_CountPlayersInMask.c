/* Count the set bits among bits 0-3 of a 16-bit value: from *param_1 when the
 * pointer is non-null, else from OS_IsTickAvailable(). */
extern unsigned short WH_GetBitmap(void);

int Ov008_CountPlayersInMask(unsigned short *param_1) {
    int value;
    unsigned char count = 0;
    unsigned char i;
    if (param_1 != 0) value = *param_1;
    else value = WH_GetBitmap();
    for (i = 0; i < 4; i++) {
        if (value & (1 << i)) count++;
    }
    return count;
}
