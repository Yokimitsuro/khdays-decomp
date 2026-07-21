/* OS_GetTickLo: reads the low 16 bits of the tick timer (TM0CNT_L, 0x04000100). */

int OS_GetTickLo(void) {
    return *(volatile unsigned short *)0x04000100;
}
