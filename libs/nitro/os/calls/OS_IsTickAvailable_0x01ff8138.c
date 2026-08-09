/* OS_IsTickAvailable: returns the tick-availability flag held at data_027e0068. */

extern unsigned short data_027e0068;

int OS_IsTickAvailable_0x01ff8138(void) {
    return data_027e0068;
}
