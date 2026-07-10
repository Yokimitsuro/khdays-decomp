/* Waits for the hardware divider to finish, then reads the 64-bit quotient. */
long long func_01ff8ab0(void) {
    while (*(volatile unsigned short *)0x4000280 & 0x8000)
        ;
    return *(long long *)0x40002a0;
}
